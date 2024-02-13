#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "punts.h"
#include "gauss.h"
#include "horner.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 1

     gcc -c -ansi -Wall gauss.c
     gcc -c -ansi -Wall horner.c
     gcc -c -ansi -Wall inter1.c
     gcc -c -ansi -Wall puntsfit.c

    gcc gauss.o horner.o inter1.o puntsfit.o -o exercici1.exe
*/

int main(){
    double valor_x;
    double* vector_f;
    double* copia_f;
    double* vector_x;
    double* vector_a; 
    double** matriu; /*Aqui aniran els coeficients*/

/*OBS: Podem hardcodejar el n que volguem, mentre tinguem prou punts per avaluar. Posem 6 d'exemple*/
    int n=8,i,j;

    /*Ara anem a alocar espai, i inicialitzem vectors i matrius*/
    matriu = (double**)malloc((n+1) * sizeof(double*)); /*Guardem la memoria: dim*sizeof(int), és a dir, a cada punter li assignem una memòria d'un altre punter*/
    for (i = 0; i < n+1; i++) {
        matriu[i] = (double*)malloc((n+1) * sizeof(double)); /*A cada punter intern li assignem la memòria de una integer *totes les integers*/
    }

    for (i = 0; i < n+1; i++) {
        for (j = 0; j < n+1; j++) {
            matriu[i][j] = 0.0;
        }
    }

    /*Inicialitzem tots els vectors necessaris*/
    vector_x=(double*)malloc((n+1)*sizeof(double));
    vector_f=(double*)malloc((n+1)*sizeof(double));
    vector_a=(double*)malloc((n+1)*sizeof(double));
    copia_f=(double*)malloc((n+1)*sizeof(double));
    for (i = 0; i < n+1; i++) {
        vector_x[i] = 0.0;
        vector_f[i]=0.0;
        copia_f[i]=0.0;
        vector_a[i] = 0.0;
    }

    /*Posem els valors de x i f*/
    punts(vector_x,vector_f,n);

    /*Prints dels vectors (comprovacio visual)*/
    printf("Vector_x: son els punts on avaluem \n");
    for(i=0;i<n+1;i++){
        printf("%12.5e\t",vector_x[i]);
    }
    printf("\nVector_f: son les avaluacions dels punts \n");
    for(i=0;i<n+1;i++){
        printf("%12.5e\t",vector_f[i]);
        copia_f[i]=vector_f[i]; /*En fem una copia, que edsprés és modificarà*/
    }

    /*Ens calculem la matriu de coeficients, ossigui la vandermonde*/
    for(i=0;i<n+1;i++){
        valor_x=1;
        matriu[i][0]=1;
        for(j=1;j<n+1;j++){
            valor_x=valor_x*vector_x[i]; /*El valor_x és per no haver de calcular el pow*/
            matriu[i][j]=valor_x;
        }
    }
    /*Print de la matriu DEBUG
    for(i=0;i<n+1;i++){
        for(j=0;j<n+1;j++){
            printf("%3.2e\t",matriu[i][j]);
        }
        printf("\n");
    }
    */

    /*Ara fem gauss per obtenir els vectors*/
    gauss(matriu,vector_a,vector_f,n+1, 1e-20); /*Nota: hem modificat el vector_f!!*/

    /*Print de la matriu resolta DEBUG
    for(i=0;i<n+1;i++){
        for(j=0;j<n+1;j++){
            printf("%3.2e\t",matriu[i][j]);
        }
        printf("\n");
    }
    */

    /*Comprovem que estigui bé: vector_a*/
    printf("\nVector_a: son els coeficients del polinomi interpolador \n");
    for (i = 0; i < n+1; i++) {
        printf("%12.5e\t",vector_a[i]);
    }

    /*COMPROVACIO "VISUAL"*/
    printf("\n");
    printf("\nVector_horner: es l'avaluacio del polinomi interpolador. \nHauria de coincidir amb el vector_f\n");
    for (i=0;i<n+1;i++){
        printf("%12.5e\t",horner(vector_a, vector_x[i], n));
    }

    /*COMPROVACIO RIGUROSA (mirem que estigui en un marge)*/
    printf("\n\nComprovacio\n");
    for(i=0; i<n+1;i++){
        if(fabs(horner(vector_a, vector_x[i], n)-copia_f[i])<1e-12){ /*tolerancia!*/
            printf("%d\t",1);
        }else{
            printf("%d\t",0);
        }
    }

    free(vector_x);
    free(vector_f);
    free(copia_f);
    free(vector_a);
    for (i = 0; i < n+1; i++) {
        free(matriu[i]);
    }
    free(matriu);
    return 1;

}