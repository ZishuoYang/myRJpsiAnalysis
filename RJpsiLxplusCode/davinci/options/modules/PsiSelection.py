from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import CombineParticles

# DATA
AllMuonsLoc = 'Phys/StdAllLooseMuons/Particles'
MuonsLoc = 'Phys/StdLooseMuons/Particles'
AllMuonsSel = AutomaticData(Location = AllMuonsLoc)
MuonsSel = AutomaticData(Location = MuonsLoc)

# (BACHELOR) MUON FILTER
MyMuonAlg = FilterDesktop("MyMuonAlg")
MyMuonAlg.Code = "(ALL)"
#MyMuonAlg.Code += " & (TRCHI2DOF < 3)"
MyMuonSel = Selection("MyMuonSel", Algorithm = MyMuonAlg, RequiredSelections = [MuonsSel])

# PSI COMBINER
MyPsiAlg = CombineParticles("MyPsiAlg")
MyPsiAlg.DecayDescriptor = 'psi(2S) -> mu+ mu-'
MyPsiAlg.DaughtersCuts = {}
MyPsiAlg.CombinationCut = "(ADAMASS('psi(2S)')<100.*MeV) & (ADOCACHI2CUT(30,''))"
MyPsiAlg.MotherCut = "(VFASPF(VCHI2) < 25.)"
MyPsiAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyPsiSel = Selection("MyPsiSel", Algorithm = MyPsiAlg, RequiredSelections = [AllMuonsSel])

# BC -> PSI MU
MyBcAlg = CombineParticles('MyBcAlg')
MyBcAlg.DecayDescriptor = '[B_c+ -> psi(2S) mu+]cc'
MyBcAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBcAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBcAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBcSel = Selection("MyBcSel", Algorithm = MyBcAlg, RequiredSelections = [MyPsiSel, MyMuonSel])
MyBcSeq = SelectionSequence("MyBcSeq",TopSelection=MyBcSel)

from Configurables import MissMassTool, AddExtraInfo
MissMassVars = AddExtraInfo( 'MissMassVars' )
MissMassVars.Inputs = [ MyBcSeq.outputLocation() ]
MMT = MissMassTool( 'MissMassVars.MissMassTool' )
MissMassVars.addTool( MMT, 'MissMassVars.MissMassTool' )
MissMassVars.Tools = [ 'MissMassTool/MissMassVars.MissMassTool' ]

MissMassFilter = FilterDesktop(
    "MissMassFilter",
    Code = "(INFO(1234567+0, 0.) > -5) & (INFO(1234567+0, 0.) < 15.0)"
    )
MissMassFilteredSel = Selection(
    'MissMassFilteredSel',
    Algorithm = MissMassFilter,
    RequiredSelections = [MyBcSel]
    )
MissMassFilteredSeq = SelectionSequence(
    'MissMassFilteredSeq',
    TopSelection = MissMassFilteredSel
    )

from Configurables import GaudiSequencer
SelectionSeq = GaudiSequencer("SelectionSeq")
from Configurables import ReadHltReport
finalsel = MissMassFilteredSeq.sequence()
finalsel.Members += [ ReadHltReport() ]

outputLocation = MissMassFilteredSeq.outputLocation()
from Refitter import getPsi2SRefitter
refitter = getPsi2SRefitter(outputLocation)

SelectionSeq.Members = [ MyBcSeq.sequence(), MissMassVars, finalsel, refitter ]
