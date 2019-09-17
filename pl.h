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
        PL(int numRestrictions, int numVariables,FILE * entrada, bool auxiliar);
        ~PL();
        void printMatrix();
        int bNegative();
        int findPivotColumn();
        int findPivotRow(int pivotColumn);
        

    };
    
    