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
        string handleImplicitConcatinationFromLeft (string instruction);
        string handleImplicitConcatinationFromRight (string instruction);

         string dealWithInsideConcatenation(string instruction);


        public:
        string getInstructionWithoutExpressions(string instruction);
        string getReadyInstruction(string instruction,vector<Matlab>& savedMatrices);
        Matlab executeInstruction(string instruction,vector<Matlab>& savedMatrices);
        void trimAllSpaces(string &s);
        void trimAllSpacesExceptMatrix(string &s);
        string dealWithBrackets(string complexString);

 int   findTheClosingBracketFromAspecificPostion(string s, int PositonOfOpenBracket,char q ) ;



        //bool checkIfSpecialMatrix(string instruction);




        public:







    void dealWithConcatenationHelperFn(string &instruction,string s);

    string  dealWithAddAndSubOperators(string instruction, string operator_);




    int findTheClosingBracket(string s,char openingBracket,int start=0);
    int findTheOpeningBracket(string s, char openingBracket,int start);
    string dealWithConcatenation(string instruction);





    string dealwithOperators(string instruction);
    string dealwithSpecialFunctions(string instruction);
    string dealwithSpecialFunctionsHelperFunction(string instruction,string specialFunction);
    string findTheMatrix(string instruction,bool openingBracket,int pos);
    string getStringMatrix(string complexString);
    int checkInstructionForFunctions(string instruction);

    enum {};
    bool checkStringForMatrix(string complexString);








    virtual ~Matlab();


    string calcSimpleExpression(string s);


        string extractStringInsideFunction(string instruction);
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

        string getInstructionWithoutFunctions(string instruction);
        bool checkSignsForMatrixOperations(string s,int pos);



        string solvetrignometry(string s) ;

        string getStringValue(string complexString);
        string solvingBrackets(string s);
        string findTheSignOperators(string s,int pos);
        bool skipNegativeSign(string s,int pos);
        string correctSigns(string s);

protected:



};

#endif // MATLAB_H

