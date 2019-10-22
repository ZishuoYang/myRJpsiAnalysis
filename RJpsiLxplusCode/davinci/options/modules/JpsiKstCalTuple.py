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
    ]

def getJpsiKstCalTuple(simulation,outputLocation):
    JpsiKstCalTuple = DecayTreeTuple("JpsiKstCalTuple")
    JpsiKstCalTuple.Inputs = [ outputLocation ]
    JpsiKstCalTuple.Decay = "[B0 -> ^(J/psi(1S) -> ^mu+ ^mu-) ^(K*(892)0 -> ^K+ ^pi-)]CC"
    JpsiKstCalTuple.addBranches({
        "B" : "[^(B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-))]CC"
        , "Jpsi" : "[B0 -> ^(J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ pi-)]CC"
        , "MuP" : "[B0 -> (J/psi(1S) -> ^mu+ mu-) (K*(892)0 -> K+ pi-)]CC"
        , "MuM" : "[B0 -> (J/psi(1S) -> mu+ ^mu-) (K*(892)0 -> K+ pi-)]CC"
        , "Kst" : "[B0 -> (J/psi(1S) -> mu+ mu-) ^(K*(892)0 -> K+ pi-)]CC"
        , "K" : "[B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> ^K+ pi-)]CC"
        , "Pi" : "[B0 -> (J/psi(1S) -> mu+ mu-) (K*(892)0 -> K+ ^pi-)]CC"
        })

    JpsiKstCalTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    JpsiKstCalTuple.addTupleTool(LoKiEvtTool,"LHETT")
    JpsiKstCalTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    JpsiKstCalTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        , "nPV" : "CONTAINS ('Rec/Vertex/Primary')"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = JpsiKstCalTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    JpsiKstCalTuple.K.addTupleTool("TupleToolMuonPid")
    JpsiKstCalTuple.Pi.addTupleTool("TupleToolMuonPid")
    JpsiKstCalTuple.MuP.addTupleTool("TupleToolMuonPid")
    JpsiKstCalTuple.MuM.addTupleTool("TupleToolMuonPid")    

    
    # MC INFO
    if (simulation):
        truth = JpsiKstCalTuple.addTupleTool("TupleToolMCTruth")
        truth.ToolList = [
            "MCTupleToolKinematic"
            , "MCTupleToolHierarchy"
            ]
        
        # TUPLETOOLMCBACKGROUNDINFO
        from Configurables import TupleToolMCBackgroundInfo
        BTTMCBI = JpsiKstCalTuple.B.addTupleTool("TupleToolMCBackgroundInfo/BTTMCBI")
        JpsiTTMCBI = JpsiKstCalTuple.Jpsi.addTupleTool("TupleToolMCBackgroundInfo/JpsiTTMCBI")
        KstTTMCBI = JpsiKstCalTuple.Kst.addTupleTool("TupleToolMCBackgroundInfo/KstTTMCBI")
        
    return JpsiKstCalTuple
