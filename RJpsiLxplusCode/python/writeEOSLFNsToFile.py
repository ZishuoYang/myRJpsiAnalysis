def writeEOSLFNsToFile(name):
    data = box(name)
    f = open(name + ".lfns",'w')
    for i in data:
        lfn = i.name
        if lfn.endswith("histos.root"):
            continue
        else:
            f.write("root://eoslhcb.cern.ch//eos/lhcb/grid/user" + lfn + "\n")
    f.close()

        
    
