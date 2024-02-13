#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/
double f(double x){

    if(x<0){
        return -(x*x*x);
    }
    else if (x>0)
    {
        return (x*x*x); 
    }
    else{
        return 0; /*en el 0 no està definida1*/
    }
}