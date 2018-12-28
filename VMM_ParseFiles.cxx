#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <dirent.h>

namespace VMMCalibration {

void correctFileName(string folderName) {
    
    int sizePDODDOfileneg = 0;
    int sizeTDOfileneg = 0;
    
    int sizePDODDOfilepos = 0;
    int sizeTDOfilepos = 0;
    
    for (int i = 0; i < nameFilesL0PDO.size(); i++) {
        
        if (nameFilesL0PDO[i].find("L0_DDO_neg_85") != -1) {
            
            char path[256];
            sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str() ,folderName.c_str(), macORWin.c_str(), "L0",macORWin.c_str(), (nameFilesL0PDO[i]).c_str());
            fstream file(path);
            file.seekg (0, std::ios::end);
            sizePDODDOfileneg = file.tellg();
            file.close();
            
            for (int j = 0; j < nameFilesL0TDO.size(); j++) {
                if (nameFilesL0TDO[j].find("L0_085_sk_01") != -1) {
                            
                char path[256];
                sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str() ,folderName.c_str(), macORWin.c_str(), "L0",macORWin.c_str(), (nameFilesL0TDO[j]).c_str());
                fstream file(path);

                file.seekg (0, std::ios::end);
                sizeTDOfileneg = file.tellg();
                file.close();
                    
                if (sizePDODDOfileneg < sizeTDOfileneg) nameFilesL0PDO[i] = nameFilesL0TDO[j];
                    
            }
            }
            
        }
    }
    
        for (int i = 0; i < nameFilesL0posPDO.size(); i++) {
        
        if (nameFilesL0posPDO[i].find("L0_DDO_pos_330") != -1) {
            char path[256];
            sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str() ,folderName.c_str(), macORWin.c_str(), "L0",macORWin.c_str(), (nameFilesL0posPDO[i]).c_str());
            fstream file(path);
            file.seekg (0, std::ios::end);
            sizePDODDOfilepos = file.tellg();
            file.close();
            
            for (int j = 0; j < nameFilesL0posTDO.size(); j++) {

                if (nameFilesL0posTDO[j].find("L0pos_330_sk_01") != -1) {
                    
                    char path[256];
                    sprintf(path, "%s%s%s%s%s%s%s", inputPath.c_str(), macORWin.c_str() ,folderName.c_str(), macORWin.c_str(), "L0",macORWin.c_str(), (nameFilesL0posTDO[j]).c_str());
                    fstream file(path);
                    
                    file.seekg (0, std::ios::end);
                    sizeTDOfilepos = file.tellg();
                    file.close();

                    if (sizePDODDOfilepos < sizeTDOfilepos) nameFilesL0posPDO[i] = nameFilesL0posTDO[j];
                    
                    
                }
            }
            
        }
        
        }
    
}

void analysisFilesName(string fileName) {
    
    if (fileName.find("pos") != -1) {
        posEnable = true;
    } else negEnable = true;
    
    if (fileName.find("L0") != -1 && fileName.find("sk") == -1 && fileName.find("ART") == -1 && fileName.find("pos") == -1) {
        nameFilesL0PDO.push_back(fileName);
    } else if (fileName.find("L0") != -1 && fileName.find("sk") != -1 && fileName.find("ART") == -1 && fileName.find("pos") == -1) {
            nameFilesL0TDO.push_back(fileName);
    } else if (fileName.find("L0") != -1 && fileName.find("sk") == -1 && fileName.find("ART") != -1 && fileName.find("pos") == -1) {
        nameFilesL0ART.push_back(fileName);
    } else
    if (fileName.find("L0") != -1 && fileName.find("pos") != -1 && fileName.find("sk") == -1 && fileName.find("ART") == -1) {
        nameFilesL0posPDO.push_back(fileName);
    } else if (fileName.find("L0") != -1 && fileName.find("pos") != -1 && fileName.find("sk") != -1 && fileName.find("ART") == -1) {
        nameFilesL0posTDO.push_back(fileName);
    } else if (fileName.find("L0") != -1 && fileName.find("pos") != -1 && fileName.find("sk") == -1 && fileName.find("ART") != -1) {
        nameFilesL0posART.push_back(fileName);
    } else
     if (fileName.find("CONT") != -1 && fileName.find("sk") == -1) {
        nameFilesContPDO.push_back(fileName);
    } else if (fileName.find("CONT") != -1 && fileName.find("sk") != -1) {
        nameFilesContTDO.push_back(fileName);
    } else if (fileName.find("ART") != -1) {
        nameFilesContART.push_back(fileName);
    } else if (fileName.find("BASELINE") != -1 && fileName.find("pos") == -1) {
        BLineNeg.push_back(fileName);
    } else if (fileName.find("BASELINE") != -1 && fileName.find("pos") != -1) {
        BLinePos.push_back(fileName);
    }
    
    
    
}

void parseFiles(string folderName) {
    
    std::vector<std::string> insideFolders;
    
    nameFilesL0PDO.clear();
    nameFilesL0TDO.clear();
    nameFilesL0ART.clear();
    
    nameFilesL0posPDO.clear();
    nameFilesL0posTDO.clear();
    nameFilesL0posART.clear();
    
    nameFilesContPDO.clear();
    nameFilesContTDO.clear();
    nameFilesContART.clear();
    
    BLinePos.clear();
    BLineNeg.clear();
    
    /////
    
    DIR *dp;
    struct dirent *ep;
    
    dp = opendir ((inputPath + "/" + folderName).c_str());
    if (dp != NULL) {
        ep = readdir (dp);
        while (ep) {
            std::string fileName = ep->d_name;
            if (fileName.find(".") == -1) {
                insideFolders.push_back(fileName);
            }
            ep = readdir (dp);
        }
        (void) closedir (dp);
    }
    
    
    ///////
    
    
    //DIR *dp;
    //struct dirent *ep;
    
    for (int i = 0; i < insideFolders.size(); i++) {
        
        dp = opendir ((inputPath + "/" + folderName + "/" + insideFolders[i]).c_str());
        if (dp != NULL) {
            ep = readdir (dp);
            while (ep) {
                string fileName = ep->d_name;
                if (fileName.find(".txt") != -1) {
                    analysisFilesName(fileName);
                }
                ep = readdir (dp);
                }
            (void) closedir (dp);
        }
    }
    
   correctFileName(folderName);
    
//    for (int i = 0; i < nameFilesL0posPDO.size(); i++) {
//         cout << "\n" << nameFilesL0posPDO[i] << " lllllllllllqqqq " << nameFilesL0posPDO.size();
//    }
}
}
