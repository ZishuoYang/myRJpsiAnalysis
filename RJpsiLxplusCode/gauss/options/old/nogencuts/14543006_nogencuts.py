# file /afs/cern.ch/lhcb/software/releases/DBASE/Gen/DecFiles/v25r20/options/14543006.py generated: Mon, 17 Dec 2012 13:53:06
#
# Event Type: 14543006
#
# ASCII decay Descriptor: [B_c+ -> (J/psi(1S) -> mu+ mu-) mu+ nu_mu]cc
#
from Configurables import Generation
Generation().EventType = 14543006
Generation().SampleGenerationTool = "Special"
from Configurables import Special
Generation().addTool( Special )
Generation().Special.ProductionTool = "BcVegPyProduction"
Generation().PileUpTool = "FixedLuminosityForRareProcess"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "Mu_MM_Ebert.dec"
Generation().Special.CutTool = "BcDaughtersInLHCb"
from Configurables import BcDaughtersInLHCb
Generation().Special.addTool( BcDaughtersInLHCb )
Generation().Special.BcDaughtersInLHCb.ChargedThetaMin = 0.
Generation().Special.BcDaughtersInLHCb.ChargedThetaMax = 10.
Generation().Special.BcDaughtersInLHCb.NeutralThetaMin = 0.
Generation().Special.BcDaughtersInLHCb.NeutralThetaMax = 10.
#Generation().FullGenEventCutTool = "DiLeptonInAcceptance"
