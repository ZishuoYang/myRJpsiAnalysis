########################################################################
# Jpsi -> E E
#
# @author Jack Wimberley
# @date 17-04-2013
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *


# OPTIONS
MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = 1000
DaVinci().PrintFreq = 1000
DaVinci().HistogramFile = "Jpsi2EE_histos.root"
DaVinci().TupleFile = "Jpsi2EE.root"

DaVinci().DataType = "2012"
from Configurables import CondDB
CondDB().UseLatestTags  = ["2012"]

ElectronsLoc = 'Phys/StdLooseElectrons/Particles'
ANNElectronsLoc = 'Phys/StdLooseANNElectrons/Particles'
JpsiEELoc = 'Phys/StdLooseJpsi2ee/Particles'

# FILTER
from PhysConf.Filters import LoKi_Filters
filt = LoKi_Filters( VOID_Code = "CONTAINS('Phys/StdLooseJpsi2ee/Particles')>1")
filtseq = filt.sequence('MyFilter')
DaVinci().EventPreFilters = [filtseq]

# DATA
from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import CombineParticles

ElectronsSel = AutomaticData(Location = ElectronsLoc)
JpsiEESel = AutomaticData(Location = JpsiEELoc)

# CUTS
from Configurables import CombineParticles
_AlgJpsi2EE = CombineParticles('AlgJpsi2EE')
_AlgJpsi2EE.DecayDescriptor = 'J/psi(1S) -> e+ e-'
_AlgJpsi2EE.DaughtersCuts = { "e+" : "(PT > 0.25*GeV) & (TRCHI2DOF < 4) & (PIDe-PIDpi > 0)",
                              "e+" : "(PT > 0.25*GeV) & (TRCHI2DOF < 4) & (PIDe-PIDpi > 0)"}
_AlgJpsi2EE.CombinationCut = "(ADAMASS('J/psi(1S)') < 400*MeV)"
_AlgJpsi2EE.CombinationCut += " & (ADOCACHI2CUT(20,''))"
_AlgJpsi2EE.MotherCut = "(ADMASS('J/psi(1S)') < 200*MeV)"
_AlgJpsi2EE.MotherCut += " & (VFASPF(VPCHI2) > 0.001)"

#JpsiSel = Selection("JpsiSel",
#                    Algorithm = _AlgJpsi2EE,
#                    RequiredSelections = [ElectronsSel])
JpsiSeq = SelectionSequence("JpsiSeq",
                            TopSelection = JpsiEESel)
DaVinci().appendToMainSequence( [ JpsiSeq.sequence() ] )

# PRE MONITOR
from Configurables import MassBiasesMonitor
premon = MassBiasesMonitor('PREMON',
                           InputLocation = JpsiSeq.outputLocation(),
                           MinMass = 3*GeV, MaxMass = 3.190*GeV,
                           MaxMom = 160*GeV, ThreshMom = 10.49*GeV, RiseMom = 0.0432/GeV, FallMom = 0.0279/GeV, BinsMom = 15,
                           # MaxMom = 160*GeV, ThreshMom = 15.15*GeV, RiseMom = 0.0663/GeV, FallMom = 0.0242/GeV, BinsMom = 15, # loose
                           MaxPt = 10*GeV, ThreshPt = 0.0558*GeV, RisePt = 0.0426/GeV, FallPt = 0.616/GeV, BinsPt = 15,
                           # MaxPt = 10*GeV, ThreshPt = 0.032*GeV, RisePt = 0.0733/GeV, FallPt = 0.55/GeV, BinsPt = 20, # loose
                           MaxMomDif = 100*GeV, FallMomDif = 0.0423/GeV, BinsMomDif = 10,
                           # MaxMomDif = 80*GeV, FallMomDif = 0.046/GeV, BinsMomDif = 10, # loose
                           PowMomAsym = 4, BinsMomAsym = 15,
                           MinEta = 1, MaxEta = 10, KEta = 28, FallEta = 7.5, BinsEta = 20,
                           MaxTx = 0.2, FallTx = 22.4, BinsTx = 10,
                           # MaxTx = 0.2, FallTx = 25.2, BinsTx = 10, # loose
                           MaxTy = 0.2, FallTy = 22.4, BinsTy = 10,
                           # MaxTy = 0.2, FallTy = 25.2, BinsTy = 10, # loose
                           MinOpenAngle = 0, MaxOpenAngle = 0.5, KOpenAngle = 2, FallOpenAngle = 21, BinsOpenAngle = 20)
# MinOpenAngle = 0, MaxOpenAngle = 0.3, KOpenAngle = 1.7, FallOpenAngle = 26.6, BinsOpenAngle = 20) # loose


# REFITTER
from DaVinciTrackRefitting.ParticleRefitter import ParticleRefitterSeq
updater = ParticleRefitterSeq(inputs=[ JpsiSeq.outputLocation() ], scale = True)

# POST MONITOR
postmon = MassBiasesMonitor('POSTMON',
                            InputLocation = JpsiSeq.outputLocation(),
                            MinMass = 3*GeV, MaxMass = 3.190*GeV,
                            MaxMom = 160*GeV, ThreshMom = 10.49*GeV, RiseMom = 0.0432/GeV, FallMom = 0.0279/GeV, BinsMom = 15,
                            # MaxMom = 160*GeV, ThreshMom = 15.15*GeV, RiseMom = 0.0663/GeV, FallMom = 0.0242/GeV, BinsMom = 15, # loose
                            MaxPt = 10*GeV, ThreshPt = 0.0558*GeV, RisePt = 0.0426/GeV, FallPt = 0.616/GeV, BinsPt = 15,
                            # MaxPt = 10*GeV, ThreshPt = 0.032*GeV, RisePt = 0.0733/GeV, FallPt = 0.55/GeV, BinsPt = 20, # loose
                            MaxMomDif = 100*GeV, FallMomDif = 0.0423/GeV, BinsMomDif = 10,
                            # MaxMomDif = 80*GeV, FallMomDif = 0.046/GeV, BinsMomDif = 10, # loose
                            PowMomAsym = 4, BinsMomAsym = 15,
                            MinEta = 1, MaxEta = 10, KEta = 28, FallEta = 7.5, BinsEta = 20,
                            MaxTx = 0.2, FallTx = 22.4, BinsTx = 10,
                            # MaxTx = 0.2, FallTx = 25.2, BinsTx = 10, # loose
                            MaxTy = 0.2, FallTy = 22.4, BinsTy = 10,
                            # MaxTy = 0.2, FallTy = 25.2, BinsTy = 10, # loose
                            MinOpenAngle = 0, MaxOpenAngle = 0.5, KOpenAngle = 2, FallOpenAngle = 21, BinsOpenAngle = 20)
# MinOpenAngle = 0, MaxOpenAngle = 0.3, KOpenAngle = 1.7, FallOpenAngle = 26.6, BinsOpenAngle = 20) # loose

# SEQUENCES
from Configurables import GaudiSequencer
preseq = GaudiSequencer('preseq')
preseq.Members = [ premon ]
postseq = GaudiSequencer('postseq')
postseq.Members = [ updater, postmon ]
DaVinci().appendToMainSequence( [ preseq, postseq ] )
