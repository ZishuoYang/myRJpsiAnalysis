## Ganga script
## for merging (multiple) root files from grid jobs' URLs
## Zishuo Yang, 2019-09-25

import ROOT
import sys

targetDir = "/eos/user/z/ziyang/RJpsi/tuples/"
targetFileName = "2012_Data_MD_subset.root"
sourceTreeName = "JpsiRecTuple/DecayTree"

fname = str(sys.argv[1])
with open(fname) as f:
    content = f.readlines()
print("length of sys.argv = "+str(len(sys.argv)))
if len(sys.argv) == 3: # For combining MagUp and MagDown
    fname2 = str(sys.argv[2])
    with open(fname2) as f2:
        content2 = f2.readlines()
        print("content2: ", len(content2))
    content = content + content2
    print("content: ", len(content))

# Divide up the input URL files 
numInputFiles = 200
numLast = len(content)%numInputFiles
if numLast == 0:
    numOutputFiles = int(len(content)/numInputFiles)
else:
    numOutputFiles = 1 + int(len(content)/numInputFiles)
print("-> To merge "+str(len(content))+" input files into "+str(numOutputFiles)+" output files...")
listFileNames = []

if numOutputFiles == 1:
    fullName = targetDir+targetFileName+".root"
    listFileNames.append(fullName)
    print("-> Start merging "+listFileNames[0])
    chain = ROOT.TChain(sourceTreeName)
    for url in content:
        url = url.rstrip('\n')
        print("adding file: "+url)
        chain.AddFile(url)
    chain.Merge(listFileNames[0])
    print("-> Done merging "+listFileNames[0])
    #chain.Draw("Bc_M") 
    #raw_input("press ENTER to close")
    #input("Press ENTER to close")    
 
elif numOutputFiles > 1:
    for i in range(0,numOutputFiles):
        fullName = targetDir+targetFileName+str(i)+".root"
        listFileNames.append(fullName)
    
    for i in range(0,numOutputFiles):
        print("-> Start merging "+listFileNames[i])
        startIndex = i*numInputFiles
        endIndex = (i+1)*numInputFiles
        if i==(numOutputFiles-1) and numLast!=0:
            endIndex = i*numInputFiles + numLast
        chain = ROOT.TChain("BuTuple/DecayTree")
        for url in content[startIndex:endIndex]: #first 20 files
            url = url.rstrip('\n')
            print("adding file: "+url)
            chain.AddFile(url)
        chain.Merge(listFileNames[i])
        print("-> Done merging "+listFileNames[i])
        #chain.Draw("Bu_M") 
        #raw_input("press ENTER to close")
else:
    print("Error: number of output files = "+str(numOutputFiles))
