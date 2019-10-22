#######################################################################
# Y -> Jpsi Mu, Jpsi -> Mu Mu (B_c, missing neutrinos)
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *

# OPTIONS
simulation = False; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2012"
from Configurables import CondDB
CondDB().UseLatestTags = ["2012"]

triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    ]
lines = ["StrippingTriMuonBc2ThreeMuDecision"
         , "StrippingBc2JpsiMuLineDecision"
         , "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision"
         , "StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision"
         ]

# RECONSTRUCTED SEQUENCE
from Configurables import GaudiSequencer
recseq = GaudiSequencer("RecSeq")

# TRIGGER LINES / STRIPPING LINE FILTER
from PhysConf.Filters import LoKi_Filters
StripFilt = LoKi_Filters(
    L0DU_Code = "L0_CHANNEL_RE('.*Muon')",
    HLT_Code  = "HLT_PASS_RE( 'Hlt1DiMuon.*MassDecision' ) & HLT_PASS_RE( 'Hlt2DiMuonJPsiHighPTDecision' )",
    STRIP_Code = "HLT_PASS_RE( 'StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision' )"
    )
DaVinci().EventPreFilters = StripFilt.filters("Filters")

# DATA
MuonsLoc = 'Phys/StdNoPIDsMuons/Particles' # has a PT cut > 250 MeV, IP chi^2 > 4 -- making these anyways!
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)

from Configurables import FilterDesktop

MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

MyMuonAlg = FilterDesktop("MyMuonAlg")
MyMuonAlg.Code
MyMuonAlg.Code += " & (TRCHI2DOF < 3)"
MyMuonSel = Selection("MyMuonSel", Algorithm = MyMuonAlg, RequiredSelections = [MuonsSel])

from Configurables import CombineParticles
MyBcAlg = CombineParticles('MyBcAlg')
MyBcAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
MyBcAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBcAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3

MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyJpsiSel, MuonsSel])

MyBcSeq = SelectionSequence("MyBcSeq", TopSelection = MyBcSel)

# ADD ALGORITHM
finalsel = MyBcSeq.sequence()
from Configurables import ReadHltReport
finalsel.Members += [ ReadHltReport() ]
recseq.Members += [ finalsel ]

#########################
### USE UPDATED PID VARIABLES
#########################

#from Configurables import ChargedProtoANNPIDConf
#nnpidseq = GaudiSequencer("ANNGPIDSeq")
#annconf = ChargedProtoANNPIDConf()
#annconf.DataType = "2012"
#annconf.NetworkVersions["2012"] = "MC12TuneV2"
#annconf.RecoSequencer = nnpidseq
#DaVinci().appendToMainSequence( [ nnpidseq ] )


#########################
### DECAYTREETUPLE
#########################

# Create tuple, add all desired tools
tuple = DecayTreeTuple("Bc2JpsiMu_Tuple")
tuple.Inputs = [ MyBcSeq.outputLocation() ]
tuple.Decay = "[B_c+ -> (^J/psi(1S) => ^mu+ ^mu-) ^mu+]cc"
tuple.ToolList = [
    "TupleToolGeometry"
    , "TupleToolKinematic"
    , "TupleToolPid"
    , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
    , "TupleToolEventInfo"
    ]
#truth = tuple.addTupleTool("TupleToolMCTruth")
#truth.ToolList = [
#    "MCTupleToolKinematic"
#    , "MCTupleToolHierarchy"
#    ]

# NUMBER OF REC/TRACKS/BEST
from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
tuple.addTupleTool(LoKiEvtTool,"LHETT")
tuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
tuple.LHETT.VOID_Variables = {
    "nTracks" : "CONTAINS ('Rec/Track/Best') "
    }

# BRANCHES
tuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> (J/psi(1S) => mu+ mu-) mu+]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => mu+ mu-) mu+]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^mu+ mu-) mu+]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => mu+ ^mu-) mu+]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => mu+ mu-) ^mu+]cc"
    })

# J/psi and Mu DOCA and Bc TM info
CHARMONIUM = " [J/psi(1S), psi(2S), chi_c0(1P), chi_c1(1P), chi_c2(1P), X_1(3872), X_2(3872)] "
PI = " [pi+,pi-,pi0] "
K = " [K+,K-,K0,K~0] "
F0 = " [f_0(980),f_0(1370)] "
RHO = " [rho(770)+,rho(770)-,rho(770)0] "
K892 = " [K*(892)+,K*(892)-,K*(892)0,K*(892)~0] "
K1270 = " [K_1(1270)+,K_1(1270)-,K_1(1270)0,K_1(1270)~0] "
K1400 = " [K_1(1400)+,K_1(1400)-,K_1(1400)0,K_1(1400)~0] "
BUEXC = "[B*+,B*-,B*_2+,B*_2-,B*_0+,B*_0-,B_1(L)+,B_1(L)-]"
BDEXC = "[B*0,B*~0,B*_20,B*_2~0,B*_00,B*_0~0,B_1(L)0,B_1(L)~0]"
BSEXC = "[B*_s0,B*_s~0,B*_s20,B*_s2~0,B*_s00,B*_s0~0,B_s1(L)0,B_s1(L)~0]"
BCEXC = "[B_c*+,B_c*-,B_c2*+,B_c2*-,B_c0*+,B_c0*-,B_c1(L)+,B_c1(L)-]"

from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
tuple.Bc.addTupleTool(LoKiTool,"LHTT")
tuple.Bc.LHTT.Preambulo += [
    "PFUNA = LoKi.Particles.PFunA"
    , "from LoKiCore.functions import *"
    , "from PartProp.Nodes import CC"
    ]
tuple.Bc.LHTT.Variables = {
    "DOCA" : "PFUNA(AMINDOCA(''))"
    , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
    }

# TUPLETOOLTISTOS
from Configurables import TupleToolTISTOS
TisTos = tuple.Bc.addTupleTool("TupleToolTISTOS/TisTos")
TisTos.Verbose = True
TisTos.TriggerList = triggers

# TUPLE TOOL STRIPPING
TTS = tuple.addTupleTool("TupleToolStripping/TTS")
TTS.StrippingList = lines

# BACHMU TRACK ISOLATION
from Configurables import TupleToolTrackIsolation
BachMuTTTI = tuple.BachMu.addTupleTool("TupleToolTrackIsolation/BachMuTTTI")
BachMuTTTI.TotalCone = True
BachMuTTTI.TotalConeMinIPChi2PV = 9.0
BachMuTTTI.CutIPChi2PV = True
BachMuTTTI.MinIPChi2PV = 9.0
BachMuTTTI.FillAsymmetry = True
BachMuTTTI.FillDeltaAngles = True
BachMuTTTI.MinConeAngle = 0.75
BachMuTTTI.MaxConeAngle = 1.25
BachMuTTTI.StepSize = 0.25

# VERTEX ISOLATION
from Configurables import TupleToolVtxIsoln
BcTTVI = tuple.Bc.addTupleTool("TupleToolVtxIsoln/BcTTVI") # B ?
BcTTVI.CutIPChi2PV = True
BcTTVI.MinIPChi2PV = 9.0
JpsiTTVI = tuple.Jpsi.addTupleTool("TupleToolVtxIsoln/JpsiTTVI") # psi(2S) ?
JpsiTTVI.CutIPChi2PV = True
JpsiTTVI.MinIPChi2PV = 9.0

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 
