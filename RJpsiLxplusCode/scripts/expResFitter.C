using namespace RooFit;
void expResFitter() {

  TFile* dataFile = new TFile("Bc_MC.root","READ");
  TTree* dataTree = (TTree*)dataFile->Get("DecayTree");

  RooRealVar lt("Lifetime","lt",0.1,8.0);
  RooRealVar tlt("TrueLifetime","tlt",0.0,10.0);
  RooRealVar mm2("MissMass2","mm2",-3.0,10.0);
  RooRealVar tag("MyBkgTag","tag",0.0);
  RooDataSet wdata("wdata","wdata",RooArgSet(lt,tlt,mm2,tag),Import(*dataTree));
  RooDataSet data("data","data",RooArgSet(lt,tlt,mm2),Import(wdata),Cut("MyBkgTag%10==0"));
  RooFormulaVar error_func("error","(@0-0.001*@1)/(0.001*@1)",RooArgList(lt,tlt));
  RooFormulaVar loglt_func("loglt","log(@0)",RooArgList(lt));
  RooRealVar* error = (RooRealVar*)data.addColumn(error_func);
  error->setRange(-1.0,1.0);
  RooRealVar* loglt = (RooRealVar*)data.addColumn(loglt_func);
  loglt->setRange(-3.0,3.0);
  RooPlot* f = lt.frame();
  data.plotOn(f);
  f->Draw();
}
