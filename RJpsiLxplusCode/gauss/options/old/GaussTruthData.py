from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['PFN:/afs/cern.ch/user/j/jwimberl/bcharm/gauss/MCTruth.sim'], clear=True)
FileCatalog().Catalogs += [ 'xmlcatalog_file:dimuon_small_pdfns_new.xml' ]
