from GangaService.Lib.ServiceAPI.ServiceAPI import GangaService

import sys
import os
from math import exp

def typedict(mode):
    type_dict = {
        "JpsiMuNu" : "MC"
        , "JpsiTauNu" : "MC"
        , "Psi2SMuNu" : "MC"
        , "Psi2STauNu" : "MC"
        , "Chic1MuNu" : "MC"
        , "Psi2SMuNu_JpsiPiPi" : "MC"
        , "Psi2STauNu_JpsiPiPi" : "MC"
        , "JpsiDx" : "MC"
        , "JpsiDxKx" : "MC"
        , "JpsiDxKxRes" : "MC"
        , "JpsiDsstst" : "MC"
        , "JpsiCharm3Body" : "MC"
        , "JpsiCharmQuasi2Body" : "MC"
        , "B0Comb6" : "MC"
        , "BpComb6" : "MC"
        , "BsComb6" : "MC"
        , "B0Comb8" : "MC"
        , "BpComb8" : "MC"
        , "BsComb8" : "MC"
        , "B0CombSideband" : "MC"
        , "BpCombSideband" : "MC"
        , "BsCombSideband" : "MC"
        , "MisID" : "Data"
        , "MisID10Per" : "Data"
        , "Data" : "Data"
        , "Data10Per" : "Data"
        , "PsiData" : "Data"
        , "JpsiPi" : "Data"
        , "JpsiPiMC" : "MC"
        , "JpsiK_Unbias" : "Data"
        , "JpsiKMC_Unbias" : "MC"
        , "JpsiKst_Unbias" : "Data"
        , "JpsiKstMC_Unbias" : "MC"
        , "JpsiKstData" : "Data"
        , "JpsiKstMC6" : "MC"
        , "JpsiKstMC8" : "MC"
        , "JpsiKData" : "Data"
        , "Psi2SCalData" : "Data"
        , "InclJpsiMC6" : "MC"
        , "InclJpsiMC8" : "MC"
        }
    return type_dict[mode]

def simdict(mode):
    sim_dict = {
        "JpsiMuNu" : "Sim08e"
        , "JpsiTauNu" : "Sim08e"
        , "Psi2SMuNu" : "Sim08e"
        , "Psi2STauNu" : "Sim08e"
        , "Chic1MuNu" : "Sim08e"
        , "Psi2SMuNu_JpsiPiPi" : "Sim08e"
        , "Psi2STauNu_JpsiPiPi" : "Sim08e"
        , "JpsiDx" : "Sim08e"
        , "JpsiDxKx" : "Sim08e"
        , "JpsiDxKxRes" : "Sim08e"
        , "JpsiDsstst" : "Sim08e"
        , "JpsiCharm3Body" : "Sim08h"
        , "JpsiCharmQuasi2Body" : "Sim08h"
        , "B0Comb6" : "Sim08d"
        , "BpComb6" : "Sim08d"
        , "BsComb6" : "Sim08d"
        , "B0Comb8" : "Sim08d"
        , "BpComb8" : "Sim08d"
        , "BsComb8" : "Sim08d"
        , "B0CombSideband" : "Sim08e"
        , "BpCombSideband" : "Sim08e"
        , "BsCombSideband" : "Sim08e"
        , "MisID" : "DATA"
        , "MisID10Per" : "DATA"
        , "Data" : "DATA"
        , "Data10Per" : "DATA"
        , "PsiData" : "DATA"
        , "JpsiPi" : "DATA"
        , "JpsiPiMC" : "Sim08a"
        , "JpsiK_Unbias" : "DATA"
        , "JpsiKMC_Unbias" : "Sim08a"
        , "JpsiKst_Unbias" : "DATA"
        , "JpsiKstMC_Unbias" : "Sim08c"
        , "JpsiKstData" : "DATA"
        , "JpsiKstMC6" : "Sim08c"
        , "JpsiKstMC8" : "Sim08c"
        , "JpsiKData" : "DATA"
        , "Psi2SCalData" : "DATA"
        , "InclJpsiMC6" : "Sim08a"
        , "InclJpsiMC8" : "Sim08b"
        }
    return sim_dict[mode]

def recodict(mode):
    reco_dict = {
        "JpsiMuNu" : "Reco14a"
        , "JpsiTauNu" : "Reco14a"
        , "Psi2SMuNu" : "Reco14a"
        , "Psi2STauNu" : "Reco14a"
        , "Chic1MuNu" : "Reco14a"
        , "Psi2SMuNu_JpsiPiPi" : "Reco14a"
        , "Psi2STauNu_JpsiPiPi" : "Reco14a"
        , "JpsiDx" : "Reco14a"
        , "JpsiDxKx" : "Reco14a"
        , "JpsiDxKxRes" : "Reco14a"
        , "JpsiDsstst" : "Reco14a"
        , "JpsiCharm3Body" : "Reco14c"
        , "JpsiCharmQuasi2Body" : "Reco14c"
        , "B0Comb6" : "Reco14a"
        , "BpComb6" : "Reco14a"
        , "BsComb6" : "Reco14a"
        , "B0Comb8" : "Reco14a"
        , "BpComb8" : "Reco14a"
        , "BsComb8" : "Reco14a"
        , "B0CombSideband" : "Reco14a"
        , "BpCombSideband" : "Reco14a"
        , "BsCombSideband" : "Reco14a"
        , "MisID" : "DATA"
        , "MisID10Per" : "DATA"
        , "Data" : "DATA"
        , "Data10Per" : "DATA"
        , "PsiData" : "DATA"
        , "JpsiPi" : "DATA"
        , "JpsiPiMC" : "Reco14a"
        , "JpsiK_Unbias" : "DATA"
        , "JpsiKMC_Unbias" : "Reco14a"
        , "JpsiKst_Unbias" : "DATA"
        , "JpsiKstMC_Unbias" : "Reco14a"
        , "JpsiKstData" : "DATA"
        , "JpsiKstMC6" : "Reco14a"
        , "JpsiKstMC8" : "Reco14a"
        , "JpsiKData" : "DATA"
        , "Psi2SCalData" : "DATA"
        , "InclJpsiMC6" : "Reco14a"
        , "InclJpsiMC8" : "Reco14a"
        }
    return reco_dict[mode]

def gendict(mode):
    gen_dict = {
    "JpsiMuNu" : "BcVegPy"
    , "JpsiTauNu" : "BcVegPy"
    , "Psi2SMuNu" : "BcVegPy"
    , "Psi2STauNu" : "BcVegPy"
    , "Chic1MuNu" : "BcVegPy"
    , "Psi2SMuNu_JpsiPiPi" : "BcVegPy"
    , "Psi2STauNu_JpsiPiPi" : "BcVegPy"
    , "JpsiDx" : "BcVegPy"
    , "JpsiCharmQuasi2Body" : "BcVegPy"
    , "JpsiCharm3Body" : "BcVegPy"
    , "B0Comb6" : "Pythia6"
    , "BpComb6" : "Pythia6"
    , "BsComb6" : "Pythia6"
    , "B0Comb8" : "Pythia8"
    , "BpComb8" : "Pythia8"
    , "BsComb8" : "Pythia8"
    , "MisID" : "NONE"
    , "MisID10Per" : "NONE"
    , "Data" : "NONE"
    , "Data10Per" : "NONE"
    , "PsiData" : "NONE"
    , "JpsiPi" : "NONE"
    , "JpsiPiMC" : "BcVegPy"
    , "JpsiK_Unbias" : "NONE"
    , "JpsiKMC_Unbias" : "Pythia6" # ??
    , "JpsiKst_Unbias" : "NONE"
    , "JpsiKstMC_Unbias" : "Pythia6" # ??
    , "JpsiKstData" : "NONE"
    , "JpsiKstMC6" : "Pythia6"
    , "JpsiKstMC8" : "Pythia8"
    , "JpsiKData" : "NONE"
    , "Psi2SCalData" : "NONE"
    , "InclJpsiMC6" : "Pythia6"
    , "InclJpsiMC8" : "Pythia8"
    }
    return gen_dict[mode]

def iddict(mode):
    id_dict = {
    "JpsiMuNu" : "14543010"
    , "JpsiTauNu" : "14643048"
    , "Psi2SMuNu" : "14845008"
    , "Psi2STauNu" : "14845018"
    , "Psi2SMuNu_JpsiPiPi" : "14845008"
    , "Psi2STauNu_JpsiPiPi" : "14845018"
    , "JpsiDx" : "14873607"
    , "JpsiCharmQuasi2Body" : "14873620"
    , "JpsiCharm3Body" : "14873430"
    , "B0Comb6" : "11442012"
    , "BpComb6" : "12442012"
    , "BsComb6" : "13442012"
    , "B0Comb8" : "11442012"
    , "BpComb8" : "12442012"
    , "BsComb8" : "13442012"
    , "MisID" : "DiMuon"
    , "MisID10Per" : "DiMuon"
    , "Data" : "DiMuon"
    , "Data10Per" : "DiMuon"
    , "PsiData" : "DiMuon"
    , "JpsiPi" : "DiMuon"
    , "JpsiPiMC" : "14143013"
    , "JpsiK_Unbias" : "DiMuon"
    , "JpsiKMC_Unbias" : "12143001"
    , "JpsiKst_Unbias" : "DiMuon"
    , "JpsiKstMC_Unbias" : "11144001"
    , "JpsiKstData" : "DiMuon"
    , "JpsiKstMC6" : "11144001"
    , "JpsiKstMC8" : "11144001"
    , "JpsiKData" : "DiMuon"
    , "Psi2SCalData" : "DiMuon"
    , "InclJpsiMC6" : "24142001"
    , "InclJpsiMC8" : "24142001"
    }
    return id_dict[mode]

def splitdict(mode):
    split_dict = {
    "JpsiMuNu" : 1
    , "JpsiTauNu" : 1
    , "Psi2SMuNu" : 1
    , "Psi2STauNu" : 1
    , "Chic1MuNu" : 1
    , "Psi2SMuNu_JpsiPiPi" : 1
    , "Psi2STauNu_JpsiPiPi" : 1
    , "JpsiDx" : 1
    , "JpsiDxKx" : 1
    , "JpsiDxKxRes" : 1
    , "JpsiDsstst" : 1
    , "JpsiCharm3Body" : 1
    , "JpsiCharmQuasi2Body" : 1
    , "B0Comb6" : 1
    , "BpComb6" : 1
    , "BsComb6" : 1
    , "B0Comb8" : 1
    , "BpComb8" : 1
    , "BsComb8" : 1
    , "B0CombSideband" : 1
    , "BpCombSideband" : 1
    , "BsCombSideband" : 1
    , "MisID" : 4
    , "MisID10Per" : 10
    , "Data" : 4
    , "Data10Per" : 10 # and only keep 1; hardcoded for now
    , "PsiData" : 10
    , "JpsiPi" : 1 # and only keep 1; hardcoded for now
    , "JpsiPiMC" : 1 # and only keep 1; hardcoded for now
    , "JpsiK_Unbias" : 1 # and only keep 1; hardcoded for now
    , "JpsiKMC_Unbias" : 1 # and only keep 1; hardcoded for now
    , "JpsiKst_Unbias" : 1 # and only keep 1; hardcoded for now
    , "JpsiKstMC_Unbias" : 1 # and only keep 1; hardcoded for now
    , "JpsiKstData" : 1 # and only keep 1; hardcoded for now
    , "JpsiKstMC6" : 1 # and only keep 1; hardcoded for now
    , "JpsiKstMC8" : 1 # and only keep 1; hardcoded for now
    , "JpsiKData" : 1 # and only keep 1; hardcoded for now
    , "Psi2SCalData" : 1 # and only keep 1; hardcoded for now
    , "InclJpsiMC6" : 1
    , "InclJpsiMC8" : 1
    }
    return split_dict[mode]

def keepdict(mode):
    keep_dict = {
    "JpsiMuNu" : 1
    , "JpsiTauNu" : 1
    , "Psi2SMuNu" : 1
    , "Psi2STauNu" : 1
    , "Chic1MuNu" : 1
    , "Psi2SMuNu_JpsiPiPi" : 1
    , "Psi2STauNu_JpsiPiPi" : 1
    , "JpsiDx" : 1
    , "JpsiDxKx" : 1
    , "JpsiDxKxRes" : 1
    , "JpsiDsstst" : 1
    , "JpsiCharm3Body" : 1
    , "JpsiCharmQuasi2Body" : 1
    , "B0Comb6" : 1
    , "BpComb6" : 1
    , "BsComb6" : 1
    , "B0Comb8" : 1
    , "BpComb8" : 1
    , "BsComb8" : 1
    , "B0CombSideband" : 1
    , "BpCombSideband" : 1
    , "BsCombSideband" : 1
    , "MisID" : 4
    , "MisID10Per" : 1
    , "Data" : 4
    , "Data10Per" : 1
    , "PsiData" : 1
    , "JpsiPi" : 1
    , "JpsiPiMC" : 1
    , "JpsiK_Unbias" : 1
    , "JpsiKMC_Unbias" : 1
    , "JpsiKst_Unbias" : 1
    , "JpsiKstMC_Unbias" : 1
    , "JpsiKstData" : 1
    , "JpsiKstMC6" : 1
    , "JpsiKstMC8" : 1
    , "JpsiKData" : 1
    , "Psi2SCalData" : 1
    , "InclJpsiMC6" : 1
    , "InclJpsiMC8" : 1
    }
    return keep_dict[mode]

def sandboxlist():
    import os
    homeDir = os.environ['HOME']
    baseDir = homeDir + '/LHCb/bcharm/davinci/options/'
    xmlDir = homeDir + '/LHCb/bcharm/IsolationBDT/'
    sandboxlist = [LocalFile(xmlDir+'weightsSoft.xml')]
    return sandboxlist

def sandboxlist5():
    import os
    homeDir = os.environ['HOME']
    baseDir = homeDir + '/LHCb/bcharm/davinci/options/'
    xmlDir = homeDir + '/LHCb/bcharm/IsolationBDT/'
    sandboxlist = [xmlDir+'weightsSoft.xml']
    return sandboxlist

def optsdict(mode):
    import os
    homeDir = os.environ['HOME']
    baseDir = homeDir + '/LHCb/bcharm/davinci/options/'
    opts_addpath = baseDir + "add_path.py"
    opts_JpsiMu = baseDir + "Bc_JpsiMu_MC.py"
    opts_JpsiTau = baseDir + "Bc_JpsiTau_MC.py"
    opts_Psi2SMu = baseDir + "Bc_Psi2SMu_MC.py"
    opts_Psi2STau = baseDir + "Bc_Psi2STau_MC.py"
    opts_Chic1Mu = baseDir + "Bc_Chic1Mu_MC.py"
    opts_Psi2SMu_JpsiPiPi = baseDir + "Bc_Psi2SMu_JpsiPiPi_MC.py"
    opts_Psi2STau_JpsiPiPi = baseDir + "Bc_Psi2STau_JpsiPiPi_MC.py"
    opts_JpsiDx = baseDir + "Bc_JpsiDx_MC.py"
    opts_Comb = baseDir + "Bc_BKG_MC.py"
    opts_MisID = baseDir + "Bc_MisID_Data.py"
    opts_Data = baseDir + "Bc_Data.py"
    opts_PsiData = baseDir + "Bc_Data_Psi.py"
    opts_JpsiPiData = baseDir + "Bc_JpsiPi_Data.py"
    opts_JpsiPiMC = baseDir + "Bc_JpsiPi_MC.py"
    opts_JpsiKData_Unbias = baseDir + "B_JpsiK_Unbias_Data.py"
    opts_JpsiKMC_Unbias = baseDir + "B_JpsiK_Unbias_MC.py"
    opts_JpsiKstData_Unbias = baseDir + "B_JpsiKst_Unbias_Data.py"
    opts_JpsiKstMC_Unbias = baseDir + "B_JpsiKst_Unbias_MC.py"
    opts_JpsiKstData = baseDir + "B_JpsiKst_Data.py"
    opts_JpsiKstMC = baseDir + "B_JpsiKst_MC.py"
    opts_JpsiKData = baseDir + "B_JpsiK_Data.py"
    opts_Psi2SCalData = baseDir + "Psi2S_JpsiPiPiData.py"
    opts_InclJpsiCal = baseDir + "Bc_MisID_MC.py" #opts_InclJpsiCal = baseDir + "Bc_BKG_MC.py"

    dict = {
    "JpsiMuNu" : opts_JpsiMu
    , "JpsiTauNu" : opts_JpsiTau
    , "Psi2SMuNu" : opts_Psi2SMu
    , "Psi2STauNu" : opts_Psi2STau
    , "Chic1MuNu" : opts_Chic1Mu
    , "Psi2SMuNu_JpsiPiPi" : opts_Psi2SMu_JpsiPiPi
    , "Psi2STauNu_JpsiPiPi" : opts_Psi2STau_JpsiPiPi
    , "JpsiDx" : opts_JpsiDx
    , "JpsiDxKx" : opts_JpsiDx
    , "JpsiDxKxRes" : opts_JpsiDx
    , "JpsiDsstst" : opts_JpsiDx
    , "JpsiCharm3Body" : opts_JpsiDx
    , "JpsiCharmQuasi2Body" : opts_JpsiDx
    , "B0Comb6" : opts_Comb
    , "BpComb6" : opts_Comb
    , "BsComb6" : opts_Comb
    , "B0Comb8" : opts_Comb
    , "BpComb8" : opts_Comb
    , "BsComb8" : opts_Comb
    , "B0CombSideband" : opts_Comb
    , "BpCombSideband" : opts_Comb
    , "BsCombSideband" : opts_Comb
    , "MisID" : opts_MisID
    , "MisID10Per" : opts_MisID
    , "Data" : opts_Data
    , "Data10Per" : opts_Data
    , "PsiData" : opts_PsiData
    , "JpsiPi" : opts_JpsiPiData
    , "JpsiPiMC" : opts_JpsiPiMC
    , "JpsiK_Unbias" : opts_JpsiKData_Unbias
    , "JpsiKMC_Unbias" : opts_JpsiKMC_Unbias
    , "JpsiKst_Unbias" : opts_JpsiKstData_Unbias
    , "JpsiKstMC_Unbias" : opts_JpsiKstMC_Unbias
    , "JpsiKstData" : opts_JpsiKstData
    , "JpsiKstMC6" : opts_JpsiKstMC
    , "JpsiKstMC8" : opts_JpsiKstMC
    , "JpsiKData" : opts_JpsiKData
    , "Psi2SCalData" : opts_Psi2SCalData
    , "InclJpsiMC6" : opts_InclJpsiCal
    , "InclJpsiMC8" : opts_InclJpsiCal
    }
    return [opts_addpath,dict[mode]]
    
def GetMCDataset(year,polarity,mode):
    if (not (year == "2011" or year == "2012")): # DONT ALLOW 2011 RECO 12 here!!! THAT IS JUST FOR DATA
        return "NONE"
    if (not (polarity == "Up" or polarity == "Down")):
        return "NONE"


    id = iddict(mode)
    sim = simdict(mode)
    gen = gendict(mode)
    reco = recodict(mode)

    energy = '3500' if (year == "2011") else '4000'
    nu = '2' if (year == "2011") else '2.5'
    trigger = '760037' if (year == "2011") else '9f0045'
    stripping = '20r1' if (year == "2011") else '20'
    value = '/MC/' + year + '/Beam' + energy + 'GeV-' + year + '-Mag' + polarity + '-Nu' + nu + '-' + gen
    value += '/' + sim + '/' + 'Digi13/Trig0x40' + trigger + '/' + reco + '/Stripping' + stripping + 'NoPrescalingFlagged/' + id + '/ALLSTREAMS.DST'
    return value

def GetDataDataset(year,polarity,mode):
    if (not (year == "2011" or year == "2011reco12" or year == "2012")):
        return "NONE"
    if (not (polarity == "Up" or polarity == "Down")):
        return "NONE"

    id = iddict(mode)

    type = '12' if (year == "2012") else '11'
    energy = '4000' if (year == "2012") else '3500'
    reco = '12' if (year == "2011reco12") else '14'
    stripping = '20r1' if (year == "2011") else ('20' if (year == "2012") else '17')
    stream = "DIMUON.DST" if (id == "DiMuon") else ("CHARMCOMPLETEEVENT.DST" if (id == "Charm") else "NONE")

    value = '/LHCb/Collision' + type + '/Beam' + energy + 'GeV-VeloClosed-Mag' + polarity
    value += '/Real Data/Reco' + reco + '/Stripping' + stripping + '/90000000/' + stream
    return value

def GetDataset(year,polarity,mode):

    if (typedict(mode) == "MC"):
        return GetMCDataset(year,polarity,mode)
    elif (typedict(mode) == "Data"):
        return GetDataDataset(year,polarity,mode)
    else:
        return 0

def OptFilesPerJob(numFiles,maxSubjobs,grouping):
    subjobs = maxSubjobs*(1.0 - exp(-1.0*numFiles/(maxSubjobs*grouping)))
    filesper  = numFiles / subjobs
    return int(filesper) + 1                 

def MakeJob(jobname,optsfilelist,data,v5=False):
    N = len(data.files)
    j = Job()
    j.name = jobname
    if (v5):
        j.application = DaVinci(version = 'v34r0')
    else:
        j.application = DaVinci(version = 'v36r1p3')
    j.application.optsfile = optsfilelist
    j.application.platform = 'x86_64-slc6-gcc48-opt'
    if (v5):
        j.inputsandbox = sandboxlist5()
    else:
        j.inputfiles = sandboxlist()
    j.inputdata = data
    j.backend = Dirac()
    j.splitter = SplitByFiles()
    #f = OptFilesPerJob(N,200,10)
    j.splitter.filesPerJob = 10
    return j


# SIMULATION CONDITIONS

def createJobs(v5=False):
    MODES = ["JpsiKst_Unbias"]
    YEARS = ["2011","2012"]
    POLARITIES = ["Up","Down"]
    NUMEVENTS = "-1"
    
    for mode in MODES:
        
        opts = optsdict(mode)
        sim = simdict(mode)
        split = splitdict(mode)
        keep = keepdict(mode)
        
        for year in YEARS:
            for polarity in POLARITIES:
                data = []
                if (mode == "Chic1MuNu"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(12)
                        elif (polarity == "Down"): 
                            data = box(11)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(27)
                        elif (polarity == "Down"):
                            data = box(28)
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "Chic2MuNu"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(38)
                        elif (polarity == "Down"): 
                            data = box(37)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(35)
                        elif (polarity == "Down"):
                            data = box(36)
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "JpsiDxKx"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(94)
                        elif (polarity == "Down"): 
                            data = box(95)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(92)
                        elif (polarity == "Down"):
                            data = box(93)
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "JpsiDxKxRes"):
                    if (year == "2011"):
                        if (polarity == "Up"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(216)])
                        elif (polarity == "Down"): 
                            data = LHCbDataset([LogicalFile(name=f) for f in box(217)])
                        else:
                            data = []
                    elif (year == "2012"):
                        if (polarity == "Up"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(218)])
                        elif (polarity == "Down"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(219)])
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "JpsiDsstst"):
                    if (year == "2011"):
                        if (polarity == "Up"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(220)])
                        elif (polarity == "Down"): 
                            data = LHCbDataset([LogicalFile(name=f) for f in box(221)])
                        else:
                            data = []
                    elif (year == "2012"):
                        if (polarity == "Up"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(222)])
                        elif (polarity == "Down"):
                            data = LHCbDataset([LogicalFile(name=f) for f in box(223)])
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "B0CombSideband"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(103)
                        elif (polarity == "Down"): 
                            data = box(106)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(97)
                        elif (polarity == "Down"):
                            data = box(100)
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "BpCombSideband"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(104)
                        elif (polarity == "Down"): 
                            data = box(107)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(98)
                        elif (polarity == "Down"):
                            data = box(101)
                        else:
                            data = []
                    else:
                        data = []
                elif (mode == "BsCombSideband"):
                    if (year == "2012"):
                        if (polarity == "Up"):
                            data = box(105)
                        elif (polarity == "Down"): 
                            data = box(108)
                        else:
                            data = []
                    elif (year == "2011"):
                        if (polarity == "Up"):
                            data = box(99)
                        elif (polarity == "Down"):
                            data = box(102)
                        else:
                            data = []
                    else:
                        data = []
                else:
                    dataname = GetDataset(year, polarity, mode)
                    print(dataname)
                    continue
                    query = BKQuery(dataname)
                    if (v5):
                        data = LHCbDataset([])
                    else:
                        data = query.getDataset()

                N = len(data.files)

                # SPLIT MISID SAMPLES INTO SMALLER SUBJOBS
                #for i in range(keep):
                for i in range(0):
                    subdata = LHCbDataset()
                    k = i
                    while (k < N):
                        subdata.files.append(data.files[k])
                        k += split

                    name = mode + '_' + year + '_' + polarity
                    if (split > 1):
                        name += '_' + str(i)
                    j = MakeJob(name,opts,subdata,v5)
                    extraOpts = ""
                    if (sim == "DATA"):
                        extraOpts += "\nDaVinci().DataType = "
                        extraOpts += "'2011'" if (year == "2011") else "'2012'"
                        extraOpts += "\nDaVinci().EvtMax = " + NUMEVENTS + "\n"
                    elif (sim == "Sim08a" or sim == "Sim08b" or sim == "Sim08c" or sim == "Sim08d" or sim == "Sim08e" or sim == "Sim08h"):
                        sim08d_prefix = "\nDaVinci().DDDBtag = 'dddb-20130929'"
                        sim08d_prefix += "\nDaVinci().CondDBtag = 'sim-20130522-vc-"
                        sim08e_prefix = "\nDaVinci().DDDBtag = 'dddb-20130929-1'"
                        sim08e_prefix += "\nDaVinci().CondDBtag = 'sim-20130522-1-vc-"
                        sim08e_prefix = "\nDaVinci().DDDBtag = 'dddb-20130929-1'"
                        sim08e_prefix += "\nDaVinci().CondDBtag = 'sim-20130522-1-vc-"
                        extraOpts = sim08d_prefix if (sim == "Sim08d") else sim08e_prefix
                        extraOpts += "md100'" if (polarity == "Down") else "mu100'"
                        extraOpts += "\nDaVinci().DataType = "
                        extraOpts += "'2011'" if (year == "2011") else "'2012'"
                        extraOpts += "\nDaVinci().EvtMax = " + NUMEVENTS + "\n"
                    else:
                        extraOpts = ""
                    j.application.extraopts = extraOpts
                    j.outputfiles = [MassStorageFile(namePattern="*.root",locations=["CERN-USER"])]
                    j.do_auto_resubmit = False
