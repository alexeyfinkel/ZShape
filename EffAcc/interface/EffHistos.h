#ifndef EFFHS_INC
#define EFFHS_INC

#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Vector3D.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "ZShape/Base/interface/ZShapeElectron.h"
#include "ZShape/Base/interface/ZShapeEvent.h"


// holds histograms for Z and e+/- quantities
// filled to carachterize candidates' pupulation at every step along selection path

class EffHistos {

 public:
  void Book(TFileDirectory& tfd,bool massFinals=false);
  void Fill(const ZShapeElectron& e1, const  ZShapeElectron& e2, 
            const ::math::PtEtaPhiMLorentzVector& eTL1, const ::math::PtEtaPhiMLorentzVector& eTL2, double wgt=1.0, bool doMC=true); 
  void FillEvt(const ZShapeEvent& zevtm, double wgt=1.0, bool justPV=false);
  void WrapUp(void);

  void setupMassWindow(double low, double high) { massWindowLow_=low; massWindowHigh_=high; }
  EffHistos() { booked_=false; massWindowLow_=0; massWindowHigh_=1000;}
 private:
  double massWindowLow_,massWindowHigh_;

  TH1 *evt_nvert_, *evt_npu_;
  TH1 *mZ_,*mZ_zoom,*mz_hfn,*mz_hfp,*YZ_, *ptZ_,*ptZmon_,*polarizationZ_,*cosPolarizationZ_;
  TH1 *YZmasscut_,*ptZmasscut_;
  TH1 *YZmasscutTL_,*ptZmasscutTL_;
  TH1 *YZTLmasscut_,*ptZTLmasscut_;
  TH1 *YZTL_,*ptZTLmon_,*mZTL_,*ptZTL_,*atZ_,*alZ_ ,*MCatZ_,*MCalZ_, *phiStar_, *MCphiStar_, *dphi_, *deta_, *phistarRes, *atRes, *ptRes, *phistarRes_scaled, *atRes_scaled, *ptRes_scaled, *phistarRes_plain, *atRes_plain, *ptRes_plain;
  bool booked_;
  TH1 *e1eta_,*e2eta_,*e1phi_,*e2phi_,*e1pt_,*e2pt_,*eeta_,*ephi_,*hfeta_, *e1charge_, *e2charge_;
  TH2 *mZ_Y_,*mZ_pt_,*pt_Y_,*e1eta_YZ_,*e2eta_YZ_,*e1eta_ptZ_,*e2eta_ptZ_,*e1eta_e2eta_,*YZTL_YZ_,*YZTL_YZ_matrix_,*atTL_at_,*atTL_at_matrix_,*phiStarTL_phiStar_,*phiStarTL_phiStar_matrix_, *ptTL_phiStar_, *ptTL_at_;
  TH2 *e1pt_e2pt_; 
  TH1 *evt_PVz_, *evt_BSz_, *evt_MET_, *evt_PFMET_, *evt_TCMET_;
  TH2* ptZTL_ptZ_, *ptZTL_ptZ_zoom_;
  TH3* mZ_e2pt_e2eta_;
  TH2* YZ_v_mz_,*ptZ_v_mz_,*ptZmon_v_mz_,*atZ_v_mz_,*phiStar_v_mz_,*e1eta_v_mz_,*e2eta_v_mz_,*eeta_v_mz_,*e1phi_v_mz_,*e2phi_v_mz_,*ephi_v_mz_,*e1pt_v_mz_,*e2pt_v_mz_,* mZ_v_mz_;

  bool massFinals_;
  struct {
    TH2 *e1eta_,*e2eta_,*e1phi_,*e2phi_,*e1pt_,*e2pt_,*hfeta_;    
  } mZ_binned_finals;

}; 

#endif
