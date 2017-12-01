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


void reverse(string & s)
{   char temp;
	for (int i = 0 , j = s.length()-1 ; i < s.length()/2; i++ , j--)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
	}
}

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

string Matlab::getInstructionWithoutMatlabNames(string instruction,vector<Matlab> savedMatrices)
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
 * hint: there is a horizontalConcatenation and verticalConcatenation fns in Cmatrix so you can convert the string to matrix then send it to it.
 */

string Matlab::getInstructionWithoutConcatenation(string instruction)
{

    CMatrix m(instruction);
    return m.getString2();//returns the string with  concatinations removed.

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
/** @brief simplify the expression to the final matrix string
 *
 * @param complexString it is a string of matrix operations without any matlab names or special matrix ex: 1.2+[1.0 2.0]*2+sin([3.3 2.2])
 * @return the resultant matrix as a string ex: [3.0423 6.0085]
 * search for all operations including dot operations
 */

string Matlab::getStringMatrix(string complexString)
{

}

/**
* this fn takes the full instruction as it is ex: B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]];
* and returns it ready for cmatrix constructor ex: B= [1.2 2.3 3.0;1.3 2.4 3.2; 4.6 1.3 7.8];
* without any Matlab names in between, concatenations or expressions.
* @param instruction the instruction taken from the user
* @param savedMatrices the vector where all Matlab objects are stored
  @return a simple instruction without any Matlab names in between, concatenations or expressions.
*/
string Matlab::getReadyInstruction(string instruction,vector<Matlab> savedMatrices)
{

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

/**
* @brief remove all white spaces from the parameter s
* @param string s where all white spaces will be removed from
*/
void Matlab:: trimAllSpaces(string & s)
{   //	s.erase(s.begin(),std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));//l. only
    //	s.erase( std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),  s.end());//r. only
	for (int i = 0; i < s.length(); i++){
            if (s[i] == ' ') {
            s.erase( i,1 );
            i--;
        }

    }
}
/** @brief simplify the expression to the final string value
 *
 * @param complexString it is a string of 1D expression, contains no matrices ex: 1+2/5*sin(2)
 * @return the final value of the expression as a string ex: 1.3637
 *
 */

string Matlab::getStringValue(string complexString)
{   trimAllSpaces(complexString);
    bool isThereBrackets = true;
    complexString=dealWithBrackets(complexString);
//    complexString = calcSimpleExpression(complexString);
    return complexString;
}

/**
* @brief helper method for getStringValue
*/

string Matlab:: dealWithBrackets(string inputString){
 int poss = inputString.find('(');
	if (poss != string::npos)
	{
		int pos2 = findTheClosingBracket(inputString,'(');

		string stringInsideTheBrackets = inputString.substr(poss + 1, pos2-poss-1);
        if(stringInsideTheBrackets.find('(')!=string::npos){
                string temp = dealWithBrackets(stringInsideTheBrackets);
                replaceString(inputString,stringInsideTheBrackets,temp);
                inputString = dealWithBrackets(inputString);
           }
            else {
            string calculatedValue = calcSimpleExpression(stringInsideTheBrackets);
            stringInsideTheBrackets = "("+stringInsideTheBrackets+")";
            replaceString(inputString,stringInsideTheBrackets,calculatedValue);
            return inputString;

           }
 	}
 	//if there's no brackets return inputString
 	return inputString;

}


// TODO (Rizk#9#12/01/17): Fix Bugs ...
//


string Matlab::calcSimpleExpression(string s){


	string operators[8] = { "^","*", "/","+","-" };
	char numbers [11] = {'0','1','2','3','4','5','6','7','8','9','.'};

	if((s[0]=='+'||s[0]=='-'))
        s='0'+s;


	for (int i = 0; i <5; i++)
	{
		int pos = s.find(operators[i]);
		if (pos != string::npos)
		{
            s.erase(pos, 1);
			double   Dafter , Dbefore, Dresult;
			string   Safter , Sbefore, Sresult;
			Safter =  s.substr(pos, s.length() - pos);
			Sbefore = s.substr(0, pos);

			int count =0,flag=0,end=12;
			for(int j=0;;j++)
                {
                    for(int d=0;d<end;d++)
                {
                    if(Safter[j]==numbers[d])
                    { count++;
                    if(d==10)end=11;
                    flag=1;
                    break;

                                        }


                }
                  if(flag==0)
                        break;
                  flag = 0 ;

                }
		//	for(int j=0;;j--)
			//{

			//}















			stringstream SSbefore, SSafter, ssresult , temp;
		// for after
		//turn into double
			SSafter << Safter;//puts after in ss form
			SSafter >>Dafter;//takes double i want

	//turn into string
	//		ostringstream strss;
      //      strss <<(Dafter);
		//	string strr = strss.str();
            Safter.erase( 0,count);



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
*/
//reverse(Sbefore);


count =0,flag=0,end=12;
			for(int j=Sbefore.length();;j--)
                {
                    for(int d=0;d<end;d++)
                {
                    if(Sbefore[j]==numbers[d])
                    { count++;
                    if(j==10)end=11;
                    flag=1;
                    break;

                                        }


                }
                  if(flag==0)
                        break;
                  flag = 0 ;

                }
count--;
string copySbefore = Sbefore ;
reverse(Sbefore);
Sbefore.erase( 0,count);
reverse(Sbefore);

string beforenumber = copySbefore.substr(copySbefore.length()-count,count);

            SSbefore << beforenumber;
			SSbefore >> fixed >> Dbefore;




			switch (i) {
			case 0: Dresult = pow(Dbefore, Dafter); break;
			case 1: Dresult = Dbefore * Dafter; break;
			case 2: Dresult = Dbefore / Dafter; break;
			case 3: Dresult = Dbefore + Dafter; break;
			case 4: Dresult = Dbefore - Dafter; break;
				//case 6: result = before % after; break;
			}
			ssresult << Dresult;
			ssresult >>std::fixed >> Sresult;
			s = Sbefore + Sresult + Safter;
			pos = string::npos;
			i--;
		}

	}

    return s;



}

/**
* @brief : private Helper function for dealing with brackets (2+5)/(5-2)
*
*/
int Matlab::findTheClosingBracket(string s,char openingBracket){
    int count =0;
    char closingBracket;
    if (openingBracket == '(')
            closingBracket=')';
    else if (openingBracket == '[')
            closingBracket=']';
    else throw ("accepted openingBracets are '(' or '[' only");
    bool foundFirstBracket = false;
    for(int i =0 ; i<s.size();i++) {
        if(s[i]==openingBracket){
            count++;
            foundFirstBracket = true;
        }
        if(s[i]==closingBracket)
        count--;
        if(count==0&&foundFirstBracket) return i;
    }
    return string::npos;
}
