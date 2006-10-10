#include "DataFormats/SiStripDetId/test/stubs/SiStripAnalyzeKeys.h"
//
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
//
#include "DataFormats/SiStripCommon/interface/SiStripConstants.h"
#include "DataFormats/SiStripDetId/interface/SiStripFecKey.h"
#include "DataFormats/SiStripDetId/interface/SiStripFedKey.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetKey.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "DataFormats/SiStripDetId/interface/TIDDetId.h"
#include "DataFormats/SiStripDetId/interface/TIBDetId.h"
#include "DataFormats/SiStripDetId/interface/TOBDetId.h"
#include "DataFormats/SiStripDetId/interface/TECDetId.h"
//
#include "CondFormats/DataRecord/interface/SiStripFedCablingRcd.h"
#include "CondFormats/SiStripObjects/interface/SiStripFedCabling.h"
//
#include <iostream>
#include <sstream>

using namespace std;

// -----------------------------------------------------------------------------
// 
void SiStripAnalyzeKeys::beginJob( const edm::EventSetup& setup ) {
  edm::LogVerbatim(/* sistrip::mlCabling_ */ "") << __PRETTY_FUNCTION__;
  
  // Retrieve FED cabling
  edm::ESHandle<SiStripFedCabling> fed_cabling;
  setup.get<SiStripFedCablingRcd>().get( fed_cabling ); 
  
  // Iterate through connections
  edm::LogVerbatim(/* sistrip::mlCabling_ */ "") << __PRETTY_FUNCTION__
						 << " Dumping all FED-FEC connections...";

  vector<uint16_t>::const_iterator ifed = fed_cabling->feds().begin();
  for ( ; ifed != fed_cabling->feds().end(); ifed++ ) {
    const vector<FedChannelConnection>& conns = fed_cabling->connections( *ifed ); 
    vector<FedChannelConnection>::const_iterator ichan = conns.begin();
    for ( ; ichan != conns.end(); ichan++ ) { 
      if ( ichan->fedId() ) {

	// FED-FEC connection description
	cout << *ichan << endl;

	// FED key
	uint32_t fed = SiStripFedKey::key( *ifed,
					   ichan->fedCh()/12, 
					   ichan->fedCh()%12 );
	SiStripFedKey::Path fed_path = SiStripFedKey::path(fed);
	cout << fed_path << endl;
	
	// FEC key
	uint32_t fec = SiStripFecKey::key( ichan->fecCrate(),
					   ichan->fecSlot(),
					   ichan->fecRing(),
					   ichan->ccuAddr(),
					   ichan->ccuChan(),
					   ichan->lldChannel() );
	SiStripFecKey::Path fec_path = SiStripFecKey::path(fec);
	cout << fec_path << endl;
	
	// DET key
	uint32_t det = SiStripDetKey::key( ichan->detId(),
					   ichan->apvPairNumber() );
	SiStripDetKey::Path det_path = SiStripDetKey::path(det);
	cout << det_path << endl;
	
	// Sub-det keys
	TIDDetId tid(det);
	TIBDetId tib(det);
	TOBDetId tob(det);
	TECDetId tec(det);
	cout << SiStripDetId(tid.rawId()) << endl
	     << SiStripDetId(tib.rawId()) << endl
	     << SiStripDetId(tob.rawId()) << endl
	     << SiStripDetId(tec.rawId()) << endl;
	
      }

    }  // channel loop
  } // fed loop
  
}
