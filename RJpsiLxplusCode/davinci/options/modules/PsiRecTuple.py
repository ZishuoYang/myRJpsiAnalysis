from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *
from Configurables import TupleToolTrigger

triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    , "Hlt2DiMuonDetachedJPsiDecision"
    , "Hlt2DiMuonDetachedHeavyDecision"
    ]

def getPsiRecTuple(simulation,outputLocation):
    PsiRecTuple = DecayTreeTuple("PsiRecTuple")
    PsiRecTuple.Inputs = [ outputLocation ]
    PsiRecTuple.Decay = "[B_c+ -> ^(psi(2S) -> ^mu+ ^mu-) ^mu+]CC"
    PsiRecTuple.addBranches({
        "Bc" : "[^(B_c+ -> (psi(2S) -> mu+ mu-) mu+)]CC"
        , "Psi" : "[B_c+ -> ^(psi(2S) -> mu+ mu-) mu+]CC"
        , "MuP" : "[B_c+ -> (psi(2S) -> ^mu+ mu-) mu+]CC"
        , "MuM" : "[B_c+ -> (psi(2S) -> mu+ ^mu-) mu+]CC"
        , "BachMu" : "[B_c+ -> (psi(2S) -> mu+ mu-) ^mu+]CC"
        })

    PsiRecTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # ISOLATION
    from Configurables import TupleToolApplyIsolation
    PsiRecTuple.Bc.addTool(TupleToolApplyIsolation, name="TupleToolApplyIsolationSoft")
    PsiRecTuple.Bc.TupleToolApplyIsolationSoft.WeightsFile="weightsSoft.xml"
    PsiRecTuple.Bc.ToolList+=["TupleToolApplyIsolation/TupleToolApplyIsolationSoft"]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    PsiRecTuple.addTupleTool(LoKiEvtTool,"LHETT")
    PsiRecTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    PsiRecTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        }

    # J/psi and Mu DOCA
    from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
    PsiRecTuple.Bc.addTupleTool(LoKiTool,"DocaTool")
    PsiRecTuple.Bc.DocaTool.Preambulo += [
        "PFUNA = LoKi.Particles.PFunA"
        , "from LoKiCore.functions import *"
        ]
    PsiRecTuple.Bc.DocaTool.Variables = {
        "DOCA" : "PFUNA(AMINDOCA(''))"
        , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = PsiRecTuple.Psi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    PsiRecTuple.BachMu.addTupleTool("TupleToolMuonPid")
    PsiRecTuple.MuP.addTupleTool("TupleToolMuonPid")
    PsiRecTuple.MuM.addTupleTool("TupleToolMuonPid")    

    # VERTEX ISOLATION
    from Configurables import TupleToolVtxIsoln
    BcTTVI = PsiRecTuple.Bc.addTupleTool("TupleToolVtxIsoln/BcTTVI")
    
    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    BachMuTTTI = PsiRecTuple.BachMu.addTupleTool("TupleToolTrackIsolation/BachMuTTTI")
    BachMuTTTI.FillAsymmetry = True
    BachMuTTTI.MinConeAngle = 0.5
    BachMuTTTI.MaxConeAngle = 0.5
    BachMuTTTI.StepSize = 0.1

    # B BACKGROUND
    # from Configurables import TupleToolBcBBkg
    # BcBBkg = PsiRecTuple.Bc.addTupleTool("TupleToolBcBBkg/BcBBkg")

    # MiSSING MASS
    CMVars = PsiRecTuple.addTupleTool('LoKi::Hybrid::TupleTool')
    CMVars.Variables = {
        'MM2' : 'INFO(1234567+0, 0.)',
        'Q2' : 'INFO(1234567+1, 0.)',
        'P_Lab' : 'INFO(1234567+2, 0.)',
        'E_Lab' : 'INFO(1234567+3, 0.)',
        'P_CM' : 'INFO(1234567+4, 0.)',
        'E_CM' : 'INFO(1234567+5, 0.)',
        'CosTheta_CM' : 'INFO(1234567+6, 0.)',
        'PsiP_CM' : 'INFO(1234567+7, 0.)',
        'PsiE_CM' : 'INFO(1234567+8, 0.)',
        'BachMuP_CM' : 'INFO(1234567+9, 0.)',
        'BachMuE_CM' : 'INFO(1234567+10, 0.)',
        'CTAU' : 'INFO(1234567+11, 0.)',
        'TAU' : 'INFO(1234567+12, 0.)',
        'LogTAU' : 'INFO(1234567+13, 0.)',
        }
    
    # MC INFO
    if (simulation):

        truth = PsiRecTuple.addTupleTool("TupleToolMCTruth")
        truth.ToolList = [
            "MCTupleToolKinematic"
            , "MCTupleToolHierarchy"
            ]
        
        # TUPLETOOLMCBACKGROUNDINFO
        from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
        BcTTMCBI = PsiRecTuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/BcTTMCBI")
        BcTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
        BcTTMCBI.BackgroundCategory.SemileptonicDecay = True
        BcTTMCBI.BackgroundCategory.NumNeutrinos = 3
        PsiTTMCBI = PsiRecTuple.Psi.addTupleTool("TupleToolMCBackgroundInfo/PsiTTMCBI")
       
        PsiRecTuple.Bc.addTupleTool(LoKiTool,"MCMatchTool")
        PsiRecTuple.Bc.MCMatchTool.Preambulo += [
            "from LoKiCore.functions import *"
            , "from LoKiPhysMC.decorators import *"
            , "from PartProp.Nodes import CC"
            , "PsiMuNu_F = mcMatch('[B_c+ => (psi(2S) => mu+ mu-) mu+ nu_mu]CC')"
            , "PsiMuNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) -> mu+ mu-) mu+ nu_mu]CC')"
            , "PsiTauNu_F = mcMatch('[B_c+ => (psi(2S) => mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "PsiTauNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) -> mu+ mu-) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Chic1MuNu_F = mcMatch('[B_c+ => (chi_c1(1P) => (psi(2S) => mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic1MuNu_NoFSR_F = mcMatch('[B_c+ -> (chi_c1(1P) -> (psi(2S) -> mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic2MuNu_F = mcMatch('[B_c+ => (chi_c2(1P) => (psi(2S) => mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic2MuNu_NoFSR_F = mcMatch('[B_c+ -> (chi_c2(1P) -> (psi(2S) -> mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Psi2SMuNu_F = mcMatch('[B_c+ => (psi(2S) --> (psi(2S) => mu+ mu-) ...) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) --> (psi(2S) -> mu+ mu-) ...) mu+ nu_mu]CC')"
            , "Psi2STauNu_F = mcMatch('[B_c+ => (psi(2S) --> (psi(2S) => mu+ mu-) ...) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) --> (psi(2S) -> mu+ mu-) ...) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_PipPim_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi+ pi-) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_PipPim_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi+ pi-) mu+ nu_mu]CC')"
            , "Psi2STauNu_PipPim_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi+ pi-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_PipPim_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi+ pi-) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Pi0Pi0_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi0 pi0) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Pi0Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi0 pi0) mu+ nu_mu]CC')"
            , "Psi2STauNu_Pi0Pi0_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi0 pi0) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Pi0Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi0 pi0) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Eta_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) eta) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Eta_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) eta) mu+ nu_mu]CC')"
            , "Psi2STauNu_Eta_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) eta) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Eta_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) eta) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Pi0_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi0) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi0) mu+ nu_mu]CC')"
            , "Psi2STauNu_Pi0_F = mcMatch('[B_c+ => (psi(2S) => (psi(2S) => mu+ mu-) pi0) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (psi(2S) -> mu+ mu-) pi0) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Chic1_F = mcMatch('[B_c+ => (psi(2S) => (chi_c1(1P) => (psi(2S) => mu+ mu-) gamma) gamma) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Chic1_F = mcMatch('[B_c+ -> (psi(2S) -> (chi_c1(1P) -> (psi(2S) -> mu+ mu-) gamma) gamma) mu+ nu_mu]CC')"
            , "Psi2STauNu_Chic1_F = mcMatch('[B_c+ => (psi(2S) => (chi_c1(1P) => (psi(2S) => mu+ mu-) gamma) gamma) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Chic1_F = mcMatch('[B_c+ -> (psi(2S) -> (chi_c1(1P) -> (psi(2S) -> mu+ mu-) gamma) gamma) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "PsiDx_F = mcMatch('[B_c+ --> (psi(2S) => mu+ mu-) (Xc --> mu+ nu_mu ...) ...]CC')"
            ]
        PsiRecTuple.Bc.MCMatchTool.Variables = {
            "PsiMuNu" : "switch(PsiMuNu_F,1,0)"
            , "PsiMuNu_NoFSR" : "switch(PsiMuNu_NoFSR_F,1,0)"
            , "PsiTauNu" : "switch(PsiTauNu_F,1,0)"
            , "PsiTauNu_NoFSR" : "switch(PsiTauNu_NoFSR_F,1,0)"
            , "Chic1MuNu" : "switch(Chic1MuNu_F,1,0)"
            , "Chic1MuNu_NoFSR" : "switch(Chic1MuNu_NoFSR_F,1,0)"
            , "Chic2MuNu" : "switch(Chic2MuNu_F,1,0)"
            , "Chic2MuNu_NoFSR" : "switch(Chic2MuNu_NoFSR_F,1,0)"
            , "Psi2SMuNu" : "switch(Psi2SMuNu_F,1,0)"
            , "Psi2SMuNu_NoFSR" : "switch(Psi2SMuNu_NoFSR_F,1,0)"
            , "Psi2STauNu" : "switch(Psi2STauNu_F,1,0)"
            , "Psi2STauNu_NoFSR" : "switch(Psi2STauNu_NoFSR_F,1,0)"
            , "Psi2SMuNu_PipPim" : "switch(Psi2SMuNu_PipPim_F,1,0)"
            , "Psi2SMuNu_NoFSR_PipPim" : "switch(Psi2SMuNu_NoFSR_PipPim_F,1,0)"
            , "Psi2STauNu_PipPim" : "switch(Psi2STauNu_PipPim_F,1,0)"
            , "Psi2STauNu_NoFSR_PipPim" : "switch(Psi2STauNu_NoFSR_PipPim_F,1,0)"
            , "Psi2SMuNu_Pi0Pi0" : "switch(Psi2SMuNu_Pi0Pi0_F,1,0)"
            , "Psi2SMuNu_NoFSR_Pi0Pi0" : "switch(Psi2SMuNu_NoFSR_Pi0Pi0_F,1,0)"
            , "Psi2STauNu_Pi0Pi0" : "switch(Psi2STauNu_Pi0Pi0_F,1,0)"
            , "Psi2STauNu_NoFSR_Pi0Pi0" : "switch(Psi2STauNu_NoFSR_Pi0Pi0_F,1,0)"
            , "Psi2SMuNu_Eta" : "switch(Psi2SMuNu_Eta_F,1,0)"
            , "Psi2SMuNu_NoFSR_Eta" : "switch(Psi2SMuNu_NoFSR_Eta_F,1,0)"
            , "Psi2STauNu_Eta" : "switch(Psi2STauNu_Eta_F,1,0)"
            , "Psi2STauNu_NoFSR_Eta" : "switch(Psi2STauNu_NoFSR_Eta_F,1,0)"
            , "Psi2SMuNu_Pi0" : "switch(Psi2SMuNu_Pi0_F,1,0)"
            , "Psi2SMuNu_NoFSR_Pi0" : "switch(Psi2SMuNu_NoFSR_Pi0_F,1,0)"
            , "Psi2STauNu_Pi0" : "switch(Psi2STauNu_Pi0_F,1,0)"
            , "Psi2STauNu_NoFSR_Pi0" : "switch(Psi2STauNu_NoFSR_Pi0_F,1,0)"
            , "Psi2SMuNu_Chic1" : "switch(Psi2SMuNu_Chic1_F,1,0)"
            , "Psi2SMuNu_NoFSR_Chic1" : "switch(Psi2SMuNu_NoFSR_Chic1_F,1,0)"
            , "Psi2STauNu_Chic1" : "switch(Psi2STauNu_Chic1_F,1,0)"
            , "Psi2STauNu_NoFSR_Chic1" : "switch(Psi2STauNu_NoFSR_Chic1_F,1,0)"
            , "PsiDx" : "switch(PsiDx_F,1,0)"
            }


    return PsiRecTuple

