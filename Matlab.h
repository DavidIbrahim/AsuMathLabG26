
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

        string getInstructionWithoutSpecialMatrices(string instruction);

        bool checkStringForMatrix(string complexString);
        string getStringMatrix(string complexString);
        string getInstructionWithoutExpressions(string instruction);
        string getReadyInstruction(string instruction,vector<Matlab>& savedMatrices);
        void trimAllSpaces(string &s);
        string dealWithBrackets(string complexString);
        int findTheClosingBracket(string s,char openingBracket);
    public:
        enum{};
        Matlab();
        Matlab(const Matlab& x);
        //static Matlab getMatlabFromVector(string name, vector<Matlab> & matlabObjects)
        Matlab(string name ,const CMatrix &matrix);
        Matlab(string instruction,vector<Matlab>& myVector);
        CMatrix getMatrix(){return matrix;}
        string getName(){return name;}
        string getString();
         string getInstructionWithoutConcatenation(string instruction);
         string getInstructionWithoutMatlabNames(string instruction,vector<Matlab>& savedMatrices);
        virtual ~Matlab();
        string solvetrignometry(string s) ;
        string calcSimpleExpression(string s);
       string getStringValue(string complexString);

      
    protected:


};

#endif // MATLAB_H

