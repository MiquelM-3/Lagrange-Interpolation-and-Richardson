#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "horner.h"

/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/
void didi(double* x, double* f, int n){

    int i,j;

    for(i=1;i<=n;i++){
        for(j=n;j>=i;j--){
            f[j]= (f[j]-f[j-1])/(x[j]-x[j-i]); /*Avaluat seguint la regla de les diferencies dividides!*/
        /*
            Te sentit perque el x[j-1] en la primera iteracio;
            En la segona, sera x[j-2], ja que estarem fent f[x1,x2,x3]= f[x2,x3]-f[x1,x2]/ (x3-x1), per exemple!
        */
        }
    }

}