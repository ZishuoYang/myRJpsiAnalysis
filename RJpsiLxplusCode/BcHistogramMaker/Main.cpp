#include <iostream>
using std::cout;
using std::endl;

#include "Main.h"
#include "TList.h"
#include "TObject.h"
#include "TObjString.h"
#include "TString.h"

#include <cstring>

ClassImp(Main) // needed for Cint

Main::Main(TList* _args):
  args(_args)
{
}

int Main::run() {
  // convert the TList args into a main compatible list
  const Int_t argc = args->GetSize();
  // memory is dynamically allocated
  char** argv = new char*[argc];
  
  TObjLink *lnk = args->FirstLink();
  Int_t count = 0;
  while (lnk) {
    const char* str = ((TObjString*)lnk->GetObject())->String();
    argv[count] = new char[strlen(str)];
    strcpy(argv[count],str);
    lnk = lnk->Next();
    count++;
  }
  Int_t result = a_main(argc,argv);
  
  // clean up
  for (int i = 0; i < argc; i++)
    delete argv[i];
  delete argv;
  
  return result;
}

    
