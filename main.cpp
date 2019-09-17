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
    PL* original = new PL(numRestrictions, numVariables,entrada, 0) ;//Ja retorna na forma de Tableau
    original->printMatrix();
    int needsAuxiliar = original->bNegative(); 
    /*
    if(needsAuxiliar){

    }
    */ //Vou implementar a logica do caso com auxiliar depois, primeiro conseguir casos em que o A ja tem a base
    
    int pivotColumn = original->findPivotColumn(); //Se retornar -1 eh pq a PL ja ta otima 
    std::cout <<pivotColumn << std::endl; ;
    if(pivotColumn == -1) std::cout << "A PL já esta em estado otimo" << std::endl ; 
    
    int pivotRow = original->findPivotRow(pivotColumn); //Se retornar -1 é pq a PL é ilimitada
    std::cout <<pivotRow  << std::endl; 
    if(pivotRow == -1) std::cout << "A PL é ilimitada" << std::endl ;
    
    original->pivoting(pivotRow, pivotColumn) ;
    original->printMatrix();
    





    
    

} 