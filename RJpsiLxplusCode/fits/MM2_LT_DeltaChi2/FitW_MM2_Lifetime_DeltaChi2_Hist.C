#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

TTree *dataTree;
RooRealVar* mm2;
RooRealVar* lt;
RooRealVar* dchi2;
RooRealVar* w;
RooRealVar* MyBkgTag;
RooDataHist* mu_hist;
RooDataHist* tau_hist;
RooDataHist* b0_hist;
RooDataHist* b_hist;
RooDataHist* comb_hist;
// RooDataHist* lowmass_hist;
// RooDataHist* other_hist;
RooDataHist* mu_hist2;
RooDataHist* tau_hist2;
RooDataHist* b0_hist2;
RooDataHist* b_hist2;
RooDataHist* comb_hist2;
// RooDataHist* lowmass_hist2;
// RooDataHist* other_hist2;
// RooDataSet* mu_data;
// RooDataSet* tau_data;
// RooDataSet* b0_data;
// RooDataSet* b_data;
// RooDataSet* comb_data;
// RooDataSet* lowmass_data;
// RooDataSet* other_data;
RooProdPdf* mu_pdf;
RooProdPdf* tau_pdf;
RooProdPdf* b0_pdf;
RooProdPdf* b_pdf;
RooProdPdf* comb_pdf;
// RooProdPdf* lowmass_pdf;
// RooProdPdf* other_pdf;
RooRealVar* num_mu;
RooRealVar *Rtau;
RooFormulaVar* num_tau;
RooRealVar* num_b0;
RooRealVar* num_b;
RooRealVar* num_comb;
// RooRealVar* num_lowmass;
// RooRealVar* num_other;
RooAddPdf* model;
RooPlot* mm2frame;
RooPlot* ltframe;
RooPlot* dchi2frame;
RooMCStudy* mcs;
RooPlot* nmu_frame;
RooPlot* nmu_eframe;
RooPlot* nmu_pframe;
RooPlot* Rtau_frame;
RooPlot* Rtau_eframe;
RooPlot* Rtau_pframe;
RooPlot* nb0_frame;
RooPlot* nb0_eframe;
RooPlot* nb0_pframe;
RooPlot* nb_frame;
RooPlot* nb_eframe;
RooPlot* nb_pframe;
RooPlot* ncomb_frame;
RooPlot* ncomb_eframe;
RooPlot* ncomb_pframe;

TCanvas* canvas;
using namespace RooFit;

void FitW_MM2_Lifetime_DeltaChi2 ()
{

  const char mm2str[10] = "MissMass2";
  const char ltstr[9] = "Lifetime";
  const char dchi2str[10] = "DeltaChi2";
  const char wstr[2] = "W";
  const char bkgstr[9] = "MyBkgTag";

  // -------------------------
  // OPENING ROOT FILES
  // -------------------------

  cout << "Opening root files ... " << endl;


  TFile dataFile("Bc_MC.root","READ");
  dataTree = (TTree*)dataFile.Get("DecayTree");

  // -------------------------
  // CREATEING ROOFIT VARIABLES AND DATASETS
  // -------------------------

  cout << "Creating roofit variables and datasets ... " << endl;

  mm2 = new RooRealVar (mm2str,"mm2",-5,15);
  lt = new RooRealVar (ltstr,"lt",0.0,8);
  dchi2 = new RooRealVar (dchi2str,"dchi2",0.0,25.0);
  w = new RooRealVar (wstr,"w",0.0,10);
  MyBkgTag = new RooRealVar(bkgstr,"tag",0.0);

  RooArgSet vars(*mm2,*lt,*dchi2,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));

  string mu_cut = "MyBkgTag % 100 == 0";
  string tau_cut = "MyBkgTag % 100 == 1";
  string b0_cut = "MyBkgTag % 1000 == 2";
  string b_cut = "MyBkgTag % 1000 == 102";
  string bunk_cut = "MyBkgTag % 1000 == 202"; // won't use
  string mispid_cut = "MyBkgTag % 100 == 3"; // won't use
  string comb_cut = "MyBkgTag % 100 == 4";
  string pv_cut = "MyBkgTag % 100 == 5"; // won't use
  string other_cut = "(MyBkgTag % 100 == 6) || (MyBkgTag % 100 == -1)"; // won't use
  
  mm2->setBins(100);
  lt->setBins(100);
  dchi2->setBins(100);

  mu_hist = new RooDataHist("mu_hist","mu_hist",RooArgSet(*mm2,*lt));
  mu_hist->add(*w_data,mu_cut.c_str());
  tau_hist = new RooDataHist("tau_hist","tau_hist",RooArgSet(*mm2,*lt));
  tau_hist->add(*w_data,tau_cut.c_str());
  b0_hist = new RooDataHist("b0_hist","b0_hist",RooArgSet(*mm2,*lt));
  b0_hist->add(*w_data,b0_cut.c_str());
  b_hist = new RooDataHist("b_hist","b_hist",RooArgSet(*mm2,*lt));
  b_hist->add(*w_data,b_cut.c_str());
  comb_hist = new RooDataHist("comb_hist","comb_hist",RooArgSet(*mm2,*lt));
  comb_hist->add(*w_data,comb_cut.c_str());
  
  mu_hist2 = new RooDataHist("mu_hist2","mu_hist2",RooArgSet(*dchi2));
  mu_hist2->add(*w_data,mu_cut.c_str());
  tau_hist2 = new RooDataHist("tau_hist2","tau_hist2",RooArgSet(*dchi2));
  tau_hist2->add(*w_data,tau_cut.c_str());
  b0_hist2 = new RooDataHist("b0_hist2","b0_hist2",RooArgSet(*dchi2));
  b0_hist2->add(*w_data,b0_cut.c_str());
  b_hist2 = new RooDataHist("b_hist2","b_hist2",RooArgSet(*dchi2));
  b_hist2->add(*w_data,b_cut.c_str());
  comb_hist2 = new RooDataHist("comb_hist2","comb_hist2",RooArgSet(*dchi2));
  comb_hist2->add(*w_data,comb_cut.c_str());
  
//   mu_data = new RooDataSet("mu_data","mu_data",RooArgSet(*dchi2,*w),Import(*w_data),Cut(mu_cut.c_str()),WeightVar(*w));
//   tau_data = new RooDataSet("tau_data","tau_data",RooArgSet(*dchi2,*w),Import(*w_data),Cut(tau_cut.c_str()),WeightVar(*w));
//   b0_data = new RooDataSet("b0_data","b0_data",RooArgSet(*dchi2,*w),Import(*w_data),Cut(b0_cut.c_str()),WeightVar(*w));
//   b_data = new RooDataSet("b_data","b_data",RooArgSet(*dchi2,*w),Import(*w_data),Cut(b_cut.c_str()),WeightVar(*w));
//   comb_data = new RooDataSet("comb_data","comb_data",RooArgSet(*dchi2,*w),Import(*w_data),Cut(comb_cut.c_str()),WeightVar(*w));

  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;

  RooHistPdf* mu_2d_pdf = new RooHistPdf ("mu_2d_pdf","mu 2d_pdf",RooArgSet(*mm2,*lt),*mu_hist,2);
  RooHistPdf* tau_2d_pdf = new RooHistPdf ("tau_2d_pdf","tau 2d_pdf",RooArgSet(*mm2,*lt),*tau_hist,2);
  RooHistPdf* b0_2d_pdf = new RooHistPdf ("b0_2d_pdf","b0 2d_pdf",RooArgSet(*mm2,*lt),*b0_hist,2);
  RooHistPdf* b_2d_pdf = new RooHistPdf ("b_2d_pdf","b 2d_pdf",RooArgSet(*mm2,*lt),*b_hist,2);
  RooHistPdf* comb_2d_pdf = new RooHistPdf ("comb_2d_pdf","comb 2d_pdf",RooArgSet(*mm2,*lt),*comb_hist,2);

  RooHistPdf* mu_dchi2_pdf = new RooHistPdf ("mu_dchi2_pdf","mu dchi2_pdf",RooArgSet(*dchi2),*mu_hist2,2);
  RooHistPdf* tau_dchi2_pdf = new RooHistPdf ("tau_dchi2_pdf","tau dchi2_pdf",RooArgSet(*dchi2),*tau_hist2,2);
  RooHistPdf* b0_dchi2_pdf = new RooHistPdf ("b0_dchi2_pdf","b0 dchi2_pdf",RooArgSet(*dchi2),*b0_hist2,2);
  RooHistPdf* b_dchi2_pdf = new RooHistPdf ("b_dchi2_pdf","b dchi2_pdf",RooArgSet(*dchi2),*b_hist2,2);
  RooHistPdf* comb_dchi2_pdf = new RooHistPdf ("comb_dchi2_pdf","comb dchi2_pdf",RooArgSet(*dchi2),*comb_hist2,2);

  mu_pdf = new RooProdPdf ("mu","mu pdf",RooArgList(*mu_2d_pdf,*mu_dchi2_pdf));
  tau_pdf = new RooProdPdf ("tau","tau pdf",RooArgList(*tau_2d_pdf,*tau_dchi2_pdf));
  b0_pdf = new RooProdPdf ("b0","b0 pdf",RooArgList(*b0_2d_pdf,*b0_dchi2_pdf));
  b_pdf = new RooProdPdf ("b","b pdf",RooArgList(*b_2d_pdf,*b_dchi2_pdf));
  comb_pdf = new RooProdPdf ("comb","comb pdf",RooArgList(*comb_2d_pdf,*comb_dchi2_pdf));
  
  num_mu = new RooRealVar ("num_mu","num_mu",1E5,1,2E5);
  Rtau = new RooRealVar ("Rtau","Rtau",0.02,1E-10,1.0);
  num_tau = new RooFormulaVar ("num_tau","num_tau","num_mu * Rtau",RooArgList(*num_mu,*Rtau));
  num_b0 = new RooRealVar ("num_b0","num_b0",1E4,1,2E5);
  num_b = new RooRealVar ("num_b","num_b",2.5E4,1,2E5);
  num_comb = new RooRealVar ("num_comb","num_comb",3.5E4,1,2E5);

  model = new RooAddPdf ("model","model",
                         RooArgList(*mu_pdf,*tau_pdf,*b0_pdf,*b_pdf,*comb_pdf),
                         RooArgList(*num_mu,*num_tau,*num_b0,*num_b,*num_comb));

  // -------------------------
  // GENERATING AND FITTING TOY MC
  // -------------------------

  cout << "generating and fitting toy MC ... " << endl;

  /* I'll set the numbers to expected values and generate toy MC
   */

  mcs = new RooMCStudy(*model,RooArgSet(*mm2,*lt,*dchi2),Binned(),FitOptions(Save(true),Minos(true),Strategy(2)));
  RooChi2MCSModule chi2mod;
  mcs->addModule(chi2mod);
  
  mcs->generateAndFit(100); // number of events taken to be 500?

  return;  
}

