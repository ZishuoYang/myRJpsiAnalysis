from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import CombineParticles

KaonsLoc = 'Phys/StdLooseKaons/Particles'
KaonsSel = AutomaticData(Location = KaonsLoc)
JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
JpsiSel = AutomaticData(Location = JpsiLoc)

# PION FILTER
MyKaonAlg = FilterDesktop("MyKaonAlg")
MyKaonAlg.Code = "(ALL)"
MyKaonSel = Selection("MyKaonSel", Algorithm = MyKaonAlg, RequiredSelections = [KaonsSel])

# JPSI FILTER
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

# BC -> JPSI K
MyBJpsiKUnbiasAlg = CombineParticles('MyBJpsiKUnbiasAlg')
MyBJpsiKUnbiasAlg.DecayDescriptor = '[B+ -> J/psi(1S) K+]cc'
MyBJpsiKUnbiasAlg.DaughtersCuts = { "K+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBJpsiKUnbiasAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBJpsiKUnbiasAlg.CombinationCut += " & (ADAMASS('B+') < 1*GeV)"
MyBJpsiKUnbiasAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBJpsiKUnbiasAlg.MotherCut += " & (ADMASS('B+') < 0.3*GeV)"
MyBJpsiKUnbiasAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBJpsiKUnbiasSel = Selection("MyBJpsiKUnbiasSel", Algorithm = MyBJpsiKUnbiasAlg, RequiredSelections = [MyJpsiSel, MyKaonSel])
MyBJpsiKUnbiasSeq = SelectionSequence("MyBJpsiKUnbiasSeq", TopSelection = MyBJpsiKUnbiasSel)

