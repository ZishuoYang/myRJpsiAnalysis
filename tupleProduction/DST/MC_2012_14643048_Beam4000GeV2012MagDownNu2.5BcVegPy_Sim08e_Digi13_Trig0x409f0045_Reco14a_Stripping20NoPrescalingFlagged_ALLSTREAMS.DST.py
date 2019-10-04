#-- GAUDI jobOptions generated on Tue Aug 20 20:56:52 2019
#-- Contains event types : 
#--   14643048 - 17 files - 286590 events - 55.71 GBytes

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
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000015_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000018_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000012_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000010_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000006_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000011_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000008_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000014_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000009_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000013_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000007_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000005_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000016_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00034395/0000/00034395_00000017_1.allstreams.dst',
], clear=True)

