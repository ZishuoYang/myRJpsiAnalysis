#include "constants.hh"

TString files(int n) {
  if (n < numMCSamples)
    return mcfiles[n];
  n -= numMCSamples;
  if (n < numDataDrivenSamples)
    return datadrivenfiles[n];
  n -= numDataDrivenSamples;
  if (n < numDataSamples)
    return datafiles[n];
  return "FAILURE";
}

TString cuts(int n) {
  if (n < numMCSamples)
    return mccuts[n];
  n -= numMCSamples;
  if (n < numDataDrivenSamples)
    return datadrivencuts[n];
  n -= numDataDrivenSamples;
  if (n < numDataSamples)
    return datacuts[n];
  return "FAILURE";
}

TString histos(int n) {
  if (n < numMCSamples)
    return mchistos[n];
  n -= numMCSamples;
  if (n < numDataDrivenSamples)
    return datadrivenhistos[n];
  n -= numDataDrivenSamples;
  if (n < numDataSamples)
    return datahistos[n];
  return "FAILURE";
}

void MakeFitHistograms() {
  
  const int N = numMCSamples + numDataDrivenSamples + numDataSamples;
  
  // Create output file
  TFile* OutFile = new TFile(locTemplates,"RECREATE");

  TH3F* templates[N];

  // loop over all files -- mc, datadriven, and data

	TString varexp;
	TString cut;
  for (int f = 0; f < N; f++) {

    // create histo
    TString name = "h_" + histos(f);
    cout << "Creating " << name << " ...\n";
    templates[f] = new TH3F(name.Data(),name.Data(),mm2_bins,mm2_low,mm2_high,loglt_bins,loglt_low,loglt_high,q2_bins,q2_low,q2_high);
	
    // load file
    TString file = files(f);
    TFile *temp = new TFile(file);
    TTree* tree = (TTree*)temp->Get("DecayTree");

    // draw


		// Bc MC w/ LIFETIME CORRECTION
		if (f == numMCSamples-1) { // psi2s is special for now
			cut = cuts(f);
			varexp = TString("Bc_MM/1000:log(Lifetime):MissMass2");
		} else if (f == N-1) { // data is special for now
			cut = cuts(f);
			varexp = TString("YM:log(YTAU):MM2");
		} else {
			//cut = TString("((abs(pidWeight) <= 1) ? pidWeight : 0) * (") + cuts(f) + TString(")");
			cut = TString("pidWeight * (") + cuts(f) + TString(")");
			varexp = TString("YM:log(YTAU):MM2");
		}
    templates[f]->SetDirectory(temp);
		Long64_t num;	
		cout << "Starting to draw..." << endl;
		cout << "VARS: " << varexp << endl;
		cout << "CUT: " << cut << endl;
    num = tree->Project(name.Data(),varexp.Data(),cut.Data());

	
		// set negative bins to 1e-9	
		for (Int_t i = 0; i <= mm2_bins; i++) {
			for (Int_t j = 0; j <= loglt_bins; j++) {
				for (Int_t k = 0; k <= q2_bins; k++) {
					Int_t bin = templates[f]->GetBin(i,j,k);
					Double_t e = templates[f]->GetBinContent(bin);
//				cout << e << endl;
					if (e <= 0) {
						templates[f]->SetBinContent(bin,1e-9);
						templates[f]->SetBinError(bin,1e-9);
					}
				}
			}
		}
	
    cout << "Entries in histogram: " << num << endl;
    OutFile->cd();
    templates[f]->SetDirectory(OutFile);
    templates[f]->Write();

    // close file
    temp->Close();
		delete templates[f];
  }
  
  // Close Output File
  OutFile->Close();
}
