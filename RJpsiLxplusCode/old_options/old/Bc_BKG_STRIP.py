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

# HAVE TO REDO FILTER, UGHH

#StripFilt = LoKi_Filters(
#    STRIP_Code = "HLT_PASS( 'StrippingTriMuonBc2ThreeMuDecision' )"
#    )
#recseq.Members += [ StripFilt.sequence('StripFiltSeq') ]

from Configurables import LoKi__VoidFilter
vf = LoKi__VoidFilter("SelFilterPhys_StdLooseMuons_Particles")
vf.Code = "CONTAINS('Phys/StdLooseMuons/Particles')>0"
recseq.Members += [ vf ]

from Configurables import FilterDesktop
fd = FilterDesktop("TriMuonGoodMuonsForTriMuons")
fd.Code = "( PT > 300 * MeV ) & ( TRCHI2DOF < 2 ) & ( BPVIPCHI2 () > 9 )"
fd.Inputs = [ 'Phys/StdLooseMuons' ]
fd.Output = 'Phys/TriMuonGoodMuonsForTriMuons/Particles'
recseq.Members += [ fd ]

vf2 = LoKi__VoidFilter("TriMuonThreeGoodMuonsEventSelection")
vf2.Code = "CONTAINS('Phys/TriMuonGoodMuonsForTriMuons/Particles') > 2.5"
recseq.Members += [vf2 ]

fd2 = FilterDesktop("TriMuonGoodMuonsForBcMuons")
fd2.Code = "( BPVIPCHI2 () > 9 ) & ( TRCHI2DOF < 2 )"
fd2.Inputs = [ 'Phys/TriMuonGoodMuonsForTriMuons' ]
fd2.Output = "Phys/TriMuonGoodMuonsForBcMuons/Particles"
recseq.Members += [ fd2 ]

vf3 = LoKi__VoidFilter("TriMuonThreeGoodMuonsForBcEventSelection")
vf3.Code = "CONTAINS('Phys/TriMuonGoodMuonsForBcMuons/Particles') > 2.5"
recseq.Members += [ vf3 ]

from Configurables import CombineParticles
cp = CombineParticles("TriMuonBc2ThreeMu")
cp.Preambulo = [
    'chi2vx = VFASPF(VCHI2) '
    , 'from GaudiKernel.PhysicalConstants import c_light'
    , 'ctau = BPVLTIME ( ) * c_light '
    , "ctauBc = PDGM('B_c+') / M * BPVLTIME ( ) * c_light "
    , "mPsi1S = PDGM('J/psi(1S)' ) "
    , "mPsi2S = PDGM( 'psi(2S)' ) "
    , 'l1S = mPsi1S - 200 * MeV '
    , 'h1S = mPsi1S + 200 * MeV '
    , 'l2S = mPsi2S - 200 * MeV '
    , 'h2S = mPsi2S + 200 * MeV '
    , 'dm1 = in_range ( l1S , AM13 , h1S ) | in_range ( l2S , AM13 , h2S ) '
    , 'dm2 = in_range ( l1S , AM23 , h1S ) | in_range ( l2S , AM23 , h2S ) ' ]
cp.Inputs = [ 'Phys/TriMuonGoodMuonsForBcMuons' ]
cp.DaughtersCuts = { '' : 'ALL' , 'mu+' : 'ALL' , 'mu-' : 'ALL' }
cp.CombinationCut = "( l1S < AM ) & AHASCHILD( PT > 1.0 * GeV ) & ( dm1 | dm2 )"
cp.MotherCut = "( chi2vx < 15 ) & ( ctauBc > 20 * micrometer )"
cp.DecayDescriptor = "[B_c+ -> mu+ mu+ mu- ]cc"
cp.DecayDescriptors = [ ' [B_c+ -> mu+ mu+ mu- ]cc' ]
cp.Output = "Phys/TriMuonBc2ThreeMu/Particles"
recseq.Members += [ cp ]

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
from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *
from Configurables import TupleToolMCTruth, TupleToolMCBackgroundInfo, BackgroundCategory, TupleToolTISTOS

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
triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    ]
TisTos.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
TTS = tuple.addTupleTool("TupleToolStripping/TTS")
lines = [
    "StrippingBc2JpsiMuLineDecision"
    , "StrippingBc2JpsiTauNuForB2XTauNuDecision"
    , "StrippingTriMuonBc2ThreeMuDecision"
    ]
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

