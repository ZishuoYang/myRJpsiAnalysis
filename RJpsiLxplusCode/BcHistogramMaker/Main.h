#ifndef MAIN_H
#define MAIN_H

#include "TObject.h"
#include "TList.h"

#include <memory>

extern int a_main(int, char**);

class Main : public TObject {
public:
  Main(){} // needed by Root IO
  Main(TList* args);
  int run();
  
private:
  std::auto_ptr<TList> args;
  ClassDef(Main,1) // needed for Cint
};

#endif
  
