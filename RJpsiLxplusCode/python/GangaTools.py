from GangaService.Lib.ServiceAPI.ServiceAPI import GangaService
#gs = GangaService()

import os, errno

def checkOutputData(j):
    import random as r
    outputs = jobs(j).backend.getOutputDataLFNs()
    L = len(outputs)
    if (L == 0):
        print "No output data"
    else:
        r1 = r.randint(0,L)
        r2 = r.randint(0,L)
        r3 = r.randint(0,L)
        print(outputs[r1].getReplicas())
        print(outputs[r2].getReplicas())
        print(outputs[r3].getReplicas())
        
def resubmit_subjobs(j):
    for s in j.subjobs:
        if (s.status == "failed"):
            try:
                list = s.backend.settings['BannedSites']
                if list == [None]:
                    list = []
            except KeyError:
                list = []
            actualCE = s.backend.actualCE
            s.backend.settings['BannedSites'] = []
            if (actualCE != None):
                s.backend.settings['BannedSites'] = list + [s.backend.actualCE]
            if s.backend.settings['BannedSites'] == []:
                del s.backend.settings['BannedSites']
            queues.add(s.resubmit)
        else:
            continue
        
def reheatLeftovers(j):
    files = []
    for s in j.subjobs:
        if (s.status != "completed"):
            files += s.inputdata.files
    newj = j.copy()
    newj.unprepare()
    data = LHCbDataset()
    data.files = files
    newj.inputdata = data
    
def reset_subjobs(j):
    for s in j.subjobs:
        if s.status == "completing":
            queues.add(s.backend.reset)
        

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc: # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else: raise
        

def lumi(data):
    num = len(data)

    L = 0.0
    for i in range(num):
        Li = data[i].bkMetadata()['Luminosity']
        L += Li

        Lproj = L * num / (i + 1.0) / 1e6
        print "Proj. luminosity is ", Lproj, " inv pb"

    print L
    return L

def joblumi(j):
    data = j.inputdata
    L = lumi(data)
    return L

def job_info(j):

    s = r = f = g = c = o = 0
    for i in j.subjobs:
        if (i.status == "submitted"):
            s += 1
        elif (i.status == "running"):
            r += 1
        elif (i.status == "failed"):
            f += 1
        elif (i.status == "completing"):
            g += 1
        elif (i.status == "completed"):
            c += 1
        else:
            o += 1
    print "Submitted: " + str(s)
    print "Running: " + str(r)
    print "Failed: " + str(f)
    print "Completing: " + str(g)
    print "Completed: " + str(c)
    print "Other: " + str(o)
        

def started_subjobs(j):
    for i in range(len(j.subjobs)):
        s = j.subjobs[i].status
        if (s != 'submitted'):
            print str(i) + " -> " + s

def running_subjobs(j):
    for i in range(len(j.subjobs)):
        s = j.subjobs[i].status
        if (s == 'running'):
            print str(i) + " -> " + s

def notdone_subjobs(j):
    for i in range(len(j.subjobs)):
        s = j.subjobs[i].status
        if (s != 'completed'):
            print str(i) + " -> " + s

def uploadOutputROOTSToDirac(j,filestr):
    from ROOT import TFile
    lfnprefix = "/lhcb/user/j/jwimberl/"
    for i in j.subjobs:
        if (i.status == "completed"):
            pfncame = i.outputdir + filestr
            lfnname = lfnprefix + pfnname.split('LocalXML/')[1]
            guid = TFile(pfnname).GetUUID().AsString()
            pfn = PhysicalFile(pfnname)
            pfn.upload(lfnname,'CERN-USER',guid)

def downloadOutputROOTS(j,outputDir,skipFirstNsubs = 0):
    numSkipped = 0
    data2download = j.backend.getOutputDataLFNs()
    for f in data2download:
        numSkipped += 1
        if (numSkipped <= 2*skipFirstNsubs):
            continue
        name = f
        dir = outputDir + "/" + name.split('/')[7]
        print(dir)
        try:
            os.makedirs(dir)
        except OSError:
            print "Folder ", dir, " exists!"
        df = DiracFile(lfn=name)
        df.localDir = dir
        queues.add(df.get)


def deleteAllData(j):
    for sj in j.subjobs:
        for f in sj.outputfiles.get(DiracFile):
            if f.lfn:
                print("Deleting data: " + f.lfn)
                queues.add(f.remove)


def composeMaps(mapb, mapa):
    newmap = {}
    akeys = mapa.keys()
    bkeys = mapb.keys()
    for key in mapa.keys():
        if (mapa[key] in bkeys):
            newmap[key] = mapb[mapa[key]]
        else:
            print "BAD VALUE: ", key, " => ", mapa[key], " NOT A KEY IN SECOND MAP"
    return newmap
