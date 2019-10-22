from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import CombineParticles

PionsLoc = 'Phys/StdLoosePions/Particles'
PionsSel = AutomaticData(Location = PionsLoc)
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
JpsiSel = AutomaticData(Location = JpsiLoc)

# PION FILTER
MyPionAlg = FilterDesktop("MyPionAlg")
MyPionAlg.Code = "(ALL)"
MyPionSel = Selection("MyPionSel", Algorithm = MyPionAlg, RequiredSelections = [PionsSel])

# JPSI FILTER
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

# BC -> JPSI PI
MyBcJpsiPiAlg = CombineParticles('MyBcJpsiPiAlg')
MyBcJpsiPiAlg.DecayDescriptor = '[B_c+ -> J/psi(1S) pi+]cc'
MyBcJpsiPiAlg.DaughtersCuts = { "pi+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBcJpsiPiAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBcJpsiPiAlg.CombinationCut += " & (ADAMASS('B_c+') < 1*GeV)"
MyBcJpsiPiAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBcJpsiPiAlg.MotherCut += " & (ADMASS('B_c+') < 0.3*GeV)"
MyBcJpsiPiAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBcJpsiPiSel = Selection("MyBcJpsiPiSel", Algorithm = MyBcJpsiPiAlg, RequiredSelections = [MyJpsiSel, MyPionSel])
MyBcJpsiPiSeq = SelectionSequence("MyBcJpsiPiSeq", TopSelection = MyBcJpsiPiSel)

