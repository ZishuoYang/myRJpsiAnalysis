#########################################################################
# Y -> chi_c1 mu, chi_c1 -> mu mu
# For running over MC Bc -> chi_c1 mu nu
#
# @author Jack Wimberley
# @date 2013-12-01
##########################################################################

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "Bc_Chic1Mu_MC_histos.root"
DaVinci().TupleFile = "Bc_Chic1Mu_MC.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = True # Data or MC
DaVinci().Simulation = simulation

#######################################
### MC BC -> JPSI MU NU TRUTH TUPLE ###
#######################################

#from Configurables import PrintMCTree, PrintMCDecayTreeTool
#mctree = PrintMCTree("PrintTrueBc")
#mctree.addTool( PrintMCDecayTreeTool, name = "PrintMC" )
#mctree.PrintMC.Information = "Name M P Px Py Pz Pt"
#mctree.ParticleNames = [  "B_c+", "B_c-" ]
#mctree.Depth = 2  # down to the K and mu
#DaVinci().appendToMainSequence( [ mctree ] )

#from MCTuples import MCBc2Chic1MuNuTuple
#DaVinci().appendToMainSequence( [ MCBc2Chic1MuNuTuple ] )

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
