##############################################################################
# File for running Gauss as a particle gun, GEANT off, for dimuon mass studies
##############################################################################

#--Pick beam conditions as set in AppConfig
from Gaudi.Configuration import *
importOptions("$APPCONFIGOPTS/Gauss/Sim08-Beam4000GeV-md100-2012-nu2.5.py")

#--Set database tags using those for Sim08
from Configurables import LHCbApp
LHCbApp().DDDBtag   = "Sim08-20130503-1"
LHCbApp().CondDBtag = "Sim08-20130503-1-vc-md100"

#
# Options specific for a given job
# ie. setting of random number seed and name of output files
#

from Gauss.Configuration import *

#--Generator phase, set random numbers
GaussGen = GenInit("GaussGen")
GaussGen.FirstEventNumber = 1
GaussGen.RunNumber        = 1111

#--Number of events
nEvts = 1
LHCbApp().EvtMax = nEvts

Gauss().Phases = ["Generator","GenToMCTree"]
#Gauss().Output = 'NONE'
#Gauss().Histograms = 'NONE'

#--Set name of output files for given job (uncomment the lines)
#  Note that if you do not set it Gauss will make a name based on event type,
#  number of events and the date
#idFile = 'DiMuonGun-Gauss'
#HistogramPersistencySvc().OutputFile = idFile+'-histos.root'
#OutputStream("GaussTape").Output = "DATAFILE='PFN:%s.sim' TYP='POOL_ROOTTREE' OPT='RECREATE'"%idFile

#GenMonitor = GaudiSequencer( "GenMonitor" )
#SimMonitor = GaudiSequencer( "SimMonitor" )
#GenMonitor.Members += [ "GaussMonitor::CheckLifeTimeHepMC/HepMCLifeTime" ]
#SimMonitor.Members += [ "GaussMonitor::CheckLifeTimeMC/MCLifeTime" ]

#gtos = GenerationToSimulation()
#gtos.SkipGeant = True
#gs = GaudiSequencer("GenMonitor")
#MCTruthStream = OutputStream("MCTruthStream")
#MCTruthStream.ItemList += [
#    "/Event/Gen#1"
#    , "/Event/Gen/HepMCEvents#1"
#    , "/Event/MC#1"
#    , "/Event/MC/Header#1"
#    , "/Event/MC/Particles#1"
#    ,"/Event/MC/Vertices#1"
#    ]
#MCTruthStream.Output = "DATAFILE='MCTruth.sim' TYP='POOL_ROOTTREE' OPT='RECREATE'"
#gs.Members += [ SimInit(), gtos, MCTruthStream ]

