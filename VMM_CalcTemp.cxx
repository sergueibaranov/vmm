namespace VMMCalibration {
void calc_data_Temp(test_t *test) {

    
    if (test->Temp > TempMax|| TempMax == nonCorrectValue) TempMax = test->Temp;
    if (test->Temp < TempMin|| TempMin == nonCorrectValue) TempMin = test->Temp;
    
    if (test->VDD_V > VDD_V_Max || VDD_V_Max == nonCorrectValue) VDD_V_Max = test->VDD_V;
    if (test->VDD_V < VDD_V_Min || VDD_V_Min == nonCorrectValue) VDD_V_Min = test->VDD_V;
    
    if (test->VDD_A > VDD_A_Max || VDD_A_Max == nonCorrectValue) VDD_A_Max = test->VDD_A;
    if (test->VDD_A < VDD_A_Min || VDD_A_Min == nonCorrectValue) VDD_A_Min = test->VDD_A;
    
    if (test->VDDD_V > VDDD_V_Max || VDDD_V_Max == nonCorrectValue) VDDD_V_Max = test->VDDD_V;
    if (test->VDDD_V < VDDD_V_Min || VDDD_V_Min == nonCorrectValue) VDDD_V_Min = test->VDDD_V;
    
    if (test->VDDD_A > VDDD_A_Max || VDDD_A_Max == nonCorrectValue) VDDD_A_Max = test->VDDD_A;
    if (test->VDDD_A < VDDD_A_Min || VDDD_A_Min == nonCorrectValue) VDDD_A_Min = test->VDDD_A;
    
    if (test->VDDP_V > VDDP_V_Max || VDDP_V_Max == nonCorrectValue) VDDP_V_Max = test->VDDP_V;
    if (test->VDDP_V < VDDP_V_Min || VDDP_V_Min == nonCorrectValue) VDDP_V_Min = test->VDDP_V;
    
    if (test->VDDP_A > VDDP_A_Max || VDDP_A_Max == nonCorrectValue) VDDP_A_Max = test->VDDP_A;
    if (test->VDDP_A < VDDP_A_Min || VDDP_A_Min == nonCorrectValue) VDDP_A_Min = test->VDDP_A;
    
    if (test->VDAD_V > VDAD_V_Max || VDAD_V_Max == nonCorrectValue) VDAD_V_Max = test->VDAD_V;
    if (test->VDAD_V < VDAD_V_Min || VDAD_V_Min == nonCorrectValue) VDAD_V_Min = test->VDAD_V;
    
    if (test->VDAD_A > VDAD_A_Max || VDAD_A_Max == nonCorrectValue) VDAD_A_Max = test->VDAD_A;
    if (test->VDAD_A < VDAD_A_Min || VDAD_A_Min == nonCorrectValue) VDAD_A_Min = test->VDAD_A;
}
}
