#-- GAUDI jobOptions generated on Wed Aug 21 21:57:58 2019
#-- Contains event types : 
#--   14873607 - 13 files - 171380 events - 34.17 GBytes

#--  Extra information about the data processing phases:

#--  Processing Pass: '/Sim08e/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged' 

#--  StepId : 124629 
#--  StepName : Merge14 for Sim08 
#--  ApplicationName : LHCb 
#--  ApplicationVersion : v35r4 
#--  OptionFiles : $APPCONFIGOPTS/Merging/CopyDST.py 
#--  DDDB : None 
#--  CONDDB : None 
#--  ExtraPackages : AppConfig.v3r164 
#--  Visible : N 

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles([
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000013_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000006_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000012_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000002_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000011_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000007_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000005_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000010_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000008_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034423/0000/00034423_00000009_1.allstreams.dst',
], clear=True)

