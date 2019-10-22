from PhysConf.Filters import LoKi_Filters
TriggerStrippingFilter = LoKi_Filters(
    L0DU_Code = "L0_CHANNEL_RE('.*Muon')",
    HLT1_Code  = "HLT_PASS_RE( 'Hlt1DiMuon.*MassDecision')",
    HLT2_Code  = "HLT_PASS_RE( 'Hlt2DiMuon.*Decision' )",
    STRIP_Code = "HLT_PASS_RE( 'StrippingFullDSTDiMuonJpsi2MuMuDetachedLineDecision' )"
    )
