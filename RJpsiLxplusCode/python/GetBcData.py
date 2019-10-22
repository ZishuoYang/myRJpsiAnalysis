JpsiMuNu = "14543010"
JpsiTauNu = "14643048"
Psi2SMuNu = "14845008"
Psi2STauNu = "14845018"
JpsiDx = "14873607"
B0Comb = "11442012"
BpComb = "12442012"
BsComb = "13442012"

def GetBcMC(year,polarity,id):
    energy = '3500' if (year == "2011") else ('4000' if (year == "2012") else 'NONE')
    nu = '2' if (year == "2011") else ('2.5' if (year == "2012") else 'NONE')
    trigger = '760037' if (year == "2011") else ('9f0045' if (year == "2012") else 'NONE')
    stripping = '20r1' if (year == "2011") else ('20' if (year == "2012") else 'NONE')
    str = '/MC/' + year + '/Beam' + energy + 'GeV-' + year + '-Mag' + polarity + '-Nu' + nu + '-BcVegPy'
    str += '/Sim08e/Digi13/Trig0x40' + trigger + '/Reco14a/Stripping' + stripping + 'NoPrescalingFlagged/' + id + '/ALLSTREAMS.DST'
    return str

def GetCombMC(year,pythia,polarity,id):
    energy = '3500' if (year == "2011") else ('4000' if (year == "2012") else 'NONE')
    nu = '2' if (year == "2011") else ('2.5' if (year == "2012") else 'NONE')
    trigger = '760037' if (year == "2011") else ('9f0045' if (year == "2012") else 'NONE')
    stripping = '20r1' if (year == "2011") else ('20' if (year == "2012") else 'NONE')
    str = '/MC/' + year + '/Beam' + energy + 'GeV-' + year + '-Mag' + polarity + '-Nu' + nu + '-Pythia' + pythia
    str += '/Sim08d/Digi13/Trig0x40' + trigger + '/Reco14a/Stripping' + stripping + 'NoPrescalingFlagged/' + id + '/ALLSTREAMS.DST'
    return str

def GetDiMuonData(year,polarity):
    type = '11' if (year == "2011" or year == "2011reco12") else ('12' if (year == "2012") else 'NONE')
    energy = '3500' if (year == "2011" or year == "2011reco12") else ('4000' if (year == "2012") else 'NONE')
    reco = '14' if (year == "2011" or year == "2012") else ('12' if (year == "2011reco12") else 'NONE')
    stripping = '20r1' if (year == "2011") else ('17' if (year == "2011reco12") else ('20' if (year == "2012") else 'NONE'))
    str = '/LHCb/Collision' + type + '/Beam' + energy + 'GeV-VeloClosed-Mag' + polarity
    str += '/Real Data/Reco' + reco + '/Stripping' + stripping + '/90000000/DIMUON.DST'
    return str

def GetCharmData(year,polarity):
    type = '11' if (year == "2011" or year == "2011reco12") else ('12' if (year == "2012") else 'NONE')
    energy = '3500' if (year == "2011" or year == "2011reco12") else ('4000' if (year == "2012") else 'NONE')
    reco = '14' if (year == "2011" or year == "2012") else ('12' if (year == "2011reco12") else 'NONE')
    stripping = '20r1' if (year == "2011") else ('17' if (year == "2011reco12") else ('20' if (year == "2012") else 'NONE'))
    str = '/LHCb/Collision' + type + '/Beam' + energy + 'GeV-VeloClosed-Mag' + polarity
    str += '/Real Data/Reco' + reco + '/Stripping' + stripping + '/90000000/CHARMCOMPLETEEVENT.DST'
    return str
