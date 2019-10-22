#######################################################################
# Y -> Jpsi Mu (B_c, missing neutrinos)
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *

#OPTIONS
simulation = True; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = 1000
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]

# MU MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
#gammas = "{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}"
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

# TRIGGER AND STRIPPING INFORMATION
triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    ]
lines = [
    "StrippingBc2JpsiMuLineDecision"
    , "StrippingBc2JpsiTauNuForB2XTauNuDecision"
    , "StrippingTriMuonBc2ThreeMuDecision"
    ]

from Configurables import TupleToolTrigger, TupleToolStripping
MuTTT = MCMuTuple.addTupleTool("TupleToolTrigger/MuTTT")
MuTTT.VerboseL0 = True
MuTTT.VerboseHlt1 = True
MuTTT.VerboseHlt2 = True
MuTTT.TriggerList = triggers
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
recseq.Members += [ StripFilt.sequence('StripFiltSeq') ]

# PRINT MC DECAY TREE
from Configurables import PrintMCTree, PrintMCDecayTreeTool
mctree = PrintMCTree("PrintTrueBc")
mctree.addTool(PrintMCDecayTreeTool, name = "PrintMC")
mctree.PrintMC.Information = "Name"
mctree.ParticleNames = [ "B_c+", "B_c-" ]
mctree.Depth = 2
#recseq.Members += [ mctree ]

# DATA
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand, Selection, SelectionSequence
#from Configurables import CombineParticles
from GaudiConfUtils.ConfigurableGenerators import FilterInTrees, CombineParticles

# FILTER STRIPPING LINE DOWN TO MUONS
#BcLoc = '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles'
#MyFlattenAlg = FilterDecays("MyFlattenAlg")
#MyFlattenAlg.Code = "[B_c+ -> ^mu+ ^mu+ ^mu-]CC"
#MyFlattenAlg.DecayDescriptor = "[B_c+ -> ^mu+ ^mu+ ^mu-]CC"
#MyFlattenAlg.Inputs = [ '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles' ]
#recseq.Members += [ MyFlattenAlg ]
#GoodMuonsSel = AutomaticData(Location = "/Event/Phys/MyFlattenAlg/Particles")

BcLoc = '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles'
BcSel = AutomaticData(BcLoc)
#MyFlattenAlg = FilterInTrees("MyFlattenAlg")
#MyFlattenAlg.Code = "('mu+'==ABSID)"
#MyFlattenAlg.Inputs = [ BcLoc ]

GoodMuonsAlg = FilterInTrees( Code = "('mu+'==ABSID)")
GoodMuonsSel = Selection( "GoodMuonsSel", Algorithm = GoodMuonsAlg, RequiredSelections = [ BcSel ] )

MyJpsiAlg = CombineParticles(
    DecayDescriptor = "J/psi(1S) -> mu+ mu-"
    , DaughtersCuts = {}
    , CombinationCut = "(ADAMASS('J/psi(1S)') < 100.*MeV) & (ADOCACHI2CUT(30,''))"
    , MotherCut = "(VFASPF(VCHI2) < 25.)"
    )
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [GoodMuonsSel])

MyBcAlg = CombineParticles(
    DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
    , DaughtersCuts = {}
    #, DaughtersCuts = { "mu+" : "(PIDmu > 0)"}
    , CombinationCut = "(AM < 6.378*GeV) & (ADOCACHI2CUT(30,''))" # a little wiggle room in mass
    , MotherCut = "(M < 6.278*GeV) & (VFASPF(VCHI2) < 25)"
    )
MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyJpsiSel, GoodMuonsSel])

MyBcSeq = SelectionSequence("MyBcSeq", TopSelection = MyBcSel)

# ADD ALGORITHM
finalsel = MyBcSeq.sequence()
from Configurables import ReadHltReport
finalsel.Members += [ ReadHltReport() ]
recseq.Members += [ finalsel ]

#########################
### DECAYTREETUPLE
#########################

# Create tuple, add all desired tools
from Configurables import TupleToolMCTruth, TupleToolMCBackgroundInfo, BackgroundCategory
from Configurables import TupleToolTISTOS

tuple = DecayTreeTuple("Bc2JpsiMu_Tuple")
tuple.Inputs = [ MyBcSeq.outputLocation() ]
tuple.Decay = "[B_c+ -> (^J/psi(1S) => ^mu+ ^mu-) ^mu+]cc"
tuple.ToolList = [
    "TupleToolGeometry"
    , "TupleToolKinematic"
    , "TupleToolAngles"
    , "TupleToolPid"
    , "TupleToolTrackIsolation"
    , "TupleToolVtxIsoln"
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

# TUPLE TOOL STRIPPING
TTS = tuple.addTupleTool("TupleToolStripping/TTS")
TTS.StrippingList = lines

# BRANCHES
tuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> (J/psi(1S) => mu+ mu-) mu+]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => mu+ mu-) mu+]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^mu+ mu-) mu+]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => mu+ ^mu-) mu+]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => mu+ mu-) ^mu+]cc"
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

# BACHMU TRACK ISOLATION
# or do I add it for head?
#tuple.BachMu.addTupleTool("TupleToolTrackIsolation")

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 

