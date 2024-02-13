#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivar.h"
#include "f.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/

double derivar(double x, double h, int ordre, double(*f)(double)){
    double value=0;
    /*printf("%le %le \n",f(x+h),f(x-h));*/
    if(ordre==1){ /*Primera derivada*/
        value=(f(x+h)-f(x-h) )/(2*h);
    }else if (ordre==2) /*Segona derivada*/
    {
        value=(f(x+h)-2*f(x) + f(x-h) )/(h*h);
    }
    return value;
}