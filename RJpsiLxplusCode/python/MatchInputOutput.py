## SIDEBAND BRUNEL => OFFLINE
#outputRange = range(1118,1130)
#inputRange = range(1130,1139) + [1140,1141]

# SIDEBAND OFFLINE => ONLINE
outputRange = range(1056,1080) + range(1118,1130) #range(1131,1139) + [1140,1141]
inputRange = range(1321,1329) + range(1330,1353)

outputNames = {}
inputNames = {}

outputFiles = {}
inputFiles = {}

map = {}
name_map = {}

for i in outputRange:
    outputNames[i] = jobs(i).name
    outputFiles[i] = jobs(i).backend.getOutputDataLFNs()[0].name
    print "ONLINE: ", i, " => ", outputNames[i]

for i in inputRange:
    inputNames[i] = jobs(i).name
    #inputFiles[i] = jobs(i).inputdata[0].name
    inputFiles[i] = jobs(i).splitter.values[0][0][4:]
    print "OFFLINE: ", i, " => ", inputNames[i]

for i in outputRange:
    match = -1
    for j in inputRange:
        if (outputFiles[i] == inputFiles[j]):
            match = j
            break
    if (match != -1):
        inputRange.remove(match)
        map[i] = match
        name_map[outputNames[i]] = inputNames[match]

import collections

omap = collections.OrderedDict(sorted(map.items()))
name_omap = collections.OrderedDict(sorted(name_map.items()))

print omap
print name_omap
