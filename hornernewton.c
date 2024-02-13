#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hornernewton.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2
*/

double hornernewton(double* dd, double* x, double z,int n){
    double b_1=0;
    int j;

    for(j=n;j>=0;j--){ /*Avaluat segons seguint horner del llibre*/
        b_1=b_1*(z-x[j])+dd[j]; 
    }

    /*
        Notem que en el fons estem fent:
        b3=a3
        b2=b3(x-x2) + a2
        b1=b2(x-x1) + a1
        b0=b1(x-x0) + a0
        = a0+(x-x0)((a3(x-x2)+a2)(x-x1)+a1), que es efectivament el resultat!
    */
    

    return b_1;
}