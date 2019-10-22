##############################################################################
# File for running Brunel 2011 simulation -- use v43r2p7
##############################################################################

from Configurables import Brunel
Brunel().DataType  = "2011"
Brunel().InputType = "DIGI"
Brunel().WithMC = True

##############################################################################

from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"


