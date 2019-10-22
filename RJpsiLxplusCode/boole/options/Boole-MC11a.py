##############################################################################
# File for running Boole MC11a simulation -- use v23r1
##############################################################################

from Configurables import Boole
Boole().DataType  = "2012"

##############################################################################

from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"

