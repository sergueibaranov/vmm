namespace VMMCalibration {
int ReadEventsCont(FILE *fp, event_data_t *events = NULL) {
    char str[2048];
    int NumEvents = 0;
    bool isEnableDataCont = false;
    
    int firstskipped[64];
    memset(firstskipped, 0, sizeof(firstskipped));
    int enventFirst = 1;
    while(!feof(fp)) {
        if( !fgets(str, 2048, fp) )
            continue;
        
        int F, T, Addr, Ampl, Time, TS, ART;
        
        char Fstr[64], Tstr[64], AddrStr[64], Ampstr[64], Timestr[64], TSstr[64], ARTstr[64];
        //char Fstr, Tstr, AddrStr, Ampstr, Timestr, TSstr, ARTstr;
        
        int test;
        
        ART = 0;
        
        if (sscanf(str, "EVENT %i", &test) == 1) {
            isEnableDataCont = false;
            enventFirst = test;
        } else
            
            if (sscanf(str, "ART %i", &test) == 1) {
                ART = test;
                if (enventFirst != 1) isEnableDataCont = true;
            } else
                
                if (isEnableDataCont) {
                    //if(sscanf(str, "%i %i %i %i %i %i", &F, &T, &Addr, &Ampl, &Time, &TS) == 6) {
                    if(sscanf(str, "%s %s %s %s %s %s", Fstr, Tstr, AddrStr, Ampstr, Timestr, TSstr) == 6) {
                        // ?????? ?????????? ?????????????? ???????????? ???????? ???????????? char[64]
                        F = atoi( Fstr);
                        T = atoi( Tstr);
                        Addr = atoi( AddrStr);
                        Ampl = atoi( Ampstr);
                        Time = atoi( Timestr);
                        TS = atoi( TSstr);
                        
                        if(Addr < 0 || Addr > 63)
                            continue;
                        
                        if (!firstskipped[Addr] ) {
                            firstskipped[Addr] = 1;
                            continue;
                        }
                        
                        if(events) {
                            
                            events[NumEvents].channel = Addr;
                            events[NumEvents].threshold = T;
                            events[NumEvents].art = ART;
                            events[NumEvents].time = Time;
                            events[NumEvents].amp = Ampl;
                            events[NumEvents].bcid = TS;
                        }
                        
                        NumEvents++;
                    }
                }
    }
    
    return NumEvents;
}

int ReadEventsART(FILE *fp, event_data_t *events = NULL) {
    char str[2048];
    int NumEvents = 0;
    bool nextEvent;
    char test[64];
    int ART = 0;
    bool firstEvent = true;
    bool trueNextEvent = false;
    while(!feof(fp)) {
        if( !fgets(str, 2048, fp) ) continue;
        if (string(str).find("Event") != -1 || string(str).find("EVENT") != -1) {
            if (!firstEvent) {
                nextEvent = true;
                
                if (trueNextEvent) {
                    
                    ART = -199;
                    
                    if (events != NULL) {events[NumEvents].ARTint = ART;
                    }
                    NumEvents++;
                    
                }
                
                trueNextEvent = true;
                
            } else {
                nextEvent = false;
                firstEvent = false;
            }
        }
        
        if (nextEvent) {
            if (sscanf(str, "ART: %s", test) == 1) {
                ART = atoi(test);
                
                if (events != NULL) {events[NumEvents].ARTint = ART;
                }
                NumEvents++;
                
                
                trueNextEvent = false;
                
            } else if (sscanf(str, "ART %s", test) == 1) {
                ART = atoi(test);
                
                if (events != NULL) {events[NumEvents].ARTint = ART;
                }
                NumEvents++;
                
                trueNextEvent = false;
            }
        }
    }
    
    return NumEvents;
}

int ReadEventsL0(FILE *fp, event_data_t *events = NULL) {
    char str[2048];
    int NumEvents = 0;
    bool isEnableData = false;
    bool eventFirst = true;
    while(!feof(fp)) {
        if( !fgets(str, 2048, fp) )
            continue;

        int T, Addr, Ampl, Time, TS, ART, BCID;
        int test1, test2, test3, test4, test5; // trash ??????????


        int test;

        ART = 0;

        if (string(str).find("Event") != -1) {
            isEnableData = false;
        } else

            if (sscanf(str, "ART: %i", &test) == 1) {
                ART = test;
                if (!eventFirst) isEnableData = true;
                else eventFirst = false;
            } else

                if (isEnableData) {

                    int readData = sscanf(str, "%i %i %i %i %i %i %i %i %i", &test1, &test2, &test3, &test4, &Addr, &Ampl,  &Time, &test5, &BCID);

                    if(readData == 4) {

                        if(events) {
                            TS = test4;
                            T = test1;
                        }

                    } else if(readData == 9) {

                        if(events)
                        {

                            events[NumEvents].channel = Addr;
                            events[NumEvents].threshold = 1;
                            events[NumEvents].art = ART;
                            events[NumEvents].time = Time;
                            events[NumEvents].amp = Ampl;
                            events[NumEvents].bcid = BCID;

                        }

                        NumEvents++;
                    }
                } else if (string(str).find("Data") != -1) {
                    if (!eventFirst) isEnableData = true;
                    else eventFirst = false;
                    ART = -1;
                }
    }

    return NumEvents;
}



//int ReadEventsL0(FILE *fp, event_data_t *events = NULL) {
//    char str[2048];
//    int NumEvents = 0;
//    bool isEnableData = false;
//    bool eventFirst = true;
//    while(!feof(fp)) {
//        if( !fgets(str, 2048, fp) )
//            continue;
//        
//        int T, Addr, Ampl, Time, TS, ART;
//        int test1, test2, test3, test4; // trash ??????????
//        
//        
//        int test;
//        
//        ART = 0;
//        
//        if (string(str).find("Event") != -1) {
//            isEnableData = false;
//        } else
//            
//            if (sscanf(str, "ART: %i", &test) == 1) {
//                ART = test;
//                if (!eventFirst) isEnableData = true;
//                else eventFirst = false;
//            } else
//                
//                if (isEnableData) {
//                    
//                    int readData = sscanf(str, "%i %i %i %i %i %i %i", &test1, &test2, &test3, &test4, &Addr, &Ampl,  &Time);
//                    
//                    if(readData == 4) {
//                        
//                        if(events) {
//                            TS = test4;
//                            T = test1;
//                        }
//                        
//                    } else if(readData == 7) {
//                        
//                        if(events)
//                        {
//                            
//                            events[NumEvents].channel = Addr;
//                            events[NumEvents].threshold = 1;
//                            events[NumEvents].art = ART;
//                            events[NumEvents].time = Time;
//                            events[NumEvents].amp = Ampl;
//                            events[NumEvents].bcid = TS;
//                            
//                        }
//                        
//                        NumEvents++;
//                    }
//                }
//    }
//    
//    return NumEvents;
//}

//int ReadEventsDDO(FILE *fp, event_data_t *events = NULL) { // под новый тип ДДО
//
//    char str[2048];
//    int NumEvents = 0;
//    bool isEnableDataDDO = false;
//    int countGlobalEvent = 0;
//    int ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, DDOcount;
//    int test;
//    char testChar[128];
//    bool eventFirst = true;
//
//    while(!feof(fp)) {
//        if( !fgets(str, 2048, fp) )
//            continue;
//
//        if (string(str).find("DDO DATA") != -1) {
//            if (!eventFirst) {
//                isEnableDataDDO = true;
//                DDOcount = 0;
//                countGlobalEvent++;
//            } else eventFirst = false;
//        } else
//
//            if (sscanf(str, "ART %i", &test) == 1) {
//                isEnableDataDDO = false;
//            }
//
//        if (isEnableDataDDO) {
//
//            int numEvent = sscanf(str, "%i %i %i %i %i %i %i %i %i %i", &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8, &ch9, &ch10);
//            if (numEvent != 0) {
//
//                if(events) {
//
//                    if (numEvent == 10 && DDOcount < 6) {
//
//                        events[NumEvents].channel = 9 + DDOcount * 10;
//                        events[NumEvents].amp = ch1;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 8 + DDOcount * 10;
//                        events[NumEvents].threshold = 1;
//                        events[NumEvents].amp = ch2;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 7 + DDOcount * 10;
//                        events[NumEvents].amp = ch3;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 6 + DDOcount * 10;
//                        events[NumEvents].amp = ch4;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 5 + DDOcount * 10;
//                        events[NumEvents].amp = ch5;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 4 + DDOcount * 10;
//                        events[NumEvents].amp = ch6;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 3 + DDOcount * 10;
//                        events[NumEvents].amp = ch7;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 2 + DDOcount * 10;
//                        events[NumEvents].amp = ch8;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 1 + DDOcount * 10;
//                        events[NumEvents].amp = ch9;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        events[NumEvents].channel = 0 + DDOcount * 10;
//                        events[NumEvents].amp = ch10;
//                        events[NumEvents].threshold = 1;
//                        NumEvents++;
//
//                        DDOcount++;
//
//                    } else {
//
//                        if (numEvent == 4 && DDOcount == 6) {
//
//                            events[NumEvents].channel = 3 + DDOcount * 10;
//                            events[NumEvents].amp = ch1;
//                            events[NumEvents].threshold = 1;
//                            NumEvents++;
//
//                            events[NumEvents].channel = 2 + DDOcount * 10;
//                            events[NumEvents].amp = ch2;
//                            events[NumEvents].threshold = 1;
//                            NumEvents++;
//
//                            events[NumEvents].channel = 1 + DDOcount * 10;
//                            events[NumEvents].amp = ch3;
//                            events[NumEvents].threshold = 1;
//                            NumEvents++;
//
//                            events[NumEvents].channel = 0 + DDOcount * 10;
//                            events[NumEvents].amp = ch4;
//                            events[NumEvents].threshold = 1;
//                            NumEvents++;
//
//                            //DDOcount = 0;
//                        }
//                        isEnableDataDDO = false;
//
//                    }
//
//                    if (((DDOcount * 10) + 3) > 63) {
//
//                        cout << " \n " << DDOcount << "Error! DDO read not corrected \n ";
//                        system("pause");
//
//                    }
//
//
//                } else {
//                    //if ((numEvent == 4 || numEvent == 10) && isEnableDataDDO)
//                    NumEvents += numEvent;
//                }
//
//            }
//
//        }
//    }
//
//    return NumEvents;
//}

int ReadEventsDDO(FILE *fp, event_data_t *events = NULL) {
    
    char str[2048];
    int NumEvents = 0;
    bool isEnableDataDDO = false;
    int countGlobalEvent = 0;
    int ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, DDOcount;
    int test;
    char testChar[128];
    bool eventFirst = true;
    
    while(!feof(fp)) {
        if( !fgets(str, 2048, fp) )
            continue;
        
        
        
        if (string(str).find("DDO DATA") != -1) {
            if (!eventFirst) {
                isEnableDataDDO = true;
                DDOcount = 0;
                countGlobalEvent++;
            } else eventFirst = false;
        } else if (string(str).find("EVENT") != -1) {
            if (!eventFirst) {
                isEnableDataDDO = true;
                DDOcount = 0;
                countGlobalEvent++;
            } else eventFirst = false;
        } else
            
            if (sscanf(str, "ART %i", &test) == 1) {
                isEnableDataDDO = false;
            }
        
        if (isEnableDataDDO) {
            
            int numEvent = sscanf(str, "%i %i %i %i %i %i %i %i %i %i", &ch1, &ch2, &ch3, &ch4, &ch5, &ch6, &ch7, &ch8, &ch9, &ch10);
            if (numEvent != 0) {
                
                if(events) {
                    
                    if (numEvent == 10 && DDOcount < 6) {
                        
                        events[NumEvents].channel = 9 + DDOcount * 10;
                        events[NumEvents].amp = ch1;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 8 + DDOcount * 10;
                        events[NumEvents].threshold = 1;
                        events[NumEvents].amp = ch2;
                        NumEvents++;
                        
                        events[NumEvents].channel = 7 + DDOcount * 10;
                        events[NumEvents].amp = ch3;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 6 + DDOcount * 10;
                        events[NumEvents].amp = ch4;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 5 + DDOcount * 10;
                        events[NumEvents].amp = ch5;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 4 + DDOcount * 10;
                        events[NumEvents].amp = ch6;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 3 + DDOcount * 10;
                        events[NumEvents].amp = ch7;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 2 + DDOcount * 10;
                        events[NumEvents].amp = ch8;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 1 + DDOcount * 10;
                        events[NumEvents].amp = ch9;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        events[NumEvents].channel = 0 + DDOcount * 10;
                        events[NumEvents].amp = ch10;
                        events[NumEvents].threshold = 1;
                        NumEvents++;
                        
                        DDOcount++;
                        
                    } else {
                        
                        if (numEvent == 4 && DDOcount == 6) {
                            
                            events[NumEvents].channel = 3 + DDOcount * 10;
                            events[NumEvents].amp = ch1;
                            events[NumEvents].threshold = 1;
                            NumEvents++;
                            
                            events[NumEvents].channel = 2 + DDOcount * 10;
                            events[NumEvents].amp = ch2;
                            events[NumEvents].threshold = 1;
                            NumEvents++;
                            
                            events[NumEvents].channel = 1 + DDOcount * 10;
                            events[NumEvents].amp = ch3;
                            events[NumEvents].threshold = 1;
                            NumEvents++;
                            
                            events[NumEvents].channel = 0 + DDOcount * 10;
                            events[NumEvents].amp = ch4;
                            events[NumEvents].threshold = 1;
                            NumEvents++;
                            
                            //DDOcount = 0;
                        }
                        isEnableDataDDO = false;
                        
                    }
                    
                    if (((DDOcount * 10) + 3) > 63) {
                        
                        cout << " \n " << DDOcount << "Error! DDO read not corrected \n ";
                        system("pause");
                        
                    }
                    
                    
                } else {
                    //if ((numEvent == 4 || numEvent == 10) && isEnableDataDDO)
                    NumEvents += numEvent;
                }
                
            }
            
        }
    }
    
    return NumEvents;
}
}

