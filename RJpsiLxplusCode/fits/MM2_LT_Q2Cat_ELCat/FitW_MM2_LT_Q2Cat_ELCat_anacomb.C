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
// RooRealVar* q2;
// RooCategory* q2cat;
// RooRealVar* el;
// RooCategory* elcat;
RooRealVar* w;
RooRealVar* MyBkgTag;
RooDataHist* mu_genhist;
RooDataHist* tau_genhist;
RooDataHist* fd_genhist;
RooDataHist* b_genhist;
RooDataHist* b0_genhist;
RooDataHist* bs_genhist;
//RooDataHist* comb_genhist;
// RooDataHist* lowmass_genhist;
// RooDataHist* other_genhist;
RooDataHist* mu_multihist;
RooDataHist* tau_multihist;
RooDataHist* fd_multihist;
RooDataHist* b_multihist;
RooDataHist* b0_multihist;
RooDataHist* bs_multihist;
//RooDataHist* comb_multihist;
// RooDataHist* lowmass_multihist;
// RooDataHist* other_multihist;
RooDataHist* mu_lthist;
RooDataHist* tau_lthist;
RooDataHist* fd_lthist;
RooDataHist* b_lthist;
RooDataHist* b0_lthist;
RooDataHist* bs_lthist;
//RooDataHist* comb_lthist;
// RooDataHist* lowmass_lthist;
// RooDataHist* other_lthist;
RooHistPdf* mu_genpdf;
RooHistPdf* tau_genpdf;
RooHistPdf* fd_genpdf;
RooHistPdf* b_genpdf;
RooHistPdf* b0_genpdf;
RooHistPdf* bs_genpdf;
//RooHistPdf* comb_genpdf;
// RooHistPdf* lowmass_genpdf;
// RooHistPdf* other_genpdf;
RooHistPdf* mu_multipdf;
RooHistPdf* tau_multipdf;
RooHistPdf* b0_multipdf;
RooHistPdf* b_multipdf;
//RooHistPdf* comb_multipdf;
// RooHistPdf* lowmass_multipdf;
// RooHistPdf* other_multipdf;
RooHistPdf* mu_ltpdf;
RooHistPdf* tau_ltpdf;
RooHistPdf* fd_ltpdf;
RooHistPdf* b_ltpdf;
RooHistPdf* b0_ltpdf;
RooHistPdf* bs_ltpdf;
//RooHistPdf* comb_ltpdf;
// RooHistPdf* lowmass_ltpdf;
// RooHistPdf* other_ltpdf;
RooProdPdf* mu_pdf;
RooProdPdf* tau_pdf;
RooProdPdf* fd_pdf;
RooProdPdf* b_pdf;
RooProdPdf* b0_pdf;
RooProdPdf* bs_pdf;
RooProdPdf* comb_pdf;
// RooProdPdf* lowmass_pdf;
// RooProdPdf* other_pdf;
RooRealVar* num_mu;
RooRealVar *rtau;
RooFormulaVar* num_tau;
RooRealVar *rfd;
RooFormulaVar* num_fd;
RooRealVar* num_b;
RooRealVar* num_b0;
RooRealVar* num_bs;
RooRealVar* num_comb;
// RooRealVar* num_lowmass;
// RooRealVar* num_other;
RooAddPdf* gen_model;
RooAddPdf* model;
RooMCStudy* mcs;
RooDataHist* gd;
RooAbsReal* nll;
RooPlot* frame;
RooFitResult* r;
using namespace RooFit;

void FitW_MM2_LT_Q2Cat_ELCat_anacomb ()
{

  const char mm2str[10] = "MissMass2";
  const char ltstr[12] = "LogLifetime"; // or ExpLifetime
  const char q2str[3] = "Q2";
  const char elstr[13] = "BachMuEnergy";
  const char wstr[7] = "W";
  const char bkgstr[9] = "MyBkgTag";

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

  mm2 = new RooRealVar (mm2str,"mm2",-3.0,9.0);
  lt = new RooRealVar (ltstr,"lt",-2.2,2.0);
//   q2 = new RooRealVar (q2str,"q2",-5.0,10.4);
//   el = new RooRealVar (elstr,"el",0.1,3.0);
//    RooThresholdCategory* q2thrcat = new RooThresholdCategory("q2thrcat","q2thrcat",*q2,"VeryHigh");
//    q2thrcat->addThreshold(-5.0,"VeryLow");
//    q2thrcat->addThreshold(8.5,"VeryHigh");
//    q2thrcat->addThreshold(7.0,"High");
//    q2thrcat->addThreshold(5.0,"Low");
//   q2thrcat->addThreshold(-5.0,"VeryLow");
//    RooThresholdCategory* elthrcat = new RooThresholdCategory("elthrcat","elthrcat",*el,"VeryHigh");
   //   elthrcat->addThreshold(1.2,"VeryHigh");
  //   elthrcat->addThreshold(0.1,"VeryLow");
//    elthrcat->addThreshold(1.2,"VeryHigh");
//    elthrcat->addThreshold(0.8,"High");
//    elthrcat->addThreshold(0.5,"Low");
//    elthrcat->addThreshold(0.1,"VeryLow");
  w = new RooRealVar (wstr,"w",0.0,10.0);
  MyBkgTag = new RooRealVar(bkgstr,"tag",0.0);

  //  RooArgSet vars(*mm2,*lt,*q2,*el,*w,*MyBkgTag);
  RooArgSet vars(*mm2,*lt,*w,*MyBkgTag);

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars,Import(*dataTree),WeightVar(*w));
  dataFile.Close();
//   q2cat = (RooCategory*)w_data->addColumn(*q2thrcat);
//   elcat = (RooCategory*)w_data->addColumn(*elthrcat);

  //  string allcut = " && BachMu_ProbNNmu > 0.7";
  string allcut = "";
  string mu_cut = "MyBkgTag == 0" + allcut;
  string tau_cut = "MyBkgTag == 1" + allcut;
  string fd_cut = "MyBkgTag == 100" + allcut;
  string b_cut = "MyBkgTag == 2" + allcut;
  string b0_cut = "MyBkgTag == 102" + allcut;
  string bs_cut = "MyBkgTag == 202" + allcut;
  string comb_cut = "MyBkgTag % 10 == 4" + allcut;
  //  string pv_cut = "MyBkgTag % 100 == 5"; // won't use
  //  string other_cut = "(MyBkgTag % 100 == 6) || (MyBkgTag % 100 == -1)"; // won't use
  
  // How many bins are enough?
  mm2->setBins(50);
  lt->setBins(50);

  //  RooArgSet fvarsset(*mm2,*lt,*q2cat,*elcat);
  RooArgSet fvarsset(*mm2,*lt);
  mu_genhist = new RooDataHist("mu_genhist","mu_genhist",fvarsset);
  mu_genhist->add(*w_data,mu_cut.c_str());
  tau_genhist = new RooDataHist("tau_genhist","tau_genhist",fvarsset);
  tau_genhist->add(*w_data,tau_cut.c_str());
  fd_genhist = new RooDataHist("fd_genhist","fd_genhist",fvarsset);
  fd_genhist->add(*w_data,fd_cut.c_str());
  b0_genhist = new RooDataHist("b0_genhist","b0_genhist",fvarsset);
  b0_genhist->add(*w_data,b0_cut.c_str());
  bs_genhist = new RooDataHist("bs_genhist","bs_genhist",fvarsset);
  bs_genhist->add(*w_data,bs_cut.c_str());
  b_genhist = new RooDataHist("b_genhist","b_genhist",fvarsset);
  b_genhist->add(*w_data,b_cut.c_str());
//   comb_genhist = new RooDataHist("comb_genhist","comb_genhist",fvarsset);
//   comb_genhist->add(*w_data,comb_cut.c_str());

  //RooArgSet multiset(*mm2,*q2cat,*elcat);   
  RooArgSet multiset(*mm2);   
  mu_multihist = new RooDataHist("mu_multihist","mu_multihist",multiset);
  mu_multihist->add(*w_data,mu_cut.c_str());
  tau_multihist = new RooDataHist("tau_multihist","tau_multihist",multiset);
  tau_multihist->add(*w_data,tau_cut.c_str());
  fd_multihist = new RooDataHist("fd_multihist","fd_multihist",multiset);
  fd_multihist->add(*w_data,fd_cut.c_str());
  b0_multihist = new RooDataHist("b0_multihist","b0_multihist",multiset);
  b0_multihist->add(*w_data,b0_cut.c_str());
  bs_multihist = new RooDataHist("bs_multihist","bs_multihist",multiset);
  bs_multihist->add(*w_data,bs_cut.c_str());
  b_multihist = new RooDataHist("b_multihist","b_multihist",multiset);
  b_multihist->add(*w_data,b_cut.c_str());
//   comb_multihist = new RooDataHist("comb_multihist","comb_multihist",multiset);
//   comb_multihist->add(*w_data,comb_cut.c_str());


  mu_lthist = new RooDataHist("mu_lthist","mu_lthist",RooArgSet(*lt));
  mu_lthist->add(*w_data,mu_cut.c_str());
  tau_lthist = new RooDataHist("tau_lthist","tau_lthist",RooArgSet(*lt));
  tau_lthist->add(*w_data,tau_cut.c_str());
  fd_lthist = new RooDataHist("fd_lthist","fd_lthist",RooArgSet(*lt));
  fd_lthist->add(*w_data,fd_cut.c_str());
  b0_lthist = new RooDataHist("b0_lthist","b0_lthist",RooArgSet(*lt));
  b0_lthist->add(*w_data,b0_cut.c_str());
  bs_lthist = new RooDataHist("bs_lthist","bs_lthist",RooArgSet(*lt));
  bs_lthist->add(*w_data,bs_cut.c_str());
  b_lthist = new RooDataHist("b_lthist","b_lthist",RooArgSet(*lt));
  b_lthist->add(*w_data,b_cut.c_str());
//   comb_lthist = new RooDataHist("comb_lthist","comb_lthist",RooArgSet(*lt));
//   comb_lthist->add(*w_data,comb_cut.c_str());
  
  // -------------------------
  // CREATING ROOFIT PDFS
  // -------------------------

  cout << "Creating roofit pdfs ... " << endl;
 
  mu_genpdf = new RooHistPdf ("mugen","mu genpdf",fvarsset,*mu_genhist,3);
  tau_genpdf = new RooHistPdf ("taugen","tau genpdf",fvarsset,*tau_genhist,3);
  fd_genpdf = new RooHistPdf ("fdgen","fd genpdf",fvarsset,*fd_genhist,3);
  b0_genpdf = new RooHistPdf ("b0gen","b0 genpdf",fvarsset,*b0_genhist,3);
  bs_genpdf = new RooHistPdf ("bsgen","bs genpdf",fvarsset,*bs_genhist,3);
  b_genpdf = new RooHistPdf ("bgen","b genpdf",fvarsset,*b_genhist,3);
  //  comb_genpdf = new RooHistPdf ("combgen","comb genpdf",fvarsset,*comb_genhist,3);

  // ANALYTIC COMB. BACKGROUND
//   RooRealVar mu1("mu1","mu1",2.265); mu1.setConstant(true);
//   RooRealVar sig1("sig1","sig1",2.557); sig1.setConstant(true);
//   RooGaussian comb_mm2("comb_mm2","comb_mm2",*mm2,mu1,sig1);
  RooRealVar mp1("mp1","mp1",0.0611797); mp1.setConstant(true);
  RooRealVar mp2("mp2","mp2",0.0415162); mp2.setConstant(true);
  RooRealVar mp3("mp3","mp3",0.0385144); mp3.setConstant(true);
  RooRealVar mp4("mp4","mp4",-0.0139308); mp4.setConstant(true);
  RooRealVar mp5("mp5","mp5",-0.00167878); mp5.setConstant(true);
  RooRealVar mp6("mp6","mp6",0.000984988); mp6.setConstant(true);
  RooRealVar mp7("mp7","mp7",-0.000116675); mp7.setConstant(true);
  RooRealVar mp8("mp8","mp8",4.46456e-6); mp8.setConstant(true);
  RooPolynomial comb_mm2("comb_mm2","comb_mm2",*mm2,RooArgList(mp1,mp2,mp3,mp4,mp5,mp6,mp7,mp8));
  //   RooRealVar mu2("mu2","mu2",0.2305); mu2.setConstant(true);
  //   RooRealVar sig2("sig2","sig2",0.690); sig2.setConstant(true);
  //   RooGaussian comb_lt("comb_lt","comb_lt",*lt,mu2,sig2);
  RooRealVar p1("p1","p1",-0.0797623); p1.setConstant(true);
  RooRealVar p2("p2","p2",-0.722157); p2.setConstant(true);
  RooRealVar p3("p3","p3",-0.0141071); p3.setConstant(true);
  RooRealVar p4("p4","p4",0.173203); p4.setConstant(true);
  RooRealVar p5("p5","p5",0.0222871); p5.setConstant(true);
  RooRealVar p6("p6","p6",-0.0111069); p6.setConstant(true);
  RooRealVar p7("p7","p7",-0.00350666); p7.setConstant(true);
  RooRealVar p8("p8","p8",-0.000618254); p8.setConstant(true);
  RooPolynomial comb_lt("comb_lt","comb_lt",*lt,RooArgList(p1,p2,p3,p4,p5,p6,p7,p8));
  RooProdPdf comb_anapdf("comb_anapdf","comb_anapdf",RooArgList(comb_mm2,comb_lt));

  double factor = 1.0;
  double theory = 21.1/11.2;
  num_mu = new RooRealVar ("num_mu","num_mu",factor*theory*1.27e4,1,2E5);
  rtau = new RooRealVar ("rtau","rtau",0.0432,1E-10,1.0);
  num_tau = new RooFormulaVar ("num_tau","num_tau","num_mu * rtau",RooArgList(*num_mu,*rtau));
  rfd = new RooRealVar ("rfd","rfd",0.0562,1E-10,1.0);
  num_fd = new RooFormulaVar ("num_fd","num_fd","num_mu * rfd",RooArgList(*num_mu,*rfd));
  //   num_b0 = new RooRealVar ("num_b0","num_b0",factor*0.2814*2.41e4,1,2E5);
//   num_bs = new RooRealVar ("num_bs","num_bs",factor*0.2069*1.70e2,1,2E5);
  num_b = new RooRealVar ("num_b","num_b",factor*0.2345*4.36e4,1,2E5);
  num_comb = new RooRealVar ("num_comb","num_comb",factor*4.56E4,1,2E5);

  gen_model = new RooAddPdf ("gen_model","gen_model",
                             RooArgList(*mu_genpdf,*tau_genpdf,*fd_genpdf,*b0_genpdf,*bs_genpdf,*b_genpdf,comb_anapdf),
                             RooArgList(*num_mu,*num_tau,*num_fd,*num_b0,*num_bs,*num_b,*num_comb));

  model = new RooAddPdf ("model","model",
                         RooArgList(*mu_genpdf,*tau_genpdf,*fd_genpdf,*b0_genpdf,*bs_genpdf,*b_genpdf,comb_anapdf),
                         RooArgList(*num_mu,*num_tau,*num_fd,*num_b0,*num_bs,*num_b,*num_comb));
//   mu_multipdf = new RooHistPdf ("mumulti","mu multipdf",multiset,*mu_multihist,3);
//   tau_multipdf = new RooHistPdf ("taumulti","tau multipdf",multiset,*tau_multihist,3);
//   fd_multipdf = new RooHistPdf ("fdmulti","fd multipdf",multiset,*fd_multihist,3);
//   b0_multipdf = new RooHistPdf ("b0multi","b0 multipdf",multiset,*b0_multihist,3);
//   b_multipdf = new RooHistPdf ("bmulti","b multipdf",multiset,*b_multihist,3);
//   //  comb_multipdf = new RooHistPdf ("combmulti","comb multipdf",multiset,*comb_multihist,3);
  
//   mu_ltpdf = new RooHistPdf ("mu_ltpdf","mu ltpdf",RooArgSet(*lt),*mu_lthist,3);
//   tau_ltpdf = new RooHistPdf ("tau_ltpdf","tau ltpdf",RooArgSet(*lt),*tau_lthist,3);
//   fd_ltpdf = new RooHistPdf ("fd_ltpdf","fd ltpdf",RooArgSet(*lt),*fd_lthist,3);
//   b0_ltpdf = new RooHistPdf ("b0_ltpdf","b0 ltpdf",RooArgSet(*lt),*b0_lthist,3);
//   b_ltpdf = new RooHistPdf ("b_ltpdf","b ltpdf",RooArgSet(*lt),*b_lthist,3);
//   //  comb_ltpdf = new RooHistPdf ("comb_ltpdf","comb ltpdf",RooArgSet(*lt),*comb_lthist,3);
  
//   mu_pdf = new RooProdPdf ("mu","mu pdf",RooArgList(*mu_multipdf,*mu_ltpdf));
//   tau_pdf = new RooProdPdf ("tau","tau pdf",RooArgList(*tau_multipdf,*tau_ltpdf));
//   fd_pdf = new RooProdPdf ("fd","fd pdf",RooArgList(*fd_multipdf,*fd_ltpdf));
//   b0_pdf = new RooProdPdf ("b0","b0 pdf",RooArgList(*b0_multipdf,*b0_ltpdf));
//   b_pdf = new RooProdPdf ("b","b pdf",RooArgList(*b_multipdf,*b_ltpdf));
//   comb_pdf = new RooProdPdf ("comb","comb pdf",RooArgList(*comb_multipdf,*comb_ltpdf));

//   model = new RooAddPdf ("model","model",
//                          RooArgList(*mu_pdf,*tau_pdf,*fd_pdf,*b0_pdf,*b_pdf,*comb_pdf),
//                          RooArgList(*num_mu,*num_tau,*num_fd,*num_b0,*num_b,*num_comb));
  

  // -------------------------
  // GENERATING AND FITTING TOY MC
  // -------------------------

  cout << "generating and fitting toy MC ... " << endl;

  /* I'll set the numbers to expected values and generate toy MC
   */

  // Remove FitModel(*model) to make the fit model the one that preserves
  // the correlations between Lifetime and MissMass2/Q2/BachMuEnergy
  mcs = new RooMCStudy(*gen_model,fvarsset,Binned(true),Extended(true),FitOptions(Save(true),Minos(true),Strategy(2)));
  //   RooChi2MCSModule chi2mod;
  //   mcs->addModule(chi2mod);
  
  mcs->generateAndFit(1,0,true); // number of events taken to be 500?
  gd = (RooDataHist*)mcs->genData(0);
  //   gd = gen_model->generateBinned(RooArgSet(*lt,*mm2,*q2cat,*elcat),Extended());
//   nll = gen_model->createNLL(*gd,Extended(true));
//   nll->setData(*gd,true);
//   RooMinuit m(*nll);
//   m.setStrategy(2);
//   m.migrad();
//   m.hesse();
//   m.minos(*rtau);
//   r = m.save();
//   cout << nll->getVal() << " -- ha" << endl;
//   frame = rtau->frame();
//   nll->plotOn(frame);
  
  // SAVE
  TFile f("fitresult.root","RECREATE");
  r->Write("r");
  f.Close();
  
//   TCanvas* c = new TCanvas("fitresult","fitresult",800,800);
//   c->Divide(1);
//   c->cd(1); gPad->SetLeftMargin(0.15); frame->Draw();
  
}

