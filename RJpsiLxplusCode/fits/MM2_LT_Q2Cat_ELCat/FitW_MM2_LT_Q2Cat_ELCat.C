#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooThresholdCategory.h"
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
RooRealVar* mm2;
RooRealVar* lt;
RooRealVar* q2;
RooCategory* q2cat;
RooRealVar* invmm;
RooCategory* invmmcat;
RooRealVar* el;
RooCategory* elcat;
RooRealVar* w;
RooRealVar* MyBkgTag;
RooDataHist* mu_genhist;
RooDataHist* tau_genhist;
RooDataHist* b_genhist;
RooDataHist* fd_genhist;
RooDataHist* pv_genhist;
RooDataHist* ghost_genhist;
RooDataHist* comb_genhist;
RooHistPdf* mu_genpdf;
RooHistPdf* tau_genpdf;
RooHistPdf* fd_genpdf;
RooHistPdf* b_genpdf;
RooHistPdf* pv_genpdf;
RooHistPdf* ghost_genpdf;
RooHistPdf* comb_genpdf;
RooRealVar* num_mu;
RooRealVar *rtau;
RooFormulaVar* num_tau;
RooRealVar *rfd;
RooFormulaVar* num_fd;
RooRealVar* num_b;
RooRealVar* num_pv;
RooRealVar* num_ghost;
RooRealVar* num_comb;
RooAddPdf* gen_model;
RooMCStudy* mcs;
RooDataHist* gd;
RooAbsReal* nll;
RooPlot* frame;
RooFitResult* r;
using namespace RooFit;

void FitW_MM2_LT_Q2Cat_ELCat ()
{

  //  const char wstr[7] = "weight*(MyBkgTag%10 < 5) + W*(MyBkgTag%10 >= 5)";
  const char wstr[150] = "weight*(Bc_SMALLESTDELTACHI2==-1 || Bc_SMALLESTDELTACHI2>5)";
  
  const char bkgstr[9] = "MyBkgTag";
  const char mm2str[10] = "MissMass2";
  const char ltstr[12] = "LogLifetime"; // or ExpLifetime
  const char q2str[3] = "Q2";
  const char invmmstr[6] = "Bc_MM";
  const char elstr[13] = "BachMuEnergy";

  // -------------------------
  // OPENING ROOT FILES
  // -------------------------

  cout << "Opening root files ... " << endl;

  TFile dataFile("Bc_MC.root","READ");
  dataTree = (TTree*)dataFile.Get("DecayTree");
  dataTree->AddFriend("weightTree","Bc_MCW.root");

  // -------------------------
  // CREATEING ROOFIT VARIABLES AND DATASETS
  // -------------------------

  cout << "Creating roofit variables and datasets ... " << endl;

  w = new RooRealVar (wstr,"w",0.0,10.0);
  MyBkgTag = new RooRealVar(bkgstr,"tag",0.0);
  mm2 = new RooRealVar (mm2str,"mm2",-3.0,9.0);
  lt = new RooRealVar (ltstr,"lt",-2.2,2.0);
  q2 = new RooRealVar (q2str,"q2",-5.0,10.4);
  RooThresholdCategory* q2thrcat = new RooThresholdCategory("q2thrcat","q2thrcat",*q2,"High");
  q2thrcat->addThreshold(10.4,"High");
  q2thrcat->addThreshold(7.0,"Medium");
  q2thrcat->addThreshold(4.0,"Low");
  el = new RooRealVar (elstr,"el",0.1,3.0);
  RooThresholdCategory* elthrcat = new RooThresholdCategory("elthrcat","elthrcat",*el,"High");
  elthrcat->addThreshold(3.0,"High");
  elthrcat->addThreshold(1.75,"Medium");
  elthrcat->addThreshold(0.75,"Low");
//   invmm = new RooRealVar (invmmstr,"invmm",3200,6300);
//   RooThresholdCategory* invmmthrcat = new RooThresholdCategory("invmmthrcat","invmmthrcat",*invmm,"AboveB");
//   invmmthrcat->addThreshold(5280,"BelowB");

  RooArgSet vars(*mm2,*lt,*q2,*el,*w,*MyBkgTag);
  //  RooArgSet vars(*mm2,*lt,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));
  dataFile.Close();
  q2cat = (RooCategory*)w_data->addColumn(*q2thrcat);
  elcat = (RooCategory*)w_data->addColumn(*elthrcat);
  //  invmmcat = (RooCategory*)w_data->addColumn(*invmmthrcat);

  string allcut = "";
  string mu_cut = "MyBkgTag == 0" + allcut;
  string tau_cut = "MyBkgTag == 1" + allcut;
  string fd_cut = "MyBkgTag == 100" + allcut;
  string b_cut = "MyBkgTag % 10 == 2" + allcut;
  string pv_cut = "MyBkgTag % 100 == 5"; // won't use
  string ghost_cut = "MyBkgTag % 100 == 6"; // won't use
  string comb_cut = "MyBkgTag % 10 == 4" + allcut;
  
  // How many bins are enough?
  mm2->setBins(100);
  lt->setBins(100);

  RooArgSet fvarsset(*mm2,*lt,*q2cat,*elcat);
  //  RooArgSet fvarsset(*mm2,*lt);
  mu_genhist = new RooDataHist("mu_genhist","mu_genhist",fvarsset);
  mu_genhist->add(*w_data,mu_cut.c_str());
  tau_genhist = new RooDataHist("tau_genhist","tau_genhist",fvarsset);
  tau_genhist->add(*w_data,tau_cut.c_str());
  fd_genhist = new RooDataHist("fd_genhist","fd_genhist",fvarsset);
  fd_genhist->add(*w_data,fd_cut.c_str());
  b_genhist = new RooDataHist("b_genhist","b_genhist",fvarsset);
  b_genhist->add(*w_data,b_cut.c_str());
  pv_genhist = new RooDataHist("pv_genhist","pv_genhist",fvarsset);
  pv_genhist->add(*w_data,pv_cut.c_str());
  ghost_genhist = new RooDataHist("ghost_genhist","ghost_genhist",fvarsset);
  ghost_genhist->add(*w_data,ghost_cut.c_str());
  comb_genhist = new RooDataHist("comb_genhist","comb_genhist",fvarsset);
  comb_genhist->add(*w_data,comb_cut.c_str());

  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;
 
  mu_genpdf = new RooHistPdf ("mugen","mu genpdf",fvarsset,*mu_genhist,0);
  tau_genpdf = new RooHistPdf ("taugen","tau genpdf",fvarsset,*tau_genhist,0);
  fd_genpdf = new RooHistPdf ("fdgen","fd genpdf",fvarsset,*fd_genhist,0);
  b_genpdf = new RooHistPdf ("bgen","b genpdf",fvarsset,*b_genhist,0);
  pv_genpdf = new RooHistPdf ("pvgen","pv genpdf",fvarsset,*pv_genhist,0);
  ghost_genpdf = new RooHistPdf ("ghostgen","ghost genpdf",fvarsset,*ghost_genhist,0);
  comb_genpdf = new RooHistPdf ("combgen","comb genpdf",fvarsset,*comb_genhist,0);

  double factor = 0.10;
  double theory = 21.1/11.2;
  num_mu = new RooRealVar ("num_mu","num_mu",factor*theory*4.68e4,1,2E5);
  rtau = new RooRealVar ("rtau","rtau",0.0237,1E-10,1.0);
  num_tau = new RooFormulaVar ("num_tau","num_tau","num_mu * rtau",RooArgList(*num_mu,*rtau));
  rfd = new RooRealVar ("rfd","rfd",0.118,1E-10,1.0);
  num_fd = new RooFormulaVar ("num_fd","num_fd","num_mu * rfd",RooArgList(*num_mu,*rfd));
  num_b = new RooRealVar ("num_b","num_b",factor*2.6e4,1,2E5);
  num_pv = new RooRealVar ("num_pv","num_pv",factor*3e3,1,2E5);
  num_ghost = new RooRealVar ("num_ghost","num_ghost",factor*420,1,2E5);
  num_comb = new RooRealVar ("num_comb","num_comb",factor*1.82E4,1,2E5);

  gen_model = new RooAddPdf ("gen_model","gen_model",
                             RooArgList(*mu_genpdf,*tau_genpdf,*fd_genpdf,*b_genpdf,*pv_genpdf),//,*ghost_genpdf,*comb_genpdf),
                             RooArgList(*num_mu,*num_tau,*num_fd,*num_b,*num_pv));//,*num_ghost,*num_comb));

  // -------------------------
  // GENERATING AND FITTING TOY MC
  // -------------------------

  cout << "generating and fitting toy MC ... " << endl;

  mcs = new RooMCStudy(*gen_model,fvarsset,Optimize(0),Binned(true),Extended(true),FitOptions(Save(true),Minos(true),Strategy(2)));
  RooChi2MCSModule chi2mod;
  mcs->addModule(chi2mod);
  
  mcs->generateAndFit(50,0,true);
  gd = (RooDataHist*)mcs->genData(0);
  nll = gen_model->createNLL(*gd,Extended(true));
  nll->setData(*gd,true);
  RooMinuit m(*nll);
  m.setStrategy(2);
  m.migrad();
  m.hesse();
  m.minos(*rtau);
  r = m.save();
  cout << nll->getVal() << " -- ha" << endl;
  frame = rtau->frame();
  nll->plotOn(frame);
  
  // SAVE
  TFile f("fitresult.root","RECREATE");
  //  mcs->Write("mcs");
  r->Write("r");
  f.Close();
  
  TCanvas* c = new TCanvas("fitresult","fitresult",800,800);
  c->Divide(1);
  c->cd(1); gPad->SetLeftMargin(0.15); frame->Draw();
  
}

