# file /nightlies/jenkins/workspace/nightly-slot-checkout/tmp/checkout/DBASE/Gen/DecFiles/v27r43/options/14543007.py generated: Tue, 21 Apr 2015 11:38:33
#
# Event Type: 14543007
#
# ASCII decay Descriptor: [B_c+ => (J/psi(1S) => mu+ mu-) mu+ nu_mu]CC
#
from Configurables import ParticleGun
from Configurables import MomentumRange
ParticleGun().addTool( MomentumRange )
from GaudiKernel import SystemOfUnits
ParticleGun().MomentumRange.MomentumMin = 0.0*SystemOfUnits.GeV
from GaudiKernel import SystemOfUnits
ParticleGun().MomentumRange.MomentumMax = 0.0*SystemOfUnits.GeV
ParticleGun().EventType = 59999999
ParticleGun().ParticleGunTool = "MomentumRange"
ParticleGun().NumberOfParticlesTool = "FlatNParticles"
ParticleGun().MomentumRange.PdgCodes = [ 541 ]

from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay, name = "EvtGenDecay" )
ToolSvc().EvtGenDecay.UserDecayFile = "$DECFILESROOT/dkfiles/Bc_JpsiMuNu,mm=BcVegPy,ffKiselev.dec"
ParticleGun().DecayTool = "EvtGenDecay"
