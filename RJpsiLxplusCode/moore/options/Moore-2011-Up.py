from Configurables import Moore
Moore().DDDBtag   = "Sim08-20130503-1"
Moore().CondDBtag = "Sim08-20130503-1-vc-mu100"

from Gaudi.Configuration import importOptions
importOptions("$APPCONFIGOPTS/Moore/MooreSimProductionWithL0Emulation.py")
importOptions("$APPCONFIGOPTS/Conditions/TCK-0x40760037.py")
importOptions("$APPCONFIGOPTS/Moore/DataType-2011.py")
importOptions("$APPCONFIGOPTS/L0/L0TCK-0x0037.py")

Moore().outputFile = "Moore.digi"
