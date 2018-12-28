#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include <sys/types.h>
#include <dirent.h>

#include "VMM_DataTreeVariable.cxx"
#include "VMM_BuildRootConst.cxx"


namespace VMMConvertor {
    
    std::string inputPathConvert = "/output";
    std::string outputPathConvert = "/output/localDB";

    std::vector<std::string> insideFolders;
    
    std::vector<std::vector<std::string>> insideNameTxtFileVec;
    
void findInsideTXTandFolder(std::string pathFolder) {
    
    
    int sizeVec = insideNameTxtFileVec.size();
    
    for (int i = 0; i < sizeVec; i++) {
        for (int j = 0; j < insideNameTxtFileVec[i].size(); j++) {
            insideNameTxtFileVec[j].clear();
        }
    }
    
    insideNameTxtFileVec.clear();
    
    DIR *dp;
    struct dirent *ep;
    
        dp = opendir (pathFolder.c_str());
        if (dp != NULL) {
            ep = readdir (dp);
            while (ep) {
                std::string fileName = ep->d_name;
                if (fileName.find(".txt") != -1 && fileName.find(".zip") == -1 && fileName.find("const_") != -1) {
                    

                    bool doubletFile = false;
                    int size = insideNameTxtFileVec.size();
                    for (int i = 0; i < size; i++) {
                        for (int j = 0; j < insideNameTxtFileVec[i].size(); j++) {
//	
				//std::string =  ; 
                            int finDifSize =  insideNameTxtFileVec[i][j].find(".txt") - insideNameTxtFileVec[i][j].find("const_") - 9;
                            std::string VMMNumber;
				if (finDifSize > 0 && insideNameTxtFileVec[i][j].length() > (insideNameTxtFileVec[i][j].find("const_") + 6 + finDifSize)) 
VMMNumber  = insideNameTxtFileVec[i][j].substr(insideNameTxtFileVec[i][j].find("const_") + 6, finDifSize);
                            	else VMMNumber = "";
                            int resFind = fileName.find(VMMNumber);
                            //std::cout << "\n VMMNumber " << VMMNumber << " " << fileName << "\n" << resFind << "\n";
                            //std::cout << "\n res fileName.find(VMMNumber) != -" << fileName.find(VMMNumber.c_str());
                            if (resFind > 0) {

                            std::cout << "\n VMMNumber " << VMMNumber << " " << fileName << "\n" << resFind << "\n";
                            std::cout << "\n res fileName.find(VMMNumber) != -" << fileName.find(VMMNumber.c_str()) << " insideNameTxtFileVec "  << 
insideNameTxtFileVec[i][j];

				int curI = i;
				
                              insideNameTxtFileVec[curI].push_back(fileName);
                               doubletFile = true;
                                
                               i = insideNameTxtFileVec.size();
				break;
                            }
                            }
                    }
                    
                    if (!doubletFile) {
                        //std::vector<std::string> instNameTxt;
                        //instNameTxt.clear();
                        //instNameTxt.push_back(fileName);
			insideNameTxtFileVec.push_back(std::vector<std::string>());
                        insideNameTxtFileVec[insideNameTxtFileVec.size()-1].push_back(fileName);
                    }
                
 
                } else if (fileName.find(".") == -1) {
                    insideFolders.push_back(pathFolder + "/" + fileName);
                }
                ep = readdir (dp);
            }
            (void) closedir (dp);
        }
    
    for (int i = 0; i < insideNameTxtFileVec.size(); i++) {
        for (int j = 0; j < insideNameTxtFileVec[i].size(); j++) {
            std::cout << "\n" << insideNameTxtFileVec[i][j] << " " << i << " " << j;
        }
    }
    
}




void convertTxtToRoot() {
    
    TFile *rootFileConvert;
    gROOT->ProcessLine("#include <vector>");
    
    insideFolders.clear();
    

    //parentDir
    
    std::string rootpath = outputPathConvert + "/const.root";
    rootFileConvert = new TFile(rootpath.c_str(), "RECREATE");
    
    buidBranchTree();
    
    std::string pathFolder = inputPathConvert;
    insideFolders.push_back(pathFolder);
    
    for (int i = 0; i < insideFolders.size(); i++) {
        findInsideTXTandFolder(insideFolders[i]);
        
//        std::cout << "\n folder is " << insideFolders[i] << " size " << insideNameTxtFileVec.size();
        int sizeVec = insideNameTxtFileVec.size();
        if (sizeVec > 0) {
            buildDataRootTree(insideFolders[i], insideNameTxtFileVec, rootFileConvert);
        }
        
//        std::cout << "\n parse folder is finish" << insideFolders[i];
    }
    
    rootFileConvert->Write();
    rootFileConvert->Print();
    delete chipConstTree;
    rootFileConvert->Close();
    delete rootFileConvert;
}

void buildLocalDB(std::string input,std::string output) {
    inputPathConvert = input;
    outputPathConvert = output;
    
    convertTxtToRoot();
}
}
