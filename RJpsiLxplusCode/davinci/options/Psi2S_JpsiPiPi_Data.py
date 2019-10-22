#########################################################################
# Y -> J/psi mu, J/psi -> mu mu
# For running over DATA, 2012
#
# @author Jack Wimberley
# @date 2013-12-01
##########################################################################

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc_Psi2S_Cal_histos.root"
DaVinci().TupleFile = "Bc_Psi2S_Cal.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = False # Data or MC
DaVinci().Simulation = simulation
DaVinci().Lumi = True

DaVinci().DataType = '2012'
DaVinci().EvtMax = 10000

##############
### FILTER ###
##############

from Filters import TriggerStrippingFilter
DaVinci().EventPreFilters = TriggerStrippingFilter.filters("Filters")

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

from CalSelection import MyPsi2SCalSeq
finalsel = MyPsi2SCalSeq.sequence()
RecSeq.Members += [ finalsel ]

from Refitter import getPsi2SCalRefitter
refitter = getPsi2SCalRefitter(MyPsi2SCalSeq.outputLocation())
RecSeq.Memers += [ refitter ]

####################
### JPSIRECTUPLE ###
####################

from Psi2SCalTuple import getPsi2SCalTuple
tuple = getPsi2SCalTuple(MyPsi2SCalSeq.outputLocation())
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
