#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"
#include<string>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
#include<sstream>
#include<math.h>
#include <iomanip>
#include <limits>


/**
 *  @brief: it reverses the string
 *
 *  @brief helper method for getStringValue
 *
 *  @return: it takes the string by refrence so return is void
 */





void reverse(string & s)
{
    char temp;
    for (int  i = 0, j = s.length()-1 ; i < s.length()/2; i++, j--)
    {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}


/** @brief: it trims all the spaces of a given string .
 *
 *  @brief helper method for getStringValue
 *
 *  @return: it takes the string by refrence so return is void
 */




void Matlab:: trimAllSpaces(string & s)
{
    //	s.erase(s.begin(),std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));//l. only
    //	s.erase( std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),  s.end());//r. only
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            s.erase( i,1 );
            i--;
        }

    }
}

/** @brief replace a substring in a  string with another substring .
 *
 * @param mainString the string that will be changed;
 * @param replacedString ... this is a string which should be a substring of the mainString and that will be replaced
 *@param replacingString ... this is the string that will be a substring of the mainString
 *@param int from  ... if u want to replace the string which found from a specific index i.e for not first concurrence
 *        by default it is set to 0 i.e it will replace the first concurrence of the substring
 *@return False if couldn't find the replacedString in the mainString and True otherwise
 */

bool replaceString(string& mainString, string replacedString, string replacingString,int from = 0)
{

    size_t start_pos = mainString.find(replacedString,from);
    if(start_pos == std::string::npos)
        return false;
    mainString.replace(start_pos, replacedString.length(), replacingString);
    return true;

}
string doubleToString(double d)//convert double to string
{
    ostringstream os;
    os<<d;
    string s(os.str());
    if(!(d-floor(d)))
        s+=".0";
    //return string(c);
    return s;
}
double stringToDouble(string s)
{
    double d;
    istringstream is(s);
    is>>d;
    return d;
}
//check that the bracket at position pos in the string s is for a special function
//returns 1 if it is for a special function

bool checkTheBracketOfSpecialFn(string s,int pos)
{
    if(s[pos]!='(')
        throw("it is not a '('");
    if(pos==0)
        return 0;
    if(s[pos-1]=='+'||s[pos-1]=='-'||s[pos-1]=='*'||s[pos-1]=='/'||s[pos-1]=='^'||s[pos-1]=='%'||s[pos-1]==' '||s[pos-1]==';'||s[pos-1]==','||s[pos-1]=='\n')
        return 0;
    return 1;
}
/*
//this fn searches for * or / in string s from a certain pos and returns the position of the first one found
int searchForMulDiv(string s,int pos)
{
    for(int i=pos;i<s.length();i++)
    {
        if(s[i]=='*'||s[i]=='/')
            return i;
    }
}
*/
//this function checks the sign(+ - * / ^ ) of position pos in the string s is a matrix operation
//returns 1 if it is a matrix operation or operation with special matrix
//we should deal with brackets before this function
bool Matlab::checkSignsForMatrixOperations(string s,int pos)
{
    if(s[pos-1]==']'||s[pos-1]=='.'||s[pos+1]=='['||s[pos-1]==')'||s[pos+1]=='s'||s[pos+1]=='c'||s[pos+1]=='a'||s[pos+1]=='e'||s[pos+1]=='l'||s[pos+1]=='f'||s[pos+1]=='p')
        return 1;
    else
    {
        if(s[pos]=='+'||s[pos]=='-')
        {
            string temp;
            for(int i=pos+1; i<s.length(); i++)
            {
                if(s[i]!='+'&&s[i]!='-'&&s[i]!=' '&&s[i]!=']'&&s[i]!=')'&&s[i]!=';')
                    temp+=s[i];
                else
                    break;
            }
            if(checkStringForMatrix(temp)||checkInstructionForFunctions(temp))
                return 1;
            temp="";
            for(int i=pos-1; i>=0; i--)
            {
                if(s[i]!='+'&&s[i]!='-'&&s[i]!=' '&&s[i]!='['&&s[i]!='('&&s[i]!=';')
                    temp+=s[i];
                else
                    break;
            }
            if(checkStringForMatrix(temp)||checkInstructionForFunctions(temp))
                return 1;
            return 0;
        }
        else
            return 0;
    }
}
/*
Matlab getMatlab(string name,vector<Matlab> & savedMatrices){

     for(int i =0; i<savedMatrices.size(); i++) {
       if(savedMatrices[i].getName()==name)
        return savedMatrices[i];
    }


 }*/




/** @brief remove any matlab names and replace them by their matrices
 *
 * @param instruction the input instruction from the user ex: A=[B,[1.2 2.3]]; where B=[2.0 3.0];
 * @param savedMatrices to look for the matlab name in the vector and find it's matrix
 * @return the instruction as a string but with matrix instead of matlab names ex: A=[[2.0 3.0],[1.2 2.3]];
 */

string Matlab::getInstructionWithoutMatlabNames(string instruction,vector<Matlab>& savedMatrices)
{
    string notMatlabNames = "0123456789 ,;[]";
    string notVariableNames =" ;[],()+-%^*/.";
    for(int i =0; i<savedMatrices.size(); i++)
    {
        int position = 1;
        while(true)
        {

            string currentName = savedMatrices[i].name;
            position = instruction.find(currentName,position);
            if(position != std::string::npos)
            {
                char afterVariableName = instruction[position+currentName.length()];
                char beforeVariableName = instruction[position-1];
                if((notVariableNames.find(afterVariableName)!=string::npos
                        || afterVariableName =='\0')&&  // ea3ny law el 7rf el abl wa b3d el name
                        notVariableNames.find(beforeVariableName)!=string::npos)   // tl3o 7aga msh bt3'erle fe asm el variable
                {
                    //eb2a dh aked hwa el variable el mtsgl 3ndy fe
                    //current name ... 3lshan mmkn ekon currentName = s
                    replaceString(instruction,currentName,savedMatrices[i].matrix.getString2(),position)   ;
                    //wa ala2e el s dh gwa sin() bs dh msh variable bta3y
                }
                position++;
            }
            else
            {
                break;
            }

        }
    }


    return instruction;


}
/** @brief remove any specialMatrix in the input string and replace it with it's string
 * special Matices are rand(r,c),eye(r,c),zeros(r,c) and ones(r,c).
 * @param instruction the input instruction from the user ex: A=[rand(2,2),[1.2;3.0]];
 * @return the instruction as a string but without special Matrices ex: A=[[1.0 2.0;3.5 6.0],[1.2;3.0]];
 *
 */
string Matlab::getInstructionWithoutSpecialMatrices(string instruction)
{
    string eye="eye";
    size_t found_eye= instruction.find(eye);
    while (found_eye!=std::string::npos)
    {
        string Srows,Scolumns ;
        size_t rowBegin = instruction.find("(",found_eye+1);
        size_t rowEnd =instruction.find(",",rowBegin);
        size_t columnEnd=instruction.find(")",rowEnd);
        Srows=instruction.substr(rowBegin+1,rowEnd-(rowBegin+1));
        Scolumns=instruction.substr(rowEnd+1,columnEnd-(rowEnd+1));
        int nrows = atoi (Srows.c_str());
        int ncolumns = atoi (Scolumns.c_str());
        CMatrix eye_matrix (nrows,ncolumns,CMatrix::MI_EYE);
        size_t length_eye=(columnEnd-found_eye+1);//length of eye matrix in the original string .
        instruction.replace(found_eye,length_eye,eye_matrix.getString2());
        found_eye=instruction.find("eye",found_eye+1);
    }
    string rand="rand";
    size_t found_rand= instruction.find(rand);
    while (found_rand!=std::string::npos)
    {
        string Srows,Scolumns ;
        size_t rowBegin = instruction.find("(",found_rand+1);
        size_t rowEnd =instruction.find(",",rowBegin);
        size_t columnEnd=instruction.find(")",rowEnd);
        Srows=instruction.substr(rowBegin+1,rowEnd-(rowBegin+1));
        Scolumns=instruction.substr(rowEnd+1,columnEnd-(rowEnd+1));
        int nrows = atoi (Srows.c_str());
        int ncolumns = atoi (Scolumns.c_str());
        CMatrix rand_matrix (nrows,ncolumns,CMatrix::MI_RAND);
        size_t length_rand=(columnEnd-found_rand+1);//length of rand matrix in the original string .
        instruction.replace(found_rand,length_rand,rand_matrix.getString2());
        found_rand=instruction.find("rand",found_rand+1);
    }
    string ones="ones";
    size_t found_ones= instruction.find(ones);
    while (found_ones!=std::string::npos)
    {
        string Srows,Scolumns ;
        size_t rowBegin = instruction.find("(",found_ones+1);
        size_t rowEnd =instruction.find(",",rowBegin);
        size_t columnEnd=instruction.find(")",rowEnd);
        Srows=instruction.substr(rowBegin+1,rowEnd-(rowBegin+1));
        Scolumns=instruction.substr(rowEnd+1,columnEnd-(rowEnd+1));
        int nrows = atoi (Srows.c_str());
        int ncolumns = atoi (Scolumns.c_str());
        CMatrix ones_matrix (nrows,ncolumns,CMatrix::MI_ONES);
        size_t length_ones=(columnEnd-found_ones+1);//length of eye matrix in the original string .
        instruction.replace(found_ones,length_ones,ones_matrix.getString2());
        found_ones=instruction.find("ones",found_ones+1);
    }
    string zeros="zeros";
    size_t found_zeros= instruction.find(zeros);
    while (found_zeros!=std::string::npos)
    {
        string Srows,Scolumns ;
        size_t rowBegin = instruction.find("(",found_zeros+1);
        size_t rowEnd =instruction.find(",",rowBegin);
        size_t columnEnd=instruction.find(")",rowEnd);
        Srows=instruction.substr(rowBegin+1,rowEnd-(rowBegin+1));
        Scolumns=instruction.substr(rowEnd+1,columnEnd-(rowEnd+1));
        int nrows = atoi (Srows.c_str());
        int ncolumns = atoi (Scolumns.c_str());
        CMatrix zeros_matrix (nrows,ncolumns,CMatrix::MI_ZEROS);
        size_t length_zeros=(columnEnd-found_zeros+1);//length of eye matrix in the original string .
        instruction.replace(found_zeros,length_zeros,zeros_matrix.getString2());
        found_zeros=instruction.find("zeros",found_zeros+1);
    }
    return instruction;
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
    End =findTheClosingBracket(instruction,'[');//first occurence of "]"
    string s=instruction.substr(Begin,(End+1)-Begin);// string between "[ ]"

    start=End;// new starting point to search from the end of first matrix.
    Begin =instruction.find("[",start);
    if(Begin==std::string::npos)//to check if its only one matrix.
        return s;
    else
    {
        primary=(s);
        End =instruction.find("]",start+1);
        s=instruction.substr(Begin,(End+1)-Begin);
        CMatrix secondary(s);
        string s1=instruction.substr((start+1),(Begin-(start+1)));// the substring between the two matrices that determines the type of concatination between them.
        for(unsigned int i=0; i<s1.length(); i++) // to check for syntax errors between matrices.
        {
            if ((s1[i])!=(' ')&&(s1[i])!=(',')&&(s1[i])!=(';')&&(s1[i])!=('\n')&&(s1.find("\r\n"))==std::string::npos)
            {
                throw ("Syntax error");
            }
        }
        if ((s1.find(";"))!=std::string::npos||(s1.find("\r\n"))!=std::string::npos||(s1.find("\n"))!=std::string::npos)//to check if its horizontal or vertical conc.
        {
            primary=secondary.verticalConcatenation(primary,secondary);
        }
        else if((s1.find(","))!=std::string::npos||(s1.find(" "))!=std::string::npos)
        {
            primary=secondary.horizontalConcatenation(primary,secondary);
        }
//        else
//        {
//            throw ("Syntax error");   //this condition checks if there's no spaces between matrices at all ([][]).
//        }
        start=End;
        instruction=(primary.getString2())+instruction.substr(start+1);
        return getInstructionWithoutConcatenation(instruction);
    }

}
/** @brief check if there are matrices in this string
 *
 * @param complexString the s[[2.0 4.0];[4.0 4.0]]tring to be checked
 * @return 0 if there is no matrices and 1 if there is matrices
 * hint: check for [] only
 */

bool Matlab::checkStringForMatrix(string complexString)
{
    int position=-1 ;
    //position can never return with a negative sign
    position = complexString.find("[");
    int position2=-1;
    position2=complexString.find("]");
    //getting the position of [ which indicates a matrix is in that string
    if(position>=0||position2>=0)
        return 1;
    return 0;



}


/** @brief this fn replace any expression(in a single element) in the instruction by it's equivalent value
 *
 * @param instruction the full instruction but without Matlab names or special matrix ex: A=[6.0+2.0 2.0+[1.0 2.0 3.0] sin([2.0 3.0+3.0])];
 * @return the instruction without any expressions ex: A=[8.0 2.0+[1.0 2.0 3.0] sin([2.0 6.0])];
 * Hint: extract every single element and call getStringValue() function
 */

string Matlab::getInstructionWithoutExpressions(string instruction)
{
    string simplifiedInstruction;
    string signOperators;
    string equivalentValue;
    simplifiedInstruction=solvingBrackets(instruction);
    //dealing with powers first
    for(int i=simplifiedInstruction.length()-1; i>=0; i--)
    {
        if(simplifiedInstruction[i]=='^'&&!checkSignsForMatrixOperations(simplifiedInstruction,i))
        {
            signOperators=findTheSignOperators(simplifiedInstruction,i);
            equivalentValue=getStringValue(signOperators);
            replaceString(simplifiedInstruction,signOperators,equivalentValue);
        }
    }
    //dealing with * & /
    for(int i=0; i<simplifiedInstruction.length(); i++)
    {
        if((simplifiedInstruction[i]=='*'||simplifiedInstruction[i]=='/')&&!checkSignsForMatrixOperations(simplifiedInstruction,i))
        {
            signOperators=findTheSignOperators(simplifiedInstruction,i);
            equivalentValue=getStringValue(signOperators);
            replaceString(simplifiedInstruction,signOperators,equivalentValue);
        }
    }
    //dealing with + & -
    for(int i=0; i<simplifiedInstruction.length(); i++)
    {
        if((simplifiedInstruction[i]=='+'||simplifiedInstruction[i]=='-')&&!checkSignsForMatrixOperations(simplifiedInstruction,i))
        {
            signOperators=findTheSignOperators(simplifiedInstruction,i);
            // cout<<signOperators<<endl;
            equivalentValue=getStringValue(signOperators);
            //cout<<equivalentValue<<endl;
            replaceString(simplifiedInstruction,signOperators,equivalentValue);
        }
    }
    return simplifiedInstruction;
    /* this code is incorrect
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
    */
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
   // cout<<instruction<<endl;
    instruction=getInstructionWithoutMatlabNames(instruction,savedMatrices);
    //cout<<instruction<<endl;
    instruction=getInstructionWithoutSpecialMatrices(instruction);
    //cout<<instruction<<endl;
    instruction=getInstructionWithoutExpressions(instruction);
    //cout<<instruction<<endl;
    instruction=getInstructionWithoutFunctions(instruction);
    //cout<<instruction<<endl;
    //after removing functions we need another simplification
    instruction=getInstructionWithoutExpressions(instruction);
    //cout<<instruction<<endl;
    instruction=getStringMatrix(instruction);
    //cout<<instruction<<endl;
    return instruction;
}

Matlab::Matlab()
{


}
Matlab::Matlab(const Matlab& x)
{
    *this = x;

}
/**
*   @brief this constructor used only for debugging ....
*/
Matlab::Matlab(string name,const CMatrix &matrix)
{
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

string Matlab::getString()
{

    return name+" = "+matrix.getString2();
}

/** @brief simplify the expression to the final string value
*
* @param complexString it is a string of 1D expression, contains no matrices ex: 1+2/5*sin(2)
* @return the final value of the expression as a string ex: 1.3637
*
*/


string Matlab::getStringValue(string complexString)
{


    trimAllSpaces(complexString);
    //make sure all operations are in the form expected
    //transform(s.begin(), s.end(), s.begin(), ::tolower);


    // uncomment this to call the values of any sin or cos
    complexString = solvetrignometry (   complexString);//


    complexString=dealWithBrackets(complexString);

    complexString = calcSimpleExpression(complexString);
    return complexString;
}

/**
*
* @brief helper method for getStringValue
* @brief it extracts what is inside the () and deals with the fact that their can be brackets inside a bracket
*
*/

string Matlab:: dealWithBrackets(string inputString)
{

    int poss = inputString.find('(');

    if (poss != string::npos)        //only enter if there's "(" else return input string
    {
        int pos2 = findTheClosingBracket(inputString,'(');

        string stringInsideTheBrackets = inputString.substr(poss + 1, pos2-poss-1);

        if(stringInsideTheBrackets.find('(')!=string::npos)
        {
            // this is to deal with brackets inside each others like ((5+2)(5*3)*4)
            string temp = dealWithBrackets(stringInsideTheBrackets);
            replaceString(inputString,stringInsideTheBrackets,temp);
            inputString = dealWithBrackets(inputString);
        }

        else
        {
            string calculatedValue = calcSimpleExpression(stringInsideTheBrackets);
            stringInsideTheBrackets = "("+stringInsideTheBrackets+")";
            replaceString(inputString,stringInsideTheBrackets,calculatedValue);
            poss =  inputString.find('(');
            if(poss != string::npos)
                return dealWithBrackets(inputString);           // this is to deal with the brackets besides each other like (5+2)-(5/5)
            else
                return inputString;

        }
    }
    //if there's no brackets return inputString
    return inputString;

}


//
/**
*
* @brief helper method for getStringValue
* @brief it calculates the value of a give string that has no any other thing than +-*^/
* @return the value as a string
*
*/



string Matlab::calcSimpleExpression(string s)
{

    string operators[5] = { "^","*", "/","+","-" };
    char numbers[11] = { '0','1','2','3','4','5','6','7','8','9','.' };
    if (( s[0] == '-'))
        s = '0' + s;



    for (int i = 0; i <5; i++)
    {
        int pos = s.find(operators[i]);

        if (pos != string::npos)
        {



            //for neg at beginning special case
            if (pos == 0 && i == 4)
            {
                pos = s.find(operators[i], 1);
                if (pos == string::npos)
                    break;


            }

            if (pos == 0 && i == 3)
            {
                s.erase(0, 1);

                continue;



            }

            s.erase(pos, 1);
            double   Dafter, Dbefore, Dresult;
            string   Safter, Sbefore, Sresult;
            string   nmafter, nmbefore;
            int      sign_after = 1, sign_before = 1;


            Safter = s.substr(pos, s.length() - pos);
            Sbefore = s.substr(0, pos);
            int count = 0, flag = 0, end = 12;


            //for the number after
            if (i != 3 && i != 4)
            {
                if (Safter[0] == '-')
                {
                    sign_after = -1;
                    Safter.erase(0, 1);
                }


                //	if (Safter[0] == '+')
                //{
                //sign_after = 1;
                //	Safter.erase(0, 1);
                //}
            }

            for (int j = 0; j < Safter.length(); j++)
            {
                for (int d = 0; d < end; d++)
                {
                    if (Safter[j] == numbers[d])
                    {
                        count++;
                        if (d == 10)
                        {
                            end = 11;
                        }
                        flag = 1;

                        break;
                    }
                }
                if (flag == 0)
                    break;
                flag = 0;

            }

            nmafter = Safter.substr(0, count);
            Dafter = atof(nmafter.c_str());
            Safter.erase(0, count);
            Dafter *= sign_after;
            //now the after number have been taken with its sign
            //after string is also ready


            /********************using sstream a waste of a day at least **************************/
            // for after
            //turn into double
            //			SSafter << Safter;//puts after in ss form
            //		SSafter >> Dafter;//takes double i want (after)
            //never mind the next line
            //turn into string	 //		ostringstream strss;      //      strss <<(Dafter);   //	string strr = strss.str();
            //gets the after ready
            //	Safter.erase(0, count);
            /*
            // for before
            // turn into double
            reverse(Sbefore);
            SSbefore << Sbefore;
            SSbefore >> fixed >> Dbefore;
            // turn into string
            ostringstream strs;
            strs << fixed<<Dbefore;
            string str = strs.str();
            // reverse back
            reverse(str);
            // urn into actual double
            temp << std::fixed<<str;
            temp >> std::fixed>>Dbefore;

            Sbefore.erase(0,str.length());
            reverse(Sbefore);

            //reverse(Sbefore);
            */

            /*****************************************************************************/
            //for number before


            count = 0, flag = 0, end = 12;
            //		cout << Sbefore.length();
            for (int j = Sbefore.length() - 1; j >= 0; j--)
            {
                for (int d = 0; d < end; d++)
                {
                    if (Sbefore[j] == numbers[d])
                    {
                        count++;
                        if (j == 10)end = 11;
                        flag = 1;
                        break;

                    }


                }
                if (flag == 0)
                    break;
                flag = 0;

            }

            //	count--;
            //to get before ready
            reverse(Sbefore);
            string copySbefore = Sbefore;
            Sbefore.erase(0, count);
            reverse(Sbefore);
            copySbefore.erase(count, copySbefore.length() - count);
            reverse(copySbefore);
            Dbefore = atof(copySbefore.c_str());
            //now for the sign of the sbefore
            int entered = 0;

            if (Sbefore.length() > 2)
                if (
                    (Sbefore[Sbefore.length() - 1] == '+')
                    || (Sbefore[Sbefore.length() - 1] == '-')
                )
                    if ( (Sbefore[Sbefore.length() - 2] == '+')
                            || (Sbefore[Sbefore.length() - 2] == '-')
                            || (Sbefore[Sbefore.length() - 2] == '*')
                            || (Sbefore[Sbefore.length() - 2] == '/')
                            || (Sbefore[Sbefore.length() - 2] == '^')
                       )
                    {
                        entered = 1;
                        if ((Sbefore[Sbefore.length() - 1] == '+'))
                            sign_before = 1;

                        if ((Sbefore[Sbefore.length() - 1] == '-'))
                            sign_before = -1;

                        Sbefore.erase(Sbefore.length() - 1, 1);
                    }


            //		cout << (Sbefore.length() - copySbefore.length()) ;
            if (
                //	(Sbefore.length() - copySbefore.length()) > 0			&&
                Sbefore.length() > 0
                && entered != 1
                && i!=0
            )
            {
                //	if (i == 3 || i == 4)
                //{
                if ((Sbefore[Sbefore.length() - 1] == '+'))
                    sign_before = 1;

                if ((Sbefore[Sbefore.length() - 1] == '-'))
                {
                    sign_before = -1;
                    Sbefore.erase(Sbefore.length() - 1, 1);
                }
                //	}

            }
            entered = 0;
            Dbefore *= sign_before;

            stringstream SSbefore, SSafter, ssresult, temp;
            /*************************using stringstream***********************************************/
            /*
            //to get the string of before

            stringstream SSbefore, SSafter, ssresult, temp;
            string beforenumber = copySbefore.substr
            (copySbefore.length() - count, count);
            //to get the before as a number
            SSbefore << beforenumber;
            SSbefore >> fixed >> Dbefore;
            // to calc.

            */
            /*****************************************************************************/

            //now for the real calculations
            switch (i)
            {
            case 0:
                Dresult = pow(Dbefore, Dafter);
                break;
            case 1:
                Dresult = Dbefore * Dafter;
                break;
            case 2:
                Dresult = Dbefore / Dafter;
                break;
            case 3:
                Dresult = Dbefore + Dafter;
                break;
            case 4:
                Dresult = Dbefore - Dafter;
                break;
                //case 5: result = before % after; break;
            }
            char text[1000] = "";
            sprintf(text, "%f", Dresult);
// _s , sizeof(text)

            // to turn answer into string
            ssresult << Dresult;
            ssresult >> std::fixed >> Sresult;
            //to get all back together


            //(i == 3 || i == 4) &&
            if ( Dresult > 0 && Sbefore.length() != 0 && sign_before==-1 )
            {
                s = Sbefore + '+' + text + Safter;
            }
            else
                //getting ready for next calc.
                s = Sbefore + text + Safter;




            pos = string::npos;
            i--;
        }

    }



    return s;



}








// here you need to use your function of find the bracket then get its value by my function then you need to
// send its  value back here to me to get its sin or cos
// the string temp is the string that you search for its first "(" and till the ")"
// and solve it like a normal function then send the value here as a string in  temp3




//            s =	 NormalOperationsAndBrackets(s);


/**
* @brief : it takes the string with sin , cos & tan and cal. them
* @breif : with the helper of getstringvalue helpers
*
* @brief helper method for getStringValue
*/


string Matlab::solvetrignometry(string s)
{

    string constants[3] = { "sin", "cos", "tan"  };

    for (int i = 0; i < 3 ; i++)
    {
        //ex: s= "5+4+3+sin(4+5)+6"
        int pos = s.find(constants[i]);//finds the first letter s here pos = 6
        if (pos != string::npos)
        {
//to get the function
            char sign ;
            if(pos>0) sign = s[pos-1];
            else
            {
                sign = '\0';
            }

            string strafter = s.substr(pos+3, s.length()-pos);//(4+5)+6
            string Sbefore = s.substr(  0,pos -1 ); //5+4+3+
            // get the position of the in function
            int startingPosisition= strafter.find('(');//0
            int endingPosition = findTheClosingBracket(strafter,'(');//4

//to return it back later
            string Safter = strafter.substr( endingPosition+1, strafter.length()-endingPosition ); //+6
// get the brackets alone and get their  value
            string calc = strafter.substr( startingPosisition+1, endingPosition-startingPosisition-1 ); //(4+5)
            calc = getStringValue( calc );//9

            // get the number in double
            stringstream SSafter, ssresult ;
            string Sresult;
            double number,Dresult  ;
            SSafter << calc;//9
            SSafter >> number;//9
            // get the trig of it
            switch (i)
            {
            case 0:
                Dresult = sin(number);
                break;//sin(9) = .1564....
            case 1:
                Dresult = cos(number);
                break;
            case 2:
                Dresult = tan(number);
                break;
            }
            // return the answer to string
            ssresult << Dresult;//.1564
            ssresult >>std::fixed >> Sresult;//.1564
            // put the string back together
            if(sign == '-'||sign == '+')
            {
                char newSign = ((Dresult >  0 && sign == '+')||(Dresult<0 && sign =='-') ) ? '+' : '-';
                if(Dresult<0) Sresult.erase(0,1);                                   // to delete the negative sign
                s = Sbefore + newSign +Sresult + Safter;//5+4+3+.1564+6
            }
            else
            {
                s = Sresult+Safter;
            }
            // search again
            i--;
        }


    }


    return  s;
}
/** @brief returns the instruction without special functions like sin()
 *
 * @param instruction it is the instruction without matlab names or special matrix ex: 1.2+sqrt([4.0 16.0],[16.0 4.0])+[6.0 pow(2,2) 3.0 4.0]
 * @return the instruction without fns like:sin-cos-tan-sqrt-pow-exp ,replace them by their equivalent value or matrix ex: 1.2+[2.0 4.0 4.0 2.0]+[6.0 4.0 3.0 4.0]
 * notes: it can be a single value or a matrix inside the function
 * special fns are sin,cos,tan,asin,acos,atan,sinh,cosh,tanh,asinh,acosh,atanh,abs,ceil,floor,sqrt,exp,log,log10,power
 */






string Matlab::getInstructionWithoutFunctions(string instruction)
{
    while(checkInstructionForFunctions(instruction))
    {
        string extractedString;
        //power fn is missing
        extractedString=extractStringInsideFunction(instruction);
        if(!checkStringForMatrix(extractedString))//no matrix found inside the special function
        {
            string value;//the equivalent value of the string
            string replacedString;
            value=getStringValue(extractedString);
            switch(checkInstructionForFunctions(instruction))
            {
            case 1:
                replacedString="sin("+extractedString+")";
                value=doubleToString(sin(stringToDouble(value)));
                break;
            case 2:
                replacedString="cos("+extractedString+")";
                value=doubleToString(cos(stringToDouble(value)));
                break;
            case 3:
                replacedString="tan("+extractedString+")";
                value=doubleToString(tan(stringToDouble(value)));
                break;
            case 4:
                replacedString="asin("+extractedString+")";
                value=doubleToString(asin(stringToDouble(value)));
                break;
            case 5:
                replacedString="acos("+extractedString+")";
                value=doubleToString(acos(stringToDouble(value)));
                break;
            case 6:
                replacedString="atan("+extractedString+")";
                value=doubleToString(atan(stringToDouble(value)));
                break;
            case 7:
                replacedString="sinh("+extractedString+")";
                value=doubleToString(sinh(stringToDouble(value)));
                break;
            case 8:
                replacedString="cosh("+extractedString+")";
                value=doubleToString(cosh(stringToDouble(value)));
                break;
            case 9:
                replacedString="tanh("+extractedString+")";
                value=doubleToString(tanh(stringToDouble(value)));
                break;
            case 10:
                replacedString="asinh("+extractedString+")";
                value=doubleToString(asinh(stringToDouble(value)));
                break;
            case 11:
                replacedString="acosh("+extractedString+")";
                value=doubleToString(acosh(stringToDouble(value)));
                break;
            case 12:
                replacedString="atanh("+extractedString+")";
                value=doubleToString(atanh(stringToDouble(value)));
                break;
            case 13:
                replacedString="fabs("+extractedString+")";
                value=doubleToString(fabs(stringToDouble(value)));
                break;
            case 14:
                replacedString="ceil("+extractedString+")";
                value=doubleToString(ceil(stringToDouble(value)));
                break;
            case 15:
                replacedString="floor("+extractedString+")";
                value=doubleToString(floor(stringToDouble(value)));
                break;
            case 16:
                replacedString="sqrt("+extractedString+")";
                value=doubleToString(sqrt(stringToDouble(value)));
                break;
            case 17:
                replacedString="exp("+extractedString+")";
                value=doubleToString(exp(stringToDouble(value)));
                break;
            case 18:
                replacedString="log("+extractedString+")";
                value=doubleToString(log(stringToDouble(value)));
                break;
            case 19:
                replacedString="log10("+extractedString+")";
                value=doubleToString(log10(stringToDouble(value)));
                break;
            //case 20:replacedString="power("+extractedString+")"; break;
            default:
                throw("not supported function");
            }
            replaceString(instruction,replacedString,value);
        }
        else//there is a matrix inside the special function
        {
            string finalMatrix;
            string replacedString;
            extractedString=getInstructionWithoutExpressions(extractedString);
            finalMatrix=getStringMatrix(extractedString);
            switch(checkInstructionForFunctions(instruction))
            {
            case 1:
                replacedString="sin("+extractedString+")";
                finalMatrix=CMatrix(finalMatrix).sin_element().getString2();
                break;
            case 2:
                replacedString="cos("+extractedString+")";
                finalMatrix=CMatrix(finalMatrix).cos_element().getString2();
                break;
            case 3:
                replacedString="tan("+extractedString+")";
                finalMatrix=CMatrix(finalMatrix).tan_element().getString2();
                break;
//            case 4:
//                replacedString="asin("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).asin_element().getString2();
//                break;
//            case 5:
//                replacedString="acos("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).acos_element().getString2();
//                break;
//            case 6:
//                replacedString="atan("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).atan_element().getString2();
//                break;
//            case 7:
//                replacedString="sinh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).sinh_element().getString2();
//                break;
//            case 8:
//                replacedString="cosh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).cosh_element().getString2();
//                break;
//            case 9:
//                replacedString="tanh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).tanh_element().getString2();
//                break;
//            case 10:
//                replacedString="asinh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).asinh_element().getString2();
//                break;
//            case 11:
//                replacedString="acosh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).acosh_element().getString2();
//                break;
//            case 12:
//                replacedString="atanh("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).atanh_element().getString2();
//                break;
//            case 13:
//                replacedString="abs("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).abs_element().getString2();
//                break;
//            case 14:
//                replacedString="ceil("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).ceil_element().getString2();
//                break;
//            case 15:
//                replacedString="floor("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).floor_element().getString2();
//                break;
//            case 16:
//                replacedString="sqrt("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).sqrt_element().getString2();
//                break;
//            case 17:
//                replacedString="exp("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).exp_element().getString2();
//                break;
//            case 18:
//                replacedString="log("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).log_element().getString2();
//                break;
//            case 19:
//                replacedString="log10("+extractedString+")";
//                finalMatrix=CMatrix(finalMatrix).log10_element().getString2();
//                break;
            /*
            case 20:
            replacedString="power("+extractedString+")";
            finalMatrix=CMatrix(finalMatrix).power().getString2();
            break;*/
            default:
                throw("not supported function");
            }
            replaceString(instruction,replacedString,finalMatrix);
        }
    }
    return instruction;
}

/** @brief search the instruction for special function and returns integer number corresponding to the function found
 *
 * @param instruction the instruction without matlab names or special matrices ex: 1.2+sqrt([4.0 16.0],[16.0 4.0])+[6.0 power(2,2) 3.0 4.0]
 * @return returns 0 if no special function found. 1 for sin,2 for cos,...:respectively by the order of the following line
 * special fns are sin,cos,tan,asin,acos,atan,sinh,cosh,tanh,asinh,acosh,atanh,abs,ceil,floor,sqrt,exp,log,log10,power
 * Note: the returned number corresponds to the first found function while searching
 */


int Matlab::checkInstructionForFunctions(string instruction)
{
    string constants[20] =
    {
        "sin", "cos", "tan"
        ,"asin", "acos", "atan"
        ,"sinh", "cosh", "tanh"
        ,"asinh", "acosh", "atanh"
        ,"abs", "ceil", "floor"
        ,"sqrt", "exp", "log"
        ,"log10", "power"
    };
    for (int i = 0; i < 20 ; i++)
    {
        int pos = instruction.find(constants[i]);
        if (pos != string::npos)
        {
            //for sin cos and tan
            if( i<3)
            {
                if( instruction[pos+3]=='h'&& instruction[pos-1]!='a' )
                {
                    i=i+6;
                }

                if(  instruction[pos+3]!='h' && instruction[pos-1]=='a'   )
                {
                    i=i+3;
                }
                if(  instruction[pos+3]=='h' && instruction[pos-1]=='a'   )
                {
                    i=i+9;
                }
            }

            //for log and log10
            if(i==17)
            {
                if(  instruction[pos+1+2]=='1' && instruction[pos+2+2]=='0'   )
                {
                    i++;
                }
            }







            return i+1;
        }
    }
    return 0;
}


/** @brief extract the string inside the () of the first special function found in the instruction
 *
 * @param instruction the instruction without matlab names or special matrices   ex: 1.2+sqrt([4.0 16.0],[16.0 4.0])+[6.0 power(2,2) 3.0 4.0]
 * @return the string inside the () of the first special function found in the instruction ex: [4.0 16.0],[16.0 4.0]
 *
 */

string Matlab::extractStringInsideFunction(string instruction)
{
    string constants[20] =
    {
        "sin", "cos", "tan"
        ,"asin", "acos", "atan"
        ,"sinh", "cosh", "tanh"
        ,"asinh", "acosh", "atanh"
        ,"abs", "ceil", "floor"
        ,"sqrt", "exp", "log"
        ,"log10", "power"
    };
    for (int i = 0; i < 20 ; i++)
    {
        int pos = instruction.find(constants[i]);
        if (pos != string::npos)
        {

            int startingpostion= instruction.find('(',pos);
            int endingPosition = findTheClosingBracket(instruction,'(');
            return instruction.substr( startingpostion+1, endingPosition-startingpostion-1 );

        }


    }
    return "invalid call for the function of extractStringInsideFunction";

}

/** @brief simplify the String to the final matrix string
 *
 * @param complexString it is a string of matrix operations without any matlab names or special matrix or special functions
 ex: 1.2+[[1.0 2.0; 3.0 3.0]*[[2.0 4.0];[4.0 4.0]]]/[6.0 5.0; 4.0 3.0]
 * @return the resultant matrix as a string ex:    [10.2000 -9.8000;22.2000 -25.8000]
 * search for all operations including dot operations
 * take care of the priority between concatenation and operations
 */

string Matlab::getStringMatrix(string complexString)
{

    complexString = dealwithSpecialFunctions(complexString);
    string oldString = "";
    while(oldString != complexString)
    {
        oldString= complexString;
        complexString = dealwithOperators(complexString);
    }
    oldString = "";
 while(oldString != complexString)
    {
        oldString= complexString;
    complexString = dealWithConcatenation(complexString);
    }


    return complexString;

}
string extractTheNumber( string const &mainString,int positionOfFirstDigit,bool reverse_ = false)
{
    if(!reverse_)
    {
        int positionOfLastDigit = positionOfFirstDigit;
        bool  stillWhiteSpace = true;
        while((mainString[positionOfLastDigit]>='0' && mainString[positionOfLastDigit]<='9')||stillWhiteSpace)
        {
            if(stillWhiteSpace)
                if(mainString[positionOfLastDigit]!=' ') stillWhiteSpace = false;
                else positionOfFirstDigit++;
            positionOfLastDigit++;
        }

        string answer = mainString.substr(positionOfFirstDigit, positionOfLastDigit -positionOfFirstDigit  );
        return answer;
    }
    else
    {

        int positionOfLastDigit = positionOfFirstDigit;
        bool  stillWhiteSpace = true;
        while((mainString[positionOfFirstDigit]>='0' && mainString[positionOfFirstDigit]<='9')||stillWhiteSpace)
        {
            if(stillWhiteSpace)
                if(mainString[positionOfFirstDigit]!=' ') stillWhiteSpace = false;
                else positionOfLastDigit--;
            positionOfFirstDigit--;
            if(positionOfFirstDigit==0) break;
        }
        if(positionOfFirstDigit == 0&&(mainString[positionOfFirstDigit]>='0' && mainString[positionOfFirstDigit]<='9')) positionOfFirstDigit = -1;

        string answer = mainString.substr(positionOfFirstDigit+1, positionOfLastDigit -positionOfFirstDigit+1  );
        return answer;


    }

}

int indexOfTheBracket(bool squareBracket,bool searchingForBeginning,string instruction,int indexOfOperator)
{
    char bracketToSearchFor;
    if(squareBracket)
    {
        if(searchingForBeginning)
        {
            bracketToSearchFor = '[';
            for(int i =indexOfOperator;  i<instruction.size() ; i++)
            {
                if(instruction[i] == bracketToSearchFor) return i;
                if(i-indexOfOperator>2 && instruction[i]!=' ') return -1;

            }
            return -1 ;
        }
        else
        {
            bracketToSearchFor = ']';

            for(int i =indexOfOperator; i>0; i--)
            {
                if(instruction[i] == bracketToSearchFor) return i;
                if(indexOfOperator-i>0 && instruction[i]!=' ') return -1;

            }
            return -1 ;

        }
    }





}

string Matlab::dealwithOperators(string instruction)
{



    // first dealing with .^ operator

    string operator_ = ".^";
    int pos = instruction.find(operator_);


    ///     .^ operator
    operator_ = ".^";

    while(pos!=string::npos)
    {
        pos = instruction.find(operator_);

        string powerDegree = extractTheNumber(instruction,pos+2) ;

        int positionOftheMatrixEnd = indexOfTheBracket(true,false,instruction,pos);
        string matrixString = findTheMatrix(instruction,false,positionOftheMatrixEnd);
        CMatrix x(matrixString);
        x = x.dot_power(atof(powerDegree.c_str()));
        int beginning = instruction.rfind(matrixString,pos);
        int ending= instruction.find(powerDegree,pos)+powerDegree.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,x.getString2());
        pos= instruction.find(operator_);

    }

    ///     ^ operator
    operator_ = '^';
    pos = instruction.find(operator_);
    while(pos!=string::npos)
    {
        pos = instruction.find(operator_);

        string powerDegree = extractTheNumber(instruction,pos+1) ;

        int positionOftheMatrixEnd = indexOfTheBracket(true,false,instruction,pos);
        string matrixString = findTheMatrix(instruction,false,positionOftheMatrixEnd);
        CMatrix x(matrixString);
        x = x.power(atof(powerDegree.c_str()));
        int beginning = instruction.rfind(matrixString,pos);
        int ending= instruction.find(powerDegree,pos)+powerDegree.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,x.getString2());
        pos= instruction.find(operator_);

    }



    /// matrix * matrix operator
    operator_ = '*';
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);

        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning==-1) continue;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);
        string rightMatrixString = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);

        CMatrix leftMatrix(leftMatrixString);
        CMatrix rightMatrix(rightMatrixString);
        leftMatrix.mul(rightMatrix);
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(rightMatrixString,pos)+rightMatrixString.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,leftMatrix.getString2());

    }

    /// matrix * number operator
    operator_ = '*';
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning!=-1) continue;
        string numberMultiplied = extractTheNumber(instruction,pos+1) ;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);


        CMatrix leftMatrix(leftMatrixString);

        leftMatrix = leftMatrix * atof(numberMultiplied.c_str());
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(numberMultiplied,pos)+numberMultiplied.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,leftMatrix.getString2());


    }
    instruction = dealWithAddAndSubOperators(instruction,".*");

    /// number * matrix operator
    operator_ = '*';
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd!=-1||positionOftheRightMatrixBeginning==-1)continue;
        string numberMultiplied = extractTheNumber(instruction,pos-1,true) ;


        string rightStringMatrix = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);


        CMatrix rightMatrix(rightStringMatrix);

        rightMatrix = rightMatrix * atof(numberMultiplied.c_str());
        int ending = instruction.find(rightStringMatrix,pos)+rightStringMatrix.size();
        int beginning= instruction.rfind(numberMultiplied,pos);
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,rightMatrix.getString2());
        pos= instruction.find(operator_);

    }


      /// matrix ./ matrix operator
    operator_ = "./";
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);

        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning==-1) continue;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);
        string rightMatrixString = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);

        CMatrix leftMatrix(leftMatrixString);
        CMatrix rightMatrix(rightMatrixString);
        leftMatrix.dot_div1(rightMatrix);
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(rightMatrixString,pos)+rightMatrixString.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,leftMatrix.getString2());

    }

    /// matrix ./ number operator
    operator_ = "./";
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning!=-1) continue;
        string numberMultiplied = extractTheNumber(instruction,pos+2) ;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);


        CMatrix leftMatrix(leftMatrixString);

        leftMatrix = leftMatrix / atof(numberMultiplied.c_str());
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(numberMultiplied,pos)+numberMultiplied.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,leftMatrix.getString2());


    }

    /// number ./ matrix operator
    operator_ = "./";
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd!=-1||positionOftheRightMatrixBeginning==-1)continue;
        string numberMultiplied = extractTheNumber(instruction,pos-1,true) ;


        string rightStringMatrix = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);


        CMatrix rightMatrix(rightStringMatrix);

        rightMatrix =  atof(numberMultiplied.c_str()) /rightMatrix ;
        int ending = instruction.find(rightStringMatrix,pos)+rightStringMatrix.size();
        int beginning= instruction.rfind(numberMultiplied,pos);
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,rightMatrix.getString2());
        pos= instruction.find(operator_);

    }


    instruction = dealWithAddAndSubOperators(instruction,"/");

    /// matrix / matrix operator
    operator_ = '/';
    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);

        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning==-1) continue;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);
        string rightMatrixString = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);

        CMatrix leftMatrix(leftMatrixString);
        CMatrix rightMatrix(rightMatrixString);
        leftMatrix.div(rightMatrix);
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(rightMatrixString,pos)+rightMatrixString.size();
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,leftMatrix.getString2());



    }
    string old = "";
    while(instruction!=old)
    {
        old = instruction;
        instruction =dealWithAddAndSubOperators(instruction,".+");
        instruction =dealWithAddAndSubOperators(instruction,"+");
    }
    old = "";
    while(instruction!=old)
    {
        old = instruction;

        instruction =dealWithAddAndSubOperators(instruction,".-");
        instruction =dealWithAddAndSubOperators(instruction,"-");
    }
    return instruction;


}

string Matlab :: dealWithAddAndSubOperators(string instruction, string operator_)
{




    /// matrix + matrix operator

    int pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);

        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning==-1) continue;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);
        string rightMatrixString = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);

        CMatrix leftMatrix(leftMatrixString);
        CMatrix rightMatrix(rightMatrixString);

        bool leftMatrixIsPositive= true;
        string sign = "";
        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(rightMatrixString,pos)+rightMatrixString.size();
        for(int i = beginning-1 ; i>0; i--)
        {
            if(instruction[i] =='-')
            {
                leftMatrixIsPositive = false;
                break;
            }
            if(instruction[i] != ' ') break;
        }

        if(!leftMatrixIsPositive)
        {
            leftMatrix = -leftMatrix;
            sign = "+";
            beginning--;
        }
        if(operator_=="+"||operator_==".+")
            leftMatrix = leftMatrix + rightMatrix;
        else if(operator_=="-"||operator_==".-")
            leftMatrix = leftMatrix - rightMatrix;
         else if(operator_==".*")
            leftMatrix = leftMatrix.dot_mult(rightMatrix);




        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,sign+leftMatrix.getString2());


    }

    /// matrix operator number operator

    pos = 0;
    while(pos!=string::npos)
    {
        pos= instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd==-1||positionOftheRightMatrixBeginning!=-1) continue;
        string numberMultiplied = extractTheNumber(instruction,pos+1) ;


        string leftMatrixString = findTheMatrix(instruction,false,positionOftheLeftMatrixEnd);


        CMatrix leftMatrix(leftMatrixString);

        int beginning = instruction.rfind(leftMatrixString,pos);
        int ending= instruction.find(numberMultiplied,pos)+numberMultiplied.size();
        string sign = "";
        bool leftMatrixIsPositive = true;
        for(int i = beginning-1 ; i>0; i--)
        {
            if(instruction[i]=='-')
            {
                leftMatrixIsPositive = false;
                break;
            }
            if(instruction[i] != ' ') break;
        }

        if(!leftMatrixIsPositive)
        {
            leftMatrix = -leftMatrix;
            beginning--;
            sign = "+";
        }

        if(operator_=="+"||operator_==".+")
            leftMatrix = leftMatrix + atof(numberMultiplied.c_str());
        else if(operator_=="-"||operator_==".-")
            leftMatrix = leftMatrix - atof(numberMultiplied.c_str());
        else if(operator_==".*")
            leftMatrix = leftMatrix * atof(numberMultiplied.c_str());
        else if(operator_=="/")
            leftMatrix = leftMatrix / atof(numberMultiplied.c_str());


        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,sign+leftMatrix.getString2());


    }

    /// number + matrix operator

    pos = 0;
    while(pos!=string::npos)
    {
        pos = instruction.find(operator_,pos+1);
        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos);
        int positionOftheLeftMatrixEnd = indexOfTheBracket(true,false,instruction,pos);

        if(positionOftheLeftMatrixEnd!=-1||positionOftheRightMatrixBeginning==-1)continue;
        string numberMultiplied = extractTheNumber(instruction,pos-1,true) ;


        string rightStringMatrix = findTheMatrix(instruction,true,positionOftheRightMatrixBeginning);


        CMatrix rightMatrix(rightStringMatrix);



        if(operator_=="+"||operator_==".+")
            rightMatrix = rightMatrix + atof(numberMultiplied.c_str());
        else if(operator_=="-"||operator_==".-")
            rightMatrix = rightMatrix- atof(numberMultiplied.c_str());
        else if(operator_==".*")
            rightMatrix = rightMatrix * atof(numberMultiplied.c_str());
          else if(operator_=="/")
            rightMatrix =  atof(numberMultiplied.c_str()) /rightMatrix ;



        int ending = instruction.find(rightStringMatrix,pos)+rightStringMatrix.size();
        int beginning= instruction.rfind(numberMultiplied,pos);
        string replacedString = instruction.substr(beginning,ending-beginning);
        replaceString(instruction,replacedString,rightMatrix.getString2());
        pos= instruction.find(operator_);

    }



    return instruction;

}
void Matlab::dealWithConcatenationHelperFn(string &instruction,string s)
{

    int pos = instruction.find(s);
    bool isThereSquareBracketsContainingTheConcatanatedMatrix = false;
    bool isThereConcatenation = false;
    while(pos!=string::npos)
    {
        int beginning = instruction.rfind("[",pos);

        int ending = instruction.find("]",pos+2);
        int theFirstOpeningSquareBracketPos= beginning;
        int theLastClosingSquareBracketPos= ending;
        for(int i = beginning-1; i>-1; i--)
        {
            if(instruction[i]=='[')
            {
                theFirstOpeningSquareBracketPos=i;
                break;
            }

            else if(instruction[i]!=' ')
            {
                theFirstOpeningSquareBracketPos = beginning;
                break;
            }
        }

        if(theFirstOpeningSquareBracketPos!=beginning)
        {
            for(int i = ending+1; i>0; i++)
            {
                if(instruction[i]==']')
                {

                    theLastClosingSquareBracketPos = i;
                    isThereSquareBracketsContainingTheConcatanatedMatrix = true;
                    break;
                }
                else if(instruction[i]!=' ')
                {
                    theFirstOpeningSquareBracketPos = beginning;

                    break;
                }

            }
        }

        string matrixConcatenated = instruction.substr(beginning,ending-beginning+1 );
        string matrixConcatenatedSolved = getInstructionWithoutConcatenation(matrixConcatenated );
        string replacedString = instruction.substr(theFirstOpeningSquareBracketPos,theLastClosingSquareBracketPos-theFirstOpeningSquareBracketPos+1);
        isThereConcatenation = true;

        replaceString(instruction,replacedString,matrixConcatenatedSolved);
        pos = instruction.find(s);

    }

   // if(!isThereSquareBracketsContainingTheConcatanatedMatrix && isThereConcatenation) throw("syntax error");


}




string Matlab::dealWithConcatenation(string instruction)
{


    dealWithConcatenationHelperFn(instruction,"];[");
    dealWithConcatenationHelperFn(instruction,"] [");
    dealWithConcatenationHelperFn(instruction,"],[");
    return instruction;

}




string Matlab::findTheMatrix(string instruction,bool openingBracket,int pos)
{
    if(openingBracket)
    {
        if(instruction[pos]!='[') throw ("not an opening bracket");

        else
        {
            int ending = findTheClosingBracket(instruction,'[',pos);
            string answer = instruction.substr(pos,ending-pos +1);
            return answer;
        }

    }

    else
    {
        if(instruction[pos]!=']') throw ("not a closing bracket");

        else
        {
            int ending = findTheOpeningBracket(instruction,'[',pos);
            string answer = instruction.substr(ending,pos-ending+1);
            return answer;
        }

    }



}

string Matlab::dealwithSpecialFunctions(string instruction)
{

    instruction = dealwithSpecialFunctionsHelperFunction(instruction,"sin");

    instruction = dealwithSpecialFunctionsHelperFunction(instruction,"cos");
    instruction = dealwithSpecialFunctionsHelperFunction(instruction,"log10");
    instruction = dealwithSpecialFunctionsHelperFunction(instruction,"log");



    return instruction;

}
string Matlab::dealwithSpecialFunctionsHelperFunction(string instruction,string specialFunction)
{


    int pos = instruction.find(specialFunction);
    while(pos!=string::npos)
    {
        int positionOfOpeningBracket = pos+specialFunction.size();
        int positionOfClosingBracket = findTheClosingBracket(instruction,'(',positionOfOpeningBracket);

        int positionOftheRightMatrixBeginning = indexOfTheBracket(true,true,instruction,pos+specialFunction.size());

        string rightStringMatrix = dealwithOperators(instruction.substr(positionOftheRightMatrixBeginning,positionOfClosingBracket-positionOftheRightMatrixBeginning));


        CMatrix rightMatrix(rightStringMatrix);

        if(specialFunction=="sin")
            rightMatrix = rightMatrix.sin_element();
        if(specialFunction=="cos")
            rightMatrix = rightMatrix.cos_element();
        if(specialFunction=="log10")
            rightMatrix = rightMatrix.log10_element();
        if(specialFunction=="log")
            rightMatrix = rightMatrix.log_element();



        string replacedString = instruction.substr(pos,positionOfClosingBracket-pos+1);
        replaceString(instruction,replacedString,rightMatrix.getString2());
        pos= instruction.find(specialFunction);

    }

    return instruction;
}

/**
* @brief : private Helper function for dealing with brackets (2+5)/(5-2)
*
* @brief helper method for getStringValue
**/
int Matlab::findTheClosingBracket(string s, char openingBracket, int start)
{

    int count =0;
    char closingBracket;

    if (openingBracket == '(')
        closingBracket=')';

    else if (openingBracket == '[')
        closingBracket=']';

    else
    {
        throw ("accepted openingBracets are '(' or '[' only");
    }

    bool foundFirstBracket = false;

    for(int i =start ; i<s.size(); i++)
    {
        if(s[i]==openingBracket)
        {
            count++;
            foundFirstBracket = true;
        }
        if(s[i]==closingBracket)
            count--;
        if(count == 0 && foundFirstBracket)
            return i;
    }
    return string::npos;
}


int Matlab::findTheOpeningBracket(string s, char openingBracket,int start)
{

    int count =0;
    char closingBracket;

    if (openingBracket == '(')
        closingBracket=')';

    else if (openingBracket == '[')
        closingBracket=']';

    else
    {
        throw ("accepted openingBracets are '(' or '[' only");
    }

    bool foundFirstBracket = false;

    for(int i =start ; i<s.size(); i--)
    {
        if(s[i]==closingBracket)
        {
            count++;
            foundFirstBracket = true;
        }
        if(s[i]==openingBracket)
            count--;
        if(count == 0 && foundFirstBracket)
            return i;
    }
    return string::npos;
}






















string Matlab::solvingBrackets(string s)
{
    string temp,replacingString;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i]=='(')
        {
            if(!checkTheBracketOfSpecialFn(s,i))
            {
                int endPosition=findTheClosingBracket(s,'(',i);
                temp=s.substr(i,endPosition-i+1);
                if(!checkStringForMatrix(temp))
                    replacingString=getStringValue(temp);
                else
                    throw("error");
                replaceString(s,temp,replacingString,i);
            }
        }
    }
    return s;
}

//input : s="5*5+6 pos=1
//output: 5*5
string Matlab::findTheSignOperators(string s,int pos)
{
    int i=pos-1;
    string replacingString="";
    string temp="";
    while(1)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='['||s[i]==']'||s[i]==' '||s[i]==';'||s[i]=='('||s[i]==')'||s[i]=='^')
            break;
        temp+=s[i];
        if(i==0)
            break;
        i--;
    }
    for(int j=0; j<temp.length(); j++)
    {
        replacingString+=temp[temp.length()-1-j];
    }
    replacingString+=s[pos];
    i=pos+1;
    while(1)
    {
        if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='['||s[i]==']'||s[i]==' '||s[i]==';'||s[i]=='('||s[i]==')'||s[i]=='^')
            break;
        replacingString+=s[i];
        if(i==s.length()-1)
            break;
        i++;
    }
    return replacingString;

}
