########################################################################
# Y -> Jpsi Mu, Jpsi -> e e (B_c, missing neutrinos)
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
DaVinci().EvtMax = 1000
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_EE_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu_EE.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]

### MONITORING SEQUENCE

# PRINT MC DECAY TREE
from Configurables import PrintMCTree, PrintMCDecayTreeTool
mctree = PrintMCTree("PrintTrueBc")
mctree.addTool(PrintMCDecayTreeTool, name = "PrintMC")
mctree.PrintMC.Information = "Name"
mctree.ParticleNames = [ "B_c+", "B_c-", "B+", "B-" ]
mctree.Depth = 2
#DaVinci().MoniSequence += [ mctree ]

# HLT REPORT
from Configurables import ReadHltReport
monihltrep = ReadHltReport(name="monihltrep")
DaVinci().MoniSequence += [ monihltrep ]

# MU MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
gammas = "{,gamma}{,gamma}{,gamma}"
mudecay = "[B_c+ -> (^J/psi(1S) => ^e+ ^e- " + gammas + ") ^mu+ ^nu_mu" + gammas + "]cc"
MCMuTuple = MCDecayTreeTuple("MCBc2JpsiMuTuple")
MCMuTuple.TupleName = "MCMuDecayTree"
MCMuTuple.Decay = mudecay
MCMuTuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> ?]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => e+ e- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^e+ e- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => e+ ^e- " + gammas + ") mu+ nu_mu " + gammas + "]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") ^mu+ nu_mu " + gammas + "]cc"
    , "NuMu" : "[B_c+ -> (J/psi(1S) => e+ e- "+ gammas + ") mu+ ^nu_mu " + gammas + "]cc"
    })
MCMuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# TRIGGER AND STRIPPING INFORMATION
triggers = [
    "L0MuonDecision"
    , "L0ElectronDecision"
    , "L0PhotonDecision"
    , "Hlt1SingleMuonNoIPDecision"
    , "Hlt1SingleMuonHighPTDecision"
    , "Hlt1SingleElectronNoIPDecision"
    , "Hlt1TrackMuonDecision"
    , "Hlt2Topo2BodyBBDTDecision"
    , "Hlt2Topo2BodySimpleDecision"
    , "Hlt3Topo2BodyBBDTDecision"
    , "Hlt3Topo2BodySimpleDecision"
    , "Hlt2TopoE2BodyBBDTDecision"
    , "Hlt2TopoE3BodyBBDTDecision"
    , "Hlt2TopoMu2BodyBBDTDecision"
    , "Hlt2TopoMu3BodyBBDTDecision"
    ]
lines = [
    ]

from Configurables import TupleToolTrigger, TupleToolStripping
MuTTT = MCMuTuple.addTupleTool("TupleToolTrigger/MuTTT")
MuTTT.VerboseL0 = True
MuTTT.VerboseHlt1 = True
MuTTT.VerboseHlt2 = True
MuTTT.TriggerList = triggers
#MuTTS = MCMuTuple.addTupleTool("TupleToolStripping/MuTTS")
#MuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCMuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCMuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCMuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

DaVinci().appendToMainSequence( [ MCMuTuple ] )

# TAU MC TRUTH TUPLE
#taudecay = "[B_c+ -> (^J/psi(1S) => ^e+ ^e-" + gammas + ") (^tau+ => ^mu+ ^nu_mu ^nu_tau~ " + gammas + ") ^nu_tau " + gammas + "]cc"
#MCTauTuple = MCDecayTreeTuple("MCBc2JpsiTauTuple")
#MCTauTuple.TupleName = "MCBc2JpsiTauTuple"
#MCTauTuple.Decay = taudecay
#MCTauTuple.addBranches({
#    "Bc" : "[B_c+]cc : [B_c+ -> ?]cc"
#    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => e+ e- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "MuP" : "[B_c+ -> (J/psi(1S) => ^e+ e- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "MuM" : "[B_c+ -> (J/psi(1S) => e+ ^e- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "Tau" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") (^tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "BachMu" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") (tau+ => ^mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "NuMu" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") (tau+ => mu+ ^nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "NuTauBar" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") (tau+ => mu+ nu_mu ^nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
#    , "NuTau" : "[B_c+ -> (J/psi(1S) => e+ e- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") ^nu_tau " + gammas + "]cc"
#    })
#MCTauTuple.ToolList = [
#    "MCTupleToolKinematic"
#    , "TupleToolEventInfo"
#    ]

# TRIGGER AND STRIPPING INFORMATION
#TauTTT = MCTauTuple.addTupleTool("TupleToolTrigger/TauTTT")
#TauTTT.TriggerList = triggers
#TauTTT.VerboseL0 = True
#TauTTT.VerboseHlt1 = True
#TauTTT.VerboseHlt2 = True
#TauTTS = MCTauTuple.addTupleTool("TupleToolStripping/TauTTS")
#TauTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
#MCTauTuple.MuP.addTupleTool("MCTupleToolReconstructed")
#MCTauTuple.MuM.addTupleTool("MCTupleToolReconstructed")
#MCTauTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

#DaVinci().appendToMainSequence( [ MCTauTuple ] )

# RECONSTRUCTED SEQUENCE
from Configurables import GaudiSequencer
recseq = GaudiSequencer("RecSeq")

# TRIGGER LINES / STRIPPING LINE FILTER
from PhysConf.Filters import LoKi_Filters

#Hlt1Filt = LoKi_Filters(
#    HLT_Code  = "HLT_PASS_RE( 'Hlt1DiMuon.*MassDecision' )"
#    )
#recseq.Members += [ Hlt1Filt.sequence('Hlt1FiltSeq') ]

#Hlt2Filt = LoKi_Filters(
#    HLT_Code   = "HLT_PASS( 'Hlt2DiMuonJPsiHighPTDecision' )",
#    )
#recseq.Members += [ Hlt2Filt.sequence('Hlt2FiltSeq') ]

#StripFilt = LoKi_Filters(
#    STRIP_Code = "HLT_PASS( 'StrippingTriMuonBc2ThreeMuDecision' )"
#    )
#recseq.Members += [ StripFilt.sequence('StripFiltSeq') ]

# DATA
MuonsLoc = 'Phys/StdAllLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2ee/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)

from Configurables import FilterDesktop

from Configurables import CombineParticles
_AlgBc2JpsiMu = CombineParticles('AlgBc2JpsiMu')
_AlgBc2JpsiMu.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
_AlgBc2JpsiMu.DaughtersCuts = {}
_AlgBc2JpsiMu.CombinationCut = "(AM < 6.278*GeV)"
_AlgBc2JpsiMu.CombinationCut += " & (ADOCACHI2CUT(30,''))"
_AlgBc2JpsiMu.MotherCut = "(M < 6.278*GeV)"
_AlgBc2JpsiMu.MotherCut += " & (VFASPF(VCHI2) < 25)"

TightBcSel = Selection("TightBcSel",
                       Algorithm = _AlgBc2JpsiMu,
                       RequiredSelections = [JpsiSel, MuonsSel])

BcSeq = SelectionSequence("BcSeq",
                          TopSelection = TightBcSel)

# ADD ALGORITHM
finalsel = BcSeq.sequence()
seqhltrep = ReadHltReport(name="seqhltrep")
finalsel.Members += [ seqhltrep ]
recseq.Members += [ finalsel ]

#########################
### DECAYTREETUPLE
#########################

# Create tuple, add all desired tools
from Configurables import TupleToolMCTruth, TupleToolMCBackgroundInfo, BackgroundCategory
from Configurables import TupleToolTISTOS

tuple = DecayTreeTuple("Bc2JpsiMu_Tuple")
tuple.Inputs = [ BcSeq.outputLocation() ]
tuple.Decay = "[B_c+ -> (^J/psi(1S) => ^e+ ^e-) ^mu+]cc"
tuple.ToolList = [
    "TupleToolGeometry"
    , "TupleToolKinematic"
    , "TupleToolAngles"
    , "TupleToolPid"
    , "TupleToolEventInfo"
    , "TupleToolTrackInfo"
    ]
truth = tuple.addTupleTool("TupleToolMCTruth")
truth.ToolList = [ "MCTupleToolKinematic"
                   , "MCTupleToolHierarchy"
                   ]
# TUPLETOOLTISTOS
TisTos = tuple.addTupleTool("TupleToolTISTOS/TisTos")
TisTos.Verbose = True
TisTos.TriggerList = triggers

# BRANCHES
tuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> (J/psi(1S) => e+ e-) mu+]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => e+ e-) mu+]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^e+ e-) mu+]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => e+ ^e-) mu+]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => e+ e-) ^mu+]cc"
    })

# TUPLETOOLMCBACKGROUNDINFO
TTMCBI = tuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/TTMCBI")
TTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
TTMCBI.BackgroundCategory.SemileptonicDecay=True
TTMCBI.BackgroundCategory.NumNeutrinos=3

# RECONSTRUCTED INFO
MuPTruth = tuple.MuP.addTupleTool("TupleToolMCTruth/MuPTruth")
MuPTruth.ToolList = [ "MCTupleToolReconstructed" ]
MuMTruth = tuple.MuM.addTupleTool("TupleToolMCTruth/MuMTruth")
MuMTruth.ToolList = [ "MCTupleToolReconstructed" ]
BachMuTruth = tuple.BachMu.addTupleTool("TupleToolMCTruth/BachMuTruth")
BachMuTruth.ToolList = [ "MCTupleToolReconstructed" ]

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 

