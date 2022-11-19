#include <stdio.h>
#include <time.h>
#include "compteur.h"
void passer15s(){
    time_t previousTime = time(NULL);
    time_t currentTime = time(NULL);
    while (difftime(currentTime, previousTime) < 2){
        currentTime = time(NULL);
    }
}


int compteur15s() {
    time_t temps1, temps2;
    struct tm currentTime, previousTime;
    char format1[100], format2[100];

    time(&temps1);
    previousTime = *localtime(&temps1);
    strftime(format1, 100, "%X\n", &previousTime);
    puts(format1);
    fflush(stdout);
    passer15s();
    time(&temps2);
    currentTime = *localtime(&temps2);
    strftime(format2, 100, "%X\n", &currentTime);
    puts(format2);
    fflush(stdout);
}