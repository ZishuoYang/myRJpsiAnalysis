def IsItMoved(i):
    hasThemAll = True
    for s in box(i):
        dict = s.getReplicas()
        isHere = 'CERN-USER' in dict
        if (isHere):
            continue
        else:
            hasThemAll = False
            break
    return hasThemAll

def moveToEOS(list):
    for i in list:
        print "Replicating dataset %d" % i
        data = box(i)
        for file in data:
            file.replicate('CERN-USER')

