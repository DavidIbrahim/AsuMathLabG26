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


        string getStringMatrix(string complexString);
        public:
        string getInstructionWithoutExpressions(string instruction);
        string getReadyInstruction(string instruction,vector<Matlab>& savedMatrices);
        void trimAllSpaces(string &s);
        string dealWithBrackets(string complexString);
        int findTheClosingBracket(string s,char openingBracket,int pos=0);
    public:
        int checkInstructionForFunctions(string instruction);
        string extractStringInsideFunction(string instruction);
        enum{};
        bool checkStringForMatrix(string complexString);
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

        string getInstructionWithoutFunctions(string instruction);
        bool checkSignsForMatrixOperations(string s,int pos);


        virtual ~Matlab();

        string solvetrignometry(string s) ;
        string calcSimpleExpression(string s);
        string getStringValue(string complexString);
        string solvingBrackets(string s);
        string findTheSignOperators(string s,int pos);

    protected:


};

#endif // MATLAB_H

