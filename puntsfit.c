#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "punts.h"

/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 1 i 2
*/

void punts(double *x, double *f , int n){

    int i,num_funcio;
    double x_i,f_i;
    FILE *fitx;

    /*
        Això és per veure com es comporten les funcions triades!
    */
    printf("Funcio on avaluar el polinomi (introdueix el numero corresponent): 1 -> exp(x), 2 -> arctan(x), 3 -> abs(x), 4 -> 1/(1+25x^2) \n");
    scanf("%i", &num_funcio);
        switch (num_funcio) {
            case 1:
                fitx=fopen("fitxer_dades_exp.txt","r");
                break;
            case 2:
                fitx=fopen("fitxer_dades_arctan.txt","r");
                break;
            case 3:
                fitx=fopen("fitxer_dades_abs.txt","r");
                break;
            case 4:
                fitx=fopen("fitxer_dades_R.txt","r");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

    if(fitx==NULL){
        return; /*Comprovem que el fitxer no sigui NULL*/
    }

    for(i=0;i<n+1;i++){
        fscanf(fitx, "%le %le" , &x_i, &f_i);
        x[i]=x_i;
        f[i]=f_i;
    }
    fclose(fitx);
}