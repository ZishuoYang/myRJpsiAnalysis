// Run as a script
using namespace RooFit;

RooPlot* mm2frame;
RooPlot* mm2pulls_frame;
RooPlot* nmu_frame;
RooPlot* nmu_eframe;
RooPlot* nmu_pframe;
RooPlot* rtau_frame;
RooPlot* rtau_eframe;
RooPlot* rtau_pframe;
RooPlot* nb0_frame;
RooPlot* nb0_eframe;
RooPlot* nb0_pframe;
RooPlot* nb_frame;
RooPlot* nb_eframe;
RooPlot* nb_pframe;
RooPlot* ncomb_frame;
RooPlot* ncomb_eframe;
RooPlot* ncomb_pframe;

TCanvas* mm2_canvas;
TCanvas* nmu_canvas;
TCanvas* rtau_canvas;
TCanvas* nb0_canvas;
TCanvas* nb_canvas;
TCanvas* ncomb_canvas;
TCanvas* chi2_canvas;

void Plot_MM2 ()
{

  RooAbsData* gd = mcs->genData(0);
  
  // MissMass^2 CANVAS
  mm2frame = mm2->frame(mm2->getBins());
  mm2frame->SetTitle("MissMass^2 (last fit)");
  mm2frame->SetXTitle("mm^2");
  gd->plotOn(mm2frame,Name("mm2data"));
  model->plotOn(mm2frame,Name("mm2fit"));
  model->plotOn(mm2frame,LineColor(kGreen),Components("mu"));
  model->plotOn(mm2frame,LineColor(kRed),Components("tau"));
  model->plotOn(mm2frame,LineColor(kMagenta),Components("b0"));
  model->plotOn(mm2frame,LineColor(kCyan),Components("b"));
  model->plotOn(mm2frame,LineColor(kSpring),Components("comb"));
  mm2pulls_frame = mm2->frame(mm2->getBins());
  mm2pulls_frame->SetTitle("");
  mm2pulls_frame->SetXTitle("mm^2");
  mm2pulls_frame->SetYTitle("pulls");
  RooHist* mm2pulls = mm2frame->pullHist("mm2data","mm2fit");
  mm2pulls_frame->addObject((TObject*)mm2pulls,"XP");
  mm2pulls_frame->SetMinimum(-5);
  mm2pulls_frame->SetMaximum(5);

  mm2_canvas = new TCanvas("mm2_canvas","mm2_canvas",800,800);
  mm2_canvas->cd();
  TPad* mm2histpad = new TPad("mm2histpad","mm2histpad",0.0,0.25,1.0,1.0);
  mm2histpad->Draw();
  mm2histpad->SetTopMargin(0.1);
  TPad* mm2pullpad = new TPad("mm2pullpad","mm2pullpad",0.0,0.0,1.0,0.25);
  mm2pullpad->Draw();
  mm2pullpad->SetTopMargin(0.1);
  mm2histpad->cd();
  mm2frame->SetTitleFont(63,"XY");
  mm2frame->SetTitleSize(18,"XY");
  mm2frame->SetTitleOffset(2,"XY");
  mm2frame->SetLabelFont(63,"XY");
  mm2frame->SetLabelSize(14,"XY");
  mm2frame->Draw();
  mm2histpad->Update();
  mm2pullpad->cd();
  mm2pulls_frame->SetTitleFont(63,"XY");
  mm2pulls_frame->SetTitleSize(18,"XY");
  mm2pulls_frame->SetTitleOffset(2,"XY");
  mm2pulls_frame->SetLabelFont(63,"XY");
  mm2pulls_frame->SetLabelSize(14,"XY");
  mm2pulls_frame->Draw();
  mm2pullpad->Update();
  mm2_canvas->Update();

  // Plot values, errors, and pulls
  nmu_frame = mcs->plotParam(*num_mu,FrameRange(0.97E5,1.03E5),FrameBins(40));
  nmu_eframe = mcs->plotError(*num_mu,675,695,40);
  nmu_pframe = mcs->plotPull(*num_mu,-4,4,40,kTRUE);

  nmu_canvas = new TCanvas("nmu_canvas","nmu_canvas",800,800);
  nmu_canvas->cd();
  TPad* nmuhistpad = new TPad("nmuhistpad","nmuhistpad",0.0,0.66666,1.0,1.0);
  nmuhistpad->Draw();
  nmuhistpad->SetTopMargin(0.1);
  TPad* nmuerrpad = new TPad("nmuerrpad","nmuerrpad",0.0,0.33333,1.0,0.66666);
  nmuerrpad->Draw();
  nmuerrpad->SetTopMargin(0.1);
  TPad* nmupullpad = new TPad("nmupullpad","nmupullpad",0.0,0.0,1.0,0.33333);
  nmupullpad->Draw();
  nmupullpad->SetTopMargin(0.1);
  nmuhistpad->cd();
  nmu_frame->SetTitleFont(63,"XY");
  nmu_frame->SetTitleSize(18,"XY");
  nmu_frame->SetTitleOffset(2,"XY");
  nmu_frame->SetLabelFont(63,"XY");
  nmu_frame->SetLabelSize(14,"XY");
  nmu_frame->Draw();
  nmuhistpad->Update();
  nmuerrpad->cd();
  nmu_eframe->SetTitleFont(63,"XY");
  nmu_eframe->SetTitleSize(18,"XY");
  nmu_eframe->SetTitleOffset(2,"XY");
  nmu_eframe->SetLabelFont(63,"XY");
  nmu_eframe->SetLabelSize(14,"XY");
  nmu_eframe->Draw();
  nmuerrpad->Update();
  nmupullpad->cd();
  nmu_pframe->SetTitleFont(63,"XY");
  nmu_pframe->SetTitleSize(18,"XY");
  nmu_pframe->SetTitleOffset(2,"XY");
  nmu_pframe->SetLabelFont(63,"XY");
  nmu_pframe->SetLabelSize(14,"XY");
  nmu_pframe->Draw();
  nmupullpad->Update();
  nmu_canvas->Update();

  // rtau
  rtau_frame = mcs->plotParam(*Rtau,FrameRange(0.005,0.045),FrameBins(40));
  rtau_eframe = mcs->plotError(*Rtau,0.0095,0.0115,40);
  rtau_pframe = mcs->plotPull(*Rtau,-4,4,40,kTRUE);

  rtau_canvas = new TCanvas("rtau_canvas","rtau_canvas",800,800);
  rtau_canvas->cd();
  TPad* rtauhistpad = new TPad("rtauhistpad","rtauhistpad",0.0,0.66666,1.0,1.0);
  rtauhistpad->Draw();
  rtauhistpad->SetTopMargin(0.1);
  TPad* rtauerrpad = new TPad("rtauerrpad","rtauerrpad",0.0,0.33333,1.0,0.66666);
  rtauerrpad->Draw();
  rtauerrpad->SetTopMargin(0.1);
  TPad* rtaupullpad = new TPad("rtaupullpad","rtaupullpad",0.0,0.0,1.0,0.33333);
  rtaupullpad->Draw();
  rtaupullpad->SetTopMargin(0.1);
  rtauhistpad->cd();
  rtau_frame->SetTitleFont(63,"XY");
  rtau_frame->SetTitleSize(18,"XY");
  rtau_frame->SetTitleOffset(2,"XY");
  rtau_frame->SetLabelFont(63,"XY");
  rtau_frame->SetLabelSize(14,"XY");
  rtau_frame->Draw();
  rtauhistpad->Update();
  rtauerrpad->cd();
  rtau_eframe->SetTitleFont(63,"XY");
  rtau_eframe->SetTitleSize(18,"XY");
  rtau_eframe->SetTitleOffset(2,"XY");
  rtau_eframe->SetLabelFont(63,"XY");
  rtau_eframe->SetLabelSize(14,"XY");
  rtau_eframe->Draw();
  rtauerrpad->Update();
  rtaupullpad->cd();
  rtau_pframe->SetTitleFont(63,"XY");
  rtau_pframe->SetTitleSize(18,"XY");
  rtau_pframe->SetTitleOffset(2,"XY");
  rtau_pframe->SetLabelFont(63,"XY");
  rtau_pframe->SetLabelSize(14,"XY");
  rtau_pframe->Draw();
  rtaupullpad->Update();
  rtau_canvas->Update();

  // B0
  nb0_frame = mcs->plotParam(*num_b0,FrameRange(5.5E3,13.5E3),FrameBins(40));
  nb0_eframe = mcs->plotError(*num_b0,1040,1100,40);
  nb0_pframe = mcs->plotPull(*num_b0,-4,4,40,kTRUE);

  nb0_canvas = new TCanvas("nb0_canvas","nb0_canvas",800,800);
  nb0_canvas->cd();
  TPad* nb0histpad = new TPad("nb0histpad","nb0histpad",0.0,0.66666,1.0,1.0);
  nb0histpad->Draw();
  nb0histpad->SetTopMargin(0.1);
  TPad* nb0errpad = new TPad("nb0errpad","nb0errpad",0.0,0.33333,1.0,0.66666);
  nb0errpad->Draw();
  nb0errpad->SetTopMargin(0.1);
  TPad* nb0pullpad = new TPad("nb0pullpad","nb0pullpad",0.0,0.0,1.0,0.33333);
  nb0pullpad->Draw();
  nb0pullpad->SetTopMargin(0.1);
  nb0histpad->cd();
  nb0_frame->SetTitleFont(63,"XY");
  nb0_frame->SetTitleSize(18,"XY");
  nb0_frame->SetTitleOffset(2,"XY");
  nb0_frame->SetLabelFont(63,"XY");
  nb0_frame->SetLabelSize(14,"XY");
  nb0_frame->Draw();
  nb0histpad->Update();
  nb0errpad->cd();
  nb0_eframe->SetTitleFont(63,"XY");
  nb0_eframe->SetTitleSize(18,"XY");
  nb0_eframe->SetTitleOffset(2,"XY");
  nb0_eframe->SetLabelFont(63,"XY");
  nb0_eframe->SetLabelSize(14,"XY");
  nb0_eframe->Draw();
  nb0errpad->Update();
  nb0pullpad->cd();
  nb0_pframe->SetTitleFont(63,"XY");
  nb0_pframe->SetTitleSize(18,"XY");
  nb0_pframe->SetTitleOffset(2,"XY");
  nb0_pframe->SetLabelFont(63,"XY");
  nb0_pframe->SetLabelSize(14,"XY");
  nb0_pframe->Draw();
  nb0pullpad->Update();
  nb0_canvas->Update();

  // B
  nb_frame = mcs->plotParam(*num_b,FrameRange(2.3E4,2.7E4),FrameBins(40));
  nb_eframe = mcs->plotError(*num_b,790,830,40);
  nb_pframe = mcs->plotPull(*num_b,-4,4,40,kTRUE);

  nb_canvas = new TCanvas("nb_canvas","nb_canvas",800,800);
  nb_canvas->cd();
  TPad* nbhistpad = new TPad("nbhistpad","nbhistpad",0.0,0.66666,1.0,1.0);
  nbhistpad->Draw();
  nbhistpad->SetTopMargin(0.1);
  TPad* nberrpad = new TPad("nberrpad","nberrpad",0.0,0.33333,1.0,0.66666);
  nberrpad->Draw();
  nberrpad->SetTopMargin(0.1);
  TPad* nbpullpad = new TPad("nbpullpad","nbpullpad",0.0,0.0,1.0,0.33333);
  nbpullpad->Draw();
  nbpullpad->SetTopMargin(0.1);
  nbhistpad->cd();
  nb_frame->SetTitleFont(63,"XY");
  nb_frame->SetTitleSize(18,"XY");
  nb_frame->SetTitleOffset(2,"XY");
  nb_frame->SetLabelFont(63,"XY");
  nb_frame->SetLabelSize(14,"XY");
  nb_frame->Draw();
  nbhistpad->Update();
  nberrpad->cd();
  nb_eframe->SetTitleFont(63,"XY");
  nb_eframe->SetTitleSize(18,"XY");
  nb_eframe->SetTitleOffset(2,"XY");
  nb_eframe->SetLabelFont(63,"XY");
  nb_eframe->SetLabelSize(14,"XY");
  nb_eframe->Draw();
  nberrpad->Update();
  nbpullpad->cd();
  nb_pframe->SetTitleFont(63,"XY");
  nb_pframe->SetTitleSize(18,"XY");
  nb_pframe->SetTitleOffset(2,"XY");
  nb_pframe->SetLabelFont(63,"XY");
  nb_pframe->SetLabelSize(14,"XY");
  nb_pframe->Draw();
  nbpullpad->Update();
  nb_canvas->Update();

  // COMB
  ncomb_frame = mcs->plotParam(*num_comb,FrameRange(3.1E4,3.9E4),FrameBins(40));
  ncomb_eframe = mcs->plotError(*num_comb,1280,1340,40);
  ncomb_pframe = mcs->plotPull(*num_comb,-4,4,40,kTRUE);
  
  ncomb_canvas = new TCanvas("ncomb_canvas","ncomb_canvas",800,800);
  ncomb_canvas->cd();
  TPad* ncombhistpad = new TPad("ncombhistpad","ncombhistpad",0.0,0.66666,1.0,1.0);
  ncombhistpad->Draw();
  ncombhistpad->SetTopMargin(0.1);
  TPad* ncomberrpad = new TPad("ncomberrpad","ncomberrpad",0.0,0.33333,1.0,0.66666);
  ncomberrpad->Draw();
  ncomberrpad->SetTopMargin(0.1);
  TPad* ncombpullpad = new TPad("ncombpullpad","ncombpullpad",0.0,0.0,1.0,0.33333);
  ncombpullpad->Draw();
  ncombpullpad->SetTopMargin(0.1);
  ncombhistpad->cd();
  ncomb_frame->SetTitleFont(63,"XY");
  ncomb_frame->SetTitleSize(18,"XY");
  ncomb_frame->SetTitleOffset(2,"XY");
  ncomb_frame->SetLabelFont(63,"XY");
  ncomb_frame->SetLabelSize(14,"XY");
  ncomb_frame->Draw();
  ncombhistpad->Update();
  ncomberrpad->cd();
  ncomb_eframe->SetTitleFont(63,"XY");
  ncomb_eframe->SetTitleSize(18,"XY");
  ncomb_eframe->SetTitleOffset(2,"XY");
  ncomb_eframe->SetLabelFont(63,"XY");
  ncomb_eframe->SetLabelSize(14,"XY");
  ncomb_eframe->Draw();
  ncomberrpad->Update();
  ncombpullpad->cd();
  ncomb_pframe->SetTitleFont(63,"XY");
  ncomb_pframe->SetTitleSize(18,"XY");
  ncomb_pframe->SetTitleOffset(2,"XY");
  ncomb_pframe->SetLabelFont(63,"XY");
  ncomb_pframe->SetLabelSize(14,"XY");
  ncomb_pframe->Draw();
  ncombpullpad->Update();
  ncomb_canvas->Update();

  // CHI^2 CANVAS

  //   TH1* hist_chi2 = mcs->fitParDataSet().createHistogram("chi2");
  //   TH1* hist_prob = mcs->fitParDataSet().createHistogram("prob");  
  //   chi2_canvas = new TCanvas("fit_chi2_canvas","fit_chi2_canvas",800,1500);
  //   chi2_canvas->Divide(2);
  //   chi2_canvas->cd(1);
  //   gPad->SetLeftMargin(0.15);
  //   hist_chi2->GetYaxis()->SetTitleOffset(1.4);
  //   hist_chi2->Draw();
  //   chi2_canvas->cd(2);
  //   gPad->SetLeftMargin(0.15);
  //   hist_prob->GetYaxis()->SetTitleOffset(1.4);
  //   hist_prob->Draw();

  return;
}
