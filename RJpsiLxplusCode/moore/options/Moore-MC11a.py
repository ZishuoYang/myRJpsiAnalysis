##############################################################################
# File for running Moore MC11a simulation -- use v12r8g1
##############################################################################

from Configurables import Moore
Moore().DataType = '2012'
Moore().DDDBtag   = "Sim08-20130503-1"
Moore().CondDBtag = "Sim08-20130503-1-vc-md100"
#Moore().DataType = '2011'
#Moore().CondDBtag = "sim-20111111-vc-mu100"
#Moore().DDDBtag   = "MC11-20111102"

##############################################################################
# From Moore/MooreSimProductionWithL0Emulation.py + TCK-0x40760037.py + 
##############################################################################

Moore().UseTCK = True # provide an invalid TCK here so one is forced to append eg. Conditions/TCK-0x00051810.py
Moore().InitialTCK = '0x409f0045'
Moore().L0 = True
Moore().ReplaceL0BanksWithEmulated = True
#Moore().RunL0Emulator = True
Moore().UseDBSnapshot = False
Moore().EnableRunChangeHandler = False

Moore().CheckOdin = False
Moore().WriterRequires = []

Moore().Simulation = True

from Configurables import L0MuonAlg
L0MuonAlg( "L0Muon" ).L0DUConfigProviderType = "L0DuConfigProvider"

Moore().outputFile = "Moore.digi"

from Gaudi.Configuration import importOptions
importOptions("$APPCONFIGOPTS/L0/L0TCK-0x0045.py")
