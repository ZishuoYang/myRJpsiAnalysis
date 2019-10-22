#########################################################################
# Y -> J/psi mu, J/psi -> mu mu
# For running over MC Bc -> J/psi tau nu, tau -> mu nu nu
#
# @author Jack Wimberley
# @date 2013-12-01
##########################################################################
import sys
sys.path.insert(0, '')

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "Bc_JpsiTau_MC_histos.root"
DaVinci().TupleFile = "Bc_JpsiTau_MC.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = True # Data or MC
DaVinci().Simulation = simulation

#######################################
### MC BC -> JPSI TAU NU TRUTH TUPLE ###
#######################################

#from MCTuples import MCBc2JpsiTauNuTuple
#DaVinci().appendToMainSequence( [ MCBc2JpsiTauNuTuple ] )

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

from PhysSelPython.Wrappers import SelectionSequence
from Selection import SelectionSeq, outputLocation
RecSeq.Members += [SelectionSeq]

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

####################
### JPSIRECTUPLE ###
####################

from JpsiRecTuple import getJpsiRecTuple
tuple = getJpsiRecTuple(simulation,outputLocation)
RecSeq.Members += [ tuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
DaVinci().DataType = '2012'
