#include <stdio.h>
#include <tgmath.h>
#include "general.h"
#include "config.h"

#define EPS 1e-6

int IsEqNum  (double n, double m) {

    return fabs(n - m) < EPS;
}

int ClearStdinBuf () {

    int trash = false;
    int c = 0;
    while((c = getchar()) != '\n'){
        if (c != ' ' && c != '\t'){
            trash = true;
        }
    }

    return trash;
}

void fswap   (double *a, double *b) {

    double *tmp = a;
    a = b;
    b = tmp;
}

void strswap (char **str1, char **str2) {

    char *tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

int WantContinue () {

    printf("Do you want to continue [Y/N]?\n");

    int c = getchar();
    int isClear = ClearBuf();
    while((c != 'Y' && c != 'y' && c != 'N' && c != 'n') || isClear != 0){
        printf("Incorrect value\n");
        printf("Do you want to continue [Y/N]?\n");

        c = getchar();
        isClear = ClearBuf();
    }

    if(c == 'Y' || c =='y'){
        return 1;
    }

    return 0;
}
