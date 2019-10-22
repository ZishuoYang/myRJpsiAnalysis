using namespace RooFit;

void ExtraDalitzFitter_2D_makeplot ()
{  
  m1frame = m1->frame(m1->getBins());
  fit_data->plotOn(m1frame);
  model->plotOn(m1frame);
  model->plotOn(m1frame,Components("sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m1frame,Components("b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m1frame,Components("bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m1frame,Components("comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m1frame,Components("lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m1frame,Components("other"),LineStyle(kDashed),LineColor(kPink));

  m2frame = m2->frame(m2->getBins());
  fit_data->plotOn(m2frame);
  model->plotOn(m2frame);
  model->plotOn(m2frame,Components("sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m2frame,Components("b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m2frame,Components("bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m2frame,Components("comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m2frame,Components("lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m2frame,Components("other"),LineStyle(kDashed),LineColor(kPink));

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
