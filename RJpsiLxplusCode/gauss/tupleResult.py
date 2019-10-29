#################################
# File: tupleResult.py
# Author: Aurelien Martens
#################################
# used to define the ROOT output file name

# Change the descriptor and header to match the decay mode you generated
DecayDescriptor = '[B0 -> (^D+ -> ^K- ^pi+ ^pi+ {,gamma} {,gamma}) (^D- -> ^K+ ^pi- ^pi- {,gamma} {,gamma}) {,gamma} {,gamma}]CC'
DecayHeader = 'B0'

# Name of the .xgen file produced at the previous step by Gauss
from Configurables import EventSelector
EventSelector().Input = [  "DATAFILE='Gauss-11296013-100ev-20130710.xgen'  TYP='POOL_ROOTTREE' Opt='READ'" ]

#################################
from DaVinci.Configuration import *
from Gaudi.Configuration import *

from Configurables import DaVinci, PrintMCTree
from Configurables import MCDecayTreeTuple, MCTupleToolKinematic, MCTupleToolHierarchy, LoKi__Hybrid__MCTupleTool

mctuple = MCDecayTreeTuple( 'MCDecayTreeTuple' )
mctuple.Decay = DecayDescriptor
mctuple.ToolList = [ "MCTupleToolHierarchy",
                                                     "MCTupleToolKinematic",
                                                     "LoKi::Hybrid::MCTupleTool/LoKi_Photos" ]

mctuple.addTool(MCTupleToolKinematic())
mctuple.MCTupleToolKinematic.Verbose=True

LoKi_Photos = LoKi__Hybrid__MCTupleTool("LoKi_Photos")
LoKi_Photos.Variables = { "nPhotos"  : "MCNINTREE ( ('gamma'==MCABSID) )" }
mctuple.addTool(LoKi_Photos)

pMC = PrintMCTree()
pMC.ParticleNames = [ DecayHeader ]

DaVinci().TupleFile  = 'tupleProduction.root'
DaVinci().EvtMax     = -1
DaVinci().Simulation = True
DaVinci().Lumi       = False
DaVinci().InputType  = "DST"
DaVinci().DataType   = "2012"
DaVinci().CondDBtag  = "MC2011-20120727-vc-md100"
DaVinci().DDDBtag    = "MC2011-20120727"
DaVinci().UserAlgorithms = [ pMC, mctuple ]