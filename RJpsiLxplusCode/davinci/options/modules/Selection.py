from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import CombineParticles

# DATA
MuonsLoc = 'Phys/StdLooseMuons/Particles'
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
MuonsSel = AutomaticData(Location = MuonsLoc)
JpsiSel = AutomaticData(Location = JpsiLoc)

# (BACHELOR) MUON FILTER
MyMuonAlg = FilterDesktop("MyMuonAlg")
MyMuonAlg.Code = "(ALL)"
#MyMuonAlg.Code += " & (TRCHI2DOF < 3)"
MyMuonSel = Selection("MyMuonSel", Algorithm = MyMuonAlg, RequiredSelections = [MuonsSel])

# JPSI FILTER
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

# BC -> JPSI MU
MyBcAlg = CombineParticles('MyBcAlg')
MyBcAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) mu+]cc'
MyBcAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBcAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBcAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyJpsiSel, MyMuonSel])
MyBcSeq = SelectionSequence("MyBcSeq",TopSelection=MyBcSel)

# This was Jack's old code for getting the rest fram variables

## from Configurables import MissMassTool, AddExtraInfo
## MissMassVars = AddExtraInfo( 'MissMassVars' )
## MissMassVars.Inputs = [ MyBcSeq.outputLocation() ]
## MMT = MissMassTool( 'MissMassVars.MissMassTool' )
## MissMassVars.addTool( MMT, 'MissMassVars.MissMassTool' )
## MissMassVars.Tools = [ 'MissMassTool/MissMassVars.MissMassTool' ]
## 
## MissMassFilter = FilterDesktop(
##     "MissMassFilter",
##     Code = "(INFO(1234567+0, 0.) > -5) & (INFO(1234567+0, 0.) < 15.0)"
##     )
## MissMassFilteredSel = Selection(
##     'MissMassFilteredSel',
##     Algorithm = MissMassFilter,
##     RequiredSelections = [MyBcSel]
##     )
## MissMassFilteredSeq = SelectionSequence(
##     'MissMassFilteredSeq',
##     TopSelection = MissMassFilteredSel
##     )
 
from Configurables import GaudiSequencer
SelectionSeq = GaudiSequencer("SelectionSeq")
## from Configurables import ReadHltReport
## finalsel = MissMassFilteredSeq.sequence()
## finalsel.Members += [ ReadHltReport() ]
## 
outputLocation = MyBcSeq.outputLocation()
from Refitter import getRefitter
refitter = getRefitter(outputLocation)

SelectionSeq.Members = [ MyBcSeq.sequence(), refitter ]
## SelectionSeq.Members = [ MyBcSeq.sequence(), MissMassVars, finalsel, refitter ]
