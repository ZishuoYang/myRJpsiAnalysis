#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooKeysPdf.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

TTree *sigDataTree;
TTree *bkgDataTree;
RooRealVar* m1;
RooRealVar* m2;
RooRealVar* Bc_SIG_Mu;
RooRealVar* Bc_SIG_Tau;
RooRealVar* Bc_SIG_Mu_SWITCHED;
RooRealVar* Bc_SIG_Tau_SWITCHED;
RooRealVar* Bc_SIG_BadTau;
RooRealVar* Bc_BKG_B2JpsiX;
RooRealVar* Bc_BKG_B02JpsiX;
RooRealVar* BBBKG;
RooRealVar* LowMassBKG;
RooCategory* variable;
RooDataHist* bm_fit_data;
RooDataHist* jpsi_fit_data;
RooDataHist* fit_data;
RooDataSet* sig_data_full;
RooDataSet* b0bkg_data_full;
RooDataSet* bbkg_data_full;
RooDataSet* comb_data_full;
RooDataSet* lowmass_data_full;
RooDataSet* bm_sig_data;
RooDataSet* bm_b0bkg_data;
RooDataSet* bm_bbkg_data;
RooDataSet* bm_comb_data;
RooDataSet* bm_lowmass_data;
RooDataSet* jpsi_sig_data;
RooDataSet* jpsi_b0bkg_data;
RooDataSet* jpsi_bbkg_data;
RooDataSet* jpsi_comb_data;
RooDataSet* jpsi_lowmass_data;
RooKeysPdf* bm_sig_pdf;
RooKeysPdf* bm_b0bkg_pdf;
RooKeysPdf* bm_bbkg_pdf;
RooKeysPdf* bm_comb_pdf;
RooKeysPdf* bm_lowmass_pdf;
RooKeysPdf* jpsi_sig_pdf;
RooKeysPdf* jpsi_b0bkg_pdf;
RooKeysPdf* jpsi_bbkg_pdf;
RooKeysPdf* jpsi_comb_pdf;
RooKeysPdf* jpsi_lowmass_pdf;
RooRealVar* num_sig;
RooRealVar* num_b0bkg;
RooRealVar* num_bbkg;
RooRealVar* num_comb;
RooRealVar* num_lowmass;
RooAddPdf* jpsi_model;
RooAddPdf* bm_model;
RooSimultaneous* model;
RooPlot* m1frame;
RooPlot* m2frame;
TCanvas* canvas;
using namespace RooFit;

void ExtraDalitzFitter_Simul_Hist ()
{

  const char m1str[100] = "Jpsi_SMALLESTDELTACHI2_MM";
  const char m2str[100] = "BachMu_SMALLESTCHI2_MM";

  // OPENING ROOT FILE
  TFile fitFile("output_histos.root","READ");
  TFile sigDataFile("Bc_SIG_Tau_Cands.root","READ");
  sigDataTree = (TTree*)sigDataFile.Get("DecayTree");
  TFile bkgDataFile("Bc_BKG_Cands.root","READ");
  bkgDataTree = (TTree*)bkgDataFile.Get("DecayTree");

  m1 = new RooRealVar (m1str,"m1",3200,7200);
  m2 = new RooRealVar (m2str,"m2",0,5000);

  THStack* jpsi_fit_stack = (THStack*)fitFile.Get("jpsiextramm_stack");
  TH1D* jpsi_fit_hist = (TH1D*)jpsi_fit_stack->GetStack()->Last();
  jpsi_fit_data = new RooDataHist("jpsi_fit_data","jpsi_fit_data",RooArgSet(*m1),jpsi_fit_hist);

  THStack* bm_fit_stack = (THStack*)fitFile.Get("bmextramm_stack");
  TH1D* bm_fit_hist = (TH1D*)bm_fit_stack->GetStack()->Last();
  bm_fit_data = new RooDataHist("bm_fit_data","bm_fit_data",RooArgSet(*m2),bm_fit_hist);

  variable = new RooCategory ("variable","variable");
  variable->defineType("jpsi");
  variable->defineType("bm");
  fit_data = new RooDataHist("fit_data","fit_data",
                             RooArgList(*m1,*m2),
                             Index(*variable),
                             Import("jpsi",*jpsi_fit_data),
                             Import("bm",*bm_fit_data));

  Bc_SIG_Mu = new RooRealVar ("Bc_SIG_Mu","Bc_SIG_Mu",0,2);
  Bc_SIG_Mu_SWITCHED = new RooRealVar ("Bc_SIG_Mu_SWITCHED","Bc_SIG_Mu_SWITCHED",0,2);
  Bc_SIG_Tau = new RooRealVar ("Bc_SIG_Tau","Bc_SIG_Tau",0,2);
  Bc_SIG_BadTau = new RooRealVar ("Bc_SIG_BadTau","Bc_SIG_BadTau",0,2);
  Bc_SIG_Tau_SWITCHED = new RooRealVar ("Bc_SIG_Tau_SWITCHED","Bc_SIG_Tau_SWITCHED",0,2);
  sig_data_full = new RooDataSet("data","data",sigDataTree,
                                 RooArgSet(*m1,*m2,*Bc_SIG_Mu,*Bc_SIG_Tau,
                                           *Bc_SIG_Mu_SWITCHED,*Bc_SIG_Tau_SWITCHED,*Bc_SIG_BadTau));
  jpsi_sig_data = (RooDataSet*)sig_data_full->reduce(Name("jpsi_sig_data"),
                                                     Title("jpsi_sig_data"),
                                                     SelectVars(RooArgSet(*m1)),
                                                     Cut("(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)"));
  bm_sig_data = (RooDataSet*)sig_data_full->reduce(Name("bm_sig_data"),
                                                   Title("bm_sig_data"),
                                                   SelectVars(RooArgSet(*m2)),
                                                     Cut("(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)"));

  Bc_BKG_B02JpsiX = new RooRealVar ("Bc_BKG_B02JpsiX","Bc_BKG_B02JpsiX",0,2);
  b0bkg_data_full = new RooDataSet("data","data",bkgDataTree,
                                 RooArgSet(*m1,*m2,*Bc_BKG_B02JpsiX));
  jpsi_b0bkg_data = (RooDataSet*)b0bkg_data_full->reduce(Name("jpsi_b0bkg_data"),
                                                     Title("jpsi_b0bkg_data"),
                                                     SelectVars(RooArgSet(*m1)),
                                                     Cut("Bc_BKG_B02JpsiX>0"));
  bm_b0bkg_data = (RooDataSet*)b0bkg_data_full->reduce(Name("bm_b0bkg_data"),
                                                   Title("bm_b0bkg_data"),
                                                   SelectVars(RooArgSet(*m2)),
                                                   Cut("Bc_BKG_B02JpsiX>0"));

  Bc_BKG_B2JpsiX = new RooRealVar ("Bc_BKG_B2JpsiX","Bc_BKG_B2JpsiX",0,2);
  bbkg_data_full = new RooDataSet("data","data",bkgDataTree,
                                  RooArgSet(*m1,*m2,*Bc_BKG_B2JpsiX));
  jpsi_bbkg_data = (RooDataSet*)bbkg_data_full->reduce(Name("jpsi_bbkg_data"),
                                                     Title("jpsi_bbkg_data"),
                                                     SelectVars(RooArgSet(*m1)),
                                                     Cut("Bc_BKG_B2JpsiX>0"));
  bm_bbkg_data = (RooDataSet*)bbkg_data_full->reduce(Name("bm_bbkg_data"),
                                                   Title("bm_bbkg_data"),
                                                   SelectVars(RooArgSet(*m2)),
                                                   Cut("Bc_BKG_B2JpsiX>0"));
  BBBKG = new RooRealVar ("BBBKG","BBBKG",0,2);
  comb_data_full = new RooDataSet("data","data",bkgDataTree,
                                  RooArgSet(*m1,*m2,*BBBKG));
  jpsi_comb_data = (RooDataSet*)comb_data_full->reduce(Name("jpsi_comb_data"),
                                                       Title("jpsi_comb_data"),
                                                       SelectVars(RooArgSet(*m1)),
                                                       Cut("(BBBKG>0)"));
  bm_comb_data = (RooDataSet*)comb_data_full->reduce(Name("bm_comb_data"),
                                                     Title("bm_comb_data"),
                                                     SelectVars(RooArgSet(*m2)),
                                                     Cut("(BBBKG>0)"));
  
  LowMassBKG = new RooRealVar ("LowMassBKG","LowMassBKG",0,2);
  lowmass_data_full = new RooDataSet("data","data",bkgDataTree,
                                     RooArgSet(*m1,*m2,*LowMassBKG));
  jpsi_lowmass_data = (RooDataSet*)lowmass_data_full->reduce(Name("jpsi_lowmass_data"),
                                                             Title("jpsi_lowmass_data"),
                                                             SelectVars(RooArgSet(*m1)),
                                                             Cut("(LowMassBKG>0)"));
  bm_lowmass_data = (RooDataSet*)lowmass_data_full->reduce(Name("bm_lowmass_data"),
                                                           Title("bm_lowmass_data"),
                                                           SelectVars(RooArgSet(*m2)),
                                                           Cut("(LowMassBKG>0)"));
  
  jpsi_sig_pdf = new RooKeysPdf ("jpsi_sig","jpsi sig pdf",
                                 *m1,
                                 *jpsi_sig_data,
                                 RooKeysPdf::NoMirror);
  bm_sig_pdf = new RooKeysPdf ("bm_sig","bm sig pdf",
                               *m2,
                               *bm_sig_data,
                               RooKeysPdf::NoMirror);
  jpsi_b0bkg_pdf = new RooKeysPdf ("jpsi_b0bkg","jpsi b0bkg pdf",
                                   *m1,
                                   *jpsi_b0bkg_data,
                                   RooKeysPdf::NoMirror);
  bm_b0bkg_pdf = new RooKeysPdf ("bm_b0bkg","bm b0bkg pdf",
                                 *m2,
                                 *bm_b0bkg_data,
                                 RooKeysPdf::NoMirror);
  jpsi_bbkg_pdf = new RooKeysPdf ("jpsi_bbkg","jpsi bbkg pdf",
                                  *m1,
                                  *jpsi_bbkg_data,
                                  RooKeysPdf::NoMirror);
  bm_bbkg_pdf = new RooKeysPdf ("bm_bbkg","bm bbkg pdf",
                                 *m2,
                                 *bm_bbkg_data,
                                 RooKeysPdf::NoMirror);
  jpsi_comb_pdf = new RooKeysPdf ("jpsi_comb","jpsi comb pdf",
                                  *m1,
                                  *jpsi_comb_data,
                                  RooKeysPdf::NoMirror);
  bm_comb_pdf = new RooKeysPdf ("bm_comb","bm comb pdf",
                                *m2,
                                *bm_comb_data,
                                RooKeysPdf::NoMirror);
  jpsi_lowmass_pdf = new RooKeysPdf ("jpsi_lowmass","jpsi lowmass pdf",
                                     *m1,
                                     *jpsi_lowmass_data,
                                     RooKeysPdf::NoMirror);
  bm_lowmass_pdf = new RooKeysPdf ("bm_lowmass","bm lowmass pdf",
                                   *m2,
                                   *bm_lowmass_data,
                                   RooKeysPdf::NoMirror);

  num_sig = new RooRealVar ("num_sig","num_sig",1,0,1E6);
  num_b0bkg = new RooRealVar ("num_b0bkg","num_b0bkg",1,0,1E6);
  num_bbkg = new RooRealVar ("num_bbkg","num_bbkg",1,0,1E6);
  num_comb = new RooRealVar ("num_comb","num_comb",1,0,1E6);
  num_lowmass = new RooRealVar ("num_lowmass","num_lowmass",1,0,1E6);
  jpsi_model = new RooAddPdf ("jpsi_model","jpsi_model",
                              RooArgList(*jpsi_sig_pdf,*jpsi_b0bkg_pdf,*jpsi_b0bkg_pdf,*jpsi_comb_pdf,*jpsi_lowmass_pdf),
                              RooArgList(*num_sig,*num_b0bkg,*num_bbkg,*num_comb,*num_lowmass));
  bm_model = new RooAddPdf ("bm_model","bm_model",
                            RooArgList(*bm_sig_pdf,*bm_b0bkg_pdf,*bm_bbkg_pdf,*bm_comb_pdf,*bm_lowmass_pdf),
                            RooArgList(*num_sig,*num_b0bkg,*num_bbkg,*num_comb,*num_lowmass));

  
  model = new RooSimultaneous ("model","model",*variable);
  model->addPdf(*jpsi_model,"jpsi");
  model->addPdf(*bm_model,"bm");
  
  cout << "Finished making model" << endl;
  model->fitTo(*fit_data,Extended(),Hesse(true),SumW2Error(true),Strategy(2),Minos(true),InitialHesse(false));
  cout << "Finished fitting" << endl;

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

