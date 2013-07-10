#include "ZShape/Base/interface/EffTableLoader.h"
#include "ZShape/Base/interface/EffTableReader.h"
#include <vector>
#include "FWCore/Utilities/interface/Exception.h"
#include "Math/PtEtaPhiE4D.h"
#include "Math/LorentzVector.h"

namespace {
  const unsigned nParameters = 6;
}

EffTableLoader::EffTableLoader () 
  : mParameters (0) 
{}

EffTableLoader::EffTableLoader (const std::string& fDataFile) 
  : mParameters (new EffTableReader (fDataFile)) 
{}

EffTableLoader::~EffTableLoader () {
  delete mParameters;
}

int EffTableLoader::GetBandIndex(float fEt, float fEta, float fPU)const {
  int index=mParameters->bandIndex(fEt, fEta,fPU);
  return index;
}


std::vector<float> EffTableLoader::correctionEff (float fEt,float fEta, float fPU) const {
  int index=mParameters->bandIndex(fEt, fEta,fPU);
  EffTableReader::Record rec=mParameters->record(index);
  std::vector<float> param=rec.parameters();
  return param;
}
std::vector<float> EffTableLoader::correctionEff (int index) const {
  EffTableReader::Record rec=mParameters->record(index);
  std::vector<float> param=rec.parameters();
  return param;
}


std::vector<std::pair<float, float> > EffTableLoader::GetCellInfo(float fEt, float fEta, float fPU)const {
  int index=mParameters->bandIndex(fEt, fEta,fPU);
  return (this->GetCellInfo(index)) ;
}
std::vector<std::pair<float, float> > EffTableLoader::GetCellInfo(int index)const {
  EffTableReader::Record rec=mParameters->record(index);
  std::pair<float, float> PtBin;
  PtBin.first = rec.EtMin();
  PtBin.second= rec.EtMax();
   
  std::pair<float, float> EtaBin;
  EtaBin.first = rec.etaMin();
  EtaBin.second= rec.etaMax();
  std::pair<float, float> PUbin;
  PUbin.first=rec.PUmin();
  PUbin.second=rec.PUmax();
  std::vector<std::pair<float, float> > BinInfo;
  BinInfo.push_back(PtBin);
  BinInfo.push_back(EtaBin);
  BinInfo.push_back(PUbin);
  return BinInfo ;
}

std::pair<float, float> EffTableLoader::GetCellCenter(float fEt, float fEta, float fPU )const {
  int index=mParameters->bandIndex(fEt, fEta,fPU);
  return (this->GetCellCenter(index)); 
}
std::pair<float, float> EffTableLoader::GetCellCenter(int index )const {
  EffTableReader::Record rec=mParameters->record(index);
  std::pair<float, float> BinCenter;
  BinCenter.first = rec.EtMiddle();
  BinCenter.second= rec.etaMiddle();
  return BinCenter ;
}


int EffTableLoader::size(void) {
  return mParameters->size();
}
