#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TError.h>

#include <TObject.h>
#include <TH2.h>

using namespace std;

namespace VMMCalibration {
    
std::string preffBline = "";
bool blineWithRMS = false;

struct event_data_bline {
    float blineData[64];
    //float blineRMS[64];
};

    float RMSBLine[64];
    float meanBLine[64];
    


int readEventsBaseLine(FILE *fp, event_data_bline *events = NULL) {

    int numEvents = -1;
    int interCount = 0;
    
    int blineNumCH = 0;
    blineWithRMS = false;
    

    float dataBLine;
    char str[2048];

        while(!feof(fp)) {
        if( !fgets(str, 2048, fp) )
            continue;
            float test;
            int chNum;
        // сделать считываение из шапки
            if(sscanf(str, "BASELINE PAUSE         %f",  &dataBLine)) bLinePause = dataBLine;
            
            if(sscanf(str, "Channel: #%i",  &chNum)) {
                blineNumCH = chNum;
                blineWithRMS = true;
                numEvents = 0;
            }
            
            if (blineWithRMS && events != NULL) {
                
                if (blineNumCH > 64) {
                    cout << "/n" << "Error! count BLine > 64" << blineNumCH;
                    system("pause");
                }
                
                if(sscanf(str, "M1:       %f",  &dataBLine))
                    events[numEvents].blineData[blineNumCH] = dataBLine;
                if(sscanf(str, "RMS:      %f",  &dataBLine))
                    RMSBLine[blineNumCH] = dataBLine;
                if(sscanf(str, "SIGMA:    %f",  &dataBLine))
                    RMSBLine[blineNumCH] = dataBLine;
            } else
        
            if(sscanf(str, "#%f", &test) == 1) {
                //if (interCount > 63 ||  numEvents == -1) {
                numEvents++;
                interCount = 0;
            } else if (events != NULL) {

                if (interCount > 64) {
                    
                    cout << "/n" << "Error! count BLine > 64";
                    system("pause");
                    
                    
                }

                if(sscanf(str, "%f", &dataBLine) == 1) {
                    if (dataBLine != 0) {
                        events[numEvents].blineData[interCount] = dataBLine;
                        interCount++;
                    }
                }
            } else {
                if(sscanf(str, "%f", &dataBLine) == 1) {
                    if (dataBLine != 0) interCount++;
                    
                }
            
            }
  
        }

        return numEvents;
}

 void calcData(event_data_bline *events, string chip_id,int numEvents) {
     
     char name[256];
     sprintf(name, "BLine %s", preffBline.c_str());
     
     TH2C *hAllBline = new TH2C(name, name, 64, cuts::cut_bline_min, cuts::cut_bline_max,  64, 0, 64);
     
     hAllBline->SetXTitle("Bline");
     hAllBline->SetYTitle("ch");
     hAllBline->SetMarkerStyle(3);
     
     sprintf(name, "BLineRMS %s", preffBline.c_str());
     
     TH2C *hBlineRMS = new TH2C(name, name, 64, cuts::cut_blineRMS_min, cuts::cut_blineRMS_max,  64, 0, 64);
     
     hBlineRMS->SetXTitle("BlineRMS");
     hBlineRMS->SetYTitle("ch");
     hBlineRMS->SetMarkerStyle(3);
     
    TFile *rootFile;
    char rootpath[256];
    sprintf(rootpath, "%s%sroot%s%s_BLine%s.root", outputPath.c_str() , macORWin.c_str(), macORWin.c_str(), chip_id.c_str(), preffBline.c_str());
    rootFile = new TFile(rootpath, "RECREATE");

    rootFile->cd();

    TTree *dataBline;
    dataBline = new TTree("DataBline","data");

    Int_t countCh = 64;
    Float_t arrayDataBLine[64];

    dataBline->Branch("countCh", &countCh, "countCh/I");
    dataBline->Branch("dataBline", &arrayDataBLine, "dataBline[countCh]/F");
    for (int i = 0; i < numEvents; i++) {
        for (int j = 0; j < 64; j++) {
            arrayDataBLine[j] = events[i].blineData[j];
            hAllBline->Fill(events[i].blineData[j], j);
        }
        dataBline->Fill();
    }

    
     
    for (int i = 0; i < 64; i++) {

    char nameDirTree[256];
    char nameLocalDir[256];

    sprintf(nameDirTree, "dataBline[%i]>>dataBline_Ch%i", i, i);
    sprintf(nameLocalDir, "dataBline_Ch%i", i);

    dataBline->Draw(nameDirTree);
        
    TH2F *his = static_cast<TH2F *> (gDirectory->Get(nameLocalDir));
    if (blineWithRMS == false) RMSBLine[i] = his->GetRMS();
        
    hBlineRMS->Fill(RMSBLine[i], i);
        
    meanBLine[i] = his->GetMean();
        
    }

        char txtpath[256];
       // sprintf(txtpath, "%s%sconstants%sconst_%s%s.txt", outputPath.c_str(),macORWin.c_str() ,macORWin.c_str(),addNameConst.c_str(), chip_id.c_str());
     
     if (preffBline.find("pos") == -1) sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
     else sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
     
        FILE *fp = fopen(txtpath, "at");
     
     if (bLinePause != nonCorrectValue) fprintf(fp, "BLinePause%s %f \n", preffBline.c_str(), bLinePause);

    for (int i = 0; i < 64; i++) {
       fprintf(fp, "BLine_RMS%s%i %f \n", preffBline.c_str(), i, RMSBLine[i]);
     }
     
     
    for (int i = 0; i < 64; i++) {
       fprintf(fp, "BLine%s%i %f \n", preffBline.c_str(), i, meanBLine[i]);
        
        
     }
     
     if(hAllBline->GetEntries()) {
        //gStyle->SetOptStat("");
         
         gStyle->SetOptStat("eou");
         
         gCnv->Clear();
         
         gCnv->Divide(2,1);
         gCnv->cd(1);
         
         hAllBline->Write();
         hAllBline->Draw("colz");
         
          gCnv->cd(2);
         
         hBlineRMS->Write();
         hBlineRMS->Draw("colz");
         
         
         if (preffBline.find("pos") != -1) gCnv->Print(pdfnameMainPOS, "pdf");
         else gCnv->Print(pdfnameMainNEG, "pdf");
         gCnv->cd();
         gCnv->Clear();
         
        //gStyle->SetOptStat("eou");

     }
     
     delete hAllBline;
     
     


    fprintf(fp, "\n\n");

    fclose(fp);
     
//     if (preffBline.length()) cuts::AnalysisCutsBline(meanBLine);
//     else cuts::AnalysisCutsBline(meanBLine, true);
     
     if (bLinePause != nonCorrectValue) cuts::AnalysisCutsBline(meanBLine, "BLine" + preffBline, bLinePause);
     else cuts::AnalysisCutsBline(meanBLine, "BLine" + preffBline);

    rootFile->Write();
    rootFile->Print();

//    delete gCnv;
//    delete hisBLineChALL;
     
    delete dataBline;
    delete rootFile;
     

 }

  bool calibBaseLine(string chip_id) {
      
      preffBline = "";
      bLinePause = nonCorrectValue;

    
     char path[256];
     sprintf(path, "%s%s%s%sbline%sbline__%s.txt", inputPath.c_str(),macORWin.c_str() ,chip_id.c_str(),macORWin.c_str(),macORWin.c_str(), chip_id.c_str());
    
     FILE *fp = fopen(path, "r");
    
     if (fp == NULL) {

     sprintf(path, "%s%s%s%sbline__%s.txt", inputPath.c_str(),macORWin.c_str() ,chip_id.c_str(),macORWin.c_str(), chip_id.c_str());
     fp = fopen(path, "r");

     if (fp == NULL)      {
        // cout << "\n ERROR!!! file not found \n" << path;
         return false;
       }
     }
    
     int numEv = readEventsBaseLine(fp);
     fclose(fp);
    
     if (numEv > -1) {
         struct event_data_bline *eventBline = new event_data_bline[numEv + 1]; // это нужно удалить
         fp = fopen(path, "r");
        
         readEventsBaseLine(fp, eventBline);
         calcData(eventBline, chip_id, numEv + 1);
        
         fclose(fp);
         //delete eventBline;
     }
      
      return true;
 }

void calibBaseLineMode(string chip_id, string mode, string preff) {
    
    preffBline = preff;
    bLinePause = nonCorrectValue;
    
    char path[256];
    sprintf(path, "%s%s%s%sBASELINE%s%s", inputPath.c_str(),macORWin.c_str() ,chip_id.c_str(),macORWin.c_str(),macORWin.c_str(), mode.c_str());
    
    FILE *fp = fopen(path, "r");
    
    if (fp == NULL)      {
        
        cout << "\n ERROR!!! file not found \n" << path;
        return ;
        
    }
    int numEv = readEventsBaseLine(fp);
    
    fclose(fp);
    
    if (numEv > -1) {
        struct event_data_bline *eventBline = new event_data_bline[numEv + 1]; // это нужно удалить
        fp = fopen(path, "r");
        
        readEventsBaseLine(fp, eventBline);
        calcData(eventBline, chip_id, numEv + 1);
        
        fclose(fp);
        //delete eventBline;
    }
}
}
