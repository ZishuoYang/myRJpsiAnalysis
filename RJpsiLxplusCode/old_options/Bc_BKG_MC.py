######################################################################
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

DaVinci().DataType = "2012"
from Configurables import CondDB
CondDB().UseLatestTags = ["2012"]

# FILTER

from PhysConf.Filters import LoKi_Filters
Filt = LoKi_Filters(
    MC_Preambulo = [
    "from LoKiCore.functions import has"
    , "from GaudiKernel.SystemOfUnits import *"
    , "GoodJpsiFromB = MCDECTREE( 'Beauty --> ^(J/psi(1S) => mu+ mu-) ...' ) & (MCPT > 1.8 * GeV)"
    , "GoodMuPFromJpsi = MCDECTREE( 'Beauty --> (J/psi(1S) => ^mu+ mu-) ...' ) & (MCPT > 500 * MeV) & (MCP > 2.8 * GeV) & (MCPZ > 0) & (abs(MCPX/MCPZ) > 0.015) & (abs(MCPX/MCPZ) < 0.325) & (abs(MCPY/MCPZ) > 0.010) & (abs(MCPY/MCPZ) < 0.275)"
    , "GoodMuMFromJpsi = MCDECTREE( 'Beauty --> (J/psi(1S) => mu+ ^mu-) ...' ) & (MCPT > 500 * MeV) & (MCP > 2.8 * GeV) & (MCPZ > 0) & (abs(MCPX/MCPZ) > 0.015) & (abs(MCPX/MCPZ) < 0.325) & (abs(MCPY/MCPZ) > 0.010) & (abs(MCPY/MCPZ) < 0.275)"
    , "GoodMuFromB = MCDECTREE( '[Beauty -> Charm ^mu+ Nu ...]CC' ) & (MCPT > 280 * MeV) & (MCP > 2.8 * GeV) & (MCPZ > 0) & (abs(MCPX/MCPZ) > 0.015) & (abs(MCPX/MCPZ) < 0.325) & (abs(MCPY/MCPZ) > 0.010) & (abs(MCPY/MCPZ) < 0.275)"
    ]
    , MC_Code = "has(GoodJpsiFromB) & has(GoodMuPFromJpsi) & has(GoodMuMFromJpsi) & has(GoodMuFromB)"
    )
DaVinci().EventPreFilters = Filt.filters("Filters")


# B -> JPSI X MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
gammas = "{,gamma}{,gamma}"
decay = "[B+ --> ^(J/psi(1S) => ^mu+ ^mu-) ...]CC"
JpsiTuple = MCDecayTreeTuple("JpsiTuple")
JpsiTuple.TupleName = "JpsiDecayTree"
JpsiTuple.Decay = decay
JpsiTuple.ToolList = []
from Configurables import LoKi__Hybrid__MCTupleTool
LTT = JpsiTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/LTT")
LTT.Preambulo += ["from LoKiCore.functions import *"]
LTT.Variables = {
    "MCE" : "MCE"
    , "MCETA" : "MCETA"
    , "MCP" : "MCP"
    , "MCPX" : "MCPX"
    , "MCPY" : "MCPY"
    , "MCPZ" : "MCPZ"
    , "MCPT" : "MCPT"
    , "MCTHETA" : "MCTHETA"
    , "MCPHI" : "MCPHI"
    }

DaVinci().appendToMainSequence( [ JpsiTuple ] )

# COMBINE PARTICLES
MuonsLoc = 'Phys/StdAllLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'

from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)

from Configurables import FilterDesktop
MyTMJpsiAlg = FilterDesktop("MyTMJpsiAlg")
MyTMJpsiAlg.Preambulo = [ "from LoKiPhysMC.decorators import *" , "from PartProp.Nodes import CC" ] 
MyTMJpsiAlg.Code = "mcMatch( 'Beauty --> ^(J/psi(1S) => mu+ mu-) ...' )"
MyTMJpsiSel = Selection("MyTMJpsiSel", Algorithm = MyTMJpsiAlg, RequiredSelections = [JpsiSel])

MyTMMuonAlg = FilterDesktop("MyTMMuonAlg")
MyTMMuonAlg.Preambulo = [ "from LoKiPhysMC.decorators import *" , "from PartProp.Nodes import CC" ] 
MyTMMuonAlg.Code = "mcMatch( '[Beauty -> Charm ^mu+ Nu ...]CC' )"
MyTMMuonSel = Selection("MyTMMuonSel", Algorithm = MyTMMuonAlg, RequiredSelections = [MuonsSel])

from Configurables import CombineParticles
MyTMBcAlg = CombineParticles('MyTMBcAlg')
MyTMBcAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
MyTMBcAlg.MotherCut = "(ALL)"
MyTMBcSel = Selection("MyTMBcSel", Algorithm = MyTMBcAlg, RequiredSelections = [MyTMJpsiSel, MyTMMuonSel])
MyTMBcSeq = SelectionSequence("MyTMBcSeq", TopSelection = MyTMBcSel)
DaVinci().appendToMainSequence( [ MyTMBcSeq.sequence() ] )

# FINAL TUPLE
tuple = DecayTreeTuple("Bc2JpsiMu_Tuple")
tuple.Inputs = [ MyTMBcSeq.outputLocation() ]
tuple.Decay = "[B_c+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^mu+]CC"
#tuple.ToolList = []

DaVinci().appendToMainSequence( [ tuple ] )
