#include "pl.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

PL::PL(int numRestrictions, int numVariables, FILE * entrada, bool auxiliar){
    this->_numVariables = numVariables + numRestrictions ; //Variaveis de decisao + variaveis de folga
    this->_numRestrictions = numRestrictions ; 
    this->_numColumns = numRestrictions + this->_numVariables + 1 ; //VERO + (Variaveis de decisao + variaveis de folga) + b
    this->_numRows = this->_numRestrictions + 1 ;  // Numero de restricoes + c 
    this->_matrix =(double **) malloc(sizeof(double*)*this->_numRows) ;
    int i,j ;
    
    for(i = 0 ; i < this->_numRows ; i++){
        this->_matrix[i] = (double *)malloc(sizeof(double)*this->_numColumns) ;
        for(j = 0 ; j < this->_numColumns ; j++){
            this->_matrix[i][j] = 0 ;
        }
    }
    
    for (i = 1 ; i < this->_numRows ; i++){ //Init vero
        for(j = 0 ; j < this->_numRestrictions ; j++){ 
            if(j == i-1){
                this->_matrix[i][j] = 1 ; 
            }
        }
    }

    for (i = 0 ; i < this->_numRows ; i ++){ //Leitura do c, restricoes e b
        for(j = this->_numRestrictions ; j < this->_numColumns-this->_numRestrictions ; j++ ){
            if(j==this->_numColumns - this->_numRestrictions-1){ //Se j na ultima posicao de leitura(b)
                if(i==0) break; // Pra compensar o fato de que a funcao objetivo nao vem com um valor pro b
                fscanf(entrada,"%lf", &this->_matrix[i][this->_numColumns-1]) ; //Coloca o b na ultima coluna 
                break ;
            }
            fscanf(entrada,"%lf", &this->_matrix[i][j]) ;
        }
    }

    for (i = 1 ; i < this->_numRows ; i++){ //Init variaveis de folga
        for(j = this->_numRestrictions + (this->_numVariables-this->_numRestrictions)-1 ; j < this->_numColumns -1 ; j++){ 
            if(j == (i+this->_numRestrictions + (this->_numVariables - this->_numRestrictions)-1)){
                this->_matrix[i][j] = 1 ; 
            }
        }
    }
    

    for (i = 0 ; i < this->_numColumns ; i++){ //Multiplica primeira linha por -1 pra ficar na forma tableaux
        if(this->_matrix[0][i] != 0){
            this->_matrix[0][i] = -1*this->_matrix[0][i] ;
        }
    }


    //if(auxiliar==0){
        

    //}
    
}
    
PL::~PL(){

}

void PL::printMatrix(){
    int i,j;
    for(i = 0 ; i < this->_numRows ; i++){
        for(j = 0 ; j < this->_numColumns ; j++){
            std::cout << std::setw(3) << this->_matrix[i][j] << "  " ;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int PL::bNegative(){
    int i ;
    for(i = 0 ; i < this->_numRows ; i++){
        if(this->_matrix[i][this->_numColumns-1] < 0) return 1;
    }
    return 0 ;
}

int PL::findPivotColumn(){
    int i;
    int pivotCol ;
    pivotCol = this->_numRestrictions ;
    double lowestC = this->_matrix[0][pivotCol] ;
    for(i=this->_numRestrictions+1; i < this->_numColumns-1 ; i++){
        if(this->_matrix[0][i] < this->_matrix[0][pivotCol]){
            pivotCol = i ;
            lowestC = this->_matrix[0][i] ;
        }
    }
    if (lowestC >= 0) return -1 ; //ja eh otimo
    return pivotCol;
}

int PL::findPivotRow(int pivotColumn){
    int i;
    int pivotRow = -1 ;
    int allNegative ;
    double smallestRatio ;
    for(i = 1 ; i < this->_numRows ;i++){ //verificacao de que temos pelo menos um positivo
        if(this->_matrix[i][pivotColumn] > 0){
            pivotRow = i ;
            smallestRatio = this->_matrix[i][this->_numColumns-1]/this->_matrix[i][pivotColumn] ; 
        }
    }
    if(pivotRow== -1) return -1 ; //Sao todos negativos ou zero
    for (i = 1 ; i < this->_numRows ; i++){
        if((this->_matrix[i][this->_numColumns-1]/this->_matrix[i][pivotColumn] < smallestRatio) && (this->_matrix[i][pivotColumn] > 0)){
            smallestRatio = this->_matrix[i][this->_numColumns-1]/this->_matrix[i][pivotColumn] ;
            pivotRow = i ;
        }
    } 
    return pivotRow ;
} 

void PL::pivoting(int row, int col){
    int i ,j;
    for(i = 0 ; i < this->_numColumns ; i++){
        this->_matrix[row][i] = this->_matrix[row][i]/this->_matrix[row][col] ;
    }
    int multiplier ;
    for(i = 0 ; i < this->_numRows ; i++){
        if(i != row){
            multiplier = this->_matrix[i][col] ;
            for(j = 0 ; j < this->_numColumns ; j ++){
                this->_matrix[i][j] = this->_matrix[i][j] - multiplier*this->_matrix[row][j] ;
            }
        }
    }
} 

void PL::printVero(){
    int i ;
    for(i = 0 ; i < this->_numRestrictions ; i++){
        std::cout<< this->_matrix[0][i] << " " ;
    }
}

void PL::printSolutionValue(){
    std::cout<< this->_matrix[0][_numColumns -1] << std::endl ;
}

void PL::printSolution(){
    bool isBase = 1 ; 
    int position = -1 ;
    int i ,j ;
    for(i = this->_numRestrictions ; i < (this->_numRestrictions+this->_numVariables-this->_numRestrictions); i++){
        isBase = 1 ;
        position = -1 ; 
        for(j = 1 ;j < this->_numRows ; j++ ){
            if((this->_matrix[j][i] == 1) && (position == -1) && (isBase ==1)){
                position = j ;
            } else {
                if(this->_matrix[j][i] != 0){
                    isBase = 0 ;
                }
            }
            
        }
        if(isBase==1){
            std::cout << this->_matrix[position][this->_numColumns-1] << " ";
        } else {
            std::cout << 0 << " ";
        }
    }
    std::cout << std::endl; 
}

void PL::boundlessCertificate(){

}