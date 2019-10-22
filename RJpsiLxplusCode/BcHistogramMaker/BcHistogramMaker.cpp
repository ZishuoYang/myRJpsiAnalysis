// Include files
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <assert.h>

#include <TChain.h>
#include <TParameter.h>

// local
#include "BcConstants.h"
#include "RecSelector.h"
#include "JpsiMuMCSelector.h"
#include "JpsiTauMCSelector.h"

int a_main( int argc, char** argv) {

  // Instantiate maps

  // NEEDS TO BE 2 arguments => argc = 3
  if (argc < 2)
    return 1;
  
  // FIRST ARGUMENT: TUPLE NAME
  TString dtsName = argv[1];

  TString rootName = root_dict[dtsName];
  TString vdirName = vdir_dict[dtsName];
  Bool_t isMC = isMC_dict[dtsName];  

  // ---------------------------------
  // PRODUCE RECONSTRUCTION HISTOGRAMS
  // ---------------------------------

  TChain *chain = new TChain("DecayTree","");

  TString tuplename = rootName + ".root/" + vdirName + "/DecayTree";
  cout << "Processing " << tuplename << ": " << endl;
  chain->Add(tuplename);
    
  TList optList;
  TParameter<int> parDts(dtsName,0); optList.Add(&parDts);

  RecSelector* mySel = new RecSelector();
  mySel->SetInputList(&optList);
  chain->Process(mySel);
  delete mySel;
  delete chain;

  // ------------------------------
  // PRODUCE MONTE CARLO HISTOGRAMS
  // ------------------------------

  if (isMC) {
    if (dtsName == TString("JpsiMuNu")) {
        TChain *mcchain = new TChain("MCBc2JpsiMuNuDecayTree","");
        TString tuplename = rootName + ".root/MCBc2JpsiMuNuTuple/MCBc2JpsiMuNuDecayTree";
        cout << "Processing " << tuplename << ": " << endl;
        mcchain->Add(tuplename);
        JpsiMuMCSelector *myMuSel = new JpsiMuMCSelector();
        myMuSel->SetInputList(&optList);
        mcchain->Process(myMuSel);
    } else if (dtsName == TString("JpsiTauNu")) {  
        TChain *mcchain = new TChain("MCBc2JpsiTauNuDecayTree","");
        TString tuplename = rootName + ".root/MCBc2JpsiTauNuTuple/MCBc2JpsiTauNuDecayTree";
        cout << "Processing " << tuplename << ": " << endl;
        mcchain->Add(tuplename);
        JpsiTauMCSelector *myTauSel = new JpsiTauMCSelector();
        myTauSel->SetInputList(&optList);
        mcchain->Process(myTauSel);
    } else {
      std::cout << "No MC Histogram Maker defined for this type yet ... " << std::endl;
    }
  }


  return 0;
}
