#include <stdio.h>

int main() {
    FILE *temperatureFile;
    double T;
    temperatureFile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
    if (temperatureFile == NULL)
    {
        printf("Error: Unable to open thermal_zone0/temp\n");
        return(-1);
    }
    fscanf (temperatureFile, "%lf", &T);
    T /= 1000;
    printf ("The CPU temperature is: %.2lf C\n", T);
    fclose (temperatureFile);
    return 0;
}

