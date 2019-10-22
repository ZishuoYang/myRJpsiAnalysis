// struct NearNeighbors {
//   Double_t val;
//   Double_t N, S, E, W, NE;
// };

// struct NextNearNeighbors {
//   Double_t UL, ULX, ULY, ULXY;
//   Double_t UR, URX, URY, URXY;
//   Double_t LL, LLX, LLY, LLXY;
//   Double_t LR, LRX, LRY, LRXY;
// };

// Double_t DX(NearNeighbors x) {
//   return (x.E - x.W)/2.0;
// }

// Double_t DY(NearNeighbors x) {
//   return (x.N - x.S)/2.0;
// }

// Double_t DXY(NearNeighbors x) {
//   return (x.N - x.S)/2.0;
// }

// NextNearNeighbors GetNNNFromNNs(NearNeighbors ul, NearNeighbors ur, NearNeighbors ll, NearNeighbors lr) {
//   NextNearNeighbors x;
//   x.UL = ul.val;
//   x.UR = ur.val;
//   x.LL = ll.val;
//   x.LR = lr.val;
//   x.ULX = 
// }

// Double_t Sum(std::vector<Double_t> v) {
//   Double_t last = v.back();
//   v.pop_back();
//   if (v.empty()) {
//     return last;
//   } else {
//     Double_t rest = Sum(v);
//     return last + rest;
//   }
// }

// Double_t QuadSum(std::vector<Double_t> v) {
//   Double_t last = v.back();
//   v.pop_back();
//   if (v.empty()) {
//     return last;
//   } else {
//     Double_t rest = QuadSum(v);
//     return TMath::Sqrt(last*last + rest*rest);
//   }
// }

Double_t Linear(Double_t* vals) {
  return vals[1][1]
}

TH1D* HistPdfSmoothness(TH2F* hist) {

  Int_t nx = hist->GetNbinsX();
  Int_t ny = hist->GetNbinsY();

  TH1D* pull_hist = new TH1D("pull_hist","pull_hist",100,-5.0,5.0);

  // Loop over interior
  for (int i = 1; i < nx - 1; i++) {
    for (int j = 1; j < nx - 1; j++) {

      // Bin Value
      Double_t val = hist->GetBinContent(i,j);
      Double_t err = hist->GetBinError(i,j);

      Double_t vals[5][5]
      for (int di = -2; di <= 2; di++) {
	for (int dj = -2; dj <= 2; dj++) {
	  vals[di+2][dj+2] = hist->GetBinContent(i+di,j+dj);x
	}
      }

      // Bilinear interpolation (double)
      // Mean of all neighboring bins
      Double_t mean = Sum(neighbor_vals) / 8.0;

      // Bicubic Interpolation
      // This will take more work to set up
      //      Double_t inter = BiCubicInter(neighbor_vals);

      // Pull
      Double_t z = (val-mean)/err;
      pull_hist->Fill(z);
    }
  }

  return pull_hist;
}
