#include "Matlab.h"

/** @brief replace a substring in a string with another one .
 *
 * @param mainString the string that will be changed;
 * @param replacedString ... this is a string which should be a substring of the mainString and that will be replaced
 *@param replacingString ... this is the string that will be a substring of the mainString
 *@return False if couldn't find the replacedString in the mainString and True otherwise
 */

bool replaceString(string& mainString , string& replacedString , string& replacingString){

    size_t start_pos = mainString.find(replacedString);
    if(start_pos == std::string::npos)
        return false;
    mainString.replace(start_pos, replacedString.length(), replacingString);
    return true;

}

/** @brief remove any matlab names and replace them by their matrices
 *
 * @param instruction the input instruction from the user ex: A=[B,[1.2 2.3]]; where B=[2.0 3.0];
 * @param savedMatrices to look for the matlab name in the vector and find it's matrix
 * @return the instruction as a string but with matrix instead of matlab names ex: A=[[2.0 3.0],[1.2 2.3]];
 */

string Matlab::getInstructionWithoutMatlabNames(string instruction,vector<Matlab>& savedMatrices)
{

}
/** @brief remove any specialMatrix in the input string and replace it with it's string
 * special Matices are rand(r,c),eye(r,c),zeros(r,c) and ones(r,c).
 * @param instruction the input instruction from the user ex: A=[rand(2,2),[1.2;3.0]];
 * @return the instruction as a string but without special Matrices ex: A=[[1.0 2.0;3.5 6.0],[1.2;3.0]];
 *
 */
string Matlab::getInstructionWithoutSpecialMatrices(string instruction)
{

}
/** @brief search the whole instruction and remove the concatenation from it then returns it back
 *
 * @param instruction it is the instruction without any matlab names or special matrix ex: A=[[1.2 3.2],[2.2];[2.0 2.0 2.0]]; or A=[[1.2 3.2] [2.2] "\n"[2.0 2.0 2.0] ];
 * @return the instruction as a string without any concatenation ex: A=[1.2 3.2 2.2;2.0 2.0 2.0];
 * note: horizontal concatenation occurs when there is space or ','
 * note: vertical concatenation occurs when there is ';' or a new line
 * note: this function throws a syntax error message
 * hint: there is a horizontalConcatenation and verticalConcatenation fns in Cmatrix so you can convert the string to matrix then send it to it.
 */

string Matlab::getInstructionWithoutConcatenation(string instruction)
{

    CMatrix primary;
    size_t Begin,End;
    size_t start=0;
    Begin =instruction.find("[",start);// first occurence of "[".
    End =instruction.find("]",start+1);//first occurence of "]"
    string s=instruction.substr(Begin,(End+1)-Begin);// string between "[ ]"
    primary=(s);
    start=End;// new starting point to search from the end of first matrix.
    Begin =instruction.find("[",start);
    if(Begin==std::string::npos)//to check if its only one matrix.
           return s;
    else
    {
        End =instruction.find("]",start+1);
        s=instruction.substr(Begin,(End+1)-Begin);
        CMatrix secondary(s);
        string s1=instruction.substr((start+1),(Begin-(start+1)));// the substring between the two matrices that determines the type of concatination between them.
            for(unsigned int i=0;i<s1.length();i++)// to check for syntax errors between matrices.
            {
                if ((s1[i])!=(' ')&&(s1[i])!=(',')&&(s1[i])!=(';')&&(s1[i])!=('\n')&&(s1.find("\r\n"))==std::string::npos)
                 {throw ("Syntax error");}
            }
        if ((s1.find(";"))!=std::string::npos||(s1.find("\r\n"))!=std::string::npos||(s1.find("\n"))!=std::string::npos)//to check if its horizontal or vertical conc.
        {primary=secondary.verticalConcatenation(primary,secondary);}
        else if((s1.find(","))!=std::string::npos||(s1.find(" "))!=std::string::npos)
            {primary=secondary.horizontalConcatenation(primary,secondary);}
        else
            {throw ("Syntax error");}//this condition checks if there's no spaces between matrices at all ([][]).
        start=End;
        instruction=(primary.getString2())+instruction.substr(start+1);
        return getInstructionWithoutConcatenation(instruction);
    }

}
/** @brief check if there are matrices in this string
 *
 * @param complexString the string to be checked
 * @return 0 if there is no matrices and 1 if there is matrices
 * hint: check for [] only
 */

bool Matlab::checkStringForMatrix(string complexString)
{

}
/** @brief simplify the expression to the final string value
 *
 * @param complexString it is a string of 1D expression, contains no matrices ex: 1+2/5*sin(2)
 * @return the final value of the expression as a string ex: 1.3637
 *
 */

string Matlab::getStringValue(string complexString)
{

}
/** @brief simplify the expression to the final matrix string
 *
 * @param complexString it is a string of matrix operations without any matlab names or special matrix ex: 1.2+[1.0 2.0]*2+sin([3.3 2.2])
 * @return the resultant matrix as a string ex: [3.0423 6.0085]
 * search for all operations including dot operations
 */

string Matlab::getStringMatrix(string complexString)
{

}
/** @brief this fn replace any expression in the instruction by it's equivalent value or matrix
 *
 * @param instruction the full instruction but without Matlab names or special matrix ex: A=[6+2 2+[1 2 3]];
 * @return the instruction without any expressions ex: A=[8 [3 4 5]];
 *
 */

string Matlab::getInstructionWithoutExpressions(string instruction)
{
    istringstream is;
    is.str(instruction);
    char c; //to loop each character in the instruction
    string s;
    string temp; //stores the equivalent value or matrix of the string
    while(is.get(c))
    {
        if(c!='['&&c!=']'&&c!=','&&c!=';'&&c!=' ')
        {
            s+=string(1,c);
        }
        else
        {
            if(checkStringForMatrix(s))//the string contains a matrix
            {
                temp=getStringMatrix(s);
                replaceString(instruction,s,temp);
            }
            else //the string contains no matrix
            {
                temp=getStringValue(s);
                replaceString(instruction,s,temp);
            }
            s="";
            temp="";
        }
    }
    return instruction;
}
/**
* this fn takes the full instruction as it is ex: B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]];
* and returns it ready for cmatrix constructor ex: B= [1.2 2.3 3.0;1.3 2.4 3.2; 4.6 1.3 7.8];
* without any Matlab names in between, concatenations or expressions.
* @param instruction the instruction taken from the user
* @param savedMatrices the vector where all Matlab objects are stored
  @return a simple instruction without any Matlab names in between, concatenations or expressions.
*/
string Matlab::getReadyInstruction(string instruction,vector<Matlab>& savedMatrices)
{
    instruction=getInstructionWithoutMatlabNames(instruction,savedMatrices);
    instruction=getInstructionWithoutSpecialMatrices(instruction);
    instruction=getInstructionWithoutExpressions(instruction);
    instruction=getInstructionWithoutConcatenation(instruction);
    return instruction;
}

Matlab::Matlab(){


}
Matlab::Matlab(const Matlab& x){
    *this = x;

}
/**
*   @brief this constructor used only for debugging ....
*/
Matlab::Matlab(string name,const CMatrix &matrix){
    this->name = name;
    this->matrix = matrix;

}

Matlab::Matlab(string instruction, vector<Matlab>& myVector)
{


}


Matlab::~Matlab()
{
    //dtor
}
/*
*   returns true if the instruction contains "zeros("
*    or "rand(" or "eye(" or "ones("
*
*/
/*
bool Matlab::checkIfSpecialMatrix(string instruction){


    return false;
}*/
/**
* @return  the string representation of the matlab object ...
*           eg A = [ 1 2 ; 3 4]      where A is the name of matrix
*/

string Matlab::getString(){

    return name+" = "+matrix.getString2();
}
