#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/
double f(double x){
    /*fem n=4, podem hardcodejar el n que volguem*/

    /*extendre la funcio quan ln(0). 
        Agafem lim x->0 quan ln(x)*x*x*x. Aixo dona 0 (fem ln(x)/(1/x^3) i apliquem hopital)
    */
    if(x==0){
        return 0;

    }else{
        return log(fabs(x))*(x*x*x*x);
    }
}