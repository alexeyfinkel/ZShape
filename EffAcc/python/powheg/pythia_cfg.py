##################################################################
#   $title
##################################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("POWHEGLHE")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("LHESource",
  fileNames = cms.untracked.vstring(
  'file:pwgevents_noExcess.lhe'
   )
)

process.configurationMetadata = cms.untracked.PSet(
  version = cms.untracked.string('alpha'),
  name = cms.untracked.string('LHEF input'),
  annotation = cms.untracked.string('powhegz')
)

process.options = cms.untracked.PSet(SkipEvent = cms.untracked.vstring('ProductNotFound'))

process.load("Configuration.StandardSequences.Services_cff")

process.RandomNumberGeneratorService.generator = cms.PSet(
  initialSeed = cms.untracked.uint32(123456789),
  engineName = cms.untracked.string('HepJamesRandom')
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

from Configuration.Generator.PythiaUEZ2Settings_cfi import *
process.generator = cms.EDFilter("Pythia6HadronizerFilter",

     comEnergy = cms.double(7000.0),
     PythiaParameters = cms.PSet(
        pythiaUESettingsBlock,
        processParameters = cms.vstring('MSEL=0          ! User defined processes',
                                        'PMAS(5,1)=4.4   ! b quark mass',
                                        'PMAS(6,1)=172.4 ! t quark mass'),
        # This is a vector of ParameterSet names to be read, in this order
        parameterSets = cms.vstring('pythiaUESettings',
                                    'processParameters'
                                    )
        )
)

process.load("Configuration.StandardSequences.Generator_cff")

process.p0 = cms.Path(
  process.generator *
  process.pgen
)

process.load("Configuration.StandardSequences.VtxSmearedGauss_cff")

process.VtxSmeared.src = 'generator'
#process.genEventWeight.src = 'generator'
#process.genEventScale.src = 'generator'
#process.genEventPdfInfo.src = 'generator'
#process.genEventProcID.src = 'generator'
process.genParticles.src = 'generator'
process.genParticleCandidates.src = 'generator'

process.genParticles.abortOnUnknownPDGCode = False

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printList = cms.EDFilter("ParticleListDrawer",
  src = cms.InputTag("genParticles"),
  maxEventsToPrint = cms.untracked.int32(-1)
)

process.printTree = cms.EDFilter("ParticleTreeDrawer",
  src = cms.InputTag("genParticles"),
  printP4 = cms.untracked.bool(False),
  printPtEtaPhi = cms.untracked.bool(False),
  printVertex = cms.untracked.bool(True),
  printStatus = cms.untracked.bool(False),
  printIndex = cms.untracked.bool(False),
  status = cms.untracked.vint32(1, 2, 3)
)

process.p = cms.Path(
  process.printList *
  process.printTree
)


#process.demo = cms.EDAnalyzer('LHEReaderAnalyzer',
#    histName = cms.string('LHAGLUE_$nPDF')
#)
#process.r = cms.Path(process.demo)

#process.TFileService = cms.Service("TFileService",
#    fileName = cms.string('histo_LHAGLUE$nPDF-$j.root')
#)



process.load("ZShape.EffAcc.ZEventProducer_cfi")
process.ZIntoElectronsEventProducer.src = 'generator'

#process.dumpEv = cms.EDAnalyzer("EventContentAnalyzer")

process.p1 = cms.Path(
          process.VtxSmeared *
         process.ZIntoElectronsEventProducer
     #  * process.dumpEv
)


process.load("Configuration.EventContent.EventContent_cff")

process.LHE = cms.OutputModule("PoolOutputModule",
  dataset = cms.untracked.PSet(dataTier = cms.untracked.string('LHE')),
  fileName = cms.untracked.string('powhegz_LHAGLUE.root'),
  outputCommands = cms.untracked.vstring(
   "drop *",
   "keep *_ZIntoElectronsEventProducer_*_*"
	)
)


process.outpath = cms.EndPath(process.LHE)

#process.schedule = cms.Schedule(process.r, process.p0, process.p1, process.outpath)
process.schedule = cms.Schedule(process.p0, process.p1, process.outpath)
