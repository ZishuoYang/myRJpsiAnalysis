######################################################################
# Background mode for Bc analysis
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiMu_histos.root"
DaVinci().TupleFile = "Bc2JpsiMu.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = True # Data or MC
DaVinci().Simulation = simulation

##############
### FILTER ###
##############

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

#######################################
### MC BEAUTY -> JPSI X TRUTH TUPLE ###
#######################################

from MCTuples import MCBeauty2JpsiXTuple
DaVinci().appendToMainSequence( [ JpsiTuple ] )

##############################
### RECONSTRUCTED SEQUENCE ###
##############################

from Configurables import GaudiSequencer
RecSeq = GaudiSequencer("RecSeq")

##################
### CORRECTION ###
##################

from Configurables import TrackScaleState
from Configurables import TrackSmearState
if (simulation):
    smear = TrackSmearState('StateSmear')
    RecSeq.Members += [smear]
else:
    scale = TrackScaleState('StateScale')
    RecSeq.Members += [scale]

#################
### SELECTION ###
#################

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

finalsel = MyTMBcSeq.sequence()
from Configurables import ReadHltReport
finalsel.Members += [ ReadHltReport() ]
RecSeq.Members += [ finalsel ]

from Refitter import getRefitter
refitter = getRefitter(MyTMBcSeq.outputLocation())
RecSeq.Memers += [ refitter ]

####################
### JPSIRECTUPLE ###
####################

from JpsiRecTuple import JpsiRecTuple
tuple = getJpsiReqTuple(simulation,MyTMBcSeq.outputLocation())
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
