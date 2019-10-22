#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
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
RooCategory* variable;
RooDataSet* bm_fit_data;
RooDataSet* jpsi_fit_data;
RooDataSet* fit_data;
RooDataSet* bm_sig_data;
RooDataSet* bm_b0bkg_data;
RooDataSet* bm_bbkg_data;
RooDataSet* bm_comb_data;
RooDataSet* bm_lowmass_data;
RooDataSet* bm_other_data;
RooDataSet* jpsi_sig_data;
RooDataSet* jpsi_b0bkg_data;
RooDataSet* jpsi_bbkg_data;
RooDataSet* jpsi_comb_data;
RooDataSet* jpsi_lowmass_data;
RooDataSet* jpsi_other_data;
RooKeysPdf* bm_sig_pdf;
RooKeysPdf* bm_b0bkg_pdf;
RooKeysPdf* bm_bbkg_pdf;
RooKeysPdf* bm_comb_pdf;
RooKeysPdf* bm_lowmass_pdf;
RooKeysPdf* bm_other_pdf;
RooKeysPdf* jpsi_sig_pdf;
RooKeysPdf* jpsi_b0bkg_pdf;
RooKeysPdf* jpsi_bbkg_pdf;
RooKeysPdf* jpsi_comb_pdf;
RooKeysPdf* jpsi_lowmass_pdf;
RooKeysPdf* jpsi_other_pdf;
RooRealVar* num_sig;
RooRealVar* num_b0bkg;
RooRealVar* num_bbkg;
RooRealVar* num_comb;
RooRealVar* num_lowmass;
RooRealVar* num_other;
RooAddPdf* jpsi_model;
RooAddPdf* bm_model;
RooSimultaneous* model;
RooPlot* m1frame;
RooPlot* m2frame;
TCanvas* canvas;
using namespace RooFit;

const double w_sig = 0.016;
const double w_b0bkg = 2.95;
const double w_bbkg = 3.77;

void ExtraDalitzFitter_Simul ()
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
  RooRealVar* w = new RooRealVar("w","w",0);

  cout << "Finished setting up variables" << endl;

  RooArgSet vars(*m1,*m2,
                 *Bc_SIG_Mu,*Bc_SIG_Mu_SWITCHED,
                 *Bc_SIG_Tau,*Bc_SIG_Tau_SWITCHED,*Bc_SIG_BadTau);
  vars.add(*Bc_BKG_B02JpsiX);
  vars.add(*Bc_BKG_B2JpsiX);
  vars.add(*BBBKG);
  vars.add(*LowMassBKG);

  RooArgSet wvars(vars);
  wvars.add(*w);

  cout << "Finished setting up variable lists" << endl;

  RooDataSet* w_data = new RooDataSet("w_data","w_data",vars);
  
//   w->setVal(w_sig);
//   RooDataSet* unw_sig_data = new RooDataSet("unw_data","unw_data",sigDataTree,vars);
//   unw_sig_data->addColumn(*w);
//   RooDataSet* w_sig_data = new RooDataSet("w_sig_data","w_sig_data",wvars,Import(*unw_sig_data),WeightVar("w"));
//   w_data->append(*w_sig_data);

  w->setVal(w_b0bkg);
  RooDataSet* unw_b0bkg_data = new RooDataSet("unw_data","unw_data",b0bkgDataTree,vars);
  unw_b0bkg_data->addColumn(*w);
  RooDataSet* w_b0bkg_data = new RooDataSet("w_b0bkg_data","w_b0bkg_data",wvars,Import(*unw_b0bkg_data),WeightVar("w"));
  w_data->append(*w_b0bkg_data);

  w->setVal(w_bbkg);
  RooDataSet* unw_bbkg_data = new RooDataSet("unw_data","unw_data",bbkgDataTree,vars);
  unw_bbkg_data->addColumn(*w);
  RooDataSet* w_bbkg_data = new RooDataSet("w_bbkg_data","w_bbkg_data",wvars,Import(*unw_bbkg_data),WeightVar("w"));
  w_data->append(*w_bbkg_data);

//   jpsi_fit_data = (RooDataSet*)w_data->reduce(Name("jpsi_fit_data"),
//                                               Title("jpsi_fit_data"),
//                                               SelectVars(RooArgSet(*m1,*w)),
//                                               WeightVar("w"));
//   bm_fit_data = (RooDataSet*)w_data->reduce(Name("bm_fit_data"),
//                                             Title("bm_fit_data"),
//                                             SelectVars(RooArgSet(*m2,*w)),
//                                             WeightVar("w"));
  
  jpsi_fit_data = new RooDataSet("jpsi_fit_data","jpsi_fit_data",RooArgSet(*m1,*w),Import(*w_data),WeightVar("w"));
  bm_fit_data = new RooDataSet("bm_fit_data","bm_fit_data",RooArgSet(*m2,*w),Import(*w_data),WeightVar("w"));
  
  variable = new RooCategory ("variable","variable");
  variable->defineType("jpsi");
  variable->defineType("bm");
  fit_data = new RooDataSet("fit_data","fit_data",
                            RooArgList(*m1,*m2),
                            Index(*variable),
                            Import("jpsi",*jpsi_fit_data),
                            Import("bm",*bm_fit_data));

  cout << "Finished merging data" << endl;

  string sig_cut =
    "(Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)";
//   jpsi_sig_data = (RooDataSet*)w_data->reduce(Name("jpsi_sig_data"),
//                                               Title("jpsi_sig_data"),
//                                               SelectVars(RooArgSet(*m1,*w)),
//                                               WeightVar("w"),
//                                               Cut(sig_cut.c_str()));
//   bm_sig_data = (RooDataSet*)w_data->reduce(Name("bm_sig_data"),
//                                             Title("bm_sig_data"),
//                                             SelectVars(RooArgSet(*m2,*w)),
//                                             WeightVar("w"),
//                                             Cut(sig_cut.c_str()));
  
//   jpsi_b0bkg_data = (RooDataSet*)w_data->reduce(Name("jpsi_b0bkg_data"),
//                                                 Title("jpsi_b0bkg_data"),
//                                                 SelectVars(RooArgSet(*m1,*w)),
//                                                 WeightVar("w"),
//                                                 Cut("Bc_BKG_B02JpsiX>0"));
//   bm_b0bkg_data = (RooDataSet*)w_data->reduce(Name("bm_b0bkg_data"),
//                                               Title("bm_b0bkg_data"),
//                                               SelectVars(RooArgSet(*m2,*w)),
//                                               WeightVar("w"),
//                                               Cut("Bc_BKG_B02JpsiX>0"));

//   jpsi_bbkg_data = (RooDataSet*)w_data->reduce(Name("jpsi_bbkg_data"),
//                                                Title("jpsi_bbkg_data"),
//                                                SelectVars(RooArgSet(*m1,*w)),
//                                                WeightVar("w"),
//                                                Cut("Bc_BKG_B2JpsiX>0"));
//   bm_bbkg_data = (RooDataSet*)w_data->reduce(Name("bm_bbkg_data"),
//                                              Title("bm_bbkg_data"),
//                                              SelectVars(RooArgSet(*m2,*w)),
//                                              WeightVar("w"),
//                                              Cut("Bc_BKG_B2JpsiX>0"));
  
//   jpsi_comb_data = (RooDataSet*)w_data->reduce(Name("jpsi_comb_data"),
//                                                Title("jpsi_comb_data"),
//                                                SelectVars(RooArgSet(*m1,*w)),
//                                                WeightVar("w"),
//                                                Cut("(BBBKG>0)"));
//   bm_comb_data = (RooDataSet*)w_data->reduce(Name("bm_comb_data"),
//                                              Title("bm_comb_data"),
//                                              SelectVars(RooArgSet(*m2,*w)),
//                                              WeightVar("w"),
//                                              Cut("(BBBKG>0)"));
  
//   jpsi_lowmass_data = (RooDataSet*)w_data->reduce(Name("jpsi_lowmass_data"),
//                                                   Title("jpsi_lowmass_data"),
//                                                   SelectVars(RooArgSet(*m1,*w)),
//                                                   WeightVar("w"),
//                                                   Cut("(LowMassBKG>0)"));
//   bm_lowmass_data = (RooDataSet*)w_data->reduce(Name("bm_lowmass_data"),
//                                                 Title("bm_lowmass_data"),
//                                                 SelectVars(RooArgSet(*m2,*w)),
//                                                 WeightVar("w"),
//                                                 Cut("(LowMassBKG>0)"));

  string other_cut =
    "! ( (Bc_SIG_Mu>0) || (Bc_SIG_Tau>0) || (Bc_SIG_Mu_SWITCHED>0) || (Bc_SIG_Tau_SWITCHED>0) || (Bc_SIG_BadTau>0)"
    " || (Bc_BKG_B02JpsiX>0) || (Bc_BKG_B2JpsiX>0) || (BBBKG>0) || (LowMassBKG>0) )";
//   jpsi_other_data = (RooDataSet*)w_data->reduce(Name("jpsi_other_data"),
//                                                 Title("jpsi_other_data"),
//                                                 SelectVars(RooArgSet(*m1)),
//                                                 Cut(other_cut.c_str()));
//   bm_other_data = (RooDataSet*)w_data->reduce(Name("bm_other_data"),
//                                               Title("bm_other_data"),
//                                               SelectVars(RooArgSet(*m2)),
//                                               Cut(other_cut.c_str()));
  
  cout << "Finished projecting data sets" << endl;
  
  jpsi_sig_data = new RooDataSet("jpsi_sig_data","jpsi_sig_data",RooArgSet(*m1,*w),WeightVar("w"),
                                 Import(*w_data),Cut(sig_cut.c_str()));
  bm_sig_data = new RooDataSet("bm_sig_data","bm_sig_data",RooArgSet(*m2,*w),WeightVar("w"),
                               Import(*w_data),Cut(sig_cut.c_str()));
  jpsi_b0bkg_data = new RooDataSet("jpsi_b0bkg_data","jpsi_b0bkg_data",RooArgSet(*m1,*w),WeightVar("w"),
                                   Import(*w_data),Cut("Bc_BKG_B02JpsiX>0"));
  bm_b0bkg_data = new RooDataSet("bm_b0bkg_data","bm_b0bkg_data",RooArgSet(*m2,*w),WeightVar("w"),
                                 Import(*w_data),Cut("Bc_BKG_B02JpsiX>0"));
  jpsi_bbkg_data = new RooDataSet("jpsi_bbkg_data","jpsi_bbkg_data",RooArgSet(*m1,*w),WeightVar("w"),
                                  Import(*w_data),Cut("Bc_BKG_B2JpsiX>0"));
  bm_bbkg_data = new RooDataSet("bm_bbkg_data","bm_bbkg_data",RooArgSet(*m2,*w),WeightVar("w"),
                                Import(*w_data),Cut("Bc_BKG_B2JpsiX>0"));
  jpsi_comb_data = new RooDataSet("jpsi_comb_data","jpsi_comb_data",RooArgSet(*m1,*w),WeightVar("w"),
                                  Import(*w_data),Cut("(BBBKG>0)"));
  bm_comb_data = new RooDataSet("bm_comb_data","bm_comb_data",RooArgSet(*m2,*w),WeightVar("w"),
                                Import(*w_data),Cut("(BBBKG>0)"));
  jpsi_lowmass_data = new RooDataSet("jpsi_lowmass_data","jpsi_lowmass_data",RooArgSet(*m1,*w),WeightVar("w"),
                                     Import(*w_data),Cut("(LowMassBKG>0)"));
  bm_lowmass_data = new RooDataSet("bm_lowmass_data","bm_lowmass_data",RooArgSet(*m2,*w),WeightVar("w"),
                                   Import(*w_data),Cut("(LowMassBKG>0)"));
  jpsi_other_data = new RooDataSet("jpsi_other_data","jpsi_other_data",RooArgSet(*m1,*w),WeightVar("w"),
                                   Import(*w_data),Cut(other_cut.c_str()));
  bm_other_data = new RooDataSet("bm_other_data","bm_other_data",RooArgSet(*m2,*w),WeightVar("w"),
                                 Import(*w_data),Cut(other_cut.c_str()));
  
  jpsi_sig_pdf = new RooKeysPdf ("jpsi_sig","jpsi sig pdf",*m1,*jpsi_sig_data,RooKeysPdf::NoMirror);
  bm_sig_pdf = new RooKeysPdf ("bm_sig","bm sig pdf",*m2,*bm_sig_data,RooKeysPdf::NoMirror);
  jpsi_b0bkg_pdf = new RooKeysPdf ("jpsi_b0bkg","jpsi b0bkg pdf",*m1,*jpsi_b0bkg_data,RooKeysPdf::NoMirror);
  bm_b0bkg_pdf = new RooKeysPdf ("bm_b0bkg","bm b0bkg pdf",*m2,*bm_b0bkg_data,RooKeysPdf::NoMirror);
  jpsi_bbkg_pdf = new RooKeysPdf ("jpsi_bbkg","jpsi bbkg pdf",*m1,*jpsi_bbkg_data,RooKeysPdf::NoMirror);
  bm_bbkg_pdf = new RooKeysPdf ("bm_bbkg","bm bbkg pdf",*m2,*bm_bbkg_data,RooKeysPdf::NoMirror);
  jpsi_comb_pdf = new RooKeysPdf ("jpsi_comb","jpsi comb pdf",*m1,*jpsi_comb_data,RooKeysPdf::NoMirror);
  bm_comb_pdf = new RooKeysPdf ("bm_comb","bm comb pdf",*m2,*bm_comb_data,RooKeysPdf::NoMirror);
  jpsi_lowmass_pdf = new RooKeysPdf ("jpsi_lowmass","jpsi lowmass pdf",*m1,*jpsi_lowmass_data,RooKeysPdf::NoMirror);
  bm_lowmass_pdf = new RooKeysPdf ("bm_lowmass","bm lowmass pdf",*m2,*bm_lowmass_data,RooKeysPdf::NoMirror);
  jpsi_other_pdf = new RooKeysPdf ("jpsi_other","jpsi other pdf",*m1,*jpsi_other_data,RooKeysPdf::NoMirror);
  bm_other_pdf = new RooKeysPdf ("bm_other","bm other pdf",*m2,*bm_other_data,RooKeysPdf::NoMirror);
  
  num_sig = new RooRealVar ("num_sig","num_sig",1E4,1,1E6);
  num_b0bkg = new RooRealVar ("num_b0bkg","num_b0bkg",1E4,1,1E6);
  num_bbkg = new RooRealVar ("num_bbkg","num_bbkg",1E4,1,1E6);
  num_comb = new RooRealVar ("num_comb","num_comb",1E4,1,1E6);
  num_lowmass = new RooRealVar ("num_lowmass","num_lowmass",1,1,1E6);
  num_other = new RooRealVar ("num_other","num_other",1,1,1E6);
  jpsi_model = new RooAddPdf ("jpsi_model","jpsi_model",
                              RooArgList(*jpsi_sig_pdf,*jpsi_b0bkg_pdf,*jpsi_b0bkg_pdf,
                                         *jpsi_comb_pdf,*jpsi_lowmass_pdf,*jpsi_other_pdf),
                              RooArgList(*num_sig,*num_b0bkg,*num_bbkg,*num_comb,*num_lowmass,*num_other));
  bm_model = new RooAddPdf ("bm_model","bm_model",
                            RooArgList(*bm_sig_pdf,*bm_b0bkg_pdf,*bm_bbkg_pdf,
                                       *bm_comb_pdf,*bm_lowmass_pdf,*bm_other_pdf),
                            RooArgList(*num_sig,*num_b0bkg,*num_bbkg,*num_comb,*num_lowmass,*num_other));

  
  model = new RooSimultaneous ("model","model",*variable);
  model->addPdf(*jpsi_model,"jpsi");
  model->addPdf(*bm_model,"bm");
  
  cout << "Finished making fit model" << endl;

  model->fitTo(*fit_data,Extended(),Hesse(true),SumW2Error(true),Strategy(2),Minos(true),InitialHesse(false));

  cout << "Finished fitting" << endl;

  m1frame = m1->frame(m1->getBins());
  fit_data->plotOn(m1frame,Cut("variable==variable::jpsi"));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data));
//   model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
//                 Components("jpsi_sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m1frame,Slice(*variable,"jpsi"),ProjWData(*variable,*fit_data),
                Components("jpsi_other"),LineStyle(kDashed),LineColor(kPink));

  m2frame = m2->frame(m2->getBins());
  fit_data->plotOn(m2frame,Cut("variable==variable::bm"));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data));
//   model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
//                 Components("bm_sig"),LineStyle(kDashed),LineColor(kRed));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_b0bkg"),LineStyle(kDashed),LineColor(kMagenta));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_bbkg"),LineStyle(kDashed),LineColor(kOrange));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_comb"),LineStyle(kDashed),LineColor(kCyan));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_lowmass"),LineStyle(kDashed),LineColor(kGreen));
  model->plotOn(m2frame,Slice(*variable,"bm"),ProjWData(*variable,*fit_data),
                Components("bm_other"),LineStyle(kDashed),LineColor(kPink));

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

