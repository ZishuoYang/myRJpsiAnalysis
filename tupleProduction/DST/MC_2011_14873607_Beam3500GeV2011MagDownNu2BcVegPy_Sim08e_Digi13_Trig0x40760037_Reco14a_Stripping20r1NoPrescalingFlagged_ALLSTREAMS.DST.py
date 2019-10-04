#-- GAUDI jobOptions generated on Fri Sep 20 21:23:30 2019
#-- Contains event types : 
#--   14873607 - 10 files - 142717 events - 24.98 GBytes

#--  Extra information about the data processing phases:

#--  Processing Pass: '/Sim08e/Digi13/Trig0x40760037/Reco14a/Stripping20r1NoPrescalingFlagged' 

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
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000007_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000010_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000005_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000006_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000002_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000009_1.allstreams.dst',
'LFN:/lhcb/MC/2011/ALLSTREAMS.DST/00034417/0000/00034417_00000008_1.allstreams.dst',
], clear=True)

