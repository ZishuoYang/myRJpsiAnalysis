using namespace RooFit;

void ExtraDalitzFitter_Simul_makeplot ()
{ 
  m1frame = m1->frame(m1->getBins());
  fit_data->plotOn(m1frame,Cut("variable==variable::jpsi"));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_other"),LineStyle(kDashed),LineColor(kPink));

  m2frame = m2->frame(m2->getBins());
  fit_data->plotOn(m2frame,Cut("variable==variable::bm"));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_other"),LineStyle(kDashed),LineColor(kPink));

  canvas = new TCanvas("fit_canvas","fit_canvas",800,400);
  canvas->Divide(2);
  canvas->cd(1);
  gPad->SetLeftMargin(0.15);
  m1frame->GetYaxis()->SetTitleOffset(1.4);
  m1frame->Draw();
  canvas->cd(2);
  gPad->SetLeftMargin(0.15);
  m2frame->GetYaxis()->SetTitleOffset(1.4);
  m2frame->Draw();
  
  return;
}
