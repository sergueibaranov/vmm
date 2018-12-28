namespace cuts {
/////  include CUTs for specific mode
    int chipStatus = 0;
    
    int chipStatusNEG = 0;
    int chipStatusPOS = 0;
    
    int badCHPOS[64];
    int badCHNEG[64];
    
    std::string FAILED = "";
    
    std::vector<int> badCH_BlineNEG;
    std::vector<int> badCH_BlinePOS;
    
    std::vector<int> badCH_ARTNEG;
    std::vector<int> badCH_ARTPOS;
    
    std::vector<int> badCH_MEANDDOL0;
    std::vector<int> badCH_MEANDDOL0POS;
    
    std::vector<int> badCH_MEANL0;
    std::vector<int> badCH_MEANL0POS;
    
    std::vector<int> badCH_MEANTDOL0;
    std::vector<int> badCH_MEANTDOL0POS;
    
    std::vector<int> badCH_EntriesL0;
    std::vector<int> badCH_EntriesL0POS;
    
    bool badSumCurL0 = false;
    bool badSumCurL0pos = false;
    
    bool    badcutVDDD_L0 = false;//
    bool     badcutVDD_L0 = false;//
    bool    badcutVDDP_L0 = false;//
    bool    badcutVDAD_L0 = false;//
    
    bool badcutVDDD_L0POS = false;//
    bool  badcutVDD_L0POS = false;//
    bool badcutVDDP_L0POS = false;//
    bool badcutVDAD_L0POS = false;//
    

    bool    cutVDDD_L0 = true;//
    bool     cutVDD_L0 = true;//
    bool    cutVDDP_L0 = true;//
    bool    cutVDAD_L0 = true;//

    bool cutVDDD_L0POS = true;//
    bool  cutVDD_L0POS = true;//
    bool cutVDDP_L0POS = true;//
    bool cutVDAD_L0POS = true;//

    bool     cutsumcur = false;

    bool      cutBLINE = true;//
    
    bool      cutBLINEPOS = true;//
    bool        cutART = false;//



    bool   cutDEAD_CONT = false;
    bool     cutDEAD_L0 = false;
    bool  cutDEAD_L0POS = false;

    bool cutPDORMS_CONT = false;//
    bool cutINTERCEPT_CONT = false;//
    bool cutSLOPE_CONT = false;//

    bool cutINTERCEPT_L0 = false;//
    bool cutSLOPE_L0 = false;//
    bool cutPDORMS_L0 = false;//

    bool            cutARTL0 = true;//
    bool       cutPDOMEAN_L0 = true;
    bool       cutTDOMEAN_L0 = true;
    bool    cutPDOMEAN_DDOL0 = true;

    bool  cutINTERCEPT_L0POS = false;//
    bool      cutSLOPE_L0POS = false;//
    bool     cutPDORMS_L0POS = false;//

    bool         cutARTL0pos = true;//
    bool    cutPDOMEAN_L0POS = true;
    bool    cutTDOMEAN_L0POS = true;
    bool cutPDOMEAN_DDOL0pos = true;


    //////////////////////////////////////
    bool cutINTERCEPT_DDO = false;//
    bool cutSLOPE_DDO = false;//
    bool cutDEAD_DDO = false;
    bool cutPDOMEAN_DDO = false;

    bool cutINTERCEPT_DDOL0 = false;//
    bool cutSLOPE_DDOL0 = false;//
    bool cutDEAD_DDOL0 = false;


    bool cutINTERCEPT_DDOL0pos = false;//
    bool cutSLOPE_DDOL0pos = false;//
    bool cutDEAD_DDOL0pos = false;
    
    bool isGoodPOS = true;
    bool isGoodNEG = true;

    bool MEANL=true;//on average check

    int limit_max_ch = 2;
    int limit_ch = 0;
    int cut_entry = 50;

    //identify cut parameters
    float           cur_minL0 = 0;
    float           cur_maxL0 = 1.7;

    float        cur_minL0pos = 0;
    float        cur_maxL0pos = 1.7;

    float      mincurrentVDDP = 0;
    float    over_currentVDDP = 0.5;

    float       mincurrentVDD = 0;
    float     over_currentVDD = 1;

    float      mincurrentVDDD = 0;
    float    over_currentVDDD = 0.6;

    float      mincurrentVDAD = 0;
    float    over_currentVDAD = 0.12;

    float mincurrentVDDP_L0POS = 0;
    float over_currentVDDP_L0POS = 0.5;

    float mincurrentVDD_L0POS = 0;
    float over_currentVDD_L0POS = 1;

    float mincurrentVDDD_L0POS = 0;
    float over_currentVDDD_L0POS = 0.6;

    float mincurrentVDAD_L0POS = 0;
    float over_currentVDAD_L0POS = 0.12;

    float cut_bline_min = 135;
    float cut_bline_max = 195;
    
    float cut_blineRMS_min = 0;
    float cut_blineRMS_max = 2;

    float cut_RMS_L0_pdo_min = 0;
    float cut_RMS_L0_pdo_max = 100;

    float cut_RMS_L0POS_pdo_min = 0;
    float cut_RMS_L0POS_pdo_max = 50;

    float cut_RMS_cont_pdo_min = 0;
    float cut_RMS_cont_pdo_max = 10;

    float cut_slope_Cont_pdo_min = 0.5;
    float cut_slope_Cont_pdo_max = 1;

    float cut_RMS_cont_tdo_min = 2;
    float cut_RMS_cont_tdo_max = 45;

    float cut_intercept_Cont_pdo_min = -20;
    float cut_intercept_Cont_pdo_max = 100;

    float cut_RMS_L0_tdo_min = 7;
    float cut_RMS_L0_tdo_max = 40;

    float cut_intercept_L0_pdo_min = 0;
    float cut_intercept_L0_pdo_max = 600;

    float cut_intercept_L0POS_pdo_min = -50;
    float cut_intercept_L0POS_pdo_max = 200;

    float cut_slope_L0_pdo_min = 0;
    float cut_slope_L0_pdo_max = 8;

    float cut_slope_L0POS_pdo_min = 1;
    float cut_slope_L0POS_pdo_max = 6;

    float cut_DDO_slope_min = 0;
    float cut_DDO_slope_max = 0.12;

    float cut_DDO_intercept_min = -20;
    float cut_DDO_intercept_max = 20;

    float cut_DDOL0_slope_min = 0;
    float cut_DDOL0_slope_max = 0.2;

    float cut_DDOL0_intercept_min = -20;
    float cut_DDOL0_intercept_max = 50;

    float cut_DDOL0pos_slope_min = 0;
    float cut_DDOL0pos_slope_max = 0.2;

    float cut_DDOL0pos_intercept_min = -20;
    float cut_DDOL0pos_intercept_max = 50;

    ///////       MEAN
    float cut_PDOMEAN_L0_min = 200;
    float cut_PDOMEAN_L0_max = 1022;
    
    float cut_TDOMEAN_L0_min = 32;
    float cut_TDOMEAN_L0_max = 254;
    
    float cut_PDOMEAN_L0POS_min = 200;
    float cut_PDOMEAN_L0POS_max = 1022;
    
    float cut_TDOMEAN_L0POS_min = 32;
    float cut_TDOMEAN_L0POS_max = 254;
    
    float cut_DDOL0_MEAN_min = 6;
    float cut_DDOL0_MEAN__max = 62;
    
    float cut_DDOL0POS_MEAN_min = 6;
    float cut_DDOL0POS_MEAN__max = 62;

}
