#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hornernewton.h"
#include "punts.h"
#include "didi.h"
/*

    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2
    
    Comandaments
     gcc -c -ansi -Wall hornernewton.c
     gcc -c -ansi -Wall internew.c
     gcc -c -ansi -Wall puntsfit.c
     gcc -c -ansi -Wall didi.c

     gcc -c -ansi -Wall punts1.c
     gcc -c -ansi -Wall punts2.c
     gcc -c -ansi -Wall punts3.c
     gcc -c -ansi -Wall punts4.c
     gcc -c -ansi -Wall punts5.c
     gcc -c -ansi -Wall punts6.c
     gcc -c -ansi -Wall punts7.c
     gcc -c -ansi -Wall punts8.c

     gcc hornernewton.o internew.o punts3.o didi.o -o exercici2_punts3.exe

    GNUPLOT
     g(x)= atan(x), f(x)= exp(x), a(x)= abs(x), r(x)= 1/(1+25*x*x)
     plot f(x), 'fitxer_dades_pol.txt' //Aixo farà les dues a la vegada! També s'hi poden posar mes funcions despres duna altra coma
*/

/*
    ELS COMENTARIS DE LES FUNCIONS ESTAN EN EL FITXER respostes_preguntes.txt
*/
int main(){

    double* vector_f;
    double* vector_x;
    double punt_avaluar;
    int i,n,m;
    FILE *f1;

    /*
        Llegim el grau del polinomi
    */
    printf("\nQuin grau del polinomi vols? Nota: en els fitxers de punts de cada funcio només hi ha fins a 11 punts \n");
    scanf("%i", &n);
    
    /*Inicialitzem els vectors*/
    vector_x=(double*)malloc((n+1)*sizeof(double));
    vector_f=(double*)malloc((n+1)*sizeof(double));
    for (i = 0; i < n+1; i++) {
        vector_x[i] = 0.0;
        vector_f[i] = 0.0;
    }

    /*Calculem els punts i el vector_f, junt amb les diferencies dividides*/
    punts(vector_x,vector_f,n);
    didi(vector_x,vector_f,n);
    /*PROVES*/
 
    printf("vector_x: ");
    for (i = 0; i <= n; i++) {
        printf("%12.5e\t ", vector_x[i]);
    }
    printf("\n");

    printf("vector_f: ");
    for (i = 0; i <= n; i++) {
        printf("%12.5e\t ", vector_f[i]);
    }
    printf("\n");


    printf("\nQuants punts vols on avaluar el polinomi? \n ");
    scanf("%i", &m);

    /*
        Obrim el fitxer on deixarem l'avaluacio del polinomi.
        He posat 3 fitxers estàndards amb n=2,4,6,7,10 que són les comprovacions que he anat fent
    */
    switch (n) {
        case 2:
            f1=fopen("fitxer_dades_pol2.txt","w");
            break;
        case 4:
            f1=fopen("fitxer_dades_pol4.txt","w");
            break;
        case 6:
            f1=fopen("fitxer_dades_pol6.txt","w");
            break;
        case 7:
            f1=fopen("fitxer_dades_pol7.txt","w");
            break;
        case 10:
            f1=fopen("fitxer_dades_pol10.txt","w");
            break;
        default:
            f1=fopen("fitxer_dades_poln.txt","w");
            break;
    }
    if(f1==NULL){
        return -1; /*Comprovem que el fitxer no sigui NULL*/
    }

    /*
        Demanem els punts a,b on avaluarem els punts donats
    */
    printf("\n Avaluarem els punts en els limits [a,b]: \n");
    printf("%12.5e\t \n %12.5e\t \n", vector_x[0] , vector_x[n]);
    for(i=0;i<m+1;i++){
        punt_avaluar= vector_x[0]+i*((vector_x[n]-vector_x[0]) / (double)m); /*S'ha optat per avaluarlos espaiats*/
        fprintf(f1, "%12.15e %22.15e\n", punt_avaluar, hornernewton(vector_f,vector_x,punt_avaluar,n)); /*Ho guardem al fitxer*/
    }
    

    free(vector_x);
    free(vector_f);
    fclose(f1);

    return 1;
}