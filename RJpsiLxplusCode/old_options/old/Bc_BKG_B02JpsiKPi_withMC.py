########################################################################
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
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]

# MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
#gammas = "{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}"
gammas = "{,gamma}{,gamma}"
mudecay = "[B0 -> (^J/psi(1S) => ^mu+ ^mu- " + gammas + ") ^K+ ^pi- " + gammas + "]cc"
MCTuple = MCDecayTreeTuple("MCBc2JpsiMuTuple")
MCTuple.TupleName = "MCDecayTree"
MCTuple.Decay = mudecay
MCTuple.addBranches({
    "B0" : "[B0]cc : [B0 -> ?]cc"
    , "Jpsi" : "[B0 -> (^J/psi(1S) => mu+ mu- " + gammas + ") K+ pi- " + gammas + "]cc"
    , "MuP" : "[B0 -> (J/psi(1S) => ^mu+ mu- " + gammas + ") K+ pi- " + gammas + "]cc"
    , "MuM" : "[B0 -> (J/psi(1S) => mu+ ^mu- " + gammas + ") K+ pi- " + gammas + "]cc"
    , "K" : "[B0 -> (J/psi(1S) => mu+ mu- " + gammas + ") ^K+ pi- " + gammas + "]cc"
    , "Pi" : "[B0 -> (J/psi(1S) => mu+ mu- "+ gammas + ") K+ ^pi- " + gammas + "]cc"
    })
MCTuple.ToolList = [
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
MCTTT = MCTuple.addTupleTool("TupleToolTrigger/MCTTT")
MCTTT.VerboseL0 = True
MCTTT.VerboseHlt1 = True
MCTTT.VerboseHlt2 = True
MCTTT.TriggerList = triggers
MCTTS = MCTuple.addTupleTool("TupleToolStripping/MCTTS")
MCTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCTuple.K.addTupleTool("MCTupleToolReconstructed")
MCTuple.Pi.addTupleTool("MCTupleToolReconstructed")

# If I ran this, I could get reco / stripping / etc info
# However, I probably don't need this for background
# MC produced with DaughtersInLHCb
# If I really need acceptance, I can generate sample MC
# However, its a big mode and there have been measurements
# Knowing how many become background / # in acceptance is enough
# Doesn't really matter where they get rejected, just so long as they do!
# If it becomes a big background, I can rerun with MC truth and investigate more
# DaVinci().appendToMainSequence( [ MCTuple ] )

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

#Hlt1Filt = LoKi_Filters(
#    HLT_Code  = "HLT_PASS_RE( 'Hlt1DiMuon.*MassDecision' )"
#    )
#recseq.Members += [ Hlt1Filt.sequence('Hlt1FiltSeq') ]

#Hlt2Filt = LoKi_Filters(
#    HLT_Code   = "HLT_PASS( 'Hlt2DiMuonJPsiHighPTDecision' )"
#    )
#recseq.Members += [ Hlt2Filt.sequence('Hlt2FiltSeq') ]

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
MuonsLoc = 'Phys/StdAllLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
#BcLoc = '/Event/Dimuon/Phys/TriMuonBc2ThreeMu/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)
#BcSel = AutomaticData(Location = BcLoc)

from Configurables import FilterDesktop
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(ADMASS('J/psi(1S)') < 100*MeV) & (VFASPF(VCHI2) < 25)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID, TRCHI2DOF) < 4) & (MINTREE('mu+'==ABSID, PIDmu-PIDpi) > 0)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

#from Configurables import CombineParticles
#MyJpsiAlg = CombineParticles('MyJpsiAlg')
#MyJpsiAlg.DecayDescriptor = 'J/psi(1S) -> mu+ mu-'
#MyJpsiAlg.DaughtersCuts = {}
#MyJpsiAlg.CombinationCut = "(ADAMASS('J/psi(1S)') < 200*MeV) & (ADOCACHI2CUT(30,''))"
#MyJpsiAlg.MotherCut = "(ADMASS('J/psi(1S)') < 100*MeV) & (VFASPF(VCHI2) < 25)"
#MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [BcSel])

from Configurables import CombineParticles
MyBcAlg = CombineParticles('MyBcAlg')
MyBcAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
MyBcAlg.DaughtersCuts = {}
#MyBcAlg.DaughtersCuts = { "mu+" : "(TRCHI2DOF < 4) & (PIDmu-PIDpi > 0)"}
MyBcAlg.CombinationCut = "(AM < 6.378*GeV) & (ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcAlg.MotherCut = "(M < 6.278*GeV) & (VFASPF(VCHI2) < 25)"

MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyJpsiSel, MuonsSel])

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

# APPEND TO SEQUENCE
recseq.Members += [ tuple ]
DaVinci().appendToMainSequence( [ recseq ] ) 

