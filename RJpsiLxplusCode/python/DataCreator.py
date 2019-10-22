CondStrings = ['20120831','20121003','20121108','20121208']
CondFirstRuns = {CondStrings[0] : 111183,
                 CondStrings[1] : 126824,
                 CondStrings[2] : 130316,
                 CondStrings[3] : 131973}
CondLastRuns = {CondStrings[0] : 126823,
                CondStrings[1] : 130315,
                CondStrings[2] : 131972,
                CondStrings[3] : 131973}

Streams = ['DIMUON','CHARMCOMPLETEEVENT','EW','CALIBRATION']

Recos = [14]
Strippings = [20]

# A stream path will look like
# "<startrun>-<endrun>/Real Data/Reco14/Stripping20/90000000/STREAM.DST"

for cond in CondStrings:
    for stream in Streams:
        for reco in Recos:
            for stripping in Strippings:
                p = str(CondFirstRuns[cond]) + "-" + str(CondLastRuns[cond]) + "/Real Data/Reco" + str(reco) + "/Stripping" + str(stripping) + "/90000000/" + stream + ".DST"
                name = "~/data/" + stream + "_" + str(reco) + "_" + str(stripping) + "_" + cond + ".py"
                bkq = BKQuery(
                    dqflag = "OK",
                    path = p,
                    type = "Run")
                data = bkq.getDataset()
                export(data,name)

                
