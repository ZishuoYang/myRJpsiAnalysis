// modified from rs301_splot.C

#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooStats/SPlot.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooChebychev.h"
#include "RooGamma.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooAbsPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"
#include "RooConstVar.h"
#include "TH1D.h"

// use this order for safety on library loading
using namespace RooFit ;
using namespace RooStats ;

void JpsiKFit() {

  // INITIALIZE
  std::cout << "Add models" << std::endl;

  // DATA
  Double_t lowRange = 5200; // to throw out shoulder
  Double_t highRange = 5500;
  RooRealVar mass("B_MM", "B_MM", lowRange, highRange);
  RooRealVar jpsiMass("Jpsi_MM", "jpsi_MM",0);//2950,3250);
  RooRealVar dira("B_DIRA","B_DIRA",0);//-1.0,1.0);
  RooRealVar vchi2("B_VCHI2","B_VCHI2",0);//0.0,50.0);

  // THINGS TO SPLIT
  RooRealVar nTracks("nTracks","nTracks",0);//0.0,1000.0);
  RooRealVar P("K_P","K_P",0);//0.0,2.0e5);
  RooRealVar PT("K_PT","K_PT",0);//0.0,2.5e4);
  RooRealVar ETA("K_Eta","K_Eta",0);//0.0,6.0);

  RooRealVar DLLK("K_CombDLLK","K_CombDLLK",0);//-1100,200);
  RooRealVar DLLp("K_CombDLLp","K_CombDLLp",0);//-1100,200);
  RooRealVar DLLe("K_CombDLLe","K_CombDLLe",0);//-1100,200);
  RooRealVar DLLmu("K_CombDLLmu","K_combDLLmu",0);//-1100,200);

  RooRealVar isMuon("K_IsMuon","K_IsMuon",0);//0.0,1.0);
  RooRealVar isMuonLoose("K_IsMuonLoose","K_IsMuonLoose",0);//0.0,1.0);
  RooRealVar nShared("K_nShared","K_nShared",0);//0.0,100.0);

  // Forgot the K_!!!
  RooRealVar probK("ProbNNk","ProbNNk",0);//0.0,1.0);
  RooRealVar probPi("ProbNNpi","ProbNNpi",0);//0.0,1.0);
  RooRealVar probP("ProbNNp","ProbNNp",0);//0.0,1.0);
  RooRealVar probMu("ProbNNmu","ProbNNmu",0);//0.0,1.0);
  RooRealVar probE("ProbNNe","ProbNNe",0);//0.0,1.0);

  RooRealVar inMuon("K_InMuonAcc","K_InMuonAcc",0);//0.0,1.0);
  // RooRealVar region("K_regionInM2","K_regionInM2",0);//-1.0,4.0);
  // RooRealVar muondist2("K_MuonDist2","K_MuonDist2",0);//-1.1e5,1e3);
  // RooRealVar mchi2("K_MatchCHI2","K_MatchCHI2",0);//0.0,100.0);

  // SIGNAL MODEL
  RooRealVar mean("mean","mean",5285,5250,5300);
  RooRealVar sigma("sigma","sigma",18.0,1.0,50.0);
  RooRealVar mult("mult","mult",0.55,0.1,1.0);
  RooFormulaVar sigma2("sigma2","sigma2","sigma*mult",RooArgList(sigma,mult));
  RooGaussian g1("g1", "g1", mass, mean, sigma);
  RooGaussian g2("g2", "g2", mass, mean, sigma2);
  RooRealVar sigfrac("sigfrac","sigfrac",0.35,0.05,1.0);
  RooAddPdf mass_sig("mass_sig","mass_sig",RooArgList(g1,g2),RooArgList(sigfrac));

  // BACKGROUND MODEL
  RooRealVar p1("p1","p1",-1.5e-3,-1e-2,-1e-4);
  RooExponential mass_bkg("mass_bkg","mass_bkg",mass,p1);
  // RooRealVar p2("p2","p2",0,-100,100);
  //  RooChebychev mass_bkg("mass_bkg","mass_bkg",mass,RooArgList(p1,p2));

  // COMBINED MODEL
  RooRealVar nsig("nsig","nsig", 3.0e5, 1, 1e6);
  RooRealVar nbkg("nbkg","nbkg", 3.0e6, 1, 1e7);
  RooAddPdf model("model","model",
		  RooArgList(mass_sig, mass_bkg), 
		  RooArgList(nsig,nbkg));

  RooArgSet vars1(mass,jpsiMass,dira,vchi2,nTracks,P,PT,ETA);
  RooArgSet vars2(DLLK,DLLp,DLLe,DLLmu,isMuon,isMuonLoose,nShared);
  RooArgSet vars3(probK,probPi,probP,probMu,probE,inMuon);//,region,muondist2,mchi2);
  RooArgSet vars12(vars1,vars2);
  RooArgSet vars(vars12,vars3);

  // ADD DATA
  std::cout << "Add data" << std::endl;

  TFile* file = new TFile("Bc_JpsiK_Cal_SELECTION.root");
  TTree* tree = (TTree*)file->Get("DecayTree");
  RooDataSet *data = new RooDataSet("data","data",tree,vars,"log(1.0-B_DIRA)<-10.0 && abs(Jpsi_MM-3096.916)<50.0");
  // RooFormulaVar distlogFunc("distlog","distlog","log(K_MuonDist2)",muondist2);
  // RooRealVar* distlog = (RooRealVar*)data->addColumn(distlogFunc);
  // distlog->setRange(-4.0,8.0);

  // DO SPLOT
  std::cout << "Calculate sWeights" << std::endl;
  model.fitTo(*data, Extended(), NumCPU(4) );
  mean.setConstant(kTRUE);
  sigma.setConstant(kTRUE);
  mult.setConstant(kTRUE);
  sigfrac.setConstant(kTRUE);
  p1.setConstant(kTRUE);
  //  p2.setConstant(kTRUE);
  model.fitTo(*data, Extended(), NumCPU(4) );
  RooMsgService::instance().setSilentMode(true);
  RooStats::SPlot* sData = new RooStats::SPlot("sData","sData", *data, &model, RooArgList(nsig,nbkg));
  std::cout << "Check SWeights:" << std::endl;
  std::cout << std::endl <<  "Yield of sig is " 
	    << nsig.getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("nsig") << std::endl;
  std::cout << "Yield of bkg is " 
	    << nbkg.getVal() << ".  From sWeights it is "
	    << sData->GetYieldFromSWeight("nbkg") << std::endl
	    << std::endl;
  std::cout << std::endl;
    
  RooDataSet* Sdata = sData->GetSDataSet();
  RooDataSet * dataw_sig = new RooDataSet(Sdata->GetName(),Sdata->GetTitle(),Sdata,*Sdata->get(),0,"nsig_sw") ;
  RooDataSet * dataw_bkg = new RooDataSet(Sdata->GetName(),Sdata->GetTitle(),Sdata,*Sdata->get(),0,"nbkg_sw") ;

  // MAKE PLOTS
  std::cout << "Make plots" << std::endl;

  // FIT CANVAS
  char name[6] = "sPlot";
  char title[100] = "Fit";
  TCanvas* cdata = new TCanvas(name, title, 1500, 500);
  cdata->Divide(1,1);
  
  // FIT
  cdata->cd(1);
  RooPlot* frame = mass.frame() ; 
  data->plotOn(frame) ; 
  model.plotOn(frame) ;    
  model.plotOn(frame,Components(mass_sig),LineStyle(kDashed),LineColor(kRed)) ;   
  model.plotOn(frame,Components(mass_bkg),LineStyle(kDashed),LineColor(kGreen)) ;   
  frame->SetTitle("Fit of model to discriminating variable");
  frame->Draw() ;
  
   // // SWEIGHTS SPLIT nShared
   // cdata->cd(3);
   // RooPlot* frame2 = nShared.frame(Bins(10)) ; 
   // dataw_sig->plotOn(frame2, DataError(RooAbsData::SumW2) ) ; 
   // frame2->SetTitle("nShared distribution for sig");
   // frame2->Draw() ;
   // cdata->cd(4);
   // RooPlot* frame3 = nShared.frame(Bins(10)) ; 
   // dataw_bkg->plotOn(frame3,DataError(RooAbsData::SumW2) ) ; 
   // frame3->SetTitle("nShared distribution for bkg");
   // frame3->Draw();

   // SWEIGHTS SPLIT prob
   // cdata->cd(5);
   // RooPlot* frame4 = probMu.frame(Bins(30)) ; 
   // dataw_sig->plotOn(frame4, DataError(RooAbsData::SumW2) ) ; 
   // frame4->SetTitle("probMu distribution for sig");
   // frame4->Draw() ;
   // cdata->cd(6);
   // RooPlot* frame5 = probMu.frame(Bins(30)) ; 
   // dataw_bkg->plotOn(frame5,DataError(RooAbsData::SumW2) ) ; 
   // frame5->SetTitle("probMu distribution for bkg");
   // frame5->Draw();

   // // SWEIGHTS SPLIT prob
   // cdata->cd(7);
   // RooPlot* frame4 = probK.frame(Bins(30)) ; 
   // dataw_sig->plotOn(frame4, DataError(RooAbsData::SumW2) ) ; 
   // frame4->SetTitle("probK distribution for sig");
   // frame4->Draw() ;
   // cdata->cd(8);
   // RooPlot* frame5 = probK.frame(Bins(30)) ; 
   // dataw_bkg->plotOn(frame5,DataError(RooAbsData::SumW2) ) ; 
   // frame5->SetTitle("probK distribution for bkg");
   // frame5->Draw();

   // // SWEIGHTS SPLIT prob
   // cdata->cd(9);
   // RooPlot* frame4 = mchi2.frame(Bins(30)) ; 
   // dataw_sig->plotOn(frame4, DataError(RooAbsData::SumW2) ) ; 
   // frame4->SetTitle("mchi2 distribution for sig");
   // frame4->Draw() ;
   // cdata->cd(10);
   // RooPlot* frame5 = mchi2.frame(Bins(30)) ; 
   // dataw_bkg->plotOn(frame5,DataError(RooAbsData::SumW2) ) ; 
   // frame5->SetTitle("mchi2 distribution for bkg");
   // frame5->Draw();

   // // SWEIGHTS SPLIT prob
   // cdata->cd(11);
   // RooPlot* frame4 = distlog->frame(Bins(30)) ; 
   // dataw_sig->plotOn(frame4, DataError(RooAbsData::SumW2) ) ; 
   // frame4->SetTitle("distlog distribution for sig");
   // frame4->Draw() ;
   // cdata->cd(12);
   // RooPlot* frame5 = distlog->frame(Bins(30)) ; 
   // dataw_bkg->plotOn(frame5,DataError(RooAbsData::SumW2) ) ; 
   // frame5->SetTitle("distlog distribution for bkg");
   // frame5->Draw();

  // SAVE
  char filename[104]; sprintf(filename,"%s.png",name);
  cdata->SaveAs(filename,"png");
  
  // Save RooDataSet to RooWorkSpace
  TFile* outfile = new TFile("BJpsiK_DiMuonBiased_K_MagUp_StripMINE_0.root","RECREATE");
  RooWorkspace *space = new RooWorkspace("BJpsiK");
  RooDataSet* reduced = (RooDataSet*)Sdata->reduce("abs(B_MM-5279)<50.0");
  space->import(*reduced);
  space->Write();
  outfile->Close();
}

  
