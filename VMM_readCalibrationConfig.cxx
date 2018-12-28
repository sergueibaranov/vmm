namespace VMMCalibration {
void readVMM3CalibrationConfig() {
    
    char pathConfig[512];
    
    //cout << "/n \n gSystem->pwd() = " << gSystem->pwd();
    sprintf(pathConfig, "./VMM3CalibrationConfig.txt");
    FILE *f = fopen(pathConfig,"r");
    if(f) {
        
        char str[2048];
        fgets(str, 2048, f);
        
        int readData = 0;
        if (sscanf(str, "limitRMS_PDO_CONT %i", &readData)) {
            limitRMS_PDO_CONT = readData;
        }
        if (sscanf(str, "limitRMS_PDO_L0 %i", &readData)) {
            limitRMS_PDO_L0 = readData;
        }
        if (sscanf(str, "limitRMS_PDO_DDO %i", &readData)) {
            limitRMS_PDO_DDO = readData;
        }
        fgets(str, 2048, f);
        fclose(f);
    } else {
        std::ofstream VMM3CalibrationConfig;
        VMM3CalibrationConfig.open(pathConfig, std::ios::app);
        
        VMM3CalibrationConfig <<"limitRMS_PDO_CONT " << limitRMS_PDO_CONT;
        VMM3CalibrationConfig <<"\nlimitRMS_PDO_L0 " << limitRMS_PDO_L0;
        VMM3CalibrationConfig <<"\nlimitRMS_PDO_DDO " << limitRMS_PDO_DDO;
        
        VMM3CalibrationConfig.close();
    }
}
}
