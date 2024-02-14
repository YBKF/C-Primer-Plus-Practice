#ifndef _INC_12_9_3FC_FUNC
#define _INC_12_9_3FC_FUNC

int set_mode(const int iMode, int iLastUsedMode);
void get_info(const int iMode, double *pdfDistanceTraveled, double *pdfFuelConsumption);
void show_info(const int iMode, double *pdfDistanceTraveled, double *pdfFuelConsumption);

#endif