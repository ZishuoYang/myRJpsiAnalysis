void runBcHistogramMaker(char* arg1 = "", char* arg2 = "") {
  
  //load the shared library
  gSystem->Load("libBcHistogramMaker");
  
  //set up main, eg command line opts
  TList* args = new TList();
  
  args->Add(new TObjString("foo_exe"));
  //program name
  args->Add(new TObjString(arg1));
  args->Add(new TObjString(arg2));

  //run the code
  Main m(args);
  
  int returnCode = m.run();
  
  // Prevent ROOT from hanging (encountered with ROOT 5.26.00.b)
  gApplication->Terminate();
  
}
