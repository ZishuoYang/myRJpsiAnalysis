from PhysSelPython.Wrappers import AutomaticData, Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import CombineParticles

JpsiLoc = 'Phys/StdLooseJpsi2MuMu/Particles'
KaonCalLoc = 'Phys/StdNoPIDsKaons/Particles'
PionCalLoc = 'Phys/StdNoPIDsPions/Particles'
JpsiSel = AutomaticData(Location = JpsiLoc)
KaonCalSel = AutomaticData(Location = KaonCalLoc)
PionCalSel = AutomaticData(Location = PionCalLoc)

# JPSI FILTER
MyJpsiAlg = FilterDesktop("MyJpsiAlg")
MyJpsiAlg.Code = "(PT > 2*GeV)"
#MyJpsiAlg.Code += " & (MAXTREE('mu+'==ABSID,TRCHI2DOF) < 3)"
MyJpsiSel = Selection("MyJpsiSel", Algorithm = MyJpsiAlg, RequiredSelections = [JpsiSel])

# KAON FILTER
MyKaonCalAlg = FilterDesktop("MyKaonCalAlg")
MyKaonCalAlg.Code = "(ALL)"
MyKaonCalSel = Selection("MyKaonCalSel", Algorithm = MyKaonCalAlg, RequiredSelections = [KaonCalSel])

# PION FILTER
MyPionCalAlg = FilterDesktop("MyPionCalAlg")
MyPionCalAlg.Code = "(ALL)"
MyPionCalSel = Selection("MyPionCalSel", Algorithm = MyPionCalAlg, RequiredSelections = [PionCalSel])

# KST FILTER
MyKstAlg = CombineParticles('MyKstAlg')
MyKstAlg.DecayDescriptor = '[K*(892)0 -> K+ pi-]cc'
MyKstAlg.DaughtersCuts = { "K+" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)",
                           "pi-" : "(PT > 300*MeV) & (BPVIPCHI2() > 4)"}
MyKstAlg.CombinationCut = "(ADAMASS('K*(892)0') < 300.*MeV) & (ADOCACHI2CUT(30, ''))"
MyKstAlg.MotherCut = "(VFASPF(VCHI2) < 25.)"
MyKstAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyKstSel = Selection("MyKstSel", Algorithm = MyKstAlg, RequiredSelections = [MyKaonCalSel, MyPionCalSel])

# B -> JPSI KST
MyBJpsiKstCalAlg = CombineParticles('MyBJpsiKstCalAlg')
MyBJpsiKstCalAlg.DecayDescriptor = '[B0 -> J/psi(1S) K*(892)0]cc'
MyBJpsiKstCalAlg.DaughtersCuts = {}
MyBJpsiKstCalAlg.CombinationCut = "(ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBJpsiKstCalAlg.CombinationCut += " & (ADAMASS('B0') < 1*GeV)"
MyBJpsiKstCalAlg.MotherCut = "(VFASPF(VCHI2) < 25*3)" # NDOF=3
MyBJpsiKstCalAlg.MotherCut += " & (ADMASS('B0') < 0.3*GeV)"
MyBJpsiKstCalAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBJpsiKstCalSel = Selection("MyBJpsiKstCalSel", Algorithm = MyBJpsiKstCalAlg, RequiredSelections = [MyJpsiSel, MyKstSel])
MyBJpsiKstCalSeq = SelectionSequence("MyBJpsiKstCalSeq", TopSelection = MyBJpsiKstCalSel)
