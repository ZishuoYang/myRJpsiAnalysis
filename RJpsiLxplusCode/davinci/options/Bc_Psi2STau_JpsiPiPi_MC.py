#########################################################################
# Y -> Jpsi Mu, Jpsi -> mu mu
# For running over MC psi(2S) -> J/psi pi pi 
#
# @author Jack Wimberley
# @date 2013-12-01
##########################################################################

from Gaudi.Configuration import *
from GaudiKernel.SystemOfUnits import *
from Configurables import DaVinci

MessageSvc().OutputLevel = INFO

DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc_Psi2STau_MC_histos.root"
DaVinci().TupleFile = "Bc_Psi2STau_MC.root"

##########################
### SWITCHABLE OPTIONS ###
##########################

simulation = True # Data or MC
DaVinci().Simulation = simulation

#######################################
### MC BC -> JPSI MU NU TRUTH TUPLE ###
#######################################

from MCTuples import MCBc2PsiTauNuJpsiPiPiTuple
DaVinci().appendToMainSequence( [ MCBc2PsiTauNuJpsiPiPiTuple ] )

##############################
### RECONSTRUCTED SEQUENCE ###
##############################

from Configurables import GaudiSequencer
RecSeq = GaudiSequencer("RecSeq")

#################
### SELECTION ###
#################

from BcPsi2SJpiPiPiMuSelection import MyBc2PsiMuSeq
finalsel = MyBc2PsiMuSeq.sequence()
from Configurables import ReadHltReport
finalsel.Members += [ ReadHltReport() ]
RecSeq.Members += [ finalsel ]

###################
### PSIRECTUPLE ###
###################

from PsiRecTuple import PsiRecTuple
PsiRecTuple.Inputs = [ MyBc2PsiMuSeq.outputLocation() ]
RecSeq.Members += [ PsiRecTuple ]

#######################
### APPEND SEQUENCE ###
#######################

DaVinci().appendToMainSequence( [ RecSeq ] ) 
