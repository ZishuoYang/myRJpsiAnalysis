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

def getJpsiPiRecTuple(simulation,outputLocation):
    JpsiPiRecTuple = DecayTreeTuple("JpsiPiRecTuple")
    JpsiPiRecTuple.Inputs = [ outputLocation ]
    JpsiPiRecTuple.Decay = "[B_c+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^pi+]CC"
    JpsiPiRecTuple.addBranches({
        "Bc" : "[^(B_c+ -> (J/psi(1S) -> mu+ mu-) pi+)]CC"
        , "Jpsi" : "[B_c+ -> ^(J/psi(1S) -> mu+ mu-) pi+]CC"
        , "MuP" : "[B_c+ -> (J/psi(1S) -> ^mu+ mu-) pi+]CC"
        , "MuM" : "[B_c+ -> (J/psi(1S) -> mu+ ^mu-) pi+]CC"
        , "Pion" : "[B_c+ -> (J/psi(1S) -> mu+ mu-) ^pi+]CC"
        })

    JpsiPiRecTuple.ToolList = [
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
    JpsiPiRecTuple.addTupleTool(LoKiEvtTool,"LHETT")
    JpsiPiRecTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    JpsiPiRecTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        }

    # J/psi and Mu DOCA
    from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
    JpsiPiRecTuple.Bc.addTupleTool(LoKiTool,"DocaTool")
    JpsiPiRecTuple.Bc.DocaTool.Preambulo += [
        "PFUNA = LoKi.Particles.PFunA"
        , "from LoKiCore.functions import *"
        ]
    JpsiPiRecTuple.Bc.DocaTool.Variables = {
        "DOCA" : "PFUNA(AMINDOCA(''))"
        , "DOCACHI2" : "PFUNA(ADOCACHI2(''))"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = JpsiPiRecTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    # No sense attaching Muon PID tool to a pion, is there?
    JpsiPiRecTuple.MuP.addTupleTool("TupleToolMuonPid")
    JpsiPiRecTuple.MuM.addTupleTool("TupleToolMuonPid")    


    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    PionTTTI = JpsiPiRecTuple.Pion.addTupleTool("TupleToolTrackIsolation/PionTTTI")
    PionTTTI.MinConeAngle = 0.1
    PionTTTI.MaxConeAngle = 0.5
    PionTTTI.StepSize = 0.2

    MuPTTTI = JpsiPiRecTuple.MuP.addTupleTool("TupleToolTrackIsolation/MuPTTTI")
    MuPTTTI.MinConeAngle = 0.1
    MuPTTTI.MaxConeAngle = 0.5
    MuPTTTI.StepSize = 0.2

    MuMTTTI = JpsiPiRecTuple.MuM.addTupleTool("TupleToolTrackIsolation/MuMTTTI")
    MuMTTTI.MinConeAngle = 0.1
    MuMTTTI.MaxConeAngle = 0.5
    MuMTTTI.StepSize = 0.2

    # VERTEX ISOLATION
    from Configurables import TupleToolVtxIsoln
    BcTTVI = JpsiPiRecTuple.Bc.addTupleTool("TupleToolVtxIsoln/BcTTVI")
    
    # TRACK ISOLATION
    from Configurables import TupleToolTrackIsolation
    BachMuTTTI = JpsiPiRecTuple.Pion.addTupleTool("TupleToolTrackIsolation/BachMuTTTI")
    BachMuTTTI.FillAsymmetry = True
    BachMuTTTI.MinConeAngle = 0.5
    BachMuTTTI.MaxConeAngle = 0.5
    BachMuTTTI.StepSize = 0.1

    # MC INFO
    if (simulation):
        truth = JpsiPiRecTuple.addTupleTool("TupleToolMCTruth")
        truth.ToolList = [
            "MCTupleToolKinematic"
            , "MCTupleToolHierarchy"
            ]
        
        # TUPLETOOLMCBACKGROUNDINFO
        from Configurables import TupleToolMCBackgroundInfo, BackgroundCategory
        BcTTMCBI = JpsiPiRecTuple.Bc.addTupleTool("TupleToolMCBackgroundInfo/BcTTMCBI")
        BcTTMCBI.addTool(BackgroundCategory,name="BackgroundCategory")
        BcTTMCBI.BackgroundCategory.SemileptonicDecay = True
        BcTTMCBI.BackgroundCategory.NumNeutrinos = 3
        JpsiTTMCBI = JpsiPiRecTuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")
        
    return JpsiPiRecTuple
