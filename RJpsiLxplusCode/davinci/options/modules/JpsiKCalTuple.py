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

def getJpsiKCalTuple(outputLocation):
    JpsiKCalTuple = DecayTreeTuple("JpsiKCalTuple")
    JpsiKCalTuple.Inputs = [ outputLocation ]
    JpsiKCalTuple.Decay = "[B+ -> ^(J/psi(1S) -> ^mu+ ^mu-) ^K+]CC"
    JpsiKCalTuple.addBranches({
        "B" : "[^(B+ -> (J/psi(1S) -> mu+ mu-) K+)]CC"
        , "Jpsi" : "[B+ -> ^(J/psi(1S) -> mu+ mu-) K+]CC"
        , "MuP" : "[B+ -> (J/psi(1S) -> ^mu+ mu-) K+]CC"
        , "MuM" : "[B+ -> (J/psi(1S) -> mu+ ^mu-) K+]CC"
        , "K" : "[B+ -> (J/psi(1S) -> mu+ mu-) ^K+]CC"
        })

    JpsiKCalTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    JpsiKCalTuple.addTupleTool(LoKiEvtTool,"LHETT")
    JpsiKCalTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    JpsiKCalTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        , "nPV" : "CONTAINS ('Rec/Vertex/Primary')"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = JpsiKCalTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    JpsiKCalTuple.K.addTupleTool("TupleToolMuonPid")
    JpsiKCalTuple.MuP.addTupleTool("TupleToolMuonPid")
    JpsiKCalTuple.MuM.addTupleTool("TupleToolMuonPid")    

    return JpsiKCalTuple
