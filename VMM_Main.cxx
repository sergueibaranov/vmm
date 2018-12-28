#ifndef __CINT__
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

#include <TNamed.h>
#include <TArrayI.h>
#include <TColor.h>
#include <TStyle.h>
#include <TF1.h>
#include <TGraph.h>
#include <TTree.h>

#include "VMM_Variable.cxx"

#include "cuts/VMM_cutsVariable.cxx"
#include "cuts/VMM_ReadCuts.cxx"
#include "cuts/VMM_AnalysisCuts.cxx"
#include "cuts/VMM_PrintsCutChips.cxx"

#include "VMM_BaseLine.cxx"
#include "VMM_ParseFiles.cxx"
#include "VMM_readCalibrationConfig.cxx"

#include "VMM_All.cxx"

#include "convertor/VMM_ParseFilesConvertor.cxx"

#include <sys/types.h>
#include <dirent.h>

using namespace VMMCalibration;

void VMMCalibration::calibrationART(string chip_id);
void VMMCalibration::LoadTest(char *file, test_t *test);
void VMMCalibration::readVMM3CalibrationConfig();

using namespace std;

TROOT root("",""); // static TROOT object

std::vector<std::string> insideNameFolderFile;

void findInsideFolder(std::string pathFolder) {
    
    insideNameFolderFile.clear();
    
    DIR *dp;
    struct dirent *ep;
    
    dp = opendir (pathFolder.c_str());
    if (dp != NULL) {
        ep = readdir (dp);
        while (ep) {
            std::string fileName = ep->d_name;
            if (fileName.find(".") == -1) {
                insideNameFolderFile.push_back(fileName);
            }
            ep = readdir (dp);
        }
        (void) closedir (dp);
    }
}

void beginColibration() {
    
    sprintf(infoChannelsPath, "%s%s%sconstants%sInfo_Channels.txt", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), macORWin.c_str());
    
    string fileName;
    char str[2048];
//    char pathMain[512];
    
    readVMM3CalibrationConfig();
    //cuts::readCuts();
    
//    sprintf(pathMain, "%s%sAll_logfile.txt", inputPath.c_str(), macORWin.c_str());
    //FILE *f = fopen(pathMain, "r");
    
//    if(!f) {
//        gSystem->cd(inputPath.c_str());
//        gSystem->Exec("ls >> All_logfile.txt");
//        f = fopen(pathMain, "r");
//    }
    
    string query = "";
    //        query = string ("rm -r ") + outputPath + "/";
    //        gSystem->Exec(query.c_str());
    
    query = string ("rm -r ") + outputPath + "/root";
    gSystem->Exec(query.c_str());
    
    query = string ("rm -r ") + outputPath + "/constants";
    gSystem->Exec(query.c_str());
    
    query = string ("rm -r ") + outputPath + "/pdf";
    gSystem->Exec(query.c_str());
    
    query = string ("rm -r ") + outputPath + "/localDB";
    gSystem->Exec(query.c_str());
    
    //        query = string ("mkdir ") + outputPath + "/";
    //        gSystem->Exec(query.c_str());
    
    query = string ("mkdir ") + outputPath + "/root";
    gSystem->Exec(query.c_str());
    
    query = string ("mkdir ") + outputPath + "/constants";
    gSystem->Exec(query.c_str());
    
    query = string ("mkdir ") + outputPath + "/pdf";
    gSystem->Exec(query.c_str());
    
    query = string ("mkdir ") + outputPath + "/localDB";
    gSystem->Exec(query.c_str());
    
    
    findInsideFolder(inputPath);
    
    //fgets(str, 2048, f);
    
    
    for (int countFolder = 0; countFolder < insideNameFolderFile.size(); countFolder++) {
//        fileName = string(str);
//        int foundN = fileName.find("\n");
        std::string new_mod_s;
//        if (foundN != -1) new_mod_s = fileName.substr(0, foundN);
//        else new_mod_s = fileName;
        
        new_mod_s = insideNameFolderFile[countFolder];
        
        cout << "\n" << new_mod_s.c_str() << "\n";
        
        if (new_mod_s.length() && new_mod_s.find(".") == -1 && new_mod_s.find("output") == -1) {
            
            posEnable = false;
            negEnable = false;
            
            parseFiles(new_mod_s);
            
            char txtpath[512];
            sprintf(txtpath, "%s%%sconstants%sconst_%s.txt",outputPath.c_str(), macORWin.c_str(), new_mod_s.c_str());
            
            FILE *fConst = fopen(txtpath, "r");
            if (fConst) {
                fclose(fConst);
                std::remove(txtpath);
            }
            
            char txtpathPos[512];
            char txtpathNeg[512];
            
            sprintf(txtpathPos, "%s%%sconstants%sconst_POS%s.txt",outputPath.c_str(), macORWin.c_str(), new_mod_s.c_str());
            FILE *fConstPos = fopen(txtpathPos, "r");
            if (fConstPos) {
                fclose(fConstPos);
                std::remove(txtpathPos);
            }
            


            sprintf(txtpathNeg, "%s%%sconstants%sconst_NEG%s.txt",outputPath.c_str(), macORWin.c_str(), new_mod_s.c_str());
            FILE *fConstNEG = fopen(txtpathNeg, "r");
            if (fConstNEG) {
                fclose(fConstNEG);
                std::remove(txtpathNeg);
            }
            
            
            gCnv = new TCanvas("cnv_vmmda", "VMM Data Analysis", 200, 10, 700, 500);
            
//            sprintf(pdfnameMain, "%s%spdf%s%s.pdf", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), new_mod_s.c_str());
//            sprintf(pdfopenMain, "%s[", pdfnameMain);
//            sprintf(pdfcloseMain, "%s]", pdfnameMain);
//
//            gCnv->Print(pdfopenMain, "pdf");
            
            if (posEnable) {
                sprintf(pdfnameMainPOS, "%s%spdf%s%sPOS.pdf", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), new_mod_s.c_str());
                sprintf(pdfopenMainPOS, "%s[", pdfnameMainPOS);
                sprintf(pdfcloseMainPOS, "%s]", pdfnameMainPOS);
                
                gCnv->Print(pdfopenMainPOS, "pdf");
            }
            
            if (negEnable) {
                sprintf(pdfnameMainNEG, "%s%spdf%s%sNEG.pdf", outputPath.c_str(), macORWin.c_str(), macORWin.c_str(), new_mod_s.c_str());
                sprintf(pdfopenMainNEG, "%s[", pdfnameMainNEG);
                sprintf(pdfcloseMainNEG, "%s]", pdfnameMainNEG);

                gCnv->Print(pdfopenMainNEG, "pdf");
            }
            
            
            
            
            isL0 = false;
            isL0POS = false;
            isDDOCONT = false;
            isContinuous = false;
            isARTCONT = false;
            
            isL0POSDDO = false;
            isL0POSART = false;
            isL0DDO = false;
            isL0ART = false;
            
            
            cuts::clearALLBadCh();
        
            gStyle->SetOptStat("eou");
            
            
            
            for (int k = 0; k < BLineNeg.size(); k++) {
                calibBaseLineMode (new_mod_s, BLineNeg[k], "neg");
            }
            
            if (BLineNeg.size() == 0 && calibBaseLine(new_mod_s) == false) {
                cuts::BlileFail();
            }
            
            for (int k = 0; k < BLinePos.size(); k++) {
                calibBaseLineMode (new_mod_s, BLinePos[k], "pos");
            }
            
            for (int j = 0; j < 3; j++) {
                
                internalFolderName = internalFolderNameMass[j];
                
                if (j == 0) isContinuous = true;
                if (j == 1) isL0 = true;
                if (j == 2) isL0POS = true;
                
                currentNameFilesPDO.clear();
                currentNameFilesTDO.clear();
                currentNameFilesART.clear();
                
                NUM_TESTS = 0;
                NUM_TESTS_SKEW = 0;
                
                while (!(isContinuous == false && isDDOCONT == false && isL0 == false && isARTCONT == false && isL0POS == false
                         && isL0POSDDO == false && isL0POSART == false && isL0DDO == false && isL0ART == false)) {
                    
                    if (isContinuous) {
                        bitSize = 10;
                        configurationName = "CONT";
                        addNameToHistogram = "CONTneg";
                        
                        AMPDACMEAN.clear();
                        
                        for (int ii = 0; ii < APMDACContMEAN.size(); ii++) {
                            AMPDACMEAN.push_back(APMDACContMEAN[ii]);
                        }
                        
                        NUM_TESTS = nameFilesContPDO.size();
                        for (int j = 0; j < NUM_TESTS; j++) {
                            currentNameFilesPDO.push_back(nameFilesContPDO[j]);
                        }
                        
                        NUM_TESTS_SKEW = nameFilesContTDO.size();
                        for (int j = 0; j < NUM_TESTS_SKEW; j++) {
                            currentNameFilesTDO.push_back(nameFilesContTDO[j]);
                        }
                        
                        for (int j = 0; j < nameFilesContART.size(); j++) {
                            currentNameFilesART.push_back(nameFilesContART[j]);
                        }
                        
                    }
                    else if (isARTCONT) {
                        bitSize = 10;
                        configurationName = "ARTneg";
                        addNameToHistogram = "ARTneg";
                    }
                    else if (isDDOCONT) {
                        configurationName = "DDOneg";
                        addNameToHistogram = "DDOneg";
                        bitSize = 6;
                        //isL0 = false;
                    }   else if (isL0) {
                        
                        AMPDACMEAN.clear();
                        
                        for (int ii = 0; ii < APMDACL0MEAN.size(); ii++) {
                            AMPDACMEAN.push_back(APMDACL0MEAN[ii]);
                        }
                        
                        //AMPDACMEAN = APMDACL0MEAN;
                        
                        bitSize = 10;
                        configurationName = "L0";
                        addNameToHistogram = "L0neg";
                        NUM_TESTS = nameFilesL0PDO.size();
                        for (int j = 0; j < NUM_TESTS; j++) {
                            currentNameFilesPDO.push_back(nameFilesL0PDO[j]);
                        }
                        
                        NUM_TESTS_SKEW = nameFilesL0TDO.size();
                        for (int j = 0; j < NUM_TESTS_SKEW; j++) {
                            currentNameFilesTDO.push_back(nameFilesL0TDO[j]);
                        }
                        
                        for (int j = 0; j < nameFilesL0ART.size(); j++) {
                            currentNameFilesART.push_back(nameFilesL0ART[j]);
                        }
                        
                        if (NUM_TESTS == 0) cuts::isGoodNEG = false;
                        
                    } else if (isL0ART) {
                        bitSize = 10;
                        configurationName = "ARTneg";
                        addNameToHistogram = "ARTneg";
                    } else if (isL0DDO) {
                        configurationName = "DDOneg";
                        addNameToHistogram = "DDOneg";
                        bitSize = 6;
                        
                    } else if(isL0POS) {
                        bitSize = 10;
                        configurationName = "L0pos";
                        addNameToHistogram = "L0pos";
                        
                         AMPDACMEAN.clear();
                        
                        for (int ii = 0; ii < APMDACL0POSMEAN.size(); ii++) {
                            AMPDACMEAN.push_back(APMDACL0POSMEAN[ii]);
                        }
                        
                        //AMPDACMEAN = APMDACL0POSMEAN;
                        
                        NUM_TESTS = nameFilesL0posPDO.size();
                        for (int j = 0; j < NUM_TESTS; j++) {
                            currentNameFilesPDO.push_back(nameFilesL0posPDO[j]);
                        }
                        
                        NUM_TESTS_SKEW = nameFilesL0posTDO.size();
                        for (int j = 0; j < NUM_TESTS_SKEW; j++) {
                            currentNameFilesTDO.push_back(nameFilesL0posTDO[j]);
                        }
                        
                        for (int j = 0; j < nameFilesL0posART.size(); j++) {
                            currentNameFilesART.push_back(nameFilesL0posART[j]);
                        }
                        
                        if (NUM_TESTS == 0) cuts::isGoodPOS = false;
                    } else if (isL0POSART) {
                        bitSize = 10;
                        configurationName = "ARTpos";
                        addNameToHistogram = "ARTpos";
                    } else if (isL0POSDDO) {
                        configurationName = "DDOpos";
                        addNameToHistogram = "DDOpos";
                        bitSize = 6;
                        
                    }
                    
                    for (int k = 0; k < 64; k++) {
                        meanTDO[k] = nonCorrectValue;
                        entriesMeanTDO[k] = 0;
                        meanPDO[k] = nonCorrectValue;
                        entriesMeanPDO[k] = 0;
                    }
                    
                    cout << "\n START CALIBRATION : " << configurationName << " " << new_mod_s;
                    calibrationAll(new_mod_s);
                    cout << "\n END CALIBRATION : " << configurationName << " " << new_mod_s <<"\n";
                    
                    if (isDDOCONT && !isARTCONT && !isContinuous) isDDOCONT = false;
                    if (isARTCONT  && !isContinuous) isARTCONT = false;
                    if (isContinuous) isContinuous = false;
                    
                    if (isL0DDO && !isL0ART && !isL0) isL0DDO = false;
                    if (isL0ART  && !isL0) isL0ART = false;
                    if (isL0) isL0 = false;
                    
                    if (isL0POSDDO && !isL0POSART && !isL0POS) isL0POSDDO = false;
                    if (isL0POSART  && !isL0POS) isL0POSART = false;
                    if (isL0POS) isL0POS = false;
                    
                }
            }
            if (new_mod_s.length() > 0) {
                
                char txtpath[256];
                
                if (negEnable) {
                    sprintf(txtpath, "%s%sconstants%sNEGconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,new_mod_s.c_str());
                    printEndConstFile(new_mod_s, txtpath, false);
                }
                if (posEnable) {
                    sprintf(txtpath, "%s%sconstants%sPOSconst_%s%s.txt",outputPath.c_str(), macORWin.c_str(), macORWin.c_str(),addNameConst.c_str() ,new_mod_s.c_str());
                    printEndConstFile(new_mod_s, txtpath, true);
                }
                //printEndConstFile(new_mod_s, txtpath);
                cuts::printCutChips(new_mod_s);
                
                
            }
            
//            gCnv->Print(pdfcloseMain, "pdf");
//            gCnv->Clear();
            
            if (posEnable) {
                gCnv->Print(pdfcloseMainPOS, "pdf");
            }
            
            if (negEnable) {
                gCnv->Print(pdfcloseMainNEG, "pdf");
            }
            
            delete gCnv;
        }
        
//        fgets(str, 2048, f);
//        if (feof(f)) break;
    }
    //fclose(f);
    
    // build LocalDB set input and set output
    VMMConvertor::buildLocalDB(outputPath + "/constants", outputPath + "/localDB");
    
}

std::vector<std::string> pathInputFile;
std::vector<std::string> pathOutputFile;

int main(int argc, char** argv)
#else
TFile* hsimple(Int_t get=0)
#endif
{
//
    string query = "";

    /////
//    for (int i = 0; i < pathInputFile.size(); i++) {
//
//        inputPath = pathInputFile[i];
//        outputPath = pathOutputFile[i];
////
        query = string ("mkdir ") + outputPath;
        gSystem->Exec(query.c_str());
//
        beginColibration();
//    }

    pathInputFile.clear();
    pathOutputFile.clear();

    return 1;
#ifdef __CINT__
    return hfile;
#else
    return 0;
#endif
}

