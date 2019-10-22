#-- GAUDI jobOptions generated on Wed Jul 16 15:55:52 2014
#-- Contains event types : 
#--   12143001 - 5 files - 59200 events - 17.60 GBytes


#--  Extra information about the data processing phases:


#--  Processing Pass Step-17394 

#--  StepId : 17394 
#--  StepName : Reco13a for MC - MagUp - MayJune2012 
#--  ApplicationName : Brunel 
#--  ApplicationVersion : v42r3p2 
#--  OptionFiles : $APPCONFIGOPTS/Brunel/DataType-2012.py;$APPCONFIGOPTS/Brunel/MC-WithTruth.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : head-20120413 
#--  CONDDB : sim-20120727-vc-mu100 
#--  ExtraPackages : AppConfig.v3r140 
#--  Visible : Y 


#--  Processing Pass Step-18089 

#--  StepId : 18089 
#--  StepName : Sim06a with Nu=2.5 - MU - MayJune 2012 
#--  ApplicationName : Gauss 
#--  ApplicationVersion : v42r1 
#--  OptionFiles : $APPCONFIGOPTS/Gauss/Beam4000GeV-mu100-MayJun2012-nu2.5.py;$DECFILESROOT/options/@{eventType}.py;$LBPYTHIAROOT/options/Pythia.py;$APPCONFIGOPTS/Gauss/G4PL_LHEP_EmNoCuts.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : head-20120413 
#--  CONDDB : sim-20120727-vc-mu100 
#--  ExtraPackages : AppConfig.v3r147;DecFiles.v25r14 
#--  Visible : Y 


#--  Processing Pass Step-17464 

#--  StepId : 17464 
#--  StepName : Stripping19a-NoPrescalingFlagged for MC MagUp 
#--  ApplicationName : DaVinci 
#--  ApplicationVersion : v30r4p1 
#--  OptionFiles : $APPCONFIGOPTS/DaVinci/DV-Stripping19a-Stripping-MC-NoPrescaling.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : head-20120413 
#--  CONDDB : sim-20120727-vc-mu100 
#--  ExtraPackages : AppConfig.v3r140 
#--  Visible : Y 


#--  Processing Pass Step-17922 

#--  StepId : 17922 
#--  StepName : Digi12 w/o spillover - MU - L0TCK 0x003D 
#--  ApplicationName : Boole 
#--  ApplicationVersion : v24r0 
#--  OptionFiles : $APPCONFIGOPTS/Boole/Default.py;$APPCONFIGOPTS/Boole/DataType-2012.py;$APPCONFIGOPTS/L0/L0TCK-0x003D.py;$APPCONFIGOPTS/Persistency/Compression-ZLIB-1.py 
#--  DDDB : head-20120413 
#--  CONDDB : sim-20120727-vc-mu100 
#--  ExtraPackages : AppConfig.v3r140 
#--  Visible : N 


#--  Processing Pass Step-18085 

#--  StepId : 18085 
#--  StepName : Trigger - TCK 0x4097003d Flagged - MU - MayJune 2012 
#--  ApplicationName : Moore 
#--  ApplicationVersion : v14r2p1 
#--  OptionFiles : $APPCONFIGOPTS/Moore/MooreSimProduction.py;$APPCONFIGOPTS/Conditions/TCK-0x4097003d.py;$APPCONFIGOPTS/Moore/DataType-2012.py;$APPCONFIGOPTS/L0/L0TCK-0x003D.py 
#--  DDDB : head-20120413 
#--  CONDDB : sim-20120727-vc-mu100 
#--  ExtraPackages : AppConfig.v3r147 
#--  Visible : Y 

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00020066/0000/00020066_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00020066/0000/00020066_00000002_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00020066/0000/00020066_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00020066/0000/00020066_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00020066/0000/00020066_00000005_1.allstreams.dst'
], clear=True)
FileCatalog().Catalogs += [ 'xmlcatalog_file:JpsiKTestData.xml' ]
