# produces cones around electrons type 1
# reconstructing electrons and provides smearing

import FWCore.ParameterSet.Config as cms

SmearedElectronsProducer = cms.EDProducer("ZSmearingProducer",
    zsrc = cms.untracked.InputTag("ZIntoElectronsEventProducer","ZEventParticles"),
    doSmearing = cms.untracked.bool(True),
    quiet = cms.untracked.bool(True),
    zElectronsCone = cms.double(0.08),
    randomSeed = cms.int32(134),
    SmearTable = cms.FileInPath('ZShape/EffAcc/data/CBBinsFile.txt'),
    HF = cms.PSet(
       stocastic = cms.double(2.08),
       constantp = cms.double(0.110),
       constantm = cms.double(0.100),
       constantp2 = cms.double(0.110),
       constantm2 = cms.double(0.100),
       fraction2 = cms.double(0.00),
       meanp = cms.double(1.046),
       meanm = cms.double(1.046),
       reseta = cms.double(0.045),
       resphi = cms.double(0.045)
       #tuned J. Mans 02-26-11
    ),
    EB = cms.PSet(
       #tuned by j. Mans on 06-08-09
       p0 = cms.double(0.0407878) , 
       p1 = cms.double(1.06),
       p2 = cms.double(4.78),
       c = cms.double(0.0160),   #due to constant term being summed in quadrature (was linearly summed)
       alpha = cms.double(1.504), 
       mean = cms.double(1.00082),  #
       n = cms.double(2.0) 	   
    ),
     EE = cms.PSet(
       p0 = cms.double(0.053),      # keep this fixed to value from CMS DN-2009/002
       p1 = cms.double(0.72),
       p2 = cms.double(0.15),       #0.15
       c  = cms.double(0.0439715),  
       alpha = cms.double(1.8018),
       mean = cms.double(0.979563),
       n = cms.double(2.0) 	
    )
)
