#include <stdio.h>
#include <stdlib.h>
#include "pl.h"
#include <iostream>


int main (int argc, char const *argv[]){

    FILE* entrada; 
    int numRestrictions, numVariables ;
    entrada = fopen(argv[1],"r");
    fscanf(entrada,"%d %d", &numRestrictions, &numVariables) ;
    //std::cout << numRestrictions << " " << numVariables ;
    PL* original = new PL(numRestrictions, numVariables,entrada, 0) ;
    original->printMatrix();
    int needsAuxiliar = original->bNegative();
    /*
    if(needsAuxiliar){

    }
    */ //Vou implementar a logica do caso com auxiliar depois, primeiro conseguir casos em que o A ja tem a base
    pivotRow = original->




    
    

} 