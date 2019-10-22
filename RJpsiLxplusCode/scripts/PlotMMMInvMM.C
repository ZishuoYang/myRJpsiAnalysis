void PlotMMMInvMM() 
{

  string invmm = "sqrt((muplus0_TRUEP_E + J_psi_1S_TRUEP_E)^2-(muplus0_TRUEP_X+J_psi_1S_TRUEP_X)^2-(muplus0_TRUEP_Y+J_psi_1S_TRUEP_Y)^2-(muplus0_TRUEP_Z+J_psi_1S_TRUEP_Z)^2)";

  string mup = "sqrt((muplus0_TRUEPT)^2+(muplus0_TRUEP_Z)^2)";

  string FAKEDOCA

  string acceptance = "(muplus0_TRUEP_Z>0) && (muplus0_TRUEPT/muplus0_TRUEP_Z<sin(0.400)) && (muplus0_TRUEPT/muplus0_TRUEP_Z>sin(0.100))";
  string ptcut = "(muplus0_TRUEPT>250)";
  string pcut = "(" + mup + ">2500)";
  string mmcut = "(" + invmm + "<6500)";
  string totalcut = acceptance + " && " + ptcut + " && " + pcut + " && " + mmcut;

  SemiLepDecayTree->Draw(totalcut.c_str());
  //  SemiLepDecayTree->Draw(invmm.c_str(),totalcut.c_str(),"");

}

