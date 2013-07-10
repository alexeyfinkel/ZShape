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
    input = cms.untracked.int32(-1)
    )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames = cms.untracked.vstring("" )
)





process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tags:
process.GlobalTag.globaltag = cms.string('GR_R_42_V14::All')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load("PhysicsTools.PatAlgos.patSequences_cff")










process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo_10M_partBUILDINGTTEST.root')
)

process.load("ZShape.EffAcc.FullSimSmearedElectronProducer_cfi")
process.load("ZShape.EffAcc.ZEfficiencyKevin_cfi")


process.mcEff.systematic = "ECALScale+"
process.mcEff.zsrc = cms.untracked.InputTag("FullSimSmearedElectronsProducer","ZEventParticles")
process.mcEff.zElectronsCollection = cms.untracked.InputTag("FullSimSmearedElectronsProducer","ZEventParticles")
process.mcEff.zTreeLevelElectronsCollection = cms.untracked.InputTag("f2s","ZEventEle3")

process.f2s = cms.EDProducer("ZFullSim2Event"
                             )
process.load("RecoEgamma.EgammaHFProducers.hfEMClusteringSequence_cff")

#process.p = cms.Path(process.makePatElectrons+process.f2s)
process.p = cms.Path(process.hfEMClusteringSequence+process.f2s+process.FullSimSmearedElectronsProducer+process.mcEff)

#process.p = cms.Path(process.SmearedElectronsProducer+ process.mcEff)

