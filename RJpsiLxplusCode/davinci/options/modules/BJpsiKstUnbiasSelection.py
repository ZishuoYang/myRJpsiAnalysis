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

# B -> JPSI K
MyBJpsiKUnbiasAlg = CombineParticles('MyBJpsiKUnbiasAlg')
MyBJpsiKUnbiasAlg.DecayDescriptor = '[B+ -> J/psi(1S) K+]cc'
MyBJpsiKUnbiasAlg.DaughtersCuts = { "K+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBJpsiKUnbiasAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBJpsiKUnbiasAlg.CombinationCut += " & (ADAMASS('B+') < 1*GeV)"
MyBJpsiKUnbiasAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBJpsiKUnbiasAlg.MotherCut += " & (ADMASS('B+') < 0.3*GeV)"
MyBJpsiKUnbiasAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBJpsiKUnbiasSel = Selection("MyBJpsiKUnbiasSel", Algorithm = MyBJpsiKUnbiasAlg, RequiredSelections = [MyJpsiSel, MyKaonSel])

# B -> JPSI K
MyBJpsiKUnbiasAlg = CombineParticles('MyBJpsiKUnbiasAlg')
MyBJpsiKUnbiasAlg.DecayDescriptor = '[B+ -> J/psi(1S) K+]cc'
MyBJpsiKUnbiasAlg.DaughtersCuts = { "K+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBJpsiKUnbiasAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBJpsiKUnbiasAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBJpsiKUnbiasAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBJpsiKUnbiasSel = Selection("MyBJpsiKUnbiasSel", Algorithm = MyBJpsiKUnbiasAlg, RequiredSelections = [MyJpsiSel, MyKaonSel])

# B -> JPSI KST
MyBJpsiKstUnbiasAlg = CombineParticles('MyBJpsiKstUnbiasAlg')
MyBJpsiKstUnbiasAlg.DecayDescriptor = '[B0 -> (B+ -> J/psi(1S) K+) pi-]cc'
MyBJpsiKstUnbiasAlg.DaughtersCuts = { "pi-" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyBJpsiKstUnbiasAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBJpsiKstUnbiasAlg.CombinationCut += " & (dump1(MASS(5,6)) > 592*MeV) & (MASS(5,6) < 1192*MeV)"
MyBJpsiKstUnbiasAlg.CombinationCut += " & (ADAMASS('B0') < 1*GeV)"
MyBJpsiKstUnbiasAlg.MotherCut = " (ADMASS('B0') < 0.3*GeV)"
MyBJpsiKstUnbiasAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBJpsiKstUnbiasSel = Selection("MyBJpsiKstUnbiasSel", Algorithm = MyBJpsiKstUnbiasAlg, RequiredSelections = [MyJpsiSel, MyKstSel])
MyBJpsiKstUnbiasSeq = SelectionSequence("MyBJpsiKstUnbiasSeq", TopSelection = MyBJpsiKstUnbiasSel)

