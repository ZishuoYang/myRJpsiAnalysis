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
#include "RooMCStudy.h"
#include "RooChi2MCSModule.h"

#include <iostream>
#include <string>
using namespace std;

TTree *dataTree;
RooRealVar* q2mmm2;
RooRealVar* lt;
RooRealVar* w;
RooRealVar* MyBkgTag;
RooDataHist* mu_hist;
RooDataHist* tau_hist;
RooDataHist* b0_hist;
RooDataHist* b_hist;
RooDataHist* comb_hist;
// RooDataHist* lowmass_data;
// RooDataHist* other_data;
RooHistPdf* mu_pdf;
RooHistPdf* tau_pdf;
RooHistPdf* b0_pdf;
RooHistPdf* b_pdf;
RooHistPdf* comb_pdf;
// RooHistPdf* lowmass_pdf;
// RooHistPdf* other_pdf;
RooRealVar* num_mu;
RooRealVar *Rtau;
RooFormulaVar* num_tau;
RooRealVar* num_b0;
RooRealVar* num_b;
RooRealVar* num_comb;
// RooRealVar* num_lowmass;
// RooRealVar* num_other;
RooAddPdf* model;
RooMCStudy* mcs;
using namespace RooFit;

void FitW_Q2mMM2_Lifetime ()
{

  const char q2mmm2str[7] = "Q2mMM2";
  const char ltstr[12] = "ExpLifetime"; 
  const char wstr[7] = "weight";
  const char bkgstr[9] = "MyBkgTag";

  // -------------------------
  // OPENING ROOT FILES
  // -------------------------

  cout << "Opening root files ... " << endl;

  TFile dataFile("Bc_MC.root","READ");
  dataTree = (TTree*)dataFile.Get("DecayTree");
  dataTree->AddFriend("weightTree","Bc_MC_Weights.root");

  // -------------------------
  // CREATEING ROOFIT VARIABLES AND DATASETS
  // -------------------------

  cout << "Creating roofit variables and datasets ... " << endl;

  q2mmm2 = new RooRealVar (q2mmm2str,"q2mmm2",-1,15);
  lt = new RooRealVar (ltstr,"lt",0.0,0.8);
  w = new RooRealVar (wstr,"w",0.0,10.0);
  MyBkgTag = new RooRealVar(bkgstr,"tag",0.0);

  RooArgSet vars(*q2mmm2,*lt,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));

//   RooDataSet* w_data = new RooDataSet("w_data","w_data",vars);
//   RooDataSet* mu_data_toadd = new RooDataSet("mu_data_toadd","mu_data_toadd",muDataTree,vars);
//   w_data->append(*mu_data_toadd);
//   RooDataSet* tau_data_toadd = new RooDataSet("tau_data_toadd","tau_data_toadd",tauDataTree,vars);
//   w_data->append(*tau_data_toadd);
//   RooDataSet* b0_data_toadd = new RooDataSet("b0_data_toadd","b0_data_toadd",b0DataTree,vars);
//   w_data->append(*b0_data_toadd);
//   RooDataSet* b_data_toadd = new RooDataSet("b_data_toadd","b_data_toadd",bDataTree,vars);
//   w_data->append(*b_data_toadd);

  string mu_cut = "MyBkgTag % 100 == 0";
  string tau_cut = "MyBkgTag % 100 == 1";
  string b0_cut = "MyBkgTag % 1000 == 2";
  string b_cut = "MyBkgTag % 1000 == 102";
  string bunk_cut = "MyBkgTag % 1000 == 202"; // won't use
  string mispid_cut = "MyBkgTag % 100 == 3"; // won't use
  string comb_cut = "MyBkgTag % 100 == 4";
  string pv_cut = "MyBkgTag % 100 == 5"; // won't use
  string other_cut = "(MyBkgTag % 100 == 6) || (MyBkgTag % 100 == -1)"; // won't use
  
  // How many bins are enough?
  q2mmm2->setBins(20);
  lt->setBins(20);

  RooArgSet fvarsset(*q2mmm2,*lt);
  mu_hist = new RooDataHist("mu_hist","mu_hist",fvarsset);
  mu_hist->add(*w_data,mu_cut.c_str());
  tau_hist = new RooDataHist("tau_hist","tau_hist",fvarsset);
  tau_hist->add(*w_data,tau_cut.c_str());
  b0_hist = new RooDataHist("b0_hist","b0_hist",fvarsset);
  b0_hist->add(*w_data,b0_cut.c_str());
  b_hist = new RooDataHist("b_hist","b_hist",fvarsset);
  b_hist->add(*w_data,b_cut.c_str());
  comb_hist = new RooDataHist("comb_hist","comb_hist",fvarsset);
  comb_hist->add(*w_data,comb_cut.c_str());
  
  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;

  mu_pdf = new RooHistPdf ("mu","mu pdf",fvarsset,*mu_hist,3);
  tau_pdf = new RooHistPdf ("tau","tau pdf",fvarsset,*tau_hist,3);
  b0_pdf = new RooHistPdf ("b0","b0 pdf",fvarsset,*b0_hist,3);
  b_pdf = new RooHistPdf ("b","b pdf",fvarsset,*b_hist,3);
  comb_pdf = new RooHistPdf ("comb","comb pdf",fvarsset,*comb_hist,3);
  
   num_mu = new RooRealVar ("num_mu","num_mu",0.5E5,1,2E5);
   Rtau = new RooRealVar ("Rtau","Rtau",0.02,1E-10,1.0);
   num_tau = new RooFormulaVar ("num_tau","num_tau","num_mu * Rtau",RooArgList(*num_mu,*Rtau));
   num_b0 = new RooRealVar ("num_b0","num_b0",0.5E4,1,2E5);
   num_b = new RooRealVar ("num_b","num_b",1.25E4,1,2E5);
   num_comb = new RooRealVar ("num_comb","num_comb",1.75E4,1,2E5);

  model = new RooAddPdf ("model","model",
                         RooArgList(*mu_pdf,*tau_pdf,*b0_pdf,*b_pdf,*comb_pdf),
                         RooArgList(*num_mu,*num_tau,*num_b0,*num_b,*num_comb));

  // -------------------------
  // GENERATING AND FITTING TOY MC
  // -------------------------

  cout << "generating and fitting toy MC ... " << endl;

  /* I'll set the numbers to expected values and generate toy MC
   */

  mcs = new RooMCStudy(*model,fvarsset,Binned(true),Extended(true),FitOptions(Save(true),Minos(true),Strategy(2)));
  RooChi2MCSModule chi2mod;
  mcs->addModule(chi2mod);
  
  mcs->generateAndFit(1000,0,true); // number of events taken to be 500?

  return;  
}

