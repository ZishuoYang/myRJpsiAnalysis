##############################################################################
# File for running Brunel MC11a simulation -- use v41r1p1
##############################################################################

from Configurables import Brunel
Brunel().DataType  = "2012"
Brunel().InputType = "DIGI"
Brunel().WithMC = True

##############################################################################

from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"


