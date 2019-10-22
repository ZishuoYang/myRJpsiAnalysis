#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
// #include "RooHistPdf.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

TTree *fitTree;
TTree *sigDataTree;
TTree *bkgDataTree;
RooRealVar* m1;
RooRealVar* m2;
RooRealVar* Bc_SIG_Mu;
RooRealVar* Bc_SIG_Mu_SWITCHED;
RooRealVar* Bc_SIG_Tau_SWITCHED;
RooRealVar* Bc_SIG_Tau_BadTau;
RooRealVar* Bc_BKG_B2JpsiX;
RooRealVar* Bc_BKG_B02JpsiX;
RooRealVar* BBBKG;
RooRealVar* LowMassBKG;
RooDataSet* fit_data;
RooDataSet* sig_data_full;
RooDataSet* bkg_data_full;
RooDataSet* comb_data_full;
RooDataSet* sig_data;
RooDataSet* bkg_data;
RooDataSet* comb_data;
RooNDKeysPdf* sig_pdf;
RooNDKeysPdf* bkg_pdf;
RooNDKeysPdf* comb_pdf;
RooRealVar* num0;
RooRealVar* num1;
RooRealVar* num2;
RooAddPdf* model;
RooPlot* m1frame;
RooPlot* m2frame;
using namespace RooFit;

void ExtraDalitzFitter()
{

  const char m1str[100] = "Jpsi_SMALLESTDELTACHI2_MM";
  const char m2str[100] = "BachMu_SMALLESTCHI2_MM";

  // OPENING ROOT FILE
  TFile fitFile("result.root","READ");
  fitTree = (TTree*)fitFile.Get("DecayTree");
  TFile sigDataFile("Bc_SIG_Tau_Cands.root","READ");
  sigDataTree = (TTree*)sigDataFile.Get("DecayTree");
  TFile bkgDataFile("Bc_BKG_Cands.root","READ");
  bkgDataTree = (TTree*)bkgDataFile.Get("DecayTree");

  m1 = new RooRealVar (m1str,"m1",3200,6400);
  m2 = new RooRealVar (m2str,"m2",0,5000);

  fit_data = new RooDataSet("fit_data","fit_data",fitTree,RooArgSet(*m1,*m2));
  
  Bc_SIG_Mu = new RooRealVar ("Bc_SIG_Mu","Bc_SIG_Mu",0,2);
  Bc_SIG_Mu_SWITCHED = new RooRealVar ("Bc_SIG_Mu_SWITCHED","Bc_SIG_Mu_SWITCHED",0,2);
  Bc_SIG_Tau = new RooRealVar ("Bc_SIG_Tau","Bc_SIG_Tau",0,2);
  Bc_SIG_BadTau = new RooRealVar ("Bc_SIG_BadTau","Bc_SIG_BadTau",0,2);
  Bc_SIG_Tau_SWITCHED = new RooRealVar ("Bc_SIG_Tau_SWITCHED","Bc_SIG_Tau_SWITCHED",0,2);
  sig_data_full = new RooDataSet("data","data",fitTree,//sigDataTree,
                                 RooArgSet(*m1,*m2,*Bc_SIG_Mu,*Bc_SIG_Tau,
                                           *Bc_SIG_Mu_SWITCHED,*Bc_SIG_Tau_SWITCHED,*Bc_SIG_BadTau));
  sig_data = (RooDataSet*)sig_data_full->reduce(Name("sig_data"),
                                                Title("sig_data"),
                                                SelectVars(RooArgSet(*m1,*m2)),
                                                Cut("(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0)"));
  Bc_BKG_B2JpsiX = new RooRealVar ("Bc_BKG_B2JpsiX","Bc_BKG_B2JpsiX",0,2);
  Bc_BKG_B02JpsiX = new RooRealVar ("Bc_BKG_B02JpsiX","Bc_BKG_B02JpsiX",0,2);
  bkg_data_full = new RooDataSet("data","data",fitTree,//bkgDataTree,
                                 RooArgSet(*m1,*m2,*Bc_BKG_B2JpsiX,*Bc_BKG_B02JpsiX));
  bkg_data = (RooDataSet*)bkg_data_full->reduce(Name("bkg_data"),
                                                Title("bkg_data"),
                                                SelectVars(RooArgSet(*m1,*m2)),
                                                Cut("(Bc_BKG_B2JpsiX>0) || (Bc_BKG_B02JpsiX>0)"));
  BBBKG = new RooRealVar ("BBBKG","BBBKG",0,2);
  comb_data_full = new RooDataSet("data","data",fitTree,//bkgDataTree,
                                  RooArgSet(*m1,*m2,*BBBKG));
  comb_data = (RooDataSet*)comb_data_full->reduce(Name("comb_data"),
                                                  Title("comb_data"),
                                                  SelectVars(RooArgSet(*m1,*m2)),
                                                  Cut("(BBBKG>0)"));
  LowMassBKG = new RooRealVar ("LowMassBKG","LowMassBKG",0,2);
  comb_data_full = new RooDataSet("data","data",fitTree,//bkgDataTree,
                                  RooArgSet(*m1,*m2,*BBBKG));
  comb_data = (RooDataSet*)comb_data_full->reduce(Name("comb_data"),
                                                  Title("comb_data"),
                                                  SelectVars(RooArgSet(*m1,*m2)),
                                                  Cut("(LowMassBKG>0)"));
  
  sig_pdf = new RooNDKeysPdf ("sig","sig pdf",
                              RooArgSet(*m1,*m2),
                              *sig_data,
                              RooKeysPdf::NoMirror);
  bkg_pdf = new RooNDKeysPdf ("bkg","bkg pdf",
                              RooArgSet(*m1,*m2),
                              *bkg_data,
                              RooKeysPdf::NoMirror);
  comb_pdf = new RooNDKeysPdf ("comb","comb pdf",
                               RooArgSet(*m1,*m2),
                               *comb_data,
                               RooKeysPdf::NoMirror);
  num0 = new RooRealVar ("num0","num0",1,0,1E6);
  num1 = new RooRealVar ("num1","num1",1,0,1E6);
  num2 = new RooRealVar ("num2","num2",1,0,1E6);
//   model = new RooAddPdf ("model","model",
//                          RooArgList(*sig_pdf,*bkg_pdf,*comb_pdf),
//                          RooArgList(*num0,*num1,*num2));
  model = new RooAddPdf ("model","model",
                         RooArgList(*sig_pdf,*bkg_pdf),
                         RooArgList(*num0,*num1));
  
  cout << "Finished making model" << endl;
  model->fitTo(*fit_data,Extended());
  cout << "Finished fitting" << endl;
//   m1frame = m1->frame(m1->getBins());
//   fit_data->plotOn(m1frame);
//   model->plotOn(m1frame);
//   model->plotOn(m1frame,Components("sig"),LineStyle(kDashed),LineColor(kRed));
//   model->plotOn(m1frame,Components("bkg"),LineStyle(kDashed),LineColor(kMagenta));
//   model->plotOn(m1frame,Components("comb"),LineStyle(kDashed),LineColor(kCyan));
//   m1frame->Draw();

//   TCanvas *c = new TCanvas("c","c",800,800);
//   c->cd();
  return;
  
}

