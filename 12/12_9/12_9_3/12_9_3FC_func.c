#include <stdio.h>

#define STR_MODE0_LABEL ("Metric")
#define STR_MODE1_LABEL ("US")
#define STR_DIST_UNIT_KM ("kilometers")
#define STR_DIST_UNIT_MILE ("miles")
#define STR_CAPA_UNIT_L ("liters")
#define STR_CAPA_UNIT_GAL ("gallons")

int set_mode(const int iMode, int iLastUsedMode)
{
    const char *pModeLabel = STR_MODE0_LABEL;

    if (iMode != 0 && iMode != 1)
    {
        // Update ModeLabel
        if (iLastUsedMode)
            pModeLabel = STR_MODE1_LABEL;
        else
            pModeLabel = STR_MODE0_LABEL;

        printf("Invalid mode specified. Mode %d(%s) used.\n", iLastUsedMode, pModeLabel);

        return iLastUsedMode;
    }

    return iMode;
}

void get_info(const int iMode, double *pdfDistanceTraveled, double *pdfFuelConsumption)
{
    const char *pDistanceUnit = STR_DIST_UNIT_KM;
    const char *pCapacityUnit = STR_CAPA_UNIT_L;

    if (iMode)
    {
        pDistanceUnit = STR_DIST_UNIT_MILE;
        pCapacityUnit = STR_CAPA_UNIT_GAL;
    }
    else
    {
        pDistanceUnit = STR_DIST_UNIT_KM;
        pCapacityUnit = STR_CAPA_UNIT_L;
    }

    printf("Enter distance traveled in %s: ", pDistanceUnit);
    scanf("%lf", pdfDistanceTraveled);
    printf("Enter fuel consumed in %s: ", pCapacityUnit);
    scanf("%lf", pdfFuelConsumption);
}

void show_info(const int iMode, double *pdfDistanceTraveled, double *pdfFuelConsumption)
{
    if (iMode)
        printf("Fuel consumption is %.2lf miles per gallon.\n", *pdfDistanceTraveled / *pdfFuelConsumption);
    else
        printf("Fuel consumption is %.2lf liters per 100 km.\n", *pdfFuelConsumption / (*pdfDistanceTraveled / 100));
}