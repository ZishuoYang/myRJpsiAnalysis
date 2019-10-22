CXX = g++
CXXFLAGS = -O -Wall -fPIC -g -ansi
LD = g++
LDFLAGS = -O
SOFLAGS = -shared

all: $(TARGET)

ROOTCONFIG := $(ROOTSYS)/bin/root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --ldflags) $(shell $(ROOTCONFIG) --libs)

CXXFLAGS += $(ROOTCFLAGS)
LDFLAGS += $(ROOTLDFLAGS)

ACLICKHEADERS = Main.h
ACLICKSOURCE = Main.cpp
ACLICKOBJS = rootdict.o Main.o

HEADERS = BcConstants.h RecSelector.h JpsiMuMCSelector.h JpsiTauMCSelector.h
SOURCE = BcHistogramMaker.cpp RecSelector.C JpsiMuMCSelector.C JpsiTauMCSelector.h
SOURCE += $(ACLICKSOURCE)
OBJS = BcHistogramMaker.o RecSelector.o JpsiMuMCSelector.o JpsiTauMCSelector.o
OBJS += $(ACLICKOBJS)

EXE = BcHistogramMaker_exe
SHAREDLIB = libBcHistogramMaker.so

all: $(EXE)

lib: $(SHAREDLIB)

$(EXE): $(HEADERS) $(OBJS) main.o
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) main.o -o $(EXE)

$(SHAREDLIB): $(HEADERS) $(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) -$(SOFLAGS) -o $(SHAREDLIB)

rootdict.cpp: $(ACLICKHEADERS)
	@echo "Making the rootdict"
	@$(ROOTSYS)/bin/rootcint -f rootdict.cpp -c $(ACLICKHEADERS)

clean:
	@rm -f $(OBJS) rootdict.h rootdict.cpp main.o $(EXE) $(SHAREDLIB)