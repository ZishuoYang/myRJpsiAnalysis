#######################################################################
# Y -> Jpsi Mu, Jpsi -> Mu Mu (B_c, missing neutrinos)
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *

# OPTIONS
simulation = True; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc_NormChecker_histos.root"
DaVinci().TupleFile = "Bc_NormChecker.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]
