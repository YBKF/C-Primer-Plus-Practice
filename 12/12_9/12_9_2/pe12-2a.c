#include <stdio.h>
// #include <stdbool.h>

#define STR_MODE0_LABEL ("Metric")
#define STR_MODE1_LABEL ("US")
#define STR_DIST_UNIT_KM ("kilometers")
#define STR_DIST_UNIT_MILE ("miles")
#define STR_CAPA_UNIT_L ("liters")
#define STR_CAPA_UNIT_GAL ("gallons")

/**
 * Save selected mode. Only 0 or 1.
 */
static int s_iCurrentMode = 0;
static double s_dfDistanceTraveled = 0.0;
static double s_dfFuelConsumption = 0.0;

void set_mode(const int mode)
{
    static const char *s_pModeLabel = STR_MODE0_LABEL;
    // bool unchanged = 0;

    // When user enter a correct mode number then s_iCurrentMode = mode, if not do nothing
    if (mode != 0 && mode != 1)
    {
        printf("Invalid mode specified. Mode %d(%s) used.\n", s_iCurrentMode, s_pModeLabel);
        return;
    }

    // If mode changed.
    if (s_iCurrentMode != mode)
    {
        // Update CurrentMode
        s_iCurrentMode = mode;

        // Update ModeLabel
        if (s_iCurrentMode)
            s_pModeLabel = STR_MODE1_LABEL;
        else
            s_pModeLabel = STR_MODE0_LABEL;
    }
}

void get_info()
{
    static const char *s_pDistanceUnit = STR_DIST_UNIT_KM;
    static const char *s_pCapacityUnit = STR_CAPA_UNIT_L;
    static int s_iLastUsedMode = 0;

    // If mode changed.
    if (s_iLastUsedMode != s_iCurrentMode)
    {
        s_iLastUsedMode = s_iCurrentMode;

        if (s_iCurrentMode)
        {
            s_pDistanceUnit = STR_DIST_UNIT_MILE;
            s_pCapacityUnit = STR_CAPA_UNIT_GAL;
        }
        else
        {
            s_pDistanceUnit = STR_DIST_UNIT_KM;
            s_pCapacityUnit = STR_CAPA_UNIT_L;
        }
    }

    printf("Enter distance traveled in %s: ", s_pDistanceUnit);
    scanf("%lf", &s_dfDistanceTraveled);
    printf("Enter fuel consumed in %s: ", s_pCapacityUnit);
    scanf("%lf", &s_dfFuelConsumption);
}

void show_info()
{
    if (s_iCurrentMode)
        printf("Fuel consumption is %.2lf miles per gallon.\n", s_dfDistanceTraveled / s_dfFuelConsumption);
    else
        printf("Fuel consumption is %.2lf liters per 100 km.\n", s_dfFuelConsumption / (s_dfDistanceTraveled / 100));
}