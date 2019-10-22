// Run as a script
using namespace RooFit;

RooPlot* mm2frame;
RooPlot* ltframe;
RooPlot* mm2pulls_frame;
RooPlot* ltpulls_frame;
RooPlot* nmu_frame;
RooPlot* nmu_eframe;
RooPlot* nmu_pframe;
RooPlot* rtau_frame;
RooPlot* rtau_eframe;
RooPlot* rtau_pframe;
RooPlot* npv_frame;
RooPlot* npv_eframe;
RooPlot* npv_pframe;
RooPlot* nghost_frame;
RooPlot* nghost_eframe;
RooPlot* nghost_pframe;
RooPlot* ncomb_frame;
RooPlot* ncomb_eframe;
RooPlot* ncomb_pframe;

TCanvas* mm2_canvas;
TCanvas* lt_canvas;
TCanvas* nmu_canvas;
TCanvas* rtau_canvas;
TCanvas* npv_canvas;
TCanvas* nghost_canvas;
TCanvas* ncomb_canvas;
TCanvas* chi2_canvas;

void Plot_MM2_LT_Q2Cat_ELCat ()
{

  goto quickplots;
  // MissMass^2 CANVAS
  mm2frame = mm2->frame(mm2->getBins());
  mm2frame->SetTitle("MissMass^2 (last fit)");
  mm2frame->SetXTitle("mm^2");
  gd->plotOn(mm2frame,Name("mm2data"));
  gen_model->plotOn(mm2frame,LineColor(kBlue),FillColor(kBlue),Name("mm2fit"),DrawOption("F")); // all
  gen_model->plotOn(mm2frame,LineColor(kRed),FillColor(kRed),Components("fd*,mu*,ghost*,pv*,b*,comb*"),DrawOption("F")); // - signal
  gen_model->plotOn(mm2frame,LineColor(kBlue+3),FillColor(kBlue+3),Components("mu*,ghost*,pv*,b*,comb*"),DrawOption("F")); // - feeddown
  gen_model->plotOn(mm2frame,LineColor(kCyan+1),FillColor(kCyan+1),Components("ghost*,pv*,b*,comb*"),DrawOption("F")); // - mu
  gen_model->plotOn(mm2frame,LineColor(kGreen+1),FillColor(kGreen+1),Components("pv*,b*,comb*"),DrawOption("F")); // - ghost
  gen_model->plotOn(mm2frame,LineColor(kMagenta),FillColor(kMagenta),Components("b*,comb*"),DrawOption("F")); // - pv
  gen_model->plotOn(mm2frame,LineColor(kBlack),FillColor(kBlack),Components("comb*"),DrawOption("F")); // - b
//   gen_model->plotOn(mm2frame,Name("mm2fit"));
//   gen_model->plotOn(mm2frame,LineColor(kGreen+2),Components("mu*"));
//   gen_model->plotOn(mm2frame,LineColor(kRed),Components("tau*"));
//   gen_model->plotOn(mm2frame,LineColor(kSpring),Components("fd*"));
//   gen_model->plotOn(mm2frame,LineColor(kMagenta),Components("pv*"));
//   gen_model->plotOn(mm2frame,LineColor(kCyan+3),Components("ghost*"));
//   gen_model->plotOn(mm2frame,LineColor(kCyan),Components("b*"));
//   gen_model->plotOn(mm2frame,LineColor(kViolet),Components("comb*"));
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
  //  mm2histpad->SetLogy();
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

  ltframe = lt->frame(lt->getBins());
  ltframe->SetTitle("log(lifetime) (last fit)");
  ltframe->SetXTitle("log(lt)");
  gd->plotOn(ltframe,Name("ltdata"));
  gen_model->plotOn(ltframe,LineColor(kBlue),FillColor(kBlue),Name("ltfit"),DrawOption("F")); // all
  gen_model->plotOn(ltframe,LineColor(kRed),FillColor(kRed),Components("fd*,mu*,ghost*,pv*,b*,comb*"),DrawOption("F")); // - signal
  gen_model->plotOn(ltframe,LineColor(kBlue+3),FillColor(kBlue+3),Components("mu*,ghost*,pv*,b*,comb*"),DrawOption("F")); // - feeddown
  gen_model->plotOn(ltframe,LineColor(kCyan+1),FillColor(kCyan+1),Components("ghost*,pv*,b*,comb*"),DrawOption("F")); // - mu
  gen_model->plotOn(ltframe,LineColor(kGreen+1),FillColor(kGreen+1),Components("pv*,b*,comb*"),DrawOption("F")); // - ghost
  gen_model->plotOn(ltframe,LineColor(kMagenta),FillColor(kMagenta),Components("b*,comb*"),DrawOption("F")); // - pv
  gen_model->plotOn(ltframe,LineColor(kBlack),FillColor(kBlack),Components("comb*"),DrawOption("F")); // - b
//   gen_model->plotOn(ltframe,Name("ltfit"));
//   gen_model->plotOn(ltframe,LineColor(kGreen+2),Components("mu*"));
//   gen_model->plotOn(ltframe,LineColor(kRed),Components("tau*"));
//   gen_model->plotOn(ltframe,LineColor(kSpring),Components("fd*"));
//   gen_model->plotOn(ltframe,LineColor(kMagenta),Components("pv*"));
//   gen_model->plotOn(ltframe,LineColor(kCyan+3),Components("ghost*"));
//   gen_model->plotOn(ltframe,LineColor(kCyan),Components("b*"));
//   gen_model->plotOn(ltframe,LineColor(kViolet),Components("comb*"));
  ltpulls_frame = lt->frame(lt->getBins());
  ltpulls_frame->SetTitle("");
  ltpulls_frame->SetXTitle("log(lt)");
  ltpulls_frame->SetYTitle("pulls");
  RooHist* ltpulls = ltframe->pullHist("ltdata","ltfit");
  ltpulls_frame->addObject((TObject*)ltpulls,"XP");
  ltpulls_frame->SetMinimum(-5);
  ltpulls_frame->SetMaximum(5);

  lt_canvas = new TCanvas("lt_canvas","lt_canvas",800,800);
  lt_canvas->cd();
  TPad* lthistpad = new TPad("lthistpad","lthistpad",0.0,0.25,1.0,1.0);
  //  lthistpad->SetLogy();
  lthistpad->Draw();
  lthistpad->SetTopMargin(0.1);
  TPad* ltpullpad = new TPad("ltpullpad","ltpullpad",0.0,0.0,1.0,0.25);
  ltpullpad->Draw();
  ltpullpad->SetTopMargin(0.1);
  lthistpad->cd();
  ltframe->SetTitleFont(63,"XY");
  ltframe->SetTitleSize(18,"XY");
  ltframe->SetTitleOffset(2,"XY");
  ltframe->SetLabelFont(63,"XY");
  ltframe->SetLabelSize(14,"XY");
  ltframe->Draw();
  lthistpad->Update();
  ltpullpad->cd();
  ltpulls_frame->SetTitleFont(63,"XY");
  ltpulls_frame->SetTitleSize(18,"XY");
  ltpulls_frame->SetTitleOffset(2,"XY");
  ltpulls_frame->SetLabelFont(63,"XY");
  ltpulls_frame->SetLabelSize(14,"XY");
  ltpulls_frame->Draw();
  ltpullpad->Update();
  lt_canvas->Update();
  
 quickplots:
  // Plot values, errors, and pulls
     nmu_frame = mcs->plotParam(*num_mu,FrameRange(0.7e4,1.0e4),FrameBins(40));
     nmu_eframe = mcs->plotError(*num_mu,100,150,40);
     nmu_pframe = mcs->plotPull(*num_mu,-10,10,50,kTRUE);

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
  rtau_frame = mcs->plotParam(*rtau,FrameRange(0.0,0.1),FrameBins(40));
  rtau_eframe = mcs->plotError(*rtau,0,0.03,40);
  rtau_pframe = mcs->plotPull(*rtau,-10,10,50,kTRUE);

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

  // rfd
  rfd_frame = mcs->plotParam(*rfd,FrameRange(0.05,0.2),FrameBins(40));
  rfd_eframe = mcs->plotError(*rfd,0.004,0.008,40);
  rfd_pframe = mcs->plotPull(*rfd,-10,10,50,kTRUE);

  rfd_canvas = new TCanvas("rfd_canvas","rfd_canvas",800,800);
  rfd_canvas->cd();
  TPad* rfdhistpad = new TPad("rfdhistpad","rfdhistpad",0.0,0.66666,1.0,1.0);
  rfdhistpad->Draw();
  rfdhistpad->SetTopMargin(0.1);
  TPad* rfderrpad = new TPad("rfderrpad","rfderrpad",0.0,0.33333,1.0,0.66666);
  rfderrpad->Draw();
  rfderrpad->SetTopMargin(0.1);
  TPad* rfdpullpad = new TPad("rfdpullpad","rfdpullpad",0.0,0.0,1.0,0.33333);
  rfdpullpad->Draw();
  rfdpullpad->SetTopMargin(0.1);
  rfdhistpad->cd();
  rfd_frame->SetTitleFont(63,"XY");
  rfd_frame->SetTitleSize(18,"XY");
  rfd_frame->SetTitleOffset(2,"XY");
  rfd_frame->SetLabelFont(63,"XY");
  rfd_frame->SetLabelSize(14,"XY");
  rfd_frame->Draw();
  rfdhistpad->Update();
  rfderrpad->cd();
  rfd_eframe->SetTitleFont(63,"XY");
  rfd_eframe->SetTitleSize(18,"XY");
  rfd_eframe->SetTitleOffset(2,"XY");
  rfd_eframe->SetLabelFont(63,"XY");
  rfd_eframe->SetLabelSize(14,"XY");
  rfd_eframe->Draw();
  rfderrpad->Update();
  rfdpullpad->cd();
  rfd_pframe->SetTitleFont(63,"XY");
  rfd_pframe->SetTitleSize(18,"XY");
  rfd_pframe->SetTitleOffset(2,"XY");
  rfd_pframe->SetLabelFont(63,"XY");
  rfd_pframe->SetLabelSize(14,"XY");
  rfd_pframe->Draw();
  rfdpullpad->Update();
  rfd_canvas->Update();

  // B0
  npv_frame = mcs->plotParam(*num_pv,FrameRange(0,1500),FrameBins(40));
  npv_eframe = mcs->plotError(*num_pv,0,50,40);
  npv_pframe = mcs->plotPull(*num_pv,-10,10,50,kTRUE);

  npv_canvas = new TCanvas("npv_canvas","npv_canvas",800,800);
  npv_canvas->cd();
  TPad* npvhistpad = new TPad("npvhistpad","npvhistpad",0.0,0.66666,1.0,1.0);
  npvhistpad->Draw();
  npvhistpad->SetTopMargin(0.1);
  TPad* npverrpad = new TPad("npverrpad","npverrpad",0.0,0.33333,1.0,0.66666);
  npverrpad->Draw();
  npverrpad->SetTopMargin(0.1);
  TPad* npvpullpad = new TPad("npvpullpad","npvpullpad",0.0,0.0,1.0,0.33333);
  npvpullpad->Draw();
  npvpullpad->SetTopMargin(0.1);
  npvhistpad->cd();
  npv_frame->SetTitleFont(63,"XY");
  npv_frame->SetTitleSize(18,"XY");
  npv_frame->SetTitleOffset(2,"XY");
  npv_frame->SetLabelFont(63,"XY");
  npv_frame->SetLabelSize(14,"XY");
  npv_frame->Draw();
  npvhistpad->Update();
  npverrpad->cd();
  npv_eframe->SetTitleFont(63,"XY");
  npv_eframe->SetTitleSize(18,"XY");
  npv_eframe->SetTitleOffset(2,"XY");
  npv_eframe->SetLabelFont(63,"XY");
  npv_eframe->SetLabelSize(14,"XY");
  npv_eframe->Draw();
  npverrpad->Update();
  npvpullpad->cd();
  npv_pframe->SetTitleFont(63,"XY");
  npv_pframe->SetTitleSize(18,"XY");
  npv_pframe->SetTitleOffset(2,"XY");
  npv_pframe->SetLabelFont(63,"XY");
  npv_pframe->SetLabelSize(14,"XY");
  npv_pframe->Draw();
  npvpullpad->Update();
  npv_canvas->Update();


//   // GHOST
//   nghost_frame = mcs->plotParam(*num_ghost,FrameRange(0,400),FrameBins(40));
//   nghost_eframe = mcs->plotError(*num_ghost,0,100,40);
//   nghost_pframe = mcs->plotPull(*num_ghost,-10,10,50,kTRUE);

//   nghost_canvas = new TCanvas("nghost_canvas","nghost_canvas",800,800);
//   nghost_canvas->cd();
//   TPad* nghosthistpad = new TPad("nghosthistpad","nghosthistpad",0.0,0.66666,1.0,1.0);
//   nghosthistpad->Draw();
//   nghosthistpad->SetTopMargin(0.1);
//   TPad* nghosterrpad = new TPad("nghosterrpad","nghosterrpad",0.0,0.33333,1.0,0.66666);
//   nghosterrpad->Draw();
//   nghosterrpad->SetTopMargin(0.1);
//   TPad* nghostpullpad = new TPad("nghostpullpad","nghostpullpad",0.0,0.0,1.0,0.33333);
//   nghostpullpad->Draw();
//   nghostpullpad->SetTopMargin(0.1);
//   nghosthistpad->cd();
//   nghost_frame->SetTitleFont(63,"XY");
//   nghost_frame->SetTitleSize(18,"XY");
//   nghost_frame->SetTitleOffset(2,"XY");
//   nghost_frame->SetLabelFont(63,"XY");
//   nghost_frame->SetLabelSize(14,"XY");
//   nghost_frame->Draw();
//   nghosthistpad->Update();
//   nghosterrpad->cd();
//   nghost_eframe->SetTitleFont(63,"XY");
//   nghost_eframe->SetTitleSize(18,"XY");
//   nghost_eframe->SetTitleOffset(2,"XY");
//   nghost_eframe->SetLabelFont(63,"XY");
//   nghost_eframe->SetLabelSize(14,"XY");
//   nghost_eframe->Draw();
//   nghosterrpad->Update();
//   nghostpullpad->cd();
//   nghost_pframe->SetTitleFont(63,"XY");
//   nghost_pframe->SetTitleSize(18,"XY");
//   nghost_pframe->SetTitleOffset(2,"XY");
//   nghost_pframe->SetLabelFont(63,"XY");
//   nghost_pframe->SetLabelSize(14,"XY");
//   nghost_pframe->Draw();
//   nghostpullpad->Update();
//   nghost_canvas->Update();

  // B
  nb_frame = mcs->plotParam(*num_b,FrameRange(2E3,3.5E3),FrameBins(40));
  nb_eframe = mcs->plotError(*num_b,40,100,40);
  nb_pframe = mcs->plotPull(*num_b,-10,10,50,kTRUE);

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

  return;

  // COMB
  ncomb_frame = mcs->plotParam(*num_comb,FrameRange(3.5e3,5.5e3),FrameBins(40));
  ncomb_eframe = mcs->plotError(*num_comb,100,160,40);
  ncomb_pframe = mcs->plotPull(*num_comb,-10,10,50,kTRUE);
  
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
