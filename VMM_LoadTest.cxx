namespace VMMCalibration {
void LoadTest(char *file, test_t *test) {
    
    test->num_events = 0;
    FILE *fp = fopen(file, "r");
    ReadHeader(fp, test);
    fclose(fp);
    
    fp = fopen(file, "r");
    
    if (isContinuous) {
        test->num_events = ReadEventsCont(fp);
    }
    else if (isL0) {
        test->num_events = ReadEventsL0(fp);
    }
    else if (isL0POS) {
        test->num_events = ReadEventsL0(fp);
    }
    
    else if (isARTCONT || isL0ART || isL0POSART) {
        test->num_events = ReadEventsART(fp);
    } else if (isDDOCONT || isL0DDO || isL0POSDDO) test->num_events = ReadEventsDDO(fp);
    
    test->events = new event_data_t[test->num_events];
    
    fseek(fp, 0, 0);
    fclose(fp);
    
    for (int pp = 0; pp < AMPDACMEAN.size(); pp++) {
        if(test->DAC == AMPDACMEAN[pp]) {
                    FILE *fp = fopen(file, "r");
                    ReadHeaderMeanFile(fp, test);
                    fclose(fp);
        }
    }
    
//    if (test->DAC == AMPDACMEAN) {
//        FILE *fp = fopen(file, "r");
//        ReadHeaderMeanFile(fp, test);
//        fclose(fp);
//    }
    
    fp = fopen(file, "r");
    
    if (isContinuous) ReadEventsCont(fp, test->events);
    else if (isL0) ReadEventsL0(fp, test->events);
    else if (isL0POS) ReadEventsL0(fp, test->events);
    else if (isARTCONT || isL0ART || isL0POSART) {
        ReadEventsART(fp, test->events);
    } else if (isDDOCONT || isL0DDO || isL0POSDDO) test->num_events = ReadEventsDDO(fp, test->events);
    
    fclose(fp);
}
}
