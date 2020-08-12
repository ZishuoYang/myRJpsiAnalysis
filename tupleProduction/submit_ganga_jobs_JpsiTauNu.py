## ------------------------------------------------------------
## For submitting DV jobs to the grid, with local DaVinci build
## and local Python modules
## Zishuo Yang, 2018-02-01
## ------------------------------------------------------------

j = Job( name = 'new_2016_MC_MD_Bc2JpsiTau') #application = Gauss(platform='x86_64-slc6-gcc49-opt', version='v42r5p1') , backend = Dirac() )
myApp = GaudiExec() #'DaVinci', 'v42r5p1', myPath='/afs/cern.ch/user/z/ziyang/cmtuser/')
myApp.directory='/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/DaVinci_v44r5'
j.application = myApp
j.application.platform="x86_64-centos7-gcc62-opt"
j.inputfiles = [LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/IsolationBDT/weightsSoft.xml"),
                LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/modules/Refitter.py"),
                LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/modules/Selection.py"),
                LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/modules/Filters.py"),
                LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/modules/JpsiRecTuple.py"),
                LocalFile("/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/modules/MCTuples.py"),
                ]
j.application.options = [
                        "/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/Bc_JpsiTau_MC.py",
                        ]
j.application.readInputData("DST/MC_2016_14643048_Beam6500GeV2016MagDownNu1.625nsBcVegPyPythia8_Sim09c_Trig0x6138160F_Reco16_Turbo03_Stripping28NoPrescalingFlagged_ALLSTREAMS.DST.py")
j.backend = Dirac()
j.outputfiles = [ DiracFile("Bc_JpsiTau_MC.root") ] 
#j.backend.settings['BannedSites'] = ['LGC.CERN.cern'] #CERN sites failed all last time
j.splitter = SplitByFiles(filesPerJob=5)
j.backend.settings['CPUTime'] = 100000
j.submit()

