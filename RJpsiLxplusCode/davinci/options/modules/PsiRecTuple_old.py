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

def getJpsiRecTuple(simulation,outputLocation):
    JpsiRecTuple = DecayTreeTuple("JpsiRecTuple")
    JpsiRecTuple.Inputs = [ outputLocation ]
    JpsiRecTuple.Decay = "[B_c+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^mu+]CC"
    JpsiRecTuple.addBranches({
        "Bc" : "[^(B_c+ -> (J/psi(1S) -> mu+ mu-) mu+)]CC"
        , "Jpsi" : "[B_c+ -> ^(J/psi(1S) -> mu+ mu-) mu+]CC"
        , "MuP" : "[B_c+ -> (J/psi(1S) -> ^mu+ mu-) mu+]CC"
        , "MuM" : "[B_c+ -> (J/psi(1S) -> mu+ ^mu-) mu+]CC"
        , "BachMu" : "[B_c+ -> (J/psi(1S) -> mu+ mu-) ^mu+]CC"
        })

    JpsiRecTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # ISOLATION
    from Configurables import TupleToolApplyIsolation
    JpsiRecTuple.Bc.addTool(TupleToolApplyIsolation, name="TupleToolApplyIsolationSoft")
    JpsiRecTuple.Bc.TupleToolApplyIsolationSoft.WeightsFile="weightsSoft.xml"
    JpsiRecTuple.Bc.ToolList+=["TupleToolApplyIsolation/TupleToolApplyIsolationSoft"]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    JpsiRecTuple.addTupleTool(LoKiEvtTool,"LHETT")
    JpsiRecTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    JpsiRecTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        }

    # J/psi and Mu DOCA
    from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
    JpsiRecTuple.Bc.addTupleTool(LoKiTool,"DocaTool")
    JpsiRecTuple.Bc.DocaTool.Preambulo += [
        "PFUNA = LoKi.Particles.PFunA"
        , "from LoKiCore.functions import *"
        ]
    JpsiRecTuple.Bc.DocaTool.Variables = {
        "DOCA" : "PFUNA(AMINDOCA(''))"
        , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = JpsiRecTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    JpsiRecTuple.BachMu.addTupleTool("TupleToolMuonPid")
    JpsiRecTuple.MuP.addTupleTool("TupleToolMuonPid")
    JpsiRecTuple.MuM.addTupleTool("TupleToolMuonPid")    

    # VERTEX ISOLATION
    from Configurables import TupleToolVtxIsoln
    BcTTVI = JpsiRecTuple.Bc.addTupleTool("TupleToolVtxIsoln/BcTTVI")
    
    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    BachMuTTTI = JpsiRecTuple.BachMu.addTupleTool("TupleToolTrackIsolation/BachMuTTTI")
    BachMuTTTI.FillAsymmetry = True
    BachMuTTTI.MinConeAngle = 0.5
    BachMuTTTI.MaxConeAngle = 0.5
    BachMuTTTI.StepSize = 0.1

    # B BACKGROUND
    # from Configurables import TupleToolBcBBkg
    # BcBBkg = JpsiRecTuple.Bc.addTupleTool("TupleToolBcBBkg/BcBBkg")

    # MiSSING MASS
    CMVars = JpsiRecTuple.addTupleTool('LoKi::Hybrid::TupleTool')
    CMVars.Variables = {
        'MM2' : 'INFO(1234567+0, 0.)',
        'Q2' : 'INFO(1234567+1, 0.)',
        'P_Lab' : 'INFO(1234567+2, 0.)',
        'E_Lab' : 'INFO(1234567+3, 0.)',
        'P_CM' : 'INFO(1234567+4, 0.)',
        'E_CM' : 'INFO(1234567+5, 0.)',
        'CosTheta_CM' : 'INFO(1234567+6, 0.)',
        'JpsiP_CM' : 'INFO(1234567+7, 0.)',
        'JpsiE_CM' : 'INFO(1234567+8, 0.)',
        'BachMuP_CM' : 'INFO(1234567+9, 0.)',
        'BachMuE_CM' : 'INFO(1234567+10, 0.)',
        'CTAU' : 'INFO(1234567+11, 0.)',
        'TAU' : 'INFO(1234567+12, 0.)',
        'LogTAU' : 'INFO(1234567+13, 0.)',
        }
    
    # MC INFO
    if (simulation):

        truth = JpsiRecTuple.addTupleTool("TupleToolMCTruth")
        truth.ToolList = [
            "MCTupleToolKinematic"
            , "MCTupleToolHierarchy"
            ]
        
        # TUPLETOOLMCBACKGROUNDINFO
        from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
        BcTTMCBI = JpsiRecTuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/BcTTMCBI")
        BcTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
        BcTTMCBI.BackgroundCategory.SemileptonicDecay = True
        BcTTMCBI.BackgroundCategory.NumNeutrinos = 3
        JpsiTTMCBI = JpsiRecTuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")
       
        JpsiRecTuple.Bc.addTupleTool(LoKiTool,"MCMatchTool")
        JpsiRecTuple.Bc.MCMatchTool.Preambulo += [
            "from LoKiCore.functions import *"
            , "from LoKiPhysMC.decorators import *"
            , "from PartProp.Nodes import CC"
            , "JpsiMuNu_F = mcMatch('[B_c+ => (J/psi(1S) => mu+ mu-) mu+ nu_mu]CC')"
            , "JpsiMuNu_NoFSR_F = mcMatch('[B_c+ -> (J/psi(1S) -> mu+ mu-) mu+ nu_mu]CC')"
            , "JpsiTauNu_F = mcMatch('[B_c+ => (J/psi(1S) => mu+ mu-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "JpsiTauNu_NoFSR_F = mcMatch('[B_c+ -> (J/psi(1S) -> mu+ mu-) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Chic1MuNu_F = mcMatch('[B_c+ => (chi_c1(1P) => (J/psi(1S) => mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic1MuNu_NoFSR_F = mcMatch('[B_c+ -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic2MuNu_F = mcMatch('[B_c+ => (chi_c2(1P) => (J/psi(1S) => mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Chic2MuNu_NoFSR_F = mcMatch('[B_c+ -> (chi_c2(1P) -> (J/psi(1S) -> mu+ mu-) gamma) mu+ nu_mu]CC')"
            , "Psi2SMuNu_F = mcMatch('[B_c+ => (psi(2S) --> (J/psi(1S) => mu+ mu-) ...) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) --> (J/psi(1S) -> mu+ mu-) ...) mu+ nu_mu]CC')"
            , "Psi2STauNu_F = mcMatch('[B_c+ => (psi(2S) --> (J/psi(1S) => mu+ mu-) ...) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_F = mcMatch('[B_c+ -> (psi(2S) --> (J/psi(1S) -> mu+ mu-) ...) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_PipPim_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi+ pi-) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_PipPim_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi-) mu+ nu_mu]CC')"
            , "Psi2STauNu_PipPim_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi+ pi-) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_PipPim_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi-) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Pi0Pi0_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi0 pi0) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Pi0Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi0 pi0) mu+ nu_mu]CC')"
            , "Psi2STauNu_Pi0Pi0_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi0 pi0) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Pi0Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi0 pi0) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Eta_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) eta) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Eta_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) eta) mu+ nu_mu]CC')"
            , "Psi2STauNu_Eta_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) eta) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Eta_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) eta) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Pi0_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi0) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi0) mu+ nu_mu]CC')"
            , "Psi2STauNu_Pi0_F = mcMatch('[B_c+ => (psi(2S) => (J/psi(1S) => mu+ mu-) pi0) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Pi0_F = mcMatch('[B_c+ -> (psi(2S) -> (J/psi(1S) -> mu+ mu-) pi0) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2SMuNu_Chic1_F = mcMatch('[B_c+ => (psi(2S) => (chi_c1(1P) => (J/psi(1S) => mu+ mu-) gamma) gamma) mu+ nu_mu]CC')"
            , "Psi2SMuNu_NoFSR_Chic1_F = mcMatch('[B_c+ -> (psi(2S) -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) gamma) gamma) mu+ nu_mu]CC')"
            , "Psi2STauNu_Chic1_F = mcMatch('[B_c+ => (psi(2S) => (chi_c1(1P) => (J/psi(1S) => mu+ mu-) gamma) gamma) (tau+ => mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "Psi2STauNu_NoFSR_Chic1_F = mcMatch('[B_c+ -> (psi(2S) -> (chi_c1(1P) -> (J/psi(1S) -> mu+ mu-) gamma) gamma) (tau+ -> mu+ nu_mu nu_tau~) nu_tau]CC')"
            , "JpsiDx_F = mcMatch('[B_c+ --> (J/psi(1S) => mu+ mu-) (Xc --> mu+ nu_mu ...) ...]CC')"
            ]
        JpsiRecTuple.Bc.MCMatchTool.Variables = {
            "JpsiMuNu" : "switch(JpsiMuNu_F,1,0)"
            , "JpsiMuNu_NoFSR" : "switch(JpsiMuNu_NoFSR_F,1,0)"
            , "JpsiTauNu" : "switch(JpsiTauNu_F,1,0)"
            , "JpsiTauNu_NoFSR" : "switch(JpsiTauNu_NoFSR_F,1,0)"
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
            , "JpsiDx" : "switch(JpsiDx_F,1,0)"
            }


    return JpsiRecTuple

#        CHARMONIUM = " [J/psi(1S), psi(2S), chi_c0(1P), chi_c1(1P), chi_c2(1P), X_1(3872), X_2(3872)] "
#        PI = " [pi+,pi-,pi0] "
#        K = " [K+,K-,K0,K~0] "
#        F0 = " [f_0(980),f_0(1370)] "
#        RHO = " [rho(770)+,rho(770)-,rho(770)0] "
#        K892 = " [K*(892)+,K*(892)-,K*(892)0,K*(892)~0] "
#        K1270 = " [K_1(1270)+,K_1(1270)-,K_1(1270)0,K_1(1270)~0] "
#        K1400 = " [K_1(1400)+,K_1(1400)-,K_1(1400)0,K_1(1400)~0] "
#        BUEXC = "[B*+,B*-,B*_2+,B*_2-,B*_0+,B*_0-,B_1(L)+,B_1(L)-]"
#        BDEXC = "[B*0,B*~0,B*_20,B*_2~0,B*_00,B*_0~0,B_1(L)0,B_1(L)~0]"
#        BSEXC = "[B*_s0,B*_s~0,B*_s20,B*_s2~0,B*_s00,B*_s0~0,B_s1(L)0,B_s1(L)~0]"
#        BCEXC = "[B_c*+,B_c*-,B_c2*+,B_c2*-,B_c0*+,B_c0*-,B_c1(L)+,B_c1(L)-]"
#        
#        JpsiRecTuple.Bc.addTupleTool(LoKiTool,"BcMCTool")
#        JpsiRecTuple.Bc.BcMCTool.Preambulo += [
#            "from LoKiCore.functions import *"
#            , "from LoKiPhysMC.decorators import *"
#            , "from PartProp.Nodes import CC"
#            ]
#        
#        JpsiRecTuple.Bc.BcMCTool.Variables = {
#            
#            # Bc -> J/psi X
#            "Bc2JpsiMuNu" : "switch(mcMatch('[B_c+ => J/psi(1S) mu+ nu_mu]CC'),1,0)"
#            , "Bc2JpsiTauNu" : "switch(mcMatch('[B_c+ => J/psi(1S) tau+ nu_tau]CC'),1,0)"
#            , "Bc2Psi2SMuNu" : "switch(mcMatch('[B_c+ => psi(2S) mu+ nu_mu]CC'),1,0)"
#            , "Bc2Psi2STauNu" : "switch(mcMatch('[B_c+ => psi(2S) tau+ nu_tau]CC'),1,0)"
#            , "B2JpsiK" : "switch(mcMatch('[B+ => J/psi(1S) K+]CC'),1,0)"
#            , "B2JpsiPi" : "switch(mcMatch('[B+ => J/psi(1S) pi+]CC'),1,0)"
#            , "Psi2S2JpsiPiPi" : "switch(mcMatch('psi(2S) => J/psi(1S) pi+ pi-'),1,0)"
            
#            # B type
#            , "IsABc" : "switch(mcMatch('[B_c+]cc'),1,0)"
#            , "IsABu" : "switch(mcMatch('[B+]cc'),1,0)"
#            , "IsABd" : "switch(mcMatch('[B0]cc'),1,0)"
#            , "IsABs" : "switch(mcMatch('[B_s0]cc'),1,0)"
#            , "IsABu_star" : "switch(mcMatch('" + BUEXC + "'),1,0)"
#            , "IsABd_star" : "switch(mcMatch('" + BDEXC + "'),1,0)"
#            , "IsABs_star" : "switch(mcMatch('" + BSEXC + "'),1,0)"
#            , "IsABc_star" : "switch(mcMatch('" + BCEXC + "'),1,0)"
            
#            # CHARMONIUM type
#            , "JpsiX" : "switch(mcMatch('Beauty -> J/psi(1S) ...'),1,0)"
#            , "Psi2SX" : "switch(mcMatch('Beauty -> psi(2S) ...'),1,0)"
#            , "ChiC0X" : "switch(mcMatch('Beauty -> chi_c0(1P) ...'),1,0)"
#            , "ChiC1X" : "switch(mcMatch('Beauty -> chi_c1(1P) ...'),1,0)"
#            , "ChiC2X" : "switch(mcMatch('Beauty -> chi_c2(1P) ...'),1,0)"
            
#            # B -> CHARMONIUM DECAY TYPES
#            , "Bm2CCPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + PI + "'),1,0)"
#            , "Bm2CCPiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + PI + PI + "'),1,0)"
#            , "Bm2CCEta" : "switch(mcMatch('Beauty => " + CHARMONIUM + "eta'),1,0)"
#            , "Bm2CCRho" : "switch(mcMatch('Beauty => " + CHARMONIUM + RHO + "'),1,0)"
#            , "Bm2CCEtaP" : "switch(mcMatch('Beauty => " + CHARMONIUM + "eta_prime'),1,0)"
#            , "Bm2CCF0" : "switch(mcMatch('Beauty => " + CHARMONIUM + F0 + "'),1,0)"
#            , "Bm2CCPhi" : "switch(mcMatch('Beauty => " + CHARMONIUM + "phi(1020)'),1,0)"
#            , "Bm2CCOmega" : "switch(mcMatch('Beauty => " + CHARMONIUM + "omega(782)'),1,0)"
#            , "Bm2CCK" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "'),1,0)"
#            , "Bm2CCKPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + PI + "'),1,0)"
#            , "Bm2CCKPiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + PI + PI + "'),1,0)"
#            , "Bm2CCKEta" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "eta'),1,0)"
#            , "Bm2CCKEtaP" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "eta_prime'),1,0)"
#            , "Bm2CCKPhi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "phi(1020)'),1,0)"
#            , "Bm2CCKOmega" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + "omega(782)'),1,0)"
#            , "Bm2CCKRho" : "switch(mcMatch('Beauty => " + CHARMONIUM + K + RHO + "'),1,0)"
#            , "Bm2CCK892" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + "'),1,0)"
#            , "Bm2CCK892Pi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + PI + "'),1,0)"
#            , "Bm2CCK892PiPi" : "switch(mcMatch('Beauty => " + CHARMONIUM + K892 + PI + PI + "'),1,0)"
#            , "Bm2CCK1270" : "switch(mcMatch('Beauty => " + CHARMONIUM + K1270 + "'),1,0)"
#            , "Bm2CCK1400" : "switch(mcMatch('Beauty => " + CHARMONIUM + K1400 + "'),1,0)"
#            
#            }
#        
#        JpsiRecTuple.BachMu.addTupleTool(LoKiTool,"BachMuMCTool")
#        JpsiRecTuple.BachMu.BachMuMCTool.Preambulo += [
#            "from LoKiCore.functions import *"
#            , "from LoKiPhysMC.decorators import *"
#            , "from PartProp.Nodes import CC"
#            , "IsAMu = mcMatch('[mu+]cc')"
#            , "IsAPi = mcMatch('[pi+]cc')"
#            , "IsAK = mcMatch('[K+]cc')"
#            , "Pi2Mu = mcMatch('[pi+ -> mu+ nu_mu ... ]CC')"
#            , "MuFromPi = mcMatch('[pi+ -> ^mu+ nu_mu ... ]CC')"
#            , "K2Mu = mcMatch('[K+ -> mu+ nu_mu ... ]CC')"
#            , "MuFromK = mcMatch('[K+ -> ^mu+ nu_mu ... ]CC')"
#            ]
#        JpsiRecTuple.BachMu.BachMuMCTool.Variables = {
#            "TrueMu" : "switch(IsAMu,1,0)"
#            , "TrueMu" : "switch(IsAPi,1,0)"
#            , "TrueMu" : "switch(IsAK,1,0)"
#            , "TruePi2Mu" : "switch(IsAPi & Pi2Mu,1,0)"
#            , "TrueMuFromPi" : "switch(IsAMu & MuFromPi,1,0)"
#            , "TrueK2Mu" : "switch(IsAK & Pi2Mu,1,0)"
 #           , "TrueMuFromK" : "switch(IsAMu & MuFromK,1,0)"
 #           }

