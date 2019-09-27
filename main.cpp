#include <stdio.h>
#include <stdlib.h>
#include "pl.h"
#include <iostream>


int main (int argc, char const *argv[]){

    FILE* entrada; 
    int numRestrictions, numVariables ;
    entrada = fopen(argv[1],"r");
    fscanf(entrada,"%d %d", &numRestrictions, &numVariables) ;
    PL* original = new PL(numRestrictions, numVariables,entrada, 0) ;//Ja retorna na forma de Tablea

    rewind (entrada); 
    fscanf(entrada,"%d %d", &numRestrictions, &numVariables) ;
    int needsAuxiliar = original->bNegative();
    if(needsAuxiliar){
        PL* auxiliar = new PL(numRestrictions, numVariables,entrada, 1) ;
        while(1){
            int pivotColumn = auxiliar->findPivotColumn(); //Se retornar -1 eh pq a PL ja ta otima 
            if(pivotColumn == -1){
                if(auxiliar->fetchSolutionValue() < 0) {
                    std::cout << "inviavel" << std::endl; 
                    auxiliar->printVero();
                    return 0;
                } 
                break ;
            } 
            int pivotRow = auxiliar->findPivotRow(pivotColumn); //Se retornar -1 é pq a PL é ilimitada
            if(pivotRow == -1){
                std::cout << "De alguma forma a auxiliar deu ilimitada, acredito que isso não é um possibilidade" << std::endl ;  
                break ;
            } 

            auxiliar->pivoting(pivotRow, pivotColumn) ;

        }

        original->copyAuxiliar(auxiliar) ;
    } 
    while(1){
    
    int pivotColumn = original->findPivotColumn(); //Se retornar -1 eh pq a PL ja ta otima 
    if(pivotColumn == -1){
        std::cout << "otima" << std::endl;
        original->printSolutionValue();
        original->printSolution();
        original->printVero() ; 
        break ;
    } 
    
    int pivotRow = original->findPivotRow(pivotColumn); //Se retornar -1 é pq a PL é ilimitada
    if(pivotRow == -1){
        std::cout << "ilimitada" << std::endl ;
        original->printSolution();
        original->printBoundlessCertificate(pivotColumn);
        
        break ;
    } 
    
    original->pivoting(pivotRow, pivotColumn) ;

    }
} 