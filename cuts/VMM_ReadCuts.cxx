namespace cuts {
    char str[2048];

    void readCuts() {

        char pathConfig[128];
        sprintf(pathConfig, "./cuts.txt");
        FILE *f = fopen(pathConfig,"r");
        if(f) {
            fgets(str, 2048, f);
            while (!feof(f)) {
                float readData;
                
                //if(sscanf(str, "cutVDDD_L0 %f",  &readData)) cutVDDD_L0 = readData;
                
//                if(sscanf(str, "cur_minL0 %f",  &readData)) cur_minL0 = readData;
//                if(sscanf(str, "cur_maxL0 %f",  &readData)) cur_maxL0 = readData;
//
//                if(sscanf(str, "cur_minL0pos %f",  &readData)) cur_minL0pos = readData;
//                if(sscanf(str, "cur_maxL0pos %f",  &readData)) cur_maxL0pos = readData;
//
//                if(sscanf(str, "cut_bline_min %f",  &readData)) cut_bline_min = readData;
//                if(sscanf(str, "cut_bline_max %f",  &readData)) cut_bline_max = readData;
                
                
                
                
                
                
                 fgets(str, 2048, f);
            }
        }
        
        fclose(f);

    }
}
