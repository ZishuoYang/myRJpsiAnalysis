def getLFNList(dataset):
    lfnlist = []
    lfnsublist = []
    count = 0
    num = 1
    for f in dataset.files:
        if (count==num):
            lfnlist.append(lfnsublist)
            count = 0
            lfnsublist = []
        if not "_histos.root" in f.name:
            lfnsublist.append('LFN:' + f.name)
            count += 1
    if (lfnsublist != []):
        lfnlist.append(lfnsublist)
    return lfnlist

def submitOfflineJob(jname,mode,dataset):
    
    homeDir = os.environ['HOME']
    baseDir = homeDir + '/LHCb/bcharm/BcProcessor/'
    pidDir = homeDir + '/LHCb/bcharm/PidMatrix/'
    
    
    objects = [
        baseDir + 'libBcProcessor.so'
        , pidDir + 'PidMatrix_NN.root'
        , pidDir + 'IdWeights_NN.root'
        , pidDir + 'PidMatrix_DLL.root'
        , pidDir + 'IdWeights_DLL.root'
        ]

    lfnlist = getLFNList(dataset)
                        
    # CREATE SPLITTER
    s = GenericSplitter()
    s.attribute = 'backend.inputSandboxLFNs'
    s.values = lfnlist
    
    # CREATE JOB
    selection = Job(
        name = jname
        , inputsandbox = objects
        , application = Root( version="5.34.24"
                              , usepython = False
                              , script = baseDir + 'runBcProcessor.C'
                              , args = [mode]
                              )
        , backend = Dirac(settings={"CPUTime":3600})
        , splitter = s
        , outputfiles = [LocalFile("*MICRO.root")]
        , postprocessors = [RootMerger(files=['*MICRO.root'],ignorefailed=True)]
        )
    

def submitOfflineLeftovers(j):
    files = []
    for s in j.subjobs:
        if (s.status != "completed"):
            files += s.backend.inputSandboxLFNs.copy()
    newj = j.copy()
    newj.unprepare()
    data = LHCbDataset()
    data.files = files
    lfnlist = getLFNList(data)
    newj.splitter.values = lfnlist

