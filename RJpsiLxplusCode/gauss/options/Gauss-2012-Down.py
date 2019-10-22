##############################################################################
# File for running Gauss with Sim08 configuration and beam conditions as in
# production for 2012 data (4.0 TeV beams, nu=2.5, no spill-over)
#
# Syntax is:
#   gaudirun.py Gauss-2012.py <someInputJobConfiguration>.py
##############################################################################

#--Pick beam conditions as set in AppConfig
from Gaudi.Configuration import *
importOptions("$APPCONFIGOPTS/Gauss/Sim08-Beam4000GeV-md100-2012-nu2.5.py")

#--Set database tags using those for Sim08
from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"
