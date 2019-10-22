##################### Stripping Lines #####################
JpsiFromBNoPIDNoMipLine           = "MuIDCalib_JpsiFromBNoPIDNoMip"
JpsiKFromBNoPIDNoMipLine          = "MuIDCalib_JpsiKFromBNoPIDNoMip"

#################### Candidate filters ######################
from Configurables import TupleToolPIDCalib
_l0TisTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTisL0Criterion')
_hlt1TisTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTisHlt1Criterion')
_hlt2TisTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTisHlt2Criterion')

_l0TosTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTosL0Criterion')
_hlt1TosTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTosHlt1Criterion')
_hlt2TosTagCrit=TupleToolPIDCalib.getDefaultProperty('MuonTosHlt2Criterion')

def L0TIS(code):
    return "TIS('{0}', 'L0TriggerTisTos')".format(code)
def L0TOS(code):
    return "TOS('{0}', 'L0TriggerTisTos')".format(code)
def HltTIS(code):
    return "TIS('{0}', 'TriggerTisTos')".format(code)
def HltTOS(code):
    return "TOS('{0}', 'TriggerTisTos')".format(code)

# Require 'LoP' line has proton momentum <40GeV/c
LoP_CandFilter = "NINTREE( ('p+'==ABSID) & (P<40000) )==1"

# Require 'HiP' line has proton momentum <40GeV/c
HiP_CandFilter =  "NINTREE( ('p+'==ABSID) & (P>40000) )==1"

# Require at least one 'MuonUnBiased' daughter
MuonUnBiased_CandFilter = ("NINTREE( (ISBASIC) & ({l0}) "
                       "& ({hlt1}) & ({hlt2}) )>0").format(
     l0=L0TIS(_l0TisTagCrit), hlt1=HltTIS(_hlt1TisTagCrit),
     hlt2=HltTIS(_hlt2TisTagCrit))

# Require at least one 'MuonUnBiased' granddaughter
MuonUnBiased_SecondaryCandFilter = ("NINGENERATION( (ISBASIC) & ({l0}) & "
            "({hlt1}) & ({hlt2}), 2 )>0").format(
     l0=L0TIS(_l0TisTagCrit), hlt1=HltTIS(_hlt1TisTagCrit),
     hlt2=HltTIS(_hlt2TisTagCrit))

# Require at least one 'Muon TOS-tagged' daughter
MuonTosTagged_CandFilter = ("NINTREE( (ISBASIC) & ({l0}) & "
                            "({hlt1}) & ({hlt2}) )>0").format(
    l0=L0TOS(_l0TosTagCrit), hlt1=HltTOS(_hlt1TosTagCrit),
    hlt2=HltTOS(_hlt2TosTagCrit))

# Require at least one 'Muon TOS-tagged' granddaughter
MuonTosTagged_SecondaryCandFilter = ("NINGENERATION( (ISBASIC) & ({l0}) "
                       "& ({hlt1}) & ({hlt2}), 2 )>0").format(
     l0=L0TOS(_l0TosTagCrit), hlt1=HltTOS(_hlt1TosTagCrit),
     hlt2=HltTOS(_hlt2TosTagCrit))

# Require Lambda_b decay is unbiased with respect to proton PID
Lb2LcMuNu_Lc2PKPi_CandFilter = ("( ({l0Tos}) | ({l0Tis}) ) & "
                                "({hlt1Tos}) & ({hlt2Tos})").format(
                                l0Tos=L0TOS("L0(Muon|Hadron)Decision"),
                                l0Tis=L0TIS("L0.*Decision"),
                                hlt1Tos=HltTOS("Hlt1(TrackAllL0|TrackMuon|SingleMuonHighPT)Decision"),
                                hlt2Tos=HltTOS("Hlt2(SingleMuon|TopoMu).*Decision"))

# Require Sigma_c decay is unbiased with respect to proton PID
Sigc2LcPi_CandFilter =  ("( ({l0Tos}) | ({l0Tis}) ) & "
                        "({hlt1Tos}) & ( ({hlt2Tos}) | ({hlt2Tis}) )").format(
                        l0Tos=L0TOS("L0HadronDecision"),
                        l0Tis=L0TIS("L0.*Decision"),
                        hlt1Tos=HltTOS("Hlt1TrackAllL0Decision"),
                        hlt2Tos=HltTOS("CharmHadD02HHXDst_hhX.*Decision"),
                        hlt2Tis=HltTIS("Hlt2.*Decision"))

# combination of MuonUnbiased filter and LoP Lambda0 filter
MuonUnBiased_LoP_CandFilter='({loPCut}) & ({muonUnbiasedCut})'.format(
    loPCut=LoP_CandFilter, muonUnbiasedCut=MuonUnBiased_CandFilter)

# combination of MuonUnbiased filter and LoP Lambda0 filter
MuonUnBiased_HiP_CandFilter='({hiPCut}) & ({muonUnbiasedCut})'.format(
    hiPCut=HiP_CandFilter, muonUnbiasedCut=MuonUnBiased_CandFilter)


##orig cut
#Jpsiee_CandFilter = "(NINTREE( ('e-'==ABSID) & (BPVIPCHI2()>25) )==2 ) & (BPVIPCHI2()<9.0) & (VFASPF(VCHI2)<9.0) & (inRange(5000,MM,5600))"
##one sided delm cut
#Jpsiee_CandFilter = "(NINTREE( ('e-'==ABSID) & (BPVIPCHI2()>25) )==2 ) & (BPVIPCHI2()<9.0) & (VFASPF(VCHI2)<9.0) & ((MM-CHILD(MM,1))>2082.3) & (inRange(2250,CHILD(MM,1),3600))"
##two sided delm cut
Jpsiee_CandFilter = "(NINTREE( ('e-'==ABSID) & (BPVIPCHI2()>25) )==2 ) & (BPVIPCHI2()<9.0) & (VFASPF(VCHI2)<9.0) & (abs(MM-CHILD(MM,1)-2182.3)<100) & (inRange(2250,CHILD(MM,1),3600))"
#Jpsiee_CandFilter = "( NINTREE( ('e-'==ABSID) & (BPVIPCHI2()>25) & (PT>500) & (P>5000) )==2 ) & (5000 < MM) & (MM < 5600) & (BPVIPCHI2()<9.0) & (VFASPF(VCHI2)<9.0)"

#"eplus_IPCHI2_OWNPV >25 && eminus_IPCHI2_OWNPV>25. && eplus_PT>500. && eminus_PT>500. && eplus_P>5000. && eminus_P>5000. &&  eplus_PIDe>5. &&  Bplus_MM>5000 && Bplus_MM<5600 && Bplus_IPCHI2_OWNPV <9.0 && Bplus_ENDVERTEX_CHI2<9.0"
#eplus_PIDe>5. &&

#eplus_IPCHI2_OWNPV >25 &&
#eminus_IPCHI2_OWNPV>25. &&
#eplus_PT>500. &&
#eminus_PT>500. &&
#eplus_P>5000. &&
#eminus_P>5000. &&

#eplus_PIDe>5. &&
#Bplus_MM>5000 &&
#Bplus_MM<5600 &&
#Bplus_IPCHI2_OWNPV <9.0 &&
#Bplus_ENDVERTEX_CHI2<9.0"

CandFilters = {
    # standard tuples
    'K0S2PiPi'                         : None
    ,'Lam02PPi_LoP'                    : LoP_CandFilter
    ,'Lam02PPi_HiP'                    : HiP_CandFilter
    ,'DSt2D0Pi_D02RSKPi'               : None
    ,'JpsiFromBNoPIDNoMip'             : MuonUnBiased_CandFilter
    ,'JpsiKFromBNoPIDNoMip'            : MuonUnBiased_SecondaryCandFilter
    ,'Lb2LcMuNu_Lc2PKPi'               : Lb2LcMuNu_Lc2PKPi_CandFilter
    ,'Sigc02LcPi_Lc2PKPi'              : None # need to check HLT2 efficiencies, especially for 2011 data
    ,'Sigcpp2LcPi_Lc2PKPi'             : None # need to check HLT2 efficiencies, especially for 2011 data
    ,'JpsieeKFromB'                    : Jpsiee_CandFilter
    # MuonUnBiased tuples
    ,'K0S2PiPi_MuonUnBiased'           : MuonUnBiased_CandFilter
    ,'Lam02PPi_LoP_MuonUnBiased'       : MuonUnBiased_LoP_CandFilter
    ,'Lam02PPi_HiP_MuonUnBiased'       : MuonUnBiased_HiP_CandFilter
    ,'DSt2D0Pi_D02RSKPi_MuonUnBiased'  : MuonUnBiased_SecondaryCandFilter
    ,'Lb2LcMuNu_Lc2PKPi_MuonUnBiased'  : MuonUnBiased_SecondaryCandFilter
    ,'Sigc02LcPi_Lc2PKPi_MuonUnBiased' : MuonUnBiased_SecondaryCandFilter
    ,'Sigcpp2LcPi_Lc2PKP_MuonUnBiased' : MuonUnBiased_SecondaryCandFilter
    ,'JpsieeKFromB_MuonUnBiased'       : MuonUnBiased_SecondaryCandFilter
    # TOSTagged tuples
    ,'JpsiFromBNoPIDNoMip_TOSTagged'   : MuonTosTagged_CandFilter
    ,'JpsiKFromBNoPIDNoMip_TOSTagged'  : MuonTosTagged_SecondaryCandFilter
}

################ Dictionaries for each NTuple ###############
### stripping line names
StripLines = {
    # standard tuples
    'K0S2PiPi'                          : K0S2PiPiLine
    ,'Lam02PPi_LoP'                     : Lam02PPi_LoPLine
    ,'Lam02PPi_HiP'                     : Lam02PPi_HiPLine
    ,'DSt2D0Pi_D02RSKPi'                : DSt2D0Pi_D02RSKPiLine
    ,'JpsiFromBNoPIDNoMip'              : JpsiFromBNoPIDNoMipLine
    ,'JpsiKFromBNoPIDNoMip'             : JpsiKFromBNoPIDNoMipLine
    ,'Lb2LcMuNu_Lc2PKPi'                : Lb2LcMuNu_Lc2PKPiLine
    ,'Sigc02LcPi_Lc2PKPi'               : Sigc02LcPi_Lc2PKPiLine
    ,'Sigcpp2LcPi_Lc2PKPi'              : Sigcpp2LcPi_Lc2PKPiLine
    ,'JpsieeKFromB'                     : JpsieeKFromBLine
    # MuonUnBiased tuples
    ,'K0S2PiPi_MuonUnBiased'            : K0S2PiPiLine
    ,'Lam02PPi_LoP_MuonUnBiased'        : Lam02PPi_LoPLine
    ,'Lam02PPi_HiP_MuonUnBiased'        : Lam02PPi_HiPLine
    ,'DSt2D0Pi_D02RSKPi_MuonUnBiased'   : DSt2D0Pi_D02RSKPiLine
    ,'Lb2LcMuNu_Lc2PKPi_MuonUnBiased'   : Lb2LcMuNu_Lc2PKPiLine
    ,'Sigc02LcPi_Lc2PKPi_MuonUnBiased'  : Sigc02LcPi_Lc2PKPiLine
    ,'Sigcpp2LcPi_Lc2PKP_MuonUnBiased'  : Sigcpp2LcPi_Lc2PKPiLine
    ,'JpsieeKFromB_MuonUnBiased'        : JpsieeKFromBLine
    # TOSTagged tuples
    ,'JpsiFromBNoPIDNoMip_TOSTagged'    : JpsiFromBNoPIDNoMipLine
    ,'JpsiKFromBNoPIDNoMip_TOSTagged'   : JpsiKFromBNoPIDNoMipLine
}

### Event filters
EventFilters = {
    # standard tuples
    'K0S2PiPi'                          : None
    ,'Lam02PPi_LoP'                     : None
    ,'Lam02PPi_HiP'                     : None
    ,'DSt2D0Pi_D02RSKPi'                : None
    ,'JpsiFromBNoPIDNoMip'              : None
    ,'JpsiKFromBNoPIDNoMip'             : None
    ,'Lb2LcMuNu_Lc2PKPi'                : None
    ,'Sigc02LcPi_Lc2PKPi'               : None
    ,'Sigcpp2LcPi_Lc2PKP'               : None
    ,'JpsieeKFromB'                     : None
    # MuonUnBiased tuples
    ,'K0S2PiPi_MuonUnBiased'            : None
    ,'Lam02PPi_LoP_MuonUnBiased'        : None
    ,'Lam02PPi_HiP_MuonUnBiased'        : None
    ,'DSt2D0Pi_D02RSKPi_MuonUnBiased'   : None
    ,'Lb2LcMuNu_Lc2PKPi_MuonUnBiased'   : None
    ,'Sigc02LcPi_Lc2PKPi_MuonUnBiased'  : None
    ,'Sigcpp2LcPi_Lc2PKP_MuonUnBiased'  : None
    ,'JpsieeKFromB_MuonUnBiased'        : None
    # TOSTagged tuples
    ,'JpsiFromBNoPIDNoMip_TOSTagged'    : None
    ,'JpsiKFromBNoPIDNoMip_TOSTagged'   : None
}

__all__=('StripLines', 'CandFilters', 'EventFilters')

