namespace VMMCalibration {

#define FILE_HEADER_STRINGS 60

void ReadHeader(FILE *fp, test_t *test = NULL) {
    char str[2048];
    
    float readData = 0;
    
    for(int i = 0; i < FILE_HEADER_STRINGS; i++) {
        fgets(str, 2048, fp);
        
        if(!test)
            continue;
        
//        if(sscanf(str, "BOARD ID          %f", &readData)) BOARD_ID = readData;
//        else
//            if(sscanf(str, "VMM3 ID#          %f", &readData)) test->chip_id = readData;
//            else
        
        if(sscanf(str, "BASELINE PAUSE         %f",  &readData)) test->bLinePause = readData;
        else
                if(sscanf(str, "SKEW          %f",  &readData)) test->SKEW = readData;
                else
                    if(sscanf(str, "BURST           %f", &readData)) test->pulses = readData;
                    else
                        if(sscanf(str, "TEMP [%f", &readData)) test->Temp = readData;
                        else
                            if(sscanf(str, "VDD  [%f", &readData)) {
                                if (string(str).find("] V") != -1) test->VDD_V = readData;
                                else if (string(str).find("] A") != -1) test->VDD_A = readData;
                            }
                            else
                                if (sscanf(str, "VDDD [%f", &readData)) {
                                    if (string(str).find("] V") != -1) test->VDDD_V = readData;
                                    else if (string(str).find("] A") != -1) test->VDDD_A = readData;
                                }
                                else
                                    if(sscanf(str, "VDDP [%f", &readData)) {
                                        if (string(str).find("] V") != -1) test->VDDP_V = readData;
                                        else if (string(str).find("] A") != -1) test->VDDP_A = readData;
                                    }
                                    else
                                        if (sscanf(str, "VDAD [%f", &readData)) {
                                            if (string(str).find("] V") != -1) test->VDAD_V = readData;
                                            else if (string(str).find("] A") != -1) test->VDAD_A = readData;
                                        }
                                        else
                                            
                                            if (sscanf(str, "P. TIME (st)           %f", &readData)) test->PEAKINGTIME = readData;
                                            else
                                                if (sscanf(str, "GAIN (sg)              %f", &readData)) test->GAIN = readData;
                                                else
                                                    if (sscanf(str, "TAC SLOPE (stc)        %f", &readData)) test->TAC = readData;
                                                    else
                                                        if (sscanf(str, "CRC. THRSHLD DAC (sdt) %f", &readData)) test->THRESHOLD = readData;
                                                        else
                                                            if (sscanf(str, "INT. PULSE DAC (sdp)   %f", &readData)) test->DAC = readData;
                                                            else  {
//                                                                if (string(str).find("CONFIG PATH") != -1) {
//                                                                    string strString(str);// = string(str);
//                                                                    while (strString.find('\\') != -1) {
//                                                                        strString = strString.substr(strString.find('\\') + 1);
//                                                                    }
//                                                                    sprintf(test_mode, "%s", strString.c_str());
//
//                                                                } else
                                                                    if (string(str).find("TEST FLAGS") != -1) {
                                                                    
                                                                    string strString(str);
                                                                    
                                                                    if ((strString.find("ART") != -1)  && isContinuous) isARTCONT = true;
                                                                    if ((strString.find("DDO") != -1)  && isContinuous) isDDOCONT = true;
                                                                    
                                                                    if ((strString.find("ART") != -1)  && isL0) isL0ART = true;
                                                                    if ((strString.find("DDO") != -1)  && isL0) isL0DDO = true;
                                                                    
                                                                    if ((strString.find("ART") != -1)  && isL0POS) isL0POSART = true;
                                                                    if ((strString.find("DDO") != -1)  && isL0POS) isL0POSDDO = true;
                                                                }
//                                                                else {
//                                                                    string strString(str);
//
//                                                                    int posFieldVariale;
//                                                                    posFieldVariale = strString.find("VMM3 PART ID");
//                                                                    if (posFieldVariale != -1) VMM3_PART_ID = strString.substr(18);
//                                                                    posFieldVariale = strString.find("USER ID");
//                                                                    if (posFieldVariale != -1) userID = strString.substr(18);
//                                                                    posFieldVariale = strString.find("DataTesting");
//                                                                    if (posFieldVariale != -1) dataTesting = strString.substr(18);
//                                                                }
                                                                
                                                            }
    }
    
    
}

void ReadHeaderMeanFile(FILE *fp, test_t *test = NULL) {
    char str[2048];
    
    float readData = 0;
    
    for(int i = 0; i < FILE_HEADER_STRINGS; i++) {
        fgets(str, 2048, fp);
        
        if(!test)
            continue;
        
        if(sscanf(str, "BOARD ID          %f", &readData)) BOARD_ID = readData;
        else
            if(sscanf(str, "VMM3 ID#          %f", &readData)) test->chip_id = readData;
        else if (string(str).find("CONFIG PATH") != -1) {
                string strString(str);// = string(str);
                while (strString.find('\\') != -1) {
                strString = strString.substr(strString.find('\\') + 1);
                }
                sprintf(test_mode, "%s", strString.c_str());
            
        } else {
                string strString(str);
                int posFieldVariale;
                posFieldVariale = strString.find("VMM3 PART ID");
                if (posFieldVariale != -1) VMM3_PART_ID = strString.substr(18);
                posFieldVariale = strString.find("USER ID");
                if (posFieldVariale != -1) userID = strString.substr(18);
                posFieldVariale = strString.find("DATA              ");
                if (posFieldVariale != -1) {
                dataTesting = strString.substr(18);
                }
                posFieldVariale = strString.find("FPGA VER");
                if (posFieldVariale != -1) {
                FPGA_VER = strString.substr(18);
                }
            }
                                                                
        
    }
}
}
