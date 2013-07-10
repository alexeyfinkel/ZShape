import FWCore.ParameterSet.Config as cms

process = cms.Process("Zefficiency")
process.TimerService = cms.Service("TimerService")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    SkipEvent = cms.untracked.vstring('ProductNotFound') 
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(40000)
    )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring("file:/hdfs/cms/phedex/store/mc/Summer11/DYToEE_M-20_CT10_TuneZ2_7TeV-powheg-pythia/GEN-SIM-RECO/PU_S4_START42_V11-v1/0001/08EAC5D5-96A8-E011-A47C-0024E876A7E0.root" )
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo_10M_partBUILDINGTTEST.root')
)

process.f2s = cms.EDProducer("ZFullSim2Event"
                             )
import ZShape.EffAcc.FullSimSmearedElectronProducer_cfi
import ZShape.EffAcc.ZEfficiencyKevin_cfi


process.EEXmeanXX9Xsmear = ZShape.EffAcc.FullSimSmearedElectronProducer_cfi.FullSimSmearedElectronsProducer.clone()
process.EEXmeanXX9Xsmear.EE.mean = cms.double(.9)

process.EEXmeanXX9 = ZShape.EffAcc.ZEfficiencyKevin_cfi.mcEff.clone()
process.EEXmeanXX9.zTreeLevelElectronsCollection = cms.untracked.InputTag("f2s","ZEventEle3")
process.EEXmeanXX9.zsrc = cms.untracked.InputTag("EEXmeanXX9Xsmear","ZEventParticles")
process.EEXmeanXX9.zElectronsCollection = cms.untracked.InputTag("EEXmeanXX9Xsmear","ZEventParticles")

process.EEXmeanX1XXsmear = ZShape.EffAcc.FullSimSmearedElectronProducer_cfi.FullSimSmearedElectronsProducer.clone()
process.EEXmeanX1XXsmear.EE.mean = cms.double(1.)

process.EEXmeanX1X = ZShape.EffAcc.ZEfficiencyKevin_cfi.mcEff.clone()
process.EEXmeanX1X.zTreeLevelElectronsCollection = cms.untracked.InputTag("f2s","ZEventEle3")
process.EEXmeanX1X.zsrc = cms.untracked.InputTag("EEXmeanX1XXsmear","ZEventParticles")
process.EEXmeanX1X.zElectronsCollection = cms.untracked.InputTag("EEXmeanX1XXsmear","ZEventParticles")

process.EEXmeanX1X1Xsmear = ZShape.EffAcc.FullSimSmearedElectronProducer_cfi.FullSimSmearedElectronsProducer.clone()
process.EEXmeanX1X1Xsmear.EE.mean = cms.double(1.1)

process.EEXmeanX1X1 = ZShape.EffAcc.ZEfficiencyKevin_cfi.mcEff.clone()
process.EEXmeanX1X1.zTreeLevelElectronsCollection = cms.untracked.InputTag("f2s","ZEventEle3")
process.EEXmeanX1X1.zsrc = cms.untracked.InputTag("EEXmeanX1X1Xsmear","ZEventParticles")
process.EEXmeanX1X1.zElectronsCollection = cms.untracked.InputTag("EEXmeanX1X1Xsmear","ZEventParticles")

process.load("RecoEgamma.EgammaHFProducers.hfEMClusteringSequence_cff")

process.p = cms.Path(process.hfRecoEcalCandidate+
process.f2s
+ process.EEXmeanXX9Xsmear
+ process.EEXmeanXX9
+ process.EEXmeanX1XXsmear
+ process.EEXmeanX1X
+ process.EEXmeanX1X1Xsmear
+ process.EEXmeanX1X1
)
