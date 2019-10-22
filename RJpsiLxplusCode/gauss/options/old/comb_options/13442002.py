# file /afs/cern.ch/lhcb/software/releases/DBASE/Gen/DecFiles/v27r13/options/13442002.py generated: Mon, 07 Oct 2013 08:51:12
#
# Event Type: 13442002
#
# ASCII decay Descriptor: {[B_s0 => (J/psi(1S) -> mu+ mu- {,gamma} {,gamma}) X]cc, [B_s0 => (psi(2S) -> mu+ mu- {,gamma} {,gamma} X]cc}
#
from Gaudi.Configuration import *
importOptions( "$DECFILESROOT/options/CharmoniumInAcc.py" )
from Configurables import Generation
Generation().EventType = 13442002
Generation().SampleGenerationTool = "SignalRepeatedHadronization"
from Configurables import SignalRepeatedHadronization
Generation().addTool( SignalRepeatedHadronization )
Generation().SignalRepeatedHadronization.ProductionTool = "PythiaProduction"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "$Bs_JpsiX,mm=JpsiInAcc.dec"
Generation().SignalRepeatedHadronization.CutTool = "SelectedDaughterInLHCb"
Generation().SignalRepeatedHadronization.SignalPIDList = [ 531,-531 ]
Generation().FullGenEventCutTool = "JpsiLeptonInAcceptance"
from Configurables import JpsiLeptonInAcceptance
Generation().addTool( JpsiLeptonInAcceptance )
Generation().JpsiLeptonInAcceptance.PreselDoca = True

#Generation().SignalRepeatedHadronization.CutTool = "LoKi::GenCutTool/TightCut"
#from Configurables import LoKi__GenCutTool
#Generation().SignalRepeatedHadronization.addTool(LoKi__GenCutTool,'TightCut')
#trackFilters = Generation().SignalRepeatedHadronization.TightCut
#trackFilters.Preambulo += [
#    'inAccXZ   = in_range ( 0.015, abs(GPX/GPZ), 0.325 )',
#    'inAccYZ   = in_range ( 0.010, abs(GPY/GPZ), 0.275 )' , 
#    'goodMuon  = ( GPT > 500 * MeV ) & ( GP > 2.85 * GeV ) & inAcc & ( GPZ > 0 )' , 
#    'goodPsi   = ( GPT > 1.85 * GeV )'
#    ]
#trackFilters.Decay = "Beauty --> ^( J/psi(1S) => ^mu+ ^mu-) ..."
#trackFilters.Cuts = {
#    'J/psi(1S)' : 'goodPsi',
#    '[mu+]cc' : 'goodMuon'
#    }
