## For merging into multiple root files:
import ROOT
import sys

targetDir = "/afs/cern.ch/work/z/ziyang/Data2016_stripped"
targetFileName = "2016_MU_ntuple_"

fname = str(sys.argv[1])
with open(fname) as f:
    content = f.readlines()
# Divide up the input URL files 
numInputFiles = 16
numLast = len(content)%numInputFiles
if numLast == 0:
    numOutputFiles = int(len(content)/numInputFiles)
else:
    numOutputFiles = 1 + int(len(content)/numInputFiles)
print("-> To merge into "+str(numOutputFiles)+" output files...")
listFileNames = []
for i in range(0,numOutputFiles):
    fullName = targetDir+targetFileName+str(i)+".root"
    listFileNames.append(fullName)

for i in range(0,numOutputFiles):
#    if i == (numOutputFiles-1):#for the last output file case
#        if numLast == 0:
#            continue
#        else:
#            print("Start merging "+listFileNames[i])
#            startIndex = i*numInputFiles
#            endIndex = i*numInputFiles + numLast
#            chain = ROOT.TChain("BuTuple/DecayTree")
#            for url in content[startIndex:endIndex]: #first 20 files
#                url = url.rstrip('\n')
#                print("adding file: "+url)
#                chain.AddFile(url)
#            chain.Merge(listFileNames[i])
#            print("Done merging "+listFileNames[i])
#            break
            
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

