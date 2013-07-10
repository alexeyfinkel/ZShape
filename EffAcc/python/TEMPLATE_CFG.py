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
    fileNames = cms.untracked.vstring("file:/home/jmmans/data/zshape/Summer11_DYToEE_M-20_CT10_TuneZ2_7TeV-powheg-pythia/F61A0CD6-9AA8-E011-A92B-0024E8769B05.root" )
)
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tags:
#process.GlobalTag.globaltag = cms.string('GR_P_V16::All')
#process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load('Configuration.StandardSequences.Services_cff')
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo_10M_partBUILDINGTTEST.root')
)

process.f2s = cms.EDProducer("ZFullSim2Event"
                             )
import ZShape.EffAcc.FullSimSmearedElectronProducer_cfi
import ZShape.EffAcc.ZEfficiencyKevin_cfi

process.pcs=ZShape.EffAcc.FullSimSmearedElectronProducer_cfi.FullSimSmearedElectronsProducer.clone()
process.pcs.HF.constantp = cms.double(meanHFp)
process.pcs.HF.constantm = cms.double(meanHFm)
process.pcs.HF.constantp2 = cms.double(meanHFp)
process.pcs.HF.constantm2 = cms.double(meanHFm)
process.pcs.EB.c = cms.double(meanEB)
process.pcs.EE.c = cms.double(meanEE)
process.pcs.HF.reseta = cms.double(etaResHF)
process.pcs.HF.resphi = cms.double(phiResHF)

process.pcf=ZShape.EffAcc.ZEfficiencyKevin_cfi.mcEff.clone()
process.pcf.zTreeLevelElectronsCollection = cms.untracked.InputTag("f2s","ZEventEle3")
process.pcf.zsrc = cms.untracked.InputTag("pcs","ZEventParticles")
process.pcf.zElectronsCollection = cms.untracked.InputTag("pcs","ZEventParticles")



#process.p = cms.Path(process.makePatElectrons+process.f2s)
process.p = cms.Path(


    process.f2s
    + process.pcs
    + process.pcf



    )
