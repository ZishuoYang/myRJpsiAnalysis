string bkgcut = "!Bc_Bc2JpsiMuNu";

string cutstr(int num) 
{
  const char str[100];
  sprintf(str,"Bc_BKGCAT==%d",num);
  string ret = string(str);
  if (bkgcut != "")
    ret += " && " + bkgcut;
  return ret;
}

Long_t raw_num(int num) 
{
  string cut;
  if (num >= 0)
    cut = cutstr(num);
  else
    cut = bkgcut;
  return DecayTree->Draw("",cut.c_str());
}


Double_t weighted_num(int num) 
{
  string cut;
  if (num >= 0)
    cut = "weight/W*(" + cutstr(num) + ")";
  else if (bkgcut != "")
    cut = "weight/W*(" + bkgcut + ")";
  else
    cut = "weight/W";
  TH1F* htemp = new TH1F("htemp","htemp",100,-100,100);
  DecayTree->Draw("MissMass2>>htemp",cut.c_str());
  double N = htemp->Integral();
  long c = static_cast<long>(N);
  return c;
}


void bkgtable() 
{
  long ntotal = raw_num(-1);
  long n30 = raw_num(30);
  long n40 = raw_num(40);
  long n50 = raw_num(50);
  long n60 = raw_num(60);
  long n63 = raw_num(63);
  long n66 = raw_num(66);
  long n70 = raw_num(70);
  long n100 = raw_num(100);
  long n110 = raw_num(110);

  cout << "Ntotal (Raw): " << ntotal << endl;
  cout << "Frac(MisID): " << n30/double(ntotal) << endl;
  cout << "Frac(Inc): " << (n40+n50)/double(ntotal) << endl;
  cout << "Frac(Ghost): " << (n60+n63+n66)/double(ntotal) << endl;
  cout << "Frac(PV): " << n70/double(ntotal) << endl;
  cout << "Frac(Pileup): " << n100/double(ntotal) << endl;
  cout << "Frac(BB): " << n110/double(ntotal) << endl;

  cout << "-------------------------" << endl;
  
  double dtotal = weighted_num(-1);
  double d30 = weighted_num(30);
  double d40 = weighted_num(40);
  double d50 = weighted_num(50);
  double d60 = weighted_num(60);
  double d63 = weighted_num(63);
  double d66 = weighted_num(66);
  double d70 = weighted_num(70);
  double d100 = weighted_num(100);
  double d110 = weighted_num(110);

  cout << "Ntotal (Weighted): " << dtotal << endl;
  cout << "Frac(MisID): " << d30/double(dtotal) << endl;
  cout << "Frac(Inc): " << (d40+d50)/double(dtotal) << endl;
  cout << "Frac(Ghost): " << (d60+d63+d66)/double(dtotal) << endl;
  cout << "Frac(PV): " << d70/double(dtotal) << endl;
  cout << "Frac(Pileup): " << d100/double(dtotal) << endl;
  cout << "Frac(BB): " << d110/double(dtotal) << endl;
}
