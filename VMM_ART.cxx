namespace VMMCalibration {

int numEntriesART[64];

bool processTestART (test_t *test, int number, TH2C * hAll) {
    calc_data_Temp(test);
    
    char title[256];
    sprintf(title, "Channel %s %i ", addNameToHistogram.c_str(), number);
    
    char name[256];
    sprintf(name, "Channel %s %i ", addNameToHistogram.c_str(), number);
    
    TH1I *h = new TH1I(title, name, 64, 0, 64);
    
    
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("ch");
    h->SetYTitle("ART");
    
    
    bool triggerART = true;
    int countTrueEvents = 0;
    for(int i = 0; i < test->num_events; i++) {
        int b = test->events[i].ARTint;
        if (number != test->events[i].ARTint) triggerART = false;
        else countTrueEvents++;
        h->Fill(test->events[i].ARTint);
        hAll->Fill(number, test->events[i].ARTint);
        //hAll->Fill(number, test->events[i].ARTint, 0.1);
    }
    numEntriesART[number] = countTrueEvents;
    
    
    h->Draw();
    
    //gCnv->Clear();
    if(h->GetEntries())
        h->Write();
    
    delete h;
    return triggerART;
}


#define NUM_TESTS_ART 64
test_t testsART[NUM_TESTS_ART];
void calibrationART(string chip_id) {
    
    if (currentNameFilesART.size() == 0) return;
    gStyle->SetOptStat("");
    //TCanvas *gCnv;
    //gCnv = new TCanvas("cnv_vmmda", "VMM Data Analysis", 200, 10, 700, 500);
    
    char rootpath[256];
    sprintf(rootpath, "%s%sroot%s%s_%s.root", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), chip_id.c_str(), configurationName.c_str());
    TFile *rootFile;
    rootFile = new TFile(rootpath, "RECREATE");
    rootFile->cd();
    
    //TH1I *hALL = new TH1I("Channel ALL ART", "Channel ALL ART", 64, 0, 64);
    //cout << "/n \n check work ART ";
    
    char name[256];
    sprintf(name, "%s channel all", addNameToHistogram.c_str());
    
    TH2C *hALL = new TH2C(name, name, 64, 0, 64, 64, 0, 64);
    
    //hALL->SetLineColor(4);
    //hALL->SetFillColor(34);
    hALL->SetXTitle("ch");
    hALL->SetYTitle("ch response");
    hALL->SetMarkerStyle(3);
    
    bool triggerART[64];
    
    for(int i = 0; i < currentNameFilesART.size(); i++)  {
        char path[256];
        sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str(), chip_id.c_str(), macORWin.c_str(), internalFolderName.c_str(), macORWin.c_str(), currentNameFilesART[i].c_str());
        FILE *fp = fopen(path, "r");
        
        LoadTest(path, &testsART[i]);
        
        int numberART =  atoi((currentNameFilesART[i].substr(currentNameFilesART[i].find("ART_") + 4)).c_str());
        triggerART[numberART] = processTestART(&testsART[i], numberART, hALL);
        fclose(fp);
        
    }
    
    char txtpath[512];
    
    //sprintf(txtpath, "%s%sconstants%sconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    
    if (addNameToHistogram.find("pos") == -1) sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    else sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    
    FILE *fp = fopen(txtpath, "at");
    
    //fprintf(fp, "%s_BOARD_ID %i \n", configurationName.c_str(), BOARD_ID);
   // fprintf(fp, "%s_TestMode %s\n \n", configurationName.c_str(), test_mode);
    
    string secART = "true";
    
    fprintf(fp, "\n%s_Bad_CH  ", configurationName.c_str());
    
    bool notBadART = true;
    
    for(int i = 0; i < 64; i++)  {
        
        if (!triggerART[i]) {
            if (notBadART) {
                notBadART = false;
                
                fprintf(fp, "%i", i);
            } else fprintf(fp, ", %i", i);
        }
    }
    
    cuts::AnalysisCutsART(triggerART, configurationName);
    
    if (notBadART) {
        fprintf(fp, "No");
    }
    fprintf(fp, "\n\n");
    
    for(int i = 0; i < 64; i++)  {
        fprintf(fp, "\n%sEntries_CH%i %i", configurationName.c_str(),i ,numEntriesART[i]);
    }
    
    fprintf(fp, "\n\n");
    
    if (fp) {
        fprintf(fp, "\n%s_Temp_Max %f", configurationName.c_str(), TempMax);
        //    fprintf(fp,"\nTemp_Min %f" , TempMin);
        fprintf(fp,"\n%s_VDD_V_Max %f",configurationName.c_str(), VDD_V_Max);
        //    fprintf(fp,"\nVDD_V_Min %f" , VDD_V_Min);
        fprintf(fp,"\n%s_VDD_A_Max %f", configurationName.c_str(), VDD_A_Max);
        //    fprintf(fp,"\nVDD_A_Min %f" , VDD_A_Min);
        fprintf(fp,"\n%s_VDDD_V_Max %f", configurationName.c_str(), VDDD_V_Max);
        //    fprintf(fp,"\nVDDD_V_Min %f" , VDDD_V_Min);
        fprintf(fp,"\n%s_VDDD_A_Max %f", configurationName.c_str(), VDDD_A_Max);
        //    fprintf(fp,"\nVDDD_A_Min %f" , VDDD_A_Min);
        fprintf(fp,"\n%s_VDDP_V_Max %f",configurationName.c_str(), VDDP_V_Max);
        //    fprintf(fp,"\nVDDP_V_Min %f" , VDDP_V_Min);
        fprintf(fp,"\n%s_VDDP_A_Max %f", configurationName.c_str(), VDDP_A_Max);
        //    fprintf(fp,"\nVDDP_A_Min %f" , VDDP_A_Min);
        fprintf(fp,"\n%s_VDAD_V_Max %f", configurationName.c_str(), VDAD_V_Max);
        //    fprintf(fp,"\nVDAD_V_Min %f" , VDAD_V_Min);
        fprintf(fp,"\n%s_VDAD_A_Max %f", configurationName.c_str(), VDAD_A_Max);
        //    fprintf(fp,"\nVDAD_A_Min %f" , VDAD_A_Min);
        fprintf(fp,"\n");
        
        //   fclose(fp);
    }
    
    fclose(fp);
    
    if(hALL->GetEntries()) {
        
        rootFile->cd();
        
        hALL->Write();
        char file[256];
        
        sprintf(file, "%s_ART_%s", chip_id.c_str(), configurationName.c_str()); //???????????????? ?????? ?????? ????????????
        //sprintf(pdfname, "%s%spdf%s%s.pdf", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), file);
        gCnv->Divide(1,1);
        gCnv->cd(1);
        
        hALL->Draw("colz");
        
//        gCnv->Print(pdfnameMain, "pdf");
        
        if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
        else gCnv->Print(pdfnameMainNEG, "pdf");
        
        gCnv->cd();
        gCnv->Clear();
        
        gStyle->SetOptStat("eou");
        
    }
    
    delete hALL;
    delete rootFile;
//    delete gCnv;
}
}
