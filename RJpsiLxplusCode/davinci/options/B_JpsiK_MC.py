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

DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "Bc_JpsiK_Cal_histos.root"
DaVinci().TupleFile = "Bc_JpsiK_Cal.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = False # Data or MC
DaVinci().Simulation = simulation
DaVinci().Lumi = True

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

from Selection import MyBJpsiKCalSeq
finalsel = MyBJpsiKCalSeq.sequence()
from Configurables import ReadHltReport
finalsel.Members += [ ReadHltReport() ]
RecSeq.Members += [ finalsel ]

from Refitter import getJpsiKRefitter
refitter = getJpsiKRefitter(MyBJpsiKcalSeq.outputLocation())
RecSeq.Memers += [ refitter ]

####################
### JPSIRECTUPLE ###
####################

from JpsiKCalTuple import getJpsiKCalTuple
tuple = getJpsiKCalTuple(MyBJpsiKCalSeq.outputLocation())
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
