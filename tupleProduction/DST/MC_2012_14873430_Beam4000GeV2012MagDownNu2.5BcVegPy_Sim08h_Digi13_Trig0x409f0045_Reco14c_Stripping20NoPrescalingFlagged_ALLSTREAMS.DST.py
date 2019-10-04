#-- GAUDI jobOptions generated on Wed Aug 28 19:14:41 2019
#-- Contains event types : 
#--   14873430 - 9 files - 212730 events - 56.20 GBytes

#--  Extra information about the data processing phases:

#--  Processing Pass: '/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20NoPrescalingFlagged' 

#--  StepId : 125836 
#--  StepName : Stripping20-NoPrescalingFlagged for Sim08 - Implicit merging. 
#--  ApplicationName : DaVinci 
#--  ApplicationVersion : v32r2p1 
#--  OptionFiles : $APPCONFIGOPTS/DaVinci/DV-Stripping20-Stripping-MC-NoPrescaling.py;$APPCONFIGOPTS/DaVinci/DataType-2012.py;$APPCONFIGOPTS/DaVinci/InputType-DST.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : dddb-20130929-1 
#--  CONDDB : sim-20130522-1-vc-md100 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : Y 

#--  Processing Pass: '/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20NoPrescalingFlagged' 

#--  StepId : 127969 
#--  StepName : Reco14c for MC - 2012 
#--  ApplicationName : Brunel 
#--  ApplicationVersion : v43r2p11 
#--  OptionFiles : $APPCONFIGOPTS/Brunel/DataType-2012.py;$APPCONFIGOPTS/Brunel/MC-WithTruth.py;$APPCONFIGOPTS/Persistency/DST-multipleTCK-2012.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : dddb-20130929-1 
#--  CONDDB : sim-20130522-1-vc-md100 
#--  ExtraPackages : AppConfig.v3r218 
#--  Visible : Y 

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles([
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000003_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000008_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000009_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000006_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000001_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000004_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000005_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000007_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00049450/0000/00049450_00000002_2.AllStreams.dst',
], clear=True)
