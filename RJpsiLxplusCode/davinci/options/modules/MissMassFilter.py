from PhysSelPython.Wrappers import Selection, SelectionSequence
from Configurables import FilterDesktop
from Configurables import AddExtraInfo, MissMassTool

def getMissMassVars(MyBcSelection):

    return MissMassVars

def getMissMassFilteredSeq(MyBcSelection):
    
    MissMassFilter = FilterDesktop( "MissMassFilter",
                                    Code = "(INFO(1234567+0, 0.) > -5) & (INFO(1234567+0, 0.) < 15.0)" )
    MissMassFilteredSel = Selection('MissMassFilteredSel',
                                    Algorithm = MissMassFilter,
                                    RequiredSelections = [MyBcSelection])
    MissMassFilteredSeq = SelectionSequence('MissMassFilteredSeq',
                                            TopSelection = MissMassFilteredSel)
    return MissMassFilteredSeq

