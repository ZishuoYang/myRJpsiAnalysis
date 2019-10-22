from Configurables import ChargedProtoANNPIDConf
PIDUpdater = GaudiSequencer("ANNGPIDSeq")
annconf = ChargedProtoANNPIDConf()
annconf.DataType = "2011"
annconf.NetworkVersions["2011"] = "MC12TuneV2"
annconf.RecoSequencer = PIDUpdater
