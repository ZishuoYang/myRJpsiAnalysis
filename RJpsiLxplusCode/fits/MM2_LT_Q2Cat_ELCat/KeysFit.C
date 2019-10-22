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
RooDataSet* mu_genset;
RooDataSet* tau_genset;
RooDataSet* b_genset;
RooDataSet* fd_genset;
RooDataSet* pv_genset;
RooDataSet* ghost_genset;
RooDataSet* comb_genset;
RooNDKeysPdf* mu_genpdf;
RooNDKeysPdf* tau_genpdf;
RooNDKeysPdf* fd_genpdf;
RooNDKeysPdf* b_genpdf;
RooNDKeysPdf* pv_genpdf;
RooNDKeysPdf* ghost_genpdf;
RooNDKeysPdf* comb_genpdf;
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
RooDataSet* gd;
RooAbsReal* nll;
RooPlot* frame;
RooFitResult* r;
using namespace RooFit;

void KeysFit()
{

  const char wstr[7] = "weight*(MyBkgTag%10 < 5) + W*(MyBkgTag%10 >= 5)";
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
//   RooThresholdCategory* q2thrcat = new RooThresholdCategory("q2thrcat","q2thrcat",*q2,"High");
//   q2thrcat->addThreshold(10.4,"High");
//   q2thrcat->addThreshold(7.0,"Medium");
//   q2thrcat->addThreshold(4.0,"Low");
//   el = new RooRealVar (elstr,"el",0.1,3.0);
//   RooThresholdCategory* elthrcat = new RooThresholdCategory("elthrcat","elthrcat",*el,"High");
//   elthrcat->addThreshold(3.0,"High");
//   elthrcat->addThreshold(1.75,"Medium");
//   elthrcat->addThreshold(0.75,"Low");
//   invmm = new RooRealVar (invmmstr,"invmm",3200,6300);
//   RooThresholdCategory* invmmthrcat = new RooThresholdCategory("invmmthrcat","invmmthrcat",*invmm,"AboveB");
//   invmmthrcat->addThreshold(5280,"BelowB");

//  RooArgSet vars(*mm2,*lt,*q2,*el,*w,*MyBkgTag);
  RooArgSet vars(*mm2,*lt,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));
  dataFile.Close();
//   q2cat = (RooCategory*)w_data->addColumn(*q2thrcat);
//   elcat = (RooCategory*)w_data->addColumn(*elthrcat);
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
//   mm2->setBins(80);
//   lt->setBins(80);

  // RooArgSet fvarsset(*mm2,*lt,*q2cat,*elcat);
  RooArgSet fvarsset(*mm2,*lt);
  mu_genset = (RooDataSet*)w_data->reduce(Name("mu_genset")
					  , Title("mu_genset")
					  , SelectVars(fvarsset)
					  , Cut(mu_cut.c_str()));
  tau_genset = (RooDataSet*)w_data->reduce(Name("tau_genset")
					  , Title("tau_genset")
					  , SelectVars(fvarsset)
					  , Cut(tau_cut.c_str()));
  fd_genset = (RooDataSet*)w_data->reduce(Name("fd_genset")
					  , Title("fd_genset")
					  , SelectVars(fvarsset)
					  , Cut(fd_cut.c_str()));
  b_genset = (RooDataSet*)w_data->reduce(Name("b_genset")
					  , Title("b_genset")
					  , SelectVars(fvarsset)
					  , Cut(b_cut.c_str()));
  pv_genset = (RooDataSet*)w_data->reduce(Name("pv_genset")
					  , Title("pv_genset")
					  , SelectVars(fvarsset)
					  , Cut(pv_cut.c_str()));
  ghost_genset = (RooDataSet*)w_data->reduce(Name("ghost_genset")
					  , Title("ghost_genset")
					  , SelectVars(fvarsset)
					  , Cut(ghost_cut.c_str()));
  comb_genset = (RooDataSet*)w_data->reduce(Name("comb_genset")
					  , Title("comb_genset")
					  , SelectVars(fvarsset)
					  , Cut(comb_cut.c_str()));

  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;
 
  mu_genpdf = new RooNDKeysPdf ("mugen","mu genpdf",fvarsset,*mu_genset,RooKeysPdf::NoMirror);
  tau_genpdf = new RooNDKeysPdf ("taugen","tau genpdf",fvarsset,*tau_genset,RooKeysPdf::NoMirror);
  fd_genpdf = new RooNDKeysPdf ("fdgen","fd genpdf",fvarsset,*fd_genset,RooKeysPdf::NoMirror);
  b_genpdf = new RooNDKeysPdf ("bgen","b genpdf",fvarsset,*b_genset,RooKeysPdf::NoMirror);
  pv_genpdf = new RooNDKeysPdf ("pvgen","pv genpdf",fvarsset,*pv_genset,RooKeysPdf::NoMirror);
  ghost_genpdf = new RooNDKeysPdf ("ghostgen","ghost genpdf",fvarsset,*ghost_genset,RooKeysPdf::NoMirror);
  comb_genpdf = new RooNDKeysPdf ("combgen","comb genpdf",fvarsset,*comb_genset,RooKeysPdf::NoMirror);

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

  mcs = new RooMCStudy(*gen_model,fvarsset,Extended(true),FitOptions(Save(true),Minos(true),Strategy(2)));
  RooChi2MCSModule chi2mod;
  mcs->addModule(chi2mod);
  
  mcs->generateAndFit(5,0,true);
  gd = (RooDataSet*)mcs->genData(0);
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

