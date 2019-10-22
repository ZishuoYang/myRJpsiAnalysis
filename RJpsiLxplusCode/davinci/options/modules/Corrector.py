from Configurables import FitDecayTrees
from Configurables import TrackScaleState as DATA_SCALER
from Configurables import TrackSmearState as MC_SMEARER

def getRefitter(simulation):

    refitter = FitDecayTrees
