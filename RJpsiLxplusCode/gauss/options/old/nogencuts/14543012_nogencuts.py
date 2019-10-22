# file /afs/cern.ch/lhcb/software/releases/DBASE/Gen/DecFiles/v25r20/options/14543011.py generated: Mon, 17 Dec 2012 13:53:10
#
# Event Type: 14543011
#
# ASCII decay Descriptor: [B_c+ -> (JPsi -> mu+ mu-) (tau+ -> mu+ nu_mu anti-nu_tau) nu_tau]cc
#
from Configurables import Generation
Generation().EventType = 14543011
Generation().SampleGenerationTool = "Special"
from Configurables import Special
Generation().addTool( Special )
Generation().Special.ProductionTool = "BcVegPyProduction"
Generation().PileUpTool = "FixedLuminosityForRareProcess"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "../dkfiles/Tau_MM_Kiselev.dec"
Generation().Special.CutTool = "BcDaughtersInLHCb"
Generation().Special.addTool( BcDaughtersInLHCb )
Generation().Special.BcDaughtersInLHCb.ChargedThetaMin = 0.
Generation().Special.BcDaughtersInLHCb.ChargedThetaMax = 10.
Generation().Special.BcDaughtersInLHCb.NeutralThetaMin = 0.
Generation().Special.BcDaughtersInLHCb.NeutralThetaMax = 10.
