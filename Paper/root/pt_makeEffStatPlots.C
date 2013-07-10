{
#include "pt_plotEffStat.C"



TFile *my95    = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_WP95_001.root");
TFile *myo95   = new TFile("WP95.root","RECREATE");
TFile *my80    = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_WP80_001.root");
TFile *myo80    = new TFile("WP80.root","RECREATE");
TFile *myGSF   = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_GsfTrack-EtaDet_001.root");
TFile *myoGSF   = new TFile("GSF.root","RECREATE");
TFile *myHFEID = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_HFElectronId-EtaDet_001.root");
TFile *myoHFEID = new TFile("HFEID.root","RECREATE");
TFile *myHFSC  = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_HFSuperCluster-Et_001.root");
TFile *myoHFSC  = new TFile("HFSC.root","RECREATE");
TFile *mySC    = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_Supercluster-Eta_001.root");
TFile *myoSC    = new TFile("SC.root","RECREATE");
TFile *myHLT   = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_HLT-GSF_001.root");
TFile *myoHLT   = new TFile("HLT.root","RECREATE");
TFile *myNT    = new TFile("/local/cms/user/klapoetke/Z2Pow_apr/Z2EcalEffStat100Trials_NTTightElectronId_001.root");
TFile *myoNT    = new TFile("NT.root","RECREATE");

pt_plotEffStat(my95,myo95);
myo95->Write();
pt_plotEffStat(my80,myo80);
myo80->Write();
pt_plotEffStat(myGSF,myoGSF);
myoGSF->Write();
//pt_plotEffStat(myHFEID,myoHFEID);
//myoHFEID->Write();
//pt_plotEffStat(myHFSC,myoHFSC);
//myoHFSC->Write();
pt_plotEffStat(mySC,myoSC);
myoSC->Write();
pt_plotEffStat(myHLT,myoHLT);
myoHLT->Write();
pt_plotEffStat(myNT,myoNT);
myoNT->Write();
myoNT->Close();

}

