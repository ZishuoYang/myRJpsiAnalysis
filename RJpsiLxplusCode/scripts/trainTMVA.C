#include <TROOT.h>

#include <TApplication.h>
#include <TString.h>
#include <TStopwatch.h>

#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TFormula.h>
#include <TKey.h>

#include "TMVA/Factory.h"
#include "TMVA/Config.h"

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

const int NumMM2Bins = 50;
const double MinMM2 = -50;
const double MaxMM2 = 15;

const string ntpDefFile = "~/workspace/bcharm_mc_roots/Bc_MC.root";
const string ntpWeightFile = "~/workspace/bcharm_mc_roots/Bc_MCW.root";
const string outDir = "./";
const string outBasename = "trainedTMVA";

const int nSigTr = 2E4;
const int nSigTe = 2E4;
const int nBkgTr = 1.5E4;
const int nBkgTe = 1.5E4;

int trainTMVA()
{

  // START ROOT APPLICATION
  TApplication app();
  TStopwatch t;
  t.Start();

  // create chain of file to be processed
  TChain *chain = new TChain("DecayTree","");
  chain->Add(ntpDefFile.c_str());
  chain->AddFriend("weightTree",ntpWeightFile.c_str());

  Int_t nEvents = chain->GetEntries();
  cout << "Event num:  "<< nEvents << endl;

  char tauSelStr[100] = "MyBkgTag == 1";
  TH1F hTau("hTau","hTau",NumMM2Bins,MinMM2,MaxMM2);
  chain->Project("hTau","MissMass2",tauSelStr);
  
  char incSelStr[100] = "MyBkgTag % 10 == 2";
  TH1F hInc("hInc","hInc",NumMM2Bins,MinMM2,MaxMM2);
  chain->Project("hInc","MissMass2",incSelStr);


  // Print number of signal and bkg events
  Double_t nSig(hTau.Integral()), nBkg(hInc.Integral());
  cout << "Signal region: nSig " << nSig << ", nBkg " << nBkg << endl;

  // create TMVA factory
  TString trainedFileName = outDir + "/" + outBasename + ".root";
  TFile *fout = new TFile(trainedFileName,"recreate");
  TMVA::Factory *factory = new TMVA::Factory("train",fout);
  //  (TMVA::gConfig().GetIONames()).fWeightFileDir = outDir;

  TCut sigCut = tauSelStr;
  TCut bkgCut = incSelStr;
  factory->SetInputTrees(chain, sigCut, bkgCut);

  // ESTIMATED PARAMETERS
  factory->AddSpectator("MissMass2",'F');
  factory->AddSpectator("Q2",'F');
  factory->AddSpectator("BachMuEnergy",'F');
  factory->AddSpectator("TMath::Log(Lifetime)",'F');
  factory->AddSpectator("BachMu_ProbNNmu",'F');
  factory->AddSpectator("BachMu_cmult_0.75",'I');
  factory->AddSpectator("BachMu_ptasy_0.75",'F');
  factory->AddSpectator("BachMu_deltaPhi_0.75",'F');
  factory->AddSpectator("BachMu_deltaEta_0.75",'F');
  factory->AddSpectator("BachMu_cmult_totl",'I');
  factory->AddSpectator("Bc_MM");
  factory->AddSpecatator("Jpsi_MM",'F');

  // VERTEX PARAMETERS
  factory->AddVariable("TMath::Log(BachMu_PT)",'F');
  factory->AddVariable("TMath::Log(DeltaChi2)",'F');
  factory->AddVariable("BachMu_ptasy_totl",'F');
  factory->AddVariable("BachMu_deltaPhi_totl",'F');
  factory->AddVariable("BachMu_deltaEta_totl",'F');
  factory->AddVariable("TMath::Log(Bc_SMALLESTDELTACHI2)",'F');
  factory->AddVariable("Bc_SMALLESTDELTACHI2_MM");
  factory->AddVariable("TMath::Log(Jpsi_SMALLESTDELTACHI2)",'F');
  factory->AddVariable("Jpsi_SMALLESTDELTACHI2_MM",'F');
  factory->AddVariable("Pointing",'F'); // should be called Pointing

  // VERTEX ISOLATION VARIABLES
  factory->AddSpectator("Bc_NOPARTWITHINDCHI2_25",'I');

  // FLIGHT DISTANCES AND IMPACT PARAMETERS
  factory->AddSpectator("TMath::Log(Bc_FD_OWNPV)",'F');
  factory->AddSpectator("TMath::Log(Bc_FDCHI2_OWNPV)",'F'); // correlated with Lifetime
  factory->AddSpectator("TMath::Log(1-Bc_DIRA_OWNPV)",'F');
  factory->AddSpectator("TMath::Log(Jpsi_FD_OWNPV)",'F');
  factory->AddSpectator("TMath::Log(Jpsi_FDCHI2_OWNPV)",'F');
  factory->AddSpectator("TMath::Log(1-Jpsi_DIRA_OWNPV)");
  factory->AddSpectator("TMath::Log(BachMu_IP_OWNPV)",'F');
  factory->AddSpectator("TMath::Log(BachMu_IPCHI2_OWNPV)",'F');
  
  // Setup TMVA Factory
  factory->SetWeightExpression("weight"); 
  factory->PrepareTrainingAndTestTree("",nSigTr,nBkgTr,nSigTe,nBkgTe,"SplitMode=Random");
  
  factory->BookMethod(TMVA::Types::kLikelihood,"Likelihood","NSmooth=5:NAvEvtPerBin=100");
  //  factory->BookMethod(TMVA::Types::kBDT,"BDT","BoostType=AdaBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity");
  factory->BookMethod(TMVA::Types::kCFMlpANN,"CF_ANN");
                                                        
  // Run TMVA Factory
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  // Close File
  fout->Close();

  ////////////////
  TFormula f("sigf","x/sqrt(x+y)"); //"S/sqrt(S+B)");
  TString methodName, methodTitle;
  TH1*     sig;
  TH1*     bgd;
  TH1*     origSigE;
  TH1*     origBgdE;
  TH1*     sigE;
  TH1*     bgdE;
  TH1*     purS;
  TH1*     sSig;    
  TH1*     effpurS;

  TFile *fout2; fout2 = new TFile(trainedFileName); // reopen file to avoid error



  // retrieve and print the cut that maximize the significance from factory output

  // search for the right histograms in full list of keys
  TIter next(gDirectory->GetListOfKeys());
  TKey *key(0);   
  while( (key = (TKey*)next()) ) {

    if (!TString(key->GetName()).BeginsWith("Method_")) continue;
    if( ! gROOT->GetClass(key->GetClassName())->InheritsFrom("TDirectory") ) continue;

    cout << "--- Found directory: " << ((TDirectory*)key->ReadObj())->GetName() << endl;

    TDirectory* mDir = (TDirectory*)key->ReadObj();

    TIter keyIt(mDir->GetListOfKeys());
    TKey *titkey;
    while((titkey = (TKey*)keyIt())) {

      if( ! gROOT->GetClass(titkey->GetClassName())->InheritsFrom("TDirectory") ) continue;
        
      TDirectory* titDir = (TDirectory *)titkey->ReadObj();

      methodName = key->GetName(); methodName.ReplaceAll("Method_","");
      methodTitle = titDir->GetName(); 

      //      if (methodTitle.Length() > maxLenTitle) maxLenTitle = info->methodTitle.Length();
      TString hname = "MVA_" + methodTitle;
        
      cout << "--- Classifier: " << methodTitle << endl;
        
      sig = (TH1*)(titDir->Get( hname + "_S" ));
      bgd = (TH1*)(titDir->Get( hname + "_B" ));
      origSigE = (TH1*)(titDir->Get( hname + "_effS" ));
      origBgdE = (TH1*)(titDir->Get( hname + "_effB" ));      
      if (origSigE==0 || origBgdE==0) { cout <<"error in reading histo" << endl; continue; }

      TString pname    = "purS_"         + methodTitle;
      TString epname   = "effpurS_"      + methodTitle;
      TString ssigname = "significance_" + methodTitle;

      sigE = (TH1*)origSigE->Clone("sigEffi");
      bgdE = (TH1*)origBgdE->Clone("bgdEffi");
      
      Int_t nbins = sigE->GetNbinsX();
      Double_t low = sigE->GetBinLowEdge(1);
      Double_t high = sigE->GetBinLowEdge(nbins+1);
      purS    = new TH1F(pname, pname, nbins, low, high);
      sSig    = new TH1F(ssigname, ssigname, nbins, low, high);
      effpurS = new TH1F(epname, epname, nbins, low, high);        

      // chop off useless stuff
      sigE->SetTitle( Form("Cut efficiencies for %s classifier", methodTitle.Data()) );
         
      for (Int_t i=1; i<=origSigE->GetNbinsX(); i++) {
        Float_t eS = origSigE->GetBinContent( i );
        Float_t S = eS * nSig;
        Float_t B = origBgdE->GetBinContent( i ) * nBkg;
        purS->SetBinContent( i, (S+B==0)?0:S/(S+B) );
        sSig->SetBinContent( i, f.Eval(S,B) );
        effpurS->SetBinContent( i, eS*purS->GetBinContent( i ) );
      }
      
      Double_t maxSignificance = sSig->GetMaximum();
      //     sSig->Scale(1/maxSignificance);
      Int_t maxbin = sSig->GetMaximumBin();
      Double_t optCut = sSig->GetXaxis()->GetBinCenter(maxbin);
      cout << "--- Classifier: " << methodTitle 
	   << " OptCut: " << optCut << " Max Significance: " << maxSignificance << endl;

    }

  }

  // CLOSE
  fout->Close();
  cout << "RealTime = "<< t.RealTime() << "  seconds" << endl
       << "CpuTime =  "<< t.CpuTime() << "  seconds" << endl;
  return 0;
}

