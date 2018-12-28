namespace cuts {
    
    void printBadChNegAndPos() {
        
    }
    
    void printCutChips(std::string chip_id) {
        
        std::ofstream infoChannelsFile;
        infoChannelsFile.open(VMMCalibration::infoChannelsPath, std::ios::app);
        infoChannelsFile << "\n ********************************************************** \n";
        infoChannelsFile <<"\nchip_id : "<< chip_id;
        
        if (badCH_BlineNEG.size()) {
            infoChannelsFile << "\nBad_CH_BLineNEG :" ;
            for (int i = 0; i < badCH_BlineNEG.size(); i++) {
                infoChannelsFile << " " << badCH_BlineNEG[i];
            }
        }
        
        if (badCH_BlinePOS.size()) {
            infoChannelsFile << "\nBad_CH_BLinePOS :" ;
            for (int i = 0; i < badCH_BlinePOS.size(); i++) {
                infoChannelsFile << " " << badCH_BlinePOS[i];
            }
        }
        
        if (badCH_ARTNEG.size()) {
            infoChannelsFile << "\nBad_CH_ARTNEG :" ;
            for (int i = 0; i < badCH_ARTNEG.size(); i++) {
                infoChannelsFile << " " << badCH_ARTNEG[i];
            }
        }
        
        if (badCH_ARTPOS.size()) {
            infoChannelsFile << "\nBad_CH_ARTPOS :" ;
            for (int i = 0; i < badCH_ARTPOS.size(); i++) {
                infoChannelsFile << " " << badCH_ARTPOS[i];
            }
        }
        
        //
        
        if (badCH_MEANDDOL0.size()) {
            infoChannelsFile << "\n badCH_MEANDDOL0 :" ;
            for (int i = 0; i < badCH_MEANDDOL0.size(); i++) {
                infoChannelsFile << " " << badCH_MEANDDOL0[i];
            }
        }
        
        if (badCH_MEANDDOL0POS.size()) {
            infoChannelsFile << "\n badCH_MEANDDOL0POS :" ;
            for (int i = 0; i < badCH_MEANDDOL0POS.size(); i++) {
                infoChannelsFile << " " << badCH_MEANDDOL0POS[i];
            }
        }
        
        if (badCH_MEANL0.size()) {
            infoChannelsFile << "\n badCH_MEANL0 :" ;
            for (int i = 0; i < badCH_MEANL0.size(); i++) {
                infoChannelsFile << " " << badCH_MEANL0[i];
            }
        }
        
        if (badCH_MEANL0POS.size()) {
            infoChannelsFile << "\n badCH_MEANL0POS :" ;
            for (int i = 0; i < badCH_MEANL0POS.size(); i++) {
                infoChannelsFile << " " << badCH_MEANL0POS[i];
            }
        }
        
        if (badCH_MEANTDOL0.size()) {
            infoChannelsFile << "\n badCH_MEANTDOL0 :" ;
            for (int i = 0; i < badCH_MEANTDOL0.size(); i++) {
                infoChannelsFile << " " << badCH_MEANTDOL0[i];
            }
        }
        
        if (badCH_MEANTDOL0POS.size()) {
            infoChannelsFile << "\n badCH_MEANTDOL0POS :" ;
            for (int i = 0; i < badCH_MEANTDOL0POS.size(); i++) {
                infoChannelsFile << " " << badCH_MEANTDOL0POS[i];
            }
        }
        
        if (badCH_EntriesL0.size()) {
            infoChannelsFile << "\n badCH_EntriesL0 :" ;
            for (int i = 0; i < badCH_EntriesL0.size(); i++) {
                infoChannelsFile << " " << badCH_EntriesL0[i];
            }
        }
        
        if (badCH_EntriesL0POS.size()) {
            infoChannelsFile << "\n badCH_EntriesL0POS :" ;
            for (int i = 0; i < badCH_EntriesL0POS.size(); i++) {
                infoChannelsFile << " " << badCH_EntriesL0POS[i];
            }
        }
        
        
        if (badSumCurL0) {
            infoChannelsFile << "\n badSumCurL0 :" ;
        }
        
        if (badSumCurL0pos) {
            infoChannelsFile << "\n badSumCurL0pos :" ;
        }
        
        if (badcutVDDD_L0) {
            infoChannelsFile << "\n badcutVDDD_L0 :" ;
        }
        
        if (badcutVDD_L0) {
            infoChannelsFile << "\n badcutVDD_L0 :" ;
        }
        
        if (badcutVDDP_L0) {
            infoChannelsFile << "\n badcutVDDP_L0 :" ;
        }
        
        if (badcutVDAD_L0) {
            infoChannelsFile << "\n badcutVDAD_L0 :" ;
        }
        
        if (badcutVDDD_L0POS) {
            infoChannelsFile << "\n badcutVDDD_L0POS :" ;
        }
        
        if (badcutVDD_L0POS) {
            infoChannelsFile << "\n badcutVDD_L0POS :" ;
        }
        
        if (badcutVDDP_L0POS) {
            infoChannelsFile << "\n badcutVDDP_L0POS :" ;
        }
        
        if (badcutVDAD_L0POS) {
            infoChannelsFile << "\n badcutVDAD_L0POS :" ;
        }
        
            infoChannelsFile << "\n chipStatus : " << chipStatus << "\n" ;
        
        
        infoChannelsFile.close();
    }
    

}
