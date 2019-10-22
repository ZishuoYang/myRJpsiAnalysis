##############################################################################
# File for running Gauss MC11a simulation -- use v41r4
##############################################################################


##############################################################################
# MC11a Beam Conditions
##############################################################################

# These were condensed from the following options files:
# $APPCONFIGOPTS/Gauss/Beam3500GeV-mu100-MC11-nu2.py

# File for setting Beam conditions for MC11a corresponding to most of the data
# taken in 2011 with magnet up.
# Beam 3.5 TeV, beta* = 3m , emittance(normalized) ~ 2 micron
#
# Requires Gauss v40r0 or higher.
#
# Syntax is: 
#  gaudirun.py $APPCONFIGOPTS/Gauss/Beam3500GeV-mu100-MC11-nu2.py
#              $DECFILESROOT/options/30000000.opts (i.e. event type)
#              $LBGENROOT/options/GEN.py (i.e. production engine)
#              MC11a-Tags.py (i.e. database tags to be used)
#              gaudi_extra_options_NN_II.py (ie. job specific: random seed,
#                               output file names, see Gauss-Job.py as example)
#

from Configurables import Gauss
from Configurables import EventClockSvc, FakeEventTime
from GaudiKernel import SystemOfUnits

#--Set the L/nbb, total cross section and revolution frequency and configure
#--the pileup tool
Gauss().Luminosity        = 0.247*(10**30)/(SystemOfUnits.cm2*SystemOfUnits.s)
# CrossingRate = 11.245*SystemOfUnits.kilohertz used internally
Gauss().TotalCrossSection = 91.1*SystemOfUnits.millibarn

#--Set the luminous region for colliding beams and beam gas and configure
#--the corresponding vertex smearing tools, the choice of the tools is done
#--by the event type
Gauss().InteractionSize = [ 0.030*SystemOfUnits.mm, 0.030*SystemOfUnits.mm,
                            57.00*SystemOfUnits.mm ]  # Only z is used from Gauss v40r0, the others are calcuted from beta* and emittance, and in fact it is NOT the Interaction size but the BunchRMS

Gauss().InteractionPosition = [ 0.0*SystemOfUnits.mm ,
                                0.0*SystemOfUnits.mm ,
                                6.2*SystemOfUnits.mm ]

#--Set the energy of the beam,
#--the half effective crossing angle (in LHCb coordinate system),
#--beta* and emittance (e_norm ~ 2 microns)
Gauss().BeamMomentum      = 3.5*SystemOfUnits.TeV
Gauss().BeamCrossingAngle = 0.020*SystemOfUnits.mrad
Gauss().BeamEmittance     = 0.0022*SystemOfUnits.mm
Gauss().BeamBetaStar      = 3.0*SystemOfUnits.m
Gauss().BeamLineAngles    = [-0.085*SystemOfUnits.mrad, 0.035*SystemOfUnits.mrad]


#
#--Starting time, all events will have the same
#--Can be used for beam conditions: YEBM (year,energy,bunch-spacing,field)
ec = EventClockSvc()
ec.addTool(FakeEventTime(), name="EventTimeDecoder")
ec.EventTimeDecoder.StartTime = 1302.0*SystemOfUnits.ms
ec.EventTimeDecoder.TimeStep  = 0.0

##############################################################################
# Database tags for MC11a
##############################################################################

from Configurables import LHCbApp
LHCbApp().CondDBtag = "sim-20111111-vc-mu100"
LHCbApp().DDDBtag   = "MC11-20111102"

##############################################################################
# Generation options
##############################################################################

#
# Options specific for a given job
# ie. setting of random number seed and name of output files
#

from Gauss.Configuration import *

#--Generator phase, set random numbers
GaussGen = GenInit("GaussGen")
GaussGen.FirstEventNumber = 1
GaussGen.RunNumber        = 7382

#--Number of events
LHCbApp().EvtMax = 5000

#Gauss().Phases = ["Generator"]
#Gauss().Output = 'NONE'
#Gauss().Histograms = 'NONE'
#--Set name of output files for given job (uncomment the lines)
#  Note that if you do not set it Gauss will make a name based on event type,
#  number of events and the date
#idFile = 'Bc2JpsiMuNu-Gauss'
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

##############################################################################
# Extra Generation options (IGNORE)
##############################################################################

# These were condensed from the following options file:
# $LBGENXICCROOT/options/GenXicc.py
# $APPCONFIGOPTS/Gauss/GenXicc_ProdFix.py
# $APPCONFIGOPTS/Gauss/G4PL_LHEP_EmNoCuts.py

#from Configurables import Generation, Special, GenXiccProduction, XiccDaughtersInLHCb, ToolSvc

#GenXiccListOfCommands = [
#  "loggrade iusecurdir 1",
#  "vegasinf number 10000",
#  "vegasinf nitmx 2",
#  "vegasbin nvbin 100",
#  "confine ptcut 0.2",
#  "counter xmaxwgt 1000000"
#]

#gen = Generation()
#gen.addTool( Special , name = "Special" )
#gen.Special.addTool( GenXiccProduction, name = "GenXiccProduction" )
#gen.Special.ProductionTool = "GenXiccProduction"

#gen.Special.GenXiccProduction.GenXiccCommands = [
#    "loggrade iusecurdir 0",
#    "vegasinf number 10000",
#    "vegasinf nitmx 2",
#    "vegasbin nvbin 100",
#    "confine ptcut 0.2",
#    "counter xmaxwgt 1000000"]
#gen.Special.GenXiccProduction.BaryonState = "Xi_cc+"
#gen.Special.GenXiccProduction.BeamMomentum = Gauss().BeamMomentum
#gen.PileUpTool = "FixedLuminosityForRareProcess";

#gen.Special.CutTool = "XiccDaughtersInLHCb"
#gen.Special.addTool(XiccDaughtersInLHCb)
#gen.Special.XiccDaughtersInLHCb.BaryonState = gen.Special.GenXiccProduction.BaryonState

#Gauss().PhysicsList = {"Em":'NoCuts', "Hadron":"LHEP", "GeneralPhys":True, "LHCbPhys":True}



