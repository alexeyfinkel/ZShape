import FWCore.ParameterSet.Config as cms

process = cms.Process("PAT")


process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
)
# source
process.source = cms.Source("PoolSource",      
    fileNames=cms.untracked.vstring(     )
                  
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

## Load additional processes
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tags:
process.GlobalTag.globaltag = cms.string('GR_P_V16::All')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Services_cff')


################################################################################################
###    P r e p a r a t i o n      o f    t h e    P A T    O b j e c t s   f r o m    A O D  ###
################################################################################################

## pat sequences to be loaded:
#process.load("PhysicsTools.PFCandProducer.PF2PAT_cff")
process.load("PhysicsTools.PatAlgos.patSequences_cff")
#process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")
##
#
## %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
## MET creation     <=== WARNING: YOU MAY WANT TO MODIFY THIS PART OF THE CODE       %%%%%%%%%%%%%
##                                specify the names of the MET collections that you need here %%%%
##                                                                                             #%%
## if you don't specify anything the default MET is the raw Calo MET                           #%%
## if you don't specify anything the default MET is the raw Calo MET                           #%%
process.caloMET = process.patMETs.clone(                                                       #%%
        metSource = cms.InputTag("met","","RECO"),
            addTrigMatch = cms.bool(False),
            addMuonCorrections = cms.bool(False),
            addGenMET = cms.bool(False),
        )
process.tcMET = process.patMETs.clone(                                                         #%%
        metSource = cms.InputTag("tcMet","","RECO"),
            addTrigMatch = cms.bool(False),
            addMuonCorrections = cms.bool(False),
            addGenMET = cms.bool(False),
        )
process.pfMET = process.patMETs.clone(                                                         #%%
        metSource = cms.InputTag("pfMet","","RECO"),
            addTrigMatch = cms.bool(False),
            addMuonCorrections = cms.bool(False),
            addGenMET = cms.bool(False),
        )
## specify here what you want to have on the plots! <===== MET THAT YOU WANT ON THE PLOTS  %%%%%%%
myMetCollection   = 'caloMET'
myPfMetCollection =   'pfMET'
myTcMetCollection =   'tcMET'

## specify here what you want to have on the plots! <===== MET THAT YOU WANT ON THE PLOTS  %%%%%%%
## myDesiredMetCollection = 'layer1RawCaloMETs'
## modify the sequence of the MET creation:                                                    #%%
process.makePatMETs = cms.Sequence(process.caloMET*process.tcMET*process.pfMET)

## GF changed here: more than one pat done here

## %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
## modify the final pat sequence: keep only electrons + METS (muons are needed for met corrections)
process.load("RecoEgamma.EgammaIsolationAlgos.egammaIsolationSequence_cff")
#process.patElectronIsolation = cms.Sequence(process.egammaIsolationSequence)

process.patElectrons.isoDeposits = cms.PSet()
process.patElectrons.userIsolation = cms.PSet()
process.patElectrons.addElectronID = cms.bool(True)
process.patElectrons.electronIDSources = cms.PSet(
    simpleEleId95relIso= cms.InputTag("simpleEleId95relIso"),
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId85relIso= cms.InputTag("simpleEleId85relIso"),
    simpleEleId80relIso= cms.InputTag("simpleEleId80relIso"),
    simpleEleId70relIso= cms.InputTag("simpleEleId70relIso"),
    simpleEleId60relIso= cms.InputTag("simpleEleId60relIso"),
    simpleEleId95cIso= cms.InputTag("simpleEleId95cIso"),
    simpleEleId90cIso= cms.InputTag("simpleEleId90cIso"),
    simpleEleId85cIso= cms.InputTag("simpleEleId85cIso"),
    simpleEleId80cIso= cms.InputTag("simpleEleId80cIso"),
    simpleEleId70cIso= cms.InputTag("simpleEleId70cIso"),
    simpleEleId60cIso= cms.InputTag("simpleEleId60cIso"),    
    )
##
process.patElectrons.addGenMatch = cms.bool(False)
process.patElectrons.embedGenMatch = cms.bool(False)
process.patElectrons.usePV = cms.bool(False)
##
process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")
process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
process.makePatElectrons = cms.Sequence(process.patElectronIDs*process.patElectrons)
# process.makePatMuons may be needed depending on how you calculate the MET
process.makePatCandidates = cms.Sequence(process.makePatElectrons+process.makePatMETs)
process.patDefaultSequence = cms.Sequence(process.makePatCandidates)


##
##  ################################################################################
##
##  generator level filter
##
##  ################################################################################
##  conditions on different particles are OR-ed
process.genFilter = cms.EDFilter("MCSingleParticleFilter",
                                 Status = cms.untracked.vint32(1, 1),
                                 MinEta = cms.untracked.vdouble(-2.4, -2.4),
                                 MaxEta = cms.untracked.vdouble(2.4, 2.4),
                                 MinPt = cms.untracked.vdouble(15.0, 15.0),
                                 ParticleID = cms.untracked.vint32(11, -11) ## these are electron and positron
                                 )





##
##  ################################################################################
##
##  the filter to select the candidates from the data samples
##
##
## WARNING: you may want to modify this item:
HLT_process_name = "HLT"   # 
# trigger path selection
# HLT_path_name    = "HLT_Ele15_LW_L1R"
HLT_path_name     = "HLT_Photon10_L1R"
# trigger filter name
HLT_filter_name  =  "hltL1NonIsoHLTNonIsoSinglePhotonEt10HcalIsolFilter"
# HLT_filter_name  =  "hltL1NonIsoHLTNonIsoSingleElectronLWEt15PixelMatchFilter"
#
HLT_path_name_extra   = "HLT_Photon15_L1R" #= "HLT_Ele15_LW_L1R" #
HLT_filter_name_extra = "hltL1NonIsoHLTNonIsoSinglePhotonEt15HcalIsolFilter"
process.z1legFilter=cms.EDFilter('WenuCandidateFilter',
                                  ### the input collections needed:
                                  electronCollectionTag = cms.untracked.InputTag("patElectrons","","PAT"),
                                  metCollectionTag = cms.untracked.InputTag(myMetCollection,"","PAT"),
                                  pfMetCollectionTag = cms.untracked.InputTag(myPfMetCollection,"","PAT"),
                                  tcMetCollectionTag = cms.untracked.InputTag(myTcMetCollection,"","PAT"),
                                  triggerCollectionTag = cms.untracked.InputTag("TriggerResults","",HLT_process_name),
                                  triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLT_process_name),
                                  hltpath = cms.untracked.string(HLT_path_name),
                                  hltpathFilter = cms.untracked.InputTag(HLT_filter_name,"",HLT_process_name),
                                  ebRecHits = cms.untracked.InputTag("reducedEcalRecHitsEB"),
                                  eeRecHits = cms.untracked.InputTag("reducedEcalRecHitsEE"),
                                  PrimaryVerticesCollection = cms.untracked.InputTag("offlinePrimaryVertices"),
                                  ### here the preselection is applied
                                  # fiducial cuts:
                                  BarrelMaxEta = cms.untracked.double(1.4442),
                                  EndCapMinEta = cms.untracked.double(1.566),
                                  EndCapMaxEta = cms.untracked.double(2.5),
                                  # demand ecal driven electron:
                                  useEcalDrivenElectrons = cms.untracked.bool(True),
                                  # demand offline spike cleaning with the Swiss Cross criterion:
                                  useSpikeRejection = cms.untracked.bool(True),
                                  spikeCleaningSwissCrossCut = cms.untracked.double(0.95),
                                  # demand geometrically matched to an HLT object with ET>15GeV
                                  useTriggerInfo = cms.untracked.bool(False), # GF 
                                  electronMatched2HLT = cms.untracked.bool(False), # GF 
                                  electronMatched2HLT_DR = cms.untracked.double(0.2), # GF 
                                  useHLTObjectETCut = cms.untracked.bool(False), # GF 
                                  hltObjectETCut = cms.untracked.double(15.),
                                  useExtraTrigger = cms.untracked.bool(False), # GF 
                                  hltpathExtra = cms.untracked.string(HLT_path_name_extra),
                                  hltpathFilterExtra = cms.untracked.InputTag(HLT_filter_name_extra,"",HLT_process_name),
                                  # ET Cut in the SC
                                  ETCut = cms.untracked.double(10.), # GF : mistakenly set to 20 in the first pass
                                  METCut = cms.untracked.double(0.),
                                  # reject events with a 2nd electron with ET > 20 that passes the WP95%
                                  vetoSecondElectronEvents = cms.untracked.bool(False),
                                  storeSecondElectron = cms.untracked.bool(False),
                                  ETCut2ndEle = cms.untracked.double(20.),
                                  vetoSecondElectronIDType = cms.untracked.string("simpleEleId80relIso"), # GF
                                  vetoSecondElectronIDSign = cms.untracked.string("="),
                                  vetoSecondElectronIDValue = cms.untracked.double(7.),
                                  # Other parameters of the code - leave them as they are
                                  useValidFirstPXBHit = cms.untracked.bool(False),
                                  useConversionRejection = cms.untracked.bool(False),
                                  useExpectedMissingHits = cms.untracked.bool(False),
                                  maxNumberOfExpectedMissingHits = cms.untracked.int32(1),
                                  # calculate some new cuts
                                  calculateValidFirstPXBHit = cms.untracked.bool(True),
                                  calculateConversionRejection = cms.untracked.bool(True),
                                  calculateExpectedMissingHits = cms.untracked.bool(True),
                                  # we are dealing with DATA
                                  dataMagneticFieldSetUp = cms.untracked.bool(False),
                                  dcsTag = cms.untracked.InputTag("scalersRawToDigi"),
                                  )

# = cms.EDFilter('WenuCandidateFilter',
#                                   # cfg for data
#                                   dataMagneticFieldSetUp = cms.untracked.bool(False), # set to False in MC!
#                                   dcsTag = cms.untracked.InputTag("scalersRawToDigi"),
#                                   # cuts
#                                   ETCut = cms.untracked.double(10.),
#                                   METCut = cms.untracked.double(0.),
#                                   # 2nd electron in W events
#                                   vetoSecondElectronEvents = cms.untracked.bool(False),
#                                   ETCut2ndEle = cms.untracked.double(20.),
#                                   vetoSecondElectronIDType = cms.untracked.string("simpleEleId80relIso"),
#                                   vetoSecondElectronIDSign = cms.untracked.string("="),
#                                   vetoSecondElectronIDValue = cms.untracked.double(7.),
#                                   # trigger 
#                                   useTriggerInfo = cms.untracked.bool(False),
#                                   triggerCollectionTag = cms.untracked.InputTag("TriggerResults","",HLT_process_name),
#                                   triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLT_process_name),
#                                   hltpath = cms.untracked.string(HLT_path_name), 
#                                   hltpathFilter = cms.untracked.InputTag(HLT_filter_name,"",HLT_process_name),
#                                   electronMatched2HLT = cms.untracked.bool(False),
#                                   electronMatched2HLT_DR = cms.untracked.double(0.2),
#                                   # additional preselection cuts
#                                   useValidFirstPXBHit = cms.untracked.bool(False),
#                                   useConversionRejection = cms.untracked.bool(False),
#                                   useExpectedMissingHits = cms.untracked.bool(False),
#                                   maxNumberOfExpectedMissingHits = cms.untracked.int32(1),
#                                   # calculate some new cuts
#                                   calculateValidFirstPXBHit = cms.untracked.bool(True),
#                                   calculateConversionRejection = cms.untracked.bool(True),
#                                   calculateExpectedMissingHits = cms.untracked.bool(True),
#                                   # electrons and MET
#                                   electronCollectionTag = cms.untracked.InputTag("patElectrons","","PAT"),
#                                   metCollectionTag = cms.untracked.InputTag(myDesiredMetCollection,"","PAT"),
# 
#                                   )
####################################################################################







# to access values of EldId cuts as defined by the EWK group
import ElectroWeakAnalysis.WENu.simpleCutBasedElectronIDSpring10_cfi

# EWK analyzer: different Z definitions with one ECAL electron and one HF electron
# ---> this is the instance to run AFTER the Wenu EWK filter


import ZShape.HFZeeVBTF.hfzeevbtf_cfi

process.hfzee = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzee.Zmass=cms.vdouble(70,120)
process.hfzee.skipTrigger = cms.bool(True)

# EWK analyzer: different Z definitions with one ECAL electron and one HF electron
process.hfzeeLoose = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()

process.hfzeeLoose.acceptedElectronIDs = cms.vint32( 3, 7 )
process.hfzeeLoose.myName=cms.string('looseish')
process.hfzeeLoose.skipTrigger = cms.bool(True)                             

process.hfzeeBefCuts = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzeeBefCuts.Zmass=cms.vdouble(2,200)
process.hfzeeBefCuts.minEtECAL=cms.double(10)
process.hfzeeBefCuts.minEtHF=cms.double(10)
process.hfzeeBefCuts.acceptedElectronIDs = cms.vint32( 1,2,3,4,5,6,7 )
process.hfzeeBefCuts.ECALid=cms.string('simpleEleId95cIso')
process.hfzeeBefCuts.hFselParams =  cms.vdouble(0.2, 0.90,      0.0, 0.0,    -9999, -9999,     9999, 9999)
process.hfzeeBefCuts.myName=cms.string('befCuts')
process.hfzeeBefCuts.skipTrigger = cms.bool(True)

process.hfzeeTriggered = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzeeTriggered.acceptedElectronIDs = cms.vint32( 1,2,3,4,5,6,7 )
process.hfzeeTriggered.Zmass=cms.vdouble(2,200)
process.hfzeeTriggered.minEtECAL=cms.double(10)
process.hfzeeTriggered.minEtHF=cms.double(10)
process.hfzeeTriggered.ECALid=cms.string('simpleEleId95cIso')
process.hfzeeTriggered.hFselParams =  cms.vdouble(0.2, 0.90,      0.0, 0.0,    -9999, -9999,     9999, 9999)
process.hfzeeTriggered.myName=cms.string('befCuts')
process.hfzeeTriggered.skipTrigger = cms.bool(True)

process.hfzeeTSigLike = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzeeTSigLike.acceptedElectronIDs = cms.vint32( 7 )
process.hfzeeTSigLike.Zmass=cms.vdouble(70,115)
process.hfzeeTSigLike.minEtECAL=cms.double(10)
process.hfzeeTSigLike.minEtHF=cms.double(10)
process.hfzeeTSigLike.ECALid=cms.string('simpleEleId80cIso')   
process.hfzeeTSigLike.hFselParams =  cms.vdouble(0.2, 0.90,      0.0, 0.0,    -9999, -9999,     9999, 9999)
process.hfzeeTSigLike.myName=cms.string('befCuts')
process.hfzeeTSigLike.skipTrigger = cms.bool(True)

process.hfzeeTBkgLike = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzeeTBkgLike.acceptedElectronIDs = cms.vint32( 1,2,3,4,5,6,7 )
process.hfzeeTBkgLike.Zmass=cms.vdouble(2,70)
process.hfzeeTBkgLike.minEtECAL=cms.double(10)
process.hfzeeTBkgLike.minEtHF=cms.double(10)
process.hfzeeTBkgLike.ECALid=cms.string('simpleEleId95cIso')   
process.hfzeeTBkgLike.hFselParams =  cms.vdouble(-0.2, -0.90,      0.0, 0.0,    -9999, -9999,     9999, 9999)
process.hfzeeTBkgLike.myName=cms.string('befCuts')
process.hfzeeTBkgLike.skipTrigger = cms.bool(True)


process.hfzeeNotTrig = ZShape.HFZeeVBTF.hfzeevbtf_cfi.hfzeevbtf.clone()
process.hfzeeNotTrig.acceptedElectronIDs = cms.vint32( 1,2,3,4,5,6,7 )
process.hfzeeNotTrig.Zmass=cms.vdouble(2,200)
process.hfzeeNotTrig.minEtECAL=cms.double(10)
process.hfzeeNotTrig.minEtHF=cms.double(10)
process.hfzeeNotTrig.ECALid=cms.string('simpleEleId95cIso')
process.hfzeeNotTrig.hFselParams =  cms.vdouble(0.2, 0.90,      0.0, 0.0,    -9999, -9999,     9999, 9999)
process.hfzeeNotTrig.myName=cms.string('befCuts')
process.hfzeeNotTrig.skipTrigger = cms.bool(True)                             

# THIS IS PROD
process.TFileService = cms.Service("TFileService",
       fileName = cms.string(""),
)


process.pickTriggered=triggerResultsFilter = cms.EDFilter('TriggerResultsFilter',
                                                          hltResults              = cms.InputTag('TriggerResults','','HLT'),   # HLT results   - set to empty to ignore HLT
                                                          l1tResults              = cms.InputTag(''),       # L1 GT results - set to empty to ignore L1
                                                          l1tIgnoreMask           = cms.bool(False),                  # use L1 mask
                                                          l1techIgnorePrescales   = cms.bool(False),                  # read L1 technical bits from PSB#9, bypassing the prescales
                                                          daqPartitions           = cms.uint32(0x01),                 # used by the definition of the L1 mask
                                                          throw                   = cms.bool(True),                   # throw exception on unknown trigger names
                                                          triggerConditions       = cms.vstring( 'HLT_Ele17_CaloIdL_CaloIsoVL_Ele15_HFL_*' )
                                                          )

process.pickNotTriggered=triggerResultsFilter = cms.EDFilter('TriggerResultsFilter',
                                                          hltResults              = cms.InputTag('TriggerResults','','HLT'),   # HLT results   - set to empty to ignore HLT
                                                          l1tResults              = cms.InputTag(''),       # L1 GT results - set to empty to ignore L1
                                                          l1tIgnoreMask           = cms.bool(False),                  # use L1 mask
                                                          l1techIgnorePrescales   = cms.bool(False),                  # read L1 technical bits from PSB#9, bypassing the prescales
                                                          daqPartitions           = cms.uint32(0x01),                 # used by the definition of the L1 mask
                                                          throw                   = cms.bool(True),                   # throw exception on unknown trigger names
                                                          triggerConditions       = cms.vstring( 'HLT_Ele17_CaloIdL_CaloIsoVL_* AND (NOT HLT_Ele17_CaloIdL_CaloIsoVL_Ele15_HFL_*)' )
                                                          )

process.load("RecoEgamma.EgammaHFProducers.hfRecoEcalCandidate_cfi")
process.hfRecoEcalCandidate.intercept2DCut=0.2
process.hfRecoEcalCandidate.e9e25Cut      =0.9

process.hfRecoEcalCandidate.e1e9Cut = cms.vdouble(0.6,99)

# 0.94 is the same as default in the HF cluster producer


process.ztPath = cms.Path(
    process.patDefaultSequence *
    process.hfzeeBefCuts *
    process.z1legFilter *
    process.hfRecoEcalCandidate *
    process.pickTriggered *
    process.hfzeeTriggered *
    process.hfzeeTSigLike *
    process.hfzeeTBkgLike
    )

process.zntPath = cms.Path(
    process.patDefaultSequence *
    process.hfzeeBefCuts *
    process.z1legFilter *
    process.hfRecoEcalCandidate *
    process.pickNotTriggered *
    process.hfzeeNotTrig
    )

