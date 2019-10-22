# PSI(2S) -> JPSI PI PI COMBINER
MyPsi2SAlg = CombineParticles('MyPsi2SAlg')
MyPsi2SAlg.DecayDescriptor = '[psi(2S) -> J/psi(1S) mu+ mu-'
MyPsi2SAlg.DaughtersCuts = {}
MyPsi2SAlg.CombinationCut = "(ADMASS('psi(2S)') < 300*MeV) & (ADOCACHI2CUT(30,''))"
MyPsi2SAlg.MotherCut = "(DMASS('psi(2S)') < 250*MeV) & (VFASPF(VCHI2) < 25)"
MyPsi2SAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyPsi2SSel = Selection("MyPsi2SSel",Algorithm = MyPsi2SAlg, RequiredSelections = [MyMuonSel])

# BC -> PSI(2S) MU
MyBc2PsiMuAlg = CombineParticles('MyBc2PsiMuAlg')
MyBc2PsiMuAlg.DecayDescriptor = '[B_c+ -> psi(2S) mu+]CC'
MyBc2PsiMuAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (TRCHI2DOF < 2) & (BPVIPCHI2() > 9)"}
MyBc2PsiMuAlg.CombinationCut = "(AM < 6.378*GeV) & (ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBc2PsiMuAlg.MotherCut = "(M < 6.278*GeV) & (VFASPF(VCHI2) < 25)"
MyBc2PsiMuAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBc2PsiMuSel = Selection("MyBc2PsiMuSel", Algorithm = MyBc2PsiMuAlg, RequiredSelections = [MyPsi2SSel, MuonsSel])
MyBc2PsiMuSeq = SelectionSequence("MyBc2PsiMuSeq", TopSelection = MyBc2PsiMuSel)

# BC -> PSI(2S) MU
MyBc2PsiMuAlg = CombineParticles('MyBc2PsiMuAlg')
MyBc2PsiMuAlg.DecayDescriptor = '[B_c+ -> psi(2S) mu+]CC'
MyBc2PsiMuAlg.DaughtersCuts = { "mu+" : "(PT > 300*MeV) & (TRCHI2DOF < 2) & (BPVIPCHI2() > 9)"}
MyBc2PsiMuAlg.CombinationCut = "(AM < 6.378*GeV) & (ADOCACHI2CUT(30,''))" # a little wiggle room in mass
MyBc2PsiMuAlg.MotherCut = "(M < 6.278*GeV) & (VFASPF(VCHI2) < 25)"
MyBc2PsiMuAlg.ParticleCombiners.update({"" : "LoKi::VertexFitter"})
MyBc2PsiMuSel = Selection("MyBc2PsiMuSel", Algorithm = MyBc2PsiMuAlg, RequiredSelections = [MyPsi2SSel, MuonsSel])
MyBc2PsiMuSeq = SelectionSequence("MyBc2PsiMuSeq", TopSelection = MyBc2PsiMuSel)

