#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

#include <TFile.h>
#include <TNtuple.h>
#include <TH2.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TFrame.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TRandom3.h>
#include <TBenchmark.h>
#include <TInterpreter.h>
#include <TApplication.h>
#include <TString.h>
#include <TBits.h>
#include <iomanip>
#include "Cut.h"

using namespace std;


#define VMMTree2_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "Main_tree.h"
void current(float Cur, float cut_min_cur, float cut_max_cur, int num, int *countBadCur)
{
    if(cut_min_cur <= Cur && Cur <= cut_max_cur)
    {
        countBadCur[num] = 1;
    }
}

int select(float *ValueMode, float cut_min, float cut_max, float *ValueModePos, float cut_min_pos, float cut_max_pos, float CUR, float CURpos)
{
    int  countBad = 0;
    if (CUR>0){
        for(int i=0; i<64; i++){
            if(cut_min <= ValueMode[i] && ValueMode[i] <= cut_max)
            {
            } else {
                countBad ++;
            }
        }}
    if (CURpos>0){
        for(int i=0; i<64; i++){
            if(cut_min_pos <= ValueModePos[i] && ValueModePos[i] <= cut_max_pos)
            {
            } else {
                countBad ++;
            }}}
    return countBad;
    
}

int selectB(float *ValueMode, float cut_min, float cut_max)
{
    int  countBad = 0;
    
    for(int i=0; i<64; i++){
        if(cut_min <= ValueMode[i] && ValueMode[i] <= cut_max)
        {
        } else {
            countBad ++;
        }
        
    }
    return countBad;
}


void VMMTree2::Loop()
{
    if (fChain == 0) return;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;

   
    
    //###########################################################
    //##################   PATH     #############################
    //###########################################################
    
    ofstream STATUS("/var/www/html/www/summary/status/STATUS_FR3018_FR3118.txt", ios::out);
    
    ofstream CERT("/var/www/html/www/summary/certification/CERT_FR3018_FR3118.txt", ios::out);
    
    ofstream baseData("/var/www/html/www/summary/best_test/Database.txt");
    
    gCnv = new TCanvas();
    sprintf(pdfname, "/var/www/html/www/summary/histogram/HIST_FR3018_FR3118.pdf");
    sprintf(pdfopen, "%s[", pdfname);
    sprintf(pdfclose, "%s]", pdfname);
    gCnv->Print(pdfopen, "pdf");

    TString link = "";
    
    link = "http://atlas.tsu.regplat.ru/www/output/";
    
////************************************************************************
    
    STATUS<<"==============VMMId certification=============="<<endl;
        STATUS<<"VMM3a FR 30 18"<<endl;
        STATUS<<"VMM3a FR 31 18"<<endl;
//    STATUS<<"VMM3a quantity - "<<nentries<<endl;
    STATUS<<setw(22)<<right<<"Data taking entries(statistics):"<<endl;
    STATUS<<setw(26)<<right<<"Baseline 50 "<<endl;
    STATUS<<setw(26)<<right<<"ART 49 "<<endl;
    STATUS<<setw(26)<<right<<"L0 99 "<<endl;
    STATUS<<setw(26)<<right<<"DDO 99 "<<endl;
    STATUS<<"=========================================================="<<endl;

    STATUS<<setw(30)<<right<<"Below selection done with MEAN criteria :"<<endl;
    STATUS<<endl;

    STATUS<<setw(6)<<right<<"Defective channels "<< "<= "<<limit_max_ch<<endl;
    STATUS<<endl;
    STATUS<<setw(20)<<right<<"L0 and DDO efficient cut"<< " > "<<cut_entry<<"(entries)"<<endl;
    STATUS<<endl;
    if(cutsumcur)
    {
        STATUS<<setw(20)<<right<<"Sum currents L0 negative "<<cur_minL0<<" - "<<cur_maxL0<<endl;
        STATUS<<endl;
    }

    if (cutVDDP_L0==true)
    {
        STATUS<<setw(20)<<right<<"VDDP L0 neg current "<<mincurrentVDDP<<" - "<<over_currentVDDP<<endl;
    }

    if (cutVDD_L0 == true)
    {
        STATUS<<setw(20)<<right<<"VDD L0 neg current "<<mincurrentVDD<<" - "<<over_currentVDD<<endl;
    }

    if (cutVDDD_L0 == true){STATUS<<setw(20)<<right<<"VDDD L0 neg current "<<mincurrentVDDD<<" - "<<over_currentVDDD<<endl;}


    if (cutVDAD_L0 == true){STATUS<<setw(20)<<right<<"VDAD L0 neg current "<<mincurrentVDAD<<" - "<<over_currentVDAD<<endl;
        STATUS<<endl;
    }

    if(cutsumcur)
    {
        STATUS<<setw(20)<<right<<"Sum currents L0 positive "<<cur_minL0pos<<" - "<<cur_maxL0pos<<endl;
        STATUS<<endl;
    }

    if (cutVDDP_L0POS==true){
        STATUS<<setw(20)<<right<<"VDDP L0 POS current "<<mincurrentVDDP_L0POS<<" - "<<over_currentVDDP_L0POS<<endl;}

    if (cutVDD_L0POS == true)
    {
        STATUS<<setw(20)<<right<<"VDD L0 POS current "<<mincurrentVDD_L0POS<<" - "<<over_currentVDD_L0POS<<endl;
    }

    if (cutVDDD_L0POS == true)
    {
        STATUS<<setw(20)<<right<<"VDDD L0 POS current "<<mincurrentVDDD_L0POS<<" - "<<over_currentVDDD_L0POS<<endl;

    }

    if (cutVDAD_L0POS == true)
    {
        STATUS<<setw(20)<<right<<"VDAD L0 POS current "<<mincurrentVDAD_L0POS<<" - "<<over_currentVDAD_L0POS<<endl;
        STATUS<<endl;
    }

    if (cutBLINE == true)
    {
        STATUS<<setw(20)<<right<<"Baseline "<<cut_bline_min<<"..."<<cut_bline_max<<endl;}
    STATUS<<setw(20)<<right<<"ART ";
    STATUS<<setw(20)<<"64 efficient channel";
    STATUS<<endl;
    STATUS<<endl;

    if (cutPDOMEAN_L0)
    {
        STATUS<<setw(20)<<right<<"L0 neg PDO mean "<<cut_PDOMEAN_L0_min<<"..."<<cut_PDOMEAN_L0_max<<endl;
    }

    if (cutTDOMEAN_L0)
    {
        STATUS<<setw(20)<<right<<"L0 neg TDO mean "<<cut_TDOMEAN_L0_min<<"..."<<cut_TDOMEAN_L0_max<<endl;
    }

    if (cutMEAN_DDOneg){
        STATUS<<setw(20)<<right<<"DDO negative mean "<<cut_DDOneg_MEAN_min<<"..."<<cut_DDOneg_MEAN__max<<endl;
        STATUS<<endl;
    }
    
    if (cutPDOMEAN_L0POS)
    {
        STATUS<<setw(20)<<right<<"L0 pos PDO mean "<<cut_PDOMEAN_L0POS_min<<"..."<<cut_PDOMEAN_L0POS_max<<endl;
    }

    if (cutTDOMEAN_L0POS){
        STATUS<<setw(20)<<right<<"L0 pos TDO mean "<<cut_TDOMEAN_L0POS_min<<"..."<<cut_TDOMEAN_L0POS_max<<endl;
    }

    if (cutMEAN_DDOpos){
        STATUS<<setw(20)<<right<<"DDO positive mean "<<cut_DDOpos_MEAN_min<<"..."<<cut_DDOpos_MEAN__max<<endl;
    }
    STATUS<<endl;
    STATUS<<endl;
////**********************************************************
    
   
    
    
    TDatime *date = new TDatime();
    
    
    
    int IdVMM[nentries];
    TString series [nentries];
    int status[nentries];
    int status1[nentries];
    TString date_best[nentries];
    TString fail[nentries];
    int day[nentries];
    int month[nentries];
    int year[nentries];
    int VMM_BL[nentries];
    
//    TH1F *hbline = new TH1F("hbline","Baseline",300,0,220);
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        date->Set(dateTime);
        
        
        if(bLinePos[2]>0)
        {
            VMM_BL[jentry] = VMMId;
        } else {
            VMM_BL[jentry] = 0;
        }
        
        
        //       otsev partii FR2218
        if(dateTime>1532000000 && VMMId<10000)
        {
            IdVMM[jentry] = VMMId;
            
        }else{
            IdVMM[jentry] = 0;
        }
        
        status[jentry] = pow(10,chipStatus);
        status1[jentry] = chipStatus;
        series[jentry] = partID;
        fail[jentry] = FAILED;
        day[jentry] = date->GetDay();
        month[jentry] = date->GetMonth();
        year[jentry] = date->GetYear();
        
        //       zapis date v need style
        
        if(date->GetDay()/10 == 0)
        {
            date_best[jentry] += "0";
            date_best[jentry] += date->GetDay();
        }else{
            date_best[jentry] += date->GetDay();
        }
        date_best[jentry] += "/";
        
        if(date->GetMonth()/10 == 0)
        {
            date_best[jentry] += "0";
            date_best[jentry] += date->GetMonth();
        }else
        {
            date_best[jentry] += date->GetMonth();
        }
        date_best[jentry] += "/";
        date_best[jentry] += date->GetYear();
        date_best[jentry] += " S";
        
        date_best[jentry] += status1[jentry];
        date_best[jentry] += "|";
        
        nb = fChain->GetEntry(jentry);   nbytes += nb;
    }
    
    
    
    
    //       recieve repeat chips
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            if (IdVMM[j]==IdVMM[j+i])
            {
                IdVMM[j+i]=0;
                status[j]=status[j]+status[j+i];
                status[j+i] = 0;
                date_best[j] = date_best[j];
                date_best[j] += "\n";
                date_best[j] += date_best[j+i];
            }
        }
    }
    
    int NBomb = 0;
    int NPassed = 0;
    int NFailed = 0;
    int NNeg = 0;
    int NPos = 0;
    int NBomb_neg = 0;
    int NBomb_pos = 0;
    TString VMMStatus[nentries];
    TString VMMStatus1[nentries];
    TString VMMstatus[nentries];
    int vg=0;
    
    //    define status
    
    for(int j=0; j<nentries; j++)
    {
        if (IdVMM[j]>0)
        {
           
            if(status[j]<10)
            {
                NFailed ++;
                VMMStatus1[j] = "Failed";
            }
            
            if(status[j]>=1000000)
            {
                NBomb ++;
                VMMStatus[j] = "Bomb";
            } else
            {
                if(status[j]%100000<1000)
                {
                    NPassed ++;
                    VMMStatus[j] = "Passed";
                } else
                {
                    if(status[j]%100000<10000)
                    {
                        NBomb_neg ++;
                        VMMStatus[j] = "Bomb Neg";
                    } else {
                        if(status[j]%100000<100000)
                        {
                            NBomb_pos ++;
                            VMMStatus[j] = "Bomb Pos";
                            
                        }else{
                            NBomb ++;
                            VMMStatus[j] = "Bomb";
                 }
                }
              }
            }
            
            if(status[j]>=10 && status[j]<100)
            {
                NNeg ++;
                VMMStatus[j] = "Passed Neg";
            } else{
                if(status[j]>=100 && status[j]<1000 && status[j]%100<10)
                {
                    NPos ++;
                    VMMStatus[j] = "Passed Pos";
                } else{
                    if(status[j]>=110 && status[j]<1000 && status[j]%100 >=10)
                    {
                        NPassed ++;
                        VMMStatus[j] = "Passed";
                    }
                }
            }
      
            vg++;
            
        }
        
    }
    
    STATUS<<"Quantity "<<vg<<endl;
    STATUS<<" Bomb "<<NBomb<<endl;
    STATUS<<" Bomb NEG "<<NBomb_neg<<endl;
    STATUS<<" Bomb POS "<<NBomb_pos<<endl;
    STATUS<<" Passed "<<NPassed<<endl;
    STATUS<<" Passed Neg "<<NNeg<<endl;
    STATUS<<" Passed Pos "<<NPos<<endl;
    STATUS<<" Failed "<<NFailed<<endl;
    STATUS<<endl;
    
    int NumBadCur = 0;
    int NumBadBl = 0;
    int NumBadPDO = 0;
    int NumBadArt = 0;
    int NumBadTDO = 0;
    int NumBadDDO = 0;
    int NumGood = 0;
    
    int NumBadCurPos = 0;
    int NumBadBlPos = 0;
    int NumBadPDOPos = 0;
    int NumBadArtPos = 0;
    int NumBadTDOPos = 0;
    int NumBadDDOPos = 0;
    int NumGoodPos = 0;
    
    ///////////////////
    
    int numberBad[64];
    
    for (int i = 0; i<64; i++)
    {
        numberBad[i] = 0;
    }
    
    int fail_current[nentries];
    int fail_baseline[nentries];
    int fail_ART[nentries];
    int fail_PDO[nentries];
    int fail_TDO[nentries];
    int fail_DDO[nentries];
    
    for (int i=0;i<nentries;i++)
    {
        fail_current[i]=0;
        fail_baseline[i]=0;
        fail_ART[i]=0;
        fail_PDO[i]=0;
        fail_TDO[i]=0;
        fail_DDO[i]=0;
    }
    int why = 0;
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        
        int countBadCur[10] = {0,0,0,0,0,0,0,0,0,0};
        int countBadCur_L0POS[10] = {0,0,0,0,0,0,0,0,0,0};
        int countBad = 0;
        int result;
        
        for(int i = 0; i<64; i++)
        {
            cout<<bLine[i]<<" ";
        }
        cout<<endl;
        
        for(int i=0; i<countCh; i++){
            if (cut_bline_min<=bLine[i] && bLine[i]<=cut_bline_max)
            {
            }else
            {
                numberBad[i] ++;
            }
        }
        ///// certification
        
        
        
        if(VMMStatus1[jentry] == "Failed")
        {
            why ++;
            
            
            
            if (tempMax_L0>0 && tempMax_L0POS>0)
            {
                current(VDDP_A_Max_L0,mincurrentVDDP,over_currentVDDP,0,countBadCur);
                current(VDD_A_Max_L0,mincurrentVDD,over_currentVDD,1,countBadCur);
                current(VDDD_A_Max_L0,mincurrentVDDD,over_currentVDDD,2,countBadCur);
                current(VDAD_A_Max_L0,mincurrentVDAD,over_currentVDAD,3,countBadCur);
                current(VDDD_A_Max_L0+VDD_A_Max_L0+VDAD_A_Max_L0+VDDP_A_Max_L0,cur_minL0,cur_maxL0,4,countBadCur);
                current(VDDP_A_Max_L0POS,mincurrentVDDP_L0POS,over_currentVDDP_L0POS,5,countBadCur);
                current(VDDP_A_Max_L0POS,mincurrentVDD_L0POS,over_currentVDD_L0POS,6,countBadCur);
                current(VDDD_A_Max_L0POS,mincurrentVDDD_L0POS,over_currentVDDD_L0POS,7,countBadCur);
                current(VDAD_A_Max_L0POS,mincurrentVDAD_L0POS,over_currentVDAD_L0POS,8,countBadCur);
                current(VDDD_A_Max_L0POS+VDD_A_Max_L0POS+VDAD_A_Max_L0POS+VDDP_A_Max_L0POS,cur_minL0,cur_maxL0,9,countBadCur);
                //////////////////
                int  sumCur = 0;
                for(int i=0; i<10; i++){
                    sumCur += countBadCur[i];
                }
                
                
                if(sumCur<10)
                {
                    NumBadCur ++;
                    fail_current[jentry] = VMMId;
                }
                else {
                    
                    result = selectB(bLine, cut_bline_min, cut_bline_max);
                    if (result >= limit_max_ch)
                    {
                        NumBadBl ++;
                        fail_baseline[jentry] = VMMId;
                        
                    } else {
                        result =  select(PDOMEAN_L0, cut_PDOMEAN_L0_min, cut_PDOMEAN_L0_max, PDOMEAN_L0POS, cut_PDOMEAN_L0_min, cut_PDOMEAN_L0_max,VDDP_A_Max_L0,
                                         VDDP_A_Max_L0POS);
                        if (result>= limit_max_ch)
                        {
                            NumBadPDO ++;
                            fail_PDO[jentry] = VMMId;
                        } else {
                            result = select(TDOMEAN_L0, cut_TDOMEAN_L0_min, cut_TDOMEAN_L0_max, TDOMEAN_L0POS, cut_TDOMEAN_L0_min, cut_TDOMEAN_L0_max,VDDP_A_Max_L0,
                                            VDDP_A_Max_L0POS);
                            
                            if (result>=limit_max_ch)
                            {
                                NumBadTDO ++;
                                fail_TDO[jentry] = VMMId;
                            }
                            else {
                                if ((countBadCh_ARTneg + countBadCh_ARTpos) >= limit_max_ch)
                                {
                                    NumBadArt ++;
                                    fail_ART[jentry] = VMMId;
                                }
                                else {
                                    result =  select(MEAN_DDOneg, cut_DDOneg_MEAN_min, cut_DDOneg_MEAN__max, MEAN_DDOpos, cut_DDOneg_MEAN_min, cut_DDOneg_MEAN__max,VDDP_A_Max_L0,
                                                     VDDP_A_Max_L0POS);
                                    if(result>=limit_max_ch)
                                    {
                                        NumBadDDO ++;
                                        fail_DDO[jentry] = VMMId;
                                    } else {
                                        NumGood ++;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (tempMax_L0POS>0 || tempMax_L0>0)
                {
                    current(VDDP_A_Max_L0,mincurrentVDDP,over_currentVDDP,0,countBadCur);
                    current(VDD_A_Max_L0,mincurrentVDD,over_currentVDD,1,countBadCur);
                    current(VDDD_A_Max_L0,mincurrentVDDD,over_currentVDDD,2,countBadCur);
                    current(VDAD_A_Max_L0,mincurrentVDAD,over_currentVDAD,3,countBadCur);
                    current(VDDD_A_Max_L0+VDD_A_Max_L0+VDAD_A_Max_L0+VDDP_A_Max_L0,cur_minL0,cur_maxL0,4,countBadCur);
                    
                    //////////////////
                    int sumCur = 0;
                    for(int i=0; i<5; i++){
                        sumCur += countBadCur[i];
                    }
                    current(VDDP_A_Max_L0POS ,mincurrentVDDP_L0POS ,over_currentVDDP_L0POS,0,countBadCur_L0POS);
                    current(VDD_A_Max_L0POS,mincurrentVDD_L0POS,over_currentVDD_L0POS,1,countBadCur_L0POS);
                    current(VDDD_A_Max_L0POS,mincurrentVDDD_L0POS,over_currentVDDD_L0POS,2,countBadCur_L0POS);
                    current(VDAD_A_Max_L0POS,mincurrentVDAD_L0POS,over_currentVDAD_L0POS,3,countBadCur_L0POS);
                    current(VDDD_A_Max_L0POS+VDD_A_Max_L0POS+VDAD_A_Max_L0POS+VDDP_A_Max_L0POS,cur_minL0,cur_maxL0,4,countBadCur_L0POS);
                    
                    //////////////////
                    int sumCur_L0POS = 0;
                    for(int i=0; i<5; i++){
                        sumCur_L0POS += countBadCur_L0POS[i];
                    }
                    
                    if(sumCur<5)
                    {
                        NumBadCur ++;
                        fail_current[jentry] = VMMId;
                    } else {
                        
                        result = selectB(bLine, cut_bline_min, cut_bline_max);
                        if (result >= limit_max_ch)
                        {
                            NumBadBl ++;
                            fail_baseline[jentry] = VMMId;
                            
                        } else {
                            result =  select(PDOMEAN_L0, cut_PDOMEAN_L0_min, cut_PDOMEAN_L0_max, PDOMEAN_L0POS, cut_PDOMEAN_L0_min, cut_PDOMEAN_L0_max,VDDP_A_Max_L0,
                                             VDDP_A_Max_L0POS);
                            if (result>= limit_max_ch)
                            {
                                NumBadPDO ++;
                                fail_PDO[jentry] = VMMId;
                            } else {
                                result = select(TDOMEAN_L0, cut_TDOMEAN_L0_min, cut_TDOMEAN_L0_max, TDOMEAN_L0POS, cut_TDOMEAN_L0_min, cut_TDOMEAN_L0_max,VDDP_A_Max_L0,
                                                VDDP_A_Max_L0POS);
                                
                                if (result>=limit_max_ch)
                                {
                                    NumBadTDO ++;
                                    fail_TDO[jentry] = VMMId;
                                } else {
                                    if ((countBadCh_ARTneg + countBadCh_ARTpos) >= limit_max_ch)
                                    {
                                        NumBadArt ++;
                                        fail_ART[jentry] = VMMId;
                                    }
                                    else {
                                        result =  select(MEAN_DDOneg, cut_DDOneg_MEAN_min, cut_DDOneg_MEAN__max, MEAN_DDOpos, cut_DDOneg_MEAN_min, cut_DDOneg_MEAN__max,VDDP_A_Max_L0,
                                                         VDDP_A_Max_L0POS);
                                        if(result>=limit_max_ch)
                                        {
                                            NumBadDDO ++;
                                            fail_DDO[jentry] = VMMId;
                                        } else {
                                            NumGood ++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    
                    NumBadBl ++;
                    fail_baseline[jentry] = VMMId;
                }
                
                
            }
        }
        
        
        
        
        
        nb = fChain->GetEntry(jentry);   nbytes += nb;
    }
    
  cout<<"++++++++++++++++"<<why;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(27)<<right<<"Failed by priorities"<<"|"<<endl;
    
    STATUS<<"============================="<<endl;
    STATUS<<"|"<<setw(10)<<left<<"Current"<<"|"<<setw(16)<<left<<NumBadCur<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"Baseline"<<"|"<<setw(16)<<left<<NumBadBl<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"PDO"<<"|"<<setw(16)<<left<<NumBadPDO<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"TDO"<<"|"<<setw(16)<<left<<NumBadTDO<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"ART"<<"|"<<setw(16)<<left<<NumBadArt<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"DDO"<<"|"<<setw(16)<<left<<NumBadDDO<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<"|"<<setw(10)<<"Passed"<<"|"<<setw(16)<<left<<NumGood<<"|"<<endl;
    STATUS<<"|---------------------------|"<<endl;
    STATUS<<endl;
    
    STATUS<<endl;
    STATUS<<setw(10)<<left<<"S  -  status"<<endl;
    STATUS<<endl;
    STATUS<<setw(10)<<"C  -  current"<<endl;
    STATUS<<setw(10)<<"B  -  Baseline"<<endl;
    STATUS<<setw(10)<<"P  -  PDO"<<endl;
    STATUS<<setw(10)<<"T  -  TDO"<<endl;
    STATUS<<setw(10)<<"D  -  DDO"<<endl;
    STATUS<<setw(10)<<"A  -  ART"<<endl;
    STATUS<<endl;
    STATUS<<setw(10)<<"<+>  -  failed in positive"<<endl;
    STATUS<<setw(10)<<"<->  -  failed in negative"<<endl;
    STATUS<<endl;
    
    
    
    int mystatus[nentries];
    int status2[nentries];
    int VMM[nentries];
    TString part[nentries];
    TString Date_best[nentries];
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        date->Set(dateTime);
        
        //       otsev partii FR2218
        if(dateTime>1532000000 && VMMId<10000)
        {
            VMM[jentry] = VMMId;
        }else{
            VMM[jentry] = 0;
        }
        
        mystatus[jentry] = pow(10,chipStatus);
        status2[jentry] = chipStatus;
        part[jentry]= partID;
        
        if(date->GetDay()/10 == 0)
        {
            Date_best[jentry] += "0";
            Date_best[jentry] += date->GetDay();
        }else{
            Date_best[jentry] += date->GetDay();
        }
        Date_best[jentry] += "/";
        
        if(date->GetMonth()/10 == 0)
        {
            Date_best[jentry] += "0";
            Date_best[jentry] += date->GetMonth();
        }else
        {
            Date_best[jentry] += date->GetMonth();
        }
        Date_best[jentry] += "/";
        Date_best[jentry] += date->GetYear();
        Date_best[jentry] += " S";
        
        Date_best[jentry] += status2[jentry];
        Date_best[jentry] += "|";
        if (tempMax_L0>0 && tempMax_L0POS>0 )
        {
            Date_best[jentry] += "negpos|";
        }else{
            if (tempMax_L0>0 && tempMax_L0POS<0 )
            {
                Date_best[jentry] += "   neg|";
            }else{
                if (tempMax_L0<0 && tempMax_L0POS>0)
                {
                    Date_best[jentry] += "   pos|";
                } else {
                    Date_best[jentry] += "stop|";
                }
            }
        }
        int len;
        Date_best[jentry] += FAILED;
        if (strlen(FAILED)<22)
        {
            len = 22-strlen(FAILED);
            
            for(int i=0; i<len;i++)
            {
                Date_best[jentry] +=" ";
            }
        }
        Date_best[jentry] += "|";
        
        nb = fChain->GetEntry(jentry);   nbytes += nb;
    }
    
    //          sort by increase
    int temp;
    TString temp2;
    
    for(int i=0; i<nentries - 1; i++){
        for(int j = 0; j < nentries - i - 1; j++){
            if (VMM[j]>VMM[j+1])
            {
                temp = VMM[j];
                VMM[j] = VMM[j+1];
                VMM[j+1] = temp;
                
                temp = mystatus[j];
                mystatus[j] = mystatus[j+1];
                mystatus[j+1] = temp;
                
                temp2 = Date_best[j];
                Date_best[j] = Date_best[j+1];
                Date_best[j+1] = temp2;
                
                temp2 = part[j];
                part[j] = part[j+1];
                part[j+1] = temp2;
                
            }
        }
    }
    //       recieve repeat chips
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            if (VMM[j]==VMM[j+i])
            {
                VMM[j+i]=0;
                mystatus[j]=mystatus[j]+mystatus[j+i];
                Date_best[j] = Date_best[j];
                Date_best[j] += "\n";
                Date_best[j] += Date_best[j+i];
            }
        }
    }
    
    NBomb = 0;
    NPassed = 0;
    NFailed = 0;
    NNeg = 0;
    NPos = 0;
    NBomb_neg = 0;
    NBomb_pos = 0;
    vg=0;
    
    //    define status
    
    for(int j=0; j<nentries; j++)
    {
        if (VMM[j]>0)
        {
            if(mystatus[j]<10)
            {
                NFailed ++;
                VMMstatus[j] = "Failed";
            } else
            {
            if(mystatus[j]>=1000000)
            {
                NBomb ++;
                VMMstatus[j] = "Bomb";
            } else
            {
                if(mystatus[j]%100000<1000)
                {
                    NPassed ++;
                    VMMstatus[j] = "Passed";
                } else
                {
                    if(mystatus[j]%100000/10000 !=0 && mystatus[j]%10000/1000!=0)
                    {
                        NBomb ++;
                        VMMstatus[j] = "Bomb";
                        
                    } else {
                        if(mystatus[j]%100000/10000 !=0)
                        {
                            NBomb_pos ++;
                            VMMstatus[j] = "Bomb Pos";
                            
                        }else{
                            if(mystatus[j]%10000/1000!=0)
                            {
                            NBomb_neg ++;
                            VMMstatus[j] = "Bomb Neg";
                            }
                        }
                    }
                }
            }
            
            if(mystatus[j]>=10 && mystatus[j]<100)
            {
                NNeg ++;
                VMMstatus[j] = "Passed Neg";
            } else{
                if(mystatus[j]>=100 && mystatus[j]<1000 && mystatus[j]%100<10)
                {
                    NPos ++;
                    VMMstatus[j] = "Passed Pos";
                } else{
                    if(mystatus[j]>=110 && mystatus[j]<1000 && mystatus[j]%100 >=10)
                    {
                        NPassed ++;
                        VMMstatus[j] = "Passed";
                    }
                }
            }
            }
//            if(mystatus[j]<10)
//            {
//                NFailed ++;
//                VMMstatus[j] = "Failed";
//            }
//
//            if(mystatus[j]>=110 && mystatus[j]<1000)
//            {
//                NPassed ++;
//                VMMstatus[j] = "Passed";
//            } else
//            {
//
//                if(mystatus[j]>=10 && mystatus[j]<100)
//                {
//                    NNeg ++;
//                    VMMstatus[j] = "Passed Neg";
//                }
//
//                if(mystatus[j]>=100 && mystatus[j]<1000)
//                {
//                    NPos ++;
//                    VMMstatus[j] = "Passed Pos";
//                }
//
//            }
//
//            if(mystatus[j]>=11000 && mystatus[j]%10000>=1000 && mystatus[j]<100000)
//            {
//                NBomb ++;
//                VMMstatus[j] = "Bomb";
//            } else {
//                if(mystatus[j]>=1000 && mystatus[j]<10000)
//                {
//                    NBomb_neg ++;
//                    VMMstatus[j] = "Bomb Neg";
//                }
//
//                if(mystatus[j]>=10000 && mystatus[j]<100000)
//                {
//                    NBomb_pos ++;
//                    VMMstatus[j] = "Bomb Pos";
//                }
//            }
//
//            if(mystatus[j]>=100000 && mystatus[j]<1000000)
//            {
//                NPassed ++;
//                VMMstatus[j] = "Passed";
//            }
//
//            if(mystatus[j]>=1000000)
//            {
//                NBomb ++;
//                VMMstatus[j] = "Bomb";
//            }
            
            vg++;
            
        }
        
    }
    
    STATUS<<"10^6 = 1000000  -  Bomb"<<endl;
    STATUS<<"10^5 = 100000  -  Passed"<<endl;
    STATUS<<"10^4 = 10000  -  Bomb positive"<<endl;
    STATUS<<"10^3 = 1000  -  Bomb negative"<<endl;
    STATUS<<"10^2 = 100  -  Passed positive"<<endl;
    STATUS<<"10^1 = 10  -  Passed negative"<<endl;
    STATUS<<"10^0 = 1  -  Failed"<<endl;
    
    STATUS<<"================================================================================="<<" "<<endl;
    STATUS<<setw(13)<<right<<"Date";
    STATUS<<"|"<<setw(6)<<left<<"CONF";
    STATUS<<"|"<<setw(22)<<left<<"FAILED";
    STATUS<<"|"<<setw(8)<<right<<"PartId";
    STATUS<<"|"<<setw(8)<<right<<"VMMId";
    STATUS<<"|"<<setw(10)<<right<<"Status";
    STATUS<<"|"<<setw(8)<<right<<"Status"<<"|"<<endl;
    
    STATUS<<"================================================================================="<<" "<<endl;

    int fg=0;
    for(int j=0; j<nentries; j++)
    {
        if (VMM[j]!=0)
        {
            
            fg ++;
            STATUS<<right<<Date_best[j];
            STATUS<<setw(8)<<right<<part[j];
            STATUS<<"|"<<setw(8)<<right<<VMM[j];
            STATUS<<"|"<<setw(10)<<right<<VMMstatus[j];
            //            STATUS<<"|"<<setw(8)<<right<<myStatus[j];
            STATUS<<"|"<<setw(8)<<right<<mystatus[j]<<"|"<<endl;
            //            STATUS<<"|"<<setw(10)<<right<<CONF[j]<<"|"<<endl;
            //            STATUS<<"|"<<setw(20)<<right<<FAIL[j]<<"|"<<endl;
            STATUS<<"---------------------------------------------------------------------------------"<<"|"<<endl;
            
        }
        
    }

   
    
    //////***********************CERTIFICATION**********************
    
    
    
    
    
    ////************************************************************************
    
    CERT<<"==============VMMId certification=============="<<endl;
    CERT<<"VMM3a FR 30 18"<<endl;
    CERT<<"VMM3a FR 31 18"<<endl;
    //    CERT<<"VMM3a quantity - "<<nentries<<endl;
    CERT<<setw(22)<<right<<"Data taking entries(statistics):"<<endl;
    CERT<<setw(26)<<right<<"Baseline 50 "<<endl;
    CERT<<setw(26)<<right<<"ART 49 "<<endl;
    CERT<<setw(26)<<right<<"L0 99 "<<endl;
    CERT<<setw(26)<<right<<"DDO 99 "<<endl;
    CERT<<"=========================================================="<<endl;
    
    CERT<<setw(30)<<right<<"Below selection done with MEAN criteria :"<<endl;
    CERT<<endl;
    
    CERT<<setw(6)<<right<<"Defective channels "<< "<= "<<limit_max_ch<<endl;
    CERT<<endl;
    CERT<<setw(20)<<right<<"L0 and DDO efficient cut"<< " > "<<cut_entry<<"(entries)"<<endl;
    CERT<<endl;
    if(cutsumcur)
    {
        CERT<<setw(20)<<right<<"Sum currents L0 negative "<<cur_minL0<<" - "<<cur_maxL0<<endl;
        CERT<<endl;
    }
    
    if (cutVDDP_L0==true)
    {
        CERT<<setw(20)<<right<<"VDDP L0 neg current "<<mincurrentVDDP<<" - "<<over_currentVDDP<<endl;
    }
    
    if (cutVDD_L0 == true)
    {
        CERT<<setw(20)<<right<<"VDD L0 neg current "<<mincurrentVDD<<" - "<<over_currentVDD<<endl;
    }
    
    if (cutVDDD_L0 == true){CERT<<setw(20)<<right<<"VDDD L0 neg current "<<mincurrentVDDD<<" - "<<over_currentVDDD<<endl;}
    
    
    if (cutVDAD_L0 == true){CERT<<setw(20)<<right<<"VDAD L0 neg current "<<mincurrentVDAD<<" - "<<over_currentVDAD<<endl;
        CERT<<endl;
    }
    
    if(cutsumcur)
    {
        CERT<<setw(20)<<right<<"Sum currents L0 positive "<<cur_minL0pos<<" - "<<cur_maxL0pos<<endl;
        CERT<<endl;
    }
    
    if (cutVDDP_L0POS==true){
        CERT<<setw(20)<<right<<"VDDP L0 POS current "<<mincurrentVDDP_L0POS<<" - "<<over_currentVDDP_L0POS<<endl;}
    
    if (cutVDD_L0POS == true)
    {
        CERT<<setw(20)<<right<<"VDD L0 POS current "<<mincurrentVDD_L0POS<<" - "<<over_currentVDD_L0POS<<endl;
    }
    
    if (cutVDDD_L0POS == true)
    {
        CERT<<setw(20)<<right<<"VDDD L0 POS current "<<mincurrentVDDD_L0POS<<" - "<<over_currentVDDD_L0POS<<endl;
        
    }
    
    if (cutVDAD_L0POS == true)
    {
        CERT<<setw(20)<<right<<"VDAD L0 POS current "<<mincurrentVDAD_L0POS<<" - "<<over_currentVDAD_L0POS<<endl;
        CERT<<endl;
    }
    
    if (cutBLINE == true)
    {
        CERT<<setw(20)<<right<<"Baseline "<<cut_bline_min<<"..."<<cut_bline_max<<endl;}
    CERT<<setw(20)<<right<<"ART ";
    CERT<<setw(20)<<"64 efficient channel";
    CERT<<endl;
    CERT<<endl;
    
    if (cutPDOMEAN_L0)
    {
        CERT<<setw(20)<<right<<"L0 neg PDO mean "<<cut_PDOMEAN_L0_min<<"..."<<cut_PDOMEAN_L0_max<<endl;
    }
    
    if (cutTDOMEAN_L0)
    {
        CERT<<setw(20)<<right<<"L0 neg TDO mean "<<cut_TDOMEAN_L0_min<<"..."<<cut_TDOMEAN_L0_max<<endl;
    }
    
    if (cutMEAN_DDOneg){
        CERT<<setw(20)<<right<<"DDO negative mean "<<cut_DDOneg_MEAN_min<<"..."<<cut_DDOneg_MEAN__max<<endl;
        CERT<<endl;
    }
    
    if (cutPDOMEAN_L0POS)
    {
        CERT<<setw(20)<<right<<"L0 pos PDO mean "<<cut_PDOMEAN_L0POS_min<<"..."<<cut_PDOMEAN_L0POS_max<<endl;
    }
    
    if (cutTDOMEAN_L0POS){
        CERT<<setw(20)<<right<<"L0 pos TDO mean "<<cut_TDOMEAN_L0POS_min<<"..."<<cut_TDOMEAN_L0POS_max<<endl;
    }
    
    if (cutMEAN_DDOpos){
        CERT<<setw(20)<<right<<"DDO positive mean "<<cut_DDOpos_MEAN_min<<"..."<<cut_DDOpos_MEAN__max<<endl;
    }
    CERT<<endl;
    CERT<<endl;
    ////**********************************************************
   
    
//    int day[nentries];
//    int month[nentries];
//    int year[nentries];
    int cut_nentries=0;
    int DATE[nentries];
    int IdVMM1[nentries];
    int myStatus[nentries];
    TString testM[nentries];
    TString FAIL[nentries];
//    TString fail[nentries];
    int idvmm[nentries];
    int Idvmm[nentries];
    int Idvmm1[nentries];
    int statusNEG[nentries];
    int statusPOS[nentries];
    int statusCONF[nentries];
    float temp_max[nentries];
    float temp_max_pos[nentries];
    int best_neg[nentries];
    int best_pos[nentries];
    int ChipS[nentries];
    int neg_def[nentries];
    int pos_def[nentries];
    int status_pro[nentries];
    
    //////////////////////////
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        status_pro[jentry] = chipStatus;
        
        if(dateTime>1532000000)
        {
            neg_def[jentry] = neg_DEAD_CHANNELS->size();
            pos_def[jentry] = pos_DEAD_CHANNELS->size();
            
            best_neg[jentry] = VMMId;
            best_pos[jentry] = VMMId;
            idvmm[jentry] = VMMId;
            IdVMM1[jentry] = VMMId;
            DATE[jentry] = dateTime;
            FAIL[jentry] = FAILED;
            fail[jentry] = FAILED;
            testM[jentry]=testMode;
            
            ChipS[jentry] = chipStatus;
            
            Idvmm[jentry] = VMMId;
            Idvmm1[jentry] = VMMId;
        } else {
            idvmm[jentry] = 0;
            IdVMM1[jentry] = 0;
            Idvmm[jentry] = 0;
            Idvmm1[jentry] = 0;
            best_neg[jentry] = VMMId;
            best_pos[jentry] = VMMId;
            neg_def[jentry] = 0;
            pos_def[jentry] = 0;
            
            
        }
        statusNEG[jentry] = chipStatusNEG;
        statusPOS[jentry] = chipStatusPOS;
        temp_max[jentry] = tempMax_L0;
        temp_max_pos[jentry]= tempMax_L0POS;
        
        if (tempMax_L0>0 && tempMax_L0POS>0)
        {
            statusCONF[jentry] = 100;
        } else {
            if (tempMax_L0>0)
            {
                statusCONF[jentry] = 10;
            } else {
                if (tempMax_L0POS>0){
                    statusCONF[jentry] = 1;
                }
            }
        }
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
    }
    
    
    for(int j=0; j<nentries; j++){
        
        for (int i=1; i<nentries-j; i++)
        {
            
            if (best_neg[j]==best_neg[j+i])
            {
                if(temp_max[j]>0 && temp_max[j+i]>0)
                {
                    if (statusNEG[j]>=statusNEG[j+i])
                    {
                        best_neg[j+i] = 0;
                    }
                    else{
                        
                        best_neg[j] = 0;
                    }
                }
                
                if(temp_max[j]>0 && temp_max[j+i]<0)
                {
                    
                    best_neg[j+i] = 0;
                }
                
                if(temp_max[j+i]>0 && temp_max[j]<0)
                {
                    
                    best_neg[j] = 0;
                }
                if(temp_max[j]<0 && temp_max[j+i]<0)
                {
                    
                    best_neg[j+i] = 0;
                    best_neg[j] = 0;
                }
            }
        }
    }
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            
            if (best_pos[j]==best_pos[j+i])
            {
                
                if(temp_max_pos[j]>0 && temp_max_pos[j+i]>0)
                {
                    if (statusPOS[j]>=statusPOS[j+i])
                    {
                        best_pos[j+i] = 0;
                    }
                    else{
                        best_pos[j] = 0;
                    }
                }
                
                if(temp_max_pos[j]>0 && temp_max_pos[j+i]<0)
                {
                    best_pos[j+i] = 0;
                }
                if(temp_max_pos[j+i]>0 && temp_max_pos[j]<0)
                {
                    
                    best_pos[j] = 0;
                }
                if(temp_max_pos[j]<0 && temp_max_pos[j+i]<0)
                {
                    
                    best_pos[j+i] = 0;
                    best_pos[j] = 0;
                }
            }
        }
    }
    
//    for(int j = 0; j<nentries; j++){
//
//        for (int i = 1; i<nentries-j; i++)
//        {
//
//            if (best_neg[j]==best_neg[j+i])
//            {
//                if(temp_max[j]>0 && temp_max[j+i]>0)
//                {
//                    if (statusNEG[j]>statusNEG[j+i])
//                    {
//                        best_neg[j+i] = 0;
//                    } else {
//                       if (statusNEG[j]==statusNEG[j+i])
//                       {
//                           if (neg_def[j]<=neg_def[j+i])
//                           {
//                               best_neg[j+i] = 0;
//                           } else{
//                               best_neg[j] = 0;
//                           }
//                       }
//                    }
//
//                }
//
//                if(temp_max[j]>0 && temp_max[j+i]<0)
//                {
//
//                    best_neg[j+i] = 0;
//                }
//
//                if(temp_max[j+i]>0 && temp_max[j]<0)
//                {
//
//                    best_neg[j] = 0;
//                }
//                if(temp_max[j]<0 && temp_max[j+i]<0)
//                {
//                    best_neg[j+i] = 0;
//                    best_neg[j] = 0;
//                }
//            }
//
//
//
//
//
//        }
//    }
//
//    for(int j=0; j<nentries; j++){
//        for (int i=1; i<nentries-j; i++)
//        {
//
//            if (best_pos[j] == best_pos[j+i])
//            {
//
//                if(temp_max_pos[j]>0 && temp_max_pos[j+i]>0)
//                {
//                    if (statusPOS[j] > statusPOS[j+i])
//                    {
//                        best_pos[j+i] = 0;
//                    }else{
//                        if (statusPOS[j] == statusPOS[j+i])
//                        {
//                        if(pos_def[j]<=pos_def[j+i])
//                        {
//                            best_pos[j+i] = 0;
//                        }else{
//                            best_pos[j] = 0;
//                        }
//                    }
//                    }
////                    else{
////                        best_pos[j] = 0;
////                    }
//                }
//
//                if(temp_max_pos[j]>0 && temp_max_pos[j+i]<0)
//                {
//                    best_pos[j+i] = 0;
//                }
//
//                if(temp_max_pos[j+i]>0 && temp_max_pos[j]<0)
//                {
//                    best_pos[j] = 0;
//                }
//                if(temp_max_pos[j]<0 && temp_max_pos[j+i]<0)
//                {
//                    best_pos[j+i] = 0;
//                    best_pos[j] = 0;
//                }
//            }
//        }
//    }
    
    
    
    
    
    
    ///////////////////////////
    int hhh = -10000;
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            
            if (idvmm[j]==idvmm[j+i])
            {
                idvmm[j+i]= hhh;
                hhh ++;
            }
        }
    }
    
    int ccccc = -10000;
    for(int j=0; j<nentries; j++){
        
        for (int i=1; i<nentries-j; i++)
        {
            
            if (Idvmm[j]==Idvmm[j+i])
            {
                
                if(temp_max[j]>0)
                {
                    ccccc ++;
                    Idvmm[j+i] = ccccc;
                } else {
                    ccccc ++;
                    Idvmm[j] = ccccc;
                }
            }
        }}
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            
            
            if (Idvmm1[j]==Idvmm1[j+i])
            {
                
                if(temp_max_pos[j]>0)
                {
                    ccccc ++;
                    Idvmm1[j+i] = ccccc;
                } else {
                    ccccc ++;
                    Idvmm1[j] = ccccc;
                }
            }
        }
    }
    //
    //
    
    for(int j=0; j<nentries; j++){
        for (int i=1; i<nentries-j; i++)
        {
            
            
            if (IdVMM1[j]==IdVMM1[j+i])
            {
                IdVMM1[j+i]=0;
            }
        }
    }
    
    ////////////////
    
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        date->Set(dateTime);
        
        //       otsev partii FR2218
        if(dateTime>1532000000 && VMMId<10000)
        {
            
            
            int totalineff[64];
            int totalL0[64];
            int totalL0POS[64];
            int totalmeanL0[64];
            int totalmeanL0POS[64];
            
            for (int i=0; i<64; i++)
            {
                totalineff[i] = 0;
                totalL0[i] = 0;
                totalL0POS[i] = 0;
                totalmeanL0[i] = 0;
                totalmeanL0POS[i] = 0;
            }
            
            // parameters with count ineff chanel
            
            int count_bline_ineff=0;
            int count_RMS_L0_pdo_ineff=0;
            int count_RMS_cont_pdo_ineff=0;
            int count_RMS_L0_tdo_ineff=0;
            int count_RMS_cont_tdo_ineff=0;
            int count_intercept_L0_pdo_ineff=0;
            int count_intercept_cont_pdo_ineff=0;
            int count_slope_L0_pdo_ineff=0;
            int count_slope_cont_pdo_ineff=0;
            int count_DDO_slope_ineff=0;
            int count_DDO_intercept_ineff=0;
            
            int count_DDOneg_slope_ineff=0;
            int count_DDOneg_intercept_ineff=0;
            
            int count_DDOpos_slope_ineff=0;
            int count_DDOpos_intercept_ineff=0;
            
            int count_Art_ineff=0;
            int count_ARTneg_ineff=0;
            int count_ARTpos_ineff=0;
            // parameters with count eff chanel
            int count_bline_eff=0;
            int count_RMS_L0_pdo_eff=0;
            int count_RMS_cont_pdo_eff=0;
            int count_RMS_L0_tdo_eff=0;
            int count_RMS_cont_tdo_eff=0;
            int count_intercept_L0_pdo_eff=0;
            int count_intercept_cont_pdo_eff=0;
            int count_slope_L0_pdo_eff=0;
            int count_slope_cont_pdo_eff=0;
            int count_DDO_slope_eff=0;
            int count_DDO_intercept_eff=0;
            
            int count_DDOneg_slope_eff=0;
            int count_DDOneg_intercept_eff=0;
            
            int count_DDOpos_slope_eff=0;
            int count_DDOpos_intercept_eff=0;
            
            int count_Art_eff=0;
            int count_ARTneg_eff=0;
            int count_ARTpos_eff=0;
            
            int count_bline_dead=0;
            int count_RMS_L0_pdo_dead=0;
            int count_RMS_cont_pdo_dead=0;
            int count_RMS_L0_tdo_dead=0;
            int count_RMS_cont_tdo_dead=0;
            int count_intercept_L0_pdo_dead=0;
            int count_intercept_cont_pdo_dead=0;
            int count_slope_L0_pdo_dead=0;
            int count_slope_cont_pdo_dead=0;
            int count_DDO_slope_dead=0;
            int count_DDO_intercept_dead=0;
            
            int count_DDOneg_slope_dead=0;
            int count_DDOneg_intercept_dead=0;
            
            int count_DDOpos_slope_dead=0;
            int count_DDOpos_intercept_dead=0;
            
            int count_VDDP=0;
            
            int countVDDPineff=0;
            int countVDDDineff=0;
            int countVDDineff=0;
            int countVDADineff=0;
            
            int countVDDP_L0POSineff=0;
            int countVDDD_L0POSineff=0;
            int countVDD_L0POSineff=0;
            int countVDAD_L0POSineff = 0;
            int count_sum_current_ineff=0;
            int count_sum_current_eff=0;
            TString str_bLine_dead = "";
            TString str_PDORMS_L0_dead = "";
            TString str_PDORMS_Cont_dead = "";
            TString str_PDOIntercept_L0_dead = "";
            TString str_PDOIntercept_Cont_dead = "";
            TString str_PDOSlope_L0_dead = "";
            TString str_PDOSlope_Cont_dead = "";
            
            TString str_Slope_DDO_dead = "";
            TString str_Intercept_DDO_dead = "";
            
            TString str_Slope_DDOneg_dead = "";
            TString str_Intercept_DDOneg_dead = "";
            
            TString str_Slope_DDOpos_dead = "";
            TString str_Intercept_DDOpos_dead = "";
            
            TString str_TDORMS_L0_dead = "";
            TString str_TDORMS_Cont_dead = "";
            
            
            TString str_bLine = "";
            TString str_PDORMS_L0 = "";
            TString str_PDORMS_Cont = "";
            TString str_PDOIntercept_L0 = "";
            TString str_PDOIntercept_Cont = "";
            TString str_PDOSlope_L0 = "";
            TString str_PDOSlope_Cont = "";
            TString str_Slope_DDO = "";
            TString str_Intercept_DDO = "";
            
            TString str_Slope_DDOneg = "";
            TString str_Intercept_DDOneg = "";
            
            TString str_Slope_DDOpos = "";
            TString str_Intercept_DDOpos = "";
            
            TString str_TDORMS_L0 = "";
            TString str_TDORMS_Cont = "";
            
            
            
            /////     VDDP MAX A L0
            
            if (cutVDDP_L0 == true)
            {
                if (mincurrentVDDP<=VDDP_A_Max_L0 && VDDP_A_Max_L0 <=over_currentVDDP){
                    VDDP_VMMId.push_back(VMMId);
                } else{
                    VDDP_bad_VMMId.push_back(VMMId);
                    countVDDPineff++;
                }
            } else {
                countVDDPineff = -1;
            }
            
            //-----------------------------VDD Max A----------------------------------
            if(cutVDD_L0 ==true)
            {
                if (mincurrentVDD<=VDD_A_Max_L0 && VDD_A_Max_L0 <=over_currentVDD){
                    VDD_VMMId.push_back(VMMId);
                } else{
                    VDD_bad_VMMId.push_back(VMMId);
                    countVDDineff++;
                }
            } else {
                countVDDineff=-1;
            }
            
            //------------------------------VDDD MAX A----------------------------------
            if(cutVDDD_L0==true)
            {
                if (mincurrentVDDD<=VDDD_A_Max_L0 && VDDD_A_Max_L0 <=over_currentVDDD){
                    VDDD_VMMId.push_back(VMMId);
                } else{
                    VDDD_bad_VMMId.push_back(VMMId);
                    countVDDDineff++;
                }
            } else {
                countVDDDineff = -1;
            }
            //------------------------------VDAD MAX A----------------------------------
            if(cutVDAD_L0 == true)
            {
                if (mincurrentVDAD<=VDAD_A_Max_L0 && VDAD_A_Max_L0 <=over_currentVDAD){
                    VDAD_VMMId.push_back(VMMId);
                } else{
                    VDAD_bad_VMMId.push_back(VMMId);
                    countVDADineff++;
                }
            } else {
                countVDADineff=-1;
            }
            
            
            //////////  PDO MEAN LO NEG
            
            
            int countBadChPDOL0 = 0;
            
            TString str_PDOMEAN_L0_dead = "";
            int count_PDOMEAN_L0_ineff = 0;
            int count_PDOMEAN_L0_eff = 0;
            if(cutPDOMEAN_L0 == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_PDOMEAN_L0_min<=PDOMEAN_L0[i] && PDOMEAN_L0[i]<=cut_PDOMEAN_L0_max && PDOEntriesMEAN_L0[i]>=cut_entry)
                    {
                        count_PDOMEAN_L0_eff++;
                    }else
                    {
                        count_PDOMEAN_L0_ineff ++;
                        str_PDOMEAN_L0_dead += i;
                        str_PDOMEAN_L0_dead += " ";
                        
                        totalmeanL0[i]=1;
                        countBadChPDOL0 ++;
                        
                    }
                    
                    if(PDOMEAN_L0[i]<=0)
                    {
                        defect.push_back(VMMId);
                    }
                }
                
            } else {
                count_PDOMEAN_L0_ineff = -1;
            }
            
            if(count_PDOMEAN_L0_ineff>limit_ch)
            {
                numberPDOMEAN_L0_ineff.push_back(VMMId);
            }
            
            
            ///////     TDO MEAN LO NEG
            
            
            int countBadChTDOL0=0;
            
            TString str_TDOMEAN_L0_dead = "";
            int count_TDOMEAN_L0_ineff = 0;
            int count_TDOMEAN_L0_eff = 0;
            
            if(cutTDOMEAN_L0 == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_TDOMEAN_L0_min<=TDOMEAN_L0[i] && TDOMEAN_L0[i]<= cut_TDOMEAN_L0_max && TDOEntriesMEAN_L0[i]>=cut_entry){
                        count_TDOMEAN_L0_eff++;
                        
                    }else
                    {
                        count_TDOMEAN_L0_ineff++;
                        str_TDOMEAN_L0_dead += i;
                        str_TDOMEAN_L0_dead += " ";
                        
                        totalmeanL0[i]=1;
                        
                        countBadChTDOL0 ++;
                    }
                }
            } else {
                count_TDOMEAN_L0_ineff=-1;
            }
            if(count_TDOMEAN_L0_ineff>limit_ch)
                numberTDOMEAN_L0_ineff.push_back(VMMId);
            
            
            
            
            // -------------------------------------------------------
            
            int countBadChDDOneg=0;
            
            TString str_MEAN_DDOneg_dead = "";
            int count_MEAN_DDOneg_ineff = 0;
            int count_MEAN_DDOneg_eff = 0;
            
            if(cutMEAN_DDOneg == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_DDOneg_MEAN_min<=MEAN_DDOneg[i] && MEAN_DDOneg[i]<=cut_DDOneg_MEAN__max){
                        count_MEAN_DDOneg_eff++;
                        
                    }else
                    {
                        count_MEAN_DDOneg_ineff++;
                        str_MEAN_DDOneg_dead += i;
                        str_MEAN_DDOneg_dead += " ";
                        totalmeanL0[i]=1;
                        countBadChDDOneg ++;
                    }
                }
            } else {
                count_MEAN_DDOneg_ineff=-1;
            }
            if(count_MEAN_DDOneg_ineff>limit_ch)
                numberMEAN_DDOneg_ineff.push_back(VMMId);
            
            
            
            
            
            //------------------------------Bline---------------------------
            int countBadCh_BL = 0;
            if(cutBLINE == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_bline_min<=bLine[i] && bLine[i]<=cut_bline_max){
                        count_bline_eff++;
                    }else
                    {
                        
                        count_bline_ineff++;
                        str_bLine_dead += i;
                        str_bLine_dead += " ";
                        totalineff[i]=1;
                        totalL0[i]=1;
                        totalL0POS[i]=1;
                        totalmeanL0[i]=1;
                        totalmeanL0POS[i]=1;
                        countBadCh_BL ++;
                    }
                }
            } else {
                count_bline_ineff=-1;
            }
            
            if(count_bline_ineff>limit_ch)
            {
                numberBLine_ineff.push_back(VMMId);
            }
            
            
            
            ///////           ART L0 neg
            
            if (cutARTneg == false){
                countBadCh_ARTneg = -1;
            }
            if (countBadCh_ARTneg>limit_ch)
            { numberARTneg_ineff.push_back(VMMId);}
            
            
            
            //---------------------------- MAX A Pos --------------------------------
            
            //---------------------------- VDDP MAX A L0 pos--------------------------------
            
            if (cutVDDP_L0POS == true)
            {
                if (mincurrentVDDP_L0POS<=VDDP_A_Max_L0POS && VDDP_A_Max_L0POS <=over_currentVDDP_L0POS){
                    VDDP_VMMIdPOS.push_back(VMMId);
                } else{
                    VDDP_bad_VMMIdPOS.push_back(VMMId);
                    countVDDP_L0POSineff++;
                }
            } else {
                countVDDP_L0POSineff = -1;
            }
            
            //-----------------------------VDD Max A Pos----------------------------------
            if(cutVDD_L0POS ==true)
            {
                if (mincurrentVDD_L0POS<=VDD_A_Max_L0POS && VDD_A_Max_L0POS <=over_currentVDD_L0POS){
                    VDD_VMMIdPOS.push_back(VMMId);
                } else{
                    VDD_bad_VMMIdPOS.push_back(VMMId);
                    countVDD_L0POSineff++;
                }
            } else {
                countVDD_L0POSineff=-1;
            }
            
            //------------------------------VDDD MAX A pos----------------------------------
            if(cutVDDD_L0POS==true)
            {
                if (mincurrentVDDD_L0POS<=VDDD_A_Max_L0POS && VDDD_A_Max_L0POS <=over_currentVDDD_L0POS){
                    VDDD_VMMIdPOS.push_back(VMMId);
                } else{
                    VDDD_bad_VMMIdPOS.push_back(VMMId);
                    countVDDD_L0POSineff++;
                }
            } else {
                countVDDD_L0POSineff = -1;
            }
            //------------------------------VDAD MAX A pos----------------------------------
            
            if(cutVDAD_L0POS == true)
            {
                if (mincurrentVDAD_L0POS <= VDAD_A_Max_L0POS && VDAD_A_Max_L0POS <= over_currentVDAD_L0POS)
                {
                    VDAD_VMMIdPOS.push_back(VMMId);
                } else
                {
                    VDAD_bad_VMMIdPOS.push_back(VMMId);
                    countVDAD_L0POSineff ++;
                }
            } else
            {
                countVDAD_L0POSineff = -1;
            }
            
            
            
            //--------------------sum current-------------------------
            
            if(cutsumcur)
            {
                if(
                   (cur_minL0<=(VDDD_A_Max_L0+VDD_A_Max_L0+VDAD_A_Max_L0+VDDP_A_Max_L0)) &&
                   ((VDDD_A_Max_L0+VDD_A_Max_L0+VDAD_A_Max_L0+VDDP_A_Max_L0)<=cur_maxL0)
                   )
                {
                    count_sum_current_eff ++;
                } else{
                    sum_current.push_back(VMMId);
                    count_sum_current_ineff ++;
                }
            } else {
                count_sum_current_ineff=-1;
            }
            //--------------------sum current pos-------------------------
            
            int count_sum_current_ineff_pos = 0;
            if(cutsumcurpos)
            {
                if((cur_minL0pos<=(VDDD_A_Max_L0POS+VDD_A_Max_L0POS+VDAD_A_Max_L0POS+VDDP_A_Max_L0POS)) &&
                   ((VDDD_A_Max_L0POS+VDD_A_Max_L0POS+VDAD_A_Max_L0POS+VDDP_A_Max_L0POS)<=cur_maxL0pos))
                {
                    count_sum_current_eff ++;
                }else{
                    count_sum_current_ineff_pos ++;
                }
            }else {
                count_sum_current_ineff_pos=-1;
            }
            //---------------ART-------------------------
            
            
            if (cutART == false){
                countBadCh_ART = -1;
            }
            if (countBadCh_ART>limit_ch)
            { numberArt_ineff.push_back(VMMId);}
            
            
            
            ///////           ART L0 pos
            
            if (cutARTpos == false){
                countBadCh_ARTpos = -1;
            }
            
            if (countBadCh_ARTpos>limit_ch)
            {numberARTpos_ineff.push_back(VMMId);}
            
            
            
            
            ///////   PDO MEAN LO POS
            
            int countBadChPDOL0POS=0;
            
            TString str_PDOMEAN_L0POS_dead = "";
            int count_PDOMEAN_L0POS_ineff = 0;
            int count_PDOMEAN_L0POS_eff = 0;
            
            if(cutPDOMEAN_L0POS == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_PDOMEAN_L0POS_min<=PDOMEAN_L0POS[i] && PDOMEAN_L0POS[i]<= cut_PDOMEAN_L0POS_max && PDOEntriesMEAN_L0POS[i]>=cut_entry){
                        count_PDOMEAN_L0POS_eff++;
                        
                    }else
                    {
                        count_PDOMEAN_L0POS_ineff++;
                        str_PDOMEAN_L0POS_dead += i;
                        str_PDOMEAN_L0POS_dead += " ";
                        totalmeanL0POS[i]=1;
                        countBadChPDOL0POS ++;
                    }
                }
            } else {
                count_PDOMEAN_L0POS_ineff=-1;
            }
            if(count_PDOMEAN_L0POS_ineff>limit_ch)
                numberPDOMEAN_L0POS_ineff.push_back(VMMId);
            
            
            
            
            ///////   TDO MEAN LO POS
            
            int countBadChTDOL0POS = 0;
            
            TString str_TDOMEAN_L0POS_dead = "";
            int count_TDOMEAN_L0POS_ineff = 0;
            int count_TDOMEAN_L0POS_eff = 0;
            
            if(cutTDOMEAN_L0POS == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_TDOMEAN_L0POS_min<=TDOMEAN_L0POS[i] && TDOMEAN_L0POS[i]<=cut_TDOMEAN_L0POS_max && TDOEntriesMEAN_L0POS[i]>=cut_entry)
                    {
                        count_TDOMEAN_L0POS_eff++;
                        
                    }else
                    {
                        count_TDOMEAN_L0POS_ineff++;
                        str_TDOMEAN_L0POS_dead += i;
                        str_TDOMEAN_L0POS_dead += " ";
                        
                        totalmeanL0POS[i]=1;
                        countBadChTDOL0POS ++;
                    }
                }
            } else {
                count_TDOMEAN_L0POS_ineff=-1;
            }
            if(count_TDOMEAN_L0POS_ineff>limit_ch)
                numberTDOMEAN_L0POS_ineff.push_back(VMMId);
            
            
            
            //------------------------------DDO positive---------------------------
            
            int countBadChDDOpos = 0;
            
            TString str_MEAN_DDOpos_dead = "";
            int count_MEAN_DDOpos_ineff = 0;
            int count_MEAN_DDOpos_eff = 0;
            
            if(cutMEAN_DDOpos == true)
            {
                for(int i=0; i<countCh; i++){
                    if (cut_DDOpos_MEAN_min<=MEAN_DDOpos[i] && MEAN_DDOpos[i]<=cut_DDOpos_MEAN__max){
                        count_MEAN_DDOpos_eff++;
                    }else
                    {
                        count_MEAN_DDOpos_ineff++;
                        str_MEAN_DDOpos_dead += i;
                        str_MEAN_DDOpos_dead += " ";
                        totalmeanL0POS[i]=1;
                        countBadChDDOpos ++;
                    }
                }
            } else {
                count_MEAN_DDOpos_ineff=-1;
            }
            if(count_MEAN_DDOpos_ineff>limit_ch)
                numberMEAN_DDOpos_ineff.push_back(VMMId);
            
            //======================Intercept L0pos=============================================
            
            int count_intercept_L0POS_pdo_eff = 0;
            int count_intercept_L0POS_pdo_ineff = 0;
            int count_intercept_L0POS_pdo_dead = 0;
            TString str_PDOIntercept_L0POS = "";
            TString str_PDOIntercept_L0POS_dead= "";
            if (cutINTERCEPT_L0POS==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_intercept_L0POS_pdo_min<=PDOIntercept_L0POS[i] && PDOIntercept_L0POS[i]<=cut_intercept_L0POS_pdo_max){
                        count_intercept_L0POS_pdo_eff ++;
                    }else
                    {
                        count_intercept_L0POS_pdo_ineff ++;
                        str_PDOIntercept_L0POS += i;
                        str_PDOIntercept_L0POS += " ";
                        
                        totalineff[i]=1;
                        totalL0POS[i]=1;
                    }
                }
            } else {
                count_intercept_L0POS_pdo_ineff = -1;
            }
            if(count_intercept_L0POS_pdo_ineff>limit_ch)
                numberintercept_L0POS_ineff.push_back(VMMId);
            //==========================SLope L0pos=============================================
            
            int count_slope_L0POS_pdo_eff=0;
            int count_slope_L0POS_pdo_ineff=0;
            int count_slope_L0POS_pdo_dead = 0;
            TString str_PDOSlope_L0POS ="";
            TString str_PDOSlope_L0POS_dead = "";
            if (cutSLOPE_L0POS==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_slope_L0POS_pdo_min<=PDOSlope_L0POS[i] && PDOSlope_L0POS[i]<=cut_slope_L0POS_pdo_max){
                        count_slope_L0POS_pdo_eff++;
                    }else
                    {
                        count_slope_L0POS_pdo_ineff++;
                        str_PDOSlope_L0POS += i;
                        str_PDOSlope_L0POS += " ";
                        totalineff[i]=1;
                        totalL0POS[i]=1;
                    }
                }
            } else {
                count_slope_L0POS_pdo_ineff = -1;
            }
            if(count_slope_L0POS_pdo_ineff>limit_ch)
                numberslope_L0POS_pdo_ineff.push_back(VMMId);
            //--------------RMS LO PDO ------------------------------
            
            if(cutPDORMS_L0==true){
                for (int i=0; i<countCh; i++)
                {
                    if (cut_RMS_L0_pdo_min<=PDORMS_L0[i] && PDORMS_L0[i]<=cut_RMS_L0_pdo_max){
                        count_RMS_L0_pdo_eff++;
                    }else
                    {
                        
                        count_RMS_L0_pdo_ineff++;
                        totalineff[i]=1;
                        totalL0[i]=1;
                        str_PDORMS_L0 += i;
                        str_PDORMS_L0 += " ";
                        
                    }
                }
                
            } else {
                count_RMS_L0_pdo_ineff = -1;
            }
            
            if(count_RMS_L0_pdo_ineff>limit_ch)
            {
                numberRMS_L0_pdo_ineff.push_back(VMMId);
            }
            //--------------RMS LOPOS PDO ------------------------------
            int count_RMS_L0POS_pdo_eff=0;
            int count_RMS_L0POS_pdo_ineff=0;
            int count_RMS_L0POS_pdo_dead=0;
            TString str_PDORMS_L0POS="";
            TString str_PDORMS_L0POS_dead="";
            
            if(cutPDORMS_L0POS ==true)
            {
                for (int i=0; i<countCh; i++)
                {
                    if (cut_RMS_L0POS_pdo_min<=PDORMS_L0POS[i] && PDORMS_L0POS[i]<=cut_RMS_L0POS_pdo_max){
                        count_RMS_L0POS_pdo_eff++;
                    }else
                    {
                        
                        count_RMS_L0POS_pdo_ineff++;
                        str_PDORMS_L0POS += i;
                        str_PDORMS_L0POS += " ";
                        
                        totalineff[i]=1;
                        totalL0POS[i]=1;
                        
                    }
                }
            } else {
                count_RMS_L0POS_pdo_ineff = -1;
            }
            if(count_RMS_L0POS_pdo_ineff>limit_ch)
            {
                numberRMS_L0POS_pdo_ineff.push_back(VMMId);
            }
            //====================PDORMS_Cont=============================
            
            if(cutPDORMS_CONT==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_RMS_cont_pdo_min<PDORMS_Cont[i] && PDORMS_Cont[i]<=cut_RMS_cont_pdo_max){
                        count_RMS_cont_pdo_eff=count_RMS_cont_pdo_eff+1;
                    }else
                    {
                        
                        count_RMS_cont_pdo_ineff=count_RMS_cont_pdo_ineff+1;
                        str_PDORMS_Cont += i;
                        str_PDORMS_Cont += " ";
                        
                        totalineff[i]=1;
                    }
                }
                
            } else {
                count_RMS_cont_pdo_ineff = -1;
            }
            if (count_RMS_cont_pdo_ineff>limit_ch){
                numberRMS_cont_pdo_ineff.push_back(VMMId);
            }
            
            
            //=========================intercept L0==========================================
            
            if(cutINTERCEPT_L0==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_intercept_L0_pdo_min<=PDOIntercept_L0[i] && PDOIntercept_L0[i]<=cut_intercept_L0_pdo_max){
                        count_intercept_L0_pdo_eff = count_intercept_L0_pdo_eff+1;
                    }else
                    {
                        count_intercept_L0_pdo_ineff = count_intercept_L0_pdo_ineff+1;
                        str_PDOIntercept_L0 += i;
                        str_PDOIntercept_L0 += " ";
                        
                        totalineff[i]=1;
                        totalL0[i]=1;
                    }
                }
            } else {
                count_intercept_L0_pdo_ineff = -1;
            }
            if(count_intercept_L0_pdo_ineff>limit_ch)
                numberintercept_L0_ineff.push_back(VMMId);
            //============================PDOIntercept_Cont========================================
            
            if(cutINTERCEPT_CONT ==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_intercept_Cont_pdo_min<=PDOIntercept_Cont[i] && PDOIntercept_Cont[i]<=cut_intercept_Cont_pdo_max){
                        count_intercept_cont_pdo_eff=count_intercept_cont_pdo_eff+1;
                    }else
                    {
                        count_intercept_cont_pdo_ineff++;
                        str_PDOIntercept_Cont += i;
                        str_PDOIntercept_Cont += " ";
                        
                        totalineff[i]=1;
                    }
                }
                
            } else {
                count_intercept_cont_pdo_ineff = -1;
            }
            if(count_intercept_cont_pdo_ineff>limit_ch)
                numberintercept_cont_ineff.push_back(VMMId);
            //========================Slope L0===============================================
            
            if (cutSLOPE_L0==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_slope_L0_pdo_min<=PDOSlope_L0[i] && PDOSlope_L0[i]<=cut_slope_L0_pdo_max){
                        count_slope_L0_pdo_eff=count_slope_L0_pdo_eff+1;
                    }else
                    {
                        count_slope_L0_pdo_ineff++;
                        str_PDOSlope_L0 += i;
                        str_PDOSlope_L0 += " ";
                        
                        totalineff[i]=1;
                        totalL0[i]=1;
                    }
                }
                
            } else {
                count_slope_L0_pdo_ineff = -1;
            }
            if(count_slope_L0_pdo_ineff>limit_ch)
                numberslope_L0_pdo_ineff.push_back(VMMId);
            //================================PDOSlope_Cont==============================================
            
            if(cutSLOPE_CONT==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_slope_Cont_pdo_min<=PDOSlope_Cont[i] && PDOSlope_Cont[i]<=cut_slope_Cont_pdo_max){
                        count_slope_cont_pdo_eff=count_slope_cont_pdo_eff+1;
                    }else
                    {
                        count_slope_cont_pdo_ineff=count_slope_cont_pdo_ineff+1;
                        str_PDOSlope_Cont += i;
                        str_PDOSlope_Cont += " ";
                        totalineff[i]=1;
                    }
                }
                
            } else {
                count_slope_cont_pdo_ineff = -1;
            }
            if(count_slope_cont_pdo_ineff>limit_ch)
                numberslope_cont_pdo_ineff.push_back(VMMId);
            //===================================Slope_DDO===============================================
            
            if (cutSLOPE_DDO==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDO_slope_min<=Slope_DDO[i] && Slope_DDO[i]<=cut_DDO_slope_max){
                        count_DDO_slope_eff=count_DDO_slope_eff+1;
                    }else
                    {
                        count_DDO_slope_ineff++;
                        str_Slope_DDO += i;
                        str_Slope_DDO += " ";
                        totalineff[i]=1;
                        totalL0[i]=1;
                        totalL0POS[i]=1;
                    }
                }
            } else {
                count_DDO_slope_ineff=-1;
            }
            if(count_DDO_slope_ineff>limit_ch){
                numberDDO_slope_ineff.push_back(VMMId);
            }
            
            //===================================Slope_DDOneg===============================================
            
            if (cutSLOPE_DDOneg==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDOneg_slope_min<=Slope_DDOneg[i] && Slope_DDOneg[i]<=cut_DDOneg_slope_max){
                        count_DDOneg_slope_eff=count_DDOneg_slope_eff+1;
                    }else
                    {
                        count_DDOneg_slope_ineff++;
                        str_Slope_DDOneg += i;
                        str_Slope_DDOneg += " ";
                        totalineff[i]=1;
                        totalL0[i]=1;
                    }
                }
            } else {
                count_DDOneg_slope_ineff=-1;
            }
            if(count_DDOneg_slope_ineff>limit_ch){
                numberDDOneg_slope_ineff.push_back(VMMId);
                
            }
            
            //===================================Slope_DDOpos===============================================
            
            if (cutSLOPE_DDOpos==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDOpos_slope_min<=Slope_DDOpos[i] && Slope_DDOpos[i]<=cut_DDOpos_slope_max){
                        count_DDOpos_slope_eff=count_DDOpos_slope_eff+1;
                    }else
                    {
                        count_DDOpos_slope_ineff++;
                        str_Slope_DDOpos += i;
                        str_Slope_DDOpos += " ";
                        totalineff[i]=1;
                        totalL0POS[i]=1;
                    }
                }
            } else {
                count_DDOpos_slope_ineff=-1;
            }
            if(count_DDOpos_slope_ineff>limit_ch){
                numberDDOpos_slope_ineff.push_back(VMMId);
                
            }
            //====================================Intercept_DDO===============================================
            if (cutINTERCEPT_DDO==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDO_intercept_min<=Intercept_DDO[i] && Intercept_DDO[i]<=cut_DDO_intercept_max){
                        count_DDO_intercept_eff++;
                    }else
                    {
                        count_DDO_intercept_ineff++;
                        str_Intercept_DDO += i;
                        str_Intercept_DDO += " ";
                        totalineff[i]=1;
                        totalL0[i]=1;
                        totalL0POS[i]=1;
                    }
                }
                
            } else {
                count_DDO_intercept_ineff=-1;
            }
            if(count_DDO_intercept_ineff>limit_ch)
                numberDDO_intercept_ineff.push_back(VMMId);
            
            //====================================Intercept_DDOneg===============================================
            if (cutINTERCEPT_DDOneg==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDOneg_intercept_min<=Intercept_DDOneg[i] && Intercept_DDOneg[i]<=cut_DDOneg_intercept_max){
                        count_DDOneg_intercept_eff++;
                    }else
                    {
                        count_DDOneg_intercept_ineff++;
                        str_Intercept_DDOneg += i;
                        str_Intercept_DDOneg += " ";
                        totalineff[i]=1;
                        totalL0[i]=1;
                    }
                }
                
            } else {
                count_DDOneg_intercept_ineff=-1;
            }
            if(count_DDOneg_intercept_ineff>limit_ch)
                numberDDOneg_intercept_ineff.push_back(VMMId);
            
            //====================================Intercept_DDOpos===============================================
            if (cutINTERCEPT_DDOpos==true)
            {
                for (int i=0; i<countCh; i++){
                    if (cut_DDOpos_intercept_min<=Intercept_DDOpos[i] && Intercept_DDOpos[i]<=cut_DDOpos_intercept_max){
                        count_DDOpos_intercept_eff++;
                    }else
                    {
                        count_DDOpos_intercept_ineff++;
                        str_Intercept_DDOpos += i;
                        str_Intercept_DDOpos += " ";
                        totalineff[i]=1;
                        totalL0POS[i]=1;
                    }
                }
                
            } else {
                count_DDOpos_intercept_ineff=-1;
            }
            if(count_DDOpos_intercept_ineff>limit_ch)
                numberDDOpos_intercept_ineff.push_back(VMMId);
            
            
            
            if (cutDEAD_CONT ==false)
            {
                countDeadCh_Cont = -1;
            }
            
            if (cutDEAD_L0 == false)
            {
                countDeadCh_L0=-1;
            }
            
            if (cutDEAD_L0POS == false)
            {
                countDeadCh_L0POS = -1;
            }
            
            if (cutDEAD_DDO == false)
            {
                countDeadCh_DDO = -1;
            }
            
            if (cutDEAD_DDOneg == false)
            {
                countDeadCh_DDOneg = -1;
            }
            if (cutDEAD_DDOpos == false)
            {
                countDeadCh_DDOpos = -1;
            }
            
            
            if (countBadCh_ART>0){
                for (int i=0; i<numberBadCh_ART->size();i++) {
                    int a=numberBadCh_ART->at(i);
                    totalineff[a]=1;
                    totalL0[a]=1;
                    totalL0POS[a]=1;
                    totalmeanL0POS[a]=1;
                    totalmeanL0[a]=1;
                }
            }
            
            if (countBadCh_ARTneg>0){
                for (int i=0; i<numberBadCh_ARTneg->size();i++) {
                    int a=numberBadCh_ARTneg->at(i);
                    totalineff[a]=1;
                    totalL0[a]=1;
                    totalmeanL0[a]=1;
                }
            }
            
            if (countBadCh_ARTpos>0){
                for (int i=0; i<numberBadCh_ARTpos->size();i++) {
                    int a=numberBadCh_ARTpos->at(i);
                    totalineff[a]=1;
                    totalL0POS[a]=1;
                    totalmeanL0POS[a]=1;
                }
            }
            
            if (countDeadCh_Cont>0){
                DeadCh_Cont.push_back(VMMId);
                for(int i=0; i<numberDeadCh_Cont->size();i++){
                    int a=0;
                    a=numberDeadCh_Cont->at(i);
                    totalineff[a]=1;
                    totalL0[a]=1;
                    totalL0POS[a]=1;
                    
                }
            }
            if (countDeadCh_L0>0){
                DeadCh_L0.push_back(VMMId);
                for(int i=0; i<numberDeadCh_L0->size();i++){
                    int a=0;
                    a=numberDeadCh_L0->at(i);
                    totalineff[a]=1;
                    totalL0[a]=1;
                    
                }
            }
            if (countDeadCh_L0POS>0){
                DeadCh_L0POS.push_back(VMMId);
                for(int i=0; i<numberDeadCh_L0POS->size();i++){
                    int a=0;
                    a=numberDeadCh_L0POS->at(i);
                    totalineff[a]=1;
                    totalL0POS[a]=1;
                    
                }
            }
            if (countDeadCh_DDO>0){
                DeadCh_DDO.push_back(VMMId);
                for(int i=0; i<numberDeadCh_DDO->size();i++){
                    int a=0;
                    a=numberDeadCh_DDO->at(i);
                    totalineff[a]=1;
                }
            }
            
            if (countDeadCh_DDOneg>0){
                DeadCh_DDOneg.push_back(VMMId);
                for(int i=0; i<numberDeadCh_DDOneg->size();i++){
                    int a=0;
                    a=numberDeadCh_DDOneg->at(i);
                    totalineff[a]=1;
                }
            }
            
            
            
            
            
            ///////// uslovie sertificacii
            
            int sumineff=0;
            int sumL0=0;
            int sumL0POS=0;
            int summeanL0=0;
            int summeanL0POS=0;
            
            for (int i=0; i<64; i++)
            {
                sumineff += totalineff[i];
                sumL0 += totalL0[i];
                sumL0POS += totalL0POS[i];
                summeanL0 +=totalmeanL0[i];
                summeanL0POS +=totalmeanL0POS[i];
            }
            
            int   count_overcurrent_good = 0;
            
            if (
                (countVDDPineff<=0) &&
                (countVDDDineff<=0) &&
                (countVDADineff<=0) &&
                (countVDDineff<=0)  &&
                (countVDDP_L0POSineff<=0) &&
                (countVDDD_L0POSineff<=0) &&
                (countVDAD_L0POSineff<=0) &&
                (countVDD_L0POSineff<=0)
                )
            {
                count_overcurrent_good++;
            } else {
                over_current_fale.push_back(VMMId);
            }
            
            
            VMMId_cout.push_back(VMMId);
            ////////////// status  //////////////////////////
            
            if(
               (countVDDPineff<=0) &&
               (countVDDDineff<=0) &&
               (countVDADineff<=0) &&
               (countVDDineff<=0) &&
               (countVDDP_L0POSineff<=0) &&
               (countVDDD_L0POSineff<=0) &&
               (countVDAD_L0POSineff<=0) &&
               (countVDD_L0POSineff<=0)  &&
               summeanL0 <= 5 && summeanL0POS <= 5 &&
               count_sum_current_ineff<=0 && count_sum_current_ineff_pos<=0
               )
            {
                myStatus[jentry] = pow(10,3);
            } else {
                if(
                   (countVDDPineff<=0) &&
                   (countVDDDineff<=0) &&
                   (countVDADineff<=0) &&
                   (countVDDineff<=0) &&
                   summeanL0 <= 5 &&
                   count_sum_current_ineff<=0
                   )
                {
                    myStatus[jentry] = pow(10,1);
                } else{
                    if((countVDDP_L0POSineff<=0) &&
                       (countVDDD_L0POSineff<=0) &&
                       (countVDAD_L0POSineff<=0) &&
                       (countVDD_L0POSineff<=0) &&
                       summeanL0POS <= 5 &&
                       count_sum_current_ineff_pos<=0)
                    {
                        myStatus[jentry] = pow(10,2);
                    } else {
                        myStatus[jentry] = pow(10,0);
                    }
                }
            }
            
            
            ////////////////////////////////////////////
            if(best_neg[jentry]>0 && best_neg[jentry]<10000)
            {
                if(
                   (countVDDPineff<=0) &&
                   (countVDDDineff<=0) &&
                   (countVDADineff<=0) &&
                   (countVDDineff<=0) &&
                   summeanL0 <= limit_max_ch &&
                   count_sum_current_ineff<=0
                   )
                {
                    goodchipL0mean.push_back(VMMId);
                    
                    CERT<<endl;
                    CERT<<"***********************************************************"<<endl;
                    CERT<<" VMMId "<<VMMId<<" "<<partID<<" PASSED in L0 NEG - "<<date->GetDay()<<"/"<<date->GetMonth()<<"/"<<date->GetYear()<<" userID "<<userID<<endl;
                    
                } else{
                    CERT<<endl;
                    CERT<<"***********************************************************"<<endl;
                    CERT<<" VMMId "<<VMMId<<" "<<partID<<" FAILED in L0 NEG - "<<date->GetDay()<<"/"<<date->GetMonth()<<"/"<<date->GetYear()<<" userID "<<userID<<endl;
                    if(tempMax_L0>0)
                    {
                        
                        
                        CERT<<endl;
                        CERT<<"Count defective channels = "<<summeanL0<<endl;
                        CERT<<endl;
                        CERT<<setw(23)<<right<<"VDDP_L0 neg|";
                        if (countVDDPineff==0)
                        {
                            CERT<<setw(7)<<left<<VDDP_A_Max_L0<<" - PASSED";
                        }else{
                            if(countVDDPineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDDP_A_Max_L0<<" - FAILED";}
                        }
                        CERT<<endl;
                        
                        CERT<<setw(23)<<right<<"VDD_L0 neg|";
                        if (countVDDineff==0)
                        {
                            CERT<<setw(7)<<left<<VDD_A_Max_L0<<" - PASSED";
                        }else{
                            if(countVDDineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDD_A_Max_L0<<" - FAILED";}
                        }
                        
                        CERT<<endl;
                        
                        CERT<<setw(23)<<right<<"VDDD_L0 neg|";
                        if (countVDDDineff==0)
                        {
                            CERT<<setw(7)<<left<<VDDD_A_Max_L0<<" - PASSED";
                        }else{
                            if(countVDDDineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDDD_A_Max_L0<<" - FAILED";}
                        }
                        
                        CERT<<endl;
                        
                        CERT<<setw(23)<<right<<"VDAD_L0 neg|";
                        if (countVDADineff==0)
                        {
                            CERT<<setw(7)<<left<<VDAD_A_Max_L0<<" - PASSED";
                        }else{
                            if(countVDADineff<0)
                            {
                                CERT<<setw(7)<<left<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDAD_A_Max_L0<<" - FAILED";}
                        }
                        CERT<<endl;
                        CERT<<endl;
                        if (cutBLINE){
                            CERT<<setw(23)<<right<<"Baseline|"<<str_bLine_dead;
                            if(count_bline_ineff==0)
                            {
                                CERT<<"PASSED";
                            }  else {
                                if(count_bline_ineff<0)
                                {
                                    CERT<<"";
                                }
                            }
                            CERT<<endl;}
                        if(cutARTneg) {CERT<<setw(23)<<right<<"ART L0 neg|";
                            
                            if (countBadCh_ARTneg>0){
                                for (int i=0; i<numberBadCh_ARTneg->size();i++) {
                                    CERT<<numberBadCh_ARTneg->at(i);
                                    CERT<<" ";
                                }
                            }
                            else {
                                if(countBadCh_ARTneg<0){
                                    CERT<<"";
                                } else
                                {
                                    CERT<<"PASSED";
                                }
                            }
                            CERT<<endl;}
                        CERT<<endl;
                        
                        
                        if (cutDEAD_L0){CERT<<setw(23)<<right<<"Dead channels in L0neg|";
                            if (countDeadCh_L0>0){
                                for(int i=0; i<numberDeadCh_L0->size();i++){
                                    CERT<<numberDeadCh_L0->at(i);
                                    CERT<<" ";
                                }
                            } else{
                                if(countDeadCh_L0<0)
                                {CERT<<"";}else
                                {
                                    CERT<<"PASSED";
                                }
                            }
                            CERT<<endl;}
                        CERT<<setw(23)<<right<<"L0 neg PDO mean|"<<str_PDOMEAN_L0_dead<<endl;
                        CERT<<setw(23)<<right<<"L0 neg TDO mean|"<<str_TDOMEAN_L0_dead<<endl;
                        //CERT<<setw(23)<<right<<"L0 neg DDO mean|"<<str_MEAN_DDO_dead<<endl;
                        CERT<<setw(23)<<right<<"DDO neg mean|"<<str_MEAN_DDOneg_dead<<endl;
                        CERT<<endl;
                    }
                }
            }
            
            
            if(best_pos[jentry]>0)
            {
                if((countVDDP_L0POSineff<=0) &&
                   (countVDDD_L0POSineff<=0) &&
                   (countVDAD_L0POSineff<=0) &&
                   (countVDD_L0POSineff<=0) &&
                   summeanL0POS <= limit_max_ch &&
                   count_sum_current_ineff_pos<=0)
                {
                    
                    
                    CERT<<endl;
                    CERT<<"***********************************************************"<<endl;
                    CERT<<" VMMId "<<VMMId<<" "<<partID<<" PASSED in LO POS - "<<date->GetDay()<<"/"<<date->GetMonth()<<"/"<<date->GetYear()<<" userID "<<userID<<endl;
                }else{
                    CERT<<endl;
                    CERT<<"***********************************************************"<<endl;
                    CERT<<" VMMId "<<VMMId<<" "<<partID<<" FAILED in LO POS - "<<date->GetDay()<<"/"<<date->GetMonth()<<"/"<<date->GetYear()<<" userID "<<userID<<endl;
                    if(tempMax_L0POS>0)
                    {
                        CERT<<endl;
                        CERT<<"Count defective channels = "<<summeanL0POS<<endl;
                        CERT<<endl;
                        CERT<<setw(23)<<right<<"VDDP_L0POS|";
                        if (countVDDP_L0POSineff==0)
                        {
                            CERT<<setw(7)<<left<<VDDP_A_Max_L0POS<<" - PASSED"<<endl;
                        }else{
                            if(countVDDP_L0POSineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDDP_A_Max_L0POS<<" - FAILED"<<endl;}
                        }
                        
                        CERT<<setw(23)<<right<<"VDD_L0POS|";
                        if (countVDD_L0POSineff==0)
                        {
                            CERT<<setw(7)<<left<<VDD_A_Max_L0POS<<" - PASSED"<<endl;
                        }else{
                            if(countVDD_L0POSineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDD_A_Max_L0POS<<" - FAILED"<<endl;}
                        }
                        
                        CERT<<setw(23)<<right<<"VDAD_L0POS|";
                        if (countVDAD_L0POSineff == 0)
                        {
                            CERT<<setw(7)<<left<<VDAD_A_Max_L0POS<<" - PASSED"<<endl;
                        }else
                        {
                            if(countVDAD_L0POSineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else
                            {
                                CERT<<setw(7)<<left<<VDAD_A_Max_L0POS<<" - FAILED"<<endl;}
                        }
                        
                        
                        CERT<<setw(23)<<right<<"VDDD_L0POS|";
                        if (countVDDD_L0POSineff==0)
                        {
                            CERT<<setw(7)<<left<<VDDD_A_Max_L0POS<<" - PASSED"<<endl;
                        }else{
                            if(countVDDD_L0POSineff<0)
                            {
                                CERT<<setw(7)<<"---"<<endl;
                            } else{
                                CERT<<setw(7)<<left<<VDDD_A_Max_L0POS<<" - FAILED"<<endl;}
                        }
                        
                        CERT<<endl;
                        if (cutBLINE){
                            CERT<<setw(23)<<right<<"Baseline|"<<str_bLine_dead;
                            if(count_bline_ineff==0)
                            {
                                CERT<<"PASSED";
                            }  else {
                                if(count_bline_ineff<0)
                                {
                                    CERT<<"";
                                }
                            }
                            CERT<<endl;}
                        
                        if(cutARTpos) {CERT<<setw(23)<<right<<"ART L0 pos|";
                            
                            if (countBadCh_ARTpos>0){
                                for (int i=0; i<numberBadCh_ARTpos->size();i++) {
                                    CERT<<numberBadCh_ARTpos->at(i);
                                    CERT<<" ";
                                }
                            }
                            else {
                                if(countBadCh_ARTpos<0){
                                    CERT<<"";
                                } else
                                {
                                    CERT<<"PASSED";
                                }
                            }
                            CERT<<endl;}
                        CERT<<endl;
                        
                        if (cutDEAD_L0POS) {CERT<<setw(23)<<right<<"Dead channels in L0pos|";
                            if (countDeadCh_L0POS>0){
                                for(int i=0; i<numberDeadCh_L0POS->size();i++){
                                    CERT<<numberDeadCh_L0POS->at(i);
                                    CERT<<" ";
                                }
                            } else{
                                if(countDeadCh_L0POS<0)
                                {CERT<<"";}else
                                {
                                    CERT<<"PASSED";
                                }
                            }
                            CERT<<endl;}
                        CERT<<setw(23)<<right<<"L0 pos PDO mean|"<<str_PDOMEAN_L0POS_dead<<endl;
                        CERT<<setw(23)<<right<<"L0 pos TDO mean|"<<str_TDOMEAN_L0POS_dead<<endl;
                        CERT<<setw(23)<<right<<"DDO pos mean|"<<str_MEAN_DDOpos_dead<<endl;
                        CERT<<endl;
                    }
                }
            }
     
        }
        nb = fChain->GetEntry(jentry);   nbytes += nb;
    }
    STATUS<<"entry "<<fg<<endl;
   
    CERT.close();
    STATUS.close();

    
    
    /////////  *******************histogram**********************
    
    UInt_t Max = fChain->GetMaximum("dateTime");
    UInt_t Min = fChain->GetMinimum("dateTime");
    Int_t MaxVMM = fChain->GetMaximum("VMMId");
    Int_t MinVMM = fChain->GetMinimum("VMMId");
    
    tDatime_Var = new TDatime();
    
    tDatime_Var->Set(Max);
    
    
    gStyle->SetOptStat("eou");
    gStyle->SetPalette(kTemperatureMap);
    
    ////// mean
    
    TH2F *hBlinecor = new TH2F("hBlinecor","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms) - not failed", 300,0,500,300,0,500);
    
    TH2F *hBlinecor11 = new TH2F("hBlinecor11","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms) - Bomb neg", 300,0,500,300,0,500);
    TH2F *hBlinecor12 = new TH2F("hBlinecor12","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms) - passed neg", 300,0,500,300,0,500);
    TH2F *hBlinecor13 = new TH2F("hBlinecor13","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms) - Bomb pos", 300,0,500,300,0,500);
    TH2F *hBlinecor14 = new TH2F("hBlinecor14","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms) - passed pos", 300,0,500,300,0,500);
    
    
    
    TH2F *hBlinecor_all = new TH2F("hBlinecor_all","Bline pos (delay 5 ms) vs Bline neg (delay 0 ms)", 300,0,500,300,0,500);
    
    TH2F *hBlinecor2 = new TH2F("hBlinecor2","Bline pos (delay 0 ms) vs Bline neg (delay 0 ms)", 300,0,500,300,0,500);
    
    TH2F *hBlinecor21 = new TH2F("hBlinecor21","Bline pos (delay 0 ms) vs Bline neg (delay 0 ms)/ without failed", 300,0,500,300,0,500);
    
    TH2F *hBlinecor3 = new TH2F("hBlinecor3","Bline pos (delay 10 ms) vs Bline neg (delay 10 ms)", 300,0,500,300,0,500);
    
    TH2F *hBlinecor4 = new TH2F("hBlinecor4","Bline pos(delay 5 ms) vs Bline neg (delay 0 ms)", 300,0,500,300,0,500);
    
    TH2F *hBlinecor5 = new TH2F("hBlinecor5","Bline pos(delay 0 ms) vs Bline neg (delay 0 ms)/BOMB", 300,0,500,300,0,500);
    TH2F *hBlinecor6 = new TH2F("hBlinecor6","Bline pos(delay 0 ms) vs Bline neg (delay 0 ms)/BOMB NEG", 300,0,500,300,0,500);
    TH2F *hBlinecor61 = new TH2F("hBlinecor61","Bline pos(delay 0 ms) vs Bline neg (delay 0 ms)/PASSED NEG", 300,0,500,300,0,500);
    
    TH2F *hBlinecor7 = new TH2F("hBlinecor7","Bline pos(delay 0 ms) vs Bline neg (delay 0 ms)/BOMB POS", 300,0,500,300,0,500);
    TH2F *hBlinecor71 = new TH2F("hBlinecor71","Bline pos(delay 0 ms) vs Bline neg (delay 0 ms)/PASSED POS", 300,0,500,300,0,500);
    
    
    TH2F *hBlinecor8 = new TH2F("hBlinecor8","Bline pos(delay 5 ms) vs Bline neg (delay 0 ms)", 300,0,500,300,0,500);
    TH2F *hBlinecor9 = new TH2F("hBlinecor9","Bline pos(delay 1 ms) vs Bline neg (delay 0 ms)", 300,0,500,300,0,500);
    
    TH2F *hALLCHANNEL = new TH2F("ALLCHANNEL", "PDO mean L0 negative (all VMM)  ", 105, 0, 1023, 105, 0, 65);
    TH2F *hALLCHANNELtdol0 = new TH2F("ALLCHANNEL_tdo_L0", "TDO mean L0 negative (all VMM)  ", 105, 0, 260, 105, 0, 65);
    TH2F *hALLCHANNELpdol0pos = new TH2F("ALLCHANNEL_pdo_L0POS", "PDO mean L0 positive (all VMM) ", 105, 0, 1023, 105, 0, 65);
    
    TH2F *hALLCHANNELtdol0pos = new TH2F("ALLCHANNEL_tdo_L0POS", "TDO mean L0 positive (all VMM)", 105, 0, 260, 105, 0, 65);
    
    TH2F *hDDOnegneg_ch = new TH2F("DDOnegneg_ch", "DDO mean negative (all VMM) ", 105, 1, 63, 105, 0, 65);
    
    TH2F *hDDOpos_ch = new TH2F("DDOpos_ch", "DDO mean positive (all VMM) ", 105, 1, 63, 105, 0, 65);
    
    TH2F *hDDOneg = new TH2F("DDOneg", "DDO mean", 105, 1, 63, 105, 0, 65);
    
    TH2F *hdifbl = new TH2F("hdifbl", "bline vs sumcurrent", 105, -5, 5, 105, 0, 2);
    TH2F *hblvsrms = new TH2F("hblvsrms", "bline pos vs bline pos RMS", 300, 0, 200, 300, 0, 5);
    TH2F *hblnegvsblpos = new TH2F("hblnegvsblpos", "bline neg RMS vs bline pos RMS", 300, 0, 10, 300, 0, 10);
    
    TH2F *hARTnegNEG =new TH2F("hARTnegNEG","Number of channels with bad ART negative (zero means no defects channels in chip)  ", 105,MinVMM,3120,105,1,65);
    TH2F *hARTpos =new TH2F("hARTpos","Number of channels with bad ART positive (zero means no defects channels in chip)  ", 105,MinVMM,3120,105,1,65);
    
    TH2F *hARTneg =new TH2F("hARTneg","Number of channels with bad ART(zero means no defects channels in chip)  ", 105,MinVMM,3120,105,1,65);
    
    TH2F *hARTnegNEG1 =new TH2F("hARTnegNEG1","VMMId with bad ART negative (zero means no defects channels in chip) ", 300,MinVMM,(3120),300,0,65);
    TH2F *hARTpos2 =new TH2F("hARTpos2","VMMId with bad ART positive (zero means no defects channels in chip) ", 300,MinVMM,(3120),300,0,65);
    TH2F *hARTneg1 =new TH2F("hARTneg1","VMMId with bad ART (zero means no defects channels in chip) ", 300,MinVMM,(3120),300,0,65);
    //////  tempreture
    
    
    TH2F *htempA = new TH2F("htempA", "Current VDAD L0 neg ",105,30,52,105,0,0.12);
    TH2F *htempAVDD = new TH2F("tempAVDD", "Current VDD L0 neg ",105,30,52,105,0,1);
    TH2F *htempAVDDD = new TH2F("htempAVDDD", "Current VDDD L0 neg ",105,30,52,105,0,0.6);
    TH2F *htempAVDDP = new TH2F("tempAVDDP", "Current VDDP L0 neg ",105,30,52,105,0,0.5);
    
    TH2F *htempApos = new TH2F("htempApos", "Current VDAD L0 pos ",105,30,52,105,0,0.12);
    TH2F *htempAVDDpos = new TH2F("tempAVDDpos", "Current VDD L0 pos ",105,30,52,105,0,1);
    TH2F *htempAVDDDpos = new TH2F("htempAVDDDpos", "Current VDDD L0 pos ",105,30,52,105,0,0.6);
    TH2F *htempAVDDPpos = new TH2F("tempAVDDPpos", "Current VDDP L0 pos ",105,30,52,105,0,0.5);
    
    TH1F *hsumcurrent_L0 = new TH1F("Sum_current_L0neg","Sum current L0 negative ", 300, 0, 1.7);
    TH1F *hsumcurrent_L0POS = new TH1F("Sum_current_L0pos","Sum current L0 positive ", 300, 0, 1.7);
    
    TH1F *hVDD = new TH1F("hVDD", "VDD L0 negative ", 300, 0, 1);
    TH1F *hVDDP = new TH1F("hVDDP", "VDDP L0 negative ", 150, 0, 0.5);
    TH1F *hVDDD = new TH1F("hVDDD", "VDDD L0 negative ", 300, 0, 0.6);
    TH1F *hVDAD = new TH1F("hVDAD", "VDAD L0 negative ", 300, 0, 0.12);
    
    TH1F *hVDDpos = new TH1F("hVDDpos", "VDD L0 positive ", 300, 0, 1);
    TH1F *hVDDPpos = new TH1F("hVDDPpos", "VDDP L0 positive ", 150, 0, 0.5);
    TH1F *hVDDDpos = new TH1F("hVDDDpos", "VDDD L0 positive ", 300, 0, 0.6);
    TH1F *hVDADpos = new TH1F("hVDADpos", "VDAD L0 positive ", 300, 0, 0.12);
    
    
    TH1F *hARTcountBad = new TH1F("ARTcountBad", "count Bad channel in ART negative", 300, 0, 64);
    TH1F *hARTBad = new TH1F("ARTBad", "count Bad channel in ART", 300, 0, 64);
    TH1F *hARTposcountBad = new TH1F("ARTposcountBad", "count Bad channel in ART positive", 300, 0, 64);
    
    /////////////////////////
    
    TH1F *hbline = new TH1F("hbaseline", "Baseline  ", 300,50,250);
    TH1F *hblineRMS = new TH1F("hblineRMS", "Baseline RMS  ", 300,0,2);
    TH2F *hblineVMM = new TH2F("hblineVMM", "Baseline vs VMMId  ", 105,50,250,105,MinVMM,3120);
    
    TH2F *hblineTEMP = new TH2F("hblineTEMP", "Baseline vs tempreture  ", 105,50,250,105,30,50);
    TH2F *hbline_RMS =  new TH2F("hbline_RMS", "Baseline  vs PDO RMS negative  ", 105,0,150,105,100,230);
    
    TH1F *hPDORMS_L0 = new TH1F("hPDORMS_L0", "PDO RMS negative  ", 500, 0, 100);
    TH1F *hPDORMS_L0POS = new TH1F("hPDORMS_L0POS", "PDO RMS positive  ", 500, 0, 100);
    TH1F *hPDOIntercept_L0 = new TH1F("hPDOIntercept_L0","PDO Intercept negative ", 400,-200,800);
    
    TH1F *hTDORMS_L0 = new TH1F("hTDORMS_L0", "TDO RMS negative  ", 500, 0, 150);
    TH1F *hTDORMS_L0POS = new TH1F("hTDORMS_L0POS", "TDO RMS positive  ", 500, 0, 150);
    TH1F *hTDOIntercept_L0 = new TH1F("hTDOIntercept_L0","TDO Intercept L0 negative  ", 400,-100,400);
    
    TH1F *hPDOSlope_L0 = new TH1F("hPDOSlope_L0","PDO Slope L0 negative  ", 200, -10,10);
    TH1F *hPDOIntercept_L0POS = new TH1F("hPDOIntercept_L0POS","PDO Intercept positive  ", 400,-200,800);
    TH1F *hPDOSlope_L0POS = new TH1F("hPDOSlope_L0POS","PDO Slope positive  ", 200, -10,10);
    
    TH1F *hTDOSlope_L0 = new TH1F("hTDOSlope_L0","TDO Slope negative  ", 200, -50,50);
    TH1F *hTDOIntercept_L0POS = new TH1F("hTDOIntercept_L0POS","TDO Intercept positive  ", 400,-100,400);
    TH1F *hTDOSlope_L0POS = new TH1F("hTDOSlope_L0POS","TDO Slope positive  ", 200, -50,50);
    
    //////   Entries
    
    TH2F *hPDOEntriesMEANL0 = new TH2F("hPDOEntriesMEANL0", "PDO entries mean L0 negative  ", 105, 1, 120,105,0,65);
    
    TH2F *hTDOEntriesMEANL0 = new TH2F("hTDOEntriesMEANL0", "TDO entries mean L0 negative  ", 105, 1, 120,105,0,65);
    
    TH2F *hPDOEntriesMEANL0POS = new TH2F("hPDOEntriesMEANL0POS", "PDO entries mean L0 positive  ", 105, 1, 120,105,0,65);
    
    TH2F *hTDOEntriesMEANL0POS = new TH2F("hTDOEntriesMEANL0POS", "TDO entries mean L0 positive  ", 105, 1, 120,105,0,65);
    
    TH2F *hEntriesARTneg = new TH2F("hEntriesARTneg", "ART negative entries  ", 105, 1, 70, 105, 0, 65);
    TH2F *hEntriesART = new TH2F("hEntriesART", "ART entries  ", 105, 1, 70, 105, 0, 65);
    
    TH2F *hEntriesARTpos = new TH2F("hEntriesARTpos", "ART positive entries  ", 105, 1, 70, 105, 0, 65);
    
  
    int CHANNEL[64];
    int sumcurrent_L0 = 0;
    int sumcurrent_L0POS = 0;
    for(int i=0; i<64;i++)
    {
        CHANNEL[i] = i;
    }
    
    if (fChain == 0) return;
   
    ///////   PDF
 
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        fChain->GetEntry(jentry);
        
        date->Set(dateTime);
        if(std::string(testMode).find("10_10_2018") != -1 && (VMMId == 1065 || VMMId == 1064 || VMMId == 1159 || VMMId == 1157 || VMMId == 1207 || VMMId == 1202) )
        {
            if (date->GetDay() == 16 && date->GetMonth() == 10)
            {
                for(int i = 0; i<64; i++)
                {
                    hBlinecor8->Fill(bLine[i],bLinePos[i]);
                }
            }
            
        }
        
        
        if(std::string(testMode).find("13_10_2018") != -1 && VMMId!=1202)
        {
            for (int i=0; i<64;i++)
            {
                if(bLinePos[i]>0)
                {
                    hBlinecor3->Fill(bLine[i],bLinePos[i]);
                }
            }
        }
        
        
        
        if(dateTime>1532000000)
        {
            
            
            for (int i=0; i<64;i++)
            {
                hblineTEMP->Fill(bLine[i],tempMax_L0);
                
                hbline->Fill(bLine[i]);
                hblineRMS->Fill(bLine_RMS[i]);
                hblineVMM->Fill(bLine[i], VMMId);
                hbline_RMS->Fill(PDORMS_L0[i],bLine[i]);
                
                
                
            }
            
            if(best_neg[jentry]>0){
                
                if(dateTime<1538*1000000 || std::string(testMode).find("CONFIGS_24_10_2018") != -1)
                {
                    for (int i=0; i<64;i++)
                    {
                        
                        if(bLinePos[i]>0)
                        {
                            if((VMMId == 1065 || VMMId == 1064 || VMMId == 1159 || VMMId == 1157 || VMMId == 1207) && std::string(testMode).find("10_10_2018") != 1)
                            {
                                hBlinecor9->Fill(bLine[i],bLinePos[i]);
                            }
                            
                            hBlinecor2->Fill(bLine[i],bLinePos[i]);
                            
                            if (chipStatus != 0)
                            {
                                hBlinecor21->Fill(bLine[i],bLinePos[i]);
                            }
                            
                            if(chipStatus == 6)
                            {
                                hBlinecor5->Fill(bLine[i],bLinePos[i]);
                            }
                            
                            if(chipStatus == 3)
                            {
                                hBlinecor6->Fill(bLine[i],bLinePos[i]);
                            }
                            
                            if(chipStatus == 1)
                            {
                                hBlinecor61->Fill(bLine[i],bLinePos[i]);
                            }
                            
                        }
                    }
                }
            }
            
            
            
            
            
            
            if(best_pos[jentry]>0){
                
                if(dateTime<1537*1000000)
                {
                    for (int i=0; i<64;i++)
                    {
                        
                        if(bLinePos[i]>0)
                        {
                           
                            if(chipStatus == 6)
                            {
                                hBlinecor5->Fill(bLine[i],bLinePos[i]);
                            }
                            if(chipStatus == 3)
                            {
                                hBlinecor6->Fill(bLine[i],bLinePos[i]);
                            }
                            if(chipStatus == 4)
                            {
                                hBlinecor7->Fill(bLine[i],bLinePos[i]);
                            }
                            
                            if(chipStatus == 2)
                            {
                                hBlinecor71->Fill(bLine[i],bLinePos[i]);
                            }
                        }
                    }
                }
            }
            
            
            
            
            
            numberVMM.push_back(VMMId);
            for (int i=0; i<64;i++)
            {
                hDDOneg->Fill(MEAN_DDO[i],CHANNEL[i]);
                hEntriesART->Fill(EntriesART[i],CHANNEL[i]);
            }
            
            
            hARTneg->Fill(VMMId,countBadCh_ART);
            
            if (countBadCh_ART>0 ){
                for(int i=0;i<countBadCh_ART;i++)
                {
                    hARTBad->Fill(numberBadCh_ART->at(i));
                }
            }
            if (countBadCh_ART>0 ){
                for (int i=0; i<countBadCh_ART;i++) {
                    hARTneg1->Fill(VMMId, numberBadCh_ART->at(i));
                }
            }
            
           
            if (tempMax_L0>0){
                if(best_neg[jentry]>0){
                    for (int i=0; i<64;i++)
                    {
                        
                        hALLCHANNEL->Fill(PDOMEAN_L0[i],CHANNEL[i]);
                        hALLCHANNELtdol0->Fill(TDOMEAN_L0[i],CHANNEL[i]);
                        hDDOnegneg_ch->Fill(MEAN_DDOneg[i], CHANNEL[i]);
                        hPDORMS_L0->Fill(PDORMS_L0[i]);
                        hPDOIntercept_L0->Fill(PDOIntercept_L0[i]);
                        hPDOSlope_L0->Fill(PDOSlope_L0[i]);
                        hTDORMS_L0->Fill(TDORMS_L0[i]);
                        hTDOIntercept_L0->Fill(TDOIntercept_L0[i]);
                        hTDOSlope_L0->Fill(TDOSlope_L0[i]);
                        hPDOEntriesMEANL0->Fill(PDOEntriesMEAN_L0[i],CHANNEL[i]);
                        hTDOEntriesMEANL0->Fill(TDOEntriesMEAN_L0[i],CHANNEL[i]);
                        hEntriesARTneg->Fill(EntriesARTneg[i],CHANNEL[i]);
                    }
                    
                    
                    if(dateTime>1536000000 && std::string(testMode).find("CONFIGS_24_10_2018") == -1)
                    {
                        for (int i=0; i<64;i++)
                        {
                            if(dateTime != 1536127466 && dateTime != 1536200702 && dateTime != 1536212145 && dateTime != 1536210917 && dateTime != 1536211173 && dateTime != 1536209925 && dateTime != 1536213514 && dateTime != 1536211781 && dateTime!=1536286129 && dateTime != 1536213216
                               && dateTime != 1536207793 && dateTime != 1536206943 && dateTime != 1536127698)
                            {
                                if(bLinePos[i]>0)
                                {
                                    hblvsrms->Fill(bLinePos[i],bLine_RMSPos[i]);
                                    hblnegvsblpos->Fill(bLine_RMS[i],bLine_RMSPos[i]);
                                    if(std::string(testMode).find("10_10_2018") != 1)
                                    {
                                        if(chipStatus>0)
                                        {
                                            hBlinecor->Fill(bLine[i],bLinePos[i]);
                                        }
                                        if(chipStatus==3)
                                        {
                                            hBlinecor11->Fill(bLine[i],bLinePos[i]);
                                        }
                                        if(chipStatus==1)
                                        {
                                            hBlinecor12->Fill(bLine[i],bLinePos[i]);
                                        }
                                        if(chipStatus==4)
                                        {
                                            hBlinecor13->Fill(bLine[i],bLinePos[i]);
                                        }
                                        if(chipStatus==2)
                                        {
                                            hBlinecor14->Fill(bLine[i],bLinePos[i]);
                                        }
                                    }
                                    
                                }
                            }
                            if(std::string(testMode).find("10_10_2018") != -1)
                            {
                                if(chipStatus>0)
                                {
                                    hBlinecor->Fill(bLine[i], bLinePos[i]);
                                }
                            }
                            
                            if(bLinePos[i]>0)
                            {
                                if(std::string(testMode).find("10_10_2018") != 1)
                                {
                                    hBlinecor_all->Fill(bLine[i],bLinePos[i]);
                                }
                            }
                            
                            if(std::string(testMode).find("10_10_2018") != -1)
                            {
                                hBlinecor_all->Fill(bLine[i], bLinePos[i]);
                            }
                        }
                    }
                    
                    
                    
                    htempA->Fill(tempMax_L0,VDAD_A_Max_L0);
                    htempAVDD->Fill(tempMax_L0,VDD_A_Max_L0);
                    htempAVDDD->Fill(tempMax_L0,VDDD_A_Max_L0);
                    htempAVDDP->Fill(tempMax_L0,VDDP_A_Max_L0);
                    hARTnegNEG->Fill(VMMId,countBadCh_ARTneg);
                    
                    
                    hsumcurrent_L0->Fill((VDDP_A_Max_L0 + VDDD_A_Max_L0 + VDAD_A_Max_L0 + VDD_A_Max_L0));
                    hVDD->Fill(VDD_A_Max_L0);
                    hVDDP->Fill(VDDP_A_Max_L0);
                    hVDDD->Fill(VDDD_A_Max_L0);
                    hVDAD->Fill(VDAD_A_Max_L0);
                    
                    if (countBadCh_ARTneg>0 ){
                        for(int i=0;i<countBadCh_ARTneg;i++)
                        {
                            hARTcountBad->Fill(numberBadCh_ARTneg->at(i));
                        }
                    }
                    
                    
                    
                    
                    if (countBadCh_ARTneg>0 ){
                        for (int i=0; i<countBadCh_ARTneg;i++) {
                            hARTnegNEG1->Fill(VMMId, numberBadCh_ARTneg->at(i));
                        }
                    }
                }
            }
            
            
            if (tempMax_L0POS>0)
            {
                if(best_pos[jentry]>0)
                {
                    
                    for (int i=0; i<64;i++)
                    {
                        
                        hALLCHANNELpdol0pos->Fill(PDOMEAN_L0POS[i],CHANNEL[i]);
                        hALLCHANNELtdol0pos->Fill(TDOMEAN_L0POS[i],CHANNEL[i]);
                        hDDOpos_ch->Fill(MEAN_DDOpos[i], CHANNEL[i]);
                        hTDORMS_L0POS->Fill(TDORMS_L0POS[i]);
                        hTDOIntercept_L0POS->Fill(TDOIntercept_L0POS[i]);
                        hTDOSlope_L0POS->Fill(TDOSlope_L0POS[i]);
                        hPDORMS_L0POS->Fill(PDORMS_L0POS[i]);
                        hPDOIntercept_L0POS->Fill(PDOIntercept_L0POS[i]);
                        hPDOSlope_L0POS->Fill(PDOSlope_L0POS[i]);
                        hPDOEntriesMEANL0POS->Fill(PDOEntriesMEAN_L0POS[i],CHANNEL[i]);
                        hTDOEntriesMEANL0POS->Fill(TDOEntriesMEAN_L0POS[i],CHANNEL[i]);
                        hEntriesARTpos->Fill(EntriesARTpos[i],CHANNEL[i]);
                    }
                    htempApos->Fill(tempMax_L0POS,VDAD_A_Max_L0POS);
                    htempAVDDpos->Fill(tempMax_L0POS,VDD_A_Max_L0POS);
                    htempAVDDDpos->Fill(tempMax_L0POS,VDDD_A_Max_L0POS);
                    htempAVDDPpos->Fill(tempMax_L0POS,VDDP_A_Max_L0POS);
                    hARTpos->Fill(VMMId,countBadCh_ARTpos);
                    
                    hsumcurrent_L0POS->Fill((VDDP_A_Max_L0POS + VDDD_A_Max_L0POS + VDAD_A_Max_L0POS + VDD_A_Max_L0POS));
                    hVDDpos->Fill(VDD_A_Max_L0POS);
                    hVDDPpos->Fill(VDDP_A_Max_L0POS);
                    hVDDDpos->Fill(VDDD_A_Max_L0POS);
                    hVDADpos->Fill(VDAD_A_Max_L0POS);
                    
                    if (countBadCh_ARTpos>0 ){
                        for(int i=0;i<countBadCh_ARTpos;i++)
                        {
                            hARTposcountBad->Fill(numberBadCh_ARTpos->at(i));
                        }
                    }
                    
                    if (countBadCh_ARTpos>0 ){
                        for (int i=0; i<countBadCh_ARTpos;i++) {
                            hARTpos2->Fill(VMMId, numberBadCh_ARTpos->at(i));
                        }
                    }}
            }
            
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            
            
        }}
    
    cout<<"number  +++++++"<< numberVMM.size()<<"+++++++"<<endl;
    
    
    
    ///////  PDF
    
    
    ///// bline
    gCnv->Divide(1,1);
    gStyle->SetOptFit(2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hbline->Draw("colz");
    hbline->SetXTitle("mV");
    hbline->SetYTitle("count channels");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    
    gCnv->cd(1);
    hbline->Draw("colz");
    hbline->SetXTitle("mV");
    hbline->SetYTitle("count channels");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    
    hblineVMM->Draw("colz");
    hblineVMM->SetYTitle("VMMId");
    hblineVMM->SetXTitle("Baseline, mV");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    
    gCnv->cd(1);
    
    hblineTEMP->Draw("colz");
    hblineTEMP->SetYTitle("temp, C");
    hblineTEMP->SetXTitle("Baseline, mV");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    ////////// RMS
   
    //    /////////// correlia
  
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hBlinecor->Draw("colz");
    hBlinecor->SetXTitle("baseline NEG, mV");
    hBlinecor->SetYTitle("baseline POS, mV");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    ////// mean criteria
    gCnv->Divide(1,1);
    
    gCnv->cd(1);
    hALLCHANNEL->Draw("colz");
    hALLCHANNEL->SetXTitle("ADC");
    hALLCHANNEL->SetYTitle("channel");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    
    hPDOEntriesMEANL0->Draw("colz");
    hPDOEntriesMEANL0->SetXTitle("Entries");
    hPDOEntriesMEANL0->SetYTitle("channel");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hALLCHANNELtdol0->Draw("colz");
    hALLCHANNELtdol0->SetXTitle("ADC");
    hALLCHANNELtdol0->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    
    hTDOEntriesMEANL0->Draw("colz");
    hTDOEntriesMEANL0->SetXTitle("Entries");
    hTDOEntriesMEANL0->SetYTitle("channel");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    //////////   positive
    
    gCnv->Divide(1,1);
    
    gCnv->cd(1);
    hALLCHANNELpdol0pos->Draw("colz");
    hALLCHANNELpdol0pos->SetXTitle("ADC");
    hALLCHANNELpdol0pos->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hPDOEntriesMEANL0POS->Draw("colz");
    hPDOEntriesMEANL0POS->SetXTitle("Entries");
    hPDOEntriesMEANL0POS->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hALLCHANNELtdol0pos->Draw("colz");
    hALLCHANNELtdol0pos->SetXTitle("ADC");
    hALLCHANNELtdol0pos->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hTDOEntriesMEANL0POS->Draw("colz");
    hTDOEntriesMEANL0POS->SetXTitle("Entries");
    hTDOEntriesMEANL0POS->SetYTitle("channel");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    ////////    DDO
    //    gCnv->Divide(1,1);
    //    gCnv->cd(1);
    //    hDDOneg->Draw("colz");
    //    hDDOneg->SetXTitle("ADC");
    //    hDDOneg->SetYTitle("channel");
    //    gCnv->Print(pdfname, "pdf");
    //    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hDDOnegneg_ch->Draw("colz");
    hDDOnegneg_ch->SetXTitle("ADC");
    hDDOnegneg_ch->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hDDOpos_ch->Draw("colz");
    hDDOpos_ch->SetXTitle("ADC");
    hDDOpos_ch->SetYTitle("channel");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    
    /////  currents L0
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hVDD->Draw("colz");
    hVDD->SetXTitle("Current, A");
    hVDD->SetYTitle("count VMMId");
    
    gCnv->cd(2);
    
    gPad->SetLogy();
    hVDDpos->Draw("colz");
    hVDDpos->SetXTitle("Current, A");
    hVDDpos->SetYTitle("count VMMId");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,2);
    gCnv->cd(1);
    gPad->SetLogy();
    hVDDP->Draw("colz");
    hVDDP->SetXTitle("Current, A");
    hVDDP->SetYTitle("count VMMId");
    
    
    gCnv->cd(2);
    gPad->SetLogy();
    hVDDPpos->Draw("colz");
    hVDDPpos->SetXTitle("Current, A");
    hVDDPpos->SetYTitle("count VMMId");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    //////// 2
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hVDDD->Draw("colz");
    hVDDD->SetXTitle("Current, A");
    hVDDD->SetYTitle("count VMMId");
    
    gCnv->cd(2);
    
    gPad->SetLogy();
    hVDDDpos->Draw("colz");
    hVDDDpos->SetXTitle("Current, A");
    hVDDDpos->SetYTitle("count VMMId");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,2);
    gCnv->cd(1); gPad->SetLogy();
    hVDAD->Draw("colz");
    hVDAD->SetXTitle("Current, A");
    hVDAD->SetYTitle("count VMMId");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hVDADpos->Draw("colz");
    hVDADpos->SetXTitle("Current, A");
    hVDADpos->SetYTitle("count VMMId");
    
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    
    
    htempAVDD->Draw("colz");
    htempAVDD->SetXTitle("temp, C");
    htempAVDD->SetYTitle("current");
    
    gCnv->cd(2);
    
    htempAVDDpos->Draw("colz");
    htempAVDDpos->SetXTitle("temp, C");
    htempAVDDpos->SetYTitle("current");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,2);
    gCnv->cd(1);
    htempAVDDP->Draw("colz");
    htempAVDDP->SetXTitle("temp, C");
    htempAVDDP->SetYTitle("current");
    
    gCnv->cd(2);
    
    htempAVDDPpos->Draw("colz");
    htempAVDDPpos->SetXTitle("temp, C");
    htempAVDDPpos->SetYTitle("current");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    
    
    //////// 4
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    htempAVDDD->Draw("colz");
    htempAVDDD->SetXTitle("temp, C");
    htempAVDDD->SetYTitle("current");
    
    gCnv->cd(2);
    
    htempAVDDDpos->Draw("colz");
    htempAVDDDpos->SetXTitle("temp, C");
    htempAVDDDpos->SetYTitle("current");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,2);
    gCnv->cd(1);
    
    htempA->Draw("colz");
    htempA->SetXTitle("temp, C");
    htempA->SetYTitle("current");
    
    
    gCnv->cd(2);
    
    htempApos->Draw("colz");
    htempApos->SetXTitle("temp, C");
    htempApos->SetYTitle("current");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    //////  5
    
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hsumcurrent_L0->Draw("colz");
    hsumcurrent_L0->SetXTitle("Current, A");
    hsumcurrent_L0->SetYTitle("count VMMId");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hsumcurrent_L0POS->Draw("colz");
    hsumcurrent_L0POS->SetXTitle("Current, A");
    hsumcurrent_L0POS->SetYTitle("count VMMId");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    //////////////////
    gCnv->Divide(1,1);
    
    
    gCnv->cd(1);
    hARTnegNEG->Draw("colz");
    hARTnegNEG->SetXTitle("VMMId");
    hARTnegNEG->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hEntriesARTneg->Draw("colz");
    hEntriesARTneg->SetXTitle("entries");
    hEntriesARTneg->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hARTnegNEG1->Draw("colz");
    hARTnegNEG1->SetXTitle("VMMId");
    hARTnegNEG1->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    gStyle->SetOptStat("e");
    hARTcountBad->Draw("colz");
    hARTcountBad->SetXTitle("channel");
    hARTcountBad->SetYTitle("count bad ART");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    gCnv->Divide(1,1);
    
    gStyle->SetOptStat("eou");
    
    gCnv->cd(1);
    hARTpos->Draw("colz");
    hARTpos->SetXTitle("VMMId");
    hARTpos->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hEntriesARTpos->Draw("colz");
    hEntriesARTpos->SetXTitle("entries");
    hEntriesARTpos->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    hARTpos2->Draw("colz");
    hARTpos2->SetXTitle("VMMId");
    hARTpos2->SetYTitle("channel");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    gStyle->SetOptStat("e");
    hARTposcountBad->Draw("colz");
    hARTposcountBad->SetXTitle("channel");
    hARTposcountBad->SetYTitle("count bad ART");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    
    
    
    ///  L0 neg
    gStyle->SetOptStat("eou");
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hPDORMS_L0->Draw("colz");
    hPDORMS_L0->SetXTitle("RMS");
    hPDORMS_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hPDORMS_L0POS->Draw("colz");
    hPDORMS_L0POS->SetXTitle("RMS");
    hPDORMS_L0POS->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    gCnv->Divide(1,1);
    gCnv->cd(1);
    gPad->SetLogy();
    hblineRMS->Draw("colz");
    hblineRMS->SetXTitle("RMS");
    hblineRMS->SetYTitle("count channels");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    /////////////
    gCnv->Divide(1,2);
    gCnv->cd(1);
    gPad->SetLogy();
    hPDOIntercept_L0->Draw("colz");
    hPDOIntercept_L0->SetXTitle("b");
    hPDOIntercept_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hPDOIntercept_L0POS->Draw("colz");
    hPDOIntercept_L0POS->SetXTitle("b");
    hPDOIntercept_L0POS->SetYTitle("count channels");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    // L0 pos
    
    gCnv->Divide(1,2);
    
    
    gCnv->cd(1);
    gPad->SetLogy();
    hPDOSlope_L0->Draw("colz");
    hPDOSlope_L0->SetXTitle("a");
    hPDOSlope_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hPDOSlope_L0POS->Draw("colz");
    hPDOSlope_L0POS->SetXTitle("a");
    hPDOSlope_L0POS->SetYTitle("count channels");
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    /// TDO L0 neg
    
    gCnv->Divide(1,2);
    
    gCnv->cd(1);
    gPad->SetLogy();
    hTDORMS_L0->Draw("colz");
    hTDORMS_L0->SetXTitle("RMS");
    hTDORMS_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hTDORMS_L0POS->Draw("colz");
    hTDORMS_L0POS->SetXTitle("RMS");
    hTDORMS_L0POS->SetYTitle("count channels");
    
   
    
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
     ///////////////////////////////
    
    gCnv->Divide(1,2);
    gCnv->cd(1);
    gPad->SetLogy();
    hTDOIntercept_L0->Draw("colz");
    hTDOIntercept_L0->SetXTitle("b");
    hTDOIntercept_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hTDOIntercept_L0POS->Draw("colz");
    hTDOIntercept_L0POS->SetXTitle("b");
    hTDOIntercept_L0POS->SetYTitle("count channels");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    /////////////////
    gCnv->Divide(1,2);
    gCnv->cd(1);
    gPad->SetLogy();
    hTDOSlope_L0->Draw("colz");
    hTDOSlope_L0->SetXTitle("a");
    hTDOSlope_L0->SetYTitle("count channels");
    
    gCnv->cd(2);
    gPad->SetLogy();
    hTDOSlope_L0POS->Draw("colz");
    gCnv->Print(pdfname, "pdf");
    gCnv->Clear();
    
    
    
    hALLCHANNEL->Reset();
    hALLCHANNELtdol0 ->Reset();
    hALLCHANNELpdol0pos ->Reset();
    
    hALLCHANNELtdol0pos ->Reset();
    
    hDDOnegneg_ch ->Reset();
    
    hDDOpos_ch ->Reset();
    
    hARTnegNEG ->Reset();
    hARTpos ->Reset();
    
    hARTnegNEG1 ->Reset();
    hARTpos2 ->Reset();
    htempA ->Reset();
    htempAVDD ->Reset();
    htempAVDDD ->Reset();
    htempAVDDP ->Reset();
    
    htempApos ->Reset();
    htempAVDDpos ->Reset();
    htempAVDDDpos ->Reset();
    htempAVDDPpos ->Reset();
    
    hsumcurrent_L0 ->Reset();
    hsumcurrent_L0POS ->Reset();
    
    hVDD ->Reset();
    hVDDP ->Reset();
    hVDDD ->Reset();
    hVDAD ->Reset();
    
    hVDDpos ->Reset();
    hVDDPpos ->Reset();
    hVDDDpos ->Reset();
    hVDADpos ->Reset();
    hARTcountBad ->Reset();
    hARTposcountBad ->Reset();
    hbline ->Reset();
    hblineRMS ->Reset();
    hblineVMM ->Reset();

    
    hblineTEMP ->Reset();
    hbline_RMS ->Reset();
   
    hPDORMS_L0 ->Reset();
    hPDORMS_L0POS ->Reset();
    hPDOIntercept_L0 ->Reset();
    
    hTDORMS_L0 ->Reset();
    hTDORMS_L0POS ->Reset();
    hTDOIntercept_L0 ->Reset();
    
    hPDOSlope_L0 ->Reset();
    hPDOIntercept_L0POS ->Reset();
    hPDOSlope_L0POS ->Reset();
    
    hTDOSlope_L0->Reset();
    hTDOIntercept_L0POS->Reset();
    hTDOSlope_L0POS ->Reset();
    hPDOEntriesMEANL0 ->Reset();
    
    hTDOEntriesMEANL0 ->Reset();
    
    hPDOEntriesMEANL0POS->Reset();
    
    hTDOEntriesMEANL0POS ->Reset();
    
    hEntriesARTneg ->Reset();
    hEntriesARTpos->Reset();
    
    gCnv->Print(pdfclose, "pdf");
    gCnv->Clear();
    delete gCnv;
  
    
    
    
    //////*********************link************************************
    
    
    
    int kol = 0;
    for(int i = 0; i<nentries; i++)
    {
       
        if (best_neg[i]>0 && best_neg[i]!=2403 && best_neg[i]!=2518 && best_neg[i]<10000)
        {
            kol ++;
            baseData<<"**********************************************************"<<endl;
            baseData<<"chip_id : "<<best_neg[i]<<" "<<series[i]<<" ";
        }
        
            if (status[i] != 0)
            {
                baseData<<"        "<<VMMStatus[i];
            }
           baseData<<endl;
            
            
            if (best_neg[i]>0 && best_neg[i]!=2403 && best_neg[i]!=2518 && best_neg[i]<10000)
            {
            baseData<<"CONF : "<<"NEG"<<endl;
            baseData<<"Status : ";
            
            if(status1[i] == 0)
            {
                baseData<<"Failed";
            } else {
                if(status1[i] == 1)
                {
                    baseData<<"Passed neg";
                } else{
                    if(status1[i] == 2)
                    {
                        baseData<<"Passed pos";
                    }else{
                        if(status1[i] == 3)
                        {
                            baseData<<"BOMB neg";
                        } else {
                            if(status1[i] == 4)
                            {
                                baseData<<"BOMB pos";
                            } else {
                                if(status1[i] == 5)
                                {
                                    baseData<<"Passed";
                                } else {
                                    if(status1[i] == 6)
                                    {
                                        baseData<<"BOMB";
                                    }
                                }
                            }
                        }
                    }
                }
            }
            baseData<<" "<<endl;
            
            baseData<<"failed : "<<fail[i]<<endl;
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/constants";
            baseData<<"/"<<status_pro[i]<<"_const_";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
                baseData<<"NEG";
            baseData<<".txt"<<endl;
            
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/pdf";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
                baseData<<"NEG";
            baseData<<".pdf"<<endl;
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_BLine";
            baseData<<".root"<<endl;
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_ARTneg";
            baseData<<".root"<<endl;
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_L0_PDO";
            baseData<<".root"<<endl;
            
            
            
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_L0_TDO";
            baseData<<".root"<<endl;
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_DDOneg";
            baseData<<".root"<<endl;
            
            //            baseData<<"chipStatus :"<<status[i]<<endl;
        }
        if (best_neg[i]==2403 || best_neg[i]==2518)
        {
            baseData<<"**********************************************************"<<endl;
            baseData<<"chip_id : "<<best_neg[i]<<" "<<series[i]<<" "<<endl;
            baseData<<"CONF : "<<"NEG"<<endl;
            baseData<<"Status : "<<"No Data"<<endl;
            
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_neg[i]/10 == 0)
            {
                baseData<<"000"<<best_neg[i];
            } else{
                if(best_neg[i]/100 == 0)
                {
                    baseData<<"00"<<best_neg[i];
                }else{
                    if(best_neg[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_neg[i];
                    } else{
                        baseData<<best_neg[i];
                    }
                }
            }
            baseData<<"_BLine";
            baseData<<".root"<<endl;
        }
    }
    
    
    for(int i = 0; i<nentries; i++)
    {

        if (best_pos[i]>0 && best_pos[i]!=1327 && best_pos[i]<10000)
        {
            baseData<<"**********************************************************"<<endl;
            baseData<<"chip_id : "<<best_pos[i]<<" "<<series[i];
        }
        
        
//        if (status[i] != 0)
//            {
//                baseData<<"        "<<VMMStatus[i];
//            }
            baseData<<endl;
            
        if (best_pos[i]>0 && best_pos[i]!=1327 && best_pos[i]<10000)
        {
            
            baseData<<"CONF : "<<"POS"<<endl;
            //        baseData<<"Status POS : "<<statusPOS[i]<<endl;

            baseData<<"Status : ";

            if(status1[i] == 0)
            {
                baseData<<"Failed"<<endl;
            } else {
                if(status1[i] == 1)
                {
                    baseData<<"Passed neg"<<endl;
                } else{
                    if(status1[i] == 2)
                    {
                        baseData<<"Passed pos"<<endl;
                    }else{
                        if(status1[i] == 3)
                        {
                            baseData<<"BOMB neg"<<endl;
                        } else {
                            if(status1[i] == 4)
                            {
                                baseData<<"BOMB pos"<<endl;
                            } else {
                                if(status1[i] == 5)
                                {
                                    baseData<<"Passed"<<endl;
                                } else {
                                    if(status1[i] == 6)
                                    {
                                        baseData<<"BOMB"<<endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            baseData<<"failed : "<<fail[i]<<endl;


            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/constants";
           baseData<<"/"<<status_pro[i]<<"_const_";

            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"POS";
            baseData<<".txt"<<endl;
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/pdf";
            baseData<<"/";
            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"POS";
            baseData<<".pdf"<<endl;
            if(VMM_BL[i]!=0)
            {
                baseData<<link;
                if(day[i]/10 == 0)
                {
                    baseData<<"0"<<day[i];
                }else{
                    baseData<<day[i];
                }
                if(month[i]/10 == 0)
                {
                    baseData<<"0"<<month[i];
                }else{
                    baseData<<month[i];
                }
                baseData<<year[i]<<"/root";
                baseData<<"/";
                if(best_pos[i]/10 == 0)
                {
                    baseData<<"000"<<best_pos[i];
                } else{
                    if(best_pos[i]/100 == 0)
                    {
                        baseData<<"00"<<best_pos[i];
                    }else{
                        if(best_pos[i]/1000 == 0)
                        {
                            baseData<<"0"<<best_pos[i];
                        } else{
                            baseData<<best_pos[i];
                        }
                    }
                }


                baseData<<"_BLinepos";


                baseData<<".root"<<endl;
            }
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"_ARTpos";
            baseData<<".root"<<endl;
            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"_L0pos_PDO";
            baseData<<".root"<<endl;

            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"_L0pos_TDO";
            baseData<<".root"<<endl;

            baseData<<link;
            if(day[i]/10 == 0)
            {
                baseData<<"0"<<day[i];
            }else{
                baseData<<day[i];
            }
            if(month[i]/10 == 0)
            {
                baseData<<"0"<<month[i];
            }else{
                baseData<<month[i];
            }
            baseData<<year[i]<<"/root";
            baseData<<"/";
            if(best_pos[i]/10 == 0)
            {
                baseData<<"000"<<best_pos[i];
            } else{
                if(best_pos[i]/100 == 0)
                {
                    baseData<<"00"<<best_pos[i];
                }else{
                    if(best_pos[i]/1000 == 0)
                    {
                        baseData<<"0"<<best_pos[i];
                    } else{
                        baseData<<best_pos[i];
                    }
                }
            }
            baseData<<"_DDOpos";
            baseData<<".root"<<endl;

        }
    }
    
    baseData.close();
}



