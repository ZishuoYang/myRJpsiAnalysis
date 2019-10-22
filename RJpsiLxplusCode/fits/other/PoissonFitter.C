#include "TFile.h"
#include "TTree.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFormulaVar.h"
#include "RooExponential.h"
#include "RooPoisson.h"
#include "RooAddPdf.h"
#include "RooPlot.h"

#include <iostream>
#include <string>
using namespace std;

RooPlot* PoissonFitter() 
{

  // OPENING ROOT FILE
  string HistoFile = "result.root";
  TFile inputFile(HistoFile.c_str(),"READ");
  if (inputFile.IsZombie()) {
    cout << "ERROR: input file not found" << endl;
    return 0;
  } else  {
    cout << "Input file opened successfully" << endl;
  }

  TTree* tree = (TTree*)inputFile.Get("DecayTree");
  RooRealVar x ("Bc_NOPARTWITHINDCHI2WDW","# part.s w/i dchi^2 wdw",0,10);
  RooDataSet data ("data","data set",tree,RooArgSet(x));
  x.setRange("R",0.0,10.0);
  
  RooRealVar mean0 ("mean0","mean0",2E-5,1E-5,5);
  RooRealVar mean1m0 ("mean1m0","mean1m0",1,0,5);
  RooFormulaVar mean1 ("mean1","mean1","@0+@1",RooArgList(mean0,mean1m0));
  RooRealVar mean2m1 ("mean2m1","mean2m1",1,0,5);
  RooFormulaVar mean2 ("mean2","mean2","@0+@1+@2",RooArgList(mean0,mean1m0,mean2m1));

  //  RooRealVar decay ("decay","decay",0,-10,10);
  //  RooExponential exp ("exp","exp",x,decay);
  RooPoisson pois0 ("pois0","pois0",x,mean0);
  RooPoisson pois1 ("pois1","pois1",x,mean1);
  RooPoisson pois2 ("pois2","pois2",x,mean2);

  RooRealVar num0 ("num0","num0",1,0,100000);
  RooRealVar num1 ("num1","num1",1,0,100000);
  RooRealVar num2 ("num2","num2",1,0,100000);

  //  RooAddPdf model ("model","model",RooArgList(pois0,pois1),RooArgList(num0,num1));
  RooAddPdf model ("model","model",RooArgList(pois0,pois1,pois2),RooArgList(num0,num1,num2));

  model.fitTo(data,RooFit::Extended(),RooFit::Range("R"));
  RooPlot* xframe = x.frame();
  data.plotOn(xframe,RooFit::Range("R"));
  model.plotOn(xframe,RooFit::Range("R"));
  model.plotOn(xframe,RooFit::Range("R"),RooFit::Components("pois0"),RooFit::LineStyle(kDashed));
  model.plotOn(xframe,RooFit::Range("R"),RooFit::Components("pois1"),RooFit::LineStyle(kDashed),RooFit::LineColor(kRed));
  model.plotOn(xframe,RooFit::Components(pois2),RooFit::LineStyle(kDashed),RooFit::LineColor(kMagenta));  
  xframe->Draw();
  return xframe;
}

