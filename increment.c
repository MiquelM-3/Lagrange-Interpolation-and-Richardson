#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "increment.h"
#include "f.h"
/*
    AUTOR: Miquel Martínez Gavagnin
    Exercici: 2

*/
double increment(double p, double q, double y,double z){
    double value=0;

    value = (z-y)/ (pow(q,p)-1); /*Utilitzem el pou aqui perque ens passen p i q obligatoriament, però es poc eficient aixo*/

    return value;
}