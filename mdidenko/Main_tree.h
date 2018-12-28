//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Jun  2 19:40:29 2018 by ROOT version 6.12/06
// from TTree ChipConstants/data
// found on file: workroot/const2.root
//////////////////////////////////////////////////////////

#ifndef VMMTree2_h
#define VMMTree2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class VMMTree2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
    
//    For output in PDF
    
TCanvas* gCnv; // Canvas
TCanvas* gCnvART;
TCanvas* cnv_out;
char pdfname[256], pdfopen[256], pdfclose[256];
char Bline[256], Blineopen[256], Blineclose[256];
char ART[256], ARTopen[256], ARTclose[256];

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   
    TDatime *tDatime_Var;

    Int_t           boardId;
    Int_t           VMMId;
    Int_t           countCh;
    Float_t           bLinePauseNeg;
    Float_t           bLinePausePos;
    
    Int_t           chipStatus;
    Int_t           chipStatusNEG;
    Int_t           chipStatusPOS;
    
    Char_t          testMode[30];
    Char_t          userID[30];
    Char_t          FAILED[30];
    Char_t          partID[30];
   
   Float_t         bLine[64];
   Float_t         bLine_RMS[64];
    
    UInt_t         dateTime;
    
    Float_t         bLinePos[64];
    Float_t         bLine_RMSPos[64];
    
    vector<int>  *neg_DEAD_CHANNELS;
    vector<int>  *pos_DEAD_CHANNELS;
    
   
    
    Int_t         PDOEntriesMEAN_L0[64];
    Int_t         TDOEntriesMEAN_L0[64];
    Int_t         PDOEntriesMEAN_L0POS[64];
    Int_t         TDOEntriesMEAN_L0POS[64];
    Int_t         EntriesARTneg[64];
    Int_t         EntriesART[64];
    Int_t         EntriesARTpos[64];
   
    Int_t           countNonEff_Cont;
   vector<int>     *numberNonEff_Cont;
   Int_t           countDeadCh_Cont;
   vector<int>     *numberDeadCh_Cont;
   Float_t         PDORMS_Cont[64];
   Float_t         PDOIntercept_Cont[64];
   Float_t         PDOSlope_Cont[64];
   Float_t         TDOIntercept_Cont[64];
   Float_t         TDOSlope_Cont[64];
   Float_t         TDORMS_Cont[64];
   Float_t         tempMax_Cont;
   Float_t         VDD_V_Max_Cont;
   Float_t         VDD_A_Max_Cont;
   Float_t         VDDD_V_Max_Cont;
   Float_t         VDDD_A_Max_Cont;
   Float_t         VDDP_V_Max_Cont;
   Float_t         VDDP_A_Max_Cont;
   Float_t         VDAD_V_Max_Cont;
   Float_t         VDAD_A_Max_Cont;
   
    Int_t           countNonEff_L0;
   vector<int>     *numberNonEff_L0;
   Int_t           countDeadCh_L0;
   Int_t           countDeadCh_L0POS;
   vector<int>     *numberDeadCh_L0;
   vector<int>     *numberDeadCh_L0POS;
   Float_t         PDORMS_L0[64];   //[countCh]
   Float_t         PDORMS_L0POS[64];   //[countCh]
   Float_t         TDORMS_L0[64];
   Float_t         TDORMS_L0POS[64];
   Float_t         PDOIntercept_L0[64];   //[countCh]
   Float_t         PDOSlope_L0[64];   //[countCh]
   Float_t         PDOIntercept_L0POS[64];   //[countCh]
   Float_t         PDOSlope_L0POS[64];   //[countCh]
   Float_t         TDOIntercept_L0[64];   //[countCh]
   Float_t         TDOSlope_L0[64];   //[countCh]
    Float_t         TDOIntercept_L0POS[64];   //[countCh]
    Float_t         TDOSlope_L0POS[64];   //[countCh]
   Float_t         tempMax_L0;
    Float_t         tempMax_L0POS;
   Float_t         VDD_V_Max_L0;
   Float_t         VDD_A_Max_L0;
   Float_t         VDDD_V_Max_L0;
   Float_t         VDDD_A_Max_L0;
   Float_t         VDDP_V_Max_L0;
   Float_t         VDDP_A_Max_L0;
   Float_t         VDAD_V_Max_L0;
   Float_t         VDAD_A_Max_L0;
    
     Float_t        PDOMEAN_L0[64];
     Float_t        TDOMEAN_L0[64];
     Float_t        PDOMEAN_L0POS[64];
     Float_t        TDOMEAN_L0POS[64];
    
    Float_t        MEAN_DDO[64];
    Float_t        MEAN_DDOneg[64];
    Float_t        MEAN_DDOpos[64];
    
    Float_t         VDD_V_Max_L0POS;
    Float_t         VDD_A_Max_L0POS;
    Float_t         VDDD_V_Max_L0POS;
    Float_t         VDDD_A_Max_L0POS;
    Float_t         VDDP_V_Max_L0POS;
    Float_t         VDDP_A_Max_L0POS;
    Float_t         VDAD_V_Max_L0POS;
    Float_t         VDAD_A_Max_L0POS;
    
   Int_t           countNonEff_DDO;
   vector<int>     *numberNonEff_DDO;
   Int_t           countDeadCh_DDO;
   vector<int>     *numberDeadCh_DDO;
   Float_t         RMS_DDO[64];   //[countCh]
   Float_t         Intercept_DDO[64];   //[countCh]
   Float_t         Slope_DDO[64];   //[countCh]
   Float_t         tempMax_DDO;
   Float_t         VDD_V_Max_DDO;
   Float_t         VDD_A_Max_DDO;
   Float_t         VDDD_V_Max_DDO;
   Float_t         VDDD_A_Max_DDO;
   Float_t         VDDP_V_Max_DDO;
   Float_t         VDDP_A_Max_DDO;
   Float_t         VDAD_V_Max_DDO;
   Float_t         VDAD_A_Max_DDO;
    
    Int_t           countNonEff_DDOneg;
    vector<int>     *numberNonEff_DDOneg;
    Int_t           countDeadCh_DDOneg;
    vector<int>     *numberDeadCh_DDOneg;
    Float_t         RMS_DDOneg[64];   //[countCh]
    Float_t         Intercept_DDOneg[64];   //[countCh]
    Float_t         Slope_DDOneg[64];   //[countCh]
    Float_t         tempMax_DDOneg;
    Float_t         VDD_V_Max_DDOneg;
    Float_t         VDD_A_Max_DDOneg;
    Float_t         VDDD_V_Max_DDOneg;
    Float_t         VDDD_A_Max_DDOneg;
    Float_t         VDDP_V_Max_DDOneg;
    Float_t         VDDP_A_Max_DDOneg;
    Float_t         VDAD_V_Max_DDOneg;
    Float_t         VDAD_A_Max_DDOneg;
    
    Int_t           countNonEff_DDOpos;
    vector<int>     *numberNonEff_DDOpos;
    Int_t           countDeadCh_DDOpos;
    vector<int>     *numberDeadCh_DDOpos;
    Float_t         RMS_DDOpos[64];   //[countCh]
    Float_t         Intercept_DDOpos[64];   //[countCh]
    Float_t         Slope_DDOpos[64];   //[countCh]
    Float_t         tempMax_DDOpos;
    Float_t         VDD_V_Max_DDOpos;
    Float_t         VDD_A_Max_DDOpos;
    Float_t         VDDD_V_Max_DDOpos;
    Float_t         VDDD_A_Max_DDOpos;
    Float_t         VDDP_V_Max_DDOpos;
    Float_t         VDDP_A_Max_DDOpos;
    Float_t         VDAD_V_Max_DDOpos;
    Float_t         VDAD_A_Max_DDOpos;
    
   Int_t           countBadCh_ART;
   vector<int>    *numberBadCh_ART;
   Float_t         tempMax_ART;
   Float_t         VDD_V_Max_ART;
   Float_t         VDD_A_Max_ART;
   Float_t         VDDD_V_Max_ART;
   Float_t         VDDD_A_Max_ART;
   Float_t         VDDP_V_Max_ART;
   Float_t         VDDP_A_Max_ART;
   Float_t         VDAD_V_Max_ART;
   Float_t         VDAD_A_Max_ART;
    
    Int_t           countBadCh_ARTneg;
    vector<int>    *numberBadCh_ARTneg;
    Float_t         tempMax_ARTneg;
    Float_t         VDD_V_Max_ARTneg;
    Float_t         VDD_A_Max_ARTneg;
    Float_t         VDDD_V_Max_ARTneg;
    Float_t         VDDD_A_Max_ARTneg;
    Float_t         VDDP_V_Max_ARTneg;
    Float_t         VDDP_A_Max_ARTneg;
    Float_t         VDAD_V_Max_ARTneg;
    Float_t         VDAD_A_Max_ARTneg;
    
    Int_t           countBadCh_ARTpos;
    vector<int>    *numberBadCh_ARTpos;
    Float_t         tempMax_ARTpos;
    Float_t         VDD_V_Max_ARTpos;
    Float_t         VDD_A_Max_ARTpos;
    Float_t         VDDD_V_Max_ARTpos;
    Float_t         VDDD_A_Max_ARTpos;
    Float_t         VDDP_V_Max_ARTpos;
    Float_t         VDDP_A_Max_ARTpos;
    Float_t         VDAD_V_Max_ARTpos;
    Float_t         VDAD_A_Max_ARTpos;

   // List of branches
   TBranch        *b_boradId;   //!
   TBranch        *b_VMMId;   //!
   TBranch        *b_countCh;   //!
    TBranch        *b_bLinePauseNeg;
    TBranch        *b_bLinePausePos;
   TBranch        *b_partID;
    TBranch        *b_userID;
    TBranch        *b_testMode;
    TBranch        *b_FAILED;
    TBranch        *b_dateTime;
    TBranch        *b_chipStatus;
    TBranch        *b_chipStatusPOS;
    TBranch        *b_chipStatusNEG;
   TBranch        *b_bLine;   //!
   TBranch        *b_bLine_RMS;   //!
    TBranch        *b_bLinePos;   //!
    TBranch        *b_bLine_RMSPos;   //!
    
   TBranch        *b_countNonEff_Cont;   //!
   TBranch        *b_numberNonEff_Cont;   //!
   TBranch        *b_countDeadCh_Cont;   //!
   TBranch        *b_numberDeadCh_Cont;   //!
   TBranch        *b_PDORMS_Cont;   //!
   TBranch        *b_TDORMS_L0;
   TBranch        *b_TDORMS_L0POS;
   TBranch        *b_TDORMS_Cont;
   TBranch        *b_PDOIntercept_Cont;   //!
   TBranch        *b_PDOSlope_Cont;   //!
   TBranch        *b_TDOIntercept_Cont;   //!
   TBranch        *b_TDOSlope_Cont;   //!
   TBranch        *b_tempMax_Cont;   //!
   TBranch        *b_VDD_V_Max_Cont;   //!
   TBranch        *b_VDD_A_Max_Cont;   //!
   TBranch        *b_VDDD_V_Max_Cont;   //!
   TBranch        *b_VDDD_A_Max_Cont;   //!
   TBranch        *b_VDDP_V_Max_Cont;   //!
   TBranch        *b_VDDP_A_Max_Cont;   //!
   TBranch        *b_VDAD_V_Max_Cont;   //!
   TBranch        *b_VDAD_A_Max_Cont;   //!
   TBranch        *b_countNonEff_L0;   //!
   TBranch        *b_numberNonEff_L0;   //!
   TBranch        *b_countDeadCh_L0;   //!
   TBranch        *b_countDeadCh_L0POS;
   TBranch        *b_numberDeadCh_L0;   //!
   TBranch        *b_numberDeadCh_L0POS;   //!
   TBranch        *b_PDORMS_L0;   //!
   TBranch        *b_PDORMS_L0POS;   //!
   TBranch        *b_PDOIntercept_L0;   //!
   TBranch        *b_PDOSlope_L0;   //!
    
    TBranch        *b_neg_DEAD_CHANNELS;
    TBranch        *b_pos_DEAD_CHANNELS;
    
    
    TBranch        *b_PDOIntercept_L0POS;   //!
    TBranch        *b_PDOSlope_L0POS;   //!
    
   TBranch        *b_TDOIntercept_L0;   //!
   TBranch        *b_TDOSlope_L0;   //!
    TBranch        *b_TDOIntercept_L0POS;   //!
    TBranch        *b_TDOSlope_L0POS;   //!
   TBranch        *b_tempMax_L0;   //!
    
    TBranch        *b_tempMax_L0POS;   //!
   TBranch        *b_VDD_V_Max_L0;   //!
   TBranch        *b_VDD_A_Max_L0;   //!
   TBranch        *b_VDDD_V_Max_L0;   //!
   TBranch        *b_VDDD_A_Max_L0;   //!
   TBranch        *b_VDDP_V_Max_L0;   //!
   TBranch        *b_VDDP_A_Max_L0;   //!
   TBranch        *b_VDAD_V_Max_L0;   //!
   TBranch        *b_VDAD_A_Max_L0;   //!
    
    TBranch        *b_PDOMEAN_L0;
    TBranch        *b_TDOMEAN_L0;
    TBranch        *b_PDOMEAN_L0POS;
    TBranch        *b_TDOMEAN_L0POS;
    TBranch        *b_MEAN_DDO;
    TBranch        *b_MEAN_DDOneg;
    TBranch        *b_MEAN_DDOpos;
    
    TBranch        *b_PDOEntriesMEAN_L0;
    TBranch        *b_TDOEntriesMEAN_L0;
    TBranch        *b_PDOEntriesMEAN_L0POS;
    TBranch        *b_TDOEntriesMEAN_L0POS;
    
    TBranch        *b_VDD_V_Max_L0POS;   //!
    TBranch        *b_VDD_A_Max_L0POS;   //!
    TBranch        *b_VDDD_V_Max_L0POS;   //!
    TBranch        *b_VDDD_A_Max_L0POS;   //!
    TBranch        *b_VDDP_V_Max_L0POS;   //!
    TBranch        *b_VDDP_A_Max_L0POS;   //!
    TBranch        *b_VDAD_V_Max_L0POS;   //!
    TBranch        *b_VDAD_A_Max_L0POS;   //!
    
   TBranch        *b_countNonEff_DDO;   //!
   TBranch        *b_numberNonEff_DDO;   //!
   TBranch        *b_countDeadCh_DDO;   //!
   TBranch        *b_numberDeadCh_DDO;   //!
   TBranch        *b_RMS_DDO;   //!
   TBranch        *b_Intercept_DDO;   //!
   TBranch        *b_Slope_DDO;   //!
   TBranch        *b_tempMax_DDO;   //!
   TBranch        *b_VDD_V_Max_DDO;   //!
   TBranch        *b_VDD_A_Max_DDO;   //!
   TBranch        *b_VDDD_V_Max_DDO;   //!
   TBranch        *b_VDDD_A_Max_DDO;   //!
   TBranch        *b_VDDP_V_Max_DDO;   //!
   TBranch        *b_VDDP_A_Max_DDO;   //!
   TBranch        *b_VDAD_V_Max_DDO;   //!
   TBranch        *b_VDAD_A_Max_DDO;   //!
    
    TBranch        *b_countNonEff_DDOneg;   //!
    TBranch        *b_numberNonEff_DDOneg;   //!
    TBranch        *b_countDeadCh_DDOneg;   //!
    TBranch        *b_numberDeadCh_DDOneg;   //!
    TBranch        *b_RMS_DDOneg;   //!
    TBranch        *b_Intercept_DDOneg;   //!
    TBranch        *b_Slope_DDOneg;   //!
    TBranch        *b_tempMax_DDOneg;   //!
    TBranch        *b_VDD_V_Max_DDOneg;   //!
    TBranch        *b_VDD_A_Max_DDOneg;   //!
    TBranch        *b_VDDD_V_Max_DDOneg;   //!
    TBranch        *b_VDDD_A_Max_DDOneg;   //!
    TBranch        *b_VDDP_V_Max_DDOneg;   //!
    TBranch        *b_VDDP_A_Max_DDOneg;   //!
    TBranch        *b_VDAD_V_Max_DDOneg;   //!
    TBranch        *b_VDAD_A_Max_DDOneg;   //!
    
    TBranch        *b_countNonEff_DDOpos;   //!
    TBranch        *b_numberNonEff_DDOpos;   //!
    TBranch        *b_countDeadCh_DDOpos;   //!
    TBranch        *b_numberDeadCh_DDOpos;   //!
    TBranch        *b_RMS_DDOpos;   //!
    TBranch        *b_Intercept_DDOpos;   //!
    TBranch        *b_Slope_DDOpos;   //!
    TBranch        *b_tempMax_DDOpos;   //!
    TBranch        *b_VDD_V_Max_DDOpos;   //!
    TBranch        *b_VDD_A_Max_DDOpos;   //!
    TBranch        *b_VDDD_V_Max_DDOpos;   //!
    TBranch        *b_VDDD_A_Max_DDOpos;   //!
    TBranch        *b_VDDP_V_Max_DDOpos;   //!
    TBranch        *b_VDDP_A_Max_DDOpos;   //!
    TBranch        *b_VDAD_V_Max_DDOpos;   //!
    TBranch        *b_VDAD_A_Max_DDOpos;   //!
    
   TBranch        *b_countBadCh_ART;   //!
   TBranch        *b_numberBadCh_ART;   //!
   TBranch        *b_tempMax_ART;   //!
   TBranch        *b_VDD_V_Max_ART;   //!
   TBranch        *b_VDD_A_Max_ART;   //!
   TBranch        *b_VDDD_V_Max_ART;   //!
   TBranch        *b_VDDD_A_Max_ART;   //!
   TBranch        *b_VDDP_V_Max_ART;   //!
   TBranch        *b_VDDP_A_Max_ART;   //!
   TBranch        *b_VDAD_V_Max_ART;   //!
   TBranch        *b_VDAD_A_Max_ART;   //!
    
    
    TBranch        *b_EntriesARTneg;
    TBranch        *b_EntriesART;
    TBranch        *b_countBadCh_ARTneg;   //!
    TBranch        *b_numberBadCh_ARTneg;   //!
    TBranch        *b_tempMax_ARTneg;   //!
    TBranch        *b_VDD_V_Max_ARTneg;   //!
    TBranch        *b_VDD_A_Max_ARTneg;   //!
    TBranch        *b_VDDD_V_Max_ARTneg;   //!
    TBranch        *b_VDDD_A_Max_ARTneg;   //!
    TBranch        *b_VDDP_V_Max_ARTneg;   //!
    TBranch        *b_VDDP_A_Max_ARTneg;   //!
    TBranch        *b_VDAD_V_Max_ARTneg;   //!
    TBranch        *b_VDAD_A_Max_ARTneg;   //!
    
    TBranch        *b_EntriesARTpos;
    TBranch        *b_countBadCh_ARTpos;   //!
    TBranch        *b_numberBadCh_ARTpos;   //!
    TBranch        *b_tempMax_ARTpos;   //!
    TBranch        *b_VDD_V_Max_ARTpos;   //!
    TBranch        *b_VDD_A_Max_ARTpos;   //!
    TBranch        *b_VDDD_V_Max_ARTpos;   //!
    TBranch        *b_VDDD_A_Max_ARTpos;   //!
    TBranch        *b_VDDP_V_Max_ARTpos;   //!
    TBranch        *b_VDDP_A_Max_ARTpos;   //!
    TBranch        *b_VDAD_V_Max_ARTpos;   //!
    TBranch        *b_VDAD_A_Max_ARTpos;   //!
    
   VMMTree2(TTree *tree=0);
   virtual ~VMMTree2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
//   virtual void     Loop1();
//   virtual void     Loop2(int *IdFailed, int *IdVMM);
   
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
    
    // list numberVMMId for each mode
    
    vector<Int_t>     numberPDOMEAN_L0_ineff;
    vector<Int_t>     numberTDOMEAN_L0_ineff;
    
    vector<Int_t>     numberPDOMEAN_L0POS_ineff;
    vector<Int_t>     numberTDOMEAN_L0POS_ineff;
    
    vector<Int_t>     numberMEAN_DDO_ineff;
    vector<Int_t>     numberMEAN_DDOneg_ineff;
    vector<Int_t>     numberMEAN_DDOpos_ineff;
    
    vector<Int_t>     numberBLine_ineff;
    vector<Int_t>     numberRMS_L0_pdo_ineff;
    vector<Int_t>     numberRMS_cont_pdo_ineff;
    vector<Int_t>     numberRMS_L0_tdo_ineff;
    vector<Int_t>     numberRMS_L0POS_pdo_ineff;
    vector<Int_t>     numberRMS_cont_tdo_ineff;
    vector<Int_t>     numberintercept_L0_ineff;
    vector<Int_t>     numberintercept_cont_ineff;
    vector<Int_t>     numberslope_L0_pdo_ineff;
    vector<Int_t>     numberslope_cont_pdo_ineff;
    vector<Int_t>     numberDDO_slope_ineff;
    vector<Int_t>     numberDDO_intercept_ineff;
    
    vector<Int_t>     numberDDOneg_slope_ineff;
    vector<Int_t>     numberDDOneg_intercept_ineff;
    
    vector<Int_t>     numberDDOpos_slope_ineff;
    vector<Int_t>     numberDDOpos_intercept_ineff;
    
    vector<Int_t>     numberArt_ineff;
    vector<Int_t>     numberARTneg_ineff;
    vector<Int_t>     numberARTpos_ineff;
    
    vector<Int_t>     VMMId_cout;
    vector<Int_t>     numberintercept_L0POS_ineff;
    vector<Int_t>     numberslope_L0POS_pdo_ineff;
    
    // list with tempreture and VMMId ineff
    vector<Float_t>     VMMId_temp_L0;
    vector<Float_t>     VMMId_temp_cont;
    vector<Float_t>     VMMId_temp_DDO;
    vector<Float_t>     VMMId_temp_DDOneg;
    vector<Float_t>     VMMId_temp_DDOpos;
    
    // list with A and VMMId ineff
    vector<Int_t>       VDDP_VMMId;
    vector<Int_t>       VDDP_VMMIdPOS;
    vector<Int_t>       VDDP_bad_VMMId;
    vector<Int_t>       VDDP_bad_VMMIdPOS;
    
    vector<Int_t>       VDD_VMMId;
    vector<Int_t>       VDD_bad_VMMId;
    
    vector<Int_t>       VDDD_VMMId;
    vector<Int_t>       VDDD_bad_VMMId;
    
    vector<Int_t>       VDAD_VMMId;
    vector<Int_t>       VDAD_bad_VMMId;
    
    vector<Int_t>       VDD_VMMIdPOS;
    vector<Int_t>       VDD_bad_VMMIdPOS;
    
    vector<Int_t>       VDDD_VMMIdPOS;
    vector<Int_t>       VDDD_bad_VMMIdPOS;
    
    vector<Int_t>       VDAD_VMMIdPOS;
    vector<Int_t>       VDAD_bad_VMMIdPOS;
    
    vector<Int_t>       over_current_fale;
    vector<Int_t>       goodchip;
    vector<Int_t>       badchip;
    vector<Int_t>       goodchipmean;
    vector<Int_t>       badchipmean;
    
    vector<Int_t>       goodchipL0;
    vector<Int_t>       badchipL0;
    
    vector<Int_t>       goodchipL0mean;
    vector<Int_t>       badchipL0mean;
    
    vector<Int_t>       goodchipL0POS;
    vector<Int_t>       badchipL0POS;
    
    vector<Int_t>       goodchipL0POSmean;
    vector<Int_t>       badchipL0POSmean;
    
    vector<Int_t>       defect;
    
    vector<Int_t>       sum_currentL0;
    vector<Int_t>       sum_currentL0POS;
    vector<Int_t>       sum_current;
    
    vector<Int_t>  DeadCh_Cont;
    vector<Int_t> DeadCh_L0;
    vector<Int_t> DeadCh_L0POS;
    vector<Int_t> DeadCh_DDO;
    vector<Int_t> DeadCh_DDOneg;
    vector<Int_t> DeadCh_DDOpos;
    
    vector<Int_t> numberVMM;
    vector<Int_t> numberVMML0;
    vector<Int_t> numberVMML0POS;
    vector<Int_t> test_Mode;
    vector<Int_t>  countBadChBL;
    vector<Int_t>  countBadCh_PDOL0;
    vector<Int_t> countBadCh_TDOL0;
    vector<Int_t> countBadCh_PDOL0POS;
    vector<Int_t> countBadCh_TDOL0POS;
    vector<Int_t> countBadCh_DDOneg;
    vector<Int_t> countBadCh_DDOpos;
    vector<Int_t> NVMM_neg;
    vector<Int_t> NVMM_pos;
};

#endif

#ifdef VMMTree2_cxx
VMMTree2::VMMTree2(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/var/www/html/www/output/localDB/const.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/var/www/html/www/output/localDB/const.root");
      }
      f->GetObject("ChipConstants",tree);

   }
   Init(tree);
}

VMMTree2::~VMMTree2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t VMMTree2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t VMMTree2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void VMMTree2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   
   numberNonEff_Cont = 0;
   numberDeadCh_Cont = 0;
   numberNonEff_L0 = 0;
   numberDeadCh_L0 = 0;
    
    numberNonEff_DDO = 0;
    numberNonEff_DDOneg = 0;
    numberNonEff_DDOpos = 0;
   
    numberDeadCh_DDO = 0;
    numberDeadCh_DDOneg = 0;
    numberDeadCh_DDOpos = 0;
    
    numberBadCh_ART = 0;
    numberBadCh_ARTneg = 0;
    numberBadCh_ARTpos = 0;
   
    neg_DEAD_CHANNELS = 0;
    pos_DEAD_CHANNELS = 0;
   
    
    // Set branch addresses and branch pointers
   
    if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
    fChain->SetBranchAddress("bLinePauseNeg", &bLinePauseNeg, &b_bLinePauseNeg);
    fChain->SetBranchAddress("bLinePausePos", &bLinePausePos, &b_bLinePausePos);
  
    
    fChain->SetBranchAddress("boardId", &boardId, &b_boradId);
   fChain->SetBranchAddress("VMMId", &VMMId, &b_VMMId);
   fChain->SetBranchAddress("countCh", &countCh, &b_countCh);
   fChain->SetBranchAddress("partID", &partID, &b_partID);
    fChain->SetBranchAddress("userID", &userID, &b_userID);
   fChain->SetBranchAddress("testMode", &testMode, &b_testMode);
    fChain->SetBranchAddress("FAILED", &FAILED, &b_FAILED);
   fChain->SetBranchAddress("dateTime", &dateTime, &b_dateTime);
   fChain->SetBranchAddress("chipStatus", &chipStatus, &b_chipStatus);
    fChain->SetBranchAddress("chipStatusNEG", &chipStatusNEG, &b_chipStatusNEG);
    fChain->SetBranchAddress("chipStatusPOS", &chipStatusPOS, &b_chipStatusPOS);
    
    
   fChain->SetBranchAddress("bLine", bLine, &b_bLine);
   fChain->SetBranchAddress("bLine_RMS", bLine_RMS, &b_bLine_RMS);
    
    fChain->SetBranchAddress("bLinePos", bLinePos, &b_bLinePos);
    fChain->SetBranchAddress("bLine_RMSPos", bLine_RMSPos, &b_bLine_RMSPos);
    
   fChain->SetBranchAddress("countNonEff_Cont", &countNonEff_Cont, &b_countNonEff_Cont);
   fChain->SetBranchAddress("numberNonEff_Cont", &numberNonEff_Cont, &b_numberNonEff_Cont);
   fChain->SetBranchAddress("countDeadCh_Cont", &countDeadCh_Cont, &b_countDeadCh_Cont);
   fChain->SetBranchAddress("numberDeadCh_Cont", &numberDeadCh_Cont, &b_numberDeadCh_Cont);
   fChain->SetBranchAddress("PDORMS_Cont", PDORMS_Cont, &b_PDORMS_Cont);
   fChain->SetBranchAddress("TDORMS_L0",TDORMS_L0, &b_TDORMS_L0);
   fChain->SetBranchAddress("TDORMS_L0POS",TDORMS_L0POS, &b_TDORMS_L0POS);
   fChain->SetBranchAddress("TDORMS_Cont", TDORMS_Cont, &b_TDORMS_Cont);
   fChain->SetBranchAddress("PDOIntercept_Cont", PDOIntercept_Cont, &b_PDOIntercept_Cont);
   fChain->SetBranchAddress("PDOSlope_Cont", PDOSlope_Cont, &b_PDOSlope_Cont);
   fChain->SetBranchAddress("TDOIntercept_Cont", TDOIntercept_Cont, &b_TDOIntercept_Cont);
   fChain->SetBranchAddress("TDOSlope_Cont", TDOSlope_Cont, &b_TDOSlope_Cont);
   fChain->SetBranchAddress("tempMax_Cont", &tempMax_Cont, &b_tempMax_Cont);
   fChain->SetBranchAddress("VDD_V_Max_Cont", &VDD_V_Max_Cont, &b_VDD_V_Max_Cont);
   fChain->SetBranchAddress("VDD_A_Max_Cont", &VDD_A_Max_Cont, &b_VDD_A_Max_Cont);
   fChain->SetBranchAddress("VDDD_V_Max_Cont", &VDDD_V_Max_Cont, &b_VDDD_V_Max_Cont);
   fChain->SetBranchAddress("VDDD_A_Max_Cont", &VDDD_A_Max_Cont, &b_VDDD_A_Max_Cont);
   fChain->SetBranchAddress("VDDP_V_Max_Cont", &VDDP_V_Max_Cont, &b_VDDP_V_Max_Cont);
   fChain->SetBranchAddress("VDDP_A_Max_Cont", &VDDP_A_Max_Cont, &b_VDDP_A_Max_Cont);
   fChain->SetBranchAddress("VDAD_V_Max_Cont", &VDAD_V_Max_Cont, &b_VDAD_V_Max_Cont);
   fChain->SetBranchAddress("VDAD_A_Max_Cont", &VDAD_A_Max_Cont, &b_VDAD_A_Max_Cont);
   fChain->SetBranchAddress("countNonEff_L0", &countNonEff_L0, &b_countNonEff_L0);
   fChain->SetBranchAddress("numberNonEff_L0", &numberNonEff_L0, &b_numberNonEff_L0);
   fChain->SetBranchAddress("countDeadCh_L0", &countDeadCh_L0, &b_countDeadCh_L0);
    fChain->SetBranchAddress("countDeadCh_L0POS", &countDeadCh_L0POS, &b_countDeadCh_L0POS);
   fChain->SetBranchAddress("numberDeadCh_L0", &numberDeadCh_L0, &b_numberDeadCh_L0);
      fChain->SetBranchAddress("numberDeadCh_L0POS", &numberDeadCh_L0POS, &b_numberDeadCh_L0POS);
  
    fChain->SetBranchAddress("neg_DEAD_CHANNELS", &neg_DEAD_CHANNELS, &b_neg_DEAD_CHANNELS);
    fChain->SetBranchAddress("pos_DEAD_CHANNELS", &pos_DEAD_CHANNELS, &b_pos_DEAD_CHANNELS);
    
    fChain->SetBranchAddress("PDORMS_L0", PDORMS_L0, &b_PDORMS_L0);
    fChain->SetBranchAddress("PDORMS_L0POS", PDORMS_L0POS, &b_PDORMS_L0POS);
   fChain->SetBranchAddress("PDOIntercept_L0", PDOIntercept_L0, &b_PDOIntercept_L0);
   fChain->SetBranchAddress("PDOSlope_L0", PDOSlope_L0, &b_PDOSlope_L0);
    fChain->SetBranchAddress("PDOIntercept_L0POS", PDOIntercept_L0POS, &b_PDOIntercept_L0POS);
    fChain->SetBranchAddress("PDOSlope_L0POS", PDOSlope_L0POS, &b_PDOSlope_L0POS);
   fChain->SetBranchAddress("TDOIntercept_L0", TDOIntercept_L0, &b_TDOIntercept_L0);
   fChain->SetBranchAddress("TDOSlope_L0", TDOSlope_L0, &b_TDOSlope_L0);
    fChain->SetBranchAddress("TDOIntercept_L0POS", TDOIntercept_L0POS, &b_TDOIntercept_L0POS);
    fChain->SetBranchAddress("TDOSlope_L0POS", TDOSlope_L0POS, &b_TDOSlope_L0POS);
   fChain->SetBranchAddress("tempMax_L0", &tempMax_L0, &b_tempMax_L0);
    
    fChain->SetBranchAddress("tempMax_L0POS", &tempMax_L0POS, &b_tempMax_L0POS);
    
   fChain->SetBranchAddress("VDD_V_Max_L0", &VDD_V_Max_L0, &b_VDD_V_Max_L0);
   fChain->SetBranchAddress("VDD_A_Max_L0", &VDD_A_Max_L0, &b_VDD_A_Max_L0);
   fChain->SetBranchAddress("VDDD_V_Max_L0", &VDDD_V_Max_L0, &b_VDDD_V_Max_L0);
   fChain->SetBranchAddress("VDDD_A_Max_L0", &VDDD_A_Max_L0, &b_VDDD_A_Max_L0);
   fChain->SetBranchAddress("VDDP_V_Max_L0", &VDDP_V_Max_L0, &b_VDDP_V_Max_L0);
   fChain->SetBranchAddress("VDDP_A_Max_L0", &VDDP_A_Max_L0, &b_VDDP_A_Max_L0);
   fChain->SetBranchAddress("VDAD_V_Max_L0", &VDAD_V_Max_L0, &b_VDAD_V_Max_L0);
   fChain->SetBranchAddress("VDAD_A_Max_L0", &VDAD_A_Max_L0, &b_VDAD_A_Max_L0);
    
    fChain->SetBranchAddress("PDOMEAN_L0", &PDOMEAN_L0, &b_PDOMEAN_L0);
    fChain->SetBranchAddress("TDOMEAN_L0", &TDOMEAN_L0, &b_TDOMEAN_L0);
    fChain->SetBranchAddress("PDOMEAN_L0POS", &PDOMEAN_L0POS, &b_PDOMEAN_L0POS);
    fChain->SetBranchAddress("TDOMEAN_L0POS", &TDOMEAN_L0POS, &b_TDOMEAN_L0POS);
//    fChain->SetBranchAddress("MEAN_DDO", &MEAN_DDO, &b_MEAN_DDO);
    fChain->SetBranchAddress("MEAN_DDOneg", &MEAN_DDOneg, &b_MEAN_DDOneg);
    fChain->SetBranchAddress("MEAN_DDOpos", &MEAN_DDOpos, &b_MEAN_DDOpos);
    
    fChain->SetBranchAddress("PDOEntriesMEAN_L0", &PDOEntriesMEAN_L0, &b_PDOEntriesMEAN_L0);
    fChain->SetBranchAddress("TDOEntriesMEAN_L0",  &TDOEntriesMEAN_L0, &b_TDOEntriesMEAN_L0);
    fChain->SetBranchAddress("PDOEntriesMEAN_L0POS", &PDOEntriesMEAN_L0POS, &b_PDOEntriesMEAN_L0POS);
    fChain->SetBranchAddress("TDOEntriesMEAN_L0POS", &TDOEntriesMEAN_L0POS, &b_TDOEntriesMEAN_L0POS);
    
    fChain->SetBranchAddress("VDD_V_Max_L0POS", &VDD_V_Max_L0POS, &b_VDD_V_Max_L0POS);
    fChain->SetBranchAddress("VDD_A_Max_L0POS", &VDD_A_Max_L0POS, &b_VDD_A_Max_L0POS);
    fChain->SetBranchAddress("VDDD_V_Max_L0POS", &VDDD_V_Max_L0POS, &b_VDDD_V_Max_L0POS);
    fChain->SetBranchAddress("VDDD_A_Max_L0POS", &VDDD_A_Max_L0POS, &b_VDDD_A_Max_L0POS);
    fChain->SetBranchAddress("VDDP_V_Max_L0POS", &VDDP_V_Max_L0POS, &b_VDDP_V_Max_L0POS);
    fChain->SetBranchAddress("VDDP_A_Max_L0POS", &VDDP_A_Max_L0POS, &b_VDDP_A_Max_L0POS);
    fChain->SetBranchAddress("VDAD_V_Max_L0POS", &VDAD_V_Max_L0POS, &b_VDAD_V_Max_L0POS);
    fChain->SetBranchAddress("VDAD_A_Max_L0POS", &VDAD_A_Max_L0POS, &b_VDAD_A_Max_L0POS);
  
    
//    fChain->SetBranchAddress("countNonEff_DDO", &countNonEff_DDO, &b_countNonEff_DDO);
//   fChain->SetBranchAddress("numberNonEff_DDO", &numberNonEff_DDO, &b_numberNonEff_DDO);
//   fChain->SetBranchAddress("countDeadCh_DDO", &countDeadCh_DDO, &b_countDeadCh_DDO);
//   fChain->SetBranchAddress("numberDeadCh_DDO", &numberDeadCh_DDO, &b_numberDeadCh_DDO);
//   fChain->SetBranchAddress("RMS_DDO", RMS_DDO, &b_RMS_DDO);
//   fChain->SetBranchAddress("Intercept_DDO", Intercept_DDO, &b_Intercept_DDO);
//   fChain->SetBranchAddress("Slope_DDO", Slope_DDO, &b_Slope_DDO);
//   fChain->SetBranchAddress("tempMax_DDO", &tempMax_DDO, &b_tempMax_DDO);
//   fChain->SetBranchAddress("VDD_V_Max_DDO", &VDD_V_Max_DDO, &b_VDD_V_Max_DDO);
//   fChain->SetBranchAddress("VDD_A_Max_DDO", &VDD_A_Max_DDO, &b_VDD_A_Max_DDO);
//   fChain->SetBranchAddress("VDDD_V_Max_DDO", &VDDD_V_Max_DDO, &b_VDDD_V_Max_DDO);
//   fChain->SetBranchAddress("VDDD_A_Max_DDO", &VDDD_A_Max_DDO, &b_VDDD_A_Max_DDO);
//   fChain->SetBranchAddress("VDDP_V_Max_DDO", &VDDP_V_Max_DDO, &b_VDDP_V_Max_DDO);
//   fChain->SetBranchAddress("VDDP_A_Max_DDO", &VDDP_A_Max_DDO, &b_VDDP_A_Max_DDO);
//   fChain->SetBranchAddress("VDAD_V_Max_DDO", &VDAD_V_Max_DDO, &b_VDAD_V_Max_DDO);
//   fChain->SetBranchAddress("VDAD_A_Max_DDO", &VDAD_A_Max_DDO, &b_VDAD_A_Max_DDO);
    
    fChain->SetBranchAddress("countNonEff_DDOneg", &countNonEff_DDOneg, &b_countNonEff_DDOneg);
    fChain->SetBranchAddress("numberNonEff_DDOneg", &numberNonEff_DDOneg, &b_numberNonEff_DDOneg);
    fChain->SetBranchAddress("countDeadCh_DDOneg", &countDeadCh_DDOneg, &b_countDeadCh_DDOneg);
    fChain->SetBranchAddress("numberDeadCh_DDOneg", &numberDeadCh_DDOneg, &b_numberDeadCh_DDOneg);
    fChain->SetBranchAddress("RMS_DDOneg", RMS_DDOneg, &b_RMS_DDOneg);
    fChain->SetBranchAddress("Intercept_DDOneg", Intercept_DDOneg, &b_Intercept_DDOneg);
    fChain->SetBranchAddress("Slope_DDOneg", Slope_DDOneg, &b_Slope_DDOneg);
    fChain->SetBranchAddress("tempMax_DDOneg", &tempMax_DDOneg, &b_tempMax_DDOneg);
    fChain->SetBranchAddress("VDD_V_Max_DDOneg", &VDD_V_Max_DDOneg, &b_VDD_V_Max_DDOneg);
    fChain->SetBranchAddress("VDD_A_Max_DDOneg", &VDD_A_Max_DDOneg, &b_VDD_A_Max_DDOneg);
    fChain->SetBranchAddress("VDDD_V_Max_DDOneg", &VDDD_V_Max_DDOneg, &b_VDDD_V_Max_DDOneg);
    fChain->SetBranchAddress("VDDD_A_Max_DDOneg", &VDDD_A_Max_DDOneg, &b_VDDD_A_Max_DDOneg);
    fChain->SetBranchAddress("VDDP_V_Max_DDOneg", &VDDP_V_Max_DDOneg, &b_VDDP_V_Max_DDOneg);
    fChain->SetBranchAddress("VDDP_A_Max_DDOneg", &VDDP_A_Max_DDOneg, &b_VDDP_A_Max_DDOneg);
    fChain->SetBranchAddress("VDAD_V_Max_DDOneg", &VDAD_V_Max_DDOneg, &b_VDAD_V_Max_DDOneg);
    fChain->SetBranchAddress("VDAD_A_Max_DDOneg", &VDAD_A_Max_DDOneg, &b_VDAD_A_Max_DDOneg);
    
    fChain->SetBranchAddress("countNonEff_DDOpos", &countNonEff_DDOpos, &b_countNonEff_DDOpos);
    fChain->SetBranchAddress("numberNonEff_DDOpos", &numberNonEff_DDOpos, &b_numberNonEff_DDOpos);
    fChain->SetBranchAddress("countDeadCh_DDOpos", &countDeadCh_DDOpos, &b_countDeadCh_DDOpos);
    fChain->SetBranchAddress("numberDeadCh_DDOpos", &numberDeadCh_DDOpos, &b_numberDeadCh_DDOpos);
    fChain->SetBranchAddress("RMS_DDOpos", RMS_DDOpos, &b_RMS_DDOpos);
    fChain->SetBranchAddress("Intercept_DDOpos", Intercept_DDOpos, &b_Intercept_DDOpos);
    fChain->SetBranchAddress("Slope_DDOpos", Slope_DDOpos, &b_Slope_DDOpos);
    fChain->SetBranchAddress("tempMax_DDOpos", &tempMax_DDOpos, &b_tempMax_DDOpos);
    fChain->SetBranchAddress("VDD_V_Max_DDOpos", &VDD_V_Max_DDOpos, &b_VDD_V_Max_DDOpos);
    fChain->SetBranchAddress("VDD_A_Max_DDOpos", &VDD_A_Max_DDOpos, &b_VDD_A_Max_DDOpos);
    fChain->SetBranchAddress("VDDD_V_Max_DDOpos", &VDDD_V_Max_DDOpos, &b_VDDD_V_Max_DDOpos);
    fChain->SetBranchAddress("VDDD_A_Max_DDOpos", &VDDD_A_Max_DDOpos, &b_VDDD_A_Max_DDOpos);
    fChain->SetBranchAddress("VDDP_V_Max_DDOpos", &VDDP_V_Max_DDOpos, &b_VDDP_V_Max_DDOpos);
    fChain->SetBranchAddress("VDDP_A_Max_DDOpos", &VDDP_A_Max_DDOpos, &b_VDDP_A_Max_DDOpos);
    fChain->SetBranchAddress("VDAD_V_Max_DDOpos", &VDAD_V_Max_DDOpos, &b_VDAD_V_Max_DDOpos);
    fChain->SetBranchAddress("VDAD_A_Max_DDOpos", &VDAD_A_Max_DDOpos, &b_VDAD_A_Max_DDOpos);
    
    
//   fChain->SetBranchAddress("countBadCh_ART", &countBadCh_ART, &b_countBadCh_ART);
//   fChain->SetBranchAddress("numberBadCh_ART", &numberBadCh_ART, &b_numberBadCh_ART);
//   fChain->SetBranchAddress("tempMax_ART", &tempMax_ART, &b_tempMax_ART);
//   fChain->SetBranchAddress("VDD_V_Max_ART", &VDD_V_Max_ART, &b_VDD_V_Max_ART);
//   fChain->SetBranchAddress("VDD_A_Max_ART", &VDD_A_Max_ART, &b_VDD_A_Max_ART);
//   fChain->SetBranchAddress("VDDD_V_Max_ART", &VDDD_V_Max_ART, &b_VDDD_V_Max_ART);
//   fChain->SetBranchAddress("VDDD_A_Max_ART", &VDDD_A_Max_ART, &b_VDDD_A_Max_ART);
//   fChain->SetBranchAddress("VDDP_V_Max_ART", &VDDP_V_Max_ART, &b_VDDP_V_Max_ART);
//   fChain->SetBranchAddress("VDDP_A_Max_ART", &VDDP_A_Max_ART, &b_VDDP_A_Max_ART);
//   fChain->SetBranchAddress("VDAD_V_Max_ART", &VDAD_V_Max_ART, &b_VDAD_V_Max_ART);
//   fChain->SetBranchAddress("VDAD_A_Max_ART", &VDAD_A_Max_ART, &b_VDAD_A_Max_ART);
//     fChain->SetBranchAddress("EntriesART", &EntriesART, &b_EntriesART);
    fChain->SetBranchAddress("countBadCh_ARTneg", &countBadCh_ARTneg, &b_countBadCh_ARTneg);
    fChain->SetBranchAddress("numberBadCh_ARTneg", &numberBadCh_ARTneg, &b_numberBadCh_ARTneg);
    
    fChain->SetBranchAddress("countBadCh_ARTpos", &countBadCh_ARTpos, &b_countBadCh_ARTpos);
    fChain->SetBranchAddress("numberBadCh_ARTpos", &numberBadCh_ARTpos, &b_numberBadCh_ARTpos);
    
    fChain->SetBranchAddress("EntriesARTneg", &EntriesARTneg, &b_EntriesARTneg);
   
    fChain->SetBranchAddress("EntriesARTpos", &EntriesARTpos, &b_EntriesARTpos);
    
    
    
   Notify();
}

Bool_t VMMTree2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void VMMTree2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t VMMTree2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef VMMTree2_cxx





