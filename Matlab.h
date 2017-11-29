#ifndef MATLAB_H
#define MATLAB_H
#include"CMatrix.h"
#include<vector>
#include<sstream>

///The object of this class consists of the matrix and it's name
class Matlab
{
    private:
        CMatrix matrix;
        string name;

        //bool checkIfSpecialMatrix(string instruction);
        string getInstructionWithoutMatlabNames(string instruction,vector<Matlab>& savedMatrices);
        string getInstructionWithoutSpecialMatrices(string instruction);
        string getInstructionWithoutConcatenation(string instruction);
        bool checkStringForMatrix(string complexString);
        string getStringValue(string complexString);
        string getStringMatrix(string complexString);
        string getInstructionWithoutExpressions(string instruction);
        string getReadyInstruction(string instruction,vector<Matlab>& savedMatrices);
    public:
        Matlab();
        Matlab(string instruction,vector<Matlab>& myVector);
        virtual ~Matlab();

    protected:


};

#endif // MATLAB_H
