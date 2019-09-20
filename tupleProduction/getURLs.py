import sys
jobNumber = int(sys.argv[1])
fileName = str(sys.argv[2])

URLs = jobs(jobNumber).backend.getOutputDataAccessURLs()
with open(fileName, 'w') as f:
    f.write('\n'.join(URLs))

#length = len(jobs(jobNumber).subjobs)
#fileName = 'job'+str(jobNumber)+'OutputLFNs.txt'
#file = open(fileName, 'w')
#if length != 0:
#    for i in range(0,length):
#        output = jobs(jobNumber).subjobs(i).backend.getOutputDataLFNs()
#        if ( output.hasLFNs() == True ):
#            s = str(jobs(jobNumber).subjobs(i).backend.getOutputDataLFNs().getReplicas().keys())
#            print s
#            file.write(s)
#            file.write('\n')
#if length == 0:
#    file.write( str(jobs(jobNumber).backend.getOutputDataLFNs().getReplicas().keys() ) )
#    file.write('\n')

