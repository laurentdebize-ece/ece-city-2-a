#include "compteur.h"

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double) t2 - t1) / CLOCKS_PER_SEC;
    return elapsed;
}

paramclock check_time_15(paramclock *majclock, DonneesJoueur *joueur) {
    clock_t t1, t2;
    t1 = majclock->t1;
    int maj = 0;
    long check15;
    t2 = clock();
    check15 = timediff(t1, t2);
    if (check15 >= 10) {
        majclock->majdon = 1;
        majclock->t1 = t2;
    }
    joueur->compteurTemps = t2 / 1000;
}
