#########################################################################
# Y -> J/psi mu, J/psi -> mu mu
# For running over DATA, 2012
# Intentionally pick a mis-IDed muon
#
# @author Jack Wimberley
# @date 2013-12-01
##########################################################################

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "B_JpsiKst_Unbias_MC_histos.root"
DaVinci().TupleFile = "B_JpsiKst_Unbias_MC.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = True # Data or MC
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

from BJpsiKstUnbiasSelection import MyBJpsiKstUnbiasSeq
finalsel = MyBJpsiKstUnbiasSeq.sequence()
RecSeq.Members += [ finalsel ]

#################################
### VELO TRACKS FOR ISOLATION ###
#################################

from Configurables import ChargedProtoParticleMaker

veloprotos = ChargedProtoParticleMaker("BProtoPMaker")
veloprotos.Inputs = ["Rec/Track/Best"]
veloprotos.Output = "Rec/ProtoP/myProtoPMaker/ProtoParticles"

DaVinci().appendToMainSequence( [ veloprotos ])

from Gaudi.Configuration import *
from Configurables       import ProtoParticleCALOFilter,CombinedParticleMaker,NoPIDsParticleMaker

from CommonParticles.Utils import *

algorithm = NoPIDsParticleMaker('StdNoPIDsVeloPions',  Particle = 'pion')
algorithm.Input = "Rec/ProtoP/myProtoPMaker/ProtoParticles"
selector = trackSelector ( algorithm , trackTypes = ['Velo'] )

locations = updateDoD ( algorithm )
DaVinci().appendToMainSequence( [ algorithm ])

######################
### JPSIPIRECTUPLE ###
######################

from JpsiKstUnbiasRecTuple import getJpsiKstUnbiasRecTuple
tuple = getJpsiKstUnbiasRecTuple(simulation,MyBJpsiKstUnbiasSeq.outputLocation())
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
