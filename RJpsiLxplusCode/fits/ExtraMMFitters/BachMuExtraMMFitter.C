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
#include "RooAddPdf.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

TTree *dataTree;
TTree *fitTree;
TTree *sigDataTree;
TTree *bkgDataTree;
RooRealVar* x;
RooRealVar* Bc_SIG_Mu;
RooRealVar* Bc_SIG_Tau;
RooRealVar* Bc_BKG_B2JpsiX;
RooRealVar* Bc_BKG_B02JpsiX;
RooRealVar* BBBKG;
RooDataSet* fit_data;
RooDataSet* sig_data_full;
RooDataSet* bkg_data_full;
RooDataSet* comb_data_full;
RooDataSet* sig_data;
RooDataSet* bkg_data;
RooDataSet* comb_data;
RooKeysPdf* sig_pdf;
RooKeysPdf* bkg_pdf;
RooKeysPdf* comb_pdf;
RooRealVar* num0;
RooRealVar* num1;
RooRealVar* num2;
RooAddPdf* model;
RooPlot* xframe;
using namespace RooFit;

void BachMuExtraMMFitter()
{

  const char varstr[100] = "BachMu_SMALLESTCHI2_MM";

  // OPENING ROOT FILE
//   TFile dataFile("result.root","READ");
//   dataTree = (TTree*)dataFile.Get("DecayTree");
  TFile fitFile("result.root","READ");
  fitTree = (TTree*)fitFile.Get("DecayTree");
  TFile sigDataFile("Bc_SIG_Tau_Cands.root","READ");
  sigDataTree = (TTree*)sigDataFile.Get("DecayTree");
  TFile bkgDataFile("Bc_BKG_Cands.root","READ");
  bkgDataTree = (TTree*)bkgDataFile.Get("DecayTree");

  x = new RooRealVar (varstr,"x",0,5000);

  fit_data = new RooDataSet("fit_data","fit_data",fitTree,RooArgSet(*x));

  Bc_SIG_Mu = new RooRealVar ("Bc_SIG_Mu","Bc_SIG_Mu",0,2);
  Bc_SIG_Tau = new RooRealVar ("Bc_SIG_Tau","Bc_SIG_Tau",0,2);
  sig_data_full = new RooDataSet("data","data",sigDataTree,
                                 RooArgSet(*x,*Bc_SIG_Mu,*Bc_SIG_Tau));
  sig_data = (RooDataSet*)sig_data_full->reduce(Name("sig_data"),Title("sig_data"),SelectVars(*x),
                                                Cut("(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0)"));
  Bc_BKG_B2JpsiX = new RooRealVar ("Bc_BKG_B2JpsiX","Bc_BKG_B2JpsiX",0,2);
  Bc_BKG_B02JpsiX = new RooRealVar ("Bc_BKG_B02JpsiX","Bc_BKG_B02JpsiX",0,2);
  bkg_data_full = new RooDataSet("data","data",bkgDataTree,
                                 RooArgSet(*x,*Bc_BKG_B2JpsiX,*Bc_BKG_B02JpsiX));
  bkg_data = (RooDataSet*)bkg_data_full->reduce(Name("bkg_data"),Title("bkg_data"),SelectVars(*x),
                                       Cut("(Bc_BKG_B2JpsiX>0) || (Bc_BKG_B02JpsiX>0)"));
  BBBKG = new RooRealVar ("BBBKG","BBBKG",0,2);
  comb_data_full = new RooDataSet("data","data",bkgDataTree,
                                 RooArgSet(*x,*BBBKG));
  comb_data = (RooDataSet*)comb_data_full->reduce(Name("comb_data"),Title("comb_data"),SelectVars(*x),
                                                  Cut("(BBBKG>0)"));
  
  sig_pdf = new RooKeysPdf ("sig","sig pdf",*x,*sig_data,RooKeysPdf::NoMirror);
  bkg_pdf = new RooKeysPdf ("bkg","bkg pdf",*x,*bkg_data,RooKeysPdf::NoMirror);
  comb_pdf = new RooKeysPdf ("comb","comb pdf",*x,*comb_data,RooKeysPdf::NoMirror);
  num0 = new RooRealVar ("num0","num0",1,0,1E6);
  num1 = new RooRealVar ("num1","num1",1,0,1E6);
  num2 = new RooRealVar ("num2","num2",1,0,1E6);
  model = new RooAddPdf ("model","model",RooArgList(*sig_pdf,*bkg_pdf,*comb_pdf),RooArgList(*num0,*num1,*num2));

  model->fitTo(*fit_data,Extended());
  xframe = x->frame(x->getBins());
  fit_data->plotOn(xframe);
  model->plotOn(xframe);
  model->plotOn(xframe,Components("sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(xframe,Components("bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(xframe,Components("comb"),LineStyle(kDashed),LineColor(kCyan));
  xframe->Draw();

//   TCanvas *c = new TCanvas("c","c",800,800);
//   c->cd();
  return;
  
}

