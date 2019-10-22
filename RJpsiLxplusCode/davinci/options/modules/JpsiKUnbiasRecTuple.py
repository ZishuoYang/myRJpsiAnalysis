from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *
from Configurables import TupleToolTrigger
from Configurables import TupleToolStripping

triggers = [
    "L0MuonDecision"
    , "L0DiMuonDecision"
    , "Hlt1DiMuonHighMassDecision"
    , "Hlt1DiMuonLowMassDecision"
    , "Hlt2DiMuonJPsiHighPTDecision"
    , "Hlt2DiMuonDetachedJPsiDecision"
    , "Hlt2DiMuonDetachedHeavyDecision"
    ]

def getJpsiKUnbiasRecTuple(simulation,outputLocation):
    JpsiKUnbiasRecTuple = DecayTreeTuple("JpsiKUnbiasRecTuple")
    JpsiKUnbiasRecTuple.Inputs = [ outputLocation ]
    JpsiKUnbiasRecTuple.Decay = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+]CC"
    JpsiKUnbiasRecTuple.addBranches({
        "B" : "[^(B+ -> (J/psi(1S) -> mu+ mu-) K+)]CC"
        , "Jpsi" : "[B+ -> ^(J/psi(1S) -> mu+ mu-) K+]CC"
        , "MuP" : "[B+ -> (J/psi(1S) -> ^mu+ mu-) K+]CC"
        , "MuM" : "[B+ -> (J/psi(1S) -> mu+ ^mu-) K+]CC"
        , "Kaon" : "[B+ -> (J/psi(1S) -> mu+ mu-) ^K+]CC"
        })

    JpsiKUnbiasRecTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPropertime"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # ISOLATION
    from Configurables import TupleToolApplyIsolation
    JpsiKUnbiasRecTuple.B.addTool(TupleToolApplyIsolation, name="TupleToolApplyIsolationSoft")
    JpsiKUnbiasRecTuple.B.TupleToolApplyIsolationSoft.WeightsFile="weightsSoft.xml"
    JpsiKUnbiasRecTuple.B.ToolList+=["TupleToolApplyIsolation/TupleToolApplyIsolationSoft"]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    JpsiKUnbiasRecTuple.addTupleTool(LoKiEvtTool,"LHETT")
    JpsiKUnbiasRecTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    JpsiKUnbiasRecTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        }

    # J/psi and Mu DOCA
    from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
    JpsiKUnbiasRecTuple.B.addTupleTool(LoKiTool,"DocaTool")
    JpsiKUnbiasRecTuple.B.DocaTool.Preambulo += [
        "PFUNA = LoKi.Particles.PFunA"
        , "from LoKiCore.functions import *"
        ]
    JpsiKUnbiasRecTuple.B.DocaTool.Variables = {
        "DOCA" : "PFUNA(AMINDOCA(''))"
        , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = JpsiKUnbiasRecTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    # No sense attaching Muon PID tool to a pion, is there?
    JpsiKUnbiasRecTuple.MuP.addTupleTool("TupleToolMuonPid")
    JpsiKUnbiasRecTuple.MuM.addTupleTool("TupleToolMuonPid")    


    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    KaonTTTI = JpsiKUnbiasRecTuple.Kaon.addTupleTool("TupleToolTrackIsolation/KaonTTTI")
    KaonTTTI.MinConeAngle = 0.1
    KaonTTTI.MaxConeAngle = 0.5
    KaonTTTI.StepSize = 0.2

    MuPTTTI = JpsiKUnbiasRecTuple.MuP.addTupleTool("TupleToolTrackIsolation/MuPTTTI")
    MuPTTTI.MinConeAngle = 0.1
    MuPTTTI.MaxConeAngle = 0.5
    MuPTTTI.StepSize = 0.2

    MuMTTTI = JpsiKUnbiasRecTuple.MuM.addTupleTool("TupleToolTrackIsolation/MuMTTTI")
    MuMTTTI.MinConeAngle = 0.1
    MuMTTTI.MaxConeAngle = 0.5
    MuMTTTI.StepSize = 0.2

    # VERTEX ISOLATION
    from Configurables import TupleToolVtxIsoln
    BTTVI = JpsiKUnbiasRecTuple.B.addTupleTool("TupleToolVtxIsoln/BTTVI")
    
    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    BachMuTTTI = JpsiKUnbiasRecTuple.Kaon.addTupleTool("TupleToolTrackIsolation/BachMuTTTI")
    BachMuTTTI.FillAsymmetry = True
    BachMuTTTI.MinConeAngle = 0.5
    BachMuTTTI.MaxConeAngle = 0.5
    BachMuTTTI.StepSize = 0.1

    # MC INFO
    if (simulation):
        truth = JpsiKUnbiasRecTuple.addTupleTool("TupleToolMCTruth")
        truth.ToolList = [
            "MCTupleToolKinematic"
            , "MCTupleToolHierarchy"
            ]
        
        # TUPLETOOLMCBACKGROUNDINFO
        from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
        BTTMCBI = JpsiKUnbiasRecTuple.B.addTupleTool("TupleToolMCBackgroundInfo/BTTMCBI")
        BTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
        BTTMCBI.BackgroundCategory.SemileptonicDecay = True
        BTTMCBI.BackgroundCategory.NumNeutrinos = 3
        JpsiTTMCBI = JpsiKUnbiasRecTuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")
        
    return JpsiKUnbiasRecTuple
