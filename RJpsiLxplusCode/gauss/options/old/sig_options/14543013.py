# file /afs/cern.ch/lhcb/software/releases/DBASE/Gen/DecFiles/v25r20/options/14543011.py generated: Mon, 17 Dec 2012 13:53:10
#
# Event Type: 14543013
#
# ASCII decay Descriptor: [B_c+ -> (JPsi -> mu+ mu-) (tau+ -> mu+ nu_mu anti-nu_tau) nu_tau]cc
#
from Configurables import Generation
Generation().EventType = 14543013
Generation().SampleGenerationTool = "Special"
from Configurables import Special
Generation().addTool( Special )
Generation().Special.ProductionTool = "BcVegPyProduction"
Generation().PileUpTool = "FixedLuminosityForRareProcess"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "$DECFILESROOT/dkfiles/Bc_JpsiTauNu,mununu=BcVegPy,ffKiselev,DecProdCut.dec"
Generation().Special.CutTool = "BcDaughtersInLHCb"
