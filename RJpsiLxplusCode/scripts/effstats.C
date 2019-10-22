string bkgcut = "MyBkgTag==1";

string cutstr(int num) 
{
  const char str[100];
  sprintf(str,"Bc_BKGCAT==%d",num);
  string ret = string(str);
  if (bkgcut != "")
    ret += " && " + bkgcut;
  return ret;
}

Double_t avg_weight(int num = -1, int num2 = -1, int num3 = -1) 
{
  string cut = "w_CalibDLL_MED*(";
  if (bkgcut != "")
    cut += bkgcut;
  else
    cut += string("1==1");
  if (num >= 0) {
    cut += " && (" + cutstr(num);
    if (num2 >= 0) {
      cut += " || " + cutstr(num2);
      if (num3 >= 0) 
        cut += " || " + cutstr(num3);
    }
    cut += ")";
  }
  cut + = ")";
  cout << cut << endl;
  TH1F* htemp = new TH1F("htemp","htemp",100,0,1.1);
  DecayTree->Draw("w_CalibDLL_MED>>htemp",cut.c_str());
  double M = htemp->GetMean(1);
  delete htemp;
  return M;
}


void effstats() 
{
  double dtotal = avg_weight();
  double d30 = avg_weight(30);
  double d40 = avg_weight(40,50);
  double d60 = avg_weight(60,63,66);
  double d70 = avg_weight(70);
  double d100 = avg_weight(100);
  double d110 = avg_weight(110);

  cout << "Total Weight: " << dtotal << endl;
  cout << "Weight(MisID): " << d30 << endl;
  cout << "Weight(Inc): " << d40 << endl;
  cout << "Weight(Ghost): " << d60 << endl;
  cout << "Weight(PV): " << d70 << endl;
  cout << "Weight(Pileup): " << d100 << endl;
  cout << "Weight(BB): " << d110 << endl;
}
