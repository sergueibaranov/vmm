namespace cuts {
    float BlinePauseAll = 0;
    void clearALLBadCh() {
        FAILED = "";
        badCH_BlineNEG.clear();
        badCH_BlinePOS.clear();
        
        badCH_ARTNEG.clear();
        badCH_ARTPOS.clear();
        
        badCH_MEANDDOL0.clear();
        badCH_MEANDDOL0POS.clear();
        
        badCH_MEANL0.clear();
        badCH_MEANL0POS.clear();
        
        badCH_MEANTDOL0.clear();
        badCH_MEANTDOL0POS.clear();
        
        badCH_EntriesL0.clear();
        badCH_EntriesL0POS.clear();
        
        badSumCurL0 = false;
        badSumCurL0pos = false;
        
        badcutVDDD_L0 = false;
        badcutVDD_L0 = false;
        badcutVDDP_L0 = false;
        badcutVDAD_L0 = false;
        
        badcutVDDD_L0POS = false;
        badcutVDD_L0POS = false;
        badcutVDDP_L0POS = false;
        badcutVDAD_L0POS = false;
        
        isGoodPOS = true;
        isGoodNEG = true;
        
        chipStatus = 0;
        
        chipStatusNEG = -1;
        chipStatusPOS = -1;
        
        BlinePauseAll = 0;
    }
    
    void analysisEntries(int *Entries, std::string configName) {
        
        if ( (configName.find("L0pos") != -1)) {
            for (int i = 0; i < 64; i++) {
                if (Entries[i] < cut_entry) badCH_EntriesL0POS.push_back(i);
            }
        }
        
        if ( (configName.find("L0") != -1) && (configName.find("pos") == -1)) {
            for (int i = 0; i < 64; i++) {
                if (Entries[i] < cut_entry) badCH_EntriesL0.push_back(i);
            }
        }
    }
    
    void analysisCutsTDO(float *TDOMEAN, std::string configName) {
        
        if ( (configName.find("L0pos") != -1) && cutTDOMEAN_L0POS) {
            for (int i = 0; i < 64; i++) {
                if ((TDOMEAN[i] < cut_TDOMEAN_L0POS_min) || (TDOMEAN[i] > cut_TDOMEAN_L0POS_max)) badCH_MEANTDOL0POS.push_back(i);
            }
        }
        
        if ((configName.find("L0") != -1) && (configName.find("pos") == -1) && cutTDOMEAN_L0) {
            for (int i = 0; i < 64; i++) {
                if ((TDOMEAN[i] < cut_TDOMEAN_L0_min) || (TDOMEAN[i] > cut_TDOMEAN_L0_max)) badCH_MEANTDOL0.push_back(i);
            }
            
        }
        
    }
    
    void analysisCutsADC(float *apmlMEAN, std::string configName) {
        
//        std::cout << "\n +++++++++++++ " << configName;
//
//        for (int i = 0; i < 64; i++) {
//            std::cout << "  " << apmlMEAN[i];
//        }
        
        if ((configName.find("DDO") == -1) && (configName.find("L0") != -1) && cutPDOMEAN_L0 && (configName.find("pos") == -1)) {
            
            for (int i = 0; i < 64; i++) {
                if ((apmlMEAN[i] < cut_PDOMEAN_L0_min) || (apmlMEAN[i] > cut_PDOMEAN_L0_max)) badCH_MEANL0.push_back(i);
            }
        }

        if ((configName.find("DDO") != -1) && cutPDOMEAN_DDOL0 && (configName.find("pos") == -1) && (configName.find("neg") != -1)) {
            for (int i = 0; i < 64; i++) {
                if ((apmlMEAN[i] < cut_DDOL0_MEAN_min) || (apmlMEAN[i] > cut_DDOL0_MEAN__max)) badCH_MEANDDOL0.push_back(i);
            }
        }
        
        
        if ((configName.find("DDO") == -1) && (configName.find("L0pos") != -1) && cutPDOMEAN_L0POS) {
            
            for (int i = 0; i < 64; i++) {
                if ((apmlMEAN[i] < cut_PDOMEAN_L0POS_min) || (apmlMEAN[i] > cut_PDOMEAN_L0POS_max)) badCH_MEANL0POS.push_back(i);
            }
            
        }
        
        if ((configName.find("DDO") != -1) && (configName.find("pos") != -1) && cutPDOMEAN_DDOL0pos) {
            for (int i = 0; i < 64; i++) {
                if ((apmlMEAN[i] < cut_DDOL0POS_MEAN_min) || (apmlMEAN[i] > cut_DDOL0POS_MEAN__max)) badCH_MEANDDOL0POS.push_back(i);
            }
        }
        
//        if ((configName.find("pos") == -1) && cutPDOMEAN_DDOL0 && (configName.find("DDO") != -1)) {
//            for (int i = 0; i < 64; i++) {
//                if ((apmlMEAN[i] < cut_DDOL0POS_MEAN_min) || (apmlMEAN[i] > cut_DDOL0POS_MEAN__max)) {
//                    badCH_MEANDDOL0POS.push_back(i);
//                    badCH_MEANDDOL0.push_back(i);
//                }
//            }
//        }
    
    }
    
    // analisis curren L0 pos and neg
    

    
    void AnCurL0PN(std::string configurationName) {
        
        
        
        
        if (cutsumcur) {
            float sumCurrent = VMMCalibration::VDD_A_Max + VMMCalibration::VDDD_A_Max + VMMCalibration::VDDP_A_Max + VMMCalibration::VDAD_A_Max;
            if (configurationName.find("pos") != -1 && configurationName.find("DDO") == -1) {
                if (cur_minL0 > sumCurrent || sumCurrent > cur_maxL0) badSumCurL0pos = false;
            }
            
            if (configurationName.find("pos") == -1 && configurationName.find("DDO") == -1) {
                if (cur_minL0pos > sumCurrent || cur_maxL0pos > cur_maxL0) badSumCurL0 = false;
            }
        }
        
        if (configurationName.find("pos") == -1 && configurationName.find("DDO") == -1) {
            
            if (cutVDDD_L0) {
                if ((VMMCalibration::VDDD_A_Max < mincurrentVDDD) || (VMMCalibration::VDDD_A_Max > over_currentVDDD)) badcutVDDD_L0 = true;
            }
            
            if (cutVDD_L0) {
                if ((VMMCalibration::VDD_A_Max < mincurrentVDD) || (VMMCalibration::VDD_A_Max > over_currentVDD) ) badcutVDD_L0 = true;
                
            }
            
            if (cutVDDP_L0) {
                if ((VMMCalibration::VDDP_A_Max < mincurrentVDDP) || (VMMCalibration::VDDP_A_Max > over_currentVDDP)) badcutVDDP_L0 = true;
            }
            
            if (cutVDAD_L0) {
            
                if ((VMMCalibration::VDAD_A_Max < mincurrentVDAD) || (VMMCalibration::VDAD_A_Max > over_currentVDAD)) badcutVDAD_L0 = true;
            }
                
            }
            else
            if (configurationName.find("pos") != -1 && configurationName.find("DDO") == -1) {
                
                if (cutVDDD_L0POS) {
                    if ((VMMCalibration::VDDD_A_Max < mincurrentVDDD_L0POS) || (VMMCalibration::VDDD_A_Max > over_currentVDDD_L0POS)) badcutVDDD_L0POS = true;
                }
                
                if (cutVDD_L0POS) {
                    if ((VMMCalibration::VDD_A_Max < mincurrentVDD_L0POS) || (VMMCalibration::VDD_A_Max > over_currentVDD_L0POS) ) badcutVDD_L0POS = true;
                    
                }
                
                if (cutVDDP_L0POS) {
                    if ((VMMCalibration::VDDP_A_Max < mincurrentVDDP_L0POS) || (VMMCalibration::VDDP_A_Max > over_currentVDDP_L0POS)) badcutVDDP_L0POS = true;
                }
                
                if (cutVDAD_L0POS) {
                    if ((VMMCalibration::VDAD_A_Max < mincurrentVDAD_L0POS) || (VMMCalibration::VDAD_A_Max > over_currentVDAD_L0POS)) badcutVDDP_L0POS = true;
                    
                }
            
        }
        
    }
    

    
    void AnalysisCutsBline(float *meanBline ,std::string configName, float BlinePause = 0) {
        
        BlinePauseAll = BlinePause;
            if ((configName.find("BLine") != -1) && (configName.find("pos") == -1) && cutBLINE) {
                    for (int i = 0; i < 64; i++) {
                            if ((meanBline[i] > cut_bline_max) || (meanBline[i] < cut_bline_min)) {
                                badCH_BlineNEG.push_back(i);
                                badCH_BlinePOS.push_back(i);
                            }
                    }
        }
        
        if ((configName.find("BLine") != -1) && (configName.find("pos") != -1) && cutBLINEPOS && BlinePause > 0) {
            badCH_BlinePOS.clear();
                for (int i = 0; i < 64; i++) {
                    if ((meanBline[i] > cut_bline_max) || (meanBline[i] < cut_bline_min)) {
                        badCH_BlinePOS.push_back(i);
                    }
                }
            
        }
    }
    
    void BlileFail() {
        for (int i = 0; i < 64; i++) {
            badCH_BlineNEG.push_back(i);
            badCH_BlinePOS.push_back(i);
        }
    }
    
    void AnalysisCutsART(bool *ch, std::string configName) {
        if ((configName.find("pos") != -1) && (configName.find("ART") != -1) && cutARTL0pos) {
            for (int i = 0; i < 64; i++) {
                if (!ch[i]) badCH_ARTPOS.push_back(i);
            }
        }
        
        if (cutARTL0 && (configName.find("ART") != -1) && configName.find("neg") != -1) {
                for (int i = 0; i < 64; i++) {
                    if (!ch[i]) badCH_ARTNEG.push_back(i);
                }
            }
        
        
//        if ((configName.find("L0") == -1)) {
//
//            for (int i = 0; i < 64; i++) {
//                if (!ch[i]) {
//                    badCH_ARTPOS.push_back(i);
//                    badCH_ARTNEG.push_back(i);
//                }
//            }
//        }
        
    }
    
    int chipsStatus() {
        
        int status;
        
        for (int i = 0; i < 64; i++) {
            badCHPOS[i] = 0;
            badCHNEG[i] = 0;
        }
        
        if (badcutVDDD_L0 || badcutVDD_L0 || badcutVDDP_L0 || badcutVDAD_L0 || badSumCurL0) {
            isGoodNEG = false;
        }
        
        int countbadCHNeg = 0;
        
        //if (isGoodNEG) {
        if (1) {
            
                for (int i = 0; i < badCH_BlineNEG.size(); i++) {
                    badCHNEG[badCH_BlineNEG[i]] = 1;
                    badCHPOS[badCH_BlineNEG[i]] = 1;
                }
            
                for (int i = 0; i < badCH_ARTNEG.size(); i++) {
                    badCHNEG[badCH_ARTNEG[i]] = 1;
                }
            
                for (int i = 0; i < badCH_MEANDDOL0.size(); i++) {
                    badCHNEG[badCH_MEANDDOL0[i]] = 1;
                }
            
                for (int i = 0; i < badCH_MEANL0.size(); i++) {
                     badCHNEG[badCH_MEANL0[i]] = 1;
                }

                for (int i = 0; i < badCH_MEANTDOL0.size(); i++) {
                     badCHNEG[badCH_MEANTDOL0[i]] = 1;
                }

                for (int i = 0; i < badCH_EntriesL0.size(); i++) {
                    badCHNEG[badCH_EntriesL0[i]] = 1;
                }
            
            
            
            for (int j = 0; j < 64; j++) {
                if (badCHNEG[j]) countbadCHNeg++;
            }
            
            if (countbadCHNeg > limit_max_ch) {
                isGoodNEG = false;
            }
            
        }
        
        if (badcutVDDD_L0POS || badcutVDD_L0POS || badcutVDDP_L0POS || badcutVDAD_L0POS || badSumCurL0pos) {
            isGoodPOS = false;
        }
        
        int countbadCHPos = 0;
        
        //if (isGoodPOS) {
         if (1) {
            
                for (int i = 0; i < badCH_BlinePOS.size(); i++) {
                    badCHPOS[badCH_BlinePOS[i]] = 1;
                }
            
                for (int i = 0; i < badCH_ARTPOS.size(); i++) {
                    badCHPOS[badCH_ARTPOS[i]] = 1;
                }
            
                for (int i = 0; i < badCH_MEANDDOL0POS.size(); i++) {
                    badCHPOS[badCH_MEANDDOL0POS[i]] = 1;
                }
            
                for (int i = 0; i < badCH_MEANL0POS.size(); i++) {
                    badCHPOS[badCH_MEANL0POS[i]] = 1;
                }
            
            
                for (int i = 0; i < badCH_MEANTDOL0POS.size(); i++) {
                    badCHPOS[badCH_MEANTDOL0POS[i]] = 1;
                }
            
                for (int i = 0; i < badCH_EntriesL0POS.size(); i++) {
                    badCHPOS[badCH_EntriesL0POS[i]] = 1;
                }
            
            
            for (int j = 0; j < 64; j++) {
                if (badCHPOS[j]) countbadCHPos++;
            }
            
            if (countbadCHPos > limit_max_ch) {
                isGoodPOS = false;
            }
        }
        
        if (isGoodPOS && isGoodNEG) {
            if ((countbadCHPos == 0) && (countbadCHNeg == 0)) status = 6;
            else {
                if (countbadCHNeg == 0) status = 3;
                else if (countbadCHPos == 0) status = 4;
                else status = 5;
            }
        }
        else if (isGoodNEG) {
            if (countbadCHNeg == 0 && countbadCHPos < 3) status = 3;
            else status = 1;
        }
        else if (isGoodPOS) {
            if (countbadCHPos == 0 && countbadCHNeg < 3) status = 4;
            else status = 2;
        }
        else status = 0;
        
        chipStatus = status;
        
        ///////
        
        if (isGoodNEG) {
            if (countbadCHNeg == 0) chipStatusNEG = 2;
            else chipStatusNEG = 1;
        } else chipStatusNEG = 0;
        
        if (isGoodPOS) {
            if (countbadCHPos == 0) chipStatusPOS = 2;
            else chipStatusPOS = 1;
        }
        else chipStatusPOS = 0;
        
        // selection
        
        if (badcutVDDD_L0POS || badcutVDD_L0POS || badcutVDDP_L0POS || badcutVDAD_L0POS || badSumCurL0pos) {
            FAILED += "C+";
        }
        
        if (badcutVDDD_L0 || badcutVDD_L0 || badcutVDDP_L0 || badcutVDAD_L0 || badSumCurL0) {
            FAILED += "C-";
        }
        
        int badCH_posFiled[64];
        int badCH_negFiled[64];
        
        std::vector<int> differentbadCH_NEG;
        std::vector<int> differentbadCH_POS;
        
        for (int i = 0; i < 64; i++) {
            badCH_posFiled[i] = 0;
            badCH_negFiled[i] = 0;
        }
        
        
        int countbadChpos = 0;
        int countbadChNeg = 0;
        
        // neg
        if (FAILED.size() == 0) {
            
            for (int i = 0; i < badCH_BlineNEG.size(); i++) {
                badCH_negFiled[badCH_BlineNEG[i]] = 1;
                countbadChNeg++;
            }
            
            for (int i = 0; i < badCH_BlinePOS.size(); i++) {
                badCH_posFiled[badCH_BlinePOS[i]] = 1;
                countbadChpos++;
            }
            
            if (countbadChNeg) {
                FAILED += "B-" + std::to_string(countbadChNeg);
            }
            
            if (countbadChpos) {
                if (BlinePauseAll != 0) FAILED += "B+" + std::to_string(countbadChpos);
            }
            
            for (int i = 0; i < badCH_MEANL0.size(); i++) {
                if (badCH_negFiled[badCH_MEANL0[i]] == 0) {
                    differentbadCH_NEG.push_back(badCH_MEANL0[i]);
                    badCH_negFiled[badCH_MEANL0[i]] = 1;
                }
            }
            
            for (int i = 0; i < badCH_EntriesL0.size(); i++) {
                if (badCH_negFiled[badCH_EntriesL0[i]] == 0) {
                    differentbadCH_NEG.push_back(badCH_EntriesL0[i]);
                    badCH_negFiled[badCH_EntriesL0[i]] = 1;
                }
            }
            
            if (differentbadCH_NEG.size()) {
                FAILED += "P-" + std::to_string(differentbadCH_NEG.size());
            }
            
            differentbadCH_NEG.clear();
            
            for (int i = 0; i < badCH_MEANTDOL0.size(); i++) {
                
                if (badCH_negFiled[badCH_MEANTDOL0[i]] == 0) {
                    differentbadCH_NEG.push_back(badCH_MEANTDOL0[i]);
                    badCH_negFiled[badCH_MEANTDOL0[i]] = 1;
                }
                
            }
            
            if (differentbadCH_NEG.size()) {
                FAILED += "T-" + std::to_string(differentbadCH_NEG.size());
            }
            
            differentbadCH_NEG.clear();

            
            for (int i = 0; i < badCH_ARTNEG.size(); i++) {
                
                if (badCH_negFiled[badCH_ARTNEG[i]] == 0) {
                    differentbadCH_NEG.push_back(badCH_ARTNEG[i]);
                    badCH_negFiled[badCH_ARTNEG[i]] = 1;
                }
                
            }
            
            if (differentbadCH_NEG.size()) {
                FAILED += "A-" + std::to_string(differentbadCH_NEG.size());
            }
            
             differentbadCH_NEG.clear();
            
            for (int i = 0; i < badCH_MEANDDOL0.size(); i++) {
               
                if (badCH_negFiled[badCH_MEANDDOL0[i]] == 0) {
                    differentbadCH_NEG.push_back(badCH_MEANDDOL0[i]);
                    badCH_negFiled[badCH_MEANDDOL0[i]] = 1;
                }
                
            }
            
            if (differentbadCH_NEG.size()) {
                FAILED += "D-" + std::to_string(differentbadCH_NEG.size());
            }
        
        // pos
        
            
            
//            for (int i = 0; i < badCH_BlinePOS.size(); i++) {
//
//            }
            

              differentbadCH_POS.clear();
            
            for (int i = 0; i < badCH_MEANL0POS.size(); i++) {
                
                if (badCH_posFiled[badCH_MEANL0POS[i]] == 0) {
                    differentbadCH_POS.push_back(badCH_MEANL0POS[i]);
                    badCH_posFiled[badCH_MEANL0POS[i]] = 1;
                }
              
            }
            
            for (int i = 0; i < badCH_EntriesL0POS.size(); i++) {
                
                if (badCH_posFiled[badCH_EntriesL0POS[i]] == 0) {
                    differentbadCH_POS.push_back(badCH_EntriesL0POS[i]);
                    badCH_posFiled[badCH_EntriesL0POS[i]] = 1;
                }
                
            }
            
            if (differentbadCH_POS.size()) {
                FAILED += "P+" + std::to_string(differentbadCH_POS.size());
            }
            
            differentbadCH_POS.clear();
            
            
            for (int i = 0; i < badCH_MEANTDOL0POS.size(); i++) {
          
                
                if (badCH_posFiled[badCH_MEANTDOL0POS[i]] == 0) {
                    differentbadCH_POS.push_back(badCH_MEANTDOL0POS[i]);
                    badCH_posFiled[badCH_MEANTDOL0POS[i]] = 1;
                }
                
            }
            
            if (differentbadCH_POS.size()) {
                FAILED += "T+" + std::to_string(differentbadCH_POS.size());
            }
            
            differentbadCH_POS.clear();
            

            for (int i = 0; i < badCH_ARTPOS.size(); i++) {
                
                if (badCH_posFiled[badCH_ARTPOS[i]] == 0) {
                    differentbadCH_POS.push_back(badCH_ARTPOS[i]);
                    badCH_posFiled[badCH_ARTPOS[i]] = 1;
                }
                
            }
            
            if (differentbadCH_POS.size()) {
                FAILED += "A+" + std::to_string(differentbadCH_POS.size());
            }
            
            differentbadCH_POS.clear();
            
            for (int i = 0; i < badCH_MEANDDOL0POS.size(); i++) {
                
                if (badCH_posFiled[badCH_MEANDDOL0POS[i]] == 0) {
                    differentbadCH_POS.push_back(badCH_MEANDDOL0POS[i]);
                    badCH_posFiled[badCH_MEANDDOL0POS[i]] = 1;
                }
                
            }
            
            if (differentbadCH_POS.size()) {
                FAILED += "D+" + std::to_string(differentbadCH_POS.size());
            }
            
            differentbadCH_NEG.clear();
            
            
            
        }
        
        if (FAILED.size() == 0)  FAILED = "0";
        
        
            
        
        
        return status;
    }
    
    
}
