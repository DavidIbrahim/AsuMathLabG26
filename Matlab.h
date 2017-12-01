#ifndef MATLAB_H
#define MATLAB_H
#include"CMatrix.h"
#include<vector>

///The object of this class consists of the matrix and it's name
class Matlab
{
    private:
        CMatrix matrix;
        string name;

        //bool checkIfSpecialMatrix(string instruction);
        string getInstructionWithoutMatlabNames(string instruction,vector<Matlab> savedMatrices);
        string getInstructionWithoutSpecialMatrices(string instruction);

        bool checkStringForMatrix(string complexString);
        string getStringMatrix(string complexString);
        string getReadyInstruction(string instruction,vector<Matlab> savedMatrices);
        void trimAllSpaces(string &s);
        string dealWithBrackets(string complexString);
        int findTheClosingBracket(string s,char openingBracket);
    public:
        string calcSimpleExpression(string s);
        Matlab();
        Matlab(const Matlab& x);
        Matlab(string name ,const CMatrix &matrix);
        Matlab(string instruction,vector<Matlab>& myVector);
        string getStringValue(string complexString);

        string getString();
        string getInstructionWithoutConcatenation(string instruction);
        virtual ~Matlab();

    protected:


};

#endif // MATLAB_H
