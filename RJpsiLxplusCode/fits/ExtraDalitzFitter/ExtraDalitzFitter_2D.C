#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooNDKeysPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

TTree *sigDataTree;
TTree *b0bkgDataTree;
TTree *bbkgDataTree;
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
RooDataSet* fit_data;
RooDataSet* sig_data;
RooDataSet* b0bkg_data;
RooDataSet* bbkg_data;
RooDataSet* comb_data;
RooDataSet* lowmass_data;
RooDataSet* other_data;
RooNDKeysPdf* sig_pdf;
RooNDKeysPdf* b0bkg_pdf;
RooNDKeysPdf* bbkg_pdf;
RooNDKeysPdf* comb_pdf;
RooNDKeysPdf* lowmass_pdf;
RooNDKeysPdf* other_pdf;
RooRealVar* num_sig;
RooRealVar* num_b0bkg;
RooRealVar* num_bbkg;
RooRealVar* num_comb;
RooRealVar* num_lowmass;
RooRealVar* num_other;
RooAddPdf* model;
RooPlot* m1frame;
RooPlot* m2frame;
TCanvas* canvas;
using namespace RooFit;

const double w_sig = 0.016;
const double w_b0bkg = 2.95;
const double w_bbkg = 3.77;

void ExtraDalitzFitter_2D ()
{

  const char m1str[100] = "Jpsi_SMALLESTDELTACHI2_MM";
  const char m2str[100] = "BachMu_SMALLESTCHI2_MM";

  // OPENING ROOT FILE
  TFile sigDataFile("Bc_SIG_Tau_Cands.root","READ");
  sigDataTree = (TTree*)sigDataFile.Get("DecayTree");
  TFile b0bkgDataFile("Bc_BKG_B02JpsiX_Cands.root","READ");
  b0bkgDataTree = (TTree*)b0bkgDataFile.Get("DecayTree");
  TFile bbkgDataFile("Bc_BKG_B2JpsiX_Cands.root","READ");
  bbkgDataTree = (TTree*)bbkgDataFile.Get("DecayTree");

  m1 = new RooRealVar (m1str,"m1",3200,6400);
  m2 = new RooRealVar (m2str,"m2",0,5000);
  Bc_SIG_Mu = new RooRealVar ("Bc_SIG_Mu","Bc_SIG_Mu",0,2);
  Bc_SIG_Mu_SWITCHED = new RooRealVar ("Bc_SIG_Mu_SWITCHED","Bc_SIG_Mu_SWITCHED",0,2);
  Bc_SIG_Tau = new RooRealVar ("Bc_SIG_Tau","Bc_SIG_Tau",0,2);
  Bc_SIG_BadTau = new RooRealVar ("Bc_SIG_BadTau","Bc_SIG_BadTau",0,2);
  Bc_SIG_Tau_SWITCHED = new RooRealVar ("Bc_SIG_Tau_SWITCHED","Bc_SIG_Tau_SWITCHED",0,2);
  Bc_BKG_B02JpsiX = new RooRealVar ("Bc_BKG_B02JpsiX","Bc_BKG_B02JpsiX",0,2);
  Bc_BKG_B2JpsiX = new RooRealVar ("Bc_BKG_B2JpsiX","Bc_BKG_B2JpsiX",0,2);
  BBBKG = new RooRealVar ("BBBKG","BBBKG",0,2);
  LowMassBKG = new RooRealVar ("LowMassBKG","LowMassBKG",0,2);

  cout << "Finished setting up variables" << endl;

  RooArgSet vars(*m1,*m2,
                 *Bc_SIG_Mu,*Bc_SIG_Mu_SWITCHED,
                 *Bc_SIG_Tau,*Bc_SIG_Tau_SWITCHED,*Bc_SIG_BadTau);
  vars.add(*Bc_BKG_B02JpsiX);
  vars.add(*Bc_BKG_B2JpsiX);
  vars.add(*BBBKG);
  vars.add(*LowMassBKG);

  cout << "Finished setting up variable lists" << endl;

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars);
  RooDataSet* sig_data_toadd = new RooDataSet("sig_data_toadd","sig_data_toadd",sigDataTree,vars);
  w_data->append(*sig_data_toadd);
  RooDataSet* b0bkg_data_toadd = new RooDataSet("b0bkg_data_toadd","b0bkg_data_toadd",b0bkgDataTree,vars);
  w_data->append(*b0bkg_data_toadd);
  RooDataSet* bbkg_data_toadd = new RooDataSet("bbkg_data_toadd","bbkg_data_toadd",bbkgDataTree,vars);
  w_data->append(*bbkg_data_toadd);

  fit_data = new RooDataSet("jpsi_fit_data","jpsi_fit_data",RooArgSet(*m1,*m2),Import(*w_data));
  
  cout << "Finished merging data" << endl;

  string sig_cut =
    "(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)";
  string other_cut =
    "! ( (Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)"
    " || (Bc_BKG_B02JpsiX>0) || (Bc_BKG_B2JpsiX>0) || (BBBKG>0) || (LowMassBKG>0) )";
  
  sig_data = new RooDataSet("sig_data","sig_data",RooArgSet(*m1,*m2),Import(*w_data),Cut(sig_cut.c_str()));
  b0bkg_data = new RooDataSet("b0bkg_data","b0bkg_data",RooArgSet(*m1,*m2),Import(*w_data),Cut("Bc_BKG_B02JpsiX>0"));
  bbkg_data = new RooDataSet("bbkg_data","bbkg_data",RooArgSet(*m1,*m2),Import(*w_data),Cut("Bc_BKG_B2JpsiX>0"));
  comb_data = new RooDataSet("comb_data","comb_data",RooArgSet(*m1,*m2),Import(*w_data),Cut("(BBBKG>0)"));
  lowmass_data = new RooDataSet("lowmass_data","lowmass_data",RooArgSet(*m1,*m2),Import(*w_data),Cut("(LowMassBKG>0)"));
  other_data = new RooDataSet("other_data","other_data",RooArgSet(*m1,*m2),Import(*w_data),Cut(other_cut.c_str()));
  
  sig_pdf = new RooNDKeysPdf ("sig","bm sig pdf",RooArgList(*m1,*m2),*sig_data);
  b0bkg_pdf = new RooNDKeysPdf ("b0bkg","bm b0bkg pdf",RooArgList(*m1,*m2),*b0bkg_data);
  bbkg_pdf = new RooNDKeysPdf ("bbkg","bm bbkg pdf",RooArgList(*m1,*m2),*bbkg_data);
  comb_pdf = new RooNDKeysPdf ("comb","bm comb pdf",RooArgList(*m1,*m2),*comb_data);
  lowmass_pdf = new RooNDKeysPdf ("lowmass","bm lowmass pdf",RooArgList(*m1,*m2),*lowmass_data);
  other_pdf = new RooNDKeysPdf ("other","bm other pdf",RooArgList(*m1,*m2),*other_data);
  
  num_sig = new RooRealVar ("num_sig","num_sig",1E4,1,1E6);
  num_b0bkg = new RooRealVar ("num_b0bkg","num_b0bkg",1E4,1,1E6);
  num_bbkg = new RooRealVar ("num_bbkg","num_bbkg",1E4,1,1E6);
  num_comb = new RooRealVar ("num_comb","num_comb",1E4,1,1E6);
  num_lowmass = new RooRealVar ("num_lowmass","num_lowmass",1,1,1E6);
  num_other = new RooRealVar ("num_other","num_other",1,1,1E6);

  model = new RooAddPdf ("model","model",
                         RooArgList(*sig_pdf,*b0bkg_pdf,*bbkg_pdf,*comb_pdf,*lowmass_pdf,*other_pdf),
                         RooArgList(*num_sig,*num_b0bkg,*num_bbkg,*num_comb,*num_lowmass,*num_other));

  
  cout << "Finished making fit model" << endl;

  model->fitTo(*fit_data,Extended(),Hesse(true),SumW2Error(true),Strategy(2),Minos(true),InitialHesse(false));

  cout << "Finished fitting" << endl;

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

