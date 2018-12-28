#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <TError.h>

namespace VMMCalibration {

std::string inputPath = "/output";
std::string outputPath = "/output/localDB";

std::string internalFolderNameMass[4] = {"CONT", "L0", "L0", "BASELINE"};

int NUM_TESTS = 0;
int NUM_TESTS_SKEW = 0;

std::vector<std::string> nameFilesContPDO;
std::vector<std::string> nameFilesContTDO;
std::vector<std::string> nameFilesContART;

std::vector<std::string> nameFilesL0PDO;
std::vector<std::string> nameFilesL0TDO;
std::vector<std::string> nameFilesL0ART;

std::vector<std::string> nameFilesL0posPDO;
std::vector<std::string> nameFilesL0posTDO;
std::vector<std::string> nameFilesL0posART;

std::vector<std::string> BLinePos;
std::vector<std::string> BLineNeg;

std::vector<std::string> currentNameFilesPDO;
std::vector<std::string> currentNameFilesTDO;
std::vector<std::string> currentNameFilesART;

std::string macORWin = "/";
//std::string macORWin = "\\";

float bLinePause;
bool isDDOCONT = false;
bool isContinuous = false;
bool isARTCONT = false;
bool isL0POS = false;
bool isL0POSDDO = false;
bool isL0POSART = false;
bool isL0 = false;
bool isL0DDO = false;
bool isL0ART = false;

TCanvas *gCnv;

int bitSize = 10;
char nameConst[256];

float limitRMS_PDO_L0 = 10;
float limitRMS_PDO_CONT = 10;
float limitRMS_PDO_DDO = 10;

float limitRMS_TDO_L0 = 10;
float limitRMS_TDO_CONT = 10;

char infoChannelsPath[2048];

std::string configurationName;
std::string addNameToHistogram = "";
    
std::string internalFolderName = "";
std::string addNameConst = "";

std::string userID = "";
std::string VMM3_PART_ID = "";
std::string dataTesting = "";
std::string FPGA_VER = "";

bool isDebug = true;

std::vector<int> AMPDACMEAN{0};
    
std::vector<int> APMDACContMEAN{400};
std::vector<int> APMDACL0MEAN{ 85, 90, 75};
std::vector<int> APMDACL0POSMEAN{330, 300};

//int APMDACContMEAN = 400;
//int APMDACL0MEAN = 85;
//int APMDACL0POSMEAN = 330;
//
//int APMDACContMEAN = 400;
//int APMDACL0MEAN = 90;
//int APMDACL0POSMEAN = 300;
//
//int APMDACContMEAN = 400;
//int APMDACL0MEAN = 75;
//int APMDACL0POSMEAN = 300;


//char infoChannelsPath[2048];
char test_mode[512];
char test_mode_path[512];
char path_testing[512];

float errorSlope[64];
float errorInter[64];

float meanTDO[64];
int entriesMeanTDO[64];
float meanPDO[64];
int entriesMeanPDO[64];

bool isFirstMEANPDO = false;
bool isFirstMEANTDO = false;

int count_chn_ne;
int count_chn_dead;

float TempMax;
float TempMin;

float VDD_V_Max;
float VDD_V_Min;
float VDD_A_Max;
float VDD_A_Min;

float VDDD_V_Max;
float VDDD_V_Min;
float VDDD_A_Max;
float VDDD_A_Min;

float VDDP_V_Max;
float VDDP_V_Min;
float VDDP_A_Max;
float VDDP_A_Min;

float VDAD_V_Max;
float VDAD_V_Min;
float VDAD_A_Max;
float VDAD_A_Min;

int BOARD_ID;

//char pdfname[256], pdfopen[256], pdfclose[256];
    
bool posEnable = false;
bool negEnable = false;
    
char pdfnameMain[256], pdfopenMain[256], pdfcloseMain[256];
char pdfnameMainPOS[256], pdfopenMainPOS[256], pdfcloseMainPOS[256];
char pdfnameMainNEG[256], pdfopenMainNEG[256], pdfcloseMainNEG[256];

struct event_data_t {
    unsigned char channel;
    bool threshold;
    unsigned char art;
    
    int ARTint;
    int time;
    int amp;
    int bcid;
};



struct test_t {
    struct event_data_t *events;
    int num_events;
    
    int pulses;
    int chip_id;
    int DAC;
    int TAC;
    int THRESHOLD;
    int PEAKINGTIME;
    float GAIN;
    
    float meanPDO[64];
    float rmsPDO[64];
    
    float meanTDO[64];
    float rmsTDO[64];
    
    int numEntries[64];
    
    float SKEW;
    float bLinePause;
    
    float Temp;
    
    float VDD_V;
    float VDD_A;
    
    float VDDD_V;
    float VDDD_A;
    
    float VDDP_V;
    float VDDP_A;
    
    float VDAD_V;
    float VDAD_A;
};

int nonCorrectValue = -100000;
}
