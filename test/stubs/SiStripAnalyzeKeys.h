#ifndef DataFormats_SiStripDetId_test_SiStripAnalyzeKeys_H
#define DataFormats_SiStripDetId_test_SiStripAnalyzeKeys_H

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include <string>

/**
   @class SiStripAnalyzeKeys 
   @brief Simple class that analyzes FED, FEC and DET keys
*/
class SiStripAnalyzeKeys : public edm::EDAnalyzer {

 public:
  
  SiStripAnalyzeKeys( const edm::ParameterSet& ) {;}
  ~SiStripAnalyzeKeys() {;}
  
  void beginJob( edm::EventSetup const& );
  void analyze( const edm::Event&, const edm::EventSetup& ) {;}
  void endJob() {;}

};

#endif // DataFormats_SiStripDetId_test_SiStripAnalyzeKeys_H

