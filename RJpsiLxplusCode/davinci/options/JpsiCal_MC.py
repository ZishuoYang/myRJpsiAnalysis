######################################################################
# CALIBRATION J/PSI -> MU MU
#
# @author Jack Wimberley
# @date 2014-06-24
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *
from Configurables import GaudiSequencer

# -------
# DATA
# -------

JpsiLine = "MuIDCalib_JpsiFromBNoPIDNoMip"
JpsiLoc = "/Event/AllStreams/Phys/" + JpsiLine + "/Particles"

# -------
# OPTIONS
# -------

MessageSvc().OutputLevel = WARNING
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "Jpsi_MuID_histos.root"
DaVinci().TupleFile = "Jpsi_MuID.root"

doing2011 = False
from Configurables import CondDB
if (doing2011):
    DaVinci().DataType = "2011"
    CondDB().UseLatestTags = ["2011"]
else:
    DaVinci().DataType = "2012"
    CondDB().UseLatestTags = ["2012"]

# -----------
# MuID FILTER
# -----------

from PhysConf.Filters import LoKi_Filters
Filt = LoKi_Filters(
    STRIP_Code = "HLT_PASS_RE( 'Stripping" + JpsiLine + "Decision' )"
    )
DaVinci().EventPreFilters = Filt.filters("Filters")

# ----------
# JPSI TUPLE
# ----------

from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *
tuple = DecayTreeTuple("DecayTree")
tuple.Inputs = [JpsiLoc]
tuple.Decay = "J/psi(1S) -> ^mu+ ^mu-"
tuple.ToolList = [
    "TupleToolGeometry"
    , "TupleToolKinematic"
    , "TupleToolPid"
    , "TupleToolTrackInfo" # only need for TRCHI2NDOF; I'm leaving in cut for now
    , "TupleToolEventInfo"
    , "TupleToolMuonPid"
    , "TupleToolMCBackgroundInfo"
    ]

# TUPLETOOLTISTOS
#from Configurables import TupleToolTISTOS
#TisTos = JpsiRecTuple.Jpsi.addTupleTool("TupleToolTISTOS/TisTos")
#TisTos.Verbose = True
#TisTos.TriggerList = triggers

from Configurables import TupleToolPIDCalib
_l0TisTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTisL0Criterion')
_hlt1TisTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTisHlt1Criterion')
_hlt2TisTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTisHlt2Criterion')

_l0TosTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTosL0Criterion')
_hlt1TosTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTosHlt1Criterion')
_hlt2TosTagCrit = TupleToolPIDCalib.getDefaultProperty('MuonTosHlt2Criterion')


def L0TIS(code):
    return "TIS('{0}', 'L0TriggerTisTos')".format(code)
def L0TOS(code):
    return "TOS('{0}', 'L0TriggerTisTos')".format(code)
def Hlt1TIS(code):
    return "TIS('{0}', 'Hlt1TriggerTisTos')".format(code)
def Hlt1TOS(code):
    return "TOS('{0}', 'Hlt1TriggerTisTos')".format(code)
def Hlt2TIS(code):
    return "TIS('{0}', 'Hlt2TriggerTisTos')".format(code)
def Hlt2TOS(code):
    return "TOS('{0}', 'Hlt2TriggerTisTos')".format(code)

MuonTisTagged = ("switch(({l0}) & ({hlt1}) & ({hlt2}),1,0)").format(
    l0 = L0TIS(_l0TisTagCrit),
    hlt1 = Hlt1TIS(_hlt1TisTagCrit),
    hlt2 = Hlt2TIS(_hlt2TisTagCrit))

MuonTosTagged = ("switch(({l0}) & ({hlt1}) & ({hlt2}),1,0)").format(
    l0 = L0TOS(_l0TosTagCrit),
    hlt1 = Hlt1TOS(_hlt1TosTagCrit),
    hlt2 = Hlt2TOS(_hlt2TosTagCrit))

from Configurables import LoKi__Hybrid__TupleTool as LoKiTool
MuonTisTosTags = tuple.addTupleTool(LoKiTool,"MuonTisTosTags")
MuonTisTosTags.Preambulo += [
    "from LoKiCore.functions import *"
    , "from LoKiHlt.decorators import *"
    ]
MuonTisTosTags.Variables = {
    "IsTis" : MuonTisTagged
    , "IsTos" : MuonTosTagged    
    }

truth = tuple.addTupleTool("TupleToolMCTruth")
truth.ToolList = [
    "MCTupleToolKinematic"
    , "MCTupleToolHierarchy"
    ]

DaVinci().appendToMainSequence( [ tuple ] )
