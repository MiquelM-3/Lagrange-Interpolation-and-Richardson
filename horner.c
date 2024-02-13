#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "horner.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 1
*/

double horner(double *a, double z, int n){

    int i;
    double b_1=0.0;

    for(i=n;i>=0;i--){ /*Avaluat segons seguint horner del llibre*/
        b_1=b_1*z+a[i];
    }

    return b_1;
}