########################################################################
# Y -> Jpsi Tau, Tau -> Mu (B_c, missing neutrinos)
#
# @author Jack Wimberley
# @date 2012-01-10
########################################################################

from Gaudi.Configuration import *
from Configurables import DaVinci
from GaudiKernel.SystemOfUnits import *

#OPTIONS
simulation = True; # Data or MC

MessageSvc().OutputLevel = INFO
DaVinci().EvtMax = -1
DaVinci().PrintFreq = 100
DaVinci().HistogramFile = "Bc2JpsiTau_GaussTruth_histos.root"
DaVinci().TupleFile = "Bc2JpsiTau_GaussTruth.root"
DaVinci().Simulation = simulation

DaVinci().DataType = "2011"
from Configurables import CondDB
CondDB().UseLatestTags = ["2011"]

# PRINT MC DECAY TREE
from Configurables import PrintMCTree, PrintMCDecayTreeTool
mctree = PrintMCTree("PrintTrueBc")
mctree.addTool(PrintMCDecayTreeTool, name = "PrintMC")
mctree.PrintMC.Information = "Name"
mctree.ParticleNames = [ "B_c+", "B_c-", "B+", "B-" ]
mctree.Depth = 2
#DaVinci().MoniSequence += [ mctree ]

# TAU MC TRUTH TUPLE
from Configurables import DecayTreeTuple, MCDecayTreeTuple
from DecayTreeTuple.Configuration import *
#gammas = "{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}{,gamma}"
gammas = "{,gamma}{,gamma}"
taudecay = "[B_c+ -> (^J/psi(1S) => ^mu+ ^mu-" + gammas + ") (^tau+ => ^mu+ ^nu_mu ^nu_tau~ " + gammas + ") ^nu_tau " + gammas + "]cc"
MCTauTuple = MCDecayTreeTuple("MCBc2JpsiTauTuple")
MCTauTuple.TupleName = "MCTauDecayTree"
MCTauTuple.Decay = taudecay
MCTauTuple.addBranches({
    "Bc" : "[B_c+]cc : [B_c+ -> ?]cc"
    , "Jpsi" : "[B_c+ -> (^J/psi(1S) => mu+ mu- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "MuP" : "[B_c+ -> (J/psi(1S) => ^mu+ mu- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "MuM" : "[B_c+ -> (J/psi(1S) => mu+ ^mu- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "Tau" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") (^tau+ => mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "BachMu" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") (tau+ => ^mu+ nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "NuMu" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") (tau+ => mu+ ^nu_mu nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "NuTauBar" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") (tau+ => mu+ nu_mu ^nu_tau~ " + gammas + ") nu_tau " + gammas + "]cc"
    , "NuTau" : "[B_c+ -> (J/psi(1S) => mu+ mu- " + gammas + ") (tau+ => mu+ nu_mu nu_tau~ " + gammas + ") ^nu_tau " + gammas + "]cc"
    })
MCTauTuple.ToolList = []
from Configurables import LoKi__Hybrid__MCTupleTool
LTT = MCTauTuple.addTupleTool("LoKi::Hybrid::MCTupleTool/LTT")
LTT.Preambulo = ["from LoKiCore.functions import *"]
LTT.Variables = {
    "MCE" : "MCE"
    , "MCETA" : "MCETA"
    , "MCP" : "MCP"
    , "MCPX" : "MCPX"
    , "MCPY" : "MCPY"
    , "MCPZ" : "MCPZ"
    , "MCPT" : "MCPT"
    , "MCTHETA" : "MCTHETA"
    , "MCPHI" : "MCPHI"
    , "MCCTAU" : "MCCTAU"
    , "ACC" : "switch( ( (MCTHETA > 0.005) & (MCTHETA < 0.400) ) | ( (MCTHETA < 3.1365926536) & (MCTHETA > 2.7415926536) ), 1, 0)"
    , "PCS" : "switch( (MCPT > 5*1000) & (MCPT < 100*1000) & ( ( (MCETA > 2.5) & (MCETA < 4.5) ) | ( (MCETA < -2.5) & (MCETA > -4.5) ) ), 1, 0)"
    }
DaVinci().appendToMainSequence( [ MCTauTuple ] )
