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
simulation = True; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_TMer_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu_TMer.root"
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
lines = ["StrippingTriMuonBc2ThreeMuDecision"
         , "StrippingBc2JpsiMuLineDecision"
         , "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision"
         , "StrippingFullDSTDiMuonJpsi2MuMuTOSLineDecision"
         ]

# MU MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
gammas = "{,gamma}{,gamma}"
mudecay = "[B_c+ -> (^J/psi(1S) => ^mu+ ^mu- " + gammas + ") ^mu+ ^nu_mu" + gammas + "]cc"
MCMuTuple = MCDecayTreeTuple("MCBc2JpsiMuTuple")
MCMuTuple.TupleName = "MCMuDecayTree"
MCMuTuple.Decay = mudecay
MCMuTuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> ?]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => mu+ mu- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^mu+ mu- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => mu+ ^mu- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") ^mu+ nu_mu " + gammas + "]cc"
    , "NuMu" : "[B_c+ -> (J/psi(1S) => mu+ mu- "+ gammas + ") mu+ ^nu_mu " + gammas + "]cc"
    })
MCMuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# TUPLE TOOL TRIGGER
from Configurables import TupleToolTrigger
MuTTT = MCMuTuple.addTupleTool("TupleToolTrigger/MuTTT")
MuTTT.VerboseL0 = True
MuTTT.VerboseHlt1 = True
MuTTT.VerboseHlt2 = True
MuTTT.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
MuTTS = MCMuTuple.addTupleTool("TupleToolStripping/MuTTS")
MuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCMuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCMuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCMuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

DaVinci().appendToMainSequence( [ MCMuTuple ] )

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
MyTMJpsiAlg = FilterDesktop("MyTMJpsiAlg")
MyTMJpsiAlg.Preambulo = [ "from LoKiPhysMC.decorators import *" , "from PartProp.Nodes import CC" ] 
MyTMJpsiAlg.Code = "mcMatch('[B_c+ => ^J/psi(1S) mu+ nu_mu]CC')"
MyTMJpsiSel = Selection("MyTMJpsiSel", Algorithm = MyTMJpsiAlg, RequiredSelections = [JpsiSel])

MyTMMuonAlg = FilterDesktop("MyTMMuonAlg")
MyTMMuonAlg.Preambulo = [ "from LoKiPhysMC.decorators import *" , "from PartProp.Nodes import CC" ] 
MyTMMuonAlg.Code = "mcMatch('[B_c+ => J/psi(1S) ^mu+ nu_mu]CC')"
MyTMMuonSel = Selection("MyTMMuonSel", Algorithm = MyTMMuonAlg, RequiredSelections = [MuonsSel])

from Configurables import CombineParticles
MyTMBcAlg = CombineParticles('MyTMBcAlg')
MyTMBcAlg.Preambulo = [ "from LoKiPhysMC.decorators import *" , "from PartProp.Nodes import CC" ] 
MyTMBcAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
MyTMBcAlg.MotherCut = "mcMatch('[B_c+ => J/psi(1S) mu+ nu_mu]CC')"
MyTMBcSel = Selection("MyTMBcSel", Algorithm = MyTMBcAlg, RequiredSelections = [MyTMJpsiSel, MyTMMuonSel])
#MyTMBcSel = Selection("MyTMBcSel", Algorithm = MyTMBcAlg, RequiredSelections = [JpsiSel, MuonsSel])

MyTMBcSeq = SelectionSequence("MyTMBcSeq", TopSelection = MyTMBcSel)

# ADD ALGORITHM
finalsel = MyTMBcSeq.sequence()
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
tuple = DecayTreeTuple("Bc2JpsiMu_Tuple")
tuple.Inputs = [ MyTMBcSeq.outputLocation() ]
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
JpsiTTVI = tuple.Jpsi.addTupleTool("TupleToolVtxIsoln/JpsiTTVI") # psi(2S) ?
JpsiTTVI.CutIPChi2PV = True
JpsiTTVI.MinIPChi2PV = 9.0

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 
