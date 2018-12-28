#include "VMM_CalcTemp.cxx"
#include "VMM_ReadHeader.cxx"
#include "VMM_ReadEvents.cxx"
#include "VMM_LoadTest.cxx"
#include "VMM_ART.cxx"

using namespace std;

namespace VMMCalibration {

TH1I *hf[6];
    
bool chn_notdead[64], chn_ne[64], chIll[64];

void build_NumberOfEvents(test_t *test, int numEvent = 0) {
    char title[256];
    sprintf(title, "Number of events. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold", test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "Entries_SKEW_%f", test->SKEW);

    TH1I *h = new TH1I(title, title, 64, 0, 64);
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Channel number");
    h->SetYTitle("Number of events");

    int num_events[64];
    memset(num_events, 0, sizeof(num_events));
    
//    for (int i = 0; i < 64; i++) {
//        test->entries[i] = 0;
//    }
    

    for(int i = 0; i < test->num_events; i++) {
        h->Fill(test->events[i].channel);
       // if(test->events[i].threshold) {
            if (test->events[i].channel > 63) cout << "\n  number ch > 63";
                else {
                    num_events[test->events[i].channel]++;
                    //test->entries[test->events[i].channel]++;
                }
      //  }
    }

    for(int i = 0; i < 64; i++) {

    if ((num_events[i] > 0 && !chn_notdead[i])) {
        chIll[i] = 1;
        chn_notdead[i] = 1;
    }

        if( (num_events[i] == 0 || test->meanPDO[i] == 0) && !chIll[i]) {
            chn_notdead[i] = 0;
        } //else chn_notdead[i] = 0;
    }
    h->Draw();
    h->Write();

    hf[0] = h;
}

void build_ChannelsInEvent(test_t *test)
{

    char title[256];
    sprintf(title, "Channels in event. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold", test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i DAC ,Channels_SKEW_%f", test->DAC, test->SKEW);

    TH1I *h = new TH1I(name, title, 65, 0, 65);
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Number of channels");
    h->SetYTitle("Number of events");


    for(int i = 0; i < test->num_events; i++)
    {
        
        h->Fill(test->chip_id);
    }
    h->Draw();
    h->Write();

    hf[1] = h;
}

void build_PDOmean(test_t *test)
{
    
    char title[256];
    sprintf(title, "%s ADC Mean value. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold", addNameToHistogram.c_str(), test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i_DAC_mean_SKEW_%f",test->DAC, test->SKEW);
    
    TH1I *h = new TH1I(name, title, 64, 0, 64);
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Channel number");
    h->SetYTitle("ADC mean");
    h->GetYaxis()->SetTitleOffset(1.0);

    int sum[64];
    int num[64];
    memset(sum, 0, sizeof(sum));
    memset(num, 0, sizeof(num));

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold)
        //if (1)
        {
            sum[test->events[i].channel] += test->events[i].amp;
            num[test->events[i].channel]++;
        }
    }

    for (int i = 0; i < 64; i++)
    {
        float val = num[i] ? (sum[i] / num[i]) : 0;
        //int val = (sum[i] / num[i]);

        test->meanPDO[i] = val;

        for( int o = 0; o < val; o++ )
            h->Fill(i);
    }
    
    h->Draw();
    h->Write();

    hf[2] = h;

}

void build_PDOrms(test_t *test)
{
    char title[256];
    sprintf(title, "%s ADC RMS value. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str(), test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i DAC, rms_SKEW_%f",test->DAC, test->SKEW);

    TH1I *h = new TH1I(name, title, 64, 0, 64); // ?????? ???????? TH1D
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Channel number");
    h->SetYTitle("RMS ADC");

    char nameRMS_mV[256];
    char titleRMS_mV[256];
    sprintf(nameRMS_mV, "RMS mV_CH  DAC %i", test->DAC); // @Ser
    sprintf(titleRMS_mV, "%s RMS mV value. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str(), test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    double sum[64];
    double num[64];
    double mean[64];
    memset(sum, 0, sizeof(sum));
    memset(num, 0, sizeof(num));

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold)
        {
            sum[test->events[i].channel] += test->events[i].amp;
            num[test->events[i].channel]++;
        }
    }

    for(int i = 0; i < 64; i++)
    {
        mean[i] = num[i] ? (sum[i] / num[i]) : 0.0;
        sum[i] = 0.0;
    }

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold)
        {
            double val = test->events[i].amp - mean[test->events[i].channel];
            sum[test->events[i].channel] += val * val;
        }
    }

    for(int i = 0; i < 64; i++) {

        double rms = 0;

        rms = sqrt(sum[i] / (num[i] - 1.0));

        h->SetBinContent(i + 1, rms);
        if (chn_notdead[i]) {


                        if (isContinuous) {
  							if (rms > limitRMS_PDO_CONT) chn_ne[i] = 1;

                        }
                        else if (isDDOCONT) {
                        	if (rms > limitRMS_PDO_DDO) chn_ne[i] = 1;
                        }   else if (isL0) {
                        	if (rms > limitRMS_PDO_L0) chn_ne[i] = 1;
                        } else if (isL0POS) {
                            if (rms > limitRMS_PDO_L0) chn_ne[i] = 1;
                        }
        }
    }

    h->Draw();
    h->Write();

    hf[3] = h;
}

void build_TDOmean(test_t *test)
{
    char title[256];
    sprintf(title, "%s TDO Mean value. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.",addNameToHistogram.c_str() ,test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i_DAC_TDOmean_SKEW_%f",test->DAC, test->SKEW);

    TH1I *h = new TH1I(name, title, 64, 0, 64);
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Channel number");
    h->SetYTitle("TDO mean");

    int sum[64];
    int num[64];
    memset(sum, 0, sizeof(sum));
    memset(num, 0, sizeof(num));

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold)
        {
            sum[test->events[i].channel] += test->events[i].time;
            num[test->events[i].channel]++;
        }
    }



    for(int i = 0; i < 64; i++)
    {
        float val = num[i] ? (sum[i] / num[i]) : 0;

        //test->meanTDO[i] = val;

        for( int o = 0; o < val; o++ )
            h->Fill(i);
        
    }
    
    if (test->DAC == currentNameFilesPDO[1]) isFirstMEANTDO = false;
    h->Draw();
    h->Write();

    hf[4] = h;
}

void build_TDOrms(test_t *test)
{
    char title[256];
    sprintf(title, "%s TDO RMS value. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", test_mode_path, test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i_DAC_TDOrms_SKEW_%f",test->DAC, test->SKEW);

    TH1I *h = new TH1I(name, title, 64, 0, 64); // ?????? ???????????? ???????? double
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("Channel number");
    h->SetYTitle("RMS TDO");

    double sum[64];
    double num[64];
    double mean[64];
    memset(sum, 0, sizeof(sum));
    memset(num, 0, sizeof(num));

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold)
        {
            sum[test->events[i].channel] += test->events[i].time;
            num[test->events[i].channel]++;
        }
    }

    for(int i = 0; i < 64; i++)
    {
        mean[i] = num[i] ? (sum[i] / num[i]) : 0.0;
        sum[i] = 0.0;
    }

    for(int i = 0; i < test->num_events; i++)
    {
        if(test->events[i].threshold) {
            double val = test->events[i].time - mean[test->events[i].channel];
            sum[test->events[i].channel] += val * val;
        }
    }

    for(int i = 0; i < 64; i++)
    {
        double rms = sqrt(sum[i] / (num[i] - 1.0));

        test->rmsTDO[i] = rms;

        h->SetBinContent(i + 1, rms);
    }
    h->Draw();
    h->Write();

    hf[5] = h;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
    void Build_ChannelAllChRelBCID(test_t *test, TH2I *hReturn) // 2D hist BCID
    {
        char title[256];
        sprintf(title, "RelBCID %s ADC. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str(), test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);
        
        char name[256];
        sprintf(name, "RelBCID %i DAC, SKEW=%f ALL_CH", test->DAC, test->SKEW);
        
        TH2I *h = new TH2I(name, title, 10, 0, 10, 64, 0, 64);
        
        h->SetLineColor(4);
        h->SetFillColor(34);
        h->SetXTitle("BCID");
        h->SetYTitle("CH");
        
        for(int i = 0; i < test->num_events; i++) {
           // if(test->events[i].threshold)
                h->Fill(test->events[i].bcid, test->events[i].channel);
        }
    
        h->SetOption("COLZ");
        //gStyle->SetOptStat("eou");
        
        h->Draw();
        
        if ( h->GetEntries()) {
            h->Write();
        }
        
        //gCnv->Clear();
        hReturn = h;
        //delete h;
    }
    
    void Build_ChannelAllChPDO(test_t *test, TH2I *hReturn) // 2D hist PDO
    {
        
//        gStyle->SetOptStat(111110110);
        
        char title[256];
        sprintf(title, "%s ADC. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str() , test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);
        
        char name[256];
        sprintf(name, "%i DAC, SKEW=%f ALL_CH", test->DAC, test->SKEW);
        
        TH2I *h = new TH2I(name, title, std::pow(2, bitSize) - 1, 1, std::pow(2, bitSize) - 1, 64, 0, 64);
        
        h->SetLineColor(4);
        h->SetFillColor(34);
        h->SetXTitle("ADC");
        h->SetYTitle("CH");
        
        for(int i = 0; i < test->num_events; i++) {
                if(test->events[i].threshold)
                    h->Fill(test->events[i].amp, test->events[i].channel);
        }
        
//        gStyle->SetOptStat(111111);
        h->SetOption("COLZ");
        h->Draw();
        
        if ( h->GetEntries()) {
            h->Write();
        }
        
        //gCnv->Clear();
        
        hReturn = h;
        
        //delete h;
    }

void Build_ChannelPDO(test_t *test, int channel) // ?????????? ???????????????? ???? PDO
{
    char title[256];
    sprintf(title, "%s Channel %i ADC. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str(),channel, test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i DAC, SKEW=%f_CH%i", test->DAC, test->SKEW, channel);
    // ???????????? ???????????????????????? PDO_mv
    TH1I *h = new TH1I(name, title, std::pow(2, bitSize), 0, std::pow(2, bitSize));

    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("ADC");
    h->SetYTitle("Number of events");
    // ?????????????????? ????????????????????????
    for(int i = 0; i < test->num_events; i++) {
        if(test->events[i].channel == channel)
                //if(test->events[i].threshold)
                    h->Fill(test->events[i].amp);
    }
    
    h->Draw();

//    gCnv->Clear();
    test->numEntries[channel] = h->GetEntries();
    if (test->numEntries[channel]) {
        test->meanPDO[channel] = h->GetMean();
        test->rmsPDO[channel] = h->GetRMS();
         h->Write();
        
        if (isFirstMEANPDO) {
            
//            for (int h = 0; AMPDACMEAN.size(); h++) {
//                if(test->DAC == AMPDACMEAN[h]) isFirstMEANTDO = false;
//            }
            
            for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
                if(test->DAC == AMPDACMEAN[pp]) {
                    meanPDO[channel] = h->GetMean();
                    entriesMeanPDO[channel] = h->GetEntries();
                }
            }
            
        }
        
    } else {
        test->meanPDO[channel] = nonCorrectValue;
        test->rmsPDO[channel] = nonCorrectValue;
        
        if (isFirstMEANPDO) {
            
                        for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
                            if(test->DAC == AMPDACMEAN[pp]) {
                                meanPDO[channel] = nonCorrectValue;
                                entriesMeanPDO[channel] = 0;
                                
                            }
                        }
            
//
//            if(test->DAC == AMPDACMEAN) {
//                meanPDO[channel] = nonCorrectValue;
//                entriesMeanPDO[channel] = 0;
//
//            }
        }
        
        
        
    }
       
    delete h;
}
    
    void Build_ChannelAllChTDO(test_t *test, TH2I *hReturn ) { // 2D HIST TDO
        char title[256];
        sprintf(title, "%s TDO. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", addNameToHistogram.c_str(), test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);
        
        char name[256];
        sprintf(name, "%i DAC,TDO_SKEW=%f all ch TDO",test->DAC, test->SKEW);
        
//        sprintf(name, "%i DAC, SKEW=%f ALL_CH", test->DAC, test->SKEW);
        
        TH2I *h = new TH2I(name, title, 256, 0, 256, 64, 0, 64);
        
        
//        TH1I *h = new TH1I(name, title, 256, 0, 256);
        h->SetLineColor(4);
        h->SetFillColor(34);
        h->SetXTitle("TDO");
        h->SetYTitle("CH");
        // ?????????????????? ????????????????????????
        for(int i = 0; i < test->num_events; i++) {
               // if(test->events[i].threshold)
                    h->Fill(test->events[i].time, test->events[i].channel);
        }
        
        h->SetOption("COLZ");
        //gStyle->SetOptStat("eou");
        h->Draw();
        
//        gCnv->Clear();
        
        if (h->GetEntries()) {
            h->Write();
        }
        
        hReturn = h;
        //delete h;
    }
    

void Build_ChannelTDO(test_t *test, int channel, bool isTDOCalib = false){ // ?????????? ???????????????? ???? ???????????????????? TDO_SKEW
    char title[256];
    sprintf(title, "Channel %i TDO. %i DAC. %i TAC. %.1f Gain. %i Peaking time, %i Threshold.", channel, test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];
    sprintf(name, "%i DAC,TDO_SKEW=%f_CH%i",test->DAC, test->SKEW, channel);

    TH1I *h = new TH1I(name, title, 256, 0, 256);
    h->SetLineColor(4);
    h->SetFillColor(34);
    h->SetXTitle("TDO");
    h->SetYTitle("Number of events");
    // ?????????????????? ????????????????????????
    for(int i = 0; i < test->num_events; i++) {
        if(test->events[i].channel == channel)
            if(test->events[i].threshold)
                h->Fill(test->events[i].time);
    }

    h->Draw();
    


    //gCnv->Clear();
    
    test->numEntries[channel] = h->GetEntries();
    
    if(test->numEntries[channel]) {
        test->rmsTDO[channel] = h->GetRMS();
        test->meanTDO[channel]=h->GetMean();
        
        if (isFirstMEANTDO) {
            
            
            for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
                if(test->DAC == AMPDACMEAN[pp]) {
                        meanTDO[channel] = h->GetMean();
                        entriesMeanTDO[channel] = h->GetEntries();
                }
            }
            
//            if(test->DAC == AMPDACMEAN) {
//                meanTDO[channel] = h->GetMean();
//                entriesMeanTDO[channel] = h->GetEntries();
//            }
        }
        
        h->Write();
    } else {
        test->rmsTDO[channel] = nonCorrectValue;
        test->meanTDO[channel] = nonCorrectValue;
        
        if (isFirstMEANTDO) {
            
            for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
                if(test->DAC == AMPDACMEAN[pp]) {
                    meanTDO[channel] = nonCorrectValue;
                    entriesMeanTDO[channel] = 0;
                }
            }
            
//            if(test->DAC == AMPDACMEAN) {
//                meanTDO[channel] = nonCorrectValue;
//                entriesMeanTDO[channel] = 0;
//            }
        }

    }
    delete h;
}

// ?????????????? ???????????? ?? root
void build_DataTree(test_t *test, bool isSkew = false){
    char title[256];
    sprintf(title, "DataTree_%i_DAC_%i_TAC_%.1f_Gain_%i_Peaking_time_%i_Threshold", test->DAC, test->TAC, test->GAIN, test->PEAKINGTIME, test->THRESHOLD);

    char name[256];

    if (isSkew) sprintf(name, "DataTree_SKEW_%f", test->SKEW);
    else sprintf(name, "DataTree_DAC_%i", test->DAC);

    event_data_t e;
    TTree t(name, title);
    t.Branch("channel", &e.channel, "channel/b");
    t.Branch("amp", &e.amp, "amp/s");
        t.Branch("threshold", &e.threshold, "threshold/i");
        t.Branch("art", &e.art, "art/i");
        t.Branch("time", &e.time, "time/i");
        t.Branch("bcid", &e.bcid, "bcid/i");

    for(int i = 0; i < test->num_events; i++) {
        e = *&test->events[i];
        t.Fill();
    }

    t.Write();
}
    
    void printSlopeAndEntercept(float *slope, float *intercept, float *slopeError, float *interceptError, std::string nameConfig) {
        
//        int markerStyle = 20;
//
//        if (addNameToHistogram.find("DDO") != -1) {
//            nameConfig = "";
//            markerStyle = 22;
//
//        }
//
//        gCnv->Clear();
//            gCnv->Divide(2,1);
//
//            gCnv->cd(1);
//
//            float slopeMin, slopeMax;
//        slopeMin = nonCorrectValue;
//        slopeMax = nonCorrectValue;
//        for(int i = 0; i < 64; i++) {
//
//            if (slope[i] != nonCorrectValue && slope[i] < 1000 && slope[i] > -500) {
//                if (slopeMin == nonCorrectValue) slopeMin = slope[i];
//                if (slopeMax == nonCorrectValue) slopeMax = slope[i];
//
//                if ( slopeMax < slope[i])  slopeMax = slope[i];
//                if ( slopeMin > slope[i])  slopeMin = slope[i];
//            }
//        }
//
//        if (slopeMin == nonCorrectValue) slopeMin = 400;
//        if (slopeMax == nonCorrectValue) slopeMax = 100;
//
//        float correctValueMin, correctValueMax;
//
//        correctValueMin = slopeMin - std::abs(slopeMin)*0.3;
//        correctValueMax = slopeMax + std::abs(slopeMax)*0.3;
//
//        if (nameConfig.find("SKEW") != -1) {
//            markerStyle = 21;
//            correctValueMax = 254;
//        }
//
//
//
//            char title[256];
//            sprintf(title, "slope %s %s", addNameToHistogram.c_str(), nameConfig.c_str());
//
//            char name[256];
//            sprintf(name, "slope");
//
//        TH2F *hslope = new TH2F(name, title, 1024, 0, 64, 64, correctValueMin, correctValueMax);
//
//            hslope->SetLineColor(4);
//            hslope->SetFillColor(34);
//            hslope->SetXTitle("CH");
//            hslope->SetYTitle("slope");
//
//        //hslope->SetFillStyle(4050);
//
//        //hslope->SetMarkerStyle(3);
//
//            hslope->SetMarkerStyle(markerStyle);
//
//        // переделать
//            for(int i = 0; i < 64; i++) {
//
//                hslope->Fill(i, slope[i], slopeError[i]);
//
//               //hslope->SetBinContent(slope[i], i);
//               //hslope->SetBinError(tests[o].DAC, tests[o].rmsPDO[i]);
//            }
//
//           // hslope->SetOption("COLZ");
//
//            hslope->Draw();
//
//            if ( hslope->GetEntries()) {
//                hslope->Write();
//            }
//
//
//        //////
//
//        gCnv->cd(2);
//
//        float interMin, interMax;
//        interMin = nonCorrectValue;
//        interMax = nonCorrectValue;
//        for(int i = 0; i < 64; i++) {
//
//            if (intercept[i] != nonCorrectValue && intercept[i] < 30 && intercept[i] > -50) {
//                if (interMin == nonCorrectValue) interMin = intercept[i];
//                if (interMax == nonCorrectValue) interMax = intercept[i];
//
//                if ( interMax < intercept[i])  interMax = intercept[i];
//                if ( interMin > intercept[i])  interMin = intercept[i];
//            }
//        }
//
//        if (interMin == nonCorrectValue) interMin = 400;
//        if (interMax == nonCorrectValue) interMax = 100;
//
//        //char title[256];
//        sprintf(title, "intercept %s %s", addNameToHistogram.c_str(), nameConfig.c_str());
//
//        //char name[256];
//        sprintf(name, "intercept ALL_CH");
//
//        TH2F *hinter = new TH2F(name, title, 1024, 0, 64, 64, interMin - std::abs(interMin)*0.3, interMax + std::abs(interMax)*0.3);
//
//        hinter->SetLineColor(4);
//        hinter->SetFillColor(34);
//        hinter->SetXTitle("CH");
//        hinter->SetYTitle("intercept");
//
//        hinter->SetMarkerStyle(markerStyle);
//
//        // переделать
//        for(int i = 0; i < 64; i++) {
//
//            if (interceptError[i] == nonCorrectValue) interceptError[i] = 0;
//
//            hinter->Fill(i, intercept[i], interceptError[i]);
//        }
//
//        //hinter->SetOption("COLZ");
//
//        hinter->Draw();
//
//        if ( hinter->GetEntries()) {
//            hinter->Write();
//        }
//
//
//
//        gCnv->Print(pdfnameMain, "pdf");
//        gCnv->Clear();
//        gCnv->cd();
        
        
        
       // char title[256];
       // sprintf(title, "Fit parametr %i", 0);
//        TH1F *fh_0 = new TH1F(title, "y = k * x + b", 64, 0, 64);
//        fh_0->SetLineColor(4);
//        fh_0->SetFillColor(34);
//        fh_0->SetXTitle("Channel number");
//        fh_0->SetYTitle("    b");
//        fh_0->SetMarkerStyle(3);
//        for(int o = 0; o < 64; o++) {
//            if (p0[o] != 0) {
//                fh_0->SetBinContent(o + 1, p0[o]);
//                fh_0->SetBinError(o + 1, p0Error[o]);
//
//            }
//        }
        
    }

void build_FirstPage(test_t *test, int numEvent = 0)
{
    gCnv->Clear();
    if ((isDDOCONT || !isContinuous) && (isL0DDO || !isL0) && (isL0POSDDO || !isL0POS)) gCnv->Divide(2,2);
    else gCnv->Divide(2,3);
    gCnv->cd(1);
    build_PDOmean(test);
    gCnv->cd(2);
    build_ChannelsInEvent(test);
    gCnv->cd(3);
    build_NumberOfEvents(test, numEvent);
//    gCnv->cd(4);
//    build_PDOrms(test);
    if ((isDDOCONT || !isContinuous) && (isL0DDO || !isL0) && (isL0POSDDO || !isL0POS)) {
//    gCnv->cd(5);
//    build_TDOmean(test);
//    gCnv->cd(6);
//    build_TDOrms(test);
    }
//    gCnv->Print(pdfnameMain, "pdf");
    
    if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
    else gCnv->Print(pdfnameMainNEG, "pdf");
    
    gCnv->cd();

    for( int i = 0; i < 6; i++ )
        delete hf[i];
}

void build_FirstPage_skew(test_t *test)
{
    gCnv->Divide(1,2);

    gCnv->cd(1);
    build_NumberOfEvents(test);
    gCnv->cd(2);
    build_ChannelsInEvent(test);
    //gCnv->cd(3);
    //build_PDOmean(test);
    //gCnv->cd(4);
    //build_PDOrms(test);

//    gCnv->cd(3);
//    build_TDOmean(test);
//
//    gCnv->cd(4);
//    build_TDOrms(test);
    
    if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
    else gCnv->Print(pdfnameMainNEG, "pdf");

//    gCnv->Print(pdfnameMain, "pdf");
    gCnv->cd();

    for( int i = 0; i < 6; i++ ) {
        if (i !=2 && i !=3 ) delete hf[i]; // ?????? ??????
    }
}
    
   // TH2I *
    
TH2I *hProcess[3];

void ProcessTest(test_t *test, bool isSkew = false, int numEvent = 0)
{
    build_DataTree(test, isSkew);
    gCnv->Clear();
    gCnv->cd();
    
    if ((!isDDOCONT || isContinuous) && (!isL0DDO || isL0) && (!isL0POSDDO || isL0POS)) {
        gCnv->Divide(2,2);
        gCnv->cd(1);
    }
    
    for(int i = 0; i < 64; i++) {
            Build_ChannelPDO(test, i);
        }
    
    Build_ChannelAllChPDO(test, hProcess[0]);
    
    if ((!isDDOCONT || isContinuous) && (!isL0DDO || isL0) && (!isL0POSDDO || isL0POS)) {
        gCnv->cd(2);
        Build_ChannelAllChRelBCID(test, hProcess[1]);
    }
    
    //if (test->DAC == AMPDACMEAN) isFirstMEANPDO = false;

 if ((!isDDOCONT || isContinuous) && (!isL0DDO || isL0) && (!isL0POSDDO || isL0POS)) {
     
        gCnv->cd(3);

        for(int i = 0; i < 64; i++)
            Build_ChannelTDO(test, i);
     
            Build_ChannelAllChTDO(test, hProcess[2]);
     
     for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
          if(test->DAC == AMPDACMEAN[pp]) isFirstMEANTDO = false;
     }
     
    }
    
    
    for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
        if(test->DAC == AMPDACMEAN[pp]) {
            
            if (isFirstMEANPDO && !isSkew) {
                if (addNameToHistogram.find("CONT") == -1)
                {
//                    gCnv->Print(pdfnameMain, "pdf");
                    
                    if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
                    else gCnv->Print(pdfnameMainNEG, "pdf");
                    
                }
                
            }
            isFirstMEANPDO = false;
            
        }
    }
    
//    if (test->DAC == AMPDACMEAN) {
//        if (isFirstMEANPDO && !isSkew) gCnv->Print(pdfnameMain, "pdf");
//        isFirstMEANPDO = false;
//    }
    
    //if (isFirstMEANPDO) gCnv->Print(pdfname, "pdf");
    
    
    gCnv->Clear();
    
    for (int i = 0; i < 3; i++) {
        if (hProcess[i]) delete hProcess[i];
    }
    
    //build_FirstPage(test, numEvent);

    calc_data_Temp(test);
}
    
TH2I *hProcessSkew[2];
    
void ProcessTest_skew(test_t *test)
{
    build_DataTree(test);

    build_FirstPage_skew(test);

    for(int i = 0; i < 64; i++)
        Build_ChannelTDO(test, i, true);
    
        Build_ChannelAllChTDO(test, hProcessSkew[0]);
        Build_ChannelAllChRelBCID(test, hProcessSkew[1]);
    
        calc_data_Temp(test);
}

test_t tests[10]; // NUM_TESTS

void WriteFitParameters( char *file, float *p0, float *p1, float *errorP0, float *errorP1 ) {

    FILE *fp = fopen(file, "at");

    if (BOARD_ID == 0) BOARD_ID = 2;
//    fprintf(fp, "%s_BOARD_ID %i \n", configurationName.c_str(), BOARD_ID);
//    fprintf(fp, "%s_TestMode %s\n \n", configurationName.c_str(), test_mode);
//
//    fprintf(fp, "%s_USER_ID %s", configurationName.c_str(), userID.c_str());
//    fprintf(fp, "%s_VMM3_PART_ID %s \n", configurationName.c_str(), VMM3_PART_ID.c_str());
//
//    bool deadchns = 0;// 3 ?????? ?????????????? ?????????????? ????????????
//    fprintf(fp, "%s_DEAD_CHANNELS ", configurationName.c_str());
//
//    count_chn_dead = 0;
//    for(int i = 0; i < 64; i++)
//    {
//        if(!chn_notdead[i]) // + 1 ?????????????? ??????????
//
//        {
//            count_chn_dead++;
//            if(deadchns)
//                fprintf(fp, ", %i", i);
//            else
//                fprintf(fp, "%i", i);
//
//            deadchns = 1;
//        }
//    }
//
//        fprintf(fp, deadchns ? "\n" : "NO\n");
//
//    bool illChns = 0;// 3 ?????? ?????????????? ?????????????? ????????????
//    fprintf(fp, "%s_Ill_CHANNELS ", configurationName.c_str());
//
//    count_chn_dead = 0;
//    for(int i = 0; i < 64; i++)
//    {
//        if(chIll[i]) // + 1 ?????????????? ??????????
//
//        {
//            if(illChns)
//                fprintf(fp, ", %i", i);
//            else
//                fprintf(fp, "%i", i);
//
//            illChns = 1;
//        }
//    }
//
//    fprintf(fp, illChns ? "\n" : "NO\n");
//
//
//    bool nechns = 0; // 4 ?????? ?????????????? ???? ?????????????????????? ????????????
//
//    fprintf(fp, "%s_NON_EFFICIENT_CHANNELS ", configurationName.c_str());
//
//    count_chn_ne = 0;
//    for(int i = 0; i < 64; i++) {
//        if(chn_ne[i])
//        {
//            count_chn_ne++; // + 1 ???????? ??????????
//            if(nechns)
//                fprintf(fp, ", %i", i);
//            else
//                fprintf(fp, "%i", i);
//
//            nechns = 1;
//        }
//    }
//
//    fprintf(fp, nechns ? "\n\n" : "NO\n\n");
    //
    for(int i = 0; i < 64; i++)
    {
        if(!chn_notdead[i])// ??????????????
            continue;

        double max = 0;

        for(int o = 0; o < NUM_TESTS; o++)
        {
            if(tests[o].rmsPDO[i] > max )
                max = tests[o].rmsPDO[i];
        }

        fprintf(fp, "%s_RMS_PDO_CHN%i %f\n", configurationName.c_str(), i, max);
    }

    fprintf(fp, "\n" );

    for(int i = 0; i < 64; i++) {
        if(!chn_notdead[i])// ??????????????
        continue;
        if (p0[i] != float(nonCorrectValue)) fprintf(fp, "%s_intercept_CHN%i %f +- %f\n", configurationName.c_str(), i, p0[i], errorP0[i]);
    }

    fprintf(fp, "\n" );

    for(int i = 0; i < 64; i++) {
            if(!chn_notdead[i])// ??????????????
            continue;
        if (p1[i] != float(nonCorrectValue)) fprintf(fp, "%s_slope_CHN%i %f +- %f\n", configurationName.c_str(), i, p1[i], errorP1[i]);
    }
    
    cuts::analysisCutsADC (meanPDO, configurationName);

    for(int i = 0; i < 64; i++) {
            if(meanPDO[i] != float(nonCorrectValue)) fprintf(fp, "%s_ADC_mean_CHN%i %f \n", configurationName.c_str(), i, meanPDO[i]);
    }
    
    cuts::analysisEntries(entriesMeanPDO, configurationName);
    
    for(int i = 0; i < 64; i++) {
//        if(!entriesMeanPDO[i])// ??????????????
//            continue;
        fprintf(fp, "%s_ADC_meanEntries_CHN%i %i \n", configurationName.c_str(), i, entriesMeanPDO[i]);
    }
    
    if ((!isDDOCONT || isContinuous) && (!isL0DDO || isL0) && (!isL0POSDDO || isL0POS)) {
        
        cuts::analysisCutsTDO(meanTDO, configurationName);
        
        for(int i = 0; i < 64; i++) {
            if(meanTDO[i] != float(nonCorrectValue)) fprintf(fp, "%s_TDO_mean_CHN%i %f \n", configurationName.c_str(), i, meanTDO[i]);
        }
    
    
        for(int i = 0; i < 64; i++) {
    //        if(!entriesMeanTDO[i])// ??????????????
    //            continue;
            fprintf(fp, "%s_TDO_meanEntries_CHN%i %i \n", configurationName.c_str(), i, entriesMeanTDO[i]);
        }
    }


    fclose(fp);

    bool chn_notdeadOne;
    bool chn_neOne;

    Float_t InterceptOne[64];
    Float_t SlopeOne[64];


    Bool_t nonEfficCh[64];
    Bool_t deadCh[64];

    char nameConst[256];

            for(int i = 0; i < 64; i++) {
            InterceptOne[i] = p0[i];
            SlopeOne[i] = p1[i];
            deadCh[i] = !chn_notdead[i];
            nonEfficCh[i] = chn_ne[i];
    }


}
// ?????????????????? ?????????????????????? ???? PDO 

void calibrationADC(string chip_id) {
for (int i = 0; i < 64; i++) {
    chn_notdead[i] = 1;
    chIll[i] = 0;
    meanPDO[i] = 0;
    meanTDO[i] = 0;
}
    int config = 3;
    //for(config = 1; config < 4; config++){

//    gROOT->SetBatch(kTRUE);
//    gStyle->SetOptStat(kTRUE);
//    gStyle->SetOptFit(111);

    char file[256];
    char rootpath[256];
    char txtpath[256];

   // gCnv = new TCanvas("cnv_vmmda", "VMM Data Analysis", 200, 10, 700, 500);
    TFile *rootFile;

    //gROOT->SetBatch(kTRUE)//BVV

    //------------------------------------------------- SBIP -------------------------------------------------
    if(config == 3) {

        
        char preffPDO[256];
        
        if (configurationName.find("DDO") == -1) sprintf(preffPDO, "_PDO");
        else sprintf(preffPDO, "");
        
        sprintf(file, "%s_%s%s", chip_id.c_str(), configurationName.c_str(), preffPDO); //???????????????? ?????? ?????? ????????????
        //	sprintf(file, "%i_PDO_Calibration", chip_id); //???????????????? ?????? ?????? ????????????
        sprintf(rootpath, "%s%sroot%s%s.root", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), file);
        
        if (addNameToHistogram.find("pos") == -1) sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
        else sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());

        rootFile = new TFile(rootpath, "RECREATE");

        for(int i = 0; i < NUM_TESTS; i++)  {

        char path[256];
        char pdoAMP[256];

        sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str() ,chip_id.c_str(), macORWin.c_str(), internalFolderName.c_str(),macORWin.c_str(), (currentNameFilesPDO[i]).c_str());
        LoadTest(path, &tests[i]);
        ProcessTest(&tests[i], false, i);

        }
    }

    float p0[64], p1[64];
    float p0Error[64], p1Error[64], chi2Error[64];
    float chi2[64]; //------------------??????????????????
    int satDAC[64]; // SATURATION DAC

    rootFile->cd();

    for(int i = 0; i < 64; i++) { //???????????? 64 ?????????????????????????? ?????????????????????? ???? ???????????? ??????????
        
        char title[256];
        sprintf(title, "Channel %i ADC FIT", i);

         TH1F *h = new TH1F(title, title, 1024, 0, 1024);
        
        h->SetLineColor(4);
        h->SetFillColor(34);
        h->SetYTitle("Mean ADC");
        h->SetXTitle("Pulse DAC");
        h->SetMarkerStyle(3);

        int pointSaturation = NUM_TESTS - 1;

        for(int o = 0; o < NUM_TESTS; o++) {
            if (isL0 || isL0POS) if (!tests[o].num_events) tests[o].meanPDO[i] = nonCorrectValue;
            if (tests[o].numEntries[i]) {
                h->SetBinContent(tests[o].DAC, tests[o].meanPDO[i]);
                h->SetBinError(tests[o].DAC, tests[o].rmsPDO[i] < 100 ? tests[o].rmsPDO[i] : 100);
            }
        }

        TF1 *fit;
        h->Fit("pol1","","");

        fit = h->GetFunction("pol1");


        if (!fit) {
            p1[i] = nonCorrectValue;
            p0[i] = nonCorrectValue;
            chi2[i] = nonCorrectValue;

            p0Error[i] = nonCorrectValue;
            p1Error[i] = nonCorrectValue;
            
             continue;
            
        }
        
        //if(!fit){p0[i] = p1[i]; continue;}

        chi2[i] = fit->GetChisquare();

        p0[i] = fit->GetParameter(0);
        p1[i] = fit->GetParameter(1);
        p0Error[i] = fit->GetParError(0);
        p1Error[i] = fit->GetParError(1);  


        satDAC[i] = (std::pow(2, bitSize) - p0[i])/p1[i];
        
        h->Draw();
        if(h->GetEntries())
            h->Write();

        delete h; // ???????????? ????????????


    }
    
    //printSlopeAndEntercept(p0, p1, p0Error, p1Error, "PDO");

     WriteFitParameters(txtpath, p0, p1, p0Error, p1Error);
    gCnv->Clear();
    // --------------------------------------- PRINTING FIT ANALYSIS ---------------------------------------
    string addNameConfigFit("");
    if (addNameToHistogram.find("DDO") != -1) {
        addNameConfigFit = "";
    } else addNameConfigFit = "PDO";
    
    char nameTitle[256];
    sprintf(nameTitle, "%s%s", addNameToHistogram.c_str(), addNameConfigFit.c_str());
    
    gCnv->Divide(2,1);
    gCnv->cd(1);
    
    char title[256];
    sprintf(title, "Fit parametr intercept %s", nameTitle);
    TH1F *fh_0 = new TH1F(title, title, 64, 0, 64);
    fh_0->SetLineColor(4);
    fh_0->SetFillColor(34);
    fh_0->SetXTitle("Channel number");
    fh_0->SetYTitle("intercept");
    fh_0->SetMarkerStyle(3);
    
    float p0ErrorVal;
    
    if (addNameToHistogram.find("DDO") != -1) {
        p0ErrorVal = 10;
    } else p0ErrorVal = 100;
    
    for(int o = 0; o < 64; o++) {
            if (p0[o] != nonCorrectValue) {
                fh_0->SetBinContent(o + 1, p0[o]);
                fh_0->SetBinError(o + 1, p0Error[o] < p0ErrorVal ? p0Error[o] : p0ErrorVal);
                //fh_0->SetBinError(o + 1, p0Error[o]);
            }
    }
    //gCnv->cd(1);
//    printPDF[0] = fh_0;
    fh_0->Draw();
    fh_0->Write();
    
    gCnv->cd(2);

    //FIT PARAMETR 1
    
    sprintf(title, "Fit parametr slope %s", nameTitle);
    TH1F *fh_1 = new TH1F(title, title, 64, 0, 64);
    fh_1->SetLineColor(4);
    fh_1->SetFillColor(34);
    fh_1->SetXTitle("Channel number");
    fh_1->SetYTitle("slope");
    fh_1->SetMarkerStyle(3);
    
    float p1ErrorVal;
    
    if (addNameToHistogram.find("DDO") != -1) {
        p1ErrorVal = 0.3;
    } else p1ErrorVal = 10;
    
    for(int o = 0; o < 64; o++) {
        if (p1[o] != 0) {
            
            if (p1[o] != nonCorrectValue) {
                fh_1->SetBinContent(o + 1, p1[o]);
                fh_1->SetBinError(o + 1, p1Error[o] < p1ErrorVal ? p1Error[o] : p1ErrorVal);
                //fh_1->SetBinError(o + 1, p1Error[o]);
            }
        }
    }
    //gCnv->cd(2);
//      printPDF[1] = fh_1;
    fh_1->Draw();
    fh_1->Write();
    if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
    else gCnv->Print(pdfnameMainNEG, "pdf");
    gCnv->Clear();
    gCnv->cd();

    //CHI SQUARE
       sprintf(title, "CHI SQUARE");
       TH1F *fh_3 = new TH1F(title, title, 64, 0, 64);
       fh_3->SetLineColor(4);
       fh_3->SetFillColor(34);
       fh_3->SetXTitle("Channel number");
       fh_3->SetYTitle("chi^2");
       fh_3->SetMarkerStyle(3);
       for(int o = 0; o < 64; o++) {
      //printf("%f\n", chi2[o]);
      float chi_2;
      if (chi2[o] > 500) chi_2 = 500;
      else if (chi2[o] < -500) chi_2 = - 500;
      else chi_2 = chi2[o];

      if (chi_2 != 0 ) fh_3->SetBinContent(o + 1, chi_2);
     }
     //gCnv->cd(3);
//     printPDF[2] = fh_3;
     fh_3->Draw();
     fh_3->Write();


//    gCnv->Print(pdfname, "pdf");
    
    
    
    
//    gCnv->Print(pdfclose, "pdf");
//    gCnv->Clear();
    
    delete fh_3;

    for(int i = 0; i < NUM_TESTS; i++)
        delete [] tests[i].events;





    delete fh_0;
    delete fh_1;
    delete rootFile;
//    delete gCnv;
    //}//for 1-3 ending
}//read_test enfing


//#define NUM_TESTS_SKEW 5

test_t tests_skew[8];

void WriteFitParameters_skew( char *file, float *p0, float *p1, float *errorP0, float *errorP1  ) {
    FILE *fp = fopen(file, "at");

    if (!fp) {
        cout << "\n " << "Error!!";
        return ;
    }

    fprintf(fp, "\n" );

        for(int i = 0; i < 64; i++) {
        if(!chn_notdead[i])// ??????????????
            continue;

        float max = 0;

        for(int o = 0; o < NUM_TESTS_SKEW; o++) {
            if(tests[o].rmsTDO[i] > max ) {
                max = tests[o].rmsTDO[i];
            }
        }

        if(!chn_notdead[i])// ??????????????
            continue;

        if (max != nonCorrectValue) fprintf(fp, "%s_RMS_TDO_CHN%i %f\n", configurationName.c_str(), i, max);
    }

    fprintf(fp, "\n");

    for(int i = 0; i < 64; i++) {
                if(!chn_notdead[i])// ??????????????
            continue;
        if (p0[i] != float(nonCorrectValue)) fprintf(fp, "%s_TDO_intercept_CHN%i %f +- %f\n", configurationName.c_str(), i, p0[i], errorP0[i]);
    }

    fprintf(fp, "\n" );

    for(int i = 0; i < 64; i++) {
            if(!chn_notdead[i])// ??????????????
            continue;
       if (p0[i] != float(nonCorrectValue)) fprintf(fp, "%s_TDO_slope_CHN%i %f +- %f\n", configurationName.c_str(), i, p1[i], errorP1[i]);
    }



fprintf(fp, "\n \n");

    fclose(fp);

    bool chn_notdeadOne;
    bool chn_neOne;

//    Float_t InterceptOne[64];
//    Float_t SlopeOne[64];
//
//
//        for(int i = 0; i < 64; i++) {
//            InterceptOne[i] = p0[i];
//            SlopeOne[i] = p1[i];
//    }

}


void calibrationSKEW(string chip_id) {

    for (int i = 0; i < 64; i++) {
        meanTDO[i] = 0;
    }

    gROOT->SetBatch(kTRUE);

    char file[256];
    sprintf( file, "%s_%s_TDO", chip_id.c_str(), configurationName.c_str());
    
    char rootpath[256], txtpath[256];
    sprintf(rootpath, "%s%sroot%s%s.root", outputPath.c_str(), macORWin.c_str(), macORWin.c_str() ,file);
    
   // sprintf(txtpath, "%s%sconstants%sconst_%s%s.txt", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), addNameConst.c_str(), chip_id.c_str());
    
    if (addNameToHistogram.find("pos") == -1) sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    else sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    
    TFile rootFile(rootpath, "RECREATE");

    gROOT->SetBatch(kTRUE);//BVV

    for(int i = 0; i < NUM_TESTS_SKEW; i++) {
        char path[256];

sprintf(path, "%s%s%s%s%s%s%s",inputPath.c_str(), macORWin.c_str(), chip_id.c_str(), macORWin.c_str(), internalFolderName.c_str(), macORWin.c_str(), currentNameFilesTDO[i].c_str());

        LoadTest(path, &tests_skew[i]);
        ProcessTest(&tests_skew[i], true);

    }

    float p0[64], p1[64], chi2[64];

    float errorp0[64], errorp1[64];

    for(int i = 0; i < 64; i++) {
        
        
        p0[i] = nonCorrectValue;
        p1[i] = nonCorrectValue;
        chi2[i] = nonCorrectValue;
        
        errorp0[i] = nonCorrectValue;
        errorp1[i] = nonCorrectValue;

        char title[256]; char name[256];
        sprintf(title, "Channel %i TDO FIT.", i);
        sprintf(name, "TDO_FIT_CH%i", i);// ?????????????? ?? ????????????????

        const int n = 8;
        float SK[n];         //SKEW
        float TDM[n];		  //TDO_MEAN
        float TDMER[n];	  //TDO_RMS


        for(int j = 0; j < NUM_TESTS_SKEW; j++) {
            if (NUM_TESTS_SKEW == 8) SK[j] = tests_skew[j].SKEW;
            else SK[j] = tests_skew[j].SKEW;
            
            TDM[j] = tests_skew[j].meanTDO[i];
            TDMER[j] = tests_skew[j].rmsTDO[i];

        }
        
        TGraph *gr1 = new TGraph(NUM_TESTS_SKEW, SK, TDM);
        TGraph *gr2 = new TGraph(NUM_TESTS_SKEW, SK, TDM);
        TGraph *gr3 = new TGraph(NUM_TESTS_SKEW, SK, TDM);

        gr1->SetLineColor(4);
        gr1->SetFillColor(34);

        gr2->SetLineColor(4);
        gr2->SetFillColor(34);

        gr3->SetLineColor(4);
        gr3->SetFillColor(34);

        //search for interval with minimum chi2 on a TDO(SKEW) graph
        
        TF1 *fit_skew_interval1;
        TF1 *fit_skew_interval2;
        TF1 *fit_skew_interval3;
        
        float chi2_skew_interval1, chi2_skew_interval2, chi2_skew_interval3;
        
        if (NUM_TESTS_SKEW == 8) {

        gr1->Fit("pol1", "", "", 0, 3);
        fit_skew_interval1 = gr1->GetFunction("pol1");
        chi2_skew_interval1 = fit_skew_interval1->GetChisquare();


        gr2->Fit("pol1", "", "", 2 , 5);
        fit_skew_interval2 = gr2->GetFunction("pol1");
        chi2_skew_interval2 = fit_skew_interval2->GetChisquare();


        gr3->Fit("pol1", "", "", 4, 7);
        fit_skew_interval3 = gr3->GetFunction("pol1");
        chi2_skew_interval3 = fit_skew_interval3->GetChisquare();

        if (fit_skew_interval1->GetParameter("p1") <  0 || fit_skew_interval2->GetParameter("p1") < 0 || fit_skew_interval3->GetParameter("p1") < 0) {
            
            if(fit_skew_interval1->GetParameter("p1") > 0) chi2_skew_interval1 = chi2_skew_interval2 + chi2_skew_interval3;
            if(fit_skew_interval2->GetParameter("p1") > 0) chi2_skew_interval2 = chi2_skew_interval1 + chi2_skew_interval3;
            if(fit_skew_interval3->GetParameter("p1") > 0) chi2_skew_interval3 = chi2_skew_interval1 + chi2_skew_interval2;

        }

        if ((chi2_skew_interval1 <= chi2_skew_interval2) && (chi2_skew_interval1 <= chi2_skew_interval3)){
            //gr->Fit("pol1", "", "", 0, 12);
            gr1->Draw("AC*");
            gr1->SetTitle(title);
            gr1->SetName(name);
            gr1->SetMarkerColor(4);

            //gr->SetMarkerStyle(21);
            gr1->SetMarkerStyle(3);
            gr1->Draw("L");
            if (fit_skew_interval1){
                p0[i] = fit_skew_interval1->GetParameter("p0");
                p1[i] = fit_skew_interval1->GetParameter("p1");
                chi2[i] = fit_skew_interval1->GetChisquare();
                errorp0[i] = fit_skew_interval1->GetParError(0);
                errorp1[i] = fit_skew_interval1->GetParError(1);
            }
            else {
                
                p0[i] = nonCorrectValue;
                p1[i] = nonCorrectValue;
                
                chi2[i] = nonCorrectValue;
                errorp0[i] = nonCorrectValue;
                errorp1[i] = nonCorrectValue;
            }
            gCnv->Clear();

            gr1->Write();

        }
        else{
            if ((chi2_skew_interval2 <= chi2_skew_interval1) && (chi2_skew_interval2 <= chi2_skew_interval3)){
                //gr->Fit("pol1", "", "", 0, 12);
                gr2->Draw("AC*");
                gr2->SetTitle(title);
                gr2->SetName(name);
                gr2->SetMarkerColor(4);
                //gr->SetMarkerStyle(21);
                gr2->SetMarkerStyle(3);
                gr2->Draw("L");
                if (fit_skew_interval2) {
                    p0[i] = fit_skew_interval2->GetParameter("p0");
                    p1[i] = fit_skew_interval2->GetParameter("p1");
                    chi2[i] = fit_skew_interval2->GetChisquare();
                    errorp0[i] = fit_skew_interval2->GetParError(0);
                    errorp1[i] = fit_skew_interval2->GetParError(1);

                }
                else {
                    p0[i] = nonCorrectValue;
                    p1[i] = nonCorrectValue;
                    
                    chi2[i] = nonCorrectValue;
                    errorp0[i] = nonCorrectValue;
                    errorp1[i] = nonCorrectValue;
                }
                
                gCnv->Clear();
                gr2->Write();

            }
            else {
                if ((chi2_skew_interval3 <= chi2_skew_interval1) && (chi2_skew_interval3 <= chi2_skew_interval2)){
                    //gr->Fit("pol1", "", "", 0, 12);
                    gr3->Draw("AC*");
                    gr3->SetTitle(title);
                    gr3->SetName(name);
                    gr3->SetMarkerColor(4);
                    //gr->SetMarkerStyle(21);
                    gr3->SetMarkerStyle(3);

                    gr3->Draw("L");
                    if (fit_skew_interval3){
                        p0[i] = fit_skew_interval3->GetParameter("p0");
                        p1[i] = fit_skew_interval3->GetParameter("p1");
                        chi2[i] = fit_skew_interval3->GetChisquare();
                        errorp0[i] = fit_skew_interval3->GetParError(0);
                         errorp1[i] = fit_skew_interval3->GetParError(1);
                    }
                    else {
                        
                        p0[i] = nonCorrectValue;
                        p1[i] = nonCorrectValue;
                        
                        chi2[i] = nonCorrectValue;
                        errorp0[i] = nonCorrectValue;
                        errorp1[i] = nonCorrectValue;
                    }
                    gCnv->Clear();

                    gr3->Write();

                }
            }
        }

    }

    if (NUM_TESTS_SKEW == 3) {


        gr1->Fit("pol1", "", "", 0, tests_skew[1].SKEW);
        fit_skew_interval1 = gr1->GetFunction("pol1");
        chi2_skew_interval1 = fit_skew_interval1->GetChisquare();


        gr2->Fit("pol1", "", "", tests_skew[1].SKEW , tests_skew[2].SKEW);
        fit_skew_interval2 = gr2->GetFunction("pol1");
        chi2_skew_interval2 = fit_skew_interval2->GetChisquare();


        if (fit_skew_interval1 && fit_skew_interval2){

                if (fit_skew_interval1->GetParameter("p1") < 0 && fit_skew_interval2->GetParameter("p1") > 0) {

                    gr1->Draw("AC*");
                    gr1->SetTitle(title);
                    gr1->SetName(name);
                    gr1->SetMarkerColor(4);
                    gr1->SetMarkerStyle(3);
                    gr1->Draw("L");

                    p0[i] = fit_skew_interval1->GetParameter("p0");
                    p1[i] = fit_skew_interval1->GetParameter("p1");
                    chi2[i] = fit_skew_interval1->GetChisquare();
                    errorp0[i] = fit_skew_interval1->GetParError(0);
                    errorp1[i] = fit_skew_interval1->GetParError(1);

//                    gCnv->Clear();
//                    gr1->Write();
                } else if (fit_skew_interval1->GetParameter("p1") > 0 && fit_skew_interval2->GetParameter("p1") < 0) {

                    gr2->Draw("AC*");
                    gr2->SetTitle(title);
                    gr2->SetName(name);
                    gr2->SetMarkerColor(4);
                    gr2->SetMarkerStyle(3);
                    gr2->Draw("L");

                    p0[i] = fit_skew_interval2->GetParameter("p0");
                    p1[i] = fit_skew_interval2->GetParameter("p1");
                    chi2[i] = fit_skew_interval2->GetChisquare();
                    errorp0[i] = fit_skew_interval2->GetParError(0);
                    errorp1[i] = fit_skew_interval2->GetParError(1);

//                    gCnv->Clear();
//                    gr2->Write();
                } else {

                        gr3->Fit("pol1", "", "", 0, tests_skew[2].SKEW);
                        fit_skew_interval3 = gr3->GetFunction("pol1");
                        chi2_skew_interval3 = fit_skew_interval3->GetChisquare();

                        if (fit_skew_interval3) {
                            gr3->Draw("AC*");
                            gr3->SetTitle(title);
                            gr3->SetName(name);
                            gr3->SetMarkerColor(4);
                            gr3->SetMarkerStyle(3);
                            gr3->Draw("L");

                            p0[i] = fit_skew_interval3->GetParameter("p0");
                            p1[i] = fit_skew_interval3->GetParameter("p1");
                            chi2[i] = fit_skew_interval3->GetChisquare();
                            errorp0[i] = fit_skew_interval3->GetParError(0);
                            errorp1[i] = fit_skew_interval3->GetParError(1);
                            
                        } else {
                            
                            p0[i] = nonCorrectValue;
                            p1[i] = nonCorrectValue;
                            
                            chi2[i] = nonCorrectValue;
                            errorp0[i] = nonCorrectValue;
                            errorp1[i] = nonCorrectValue;
                        }
                }
            }
        else {
                           gr3->Fit("pol1", "", "", 0, tests_skew[2].SKEW);
                        fit_skew_interval3 = gr3->GetFunction("pol1");
                        chi2_skew_interval3 = fit_skew_interval3->GetChisquare();

                        if (fit_skew_interval3) {
                            gr3->Draw("AC*");
                            gr3->SetTitle(title);
                            gr3->SetName(name);
                            gr3->SetMarkerColor(4);
                            gr3->SetMarkerStyle(3);
                            gr3->Draw("L");

                            p0[i] = fit_skew_interval3->GetParameter("p0");
                            p1[i] = fit_skew_interval3->GetParameter("p1");
                            chi2[i] = fit_skew_interval3->GetChisquare();
                            errorp0[i] = fit_skew_interval3->GetParError(0);
                            errorp1[i] = fit_skew_interval3->GetParError(1); 
                            
                            gCnv->Clear();
                            gr3->Write();  

                            
                        } else {
                            p0[i] = nonCorrectValue;
                            p1[i] = nonCorrectValue;
                            
                            chi2[i] = nonCorrectValue;
                            errorp0[i] = nonCorrectValue;
                            errorp1[i] = nonCorrectValue;
                        }
        }


    }


    if (NUM_TESTS_SKEW != 8 && NUM_TESTS_SKEW != 3) {

        gr1->Fit("pol1", "", "");
       // gr1->Fit("pol1", "", "", tests_skew[0].SKEW, tests_skew[NUM_TESTS_SKEW - 1].SKEW);
        fit_skew_interval1 = gr1->GetFunction("pol1");
        chi2_skew_interval1 = fit_skew_interval1->GetChisquare();


        gr1->Draw("AC*");
        gr1->SetTitle(title);
        gr1->SetName(name);
        gr1->SetMarkerColor(4);

            //gr->SetMarkerStyle(21);
            gr1->SetMarkerStyle(3);
            gr1->Draw("L");
            if (fit_skew_interval1) {
                p0[i] = fit_skew_interval1->GetParameter("p0");
                p1[i] = fit_skew_interval1->GetParameter("p1");
                chi2[i] = fit_skew_interval1->GetChisquare();
                errorp0[i] = fit_skew_interval1->GetParError(0);
                errorp1[i] = fit_skew_interval1->GetParError(1);
            }
            else {
                p0[i] = nonCorrectValue;
                p1[i] = nonCorrectValue;
                
                chi2[i] = nonCorrectValue;
                
                errorp0[i] = nonCorrectValue;
                errorp1[i] = nonCorrectValue;
                
                
            }
            gCnv->Clear();

            gr1->Write();
    }

        delete gr1;
        delete gr2;
        delete gr3;
    }

    string fitName("");
    
    gCnv->Divide(2,1);

    TH1F *arrayfh[2];
    
    for(int i = 0; i <= 1; i++){
        char title[256];
        
            gCnv->cd(i+1);
        
        if (i) fitName = "slope";
        else fitName = "intercept";
        sprintf(title, "Fit parametr %s %sSKEW",  addNameToHistogram.c_str(), fitName.c_str());

        TH1F *fh = new TH1F(title, title, 64, 0, 64);
        fh->SetLineColor(4);
        fh->SetFillColor(34);
        fh->SetXTitle("Channel number");
        fh->SetYTitle(fitName.c_str());
        float pval;
        float perrorval;
        
        float maxPval;
        float maxPError;

        for(int o = 0; o < 64; o++)
        {
            //if ((i ? p1[o] : p0[o]) != nonCorrectValue) {
            if (p1[o] != nonCorrectValue && p0[o] != nonCorrectValue) {
                
                if (i) {
                    maxPval = 20;
                    maxPError = 5;
                } else {
                    maxPval = 300;
                    maxPError = 100;
                }
                
                pval = i ? p1[o] : p0[o];
                perrorval = i ? errorp1[o] : errorp0[o];
                fh->SetBinContent(o + 1, pval < maxPval ? pval : maxPval);
                fh->SetBinError(o + 1, perrorval < maxPError ? perrorval : maxPError);
            }
        }
        
        fh->Draw();
        fh->Write();
        
        arrayfh[i] = fh;
        //delete fh;
    }
    
    //gCnv->Print(pdfnameMain, "pdf");
    
    if (addNameToHistogram.find("pos") != -1 ) gCnv->Print(pdfnameMainPOS, "pdf");
    else gCnv->Print(pdfnameMainNEG, "pdf");
    
    gCnv->Clear();
    gCnv->cd();
    
    for(int i = 0; i <= 1; i++) {
        
        delete arrayfh[i];
        
    }

///////////////
        char title[256];
        sprintf(title, "Chisquare");

        TH1F *fh = new TH1F(title, title, 64, 0, 64);
        fh->SetLineColor(4);
        fh->SetFillColor(34);
        fh->SetXTitle("Channel number");
        fh->SetYTitle("chi^2");

        for(int o = 0; o < 64; o++)
        {
            if (chi2[o]) fh->SetBinContent(o + 1, chi2[o] < 100 ? chi2[o]: 100);
        }
        fh->Draw();

        //gCnv->Print(pdfname, "pdf");
        //gCnv->Clear();

        fh->Write();
        delete fh;

    //printSlopeAndEntercept(p0, p1, errorp0, errorp1, "SKEW");
    WriteFitParameters_skew(txtpath, p0, p1, errorp0, errorp1);
    
    rootFile.cd();

    for(int i = 0; i < NUM_TESTS_SKEW; i++)
        delete [] tests_skew[i].events;

//    gCnv->Print(pdfclose, "pdf");
//    delete gCnv;
}

void calibrationAll(string chip_id) {

    if (isARTCONT && !isContinuous) {
        sprintf(test_mode_path, "");

    calibrationART(chip_id);

    } else if (isL0ART && !isL0) {
        sprintf(test_mode_path, "L0_");
        calibrationART(chip_id);

    } else if (isL0POSART && !isL0POS) {
        sprintf(test_mode_path, "L0_pos_");
        calibrationART(chip_id);

    } else {
    if (isContinuous) {
        sprintf(test_mode_path, "CONT");
    } else if (isL0) {
        sprintf(test_mode_path, "DDO_neg");
    } else if (isL0POS) {
        sprintf(test_mode_path, "DDO_pos");
    } else if (isDDOCONT) {
        sprintf(test_mode_path, "DDO_neg");
    } else if (isL0DDO) {
        sprintf(test_mode_path, "DDO_neg");
    } else if (isL0POSDDO) {
        sprintf(test_mode_path, "DDO_pos");
    }

    for(int i = 0; i < 64; i++) {
        chn_ne[i] = 0; // ?????????????? @Ser
    }

    TempMax = nonCorrectValue;
    TempMin = nonCorrectValue;

    VDD_V_Max = nonCorrectValue;
    VDD_V_Min = nonCorrectValue;
    VDD_A_Max = nonCorrectValue;
    VDD_A_Min = nonCorrectValue;

    VDDD_V_Max = nonCorrectValue;
    VDDD_V_Min = nonCorrectValue;
    VDDD_A_Max = nonCorrectValue;
    VDDD_A_Min = nonCorrectValue;

    VDDP_V_Max = nonCorrectValue;
    VDDP_V_Min = nonCorrectValue;
    VDDP_A_Max = nonCorrectValue;
    VDDP_A_Min = nonCorrectValue;

    VDAD_V_Max = nonCorrectValue;
    VDAD_V_Min = nonCorrectValue;
    VDAD_A_Max = nonCorrectValue;
    VDAD_A_Min = nonCorrectValue;
        
    isFirstMEANTDO = true;
    isFirstMEANPDO = true;

    if (NUM_TESTS > 0) calibrationADC(chip_id);
    cout << "CHECK 1 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	
	
	    if (isContinuous) {
   //    sprintf(test_mode, "20_03_2018Continuous");
        sprintf(test_mode_path, "CONT");
    } else if (isL0) {
  //      sprintf(test_mode, "20_03_2018L0");
        sprintf(test_mode_path, "L0");
    } else if (isL0POS) {
  //      sprintf(test_mode, "20_03_2018L0");
        sprintf(test_mode_path, "L0pos");
    } else if (isDDOCONT) {
//        sprintf(test_mode, "20_03_2018DDO");
         sprintf(test_mode_path, "CONT");
    }

    if ((!isDDOCONT || isContinuous) && (!isL0DDO || isL0) && (!isL0POSDDO || isL0POS)) {

    if (isContinuous) {
        sprintf(test_mode_path, "CONT");
    } else if (isL0) {
        sprintf(test_mode_path, "L0");
    } else if (isL0POS) {
        sprintf(test_mode_path, "L0pos");
    } else if (isDDOCONT) {
        sprintf(test_mode_path, "CONT");
    } else if (isL0DDO) {
        sprintf(test_mode_path, "L0");
    } else if (isL0POSDDO) {
        sprintf(test_mode_path, "L0pos");
    }

       if (NUM_TESTS_SKEW > 0) calibrationSKEW(chip_id);
    }

    cout << "CHECK 2 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    char txtpath[256];
        
    if (addNameToHistogram.find("pos") == -1) sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());
    else sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,chip_id.c_str());

    //sprintf(txtpath, "%s%sconstants%sconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str() , addNameConst.c_str() ,chip_id.c_str());
        
    if (TempMax != nonCorrectValue) {
        
    FILE *fp = fopen(txtpath, "at");
                   if (fp) {
                       
        cuts::AnCurL0PN(configurationName);
                       
       fprintf(fp, "\n%s_Temp_Max %f", configurationName.c_str(), TempMax);
          //fprintf(fp,"\nTemp_Min %f" , TempMin);
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
                       
       

       fclose(fp);
       }
   }

}
}

void printEndConstFile(string chip_id, char *txtpath,bool isPOS) {
    
    
    FILE *fp = fopen(txtpath, "at");
    if (fp) {
        
        int chipStatus;
        
        fprintf(fp,"\n");
        
        
    fprintf(fp, "CHIP_ID %s\n \n", chip_id.c_str());
        

        
        fprintf(fp, "BOARD_ID %i\n", BOARD_ID);
        
        std::string testModeStr = test_mode;
        
        if (testModeStr.find("output") != -1) {
            testModeStr = "CONFIGS_07_10_2018\n";
        }
        
        fprintf(fp, "TestMode %s\n", testModeStr.c_str());
        
        fprintf(fp, "DataTesting %s\n", dataTesting.c_str());
        
        if (userID.length() < 3) userID = "ROSLIAKOV\n";
        if (userID.find("ROALIAKOV") != -1) {
            userID = "ROSLIAKOV\n";
        }
        
        fprintf(fp, "USER_ID %s\n", userID.c_str());
        fprintf(fp, "VMM3_PART_ID %s\n", VMM3_PART_ID.c_str());
        fprintf(fp, "FPGA_VER %s\n", FPGA_VER.c_str());
        
        chipStatus = cuts::chipsStatus();
        fprintf(fp, "status %i\n", chipStatus);
        
        fprintf(fp, "statusNEG %i\n", cuts::chipStatusNEG);
        fprintf(fp, "statusPOS %i\n", cuts::chipStatusPOS);
        
            bool deadchPOS = 0;//
            fprintf(fp, "pos_DEAD_CHANNELS ");
        
            int count_chn_dead = 0;
            for(int i = 0; i < 64; i++)
            {
                if(cuts::badCHPOS[i]) // + 1 ?????????????? ??????????
                {
                    count_chn_dead++;
                    if(deadchPOS)
                        fprintf(fp, ", %i", i);
                    else
                        fprintf(fp, "%i", i);
                    deadchPOS = 1;
                }
            }
        
        fprintf(fp, deadchPOS ? "\n" : "NO\n");
        
        bool deadchNEG = 0;//
        fprintf(fp, "neg_DEAD_CHANNELS ");
        
        count_chn_dead = 0;
        for(int i = 0; i < 64; i++)
        {
            if(cuts::badCHNEG[i]) // + 1 ?????????????? ??????????
            {
                count_chn_dead++;
                if(deadchNEG)
                    fprintf(fp, ", %i", i);
                else
                    fprintf(fp, "%i", i);
                deadchNEG = 1;
            }
        }
        
        fprintf(fp, deadchNEG ? "\n" : "NO\n");
        
                fprintf(fp, "FAILED %s\n", cuts::FAILED.c_str());
        
        
        
        fclose(fp);
        
        char newname[256];
        
        if (!isPOS) sprintf(newname, "%s%sconstants%s%i_const_%s%sNEG.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), chipStatus, addNameConst.c_str() ,chip_id.c_str());
        else sprintf(newname, "%s%sconstants%s%i_const_%s%sPOS.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),chipStatus, addNameConst.c_str() ,chip_id.c_str());

        rename(txtpath, newname);
    }
    
}
}
