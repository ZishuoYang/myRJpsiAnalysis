#
# Options specific for a given job
# ie. setting of random number seed and name of output files
#

from Gauss.Configuration import *

#--Generator phase, set random numbers
GaussGen = GenInit("GaussGen")
GaussGen.FirstEventNumber = 1
GaussGen.RunNumber        = 1082

#--Number of events
nEvts = 10000
LHCbApp().EvtMax = nEvts

#Gauss().OutputType = 'NONE'
#Gauss().Histograms = 'NONE'
#--Set name of output files for given job (uncomment the lines)
#  Note that if you do not set it Gauss will make a name based on event type,
#  number of events and the date
#idFile = 'GaussTest'
#HistogramPersistencySvc().OutputFile = idFile+'-histos.root'
#
#OutputStream("GaussTape").Output = "DATAFILE='PFN:%s.sim' TYP='POOL_ROOTTREE' OPT='RECREATE'"%idFile

#GenMonitor = GaudiSequencer( "GenMonitor" )
#SimMonitor = GaudiSequencer( "SimMonitor" )
#GenMonitor.Members += [ "GaussMonitor::CheckLifeTimeHepMC/HepMCLifeTime" ]
#SimMonitor.Members += [ "GaussMonitor::CheckLifeTimeMC/MCLifeTime" ]

Gauss().Production = 'PGUN'

## 
##  Example on how to run only the generator phase
##  It can be passed as additional argument to gaudirun.py directly
##   > gaudirun.py $APPCONFIGOPTS/Gauss/MC09-b5TeV-md100.py \
##                 $APPCONFIGOPTS/Conditions/MC09-20090602-vc-md100.py \
##                 $DECFILESROOT/options/EVENTTYPE.opts \
##                 $LBPYTHIAROOT/options/Pythia.opts \
##                 $GAUSSOPTS/GenStandAlone.py \
##                 $GAUSSOPTS/Gauss-Job.py
##  or you can set the property in your Gauss-Job.py
##  Port to python of GenStandAlone.opts
## 

from Gauss.Configuration import *

Gauss().Phases = ["Generator","GenToMCTree"] 

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

