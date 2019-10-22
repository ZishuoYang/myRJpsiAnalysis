#JOBSS = [[986,987,990,991],range(1149,1153),range(994,998),range(1153,1157),range(1157,1161),range(1161,1165),range(1165,1169),range(1056,1060),range(1060,1064),range(1064,1068),range(1068,1072),range(1072,1076),range(1076,1080)]
#MODES = ["JpsiMuNu","JpsiTauNu","Psi2SMuNu","Psi2STauNu","Chic1MuNu","Chic2MuNu","JpsiDx","B0Comb6","B0Comb8","BpComb6","BpComb8","BsComb6","BsComb8"]

#JOBSS = [[905,906,907,1174],range(908,912),range(963,967),range(967,971),range(1002,1006),range(1006,1010),range(1010,1014),range(1014,1018)]
#MODES = ["Data","Data","Data","Data","MisID","MisID","MisID","MisID"]
#NAMES= ["Data_2011_Up_MICRO","Data_2011_Down_MICRO","Data_2012_Up_MICRO","Data_2012_Down_MICRO","MisID_2011_Up_MICRO","MisID_2011_Down_MICRO","MisID_2012_Up_MICRO","MisID_2012_Down_MICRO"]

JOBSS = [[i] for i in range(1713,1717)] + [[i] for i in range(1729,1740)] + [[1728]]
MODES = ["JpsiDx","JpsiDx","JpsiDx","JpsiDx","B0Comb8","BpComb8","BsComb8","B0Comb8","BpComb8","BsComb8","B0Comb8","BpComb8","BsComb8","B0Comb8","BpComb8","BsComb8"]
NAMES = ["BcJpsiDxKx_2011_Up","BcJpsiDxKx_2011_Down","BcJpsiDxKx_2012_Up","BcJpsiDxKx_2012_Down","B0CombSideband_2011_Up","BpCombSideband_2011_Up","BsCombSideband_2011_Up","B0CombSideband_2011_Down","BpCombSideband_2011_Down","BsCombSideband_2011_Down","B0CombSideband_2012_Up","BpCombSideband_2012_Up","BsCombSideband_2012_Up","B0CombSideband_2012_Down","BpCombSideband_2012_Down","BsCombSideband_2012_Down"]

import sys
import os
from math import exp

execfile("submitOfflineJob.py")

for i in range(len(JOBSS)):
    JOBS = JOBSS[i]
    mode = MODES[i]
    jname = NAMES[i]
    print "----------"
    print mode
    print "----------"
    
    for job in JOBS:
        j = jobs(job)
        dataset = j.backend.getOutputDataLFNs()
        submitOfflineJob(jname,mode,dataset)

            
