#######################################################################
# Background mode for Bc analysis
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *

# OPTIONS
simulation = True; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc_BKG_histos.root"
DaVinci().TupleFile = "Bc_BKG.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]

# TRIGGER AND STRIPPING LINE INFO
triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    ]
lines = [
    "StrippingTriMuonBc2ThreeMuDecision"
    , "StrippingBc2JpsiMuLineDecision"
    , "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision"
    , "StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision"
    ]

# RECONSTRUCTED SEQUENCE
from Configurables import GaudiSequencer
recseq = GaudiSequencer("RecSeq")

# PRESCALE EMULATOR
from Configurables import TCKPrescaleEmulator
TCKemulator = TCKPrescaleEmulator("TCKeumlator")
TCKemulator.TCKtoEmulate = 0x00760037 # see mailing list "Best TCK for 2011 data"
recseq.Members += [ TCKemulator ]

# TRIGGER LINES / STRIPPING LINE FILTER
from PhysConf.Filters import LoKi_Filters
StripFilt = LoKi_Filters(
    STRIP_Code = "HLT_PASS( 'StrippingTriMuonBc2ThreeMuDecision' )"
    )
#recseq.Members += [ StripFilt.sequence('StripFiltSeq') ]

# DATA
MuonsLoc = 'Phys/StdAllLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
#BcLoc = '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)
#BcSel = AutomaticData(Location = BcLoc)

from Configurables import FilterDesktop
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

#MyMuonAlg = FilterDesktop("MyMuonAlg")
#MyMuonAlg.Code = "TRCHI2DOF < 3"
#MyMuonSel = Selection("MyMuonSel", Algorithm = MyMuonAlg, RequiredSelections = [MuonsSel])

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

from Configurables import ChargedProtoANNPIDConf
nnpidseq = GaudiSequencer("ANNGPIDSeq")
annconf = ChargedProtoANNPIDConf()
annconf.DataType = "2011"
annconf.NetworkVersions["2011"] = "MC12TuneV2"
annconf.RecoSequencer = nnpidseq
DaVinci().appendToMainSequence( [ nnpidseq ] )


#########################
### DECAYTREETUPLE
#########################

# Create tuple, add all desired tools
from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *
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
truth = tuple.addTupleTool("TupleToolMCTruth")
truth.ToolList = [
    "MCTupleToolKinematic"
    , "MCTupleToolHierarchy"
    ]

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
    , "from LoKiPhysMC.decorators import *"
    , "from PartProp.Nodes import CC"
    ]
tuple.Bc.LHTT.Variables = {
    "DOCAMIN" : "PFUNA(AMINDOCA(''))"
    , "DOCAMAX" : "PFUNA(AMAXDOCA(''))"
    , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"

    # Bc -> J/psi X
    , "Bc2JpsiMuNu" : "switch(mcMatch('[B_c+ => J/psi(1S) mu+ nu_mu]CC'),1,0)"
    , "Bc2JpsiTauNu" : "switch(mcMatch('[B_c+ => J/psi(1S) tau+ nu_tau]CC'),1,0)"
    , "Bc2Psi2SMuNu" : "switch(mcMatch('[B_c+ => psi(2S) mu+ nu_mu]CC'),1,0)"
    , "Bc2Psi2STauNu" : "switch(mcMatch('[B_c+ => psi(2S) tau+ nu_tau]CC'),1,0)"
    , "B2JpsiK" : "switch(mcMatch('[B+ => J/psi(1S) K+]CC'),1,0)"
    , "B2JpsiPi" : "switch(mcMatch('[B+ => J/psi(1S) pi+]CC'),1,0)"
    , "Psi2S2JpsiPiPi" : "switch(mcMatch('psi(2S) => J/psi(1S) pi+ pi-'),1,0)"
    
    # B type
    , "IsABc" : "switch(mcMatch('[B_c+]cc'),1,0)"
    , "IsABu" : "switch(mcMatch('[B+]cc'),1,0)"
    , "IsABd" : "switch(mcMatch('[B0]cc'),1,0)"
    , "IsABs" : "switch(mcMatch('[B_s0]cc'),1,0)"
    , "IsABu_star" : "switch(mcMatch('" + BUEXC + "'),1,0)"
    , "IsABd_star" : "switch(mcMatch('" + BDEXC + "'),1,0)"
    , "IsABs_star" : "switch(mcMatch('" + BSEXC + "'),1,0)"
    , "IsABc_star" : "switch(mcMatch('" + BCEXC + "'),1,0)"

    # CHARMONIUM type
    , "JpsiX" : "switch(mcMatch('Beauty -> J/psi(1S) ...'),1,0)"
    , "Psi2SX" : "switch(mcMatch('Beauty -> psi(2S) ...'),1,0)"
    , "ChiC0X" : "switch(mcMatch('Beauty -> chi_c0(1P) ...'),1,0)"
    , "ChiC1X" : "switch(mcMatch('Beauty -> chi_c1(1P) ...'),1,0)"
    , "ChiC2X" : "switch(mcMatch('Beauty -> chi_c2(1P) ...'),1,0)"
    
    # B -> CHARMONIUM DECAY TYPES
    , "Bm2CCPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + PI + "'),1,0)"
    , "Bm2CCPiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + PI + PI + "'),1,0)"
    , "Bm2CCEta" : "switch(mcMatch('Beauty => " + CHARMONIUM + "eta'),1,0)"
    , "Bm2CCRho" : "switch(mcMatch('Beauty => " + CHARMONIUM + RHO + "'),1,0)"
    , "Bm2CCEtaP" : "switch(mcMatch('Beauty => " + CHARMONIUM + "eta_prime'),1,0)"
    , "Bm2CCF0" : "switch(mcMatch('Beauty => " + CHARMONIUM + F0 + "'),1,0)"
    , "Bm2CCPhi" : "switch(mcMatch('Beauty => " + CHARMONIUM + "phi(1020)'),1,0)"
    , "Bm2CCOmega" : "switch(mcMatch('Beauty => " + CHARMONIUM + "omega(782)'),1,0)"
    , "Bm2CCK" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "'),1,0)"
    , "Bm2CCKPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + PI + "'),1,0)"
    , "Bm2CCKPiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + PI + PI + "'),1,0)"
    , "Bm2CCKEta" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "eta'),1,0)"
    , "Bm2CCKEtaP" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "eta_prime'),1,0)"
    , "Bm2CCKPhi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "phi(1020)'),1,0)"
    , "Bm2CCKOmega" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "omega(782)'),1,0)"
    , "Bm2CCKRho" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + RHO + "'),1,0)"
    , "Bm2CCK892" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + "'),1,0)"
    , "Bm2CCK892Pi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + PI + "'),1,0)"
    , "Bm2CCK892PiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + PI + PI + "'),1,0)"
    , "Bm2CCK1270" : "switch(mcMatch('Beauty => " + CHARMONIUM + K1270 + "'),1,0)"
    , "Bm2CCK1400" : "switch(mcMatch('Beauty => " + CHARMONIUM + K1400 + "'),1,0)"
    
    }

tuple.BachMu.addTupleTool(LoKiTool,"BmLHTT")
tuple.BachMu.BmLHTT.Preambulo += [
    "from LoKiCore.functions import *"
    , "from LoKiPhysMC.decorators import *"
    , "from PartProp.Nodes import CC"
    ]
tuple.BachMu.BmLHTT.Variables = {
    "IsAMu" : "switch(mcMatch('[mu+]cc'),1,0)"
    , "IsAPi" : "switch(mcMatch('[pi+]cc'),1,0)"
    , "IsAK" : "switch(mcMatch('[K+]cc'),1,0)"
    , "IsAPi2Mu" : "switch(mcMatch('[pi+ -> mu+ nu_mu ... ]CC'),1,0)" # extra gamma
    , "IsAK2Mu" : "switch(mcMatch('[K+ -> mu+ nu_mu ... ]CC'),1,0)" # extra pi0 or pi pi
    , "IsAMuFromPi" : "switch(mcMatch('[pi+ -> ^mu+ nu_mu ... ]CC'),1,0)" # extra gamma
    , "IsAMuFromK" : "switch(mcMatch('[K+ -> ^mu+ nu_mu ... ]CC'),1,0)" # extra pi0 or pi pi
    }

# TUPLETOOLTISTOS
from Configurables import TupleToolTISTOS
TisTos = tuple.Bc.addTupleTool("TupleToolTISTOS/TisTos")
TisTos.Verbose = True
TisTos.TriggerList = triggers

# TUPLE TOOL STRIPPING
TTS = tuple.addTupleTool("TupleToolStripping/TTS")
TTS.StrippingList = lines

# TUPLETOOLMCBACKGROUNDINFO
from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
BcTTMCBI = tuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/BcTTMCBI")
BcTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
BcTTMCBI.BackgroundCategory.SemileptonicDecay = True
BcTTMCBI.BackgroundCategory.NumNeutrinos = 3
JpsiTTMCBI = tuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")

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
