# File for setting Beam conditions corresponding to most of the data
# taken in 2012 with magnet up.
#
# Requires Gauss v45r1 or higher.
#
# Syntax is: 
#  gaudirun.py $APPCONFIGOPTS/Gauss/Sim08-Beam4000GeV-mu100-2012-nu2.5.py
#              $DECFILESROOT/options/30000000.opts (i.e. event type)
#              $LBGENROOT/options/GEN.py (i.e. production engine)
#              Sim08-2011-Tags.py (i.e. database tags to be used)
#              gaudi_extra_options_NN_II.py (ie. job specific: random seed,
#                               output file names, see Gauss-Job.py as example)
#
from Configurables import Gauss
from GaudiKernel import SystemOfUnits

#--Set the L/nbb, total cross section and revolution frequency and configure
#  the pileup tool, a CrossingRate of 11.245 kilohertz is used internally
Gauss().Luminosity        = 0.302*(10**30)/(SystemOfUnits.cm2*SystemOfUnits.s)
Gauss().TotalCrossSection = 93.2*SystemOfUnits.millibarn

#--Set the average position of the IP
Gauss().InteractionPosition = [  0.626*SystemOfUnits.mm ,
                                 0.100*SystemOfUnits.mm ,
                                25.732*SystemOfUnits.mm ]


#--Set the bunch RMS, this will be used for calculating the sigmaZ of the
#  Interaction Region. SigmaX and SigmaY are calculated from the beta* and
#  emittance
Gauss().BunchRMS = 73.54*SystemOfUnits.mm

#--Set the energy of the beam,
Gauss().BeamMomentum      = 4.0*SystemOfUnits.TeV

#--the half effective crossing angle (in LHCb coordinate system), horizontal
#  and vertical. And tilts of the beam line
Gauss().BeamHCrossingAngle =  0.236*SystemOfUnits.mrad
Gauss().BeamVCrossingAngle =  0.100*SystemOfUnits.mrad
Gauss().BeamLineAngles     = [ 0.0, 0.0 ]

#--beta* and emittance (beta* is nomimally 3m and e_norm 2.5um,
#                       adjusted to match sigmaX and sigmaY)
Gauss().BeamEmittance     = 0.0038*SystemOfUnits.mm
Gauss().BeamBetaStar      = 3.2*SystemOfUnits.m


