#include "StPicoAnalyzer.h"

#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"

#include "StMessMgr.h"

#include "TFile.h"
#include "TH1F.h"

ClassImp(StPicoAnalyzer)

//_____________________________________________________________________________
StPicoAnalyzer::StPicoAnalyzer(const char* name, StPicoDstMaker* picoMaker, const char* outputFileName)
: StMaker(name), mPicoDstMaker(picoMaker), mEventCounter(0), mOutputFileName(outputFileName), mOutputFile(0), mTestHist(0)
{
}

//_____________________________________________________________________________
StPicoAnalyzer::~StPicoAnalyzer()
{
}

//_____________________________________________________________________________
Int_t StPicoAnalyzer::Init()
{
  LOG_INFO << "StPicoAnalyzer::Init() - starting up, output -> " << mOutputFileName.Data() << endm;
  mEventCounter = 0;
  
  mOutputFile = new TFile(mOutputFileName.Data(), "RECREATE");
  if (!mOutputFile || mOutputFile->IsZombie()) {
    LOG_ERROR << "StPicoAnalyzer::Init() - could not open output file "
	      << mOutputFileName.Data() << endm;
    return kStErr;
  }
  mTestHist = new TH1F("h","test histogram",10,0,10);
  return kStOK;
}

//_____________________________________________________________________________
Int_t StPicoAnalyzer::Make()
{
  if (!mPicoDstMaker) {
    LOG_ERROR << "StPicoAnalyzer::Make() - no StPicoDstMaker!" << endm;
    return kStErr;
  }

  StPicoDst* picoDst = mPicoDstMaker->picoDst();
  if (!picoDst) {
    LOG_ERROR << "StPicoAnalyzer::Make() - no PicoDst!" << endm;
    return kStErr;
  }

  StPicoEvent* picoEvent = picoDst->event();
  if (!picoEvent) {
    LOG_ERROR << "StPicoAnalyzer::Make() - no PicoEvent!" << endm;
    return kStErr;
  }

  ++mEventCounter;

  // This is the "do nothing but print" placeholder. Replace this block with
  // real analysis: loop over picoDst->numberOfTracks(), apply cuts, fill
  // histograms/trees, etc.
  LOG_INFO << "StPicoAnalyzer::Make() - event# " << mEventCounter
            << " | run " << picoEvent->runId()
            << " | eventID " << picoEvent->eventId()
            << " | refMult " << picoEvent->refMult()
            << " | nTracks " << picoDst->numberOfTracks()
            << endm;

  mTestHist->Fill(5);
  
  return kStOK;
}

//_____________________________________________________________________________
void StPicoAnalyzer::Clear(Option_t* opt)
{
  StMaker::Clear(opt);
}

//_____________________________________________________________________________
Int_t StPicoAnalyzer::Finish()
{
  LOG_INFO << "StPicoAnalyzer::Finish() - processed " << mEventCounter
            << " events total" << endm;

  if (mOutputFile) {
    mOutputFile->Write();
    mOutputFile->Close();
    delete mOutputFile;
    mOutputFile = 0;
  }
  return kStOK;
}
