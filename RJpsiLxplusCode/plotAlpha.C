const double MBC = 6277;

TH1F* plotAlpha() 
{
  TH1F* ret = new TH1F("min","min",100,-0.25,0.1);
  
  double p0,p1,p2,p3;
  double pj0,pj1,pj2,pj3;
  double pm0,pm1,pm2,pm3;
  
  // BC
  TBranch *b_p0 = MCMuDecayTree->GetBranch("Bc_TRUEP_E");
  b_p0->SetAddress(&p0);
  TBranch *b_p1 = MCMuDecayTree->GetBranch("Bc_TRUEP_X");
  b_p1->SetAddress(&p1);
  TBranch *b_p2 = MCMuDecayTree->GetBranch("Bc_TRUEP_Y");
  b_p2->SetAddress(&p2);
  TBranch *b_p3 = MCMuDecayTree->GetBranch("Bc_TRUEP_Z");
  b_p3->SetAddress(&p3);

  // JPSI
  TBranch *b_pj0 = MCMuDecayTree->GetBranch("Jpsi_TRUEP_E");
  b_pj0->SetAddress(&pj0);
  TBranch *b_pj1 = MCMuDecayTree->GetBranch("Jpsi_TRUEP_X");
  b_pj1->SetAddress(&pj1);
  TBranch *b_pj2 = MCMuDecayTree->GetBranch("Jpsi_TRUEP_Y");
  b_pj2->SetAddress(&pj2);
  TBranch *b_pj3 = MCMuDecayTree->GetBranch("Jpsi_TRUEP_Z");
  b_pj3->SetAddress(&pj3);

  // BACHMU
  TBranch *b_pm0 = MCMuDecayTree->GetBranch("BachMu_TRUEP_E");
  b_pm0->SetAddress(&pm0);
  TBranch *b_pm1 = MCMuDecayTree->GetBranch("BachMu_TRUEP_X");
  b_pm1->SetAddress(&pm1);
  TBranch *b_pm2 = MCMuDecayTree->GetBranch("BachMu_TRUEP_Y");
  b_pm2->SetAddress(&pm2);
  TBranch *b_pm3 = MCMuDecayTree->GetBranch("BachMu_TRUEP_Z");
  b_pm3->SetAddress(&pm3);

  Int_t nevent = MCMuDecayTree->GetEntries();
  for (Int_t i=0; i < nevent; i++) {
    
    MCMuDecayTree->GetEntry(i);
    
    double py0 = pj0 + pm0;
    double py1 = pj1 + pm1;
    double py2 = pj2 + pm2;
    double py3 = pj3 + pm3;
    double mm = sqrt(py0*py0-py1*py1-py2*py2-py3*py3);

    double v0 = p0/MBC - py0/mm;
    double v1 = p1/MBC - py1/mm;
    double v2 = p2/MBC - py2/mm;
    double v3 = p3/MBC - py3/mm;
    double alpha = 0.5*(v0*v0-v1*v1-v2*v2-v3*v3);
    double pf = -1*sqrt(alpha*(alpha-2));

    // Now, can I get the theta of the Y with respect to the B boost in the rest frame?
    TLorentzVector BcP;
    BcP.SetXYZT(p1,p2,p3,p0);
    TVector3 boost = BcP.BoostVector();
    TVector3 fd = BcP.Vect();
    fd = fd.Unit();
    TLorentzVector YP;
    YP.SetXYZT(py1,py2,py3,py0);
    YP.Boost(-boost);
    double trueE = YP.E();
    double theta = YP.Angle(fd);
    double c = cos(theta);
    YP.Boost(boost);
    
    double err = (MBC/mm*py3 - p3)/p3;
    double m1 = -1*(alpha + pf*c);
    double m2 = pf/(1-alpha)*c;

    // Iterative estimate
    //    cout << "TRUE E: " << trueE << endl;

    double E0 = mm;
    //    cout << "E0: " << E0 << endl;
    double TanTheta = fd.Perp()/(fd.Z());
    double BcPT = (MBC)/(E0)*TanTheta*py3;
    TLorentzVector BcP_est;
    BcP_est.SetPtEtaPhiM(BcPT,fd.Eta(),fd.Phi(),MBC);
    boost = BcP_est.BoostVector();
    YP.Boost(-boost);
    double E1 = YP.E();
    YP.Boost(boost);

    //    cout << "E1: " << E1 << endl;
    double TanTheta = fd.Perp()/(fd.Z());
    double BcPT = (MBC)/(E1)*TanTheta*py3;
    TLorentzVector BcP_est;
    BcP_est.SetPtEtaPhiM(BcPT,fd.Eta(),fd.Phi(),MBC);
    boost = BcP_est.BoostVector();
    YP.Boost(-boost);
    double E2 = YP.E();
    YP.Boost(boost);

    //    cout << "E2: " << E2 << endl;
    double TanTheta = fd.Perp()/(fd.Z());
    double BcPT = (MBC)/(E2)*TanTheta*py3;
    TLorentzVector BcP_est;
    BcP_est.SetPtEtaPhiM(BcPT,fd.Eta(),fd.Phi(),MBC);
    boost = BcP_est.BoostVector();
    YP.Boost(-boost);
    double E3 = YP.E();
    YP.Boost(boost);
  
    //    cout << "E3: " << E3 << endl;
    double TanTheta = fd.Perp()/(fd.Z());
    double BcPT = (MBC)/(E3)*TanTheta*py3;
    TLorentzVector BcP_est;
    BcP_est.SetPtEtaPhiM(BcPT,fd.Eta(),fd.Phi(),MBC);
    boost = BcP_est.BoostVector();
    YP.Boost(-boost);
    double E4 = YP.E();
    YP.Boost(boost);

    //    cout << "E4: " << E4 << endl;
    double TanTheta = fd.Perp()/(fd.Z());
    double BcPT = (MBC)/(E4)*TanTheta*py3;
    TLorentzVector BcP_est;
    BcP_est.SetPtEtaPhiM(BcPT,fd.Eta(),fd.Phi(),MBC);
    boost = BcP_est.BoostVector();
    YP.Boost(-boost);
    double E5 = YP.E();
    YP.Boost(boost);

    ret->Fill((E5-trueE)/trueE);
  }
  return ret;
}
