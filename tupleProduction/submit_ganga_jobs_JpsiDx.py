## ------------------------------------------------------------
## For submitting DV jobs to the grid, with local DaVinci build
## and local Python modules
## Zishuo Yang, 2018-02-01
## ------------------------------------------------------------

j = Job( name = '2011MC_MU_Bc2JpsiDxKx') #application = Gauss(platform='x86_64-slc6-gcc49-opt', version='v42r5p1') , backend = Dirac() )
myApp = GaudiExec() #'DaVinci', 'v42r5p1', myPath='/afs/cern.ch/user/z/ziyang/cmtuser/')
myApp.directory='/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/DaVinciDev_v44r5'
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
                        "/afs/cern.ch/user/z/ziyang/work/RJpsiAnalysis/RJpsiLxplusCode/davinci/options/Bc_JpsiDx_MC.py",
                        ]
j.application.readInputData("DST/MC_2011_14873607_Beam3500GeV2011MagUpNu2BcVegPy_Sim08e_Digi13_Trig0x40760037_Reco14a_Stripping20r1NoPrescalingFlagged_ALLSTREAMS.DST.py")
j.backend = Dirac()
j.outputfiles = [ DiracFile("Bc_JpsiDx_MC.root") ] 
#j.backend.settings['BannedSites'] = ['LGC.CERN.cern'] #CERN sites failed all last time
j.splitter = SplitByFiles(filesPerJob=1)
j.backend.settings['CPUTime'] = 100000
j.submit()

