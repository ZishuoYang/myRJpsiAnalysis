##############################################################################
# File for running Boole 2012 simulation
##############################################################################

from Configurables import Boole
Boole().DataType  = "2012"

##############################################################################

from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"
#set inputdata with Ganga
