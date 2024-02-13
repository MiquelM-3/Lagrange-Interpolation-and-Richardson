#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "increment.h"
#include "derivar.h"
#include "f.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/
/*
 gcc -c -ansi -Wall richardson.c
 gcc -c -ansi -Wall f4.c
 gcc -c -ansi -Wall increment.c
 gcc -c -ansi -Wall derivar.c

 gcc -c -ansi -Wall f1.c
 gcc -c -ansi -Wall f2.c
 gcc -c -ansi -Wall f3.c
 gcc -c -ansi -Wall f4.c

gcc richardson.o f1.o increment.o derivar.o -o exercici_3_f1.exe

*/

int main(){
    double prec,q,x,h,valor,derivacio_opt; /*h hauria de ser 10^-1 o algo aixi, petitonet*/
    int k,ordre,i,j,trobat; /*k com a màxim 10 o 15*/
    int numfunc;
    FILE *txt1;
    double** matriu;

    /*Assumirem que al txt estan en ordre les coses*/
    txt1=fopen("dades_richardson.txt","r");
    if (txt1==NULL){
        return -1;
    }

    /*Llegim els valors*/
    fscanf(txt1, "%le %le %d %d %le %le" , &prec, &q, &k, &ordre, &x, &h);

    printf("%s %le \n", "Precisio: ", prec);
    printf("%s %le \n", "Q (pas en la derivacio): ", q);
    printf("%s %le \n", "H (pas inicial) ", h);
    printf("%s %d \n", "K (nombre max d'iteracions): ", k);
    printf("%s %d \n", "Ordre de la derivada: ", ordre);
    printf("%s %le \n", "Avaluacio de la derivada ", x);
    

    /*Ara inicialitzem la matriu de programació dinàmica on conservarem els valors*/
    matriu = (double**)malloc(k * sizeof(double*)); /*Guardem la memoria: dim*sizeof(int), és a dir, a cada punter li assignem una memòria d'un altre punter*/
    for (i = 0; i < k; i++) {
        matriu[i] = (double*)malloc(k * sizeof(double)); /*A cada punter intern li assignem la memòria de un double*/
    }
    for (i=0;i<k;i++){
        for(j=0;j<k;j++){
            matriu[i][j]=0;
        }
    }

    /*Ara anirem omplint la taula d'amunt cap avall*/
    /*Primer omplim la primera columna, que és la de les derivades*/
    derivacio_opt=0;
    trobat=0; /*Quan trobem un valor òptim, parem*/
    valor=h;
    matriu[0][0]= derivar(x,valor,ordre,f);
    
    
    /*Ara omplirem la resta de columnes:*/
    for(i=1;i<k ;i++){ /*Revisem totes les files*/
        valor/=q;
        matriu[i][0]= derivar(x,valor,ordre,f);
        if(fabs(matriu[i][0]-matriu[i-1][0])<prec){
            derivacio_opt=matriu[i][0];
            trobat=1;
            break;
        }
        for(j=1;j<=i;j++){/*Revisem les columnes corresponents de cada fila*/
            matriu[i][j]=matriu[i][j-1]+increment(2*(j),q,matriu[i-1][j-1],matriu[i][j-1]);
            /*
            printf("%le \n",matriu[i-1][j]);
            printf("%le \n",increment(2*(j),q,2,3));
            printf("%le \n",matriu[i-1][j]-matriu[i-1][j-1]);
            */
            if(fabs(matriu[i][j]-matriu[i-1][j])<prec){
                derivacio_opt=matriu[i][j];
                trobat=1;
                break;
            }
        }
        if(trobat==1){
            break;
        }
    }
    
    printf("\n \n");
    for (i=0;i<k;i++){
        for(j=0;j<k;j++){
            printf("%10.5e \t",matriu[i][j]);
        }
        printf("\n");
    }
    

    if(trobat!=1){
        printf("%s", "No s'ha trobat cap derivacio optima. \n");
    }else{
        printf("%s", "S'ha trobat una derivacio optima:\n");
        printf("%le \n",derivacio_opt);
    

        /*Anem a comparar-ho amb l'error real. Ho harcodegem per comprovar*/
        /*d/dx -> e^x, cos(x), sng(x)*3x*x, x^(3) * (3*ln(x)+1)*/
        /*d^2/d^2x -> e^x, -sin(x), sng(x)*6x , x^2*(12*ln(x)+7)*/
        /*Nota:
            Anirem per casos, depenen de l'ordre i de x
        */
        printf("Escull una funcio, 1,2,3,4, per veure el seu error. \n");
        scanf("%d",&numfunc);
        switch(numfunc){
            case 1:
                if(ordre==1){
                    printf("%le", fabs(derivacio_opt-exp(x))); 
                }else{
                    printf("%le", fabs(derivacio_opt-exp(x))); 
                }
                break;
            case 2:
                if(ordre==1){
                    printf("%le", fabs(derivacio_opt-cos(x))); 
                }else{
                    printf("%le", fabs(derivacio_opt+sin(x))); 
                }
                break;
            case 3:
                /*la derivada no està definida en x=0 realment, aixi que "l'extendrem"*/
                if(ordre==1){
                    if(x>0){
                        printf("%le \n", fabs(derivacio_opt- 3*(x*x))); 
                    }else{
                        printf("%le \n", fabs(derivacio_opt+ 3*(x*x))); 
                    }
                }else{
                    if(x>0){
                        printf("%le \n", fabs(derivacio_opt- 6*(x))); 
                    }else{
                        printf("%le \n", fabs(derivacio_opt+ 6*(x))); 
                    }
                }
                break;
            case 4:
                /*Observacio: ni la primera ni la segona derivada estan ben definides aqui en x=0.
                    Podriem fer una extensió en x=0, fent el límits (hopitale) (ens dona 0).
                */
                if(ordre==1){

                    if(x==0){
                        printf("%le \n", fabs(derivacio_opt- 0)); 
                    }else{
                        printf("%le \n", fabs(derivacio_opt- pow(x,3)*(4*log(x)+1)));  
                    }
                }else{
                    if(x==0){
                        printf("%le \n", fabs(derivacio_opt- 0)); 
                    }else{
                        printf("%le \n", fabs(derivacio_opt- pow(x,2)*(12*log(x)+7))); 
                    }
                }
                break;
            default:
                printf("Escull entre 1 i 4.\n");
        }

    }


    for (i = 0; i < k; i++) {
        free(matriu[i]);
    }
    free(matriu);

    fclose(txt1);
    return 1;
}