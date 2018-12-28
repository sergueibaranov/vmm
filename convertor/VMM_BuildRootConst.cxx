#include <fstream>
#include <iostream>
namespace VMMConvertor {
    
void parseDataTime (char *buff) {
    int y(0), m(0), d(0), c(0), min(0), s(0);
    std::string strParse = buff;

    int posDateTime = strParse.find(".");
    if (posDateTime != -1) {
        y = std::atoi(strParse.substr(posDateTime - 4 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);
        
        std::cout << "\n year  " << y << ": :" << strParse;

        posDateTime = strParse.find(".");
        
        if (posDateTime != -1)
        m = std::atoi(strParse.substr(posDateTime - 2 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);

        posDateTime = strParse.find(" ");

        d = std::atoi(strParse.substr(posDateTime - 2 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);

        posDateTime = strParse.find(":");

        c = std::atoi(strParse.substr(posDateTime - 2 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);

        posDateTime = strParse.find(":");

        min = std::atoi(strParse.substr(posDateTime - 2 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);

        posDateTime = strParse.find(".");

        s = std::atoi(strParse.substr(posDateTime - 2 ,posDateTime).c_str());
        strParse = strParse.substr(posDateTime + 1);


        dataTime->Set(y, m, d, c, min, s);
        dataTimeInt = dataTime->Convert();
    }
}

void buildDataRootTree(std::string basePathcInputFile, std::vector<std::vector<std::string>>  vectorPatchfileTxt, TFile *rootFileConvert) {
    dataTime = new TDatime();
    
    for (int i = 0; i < vectorPatchfileTxt.size(); i++) {
        
         for (int j = 0; j < vectorPatchfileTxt[i].size(); j++) {
        
        if (vectorPatchfileTxt[i][j].find("const_") != -1) {
            
            std::string patchInputFileTxt = basePathcInputFile  + "/" + vectorPatchfileTxt[i][j];
            //std::ifstream (patchInputFileTxt);
            std::cout << "\n now parse " << patchInputFileTxt;
            
            
            
            std::string VMMNUM = "" + vectorPatchfileTxt[i][j].substr(vectorPatchfileTxt[i][j].find("const_") + 6, vectorPatchfileTxt[i][j].find(".txt") - 3);
            VMMNumber = std::stoi(VMMNUM.c_str());
            

            FILE *fileTxtData = fopen(patchInputFileTxt.c_str(), "r");
            
            listNonEffCh_Cont.clear();
            listDeadCh_Cont.clear();
            listNonEffCh_L0.clear();
            listDeadCh_L0.clear();
            listNonEffCh_L0POS.clear();
            listDeadCh_L0POS.clear();
//            listNonEffCh_DDO.clear();
//            listDeadCh_DDO.clear();
            listNonEffCh_DDOneg.clear();
            listDeadCh_DDOneg.clear();
            listNonEffCh_DDOpos.clear();
            listDeadCh_DDOpos.clear();
//            listBadCh_ART.clear();
            listBadCh_ARTneg.clear();
            listBadCh_ARTpos.clear();
            
            listbadCh_POS.clear();
            listbadCh_NEG.clear();

            if (fileTxtData) {
                
                sprintf(userID, "");
                sprintf(testMode, "");
                sprintf(FAILED, "");
                sprintf(partID, "");
                sprintf(FPGA_VER, "");
                
                //sprintf(dataTimeChar, "");
                dataTimeInt = 0;
                
                
                
                
                for (int i = 0; i < 64; i++) {
                    
                    bLinePausePOS = nonCorrectValue;
                    bLinePauseNEG = nonCorrectValue;
                    
                    bLine[i] = nonCorrectValue;
                    bLine_RMS[i] = nonCorrectValue;
                    
                    bLinePos[i] = nonCorrectValue;
                    bLine_RMSPos[i] = nonCorrectValue;
                    
                    arrayPDOInterc_Cont[i] = nonCorrectValue;
                    arrayPDOSlope_Cont[i] = nonCorrectValue;
                    arrayPDORMS_Cont[i] = nonCorrectValue;
                    arrayPDOMEAN_Cont[i] = nonCorrectValue;
                    arrayPDOEntriesMEAN_Cont[i] = nonCorrectValue;
                    arrayTDOInterc_Cont[i] = nonCorrectValue;
                    arrayTDOSlope_Cont[i] = nonCorrectValue;
                    arrayTDORMS_Cont[i] = nonCorrectValue;
                    arrayTDOMEAN_Cont[i] = nonCorrectValue;
                    arrayTDOEntriesMEAN_Cont[i] = nonCorrectValue;
                    
                    arrayPDOInterc_L0[i] = nonCorrectValue;
                    arrayPDOSlope_L0[i] = nonCorrectValue;
                    arrayPDORMS_L0[i] = nonCorrectValue;
                    arrayPDOMEAN_L0[i] = nonCorrectValue;
                    arrayPDOEntriesMEAN_L0[i] = nonCorrectValue;
                    arrayTDOInterc_L0[i] = nonCorrectValue;
                    arrayTDOSlope_L0[i] = nonCorrectValue;
                    arrayTDORMS_L0[i] = nonCorrectValue;
                    arrayTDOMEAN_L0[i] = nonCorrectValue;
                    arrayTDOEntriesMEAN_L0[i] = nonCorrectValue;
                    
                    arrayPDOInterc_L0POS[i] = nonCorrectValue;
                    arrayPDOSlope_L0POS[i] = nonCorrectValue;
                    arrayPDORMS_L0POS[i] = nonCorrectValue;
                    arrayPDOMEAN_L0POS[i] = nonCorrectValue;
                    arrayPDOEntriesMEAN_L0POS[i] = nonCorrectValue;
                    arrayTDOInterc_L0POS[i] = nonCorrectValue;
                    arrayTDOSlope_L0POS[i] = nonCorrectValue;
                    arrayTDORMS_L0POS[i] = nonCorrectValue;
                    arrayTDOMEAN_L0POS[i] = nonCorrectValue;
                    arrayTDOEntriesMEAN_L0POS[i] = nonCorrectValue;
                    
//                    arrayPDOInterc_DDO[i] = nonCorrectValue;
//                    arrayPDOSlope_DDO[i] = nonCorrectValue;
//                    arrayPDORMS_DDO[i] = nonCorrectValue;
//                    arrayPDOMEAN_DDO[i] = nonCorrectValue;
//                    arrayPDOEntriesMEAN_DDO[i] = nonCorrectValue;
                    
                    arrayPDOInterc_DDOneg[i] = nonCorrectValue;
                    arrayPDOSlope_DDOneg[i] = nonCorrectValue;
                    arrayPDORMS_DDOneg[i] = nonCorrectValue;
                    arrayPDOMEAN_DDOneg[i] = nonCorrectValue;
                    arrayPDOEntriesMEAN_DDOneg[i] = nonCorrectValue;
                    
                    arrayPDOInterc_DDOpos[i] = nonCorrectValue;
                    arrayPDOSlope_DDOpos[i] = nonCorrectValue;
                    arrayPDORMS_DDOpos[i] = nonCorrectValue;
                    arrayPDOMEAN_DDOpos[i] = nonCorrectValue;
                    arrayPDOEnriesMEAN_DDOpos[i] = nonCorrectValue;
                    
                    arrayEntriesARTneg[i] = nonCorrectValue;
                    arrayEntriesARTpos[i] = nonCorrectValue;
//                    arrayEntriesART[i] = nonCorrectValue;
                    
                    
                }
                
                bordId = nonCorrectValue;
                // VMMNumber = -1;
                
                tempMax_Cont = nonCorrectValue;
                VDD_V_Max_Cont = nonCorrectValue;
                VDD_A_Max_Cont = nonCorrectValue;
                VDDD_V_Max_Cont = nonCorrectValue;
                VDDD_A_Max_Cont = nonCorrectValue;
                VDDP_V_Max_Cont = nonCorrectValue;
                VDDP_A_Max_Cont = nonCorrectValue;
                VDAD_V_Max_Cont = nonCorrectValue;
                VDAD_A_Max_Cont = nonCorrectValue;
                countNonEff_Cont = 0;
                countDeadCh_Cont = 0;
                
                
                tempMax_L0 = nonCorrectValue;
                VDD_V_Max_L0 = nonCorrectValue;
                VDD_A_Max_L0 = nonCorrectValue;
                VDDD_V_Max_L0 = nonCorrectValue;
                VDDD_A_Max_L0 = nonCorrectValue;
                VDDP_V_Max_L0 = nonCorrectValue;
                VDDP_A_Max_L0 = nonCorrectValue;
                VDAD_V_Max_L0 = nonCorrectValue;
                VDAD_A_Max_L0 = nonCorrectValue;
                countNonEff_L0 = 0;
                countDeadCh_L0 = 0;
                
//                tempMax_DDO = nonCorrectValue;
//                VDD_V_Max_DDO = nonCorrectValue;
//                VDD_A_Max_DDO = nonCorrectValue;
//                VDDD_V_Max_DDO = nonCorrectValue;
//                VDDD_A_Max_DDO = nonCorrectValue;
//                VDDP_V_Max_DDO = nonCorrectValue;
//                VDDP_A_Max_DDO = nonCorrectValue;
//                VDAD_V_Max_DDO = nonCorrectValue;
//                VDAD_A_Max_DDO = nonCorrectValue;
//                countNonEff_DDO = 0;
//                countDeadCh_DDO = 0;
//
                tempMax_DDOneg = nonCorrectValue;
                VDD_V_Max_DDOneg = nonCorrectValue;
                VDD_A_Max_DDOneg = nonCorrectValue;
                VDDD_V_Max_DDOneg = nonCorrectValue;
                VDDD_A_Max_DDOneg = nonCorrectValue;
                VDDP_V_Max_DDOneg = nonCorrectValue;
                VDDP_A_Max_DDOneg = nonCorrectValue;
                VDAD_V_Max_DDOneg = nonCorrectValue;
                VDAD_A_Max_DDOneg = nonCorrectValue;
                countNonEff_DDOneg = 0;
                countDeadCh_DDOneg = 0;
                
                tempMax_DDOpos = nonCorrectValue;
                VDD_V_Max_DDOpos = nonCorrectValue;
                VDD_A_Max_DDOpos = nonCorrectValue;
                VDDD_V_Max_DDOpos = nonCorrectValue;
                VDDD_A_Max_DDOpos = nonCorrectValue;
                VDDP_V_Max_DDOpos = nonCorrectValue;
                VDDP_A_Max_DDOpos = nonCorrectValue;
                VDAD_V_Max_DDOpos = nonCorrectValue;
                VDAD_A_Max_DDOpos = nonCorrectValue;
                countNonEff_DDOpos = 0;
                countDeadCh_DDOpos = 0;
                
//                tempMax_ART = nonCorrectValue;
//                VDD_V_Max_ART = nonCorrectValue;
//                VDD_A_Max_ART = nonCorrectValue;
//                VDDD_V_Max_ART = nonCorrectValue;
//                VDDD_A_Max_ART = nonCorrectValue;
//                VDDP_V_Max_ART = nonCorrectValue;
//                VDDP_A_Max_ART = nonCorrectValue;
//                VDAD_V_Max_ART = nonCorrectValue;
//                VDAD_A_Max_ART = nonCorrectValue;
//                countBadCh_ART = 0;
                
                tempMax_ARTneg = nonCorrectValue;
                VDD_V_Max_ARTneg = nonCorrectValue;
                VDD_A_Max_ARTneg = nonCorrectValue;
                VDDD_V_Max_ARTneg = nonCorrectValue;
                VDDD_A_Max_ARTneg = nonCorrectValue;
                VDDP_V_Max_ARTneg = nonCorrectValue;
                VDDP_A_Max_ARTneg = nonCorrectValue;
                VDAD_V_Max_ARTneg = nonCorrectValue;
                VDAD_A_Max_ARTneg = nonCorrectValue;
                countBadCh_ARTneg = 0;
                
                tempMax_ARTpos = nonCorrectValue;
                VDD_V_Max_ARTpos = nonCorrectValue;
                VDD_A_Max_ARTpos = nonCorrectValue;
                VDDD_V_Max_ARTpos = nonCorrectValue;
                VDDD_A_Max_ARTpos = nonCorrectValue;
                VDDP_V_Max_ARTpos = nonCorrectValue;
                VDDP_A_Max_ARTpos = nonCorrectValue;
                VDAD_V_Max_ARTpos = nonCorrectValue;
                VDAD_A_Max_ARTpos = nonCorrectValue;
                countBadCh_ARTpos = 0;
                
                tempMax_L0POS = nonCorrectValue;
                VDD_V_Max_L0POS = nonCorrectValue;
                VDD_A_Max_L0POS = nonCorrectValue;
                VDDD_V_Max_L0POS = nonCorrectValue;
                VDDD_A_Max_L0POS = nonCorrectValue;
                VDDP_V_Max_L0POS = nonCorrectValue;
                VDDP_A_Max_L0POS = nonCorrectValue;
                VDAD_V_Max_L0POS = nonCorrectValue;
                VDAD_A_Max_L0POS = nonCorrectValue;
                countNonEff_L0POS = 0;
                countDeadCh_L0POS = 0;
                
                
                char buff[1024];
                while(!feof(fileTxtData)) {

                    
                    fgets(buff, 2048, fileTxtData);
                    if (feof(fileTxtData)) break;
                    
//                    if( !fgets(buff, 2048, ) )
//                        continue;
                    
                    std::string strBuff = buff;
                    
                    if (strBuff.find("BOARD_ID" ) != -1 && strBuff.find("L0") == -1) {
                        int chNum;
                        if (sscanf(buff, "BOARD_ID %i", &chNum)) {
                            bordId = chNum;
                        }
                    }
                    
                    if (strBuff.find("status") != -1) {
                        int chNum;
                        if (sscanf(buff, "status %i", &chNum)) {
                            chipStatus = chNum;
                        }
                    }
                    
                    if (strBuff.find("statusNEG") != -1) {
                        int chNum;
                        if (sscanf(buff, "statusNEG %i", &chNum)) {
                            chipStatusNEG = chNum;
                        }
                    }
                    
                    if (strBuff.find("statusPOS") != -1) {
                        int chNum;
                        if (sscanf(buff, "statusPOS %i", &chNum)) {
                            chipStatusPOS = chNum;
                        }
                    }
                    
                    
                    if (strBuff.find("L0_BOARD_ID") != -1 ) {
                        int chNum;
                        if (sscanf(buff, "L0_BOARD_ID %i", &chNum)) {
                            bordId = chNum;
                        }
                    }
                    
                    if (strBuff.find("BLineneg") != -1 && strBuff.find("pos") == -1) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "BLineneg%i %f", &chNum, &value) == 2) {
                            bLine[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("BLine_RMSneg") != -1 && strBuff.find("pos") == -1) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "BLine_RMSneg%i %f", &chNum, &value) == 2) {
                            bLine_RMS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("BLinepos") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "BLinepos%i %f", &chNum, &value) == 2) {
                            bLinePos[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("BLine_RMSpos") != -1) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "BLine_RMSpos%i %f", &chNum, &value) == 2) {
                            bLine_RMSPos[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_BOARD_ID") != -1 ) {
                        int chNum;
                        if (sscanf(buff, "L0_BOARD_ID %i", &chNum)) {
                            bordId = chNum;
                        }
                    }
                    
//                    bLinePausePOS = nonCorrectValue;
//                    bLinePausePOS = nonCorrectValue;
                    
                    if ( (strBuff.find("BLinePause") != -1) && (strBuff.find("pos") == -1)) {
                        float value;
                        if (sscanf(buff, "BLinePause %f", &value) == 1) {
                            bLinePauseNEG = value;
                        }
                    }
                    
                    if (strBuff.find("BLinePausepos") != -1 ) {
                        float value;
                        if (sscanf(buff, "BLinePausepos %f", &value) == 1) {
                            bLinePausePOS = value;
                        }
                    }
                    
                    if (strBuff.find("L0_TestMode") != -1 ) {
                        sscanf(buff, "L0_TestMode %s", testMode);
                    }
                    
                    if (strBuff.find("TestMode") != -1 && strBuff.find("L0") == -1) {
                        sscanf(buff, "TestMode %s", testMode);
                    }
                    
                    
                    if (strBuff.find("FAILED") != -1) {
                        sscanf(buff, "FAILED %s", FAILED);
                    }
                    
                    
                    if (strBuff.find("USER_ID") != -1 ) {
                        sscanf(buff, "USER_ID %s", userID);
                    }
                    
                    if (strBuff.find("FPGA_VER") != -1 ) {
                        sscanf(buff, "FPGA_VER %s", FPGA_VER);
                    }
                    
                    if (strBuff.find("L0_VMM3_PART_ID") != -1 ) {
                        sscanf(buff, "L0_VMM3_PART_ID %s", partID);
                    }
                    
                    if (strBuff.find("VMM3_PART_ID") != -1 && strBuff.find("L0") == -1) {
                        sscanf(buff, "VMM3_PART_ID %s", partID);
                    }
                    
                    // DateTime
                    
                    if (strBuff.find("DataTesting") != -1 ) {
                        parseDataTime(buff);
                        //
                    }
                    
                    if (strBuff.find("pos_DEAD_CHANNELS") != -1) {
                        int chNum;
                        if (sscanf(buff, "pos_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                listbadCh_POS.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 2).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                    }
                    
                    if (strBuff.find("neg_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        if (sscanf(buff, "neg_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                listbadCh_NEG.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 2).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                    }
                    
                    ////////// cont
                    
                    if (strBuff.find("CONT_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "CONT_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listDeadCh_Cont.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countDeadCh_Cont  = coutNum;
                    }
                    if (strBuff.find("CONT_NON_EFFICIENT_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "CONT_NON_EFFICIENT_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listNonEffCh_Cont.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                            
                        }
                        countNonEff_Cont = coutNum;
                    }
                    if (strBuff.find("CONT_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDORMS_Cont[chNum] = value;
                        }
                    }
                    if (strBuff.find("CONT_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOInterc_Cont[chNum] = value;
                        }
                    }
                    if (strBuff.find("CONT_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOSlope_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_ADC_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOMEAN_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_ADC_meanEntries_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_ADC_meanEntries_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOEntriesMEAN_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_RMS_TDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_RMS_TDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDORMS_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_TDO_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_TDO_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOInterc_Cont[chNum] = value;
                        }
                    }
                    if (strBuff.find("CONT_TDO_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_TDO_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOSlope_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_TDO_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_TDO_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOMEAN_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_TDO_meanEntries_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "CONT_TDO_meanEntries_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOEntriesMEAN_Cont[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_Temp_Max %f", &value)) {
                            tempMax_Cont = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDD_V_Max %f", &value)) {
                            VDD_V_Max_Cont = value;
                        }
                    }
                    
                    if (strBuff.find("CONT_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDD_A_Max %f", &value)) {
                            VDD_A_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_Cont = value;
                        }
                    }
                    if (strBuff.find("CONT_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "CONT_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_Cont = value;
                        }
                    }
                    
                    ////////// L0
                    if (strBuff.find("L0_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "L0_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listDeadCh_L0.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countDeadCh_L0  = coutNum;
                    }
                    if (strBuff.find("L0_NON_EFFICIENT_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "L0_NON_EFFICIENT_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listNonEffCh_L0.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                            
                        }
                        countNonEff_L0 = coutNum;
                    }
                    
                    if (strBuff.find("L0_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDORMS_L0[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOInterc_L0[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOSlope_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_ADC_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOMEAN_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_ADC_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "L0_ADC_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayPDOEntriesMEAN_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_RMS_TDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_RMS_TDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDORMS_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_TDO_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_TDO_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOInterc_L0[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0_TDO_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_TDO_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOSlope_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_TDO_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0_TDO_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOMEAN_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_TDO_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "L0_TDO_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayTDOEntriesMEAN_L0[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_Temp_Max %f", &value)) {
                            tempMax_L0 = value;
                        }
                    }
                    
                    if (strBuff.find("L0_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDD_V_Max %f", &value)) {
                            VDD_V_Max_L0 = value;
                        }
                    }
                    
                    if (strBuff.find("L0_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDD_A_Max %f", &value)) {
                            VDD_A_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_L0 = value;
                        }
                    }
                    if (strBuff.find("L0_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_L0 = value;
                        }
                    }
                    
                    ////////// L0POS
                    if (strBuff.find("L0pos_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "L0pos_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listDeadCh_L0POS.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countDeadCh_L0POS  = coutNum;
                    }
                    if (strBuff.find("L0pos_NON_EFFICIENT_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "L0pos_NON_EFFICIENT_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listNonEffCh_L0POS.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                            
                        }
                        countNonEff_L0POS = coutNum;
                    }
                    if (strBuff.find("L0pos_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDORMS_L0POS[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0pos_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOInterc_L0POS[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0pos_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOSlope_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_ADC_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOMEAN_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_ADC_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "L0pos_ADC_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayPDOEntriesMEAN_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDORMS_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_TDO_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_TDO_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOInterc_L0POS[chNum] = value;
                        }
                    }
                    if (strBuff.find("L0pos_TDO_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_TDO_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOSlope_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_TDO_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "L0pos_TDO_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayTDOMEAN_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_TDO_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "L0pos_TDO_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayTDOEntriesMEAN_L0POS[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_Temp_Max %f", &value)) {
                            tempMax_L0POS = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDD_V_Max %f", &value)) {
                            VDD_V_Max_L0POS = value;
                        }
                    }
                    
                    if (strBuff.find("L0pos_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDD_A_Max %f", &value)) {
                            VDD_A_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_L0POS = value;
                        }
                    }
                    if (strBuff.find("L0pos_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "L0pos_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_L0POS = value;
                        }
                    }
//
//                    ////////// DDO
//                    if (strBuff.find("DDOneg_DEAD_CHANNELS") != -1 ) {
//                        int chNum;
//                        Int_t coutNum = 0;
//                        if (sscanf(buff, "DDOneg_DEAD_CHANNELS %i", &chNum)) {
//                            do {
//                                coutNum++;
//                                listDeadCh_DDO.push_back(chNum);
//                                if (strBuff.find(",") == -1 ) break;
//                                else {
//                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
//                                    strBuff = buff;
//                                }
//                            }  while (sscanf(buff, "%i", &chNum));
//                        }
//                        countDeadCh_DDO  = coutNum;
//                    }
//                    if (strBuff.find("DDOneg_NON_EFFICIENT_CHANNELS") != -1 ) {
//                        int chNum;
//                        Int_t coutNum = 0;
//                        if (sscanf(buff, "DDOneg_NON_EFFICIENT_CHANNELS %i", &chNum)) {
//                            do {
//                                coutNum++;
//                                listNonEffCh_DDO.push_back(chNum);
//                                if (strBuff.find(",") == -1 ) break;
//                                else {
//                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
//                                    strBuff = buff;
//                                }
//                            }  while (sscanf(buff, "%i", &chNum));
//
//                        }
//                        countNonEff_DDO = coutNum;
//                    }
//                    if (strBuff.find("DDOneg_RMS_PDO_CHN") != -1 ) {
//                        int chNum;
//                        float value;
//                        if (sscanf(buff, "DDOneg_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
//                            arrayPDORMS_DDO[chNum] = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_intercept_CHN") != -1 ) {
//                        int chNum;
//                        float value;
//                        if (sscanf(buff, "DDOneg_intercept_CHN%i %f", &chNum, &value) == 2) {
//                            arrayPDOInterc_DDO[chNum] = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_slope_CHN") != -1 ) {
//                        int chNum;
//                        float value;
//                        if (sscanf(buff, "DDOneg_slope_CHN%i %f", &chNum, &value) == 2) {
//                            arrayPDOSlope_DDO[chNum] = value;
//                        }
//                    }
//
//                    if (strBuff.find("DDOneg_ADC_mean_CHN") != -1 ) {
//                        int chNum;
//                        float value;
//                        if (sscanf(buff, "DDOneg_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
//                            arrayPDOMEAN_DDO[chNum] = value;
//                        }
//                    }
//
//                    if (strBuff.find("DDOneg_ADC_meanEntries_CHN") != -1 ) {
//                        int chNum;
//                        int value;
//                        if (sscanf(buff, "DDOneg_ADC_meanEntries_CHN%i %i", &chNum, &value) == 2) {
//                            arrayPDOEntriesMEAN_DDO[chNum] = value;
//                        }
//                    }
//
//                    if (strBuff.find("DDOneg_Temp_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_Temp_Max %f", &value)) {
//                            tempMax_DDOneg = value;
//                        }
//                    }
//
//
//
//                    if (strBuff.find("DDOneg_VDD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDD_V_Max %f", &value)) {
//                            VDD_V_Max_DDOneg = value;
//                        }
//                    }
//
//                    if (strBuff.find("DDOneg_VDD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDD_A_Max %f", &value)) {
//                            VDD_A_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDDD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDDD_V_Max %f", &value)) {
//                            VDDD_V_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDDD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDDD_A_Max %f", &value)) {
//                            VDDD_A_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDDP_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDDP_V_Max %f", &value)) {
//                            VDDP_V_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDDP_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDDP_A_Max %f", &value)) {
//                            VDDP_A_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDAD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDAD_V_Max %f", &value)) {
//                            VDAD_V_Max_DDO = value;
//                        }
//                    }
//                    if (strBuff.find("DDOneg_VDAD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "DDOneg_VDAD_A_Max %f", &value)) {
//                            VDAD_A_Max_DDO = value;
//                        }
//                    }
                    
                    //// DDOneg
                    
                    if (strBuff.find("DDOneg_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "DDOneg_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listDeadCh_DDOneg.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countDeadCh_DDOneg  = coutNum;
                    }
                    if (strBuff.find("DDOneg_NON_EFFICIENT_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "DDOneg_NON_EFFICIENT_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listNonEffCh_DDOneg.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                            
                        }
                        countNonEff_DDOneg = coutNum;
                    }
                    if (strBuff.find("DDOneg_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOneg_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDORMS_DDOneg[chNum] = value;
                        }
                    }
                    if (strBuff.find("DDOneg_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOneg_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOInterc_DDOneg[chNum] = value;
                        }
                    }
                    if (strBuff.find("DDOneg_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOneg_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOSlope_DDOneg[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOneg_ADC_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOneg_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOMEAN_DDOneg[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOneg_ADC_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "DDOneg_ADC_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayPDOEntriesMEAN_DDOneg[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOneg_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_Temp_Max %f", &value)) {
                            tempMax_DDOneg = value;
                        }
                    }
                    
                    
                    
                    if (strBuff.find("DDOneg_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDD_V_Max %f", &value)) {
                            VDD_V_Max_DDOneg = value;
                        }
                    }
                    
                    if (strBuff.find("DDOneg_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDD_A_Max %f", &value)) {
                            VDD_A_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_DDOneg = value;
                        }
                    }
                    if (strBuff.find("DDOneg_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOneg_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_DDOneg = value;
                        }
                    }
                    
                    
                    //// DDO POS
                    
                    if (strBuff.find("DDOpos_DEAD_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "DDOpos_DEAD_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listDeadCh_DDOpos.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countDeadCh_DDOpos  = coutNum;
                    }
                    if (strBuff.find("DDOpos_NON_EFFICIENT_CHANNELS") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "DDOpos_NON_EFFICIENT_CHANNELS %i", &chNum)) {
                            do {
                                coutNum++;
                                listNonEffCh_DDOpos.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                            
                        }
                        countNonEff_DDOpos = coutNum;
                    }
                    if (strBuff.find("DDOpos_RMS_PDO_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOpos_RMS_PDO_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDORMS_DDOpos[chNum] = value;
                        }
                    }
                    if (strBuff.find("DDOpos_intercept_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOpos_intercept_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOInterc_DDOpos[chNum] = value;
                        }
                    }
                    if (strBuff.find("DDOpos_slope_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOpos_slope_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOSlope_DDOpos[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOpos_ADC_mean_CHN") != -1 ) {
                        int chNum;
                        float value;
                        if (sscanf(buff, "DDOpos_ADC_mean_CHN%i %f", &chNum, &value) == 2) {
                            arrayPDOMEAN_DDOpos[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOpos_ADC_meanEntries_CHN") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "DDOpos_ADC_meanEntries_CHN%i %i", &chNum, &value) == 2) {
                            arrayPDOEnriesMEAN_DDOpos[chNum] = value;
                        }
                    }
                    
                    if (strBuff.find("DDOpos_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_Temp_Max %f", &value)) {
                            tempMax_DDOpos = value;
                        }
                    }
                    
                    
                    
                    if (strBuff.find("DDOpos_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDD_V_Max %f", &value)) {
                            VDD_V_Max_DDOpos = value;
                        }
                    }
                    
                    if (strBuff.find("DDOpos_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDD_A_Max %f", &value)) {
                            VDD_A_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_DDOpos = value;
                        }
                    }
                    if (strBuff.find("DDOpos_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "DDOpos_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_DDOpos = value;
                        }
                    }
                    
//                    ////////// ART
//                    if (strBuff.find("ARTneg_Bad_CH") != -1 ) {
//                        int chNum;
//                        Int_t coutNum = 0;
//                        if (sscanf(buff, "ARTneg_Bad_CH %i", &chNum)) {
//                            do {
//                                coutNum++;
//                                listBadCh_ART.push_back(chNum);
//                                if (strBuff.find(",") == -1 ) break;
//                                else {
//                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
//                                    strBuff = buff;
//                                }
//                            }  while (sscanf(buff, "%i", &chNum));
//                        }
//                        countBadCh_ART  = coutNum;
//                    }
//                    if (strBuff.find("ARTneg_Temp_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_Temp_Max %f", &value)) {
//                            tempMax_ART = value;
//                        }
//                    }
//
//                    if (strBuff.find("ARTneg_VDD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDD_V_Max %f", &value)) {
//                            VDD_V_Max_ART = value;
//                        }
//                    }
//
//                    if (strBuff.find("ARTneg_VDD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDD_A_Max %f", &value)) {
//                            VDD_A_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDDD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDDD_V_Max %f", &value)) {
//                            VDDD_V_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDDD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDDD_A_Max %f", &value)) {
//                            VDDD_A_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDDP_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDDP_V_Max %f", &value)) {
//                            VDDP_V_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDDP_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDDP_A_Max %f", &value)) {
//                            VDDP_A_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDAD_V_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDAD_V_Max %f", &value)) {
//                            VDAD_V_Max_ART = value;
//                        }
//                    }
//                    if (strBuff.find("ARTneg_VDAD_A_Max") != -1 ) {
//                        float value;
//                        if (sscanf(buff, "ARTneg_VDAD_A_Max %f", &value)) {
//                            VDAD_A_Max_ART = value;
//                        }
//                    }
//
//                    if (strBuff.find("ARTnegEntries_CH") != -1 ) {
//                        int chNum;
//                        int value;
//                        if (sscanf(buff, "ARTnegEntries_CH%i %i", &chNum, &value) == 2) {
//                            arrayEntriesART[chNum] = value;
//                        }
//                    }
                    
                    
                    ////////// ART L0
                    if (strBuff.find("ARTneg_Bad_CH") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "ARTneg_Bad_CH %i", &chNum)) {
                            do {
                                coutNum++;
                                listBadCh_ARTneg.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countBadCh_ARTneg  = coutNum;
                    }
                    
                    if (strBuff.find("ARTneg_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_Temp_Max %f", &value)) {
                            tempMax_ARTneg = value;
                        }
                    }
                    
                    if (strBuff.find("ARTneg_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDD_V_Max %f", &value)) {
                            VDD_V_Max_ARTneg = value;
                        }
                    }
                    
                    if (strBuff.find("ARTneg_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDD_A_Max %f", &value)) {
                            VDD_A_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_ARTneg = value;
                        }
                    }
                    if (strBuff.find("ARTneg_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTneg_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_ARTneg = value;
                        }
                    }
                    
                    if (strBuff.find("ARTnegEntries_CH") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "ARTnegEntries_CH%i %i", &chNum, &value) == 2) {
                            arrayEntriesARTneg[chNum] = value;
                        }
                    }
                    
                    ////////// ART L0 POS
                    
                    if (strBuff.find("ARTpos_Bad_CH") != -1 ) {
                        int chNum;
                        Int_t coutNum = 0;
                        if (sscanf(buff, "ARTpos_Bad_CH %i", &chNum)) {
                            do {
                                coutNum++;
                                listBadCh_ARTpos.push_back(chNum);
                                if (strBuff.find(",") == -1 ) break;
                                else {
                                    strcpy(buff, strBuff.substr(strBuff.find(",") + 1).c_str());
                                    strBuff = buff;
                                }
                            }  while (sscanf(buff, "%i", &chNum));
                        }
                        countBadCh_ARTpos  = coutNum;
                    }
                    
                    if (strBuff.find("ARTpos_Temp_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_Temp_Max %f", &value)) {
                            tempMax_ARTpos = value;
                        }
                    }
                    
                    if (strBuff.find("ARTpos_VDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDD_V_Max %f", &value)) {
                            VDD_V_Max_ARTpos = value;
                        }
                    }
                    
                    if (strBuff.find("ARTpos_VDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDD_A_Max %f", &value)) {
                            VDD_A_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDDD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDDD_V_Max %f", &value)) {
                            VDDD_V_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDDD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDDD_A_Max %f", &value)) {
                            VDDD_A_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDDP_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDDP_V_Max %f", &value)) {
                            VDDP_V_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDDP_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDDP_A_Max %f", &value)) {
                            VDDP_A_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDAD_V_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDAD_V_Max %f", &value)) {
                            VDAD_V_Max_ARTpos = value;
                        }
                    }
                    if (strBuff.find("ARTpos_VDAD_A_Max") != -1 ) {
                        float value;
                        if (sscanf(buff, "ARTpos_VDAD_A_Max %f", &value)) {
                            VDAD_A_Max_ARTpos = value;
                        }
                    }
                    
                    if (strBuff.find("ARTposEntries_CH") != -1 ) {
                        int chNum;
                        int value;
                        if (sscanf(buff, "ARTposEntries_CH%i %i", &chNum, &value) == 2) {
                            arrayEntriesARTpos[chNum] = value;
                        }
                    }
                }
                
                fclose(fileTxtData);
                
            }
            
            
            if (tempMax_Cont == -1) {
                countDeadCh_Cont = -1;
                countNonEff_Cont = -1;
            }
            
            if (tempMax_L0 == -1) {
                countDeadCh_L0 = -1;
                countNonEff_L0 = -1;
            }
            
            if (tempMax_L0POS == -1) {
                countDeadCh_L0POS = -1;
                countNonEff_L0POS = -1;
            }
            
//            if (tempMax_DDO == -1) {
//                countDeadCh_DDO = -1;
//                countNonEff_DDO = -1;
//            }
            
            if (tempMax_DDOneg == -1) {
                countDeadCh_DDOneg = -1;
                countNonEff_DDOneg = -1;
            }
            
            if (tempMax_DDOpos == -1) {
                countDeadCh_DDOpos = -1;
                countNonEff_DDOpos = -1;
            }
            
            
            if (tempMax_ARTneg == -1) {
                countBadCh_ARTneg = -1;
            }
            
            if (tempMax_ARTpos == -1) {
                countBadCh_ARTpos = -1;
            }
            
           
        }
             
             
        
//        rootFileConvert->Write();
//        rootFileConvert->Print();
//
//        delete chipConstTree;
             
         }
        
         chipConstTree->Fill();
    }
    
    delete dataTime;
    
}
    
}
