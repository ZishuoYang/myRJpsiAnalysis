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
lines = ["StrippingTriMuonBc2ThreeMuDecision"]

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
recseq.Members += [ StripFilt.sequence('StripFiltSeq') ]

# DATA
MuonsLoc = 'Phys/StdAllLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
PionsLoc = 'Phys/StdLoosePions/Particles'
#BcLoc = '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)
PionsSel = AutomaticData(Location = PionsLoc)
#BcSel = AutomaticData(Location = BcLoc)

from Configurables import FilterDesktop
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(ADMASS('J/psi(1S)') < 100*MeV) & (VFASPF(VCHI2) < 25)"
MyJpsiAlg.Code += " & (MINTREE('mu+'==ABSID, PT) > 300*MeV) & (MAXTREE('mu+'==ABSID, TRCHI2DOF) < 4) & (MINTREE('mu+'==ABSID, BPVIPCHI2()) > 9)"
#MyJpsiAlg.Code += " & (MINTREE('mu+'==ABSID, PIDmu-PIDpi) > 0)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

from Configurables import CombineParticles
MyPsi2SAlg = CombineParticles('MyPsi2SAlg')
MyPsi2SAlg.DecayDescriptor = '[psi(2S) -> J/psi(1S) pi+ pi-]'
MyPsi2SAlg.DaughtersCuts = {}
MyPsi2SAlg.CombinationCut = "(ADMASS('psi(2S)') < 300*MeV) & (ADOCACHI2CUT(30,''))"
MyPsi2SAlg.MotherCut = "(DMASS('psi(2S)') < 250*MeV) & (VFASPF(VCHI2) < 25)"

MyPsi2SSel = Selection("MyPsi2SSel",Algorithm = MyPsi2SAlg, RequiredSelections = [MyJpsiSel, PionsSel])

MyBcAlg = CombineParticles('MyBcAlg')
MyBcAlg.DecayDescriptor = '[B_c+ -> psi(2S) mu+]cc'
MyBcAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (TRCHI2DOF < 2) & (BPVIPCHI2() > 9)"}
MyBcAlg.CombinationCut = "(AM < 6.378*GeV) & (ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcAlg.MotherCut = "(M < 6.278*GeV) & (VFASPF(VCHI2) < 25)"

MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyPsi2SSel, MuonsSel])

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
tuple.Decay = "[B_c+ -> (^psi(2S) => (^J/psi(1S) => ^mu+ ^mu-) ^pi+ ^pi-) ^mu+]cc"
tuple.ToolList = [
    "TupleToolGeometry"
    , "TupleToolKinematic"
    #, "TupleToolAngles" # this hasn't turned out to be helpful for this analysis
    , "TupleToolPid"
    #, "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
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
    "Bc" : "[B_c+]cc : [B_c+ -> (psi(1S) => (J/psi(1S) => mu+ mu-) pi+ pi-) mu+]cc"
    , "Psi2S" : "[B_c+ -> (^psi(1S) => (J/psi(1S) => mu+ mu-) pi+ pi-) mu+]cc"
    , "Jpsi" : "[B_c+ -> (psi(1S) => (^J/psi(1S) => mu+ mu-) pi+ pi-) mu+]cc"
    , "PiP" : "[B_c+ -> (psi(1S) => (J/psi(1S) => mu+ mu-) ^pi+ pi-) mu+]cc"
    , "PiM" : "[B_c+ -> (psi(1S) => (J/psi(1S) => mu+ mu-) pi+ ^pi-) mu+]cc"
    , "MuP" : "[B_c+ -> (psi(1S) => (J/psi(1S) => ^mu+ mu-) pi+ pi-) mu+]cc"
    , "MuM" : "[B_c+ -> (psi(1S) => (J/psi(1S) => mu+ ^mu-) pi+ pi-) mu+]cc"
    , "BachMu" : "[B_c+ -> (psi(1S) => (J/psi(1S) => mu+ mu-) pi+ pi-) ^mu+]cc"
    })

# psi(2S) and Mu DOCA
from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
tuple.Bc.addTupleTool(LoKiTool,"LHTT")
tuple.Bc.LHTT.Preambulo += [ "PFUNA = LoKi.Particles.PFunA" ]
tuple.Bc.LHTT.Variables = {
    "DOCA" : "PFUNA(AMINDOCA(''))"
    , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
    }

# TUPLETOOLTISTOS
from Configurables import TupleToolTISTOS
TisTos = tuple.Bc.addTupleTool("TupleToolTISTOS/TisTos")
TisTos.Verbose = True
TisTos.TriggerList = triggers

# TUPLETOOLMCBACKGROUNDINFO
from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
BcTTMCBI = tuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/BcTTMCBI")
BcTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
BcTTMCBI.BackgroundCategory.SemileptonicDecay = True
BcTTMCBI.BackgroundCategory.NumNeutrinos = 3
Psi2STTMCBI = tuple.Psi2S.addTupleTool("TupleToolMCBackgroundInfo/Psi2STTMCBI")
JpsiTTMCBI = tuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")

# RECONSTRUCTED INFO
# HELPFUL FOR MC TOOL; LESS FOR THIS
#from Configurables import TupleToolMCTruth
#MuPTruth = tuple.MuP.addTupleTool("TupleToolMCTruth/MuPTruth")
#MuPTruth.ToolList = [ "MCTupleToolReconstructed" ]
#MuMTruth = tuple.MuM.addTupleTool("TupleToolMCTruth/MuMTruth")
#MuMTruth.ToolList = [ "MCTupleToolReconstructed" ]
#BachMuTruth = tuple.BachMu.addTupleTool("TupleToolMCTruth/BachMuTruth")
#BachMuTruth.ToolList = [ "MCTupleToolReconstructed" ]

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
Psi2STTVI = tuple.Psi2S.addTupleTool("TupleToolVtxIsoln/Psi2STTVI")
Psi2STTVI.CutIPChi2PV = True
Psi2STTVI.MinIPChi2PV = 9.0

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 
