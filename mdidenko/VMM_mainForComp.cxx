
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
using namespace std;


#define VMMTree2_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "VMM_main.cxx"



int mainBuild() {
    
    
    
//    VMMTree2 *t = new VMMTree2();
//    t->Loop();
//
//    delete t;
    
    VMMTree2 t;
    t.Loop();
    
    
    cout << "\n Finish! \n";
    
    return 1;
}

TROOT root("",""); // static TROOT object

int main(int argc, char** argv)
#else
TFile* hsimple(Int_t get=0)
#endif
{
    cout<<"---> Main()"<<endl;
    mainBuild();
    
#ifdef __CINT__
    return hfile;
#else
    return 0;
#endif
}


