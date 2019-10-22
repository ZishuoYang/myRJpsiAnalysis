from Configurables import FitDecayTrees

def getRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBcJpsiMu",
        Code = "DECTREE('[B_c+ -> J/psi(1S) mu+]CC')",
        UsePVConstraint = False,
        Inputs = [outputLocation]
        )

    return refitter

def getPsi2SRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBcPsi2SMu",
        Code = "DECTREE('[B_c+ -> psi(2S) mu+]CC')",
        UsePVConstraint = False,
        Inputs = [outputLocation]
        )

    return refitter

def getPsi2SCalRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBcPsi2SMu",
        Code = "DECTREE('[psi(2S) -> J/psi(1S) pi+ pi-]CC')",
        UsePVConstraint = False, # secondary from B
        MassConstraints = ['J/psi(1S)'],
        Inputs = [outputLocation]
        )

    return refitter

def getJpsiPiRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBcJpsiPi",
        Code = "DECTREE('[B_c+ -> J/psi(1S) pi+]CC')",
        UsePVConstraint = True,
        MassConstraints = ['J/psi(1S)'],
        Inputs = [outputLocation]
        )

    return refitter

def getJpsiKRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBJpsiK",
        Code = "DECTREE('[B+ -> J/psi(1S) K+]CC')",
        UsePVConstraint = True,
        MassConstraints = ['J/psi(1S)'],
        Inputs = [outputLocation]
        )

    return refitter

def getJpsiKstRefitter(outputLocation):
    
    refitter = FitDecayTrees(
        "RefitBJpsiK",
        Code = "DECTREE('[B0 -> J/psi(1S) K*(892)0]CC')",
        UsePVConstraint = True,
        MassConstraints = ['J/psi(1S)','K*(892)0'],
        Inputs = [outputLocation]
        )

    return refitter

