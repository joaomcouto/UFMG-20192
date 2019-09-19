#include <stdio.h>
#include <stdlib.h>

class PL{
    private:
    public:
        int _numVariables ;
        int _numRestrictions ;
        int _numRows ;
        int _numColumns ;
        double ** _matrix ;
        double * vero ; 
        PL(int numRestrictions, int numVariables,FILE * entrada, bool auxiliar);
        ~PL();
        void printMatrix();
        int bNegative();
        int findPivotColumn();
        int findPivotRow(int pivotColumn);
        void pivoting(int row, int col);
        void printVero();
        void printSolutionValue();
        void printSolution();
        void boundlessCertificate();

    };
    
    