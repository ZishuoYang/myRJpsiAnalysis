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
DaVinci().HistogramFile = "Bc_JpsiPi_MC_histos.root"
DaVinci().TupleFile = "Bc_JpsiPi_MC.root"

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

from BcJpsiPiSelection import MyBcJpsiPiSeq
finalsel = MyBcJpsiPiSeq.sequence()
RecSeq.Members += [ finalsel ]

from Refitter import getJpsiPiRefitter
refitter = getJpsiPiRefitter(MyBcJpsiPiSeq.outputLocation())
RecSeq.Members += [ refitter ]

#################################
### VELO TRACKS FOR ISOLATION ###
#################################

from Configurables import ChargedProtoParticleMaker

veloprotos = ChargedProtoParticleMaker("BcProtoPMaker")
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

from JpsiPiRecTuple import getJpsiPiRecTuple
tuple = getJpsiPiRecTuple(simulation,MyBcJpsiPiSeq.outputLocation())
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
