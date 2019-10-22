
# content of the file BParticleGun.py
from Configurables import ParticleGun, MomentumRange, FlatNParticles, ToolSvc, EvtGenDecay
from GaudiKernel import SystemOfUnits

pgun = ParticleGun()
pgun.ParticleGunTool = "MomentumRange"
pgun.addTool( MomentumRange , name = "MomentumRange" )

pgun.NumberOfParticlesTool = "FlatNParticles"
pgun.addTool( FlatNParticles , name = "FlatNParticles" )

pgun.MomentumRange.PdgCodes = [ 511 , -511 ]

tsvc = ToolSvc()
tsvc.addTool( EvtGenDecay , name = "EvtGenDecay" )
tsvc.EvtGenDecay.UserDecayFile = "BDecayFile.dec"
pgun.DecayTool = "EvtGenDecay"

pgun.MomentumRange.MomentumMin = 20.0*SystemOfUnits.GeV
pgun.MomentumRange.MomentumMax = 140.0*SystemOfUnits.GeV
