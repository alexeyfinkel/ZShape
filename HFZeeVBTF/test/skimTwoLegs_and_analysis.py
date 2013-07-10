import FWCore.ParameterSet.Config as cms

# process = cms.Process("Zshape-skim-analysis")
process = cms.Process("skim-and-Zshape-analysis")


process.load('FWCore/MessageService/MessageLogger_cfi')
# JM: increase this not to be flooded by messages
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
Rethrow = cms.untracked.vstring('ProductNotFound'),
)


import FWCore.Modules.printContent_cfi
process.dumpEv = FWCore.Modules.printContent_cfi.printContent.clone()

# source
process.source = cms.Source("PoolSource",      
    fileNames=cms.untracked.vstring(     )
   #     'file:/local/cms/phedex/store/mc/Spring10/Zee/GEN-SIM-RECO/START3X_V26_S09-v1/0036/F635D8DC-9949-DF11-9934-001A64789E6C.root'  #  this is a MC test
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
                            fileMode = cms.untracked.string('NOMERGE')
)


## Load additional processes
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tags:
process.GlobalTag.globaltag = cms.string('GR_R_36X_V11A::All') ## GF changed here
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Services_cff')


################################################################################################
################################################################################################
###    P r e p a r a t i o n      o f    t h e    P A T    O b j e c t s   f r o m    A O D  ###
################################################################################################

## pat sequences to be loaded:
process.load("PhysicsTools.PatAlgos.patSequences_cff")

#
## %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
## MET creation     <=== WARNING: YOU MAY WANT TO MODIFY THIS PART OF THE CODE       %%%%%%%%%%%%%
##                                specify the names of the MET collections that you need here %%%%
##                                                                                             #%%
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
#  difference between data and MC
# JM ==> set to TRUE to tell the ID that it is data
# JM ==> or set to talse if it's MC
#  process.simpleEleId95relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId90relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId85relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId80relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId70relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId60relIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId95cIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId90cIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId85cIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId80cIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId70cIso.dataMagneticFieldSetUp = cms.bool(True)
#  process.simpleEleId60cIso.dataMagneticFieldSetUp = cms.bool(True)
#
process.simpleEleId95relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId90relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId85relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId80relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId70relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId60relIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId95cIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId90cIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId85cIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId80cIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId70cIso.dataMagneticFieldSetUp = cms.bool(False)
process.simpleEleId60cIso.dataMagneticFieldSetUp = cms.bool(False)
#

process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
process.makePatElectrons = cms.Sequence(process.patElectronIDs*process.patElectrons)
# process.makePatMuons may be needed depending on how you calculate the MET
process.makePatCandidates = cms.Sequence(process.makePatElectrons+process.makePatMETs)
process.patDefaultSequence = cms.Sequence(process.makePatCandidates)




################################################################################################
################################################################################################
###  Setting up filters: VBTF Wenu (loose,tight) and ECAL or HF SC-counting with selectors  ###
################################################################################################


## WARNING: you may want to modify this item:
HLT_process_name = "HLT"   # 
# trigger path selection


# this path was introduced at run 140058
HLT_path_name     = "HLT_Ele15_SW_L1R"
# trigger filter name
HLT_filter_name  =  "hltL1NonIsoHLTNonIsoSingleElectronEt15PixelMatchFilter"

# keep this for runs <140058 when HLT_Ele15_SW_L1R was not present. HLT_Ele15_LW_L1R was prescaled starting from run 141956
HLT_path_name_extra0   = "HLT_Ele15_LW_L1R"
HLT_filter_name_extra0 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronLWEt15PixelMatchFilter","",HLT_process_name)

HLT_path_name_extra1   = "HLT_Ele15_SiStrip_L1R"
HLT_filter_name_extra1 = cms.untracked.InputTag("hltL1NonIsoHLTNonIsoSingleElectronSiStripEt15PixelMatchFilter","",HLT_process_name)


process.z1LegFilter =cms.EDFilter('WenuCandidateFilter',
                                  ### the input collections needed:
                                  electronCollectionTag = cms.untracked.InputTag("patElectrons","","skim-and-Zshape-analysis"),
                                  metCollectionTag = cms.untracked.InputTag(myMetCollection,"","skim-and-Zshape-analysis"),
                                  pfMetCollectionTag = cms.untracked.InputTag(myPfMetCollection,"","skim-and-Zshape-analysis"),
                                  tcMetCollectionTag = cms.untracked.InputTag(myTcMetCollection,"","skim-and-Zshape-analysis"),
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
                                  useTriggerInfo = cms.untracked.bool(False), # GF >>>>>>>>>>>> changed here on Tue Aug  3 19:16:55 CEST 2010
                                  electronMatched2HLT = cms.untracked.bool(False), # GF changed Sun Aug  8 20:52:24 CEST 2010
                                  electronMatched2HLT_DR = cms.untracked.double(0.2), # GF 
                                  useHLTObjectETCut = cms.untracked.bool(False), # GF 
                                  hltObjectETCut = cms.untracked.double(15.),
                                  useExtraTrigger = cms.untracked.bool(False), # GF  >>>>>>>>>> Wed Aug  4 11:52:45 CDT 2010
                                  vHltpathExtra = cms.untracked.vstring(HLT_path_name_extra0,HLT_path_name_extra1),
                                  vHltpathFilterExtra = cms.untracked.VInputTag(HLT_filter_name_extra0, HLT_filter_name_extra1),
                                  # ET Cut in the SC
                                  ETCut = cms.untracked.double(18.), # GF : changed here Wed Aug  4 11:52:45 CDT 2010
                                  METCut = cms.untracked.double(0.),
                                  # reject events with a 2nd electron with ET > 20 that passes the WP95%
                                  vetoSecondElectronEvents = cms.untracked.bool(False),
                                  storeSecondElectron = cms.untracked.bool(False),
                                  ETCut2ndEle = cms.untracked.double(25.),
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
                                  #  difference between data and MC JM
                                  # dataMagneticFieldSetUp = cms.untracked.bool(True), # we are dealing with DATA
                                  dataMagneticFieldSetUp = cms.untracked.bool(False), # we are dealing with MC
                                  dcsTag = cms.untracked.InputTag("scalersRawToDigi"),
                                  )


##
##  ################################################################################
##
##  the filter to select the candidates from the data samples: one TIGHT electron
##
##
HLT_path_name_tight   = "HLT_Ele25_SW_L1R"
HLT_filter_name_tight = "hltL1NonIsoHLTNonIsoSingleElectronEt25PixelMatchFilter"

process.z1TightLegFilter =cms.EDFilter('WenuCandidateFilter',
                                       ### the input collections needed:
                                       electronCollectionTag = cms.untracked.InputTag("patElectrons","","skim-and-Zshape-analysis"),
                                       metCollectionTag = cms.untracked.InputTag(myMetCollection,"","skim-and-Zshape-analysis"),
                                       pfMetCollectionTag = cms.untracked.InputTag(myPfMetCollection,"","skim-and-Zshape-analysis"),
                                       tcMetCollectionTag = cms.untracked.InputTag(myTcMetCollection,"","skim-and-Zshape-analysis"),
                                       triggerCollectionTag = cms.untracked.InputTag("TriggerResults","",HLT_process_name),
                                       triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLT_process_name),
                                       hltpath = cms.untracked.string(HLT_path_name_tight),
                                       hltpathFilter = cms.untracked.InputTag(HLT_filter_name_tight,"",HLT_process_name),
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
                                       useTriggerInfo = cms.untracked.bool(False), # GF >>>>>>>>>>>> changed here on Tue Aug  3 19:16:55 CEST 2010
                                       electronMatched2HLT = cms.untracked.bool(False), # GF changed Sun Aug  8 20:52:24 CEST 2010
                                       electronMatched2HLT_DR = cms.untracked.double(0.2), # GF 
                                       useHLTObjectETCut = cms.untracked.bool(False), # GF 
                                       hltObjectETCut = cms.untracked.double(15.),
                                       useExtraTrigger = cms.untracked.bool(False), # GF  >>>>>>>>>> Wed Aug  4 11:52:45 CDT 2010
                                       vHltpathExtra = cms.untracked.vstring(HLT_path_name_extra0,HLT_path_name_extra1),
                                       vHltpathFilterExtra = cms.untracked.VInputTag(HLT_filter_name_extra0, HLT_filter_name_extra1),
                                       # ET Cut in the SC
                                       ETCut = cms.untracked.double(30.),
                                       METCut = cms.untracked.double(30.),
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
                                       # difference between data and MC JM
                                       # dataMagneticFieldSetUp = cms.untracked.bool(True), # we are dealing with DATA
                                       dataMagneticFieldSetUp = cms.untracked.bool(False), # we are dealing with MC
                                       dcsTag = cms.untracked.InputTag("scalersRawToDigi"),
                                       )


####################################################################################
# turn superclusters into candidates and require that there's a second "Z loose leg", in HF or in ECAL"


# turn superclusters into candidates
process.hybridCandidateSuperClusters = cms.EDProducer("ConcreteEcalCandidateProducer",
                                                      src = cms.InputTag("correctedHybridSuperClusters"),
                                                      particleType = cms.string("gamma")
                                                      )
process.multi5x5CandidateSuperClusters = cms.EDProducer("ConcreteEcalCandidateProducer",
                                                        src = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                                                        particleType = cms.string("gamma")
                                                        )
# select separately EB and EE candidates
process.ebSC = cms.EDFilter("CandViewSelector",
                            src = cms.InputTag("hybridCandidateSuperClusters"),
                            cut = cms.string('abs( eta ) < 1.4442')
                            )
process.eeSC = cms.EDFilter("CandViewSelector",
                            src = cms.InputTag("multi5x5CandidateSuperClusters"),
                            cut = cms.string('abs( eta ) > 1.560 & abs( eta ) < 3')
                            )
# join them in ECAL calidates (no-duplication guaranteed)
process.ecalSC = cms.EDProducer("CandViewMerger",
                              src = cms.VInputTag(cms.InputTag("ebSC"), cms.InputTag("eeSC"))
                              )                                                  
# select ECAL sucperclusters above a certain Et
process.ecalCut = cms.EDFilter("EtaPtMinCandViewSelector",
                               src = cms.InputTag("ecalSC"),
                               etaMin = cms.double(-3),
                               etaMax = cms.double(3),
                               ptMin = cms.double(13.0)
                               )
# this is the FILTER which requires at least N=2 ecal SC above a certain Et 
process.ecalSel = cms.EDFilter("CandViewCountFilter",
                               src = cms.InputTag("ecalCut"),
                               minNumber = cms.uint32(2)
                               )



# turn HF superclusters into candidates
process.hfCandidateSuperClusters = cms.EDProducer("ConcreteEcalCandidateProducer",
                                                  src = cms.InputTag("hfEMClusters"),
                                                  particleType = cms.string("gamma")
                                                  )
process.hfSC = cms.EDFilter("CandViewSelector",
                            src = cms.InputTag("hfCandidateSuperClusters"),
                            cut = cms.string('abs( eta ) > 3 & abs( eta ) < 5')
                            )
# select HF sucperclusters above a certain Et
process.hfCut = cms.EDFilter("EtaPtMinCandViewSelector",
                             src = cms.InputTag("hfSC"),
                             etaMin = cms.double(-5),
                             etaMax = cms.double(5),
                             ptMin = cms.double(10.0)
                             )
# this is the FILTER which requires at least N=1 HF SC above a certain Et 
process.hfSel = cms.EDFilter("CandViewCountFilter",
                               src = cms.InputTag("hfCut"),
                               minNumber = cms.uint32(1)
                               )




################################################################################################
################################################################################################
###  Setting up RECO and analyzers: ECAL-HF Z's and metEle; one instance per  ele selection
################################################################################################

process.load("RecoEgamma.EgammaHFProducers.hfEMClusteringSequence_cff")
## feed the re-calibrated HF rechits into a new clustering
# 0 = no corrections applied; 1=corrections applie
process.hfEMClusters.correctionType=0


# get HF cluster reco going
process.load("RecoEgamma.EgammaHFProducers.hfRecoEcalCandidate_cfi")
#process.hfRecoEcalCandidate.intercept2DCut=-100 # this is to avoid COMPLETELY the usage of the esel 
#process.hfRecoEcalCandidate.intercept2DCut=0.10 # this is to avoid NEARLY completely the usage of the esel 
process.hfRecoEcalCandidate.intercept2DCut=0.3   # standard setting (for this analysis)
process.hfRecoEcalCandidate.e9e25Cut      =0.94
# 0.94 is the same as default in the HF cluster producer

process.TFileService = cms.Service("TFileService",
       fileName = cms.string("TFskimAndAnalysisFromRECO_MC_Zoneleg.root"),
)


# to access values of EldId cuts
import ElectroWeakAnalysis.WENu.simpleCutBasedElectronIDSpring10_cfi

#from PhysicsTools.NtupleUtils.HLTrigResultsDumper_cfi import *
#process.TriggerResults = HLTrigResultsDumper.clone()

from ZShape.HFZeeVBTF.hfzeevbtf_cfi import *

process.IdIsoRej                     = demo.clone()
process.IdIsoRej.myName              = cms.string('HFZeeVBTF-IdIsoRej')
process.IdIsoRej.acceptedElectronIDs = cms.vint32( 7 )
process.IdIsoRej.DoLog               = cms.bool(True)

# EWK analyzer: different Z definitions with one ECAL electron and one HF electron
# ---> this is the instance to run AFTER the Wenu EWK filter
process.IdIso                     = demo.clone()
process.IdIso.myName              = cms.string('HFZeeVBTF-IdIso')
process.IdIso.acceptedElectronIDs = cms.vint32( 3, 7 )


process.IdRej                     = demo.clone()
process.IdRej.myName              = cms.string('HFZeeVBTF-IdRej')
process.IdRej.acceptedElectronIDs = cms.vint32( 5, 7 )


process.IsoRej                     = demo.clone()
process.IsoRej.myName              = cms.string('HFZeeVBTF-IsoRej')
process.IsoRej.acceptedElectronIDs = cms.vint32( 6, 7 )


process.Id                     = demo.clone()
process.Id.myName              = cms.string('HFZeeVBTF-Id')
process.Id.acceptedElectronIDs = cms.vint32( 1, 3, 5, 7 )


process.Iso                     = demo.clone()
process.Iso.myName              = cms.string('HFZeeVBTF-Iso')
process.Iso.acceptedElectronIDs = cms.vint32( 2, 3, 6, 7 )


process.Rej                     = demo.clone()
process.Rej.myName              = cms.string('HFZeeVBTF-Rej')
process.Rej.acceptedElectronIDs = cms.vint32( 4, 5, 6, 7 )


from RecoEgamma.EgammaHFProducers.hfRecoEcalCandidate_cfi import *
process.hfRecoEcalCandidateLoose            = hfRecoEcalCandidate.clone()
process.hfRecoEcalCandidateLoose.hfclusters = cms.InputTag("hfEMClusters")
process.hfRecoEcalCandidateLoose.intercept2DCut=-100# this is to avoid JUST completely the usage of the esel
process.hfRecoEcalCandidateLoose.e9e25Cut      =0.94

process.IdIsoRejHFIsoOnly                     = demo.clone()
process.IdIsoRejHFIsoOnly.myName              = cms.string('HFZeeVBTF-IdIsoRejHFIsonly')
process.IdIsoRejHFIsoOnly.acceptedElectronIDs = cms.vint32( 7 )
# the following params are, respectively: e9e25_loose, e9e25_tight,  var2d_loose, var2d_tight,  eCOREe9_loose, eCOREe9_tight,  eSeL_loose, eSeL_tight;
process.IdIsoRejHFIsoOnly.hFselParams         = cms.vdouble(0.90, 0.94,      -9999, -9999,    0.7, 0.85,     9999, 9999)
process.IdIsoRejHFIsoOnly.DoLog               = cms.bool(True)
process.IdIsoRejHFIsoOnly.hFElectrons         = cms.InputTag("hfRecoEcalCandidateLoose","","skim-and-Zshape-analysis")


#  this module is run at the beginning of the job sequence just to count the number of events
#  the analysis has been running on
process.demoBefCuts                     = demo.clone()
process.demoBefCuts.myName              = cms.string('demoBefCuts')
process.demoBefCuts.acceptedElectronIDs = cms.vint32( 7 )
process.demoBefCuts.DoLog               = cms.bool(False)


from ZShape.HFZeeVBTF.elewithmet_cfi import *
#myDesiredMetCollection = "caloMET"
myDesiredMetCollection = "pfMET"
#myDesiredMetCollection = "tcMET"

process.metEleIdIsoRej = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleIdIsoRej'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleIdIso = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 3, 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleIdIso'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleIdRej = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 5, 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleIdRej'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleIsoRej = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 6, 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleIsoRej'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleId = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 1, 3, 5 ,7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleId'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleIso = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 2, 3, 6, 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleIso'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )


process.metEleRej = cms.EDAnalyzer('EleWithMet',
                                 # source
                                 acceptedElectronIDs = cms.vint32( 4, 5, 6, 7 ),
                                 ECALid = cms.string('simpleEleId90relIso'),
                                 myName = cms.string('metEleRej'),
                                 DoLog = cms.bool(True),
                                 ETCut = cms.double(20.),
                                 METCut = cms.double(25.),
                                 metCollectionTag = cms.InputTag(myDesiredMetCollection,"","skim-and-Zshape-analysis"),
                                 )



################################################################################################
################################################################################################
###  Now make an end Path with OR of 3 filters folloewed by  all analyzers
################################################################################################


####################################################################################
process.z2EcalLegsPath = cms.Path(process.patDefaultSequence
                                  * process.hybridCandidateSuperClusters
                                  * process.multi5x5CandidateSuperClusters
                                  * process.ebSC
                                  * process.eeSC
                                  * process.ecalSC
                                  * process.ecalCut
                                  * process.ecalSel      # this requires 2 ECAL SC > 13 GeV
                                  * process.z1LegFilter  # this requires one electron > 15 with HLT matching
                                  # * process.dumpEv
                                  )

####################################################################################
process.z1Ecal1HfLegPath = cms.Path(process.patDefaultSequence
                                    * process.hfCandidateSuperClusters
                                    * process.hfSC
                                    * process.hfCut
                                    * process.hfSel        # this requires 1 HF SC > 10 GeV
                                    * process.z1LegFilter  # this requires one electron > 15 with HLT matching
                                    #  * process.dumpEv
                                    )

####################################################################################
process.z1EcalLegTightPath = cms.Path(process.patDefaultSequence
                                   * process.z1TightLegFilter  # this requires one electron > 25 with HLT matching
                                   #  * process.dumpEv
                                   )

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.orOfTheeSkimPaths = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
#     TriggerResultsTag = cms.InputTag("TriggerResults","","Zshape-skim-analysis"),
    TriggerResultsTag = cms.InputTag("TriggerResults","","skim-and-Zshape-analysis"),
    HLTPaths = cms.vstring("z2EcalLegsPath","z1Ecal1HfLegPath","z1EcalLegTightPath"),                # provide list of HLT paths (or patterns) you want
        eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
        andOr = cms.bool(True),              # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
        throw = cms.bool(True) 
  )

process.analyzers = cms.EndPath(
      process.demoBefCuts # this one is just to count events (needed in MC!)
     *process.orOfTheeSkimPaths 
     *process.hfEMClusteringSequence
     *process.hfRecoEcalCandidate
     *process.hfRecoEcalCandidateLoose
     *process.IdIso
     *process.IdRej
     *process.IsoRej
     *process.Id
     *process.Iso
     *process.Rej
     *process.IdIsoRej
     *process.IdIsoRejHFIsoOnly
     *process.metEleIdIsoRej
     *process.metEleIdIso
     *process.metEleIdRej
     *process.metEleIsoRej
     *process.metEleId
     *process.metEleIso
     *process.metEleRej
   # *process.dumpEv
     )

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
