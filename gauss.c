/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"

double gauss(double** a, double* x, double* b, int n, double tol){
    /*
        Primer fem el pivotatge. Si (k,k)<tol, llavors es para
    */
    double pivot,auxiliar,mult;
    double determinant;
    int contador_det=1;
    int max_fila,fila,files,files_x, col_fila_i,columnes_x;
    int i,j,k;

    /*Aqui farem gauss*/
    for(i=0; i<n ;i++){ /* Per cada fila de la matriu n*n */
        
        /*Primer trobarem el pivot, i ens el guardem junt amb la fila*/
        
        pivot=fabs(a[i][i]);
        max_fila=i;
        for(j=i+1; j<n; j++){
            if(fabs(pivot) < fabs(a[j][i])){
                pivot=a[j][i];
                max_fila=j;
            }
        }
        /*
            Si el max és més gran que la tolerància, llavors canviarem tota la fila 1 per la j
                Sinó retornem 0
        */
        if (fabs(pivot) < tol) {
            printf("tolerància arribada!");
            return 0.0;
        }
        
        /*Capgirem */
        if(max_fila!=i){
            contador_det*=-1; /*Actualitzem el contador del determinant*/
            for(k=0; k<n;k++){
                auxiliar=a[i][k];
                a[i][k]=a[max_fila][k];
                a[max_fila][k]=auxiliar;
            }
            /*També canviem el vector ind:*/
            auxiliar=b[max_fila];
            b[max_fila]=b[i];
            b[i]=auxiliar;
        }
        /*
            Per cada fila:
                Calculem el multiplicador, multipliquem tota la primera fila pel muliplicador i li restem a i fila
        */

        for(fila=i+1;fila<n;fila++){ /*Per cada fila a partir de la i*/
            mult= a[fila][i] /a[i][i]; /*Multiplicador*/

            for(col_fila_i=i; col_fila_i<n; col_fila_i++){ /*Li restem a cada element de la fila objectiu l'element de la mateixa columna en la fila i pel seu multiplicador*/
                a[fila][col_fila_i] -= a[i][col_fila_i]*mult;
            }
            b[fila] -= b[i] * mult;
        }
        
    }
    /*
        Detereminant: multipliquem tots els elements de la diagonal
    */
    determinant=1;
    for(files=0; files<n;files++){
        determinant*=a[files][files];
    }
    determinant*=contador_det; /*hem de tenir en compte el contador de les permutacions de les files!*/

    /*
        Ara calculem finalment la solució del sistema amb backtracking
    */

    for(files_x=n-1;files_x >= 0;files_x--){
        x[files_x]= b[files_x]/a[files_x][files_x]; /*Tenim la solució de x[i]*/
        for(columnes_x=n-1;columnes_x>files_x;columnes_x--){
            x[files_x]-= (x[columnes_x]*a[files_x][columnes_x])/a[files_x][files_x]; /*Formula pel backtracking als apunts*/
        }
    }
    /*
    printf("Solucio:");
    printf("\n");
    for(sol=0; sol<n;sol++){
        printf("%12.5e\t",x[sol]);
    }
    printf("\n");
    
    printf("\n");
    printf("determinant");
    printf("%12.5e",determinant);
    printf("\n");
    */
    return determinant;
}