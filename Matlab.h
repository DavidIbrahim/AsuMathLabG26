#ifndef MATLAB_H
#define MATLAB_H
#include"CMatrix.h"
#include<vector>


class Matlab
{
    private:
        CMatrix matrix;
        string name;

        bool checkIfSpecialMatrix(string instruction);
        string getStringValue(string complexString,vector<Matlab> savedMatrices); //this fn should take an expression and return it's value as a string
        string getReadyInstruction(string instruction,vector<Matlab> savedMatrices); //this fn takes the instruction as it is and returns it back without any expressions(the simplest input form)
    public:
        Matlab();
        Matlab(string instruction,vector<Matlab>& myVector);
        virtual ~Matlab();

    protected:


};

#endif // MATLAB_H
