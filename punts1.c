#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "punts.h"
/*exp*/
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2
*/

/*Calclem pi amb larctan*/
void punts(double *x, double *f , int n){
    int i;
    double a,b,x_i; /*No se ben bé com definir pi*/
    double M_PI= 4*atan(1);


    printf("Escull els limits (a,b) \n");
    scanf("%le %le", &a,&b);

    for(i=0;i<n+1;i++){
        x_i=a+ ((b-a)/2.0 ) * (1+ cos( ( M_PI *(2*i+1))/ (2*(n+1)) ));
        x[n-i]=x_i;
        f[n-i]=exp(x_i);
        }
    }

