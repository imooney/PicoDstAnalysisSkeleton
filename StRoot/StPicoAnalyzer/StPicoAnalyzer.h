#ifndef StPicoAnalyzer_h
#define StPicoAnalyzer_h

// -----------------------------------------------------------------------------
// StPicoAnalyzer
//
// Minimal skeleton StMaker for a STAR PicoDst analysis. It does nothing but
// print a line per event for now -- this is meant to be the starting point
// you build real analysis code into (track loops, cuts, histograms, trees...).
// -----------------------------------------------------------------------------

#include "StMaker.h"
#include "TString.h"

class StPicoDstMaker;
class StPicoDst;
class StPicoEvent;
class TFile;
class TH1F;

class StPicoAnalyzer : public StMaker {
 public:
  StPicoAnalyzer(const char* name, StPicoDstMaker* picoMaker, const char* outputFileName = "output.root");
  virtual ~StPicoAnalyzer();

  virtual Int_t Init();
  virtual Int_t Make();
  virtual void  Clear(Option_t* opt = "");
  virtual Int_t Finish();

 private:
  StPicoDstMaker* mPicoDstMaker;  //! not owned, just a pointer we read from
  Long64_t mEventCounter;         //! events processed so far
  TString mOutputFileName;        //! e.g. "output.root" or "$JOBID.root"
  TFile* mOutputFile;             //! opened in Init(), written+closed in Finish()
  TH1F* mTestHist;                //! test histogram -- replace with real histograms later
  
  ClassDef(StPicoAnalyzer, 1)
};

#endif
