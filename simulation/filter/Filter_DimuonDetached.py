'''
Filter option for Tracker-Only Bc->JpsiMuNu MC production,
based on StrippingFullDSTDiMuonJpsi2MuMuDetachedLine
'''

from Gaudi.Configuration import *
from Configurables import DaVinci, FilterDesktop, CombineParticles, OfflineVertexFitter
from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence, DataOnDemand
from Configurables import FilterDesktop
from Configurables import LoKiSvc


from CommonParticles.Utils import DefaultTrackingCuts
DefaultTrackingCuts().Cuts  = { "Chi2Cut" : [ 0, 5 ],
                                "CloneDistCut" : [5000, 9e+99 ] }

MessageSvc().Format = "% F%30W%S%7W%R%T %0W%M"

from Configurables import DaVinci
name = "DimuonDetached"

_stdMuons = DataOnDemand(Location = "Phys/StdAllNoPIDsMuons/Particles")
_muonFilter = FilterDesktop('muonFilter',
                    Preambulo = ["from LoKiMC.functions import *","from LoKiPhysMC.decorators import *","from LoKiPhysMC.functions import *"],
                    Code = "(mcMatch('[mu+]cc')) & (MCSELMATCH(MCNINANCESTORS(BEAUTY) > 0)) & (PT > 500 *MeV)")
MuonFilterSel = Selection(name = 'MuonFilterSel',
                          Algorithm = _muonFilter,
                          RequiredSelections = [ _stdMuons ])


_makeJpsi = CombineParticles("makeJpsi_" + name,
                DecayDescriptor = "J/psi(1S) -> mu+ mu-",
                CombinationCut = "(ADAMASS('J/psi(1S)') < 100 *MeV)",
                MotherCut = "(((BPVDLS>3) | (BPVDLS<-3))) & (VFASPF(VCHI2/VDOF) < 10.0)"
)
selJpsi = Selection ("SelJpsi",
                     Algorithm = _makeJpsi,
                     RequiredSelections = [MuonFilterSel])


seq = SelectionSequence("DimuonDetached.SafeStripTrig",
                          TopSelection = selJpsi)

#
# Configuration of SelDSTWriter
#
enablePacking = True

from DSTWriters.microdstelements import *
from DSTWriters.Configuration import (SelDSTWriter,
                                      stripDSTStreamConf,
                                      stripDSTElements
                                      )

SelDSTWriterElements = {
    'default'               : stripDSTElements(pack=enablePacking)
    }

SelDSTWriterConf = {
    'default'               : stripDSTStreamConf(pack=enablePacking)
    }

caloProtoReprocessLocs = [ "/Event/pRec/ProtoP#99", "/Event/pRec/Calo#99" ]
dstWriter = SelDSTWriter( "MyDSTWriter",
                          StreamConf = SelDSTWriterConf,
                          MicroDSTElements = SelDSTWriterElements,
                          OutputFileSuffix ='Filtered',
                          SelectionSequences = [seq]
                          )
SelDSTWriterConf['default'].extraItems += caloProtoReprocessLocs

#
# DaVinci Configuration
#
from Configurables import DaVinci
DaVinci().Simulation = True
DaVinci().EvtMax = -1
DaVinci().HistogramFile = "DVHistos.root"
DaVinci().TupleFile = "DTuple.root"

DaVinci().appendToMainSequence( [ seq.sequence() ] )
DaVinci().appendToMainSequence( [ dstWriter.sequence() ] )
