# file /afs/cern.ch/lhcb/software/releases/DBASE/Gen/DecFiles/v27r13/options/12442001.py generated: Mon, 07 Oct 2013 08:51:06
#
# Event Type: 12442001
#
# ASCII decay Descriptor: {[B+ => (J/psi(1S) -> mu+ mu- {,gamma} {,gamma}) X]cc, [B+ => (psi(2S) -> mu+ mu- {,gamma} {,gamma} X]cc}
#
from Gaudi.Configuration import *
importOptions( "$DECFILESROOT/options/CharmoniumInAcc.py" )
from Configurables import Generation
Generation().EventType = 12442001
Generation().SampleGenerationTool = "SignalRepeatedHadronization"
from Configurables import SignalRepeatedHadronization
Generation().addTool( SignalRepeatedHadronization )
Generation().SignalRepeatedHadronization.ProductionTool = "PythiaProduction"
from Configurables import ToolSvc
from Configurables import EvtGenDecay
ToolSvc().addTool( EvtGenDecay )
ToolSvc().EvtGenDecay.UserDecayFile = "../dkfiles/Bu_JpsiX,mm=JpsiInAcc.dec"
Generation().SignalRepeatedHadronization.CutTool = "SelectedDaughterInLHCb"
Generation().SignalRepeatedHadronization.SignalPIDList = [ 521,-521 ]

from Configurables import LoKi__FullGenEventCutTool
Generation().SignalRepeatedHadronization.addTool(LoKi__GenCutTool,'TightCut')
trackFilters = Generation().SignalRepeatedHadronization.TightCut
trackFilters.Preambulo += [
    "from LoKiCore.functions import has, count"
    , "from GaudiKernel.SystemOfUnits import *"
    , "GoodJpsiFromB = GDECTREE('J/psi(1S) => mu+ mu-') & (GPT > 1.8*GeV)"
    , "GoodMuPFromJpsi = (GCHILD(GPT,1)>500*MeV) & (GCHILD(GP,1)>2.8*GeV) & (GCHILD(GPZ,1)>0) & (GCHILD(abs(GPX/GPZ),1)>0.015) & (GCHILD(abs(GPX/GPZ),1)<0.325) & (GCHILD(abs(GPY/GPZ),1)>0.010) & (GCHILD(abs(GPY/GPZ),1)<0.275)"
    , "GoodMuMFromJpsi = (GCHILD(GPT,2)>500*MeV) & (GCHILD(GP,2)>2.8*GeV) & (GCHILD(GPZ,2)>0) & (GCHILD(abs(GPX/GPZ),2)>0.015) & (GCHILD(abs(GPX/GPZ),2)<0.325) & (GCHILD(abs(GPY/GPZ),2)>0.010) & (GCHILD(abs(GPY/GPZ),2)<0.275)"
    , "GoodBachMuFromB = ('mu+' == GABSID) & (GPT > 280 * MeV) & (GP > 2.8 * GeV) & (GPZ > 0) & (abs(GPX/GPZ) > 0.015) & (abs(GPX/GPZ) < 0.325) & (abs(GPY/GPZ) > 0.010) & (abs(GPY/GPZ) < 0.275)"
    ]
trackFilters.Code = "has(GBEAUTY & GINTREE(GoodJpsiFromB & GoodMuPFromJpsi & GoodMuMFromJpsi)) & has(GBEAUTY & GINTREE(GoodBachMuFromB) & ~GINTREE(GoodJpsiFromB) )"

