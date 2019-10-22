# DAVINCI JOB TO RUN OFFLINE SELCTION ON
JOBNUMS = [325,326,327,328]

import sys
import os

homeDir = os.environ['HOME']
baseDir = homeDir + '/LHCb/bcharm/BcHistogramMaker_GRID/'

files = [
    baseDir + 'libBcHistogramMaker.so'
    , baseDir + 'PidMatrix.root'
    ]

for JOBNUM in JOBNUMS:

    job = jobs(JOBNUM)

    # GET NAME
    str = job.name
    str = str.split('_')[0]

    # GET DATA
    lfns = job.backend.getOutputDataLFNs() # to put into backend.inputSandboxLFNs

    # THROW OUT HISTOS
    data = LHCbDataset()
    for f in lfns.files:
        if not "_histos.root" in f.name:
            data.files.append(f)

    # CREATE SPLITTER
    s = GenericSplitter()
    s.attribute = 'backend.inputSandboxLFNs'
    s.values = []
    for lfn in data:
        s.values.append([lfn])

    # CREATE JOB
    selection = Job(
        name = job.name + "_SELECTION"
        , inputsandbox = files
        , application = Root( version = '5.34.10'
                              , usepython = False
                              , script = baseDir + 'runBcHistogramMaker.C'
                              , args = [str,"JpsiRecTuple"]
                              )
        , backend = Dirac(settings={"CPUTime":3600})
        , splitter = s
        , outputfiles = [SandboxFile("*HISTOGRAMS.root")]
        , postprocessors = [RootMerger(files=['*HISTOGRAMS.root'],ignorefailed=True)]
        #, inputdata = data # to use T1
        #, splitter = SplitByFiles(filesPerJob=5)
        )
    
        
