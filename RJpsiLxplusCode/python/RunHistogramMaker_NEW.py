MODES = ["Data10Per"]
YEARS = ["2012"]
POLARITIES = ["Up","Down"]

import sys
import os
from math import exp

homeDir = os.environ['HOME']
baseDir = homeDir + '/LHCb/bcharm/BcHistogramMaker/'

objects = [
    baseDir + 'libBcHistogramMaker.so'
    ]

for mode in MODES:
    for year in YEARS:
        for pol in POLARITIES:

            datasetfile = homeDir + "/python/datasets/" + mode + "_" + year + "_" + pol + ".py"
            execfile(datasetfile)
            lfnlist = []
            for f in dataset.files:
                if not "_histos.root" in f.name:
                    lfnlist.append(['LFN:' + f.name])
                    
            # CREATE SPLITTER
            s = GenericSplitter()
            s.attribute = 'backend.inputSandboxLFNs'
            s.values = lfnlist
                
            # CREATE JOB
            selection = Job(
                name = mode + "_HISTOS"
                , inputsandbox = objects
                , application = Root( version = '5.34.10'
                                      , usepython = False
                                      , script = baseDir + 'runBcHistogramMaker.C'
                                      , args = [mode]
                                      )
                , backend = Dirac(settings={"CPUTime":3600})
                , splitter = s
                , outputfiles = [SandboxFile("*HISTOGRAMS.root")]
                , postprocessors = [RootMerger(files=['*HISTOGRAMS.root'],ignorefailed=True)]
                #, inputdata = lfnlist # to use T1
                #, splitter = SplitByFiles(filesPerJob=5)
                )
            
        
