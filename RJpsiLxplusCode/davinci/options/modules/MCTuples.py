from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
from Configurables import LoKi__Hybrid__MCTupleTool
from Configurables import TupleToolTrigger
from Configurables import TupleToolStripping

vars = {
    "MCE" : "MCE"
    , "MCETA" : "MCETA"
    , "MCP" : "MCP"
    , "MCPX" : "MCPX"
    , "MCPY" : "MCPY"
    , "MCPZ" : "MCPZ"
    , "MCPT" : "MCPT"
    , "MCTHETA" : "MCTHETA"
    , "MCPHI" : "MCPHI"
    , "ACC" : "switch( ( (MCTHETA > 0.005) & (MCTHETA < 0.400) ) | ( (MCTHETA < 3.1365926536) & (MCTHETA > 2.7415926536) ), 1, 0)"
    , "PCS" : "switch( (MCPT > 5*1000) & (MCPT < 100*1000) & ( ( (MCETA > 2.5) & (MCETA < 4.5) ) | ( (MCETA < -2.5) & (MCETA > -4.5) ) ), 1, 0)"
    }

triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    , "Hlt2DiMuonDetachedJPsiDecision"
    , "Hlt2DiMuonDetachedHeavyDecision"
    ]

lines = [
    "StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision"
    ]

########################
### BC -> JPSI MU NU ###
########################

jpsimudecay = "[B_c+ => ^(J/psi(1S) => ^mu+ ^mu-) ^mu+ ^nu_mu]CC"
MCBc2JpsiMuNuTuple = MCDecayTreeTuple("MCBc2JpsiMuNuTuple")
MCBc2JpsiMuNuTuple.TupleName = "MCBc2JpsiMuNuDecayTree"
MCBc2JpsiMuNuTuple.Decay = jpsimudecay
MCBc2JpsiMuNuTuple.addBranches({
    "Bc" : "[^(B_c+ => (J/psi(1S) => mu+ mu-) mu+ nu_mu)]CC"
    , "Jpsi" : "[B_c+ => ^(J/psi(1S) => mu+ mu-) mu+ nu_mu]CC"
    , "MuP" : "[B_c+ => (J/psi(1S) => ^mu+ mu-) mu+ nu_mu]CC"
    , "MuM" : "[B_c+ => (J/psi(1S) => mu+ ^mu-) mu+ nu_mu]CC"
    , "BachMu" : "[B_c+ => (J/psi(1S) => mu+ mu-) ^mu+ nu_mu]CC"
    , "NuMu" : "[B_c+ => (J/psi(1S) => mu+ mu-) mu+ ^nu_mu]CC"
    })
MCBc2JpsiMuNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
JpsiMuLTT = MCBc2JpsiMuNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/JpsiMuLTT")
JpsiMuLTT.Preambulo += ["from LoKiCore.functions import *"]
JpsiMuLTT.Variables = vars

# TUPLE TOOL TRIGGER
JpsiMuTTT = MCBc2JpsiMuNuTuple.addTupleTool("TupleToolTrigger/JpsiMuTTT")
JpsiMuTTT.TriggerList = triggers
JpsiMuTTT.VerboseL0 = True
JpsiMuTTT.VerboseHlt1 = True
JpsiMuTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
JpsiMuTTS = MCBc2JpsiMuNuTuple.addTupleTool("TupleToolStripping/JpsiMuTTS")
JpsiMuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2JpsiMuNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2JpsiMuNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2JpsiMuNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

#########################
### BC -> JPSI TAU NU ###
#########################

jpsitaudecay = "[B_c+ -> ^(J/psi(1S) => ^mu+ ^mu-) ^(tau+ => ^mu+ ^nu_mu ^nu_tau~) ^nu_tau]CC"
MCBc2JpsiTauNuTuple = MCDecayTreeTuple("MCBc2JpsiTauNuTuple")
MCBc2JpsiTauNuTuple.TupleName = "MCBc2JpsiTauNuDecayTree"
MCBc2JpsiTauNuTuple.Decay = jpsitaudecay
MCBc2JpsiTauNuTuple.addBranches({
    "Bc" : "[^(B_c+ -> (J/psi(1S) => mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau)]CC"
    , "Jpsi" : "[B_c+ -> ^(J/psi(1S) => mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuM" : "[B_c+ -> (J/psi(1S) => mu+ ^mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "Tau" : "[B_c+ -> (J/psi(1S) => mu+ mu-) ^(tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => mu+ mu-) (tau+ => ^mu+ nu_mu nu_tau~) nu_tau]CC"
    , "NuMu" : "[B_c+ -> (J/psi(1S) => mu+ mu-) (tau+ => mu+ ^nu_mu nu_tau~) nu_tau]CC"
    , "NuTauBar" : "[B_c+ -> (J/psi(1S) => mu+ mu-) (tau+ => mu+ nu_mu ^nu_tau~) nu_tau]CC"
    , "NuTau" : "[B_c+ -> (J/psi(1S) => mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) ^nu_tau]CC"
    })
MCBc2JpsiTauNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]
    
# HANDY KINEMATIC VARIABLES
JpsiTauLTT = MCBc2JpsiMuNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/JpsiTauLTT")
JpsiTauLTT.Preambulo += ["from LoKiCore.functions import *"]
JpsiTauLTT.Variables = vars
    
# TUPLE TOOL TRIGGER
JpsiTauTTT = MCBc2JpsiTauNuTuple.addTupleTool("TupleToolTrigger/JpsiTauTTT")
JpsiTauTTT.TriggerList = triggers
JpsiTauTTT.VerboseL0 = True
JpsiTauTTT.VerboseHlt1 = True
JpsiTauTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
JpsiTauTTS = MCBc2JpsiTauNuTuple.addTupleTool("TupleToolStripping/JpsiTauTTS")
JpsiTauTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2JpsiTauNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2JpsiTauNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2JpsiTauNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")


###########################
### BC -> PSI(2S) MU NU ###
###########################

psimudecay = "[B_c+ -> ^(psi(2S) -> ^(J/psi(1S) -> ^mu+ ^mu-) ... ) ^mu+ ^nu_mu]CC"
MCBc2PsiMuNuTuple = MCDecayTreeTuple("MCBc2PsiMuNuTuple")
MCBc2PsiMuNuTuple.TupleName = "MCBc2PsiMuNuDecayTree"
MCBc2PsiMuNuTuple.Decay = psimudecay
MCBc2PsiMuNuTuple.addBranches({
    "Bc" : "[^(B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu)]CC"
    , "psi2S" : "[B_c+ -> ^(psi(2S) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "Jpsi" : "[B_c+ -> (psi(2S) -> ^(J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuP" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> ^mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuM" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ ^mu-) ... ) mu+ nu_mu]CC"
    , "BachMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) ... ) ^mu+ nu_mu]CC"
    , "NuMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ ^nu_mu]CC"
    })
MCBc2PsiMuNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
PsiMuLTT = MCBc2PsiMuNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/PsiMuLTT")
PsiMuLTT.Preambulo += ["from LoKiCore.functions import *"]
PsiMuLTT.Variables = vars

# TUPLE TOOL TRIGGER
from Configurables import TupleToolTrigger
PsiMuTTT = MCBc2PsiMuNuTuple.addTupleTool("TupleToolTrigger/PsiMuTTT")
PsiMuTTT.VerboseL0 = True
PsiMuTTT.VerboseHlt1 = True
PsiMuTTT.VerboseHlt2 = True
PsiMuTTT.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
PsiMuTTS = MCBc2PsiMuNuTuple.addTupleTool("TupleToolStripping/PsiMuTTS")
PsiMuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2PsiMuNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiMuNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiMuNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

#############################
### BC -> CHIC1(!P) MU NU ###
#############################

chic1mudecay = "[B_c+ -> ^(chi_c1(1P) -> ^(J/psi(1S) -> ^mu+ ^mu-) ... ) ^mu+ ^nu_mu]CC"
MCBc2Chic1MuNuTuple = MCDecayTreeTuple("MCBc2Chic1MuNuTuple")
MCBc2Chic1MuNuTuple.TupleName = "MCBc2Chic1MuNuDecayTree"
MCBc2Chic1MuNuTuple.Decay = psimudecay
MCBc2Chic1MuNuTuple.addBranches({
    "Bc" : "[^(B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu)]CC"
    , "chic1" : "[B_c+ -> ^(chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "Jpsi" : "[B_c+ -> (chi_c1(1P) -> ^(J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuP" : "[B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> ^mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuM" : "[B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> mu+ ^mu-) ... ) mu+ nu_mu]CC"
    , "BachMu" : "[B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) ... ) ^mu+ nu_mu]CC"
    , "NuMu" : "[B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ ^nu_mu]CC"
    })
MCBc2Chic1MuNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
Chic1MuLTT = MCBc2Chic1MuNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/Chic1MuLTT")
Chic1MuLTT.Preambulo += ["from LoKiCore.functions import *"]
Chic1MuLTT.Variables = vars

# TUPLE TOOL TRIGGER
from Configurables import TupleToolTrigger
Chic1MuTTT = MCBc2Chic1MuNuTuple.addTupleTool("TupleToolTrigger/Chic1MuTTT")
Chic1MuTTT.VerboseL0 = True
Chic1MuTTT.VerboseHlt1 = True
Chic1MuTTT.VerboseHlt2 = True
Chic1MuTTT.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
Chic1MuTTS = MCBc2Chic1MuNuTuple.addTupleTool("TupleToolStripping/Chic1MuTTS")
Chic1MuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2Chic1MuNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2Chic1MuNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2Chic1MuNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

#############################
### BC -> CHIC2(!P) MU NU ###
#############################

chic2mudecay = "[B_c+ -> ^(chi_c2(1P) -> ^(J/psi(1S) -> ^mu+ ^mu-) ... ) ^mu+ ^nu_mu]CC"
MCBc2Chic2MuNuTuple = MCDecayTreeTuple("MCBc2Chic2MuNuTuple")
MCBc2Chic2MuNuTuple.TupleName = "MCBc2Chic2MuNuDecayTree"
MCBc2Chic2MuNuTuple.Decay = psimudecay
MCBc2Chic2MuNuTuple.addBranches({
    "Bc" : "[^(B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu)]CC"
    , "chic2" : "[B_c+ -> ^(chi_c2(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "Jpsi" : "[B_c+ -> (chi_c2(1P) -> ^(J/psi(1S) -> mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuP" : "[B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> ^mu+ mu-) ... ) mu+ nu_mu]CC"
    , "MuM" : "[B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> mu+ ^mu-) ... ) mu+ nu_mu]CC"
    , "BachMu" : "[B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> mu+ mu-) ... ) ^mu+ nu_mu]CC"
    , "NuMu" : "[B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> mu+ mu-) ... ) mu+ ^nu_mu]CC"
    })
MCBc2Chic2MuNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
Chic2MuLTT = MCBc2Chic2MuNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/Chic2MuLTT")
Chic2MuLTT.Preambulo += ["from LoKiCore.functions import *"]
Chic2MuLTT.Variables = vars

# TUPLE TOOL TRIGGER
from Configurables import TupleToolTrigger
Chic2MuTTT = MCBc2Chic2MuNuTuple.addTupleTool("TupleToolTrigger/Chic2MuTTT")
Chic2MuTTT.VerboseL0 = True
Chic2MuTTT.VerboseHlt1 = True
Chic2MuTTT.VerboseHlt2 = True
Chic2MuTTT.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
Chic2MuTTS = MCBc2Chic2MuNuTuple.addTupleTool("TupleToolStripping/Chic2MuTTS")
Chic2MuTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2Chic2MuNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2Chic2MuNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2Chic2MuNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

###################################################
### BC -> PSI(2S) MU NU, PSI(2S) -> J/PSI PI PI ###
###################################################

psimujpsipipidecay = "[B_c+ -> ^(psi(2S) -> ^(J/psi(1S) -> ^mu+ ^mu-) ^pi+ ^pi- ) ^mu+ ^nu_mu]CC"
MCB2PsiMuNuJpsiPiPiTuple = MCDecayTreeTuple("MCB2PsiMuNuJpsiPiPiTuple")
MCB2PsiMuNuJpsiPiPiTuple.TupleName = "MCBc2PsiMuNuJpsiPiPiDecayTree"
MCB2PsiMuNuJpsiPiPiTuple.Decay = psimujpsipipidecay
MCB2PsiMuNuJpsiPiPiTuple.addBranches({
    "Bc" : "[^(B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi- ) mu+ nu_mu)]CC"
    , "psi2S" : "[B_c+ -> ^(psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi- ) mu+ nu_mu]CC"
    , "Jpsi" : "[B_c+ -> (psi(2S) -> ^(J/psi(1S) -> mu+ mu-) pi+ pi- ) mu+ nu_mu]CC"
    , "PiP" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) ^pi+ pi- ) mu+ nu_mu]CC"
    , "PiM" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ ^pi- ) mu+ nu_mu]CC"
    , "MuP" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> ^mu+ mu-) pi+ pi- ) mu+ nu_mu]CC"
    , "MuM" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ ^mu-) pi+ pi- ) mu+ nu_mu]CC"
    , "BachMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi- ) ^mu+ nu_mu]CC"
    , "NuMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi- ) mu+ ^nu_mu]CC"
    })
MCB2PsiMuNuJpsiPiPiTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
PsiMuNuJpsiPiPiLTT = MCB2PsiMuNuJpsiPiPiTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/PsiMuNuJpsiPiPiLTT")
PsiMuNuJpsiPiPiLTT.Preambulo += ["from LoKiCore.functions import *"]
PsiMuNuJpsiPiPiLTT.Variables = vars

# TUPLE TOOL TRIGGER
from Configurables import TupleToolTrigger
PsiMuNuJpsiPiPiTTT = MCB2PsiMuNuJpsiPiPiTuple.addTupleTool("TupleToolTrigger/PsiMuNuJpsiPiPiTTT")
PsiMuNuJpsiPiPiTTT.VerboseL0 = True
PsiMuNuJpsiPiPiTTT.VerboseHlt1 = True
PsiMuNuJpsiPiPiTTT.VerboseHlt2 = True
PsiMuNuJpsiPiPiTTT.TriggerList = triggers

# TUPLE TOOL STRIPPING
from Configurables import TupleToolStripping
PsiMuNuJpsiPiPiTTS = MCB2PsiMuNuJpsiPiPiTuple.addTupleTool("TupleToolStripping/PsiMuNuJpsiPiPiTTS")
PsiMuNuJpsiPiPiTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCB2PsiMuNuJpsiPiPiTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCB2PsiMuNuJpsiPiPiTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCB2PsiMuNuJpsiPiPiTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

############################
### BC -> PSI(2S) TAU NU ###
############################

psitaudecay = "[B_c+ -> ^(J/psi(1S) => ^mu+ ^mu-) ^(tau+ => ^mu+ ^nu_mu ^nu_tau~) ^nu_tau]CC"
MCBc2PsiTauNuTuple = MCDecayTreeTuple("MCBc2PsiTauNuTuple")
MCBc2PsiTauNuTuple.TupleName = "MCBc2PsiTauNuDecayTree"
MCBc2PsiTauNuTuple.Decay = psitaudecay
MCBc2PsiTauNuTuple.addBranches({
    "Bc" : "[^(B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) nu_tau)]CC"
    , "psi2S" : "[B_c+ -> ^(psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "Jpsi" : "[B_c+ -> (psi(21S) -> ^(J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuP" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => ^mu+ mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuM" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ ^mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "Tau" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) ^(tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "BachMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => ^mu+ nu_mu nu_tau~) nu_tau]CC"
    , "NuMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ ^nu_mu nu_tau~) nu_tau]CC"
    , "NuTauBar" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ nu_mu ^nu_tau~) nu_tau]CC"
    , "NuTau" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) ... ) (tau+ => mu+ nu_mu nu_tau~) ^nu_tau]CC"
    })
MCBc2PsiTauNuTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]
    
# HANDY KINEMATIC VARIABLES
PsiTauLTT = MCBc2PsiTauNuTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/PsiTauLTT")
PsiTauLTT.Preambulo += ["from LoKiCore.functions import *"]
PsiTauLTT.Variables = vars

# TUPLE TOOL TRIGGER
PsiTauTTT = MCBc2PsiTauNuTuple.addTupleTool("TupleToolTrigger/PsiTauTTT")
PsiTauTTT.TriggerList = triggers
PsiTauTTT.VerboseL0 = True
PsiTauTTT.VerboseHlt1 = True
PsiTauTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
PsiTauTTS = MCBc2PsiTauNuTuple.addTupleTool("TupleToolStripping/PsiTauTTS")
PsiTauTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2PsiTauNuTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiTauNuTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiTauNuTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

####################################################
### BC -> PSI(2S) TAU NU, PSI(2S) -> J/PSI PI PI ###
####################################################

psitaujpsipipidecay = "[B_c+ -> ^(psi(2S) -> ^(J/psi(1S) => ^mu+ ^mu-) ^pi+ ^pi-) ^(tau+ => ^mu+ ^nu_mu ^nu_tau~) ^nu_tau]CC"
MCBc2PsiTauNuJpsiPiPiTuple = MCDecayTreeTuple("MCBc2PsiTauNuJpsiPiPiTuple")
MCBc2PsiTauNuJpsiPiPiTuple.TupleName = "MCBc2PsiTauNuJpsiPiPiDecayTree"
MCBc2PsiTauNuJpsiPiPiTuple.Decay = psitaujpsipipidecay
MCBc2PsiTauNuJpsiPiPiTuple.addBranches({
    "Bc" : "[^(B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau)]CC"
    , "psi2S" : "[B_c+ -> ^(psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "Jpsi" : "[B_c+ -> (psi(21S) -> ^(J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "PiP" : "[B_c+ -> (psi(21S) -> (J/psi(1S) => mu+ mu-) ^pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "PiM" : "[B_c+ -> (psi(21S) -> (J/psi(1S) => mu+ mu-) pi+ ^pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuP" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => ^mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "MuM" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ ^mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "Tau" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) ^(tau+ => mu+ nu_mu nu_tau~) nu_tau]CC"
    , "BachMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => ^mu+ nu_mu nu_tau~) nu_tau]CC"
    , "NuMu" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ ^nu_mu nu_tau~) nu_tau]CC"
    , "NuTauBar" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu ^nu_tau~) nu_tau]CC"
    , "NuTau" : "[B_c+ -> (psi(2S) -> (J/psi(1S) => mu+ mu-) pi+ pi- ) (tau+ => mu+ nu_mu nu_tau~) ^nu_tau]CC"
    })
MCBc2PsiTauNuJpsiPiPiTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]
    
# HANDY KINEMATIC VARIABLES
PsiTauNuJpsiPiPiLTT = MCBc2PsiTauNuJpsiPiPiTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/PsiTauNuJpsiPiPiLTT")
PsiTauNuJpsiPiPiLTT.Preambulo += ["from LoKiCore.functions import *"]
PsiTauNuJpsiPiPiLTT.Variables = vars
    
# TUPLE TOOL TRIGGER
PsiTauNuJpsiPiPiTTT = MCBc2PsiTauNuJpsiPiPiTuple.addTupleTool("TupleToolTrigger/PsiTauNuJpsiPiPiTTT")
PsiTauNuJpsiPiPiTTT.TriggerList = triggers
PsiTauNuJpsiPiPiTTT.VerboseL0 = True
PsiTauNuJpsiPiPiTTT.VerboseHlt1 = True
PsiTauNuJpsiPiPiTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
PsiTauNuJpsiPiPiTTS = MCBc2PsiTauNuJpsiPiPiTuple.addTupleTool("TupleToolStripping/PsiTauNuJpsiPiPiTTS")
PsiTauNuJpsiPiPiTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2PsiTauNuJpsiPiPiTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiTauNuJpsiPiPiTuple.MuM.addTupleTool("MCTupleToolReconstructed")
MCBc2PsiTauNuJpsiPiPiTuple.BachMu.addTupleTool("MCTupleToolReconstructed")

########################
### Beauty -> JPSI X ###
########################

jpsixdecay = "Beauty --> ^(J/psi(1S) => ^mu+ ^mu-) ..."
MCBeauty2JpsiXTuple = MCDecayTreeTuple("MCBeauty2JpsiXTuple")
MCBeauty2JpsiXTuple.TupleName = "JpsiXDecayTree"
MCBeauty2JpsiXTuple.Decay = jpsixdecay
MCBeauty2JpsiXTuple.ToolList = []
MCBeauty2JpsiXTuple.addBranches({
    "Beauty" : "^(Beauty --> (J/psi(1S) => mu+ mu-) ...)"
    , "Jpsi" : "Beauty --> ^(J/psi(1S) => mu+ mu-) ..."
    , "MuP"  : "Beauty --> (J/psi(1S) => ^mu+ mu-) ..."
    , "MuM"  : "Beauty --> (J/psi(1S) => mu+ ^mu-) ..."
    })
MCBeauty2JpsiXTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
JpsiXLTT = MCBeauty2JpsiXTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/JpsiXLTT")
JpsiXLTT.Preambulo += ["from LoKiCore.functions import *"]
JpsiXLTT.Variables = vars

# TUPLE TOOL TRIGGER
JpsiXTTT = MCBeauty2JpsiXTuple.addTupleTool("TupleToolTrigger/JpsiXTTT")
JpsiXTTT.TriggerList = triggers
JpsiXTTT.VerboseL0 = True
JpsiXTTT.VerboseHlt1 = True
JpsiXTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
JpsiXTTS = MCBeauty2JpsiXTuple.addTupleTool("TupleToolStripping/JpsiXTTS")
JpsiXTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBeauty2JpsiXTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBeauty2JpsiXTuple.MuM.addTupleTool("MCTupleToolReconstructed")

#########################
### BC -> JPSI CHARM  ###
#########################

jpsicharmdecay = "[B_c+ -> ^(J/psi(1S) => ^mu+ ^mu-) Charm]CC"
MCBc2JpsiCharmTuple = MCDecayTreeTuple("MCBc2JpsiCharmTuple")
MCBc2JpsiCharmTuple.TupleName = "JpsiCharmDecayTree"
MCBc2JpsiCharmTuple.Decay = jpsicharmdecay
MCBc2JpsiCharmTuple.ToolList = []
MCBc2JpsiCharmTuple.addBranches({
    "Bc" : "[^(B_c+ -> (J/psi(1S) => mu+ mu-) Charm)]CC"
    , "Jpsi" : "[B_c+ -> ^(J/psi(1S) => mu+ mu-) Charm]CC"
    , "MuP"  : "[B_c+ -> (J/psi(1S) => ^mu+ mu-) Charm]CC" 
    , "MuM"  : "[B_c+ -> (J/psi(1S) => mu+ ^mu-) Charm]CC"
    , "Charm"  : "[B_c+ -> (J/psi(1S) => mu+ mu-) ^Charm]CC" 
  })
MCBc2JpsiCharmTuple.ToolList = [
    "MCTupleToolKinematic"
    , "TupleToolEventInfo"
    ]

# HANDY KINEMATIC VARIABLES
JpsiCharmLTT = MCBc2JpsiCharmTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/JpsiCharmLTT")
JpsiCharmLTT.Preambulo += ["from LoKiCore.functions import *"]
JpsiCharmLTT.Variables = vars

# TUPLE TOOL TRIGGER
JpsiCharmTTT = MCBc2JpsiCharmTuple.addTupleTool("TupleToolTrigger/JpsiCharmTTT")
JpsiCharmTTT.TriggerList = triggers
JpsiCharmTTT.VerboseL0 = True
JpsiCharmTTT.VerboseHlt1 = True
JpsiCharmTTT.VerboseHlt2 = True

# TUPLE TOOL STRIPPING
JpsiCharmTTS = MCBc2JpsiCharmTuple.addTupleTool("TupleToolStripping/JpsiCharmTTS")
JpsiCharmTTS.StrippingList = lines

# RECONSTRUCTIBLE INFO
MCBc2JpsiCharmTuple.MuP.addTupleTool("MCTupleToolReconstructed")
MCBc2JpsiCharmTuple.MuM.addTupleTool("MCTupleToolReconstructed")
