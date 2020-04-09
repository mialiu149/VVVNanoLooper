#include "Begin_4LepMET.h"

void Begin_4LepMET()
{
    //==============================================
    // Begin_4LepMET:
    // This function gets called prior to the event looping.
    // This is where one declares variables, histograms, event selections for the category 4LepMET.
    //==============================================

    // Create variables used in this category.
    // Please follow the convention of <category>_<varname> structure.
    // N.B. PLEASE USE float TYPE FOR EVERYTHING, UNLESS IT IS LORENTZVECTOR (which is also done in float).
    ana.tx.createBranch<float>("4LepMET_intVar1");
    ana.tx.createBranch<float>("4LepMET_floatVar1");
    ana.tx.createBranch<LorentzVector>("4LepMET_LVVar1");

    // Define selections
    // VVVCommonCut will contain selections that should be common to all categories, starting from this cut, add cuts for this category of the analysis.
    ana.cutflow.getCut("VVVCommonCut");
    ana.cutflow.addCutToLastActiveCut("4LepMET_Preselection", [&]() { return ana.tx.getBranch<LorentzVector>("4LepMET_LVVar1").pt() > 25.;}, [&]() { return ana.tx.getBranch<float>("4LepMET_floatVar1"); } );

    // Create histograms used in this category.
    // Please follow the convention of h_<category>_<varname> structure.
    // N.B. Using nbins of size 180 or 360 can provide flexibility as it can be rebinned easily, as 180, 360 are highly composite numbers.
    ana.histograms.addHistogram("h_4LepMET_intVar1", 10, 0, 10, [&]() { return ana.tx.getBranch<float>("4LepMET_intVar1"); } );
    ana.histograms.addHistogram("h_4LepMET_floatVar1", 180, 0, 500, [&]() { return ana.tx.getBranch<float>("4LepMET_floatVar1"); } );
    ana.histograms.addHistogram("h_4LepMET_LVVar1_Pt", 180, 0, 150, [&]() { return ana.tx.getBranch<LorentzVector>("4LepMET_LVVar1").pt(); } );

    // Now book cutflow histogram (could be commented out if user does not want.)
    // N.B. Cutflow histogramming can be CPU consuming.
    ana.cutflow.bookCutflows();

    // Book histograms to cuts that user wants for this category.
    ana.cutflow.bookHistogramsForCut(ana.histograms, "4LepMET_Preselection");
}