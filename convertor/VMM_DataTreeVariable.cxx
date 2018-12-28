namespace VMMConvertor {
    
TTree *chipConstTree;

Int_t bordId;
Int_t VMMNumber;
    
Int_t chipStatus = 0;
Int_t chipStatusNEG = 0;
Int_t chipStatusPOS = 0;
    
Int_t countCh = 64;

int nonCorrectValue = -1000000;
//    int nonCorrectValue = -1;
    
Float_t bLinePauseNEG;
Float_t bLinePausePOS;

Float_t bLine[64];
Float_t bLine_RMS[64];

Float_t bLinePos[64];
Float_t bLine_RMSPos[64];
    
std::vector<Int_t> listbadCh_POS;
std::vector<Int_t> listbadCh_NEG;

// cont variable
Int_t countNonEff_Cont;
Int_t countDeadCh_Cont;
std::vector<Int_t> listNonEffCh_Cont;
std::vector<Int_t> listDeadCh_Cont;
Float_t arrayPDOInterc_Cont[64];
Float_t arrayPDOSlope_Cont[64];
Float_t arrayPDORMS_Cont[64];
Float_t arrayPDOMEAN_Cont[64];
Int_t arrayPDOEntriesMEAN_Cont[64];
Float_t arrayTDOInterc_Cont[64];
Float_t arrayTDOSlope_Cont[64];
Float_t arrayTDORMS_Cont[64];
Int_t arrayTDOEntriesMEAN_Cont[64];
Float_t arrayTDOMEAN_Cont[64];
Float_t tempMax_Cont;
Float_t VDD_V_Max_Cont;
Float_t VDD_A_Max_Cont;
Float_t VDDD_V_Max_Cont;
Float_t VDDD_A_Max_Cont;
Float_t VDDP_V_Max_Cont;
Float_t VDDP_A_Max_Cont;
Float_t VDAD_V_Max_Cont;
Float_t VDAD_A_Max_Cont;

Char_t FAILED[64];
Char_t partID[64];
Char_t testMode[64];
Char_t FPGA_VER[64];
Char_t userID[64];
Char_t dataTimeChar[64];

TDatime *dataTime;
UInt_t dataTimeInt;

// L0 variable
Int_t countNonEff_L0;
Int_t countDeadCh_L0;
std::vector<Int_t> listNonEffCh_L0;
std::vector<Int_t> listDeadCh_L0;
Float_t arrayPDOInterc_L0[64];
Float_t arrayPDOSlope_L0[64];
Float_t arrayPDORMS_L0[64];
Float_t arrayPDOMEAN_L0[64];
Int_t arrayPDOEntriesMEAN_L0[64];
Float_t arrayTDOInterc_L0[64];
Float_t arrayTDOSlope_L0[64];
Float_t arrayTDORMS_L0[64];
Float_t arrayTDOMEAN_L0[64];
Int_t arrayTDOEntriesMEAN_L0[64];
Float_t tempMax_L0;
Float_t VDD_V_Max_L0;
Float_t VDD_A_Max_L0;
Float_t VDDD_V_Max_L0;
Float_t VDDD_A_Max_L0;
Float_t VDDP_V_Max_L0;
Float_t VDDP_A_Max_L0;
Float_t VDAD_V_Max_L0;
Float_t VDAD_A_Max_L0;

// L0POS variable
Int_t countNonEff_L0POS;
Int_t countDeadCh_L0POS;
std::vector<Int_t> listNonEffCh_L0POS;
std::vector<Int_t> listDeadCh_L0POS;
Float_t arrayPDOInterc_L0POS[64];
Float_t arrayPDOSlope_L0POS[64];
Float_t arrayPDORMS_L0POS[64];
Float_t arrayPDOMEAN_L0POS[64];
Int_t arrayPDOEntriesMEAN_L0POS[64];
Float_t arrayTDOInterc_L0POS[64];
Float_t arrayTDOSlope_L0POS[64];
Float_t arrayTDORMS_L0POS[64];
Float_t arrayTDOMEAN_L0POS[64];
Int_t arrayTDOEntriesMEAN_L0POS[64];
Float_t tempMax_L0POS;
Float_t VDD_V_Max_L0POS;
Float_t VDD_A_Max_L0POS;
Float_t VDDD_V_Max_L0POS;
Float_t VDDD_A_Max_L0POS;
Float_t VDDP_V_Max_L0POS;
Float_t VDDP_A_Max_L0POS;
Float_t VDAD_V_Max_L0POS;
Float_t VDAD_A_Max_L0POS;

//// DDO variable
//Int_t countNonEff_DDO;
//Int_t countDeadCh_DDO;
//std::vector<Int_t> listNonEffCh_DDO;
//std::vector<Int_t> listDeadCh_DDO;
//Float_t arrayPDOInterc_DDO[64];
//Float_t arrayPDOSlope_DDO[64];
//Float_t arrayPDORMS_DDO[64];
//Float_t arrayPDOMEAN_DDO[64];
//Int_t arrayPDOEntriesMEAN_DDO[64];
//Float_t tempMax_DDO;
//Float_t VDD_V_Max_DDO;
//Float_t VDD_A_Max_DDO;
//Float_t VDDD_V_Max_DDO;
//Float_t VDDD_A_Max_DDO;
//Float_t VDDP_V_Max_DDO;
//Float_t VDDP_A_Max_DDO;
//Float_t VDAD_V_Max_DDO;
//Float_t VDAD_A_Max_DDO;

// DDO_L0

Int_t countNonEff_DDOneg;
Int_t countDeadCh_DDOneg;
std::vector<Int_t> listNonEffCh_DDOneg;
std::vector<Int_t> listDeadCh_DDOneg;
Float_t arrayPDOInterc_DDOneg[64];
Float_t arrayPDOSlope_DDOneg[64];
Float_t arrayPDORMS_DDOneg[64];
Float_t arrayPDOMEAN_DDOneg[64];
Int_t arrayPDOEntriesMEAN_DDOneg[64];
Float_t tempMax_DDOneg;
Float_t VDD_V_Max_DDOneg;
Float_t VDD_A_Max_DDOneg;
Float_t VDDD_V_Max_DDOneg;
Float_t VDDD_A_Max_DDOneg;
Float_t VDDP_V_Max_DDOneg;
Float_t VDDP_A_Max_DDOneg;
Float_t VDAD_V_Max_DDOneg;
Float_t VDAD_A_Max_DDOneg;

//DD0 L0 Pos


Int_t countNonEff_DDOpos;
Int_t countDeadCh_DDOpos;
std::vector<Int_t> listNonEffCh_DDOpos;
std::vector<Int_t> listDeadCh_DDOpos;
Float_t arrayPDOInterc_DDOpos[64];
Float_t arrayPDOSlope_DDOpos[64];
Float_t arrayPDORMS_DDOpos[64];
Float_t arrayPDOMEAN_DDOpos[64];
Int_t arrayPDOEnriesMEAN_DDOpos[64];
Float_t tempMax_DDOpos;
Float_t VDD_V_Max_DDOpos;
Float_t VDD_A_Max_DDOpos;
Float_t VDDD_V_Max_DDOpos;
Float_t VDDD_A_Max_DDOpos;
Float_t VDDP_V_Max_DDOpos;
Float_t VDDP_A_Max_DDOpos;
Float_t VDAD_V_Max_DDOpos;
Float_t VDAD_A_Max_DDOpos;

//// ART  variable
//Int_t countBadCh_ART;
//std::vector<Int_t> listBadCh_ART;
//Float_t tempMax_ART;
//Int_t arrayEntriesART[64];
//Float_t VDD_V_Max_ART;
//Float_t VDD_A_Max_ART;
//Float_t VDDD_V_Max_ART;
//Float_t VDDD_A_Max_ART;
//Float_t VDDP_V_Max_ART;
//Float_t VDDP_A_Max_ART;
//Float_t VDAD_V_Max_ART;
//Float_t VDAD_A_Max_ART;

// ART L0 variable
Int_t countBadCh_ARTneg;
Int_t arrayEntriesARTneg[64];
std::vector<Int_t> listBadCh_ARTneg;
Float_t tempMax_ARTneg;
Float_t VDD_V_Max_ARTneg;
Float_t VDD_A_Max_ARTneg;
Float_t VDDD_V_Max_ARTneg;
Float_t VDDD_A_Max_ARTneg;
Float_t VDDP_V_Max_ARTneg;
Float_t VDDP_A_Max_ARTneg;
Float_t VDAD_V_Max_ARTneg;
Float_t VDAD_A_Max_ARTneg;

// ART L0 POS variable
Int_t countBadCh_ARTpos;
std::vector<Int_t> listBadCh_ARTpos;
Int_t arrayEntriesARTpos[64];
Float_t tempMax_ARTpos;
Float_t VDD_V_Max_ARTpos;
Float_t VDD_A_Max_ARTpos;
Float_t VDDD_V_Max_ARTpos;
Float_t VDDD_A_Max_ARTpos;
Float_t VDDP_V_Max_ARTpos;
Float_t VDDP_A_Max_ARTpos;
Float_t VDAD_V_Max_ARTpos;
Float_t VDAD_A_Max_ARTpos;

void buidBranchTree() {
    
    //dataTime->Set(2000, 2, 3, 4, 5, 6);
    
    chipConstTree = new TTree("ChipConstants","data");
    
    chipConstTree->Branch("userID", userID, "userID/C", 64);
    
    //UInt_t dataTimeInt = dataTime->Convert(kTRUE);
    //dataTimeInt = dataTime->Convert();
    //std::cout << " \n convert Date Time "  <<dataTime->Convert();
    //std::cout << "\n  ==== " << (TDatime(dataTimeInt)).GetHour();
    
    chipConstTree->Branch("dateTime", &dataTimeInt, "dateTime/i");
    
    chipConstTree->Branch("pos_DEAD_CHANNELS", &listbadCh_POS);
    chipConstTree->Branch("neg_DEAD_CHANNELS", &listbadCh_NEG);
    
    // cont
    
    chipConstTree->Branch("countCh", &countCh, "countCh/I");
    
    

    chipConstTree->Branch("FAILED", FAILED, "FAILED/C", 64);
    chipConstTree->Branch("partID", partID, "partID/C", 64);
    chipConstTree->Branch("testMode", testMode, "testMode/C", 64);
    chipConstTree->Branch("FPGA_VER", FPGA_VER, "FPGA_VER/C", 64);
    
    chipConstTree->Branch("bLine", &bLine, "bLine[countCh]/F");
    chipConstTree->Branch("bLine_RMS", &bLine_RMS, "bLine_RMS[countCh]/F");
    
    chipConstTree->Branch("bLinePos", &bLinePos, "bLinePos[countCh]/F");
    chipConstTree->Branch("bLine_RMSPos", &bLine_RMSPos, "bLine_RMSPos[countCh]/F");
    
    chipConstTree->Branch("bLinePauseNeg", &bLinePauseNEG, "bLinePauseNeg/F");
    chipConstTree->Branch("bLinePausePos", &bLinePausePOS, "bLinePausePos/F");
    
    chipConstTree->Branch("chipStatus", &chipStatus, "chipStatus/I");
    
    chipConstTree->Branch("chipStatusNEG", &chipStatusNEG, "chipStatusNEG/I");
    chipConstTree->Branch("chipStatusPOS", &chipStatusPOS, "chipStatusPOS/I");
    
    chipConstTree->Branch("countNonEff_Cont", &countNonEff_Cont, "countNonEff_Cont/I");
    chipConstTree->Branch("numberNonEff_Cont", &listNonEffCh_Cont);
    chipConstTree->Branch("countDeadCh_Cont", &countDeadCh_Cont, "countDeadCh_Cont/I");
    chipConstTree->Branch("numberDeadCh_Cont", &listDeadCh_Cont);
    chipConstTree->Branch("PDORMS_Cont", &arrayPDORMS_Cont, "PDORMS_Cont[countCh]/F");
    chipConstTree->Branch("PDOIntercept_Cont", &arrayPDOInterc_Cont, "PDOIntercept_Cont[countCh]/F");
    chipConstTree->Branch("PDOSlope_Cont", &arrayPDOSlope_Cont, "PDOSlope_Cont[countCh]/F");
    chipConstTree->Branch("PDOMEAN_Cont", &arrayPDOMEAN_Cont, "PDOMEAN_Cont[countCh]/F");
    chipConstTree->Branch("PDOEntriesMEAN_Cont", &arrayPDOEntriesMEAN_Cont, "PDOEntriesMEAN_Cont[countCh]/I");
    chipConstTree->Branch("TDOIntercept_Cont", &arrayTDOInterc_Cont, "TDOIntercept_Cont[countCh]/F");
    chipConstTree->Branch("TDOSlope_Cont", &arrayTDOSlope_Cont, "TDOSlope_Cont[countCh]/F");
    chipConstTree->Branch("TDORMS_Cont", &arrayTDORMS_Cont, "TDORMS_Cont[countCh]/F");
    chipConstTree->Branch("TDOMEAN_Cont", &arrayTDOMEAN_Cont, "TDOMEAN_Cont[countCh]/F");
    chipConstTree->Branch("TDOEntriesMEAN_Cont", &arrayTDOEntriesMEAN_Cont, "TDOEntriesMEAN_Cont[countCh]/I");
    chipConstTree->Branch("tempMax_Cont", &tempMax_Cont, "tempMax_Cont/F");
    chipConstTree->Branch("VDD_V_Max_Cont", &VDD_V_Max_Cont, "VDD_V_Max_Cont/F");
    chipConstTree->Branch("VDD_A_Max_Cont", &VDD_A_Max_Cont, "VDD_A_Max_Cont/F");
    chipConstTree->Branch("VDDD_V_Max_Cont", &VDDD_V_Max_Cont, "VDDD_V_Max_Cont/F");
    chipConstTree->Branch("VDDD_A_Max_Cont", &VDDD_A_Max_Cont, "VDDD_A_Max_Cont/F");
    chipConstTree->Branch("VDDP_V_Max_Cont", &VDDP_V_Max_Cont, "VDDP_V_Max_Cont/F");
    chipConstTree->Branch("VDDP_A_Max_Cont", &VDDP_A_Max_Cont, "VDDP_A_Max_Cont/F");
    chipConstTree->Branch("VDAD_V_Max_Cont", &VDAD_V_Max_Cont, "VDAD_V_Max_Cont/F");
    chipConstTree->Branch("VDAD_A_Max_Cont", &VDAD_A_Max_Cont, "VDAD_A_Max_Cont/F");
    
    // L0
    
    chipConstTree->Branch("boardId", &bordId, "boradId/I");
    chipConstTree->Branch("VMMId", &VMMNumber, "VMMId/I");
    chipConstTree->Branch("countNonEff_L0", &countNonEff_L0, "countNonEff_L0/I");
    chipConstTree->Branch("numberNonEff_L0", &listNonEffCh_L0);
    chipConstTree->Branch("countDeadCh_L0", &countDeadCh_L0, "countDeadCh_L0/I");
    chipConstTree->Branch("numberDeadCh_L0", &listDeadCh_L0);
    chipConstTree->Branch("PDORMS_L0", &arrayPDORMS_L0, "PDORMS_L0[countCh]/F");
    chipConstTree->Branch("PDOIntercept_L0", &arrayPDOInterc_L0, "PDOIntercept_L0[countCh]/F");
    chipConstTree->Branch("PDOSlope_L0", &arrayPDOSlope_L0, "PDOSlope_L0[countCh]/F");
    chipConstTree->Branch("PDOMEAN_L0", &arrayPDOMEAN_L0, "PDOMEAN_L0[countCh]/F");
    chipConstTree->Branch("PDOEntriesMEAN_L0", &arrayPDOEntriesMEAN_L0, "PDOEntriesMEAN_L0[countCh]/I");
    chipConstTree->Branch("TDORMS_L0", &arrayTDORMS_L0, "TDORMS_L0[countCh]/F");
    chipConstTree->Branch("TDOIntercept_L0", &arrayTDOInterc_L0, "TDOIntercept_L0[countCh]/F");
    chipConstTree->Branch("TDOSlope_L0", &arrayTDOSlope_L0, "TDOSlope_L0[countCh]/F");
    chipConstTree->Branch("TDOMEAN_L0", &arrayTDOMEAN_L0, "TDOMEAN_L0[countCh]/F");
    chipConstTree->Branch("TDOEntriesMEAN_L0", &arrayTDOEntriesMEAN_L0, "TDOEntriesMEAN_L0[countCh]/I");
    chipConstTree->Branch("tempMax_L0", &tempMax_L0, "tempMax_L0/F");
    chipConstTree->Branch("VDD_V_Max_L0", &VDD_V_Max_L0, "VDD_V_Max_L0/F");
    chipConstTree->Branch("VDD_A_Max_L0", &VDD_A_Max_L0, "VDD_A_Max_L0/F");
    chipConstTree->Branch("VDDD_V_Max_L0", &VDDD_V_Max_L0, "VDDD_V_Max_L0/F");
    chipConstTree->Branch("VDDD_A_Max_L0", &VDDD_A_Max_L0, "VDDD_A_Max_L0/F");
    chipConstTree->Branch("VDDP_V_Max_L0", &VDDP_V_Max_L0, "VDDP_V_Max_L0/F");
    chipConstTree->Branch("VDDP_A_Max_L0", &VDDP_A_Max_L0, "VDDP_A_Max_L0/F");
    chipConstTree->Branch("VDAD_V_Max_L0", &VDAD_V_Max_L0, "VDAD_V_Max_L0/F");
    chipConstTree->Branch("VDAD_A_Max_L0", &VDAD_A_Max_L0, "VDAD_A_Max_L0/F");
    
    // L0POS variable
    
    chipConstTree->Branch("countNonEff_L0POS", &countNonEff_L0POS, "countNonEff_L0POS/I");
    chipConstTree->Branch("numberNonEff_L0POS", &listNonEffCh_L0POS);
    chipConstTree->Branch("countDeadCh_L0POS", &countDeadCh_L0POS, "countDeadCh_L0POS/I");
    chipConstTree->Branch("numberDeadCh_L0POS", &listDeadCh_L0POS);
    chipConstTree->Branch("PDORMS_L0POS", &arrayPDORMS_L0POS, "PDORMS_L0POS[countCh]/F");
    chipConstTree->Branch("PDOIntercept_L0POS", &arrayPDOInterc_L0POS, "PDOIntercept_L0POS[countCh]/F");
    chipConstTree->Branch("PDOSlope_L0POS", &arrayPDOSlope_L0POS, "PDOSlope_L0POS[countCh]/F");
    chipConstTree->Branch("PDOMEAN_L0POS", &arrayPDOMEAN_L0POS, "PDOMEAN_L0POS[countCh]/F");
    chipConstTree->Branch("PDOEntriesMEAN_L0POS", &arrayPDOEntriesMEAN_L0POS, "PDOEntriesMEAN_L0POS[countCh]/I");
    chipConstTree->Branch("TDORMS_L0POS", &arrayTDORMS_L0POS, "TDORMS_L0POS[countCh]/F");
    chipConstTree->Branch("TDOIntercept_L0POS", &arrayTDOInterc_L0POS, "TDOIntercept_L0POS[countCh]/F");
    chipConstTree->Branch("TDOSlope_L0POS", &arrayTDOSlope_L0POS, "TDOSlope_L0POS[countCh]/F");
    chipConstTree->Branch("TDOMEAN_L0POS", &arrayTDOMEAN_L0POS, "TDOMEAN_L0POS[countCh]/F");
    chipConstTree->Branch("TDOEntriesMEAN_L0POS", &arrayTDOEntriesMEAN_L0POS, "TDOEntriesMEAN_L0POS[countCh]/I");
    chipConstTree->Branch("tempMax_L0POS", &tempMax_L0POS, "tempMax_L0POS/F");
    chipConstTree->Branch("VDD_V_Max_L0POS", &VDD_V_Max_L0POS, "VDD_V_Max_L0POS/F");
    chipConstTree->Branch("VDD_A_Max_L0POS", &VDD_A_Max_L0POS, "VDD_A_Max_L0POS/F");
    chipConstTree->Branch("VDDD_V_Max_L0POS", &VDDD_V_Max_L0POS, "VDDD_V_Max_L0POS/F");
    chipConstTree->Branch("VDDD_A_Max_L0POS", &VDDD_A_Max_L0POS, "VDDD_A_Max_L0POS/F");
    chipConstTree->Branch("VDDP_V_Max_L0POS", &VDDP_V_Max_L0POS, "VDDP_V_Max_L0POS/F");
    chipConstTree->Branch("VDDP_A_Max_L0POS", &VDDP_A_Max_L0POS, "VDDP_A_Max_L0POS/F");
    chipConstTree->Branch("VDAD_V_Max_L0POS", &VDAD_V_Max_L0POS, "VDAD_V_Max_L0POS/F");
    chipConstTree->Branch("VDAD_A_Max_L0POS", &VDAD_A_Max_L0POS, "VDAD_A_Max_L0POS/F");
    
//    // DDO variable
//
//    chipConstTree->Branch("countNonEff_DDO", &countNonEff_DDO, "countNonEff_DDO/I");
//    chipConstTree->Branch("numberNonEff_DDO", &listNonEffCh_DDO);
//    chipConstTree->Branch("countDeadCh_DDO", &countDeadCh_DDO, "countDeadCh_DDO/I");
//    chipConstTree->Branch("numberDeadCh_DDO", &listDeadCh_DDO);
//    chipConstTree->Branch("PDORMS_DDO", &arrayPDORMS_DDO, "PDORMS_DDO[countCh]/F");
//    chipConstTree->Branch("PDOIntercept_DDO", &arrayPDOInterc_DDO, "PDOIntercept_DDO[countCh]/F");
//    chipConstTree->Branch("PDOSlope_DDO", &arrayPDOSlope_DDO, "PDOSlope_DDO[countCh]/F");
//    chipConstTree->Branch("PDOMEAN_DDO", &arrayPDOMEAN_DDO, "PDOMEAN_DDO[countCh]/F");
//    chipConstTree->Branch("EntriesMEAN_DDO", &arrayPDOEntriesMEAN_DDO, "EntriesMEAN_DDO[countCh]/I");
//    chipConstTree->Branch("tempMax_DDO", &tempMax_DDO, "tempMax_DDO/F");
//    chipConstTree->Branch("VDD_V_Max_DDO", &VDD_V_Max_DDO, "VDD_V_Max_DDO/F");
//    chipConstTree->Branch("VDD_A_Max_DDO", &VDD_A_Max_DDO, "VDD_A_Max_DDO/F");
//    chipConstTree->Branch("VDDD_V_Max_DDO", &VDDD_V_Max_DDO, "VDDD_V_Max_DDO/F");
//    chipConstTree->Branch("VDDD_A_Max_DDO", &VDDD_A_Max_DDO, "VDDD_A_Max_DDO/F");
//    chipConstTree->Branch("VDDP_V_Max_DDO", &VDDP_V_Max_DDO, "VDDP_V_Max_DDO/F");
//    chipConstTree->Branch("VDDP_A_Max_DDO", &VDDP_A_Max_DDO, "VDDP_A_Max_DDO/F");
//    chipConstTree->Branch("VDAD_V_Max_DDO", &VDAD_V_Max_DDO, "VDAD_V_Max_DDO/F");
//    chipConstTree->Branch("VDAD_A_Max_DDO", &VDAD_A_Max_DDO, "VDAD_A_Max_DDO/F");
    
    // DDO_neg
    
    chipConstTree->Branch("numberNonEff_DDOneg", &listNonEffCh_DDOneg);
    chipConstTree->Branch("countDeadCh_DDOneg", &countDeadCh_DDOneg, "countDeadCh_DDOneg/I");
    chipConstTree->Branch("numberDeadCh_DDOneg", &listDeadCh_DDOneg);
    chipConstTree->Branch("RMS_DDOneg", &arrayPDORMS_DDOneg, "RMS_DDOneg[countCh]/F");
    chipConstTree->Branch("Intercept_DDOneg", &arrayPDOInterc_DDOneg, "Intercept_DDOneg[countCh]/F");
    chipConstTree->Branch("Slope_DDOneg", &arrayPDOSlope_DDOneg, "Slope_DDOneg[countCh]/F");
    chipConstTree->Branch("MEAN_DDOneg", &arrayPDOMEAN_DDOneg, "MEAN_DDOneg[countCh]/F");
    chipConstTree->Branch("EntriesMEAN_DDOneg", &arrayPDOEntriesMEAN_DDOneg, "EntriesMEAN_DDOneg[countCh]/I");
    chipConstTree->Branch("tempMax_DDOneg", &tempMax_DDOneg, "tempMax_DDOneg/F");
    chipConstTree->Branch("VDD_V_Max_DDOneg", &VDD_V_Max_DDOneg, "VDD_V_Max_DDOneg/F");
    chipConstTree->Branch("VDD_A_Max_DDOneg", &VDD_A_Max_DDOneg, "VDD_A_Max_DDOneg/F");
    chipConstTree->Branch("VDDD_V_Max_DDOneg", &VDDD_V_Max_DDOneg, "VDDD_V_Max_DDOneg/F");
    chipConstTree->Branch("VDDD_A_Max_DDOneg", &VDDD_A_Max_DDOneg, "VDDD_A_Max_DDOneg/F");
    chipConstTree->Branch("VDDP_V_Max_DDOneg", &VDDP_V_Max_DDOneg, "VDDP_V_Max_DDOneg/F");
    chipConstTree->Branch("VDDP_A_Max_DDOneg", &VDDP_A_Max_DDOneg, "VDDP_A_Max_DDOneg/F");
    chipConstTree->Branch("VDAD_V_Max_DDOneg", &VDAD_V_Max_DDOneg, "VDAD_V_Max_DDOneg/F");
    chipConstTree->Branch("VDAD_A_Max_DDOneg", &VDAD_A_Max_DDOneg, "VDAD_A_Max_DDOneg/F");
    chipConstTree->Branch("countNonEff_DDOneg", &countNonEff_DDOneg, "countNonEff_DDOneg/I");
    
    //DD0 Pos
    
    chipConstTree->Branch("countNonEff_DDOpos", &countNonEff_DDOpos, "countNonEff_DDOpos/I");
    chipConstTree->Branch("numberNonEff_DDOpos", &listNonEffCh_DDOpos);
    chipConstTree->Branch("countDeadCh_DDOpos", &countDeadCh_DDOpos, "countDeadCh_DDOpos/I");
    chipConstTree->Branch("numberDeadCh_DDOpos", &listDeadCh_DDOpos);
    chipConstTree->Branch("RMS_DDOpos", &arrayPDORMS_DDOpos, "RMS_DDOpos[countCh]/F");
    chipConstTree->Branch("Intercept_DDOpos", &arrayPDOInterc_DDOpos, "Intercept_DDOpos[countCh]/F");
    chipConstTree->Branch("Slope_DDOpos", &arrayPDOSlope_DDOpos, "Slope_DDOpos[countCh]/F");
    chipConstTree->Branch("MEAN_DDOpos", &arrayPDOMEAN_DDOpos, "MEAN_DDOpos[countCh]/F");
    chipConstTree->Branch("EntriesMEAN_DDOpos", &arrayPDOEnriesMEAN_DDOpos, "EntriesMEAN_DDOpos[countCh]/I");
    chipConstTree->Branch("tempMax_DDOpos", &tempMax_DDOpos, "tempMax_DDOpos/F");
    chipConstTree->Branch("VDD_V_Max_DDOpos", &VDD_V_Max_DDOpos, "VDD_V_Max_DDOpos/F");
    chipConstTree->Branch("VDD_A_Max_DDOpos", &VDD_A_Max_DDOpos, "VDD_A_Max_DDOpos/F");
    chipConstTree->Branch("VDDD_V_Max_DDOpos", &VDDD_V_Max_DDOpos, "VDDD_V_Max_DDOpos/F");
    chipConstTree->Branch("VDDD_A_Max_DDOpos", &VDDD_A_Max_DDOpos, "VDDD_A_Max_DDOpos/F");
    chipConstTree->Branch("VDDP_V_Max_DDOpos", &VDDP_V_Max_DDOpos, "VDDP_V_Max_DDOpos/F");
    chipConstTree->Branch("VDDP_A_Max_DDOpos", &VDDP_A_Max_DDOpos, "VDDP_A_Max_DDOpos/F");
    chipConstTree->Branch("VDAD_V_Max_DDOpos", &VDAD_V_Max_DDOpos, "VDAD_V_Max_DDOpos/F");
    chipConstTree->Branch("VDAD_A_Max_DDOpos", &VDAD_A_Max_DDOpos, "VDAD_A_Max_DDOpos/F");
    
    // ART  variable
    
//    chipConstTree->Branch("numberBadCh_ART", &listBadCh_ART);
//    chipConstTree->Branch("EntriesART", &arrayEntriesART, "EntriesART[countCh]/I");
//    chipConstTree->Branch("tempMax_ART", &tempMax_ART, "tempMax_ART/F");
//    chipConstTree->Branch("VDD_V_Max_ART", &VDD_V_Max_ART, "VDD_V_Max_ART/F");
//    chipConstTree->Branch("VDD_A_Max_ART", &VDD_A_Max_ART, "VDD_A_Max_ART/F");
//    chipConstTree->Branch("VDDD_V_Max_ART", &VDDD_V_Max_ART, "VDDD_V_Max_ART/F");
//    chipConstTree->Branch("VDDD_A_Max_ART", &VDDD_A_Max_ART, "VDDD_A_Max_ART/F");
//    chipConstTree->Branch("VDDP_V_Max_ART", &VDDP_V_Max_ART, "VDDP_V_Max_ART/F");
//    chipConstTree->Branch("VDDP_A_Max_ART", &VDDP_A_Max_ART, "VDDP_A_Max_ART/F");
//    chipConstTree->Branch("VDAD_V_Max_ART", &VDAD_V_Max_ART, "VDAD_V_Max_ART/F");
//    chipConstTree->Branch("VDAD_A_Max_ART", &VDAD_A_Max_ART, "VDAD_A_Max_ART/F");
//    chipConstTree->Branch("countBadCh_ART", &countBadCh_ART, "countBadCh_ART/I");
    
    // ART neg variable
    
    
    chipConstTree->Branch("countBadCh_ARTneg", &countBadCh_ARTneg, "countBadCh_ARTneg/I");
    chipConstTree->Branch("numberBadCh_ARTneg", &listBadCh_ARTneg);
    chipConstTree->Branch("EntriesARTneg", &arrayEntriesARTneg, "EntriesARTneg[countCh]/I");
    chipConstTree->Branch("tempMax_ARTneg", &tempMax_ARTneg, "tempMax_ARTneg/F");
    chipConstTree->Branch("VDD_V_Max_ARTneg", &VDD_V_Max_ARTneg, "VDD_V_Max_ARTneg/F");
    chipConstTree->Branch("VDD_A_Max_ARTneg", &VDD_A_Max_ARTneg, "VDD_A_Max_ARTneg/F");
    chipConstTree->Branch("VDDD_V_Max_ARTneg", &VDDD_V_Max_ARTneg, "VDDD_V_Max_ARTneg/F");
    chipConstTree->Branch("VDDD_A_Max_ARTneg", &VDDD_A_Max_ARTneg, "VDDD_A_Max_ARTneg/F");
    chipConstTree->Branch("VDDP_V_Max_ARTneg", &VDDP_V_Max_ARTneg, "VDDP_V_Max_ARTneg/F");
    chipConstTree->Branch("VDDP_A_Max_ARTneg", &VDDP_A_Max_ARTneg, "VDDP_A_Max_ARTneg/F");
    chipConstTree->Branch("VDAD_V_Max_ARTneg", &VDAD_V_Max_ARTneg, "VDAD_V_Max_ARTneg/F");
    chipConstTree->Branch("VDAD_A_Max_ARTneg", &VDAD_A_Max_ARTneg, "VDAD_A_Max_ARTneg/F");
    
    // ART pos variable
    
    chipConstTree->Branch("countBadCh_ARTpos", &countBadCh_ARTpos, "countBadCh_ARTpos/I");
    chipConstTree->Branch("numberBadCh_ARTpos", &listBadCh_ARTpos);
    chipConstTree->Branch("EntriesARTpos", &arrayEntriesARTpos, "EntriesARTpos[countCh]/I");
    chipConstTree->Branch("tempMax_ARTpos", &tempMax_ARTpos, "tempMax_ARTpos/F");
    chipConstTree->Branch("VDD_V_Max_ARTpos", &VDD_V_Max_ARTpos, "VDD_V_Max_ARTpos/F");
    chipConstTree->Branch("VDD_A_Max_ARTpos", &VDD_A_Max_ARTpos, "VDD_A_Max_ARTpos/F");
    chipConstTree->Branch("VDDD_V_Max_ARTpos", &VDDD_V_Max_ARTpos, "VDDD_V_Max_ARTpos/F");
    chipConstTree->Branch("VDDD_A_Max_ARTpos", &VDDD_A_Max_ARTpos, "VDDD_A_Max_ARTpos/F");
    chipConstTree->Branch("VDDP_V_Max_ARTpos", &VDDP_V_Max_ARTpos, "VDDP_V_Max_ARTpos/F");
    chipConstTree->Branch("VDDP_A_Max_ARTpos", &VDDP_A_Max_ARTpos, "VDDP_A_Max_ARTpos/F");
    chipConstTree->Branch("VDAD_V_Max_ARTpos", &VDAD_V_Max_ARTpos, "VDAD_V_Max_ARTpos/F");
    chipConstTree->Branch("VDAD_A_Max_ARTpos", &VDAD_A_Max_ARTpos, "VDAD_A_Max_ARTpos/F");
    

    
}
}
