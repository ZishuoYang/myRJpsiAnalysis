void significance(const char* cut) 
{
  // char cut[50]; sprintf(cut,"BachMu_ProbNNmu>%f",num);
  string smustr = "W*(MyBkgTag==0 && (" + string(cut) + "))";
  string staustr = "W*(MyBkgTag==1 && (" + string(cut) + "))";
  string sbstr = "W*(MyBkgTag>1 && (" + string(cut) + "))";
  DecayTree->Project("hmu","MissMass2",smustr.c_str());
  DecayTree->Project("htau","MissMass2",staustr.c_str());
  DecayTree->Project("hb","MissMass2",sbstr.c_str());
  Double_t Smu = hmu->Integral();
  cout << "Smu: " << Smu << endl;
  Double_t Stau = htau->Integral();
  cout << "Stau: " << Stau << endl;
  Double_t B = hb->Integral();
  cout << "SB: " << B << endl;

  cout << cut << endl;
  cout << "Smu / B: " << Smu / double(B) << endl;
  cout << "Smu / sqrt(B): " << Smu / sqrt(B) << endl;
  cout << "Smu / sqrt(Smu + B): " << Smu / sqrt(Smu + B) << endl;
  cout << "Smu / sqrt(Smu + Stau + B): " << Smu / sqrt(Smu + Stau + B) << endl;
  cout << "Stau / B: " << Stau / double(B) << endl;
  cout << "Stau / sqrt(B): " << Stau / sqrt(B) << endl;
  cout << "Stau / sqrt(Stau + B): " << Stau / sqrt(Stau + B) << endl;
  cout << "Stau / sqrt(Smu + Stau + B): " << Stau / sqrt(Smu + Stau + B) << endl;
  cout << "(Smu + Stau) / B: " << (Smu + Stau) / double(B) << endl;
  cout << "(Smu + Stau) / sqrt(B): " << (Smu + Stau) / sqrt(B) << endl;
  cout << "(Smu + Stau) / sqrt(Smu + Stau + B): " << (Smu + Stau) / sqrt(Smu + Stau + B) << endl;
  
  
}
