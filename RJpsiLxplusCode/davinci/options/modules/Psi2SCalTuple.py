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

def getPsi2SCalTuple(outputLocation):
    Psi2SCalTuple = DecayTreeTuple("Psi2SCalTuple")
    Psi2SCalTuple.Inputs = [ outputLocation ]
    Psi2SCalTuple.Decay = "psi(2S) -> ^(J/psi(1S) -> ^mu+ ^mu-) ^pi+ pi-"
    Psi2SCalTuple.addBranches({
        "Psi" : "^(psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ pi-)"
        , "Jpsi" : "psi(2S) -> ^(J/psi(1S) -> mu+ mu-) pi+ pi-"
        , "MuP" : "psi(2S) -> (J/psi(1S) -> ^mu+ mu-) pi+ pi-"
        , "MuM" : "psi(2S) -> (J/psi(1S) -> mu+ ^mu-) pi+ pi-"
        , "PiP" : "psi(2S) -> (J/psi(1S) -> mu+ mu-) ^pi+ pi-"
        , "PiM" : "psi(2S) -> (J/psi(1S) -> mu+ mu-) pi+ ^pi-"
        })

    Psi2SCalTuple.ToolList = [
        "TupleToolGeometry"
        , "TupleToolKinematic"
        , "TupleToolPid"
        , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
        , "TupleToolEventInfo"
        , "TupleToolPrimaries"
        ]

    # NUMBER OF REC/TRACKS/BEST
    from Configurables import LoKi__Hybrid__EvtTupleTool as LoKiEvtTool
    Psi2SCalTuple.addTupleTool(LoKiEvtTool,"LHETT")
    Psi2SCalTuple.LHETT.Preambulo += [ "from LoKiCore.functions import *" ]
    Psi2SCalTuple.LHETT.VOID_Variables = {
        "nTracks" : "CONTAINS ('Rec/Track/Best')"
        , "SPDhits" : "CONTAINS ('Raw/Spd/Digits')"
        , "nPV" : "CONTAINS ('Rec/Vertex/Primary')"
        }

    # TUPLETOOLTISTOS
    from Configurables import TupleToolTISTOS
    TisTos = Psi2SCalTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
    TisTos.Verbose = True
    TisTos.TriggerList = triggers

    # MUON PID INFORMATION
    Psi2SCalTuple.PiP.addTupleTool("TupleToolMuonPid")
    Psi2SCalTuple.PiM.addTupleTool("TupleToolMuonPid")
    Psi2SCalTuple.MuP.addTupleTool("TupleToolMuonPid")
    Psi2SCalTuple.MuM.addTupleTool("TupleToolMuonPid")    

    return Psi2SCalTuple
