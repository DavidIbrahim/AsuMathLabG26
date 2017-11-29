#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"

#include<string.h>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
#include<sstream>
#include<math.h>




using namespace std;

void reverse(string & s)
{   char temp;
	for (int i = 0 , j = s.length()-1 ; i < s.length()/2; i++ , j--)
	{
		temp = s[j];
		s[j] = s[i];
		s[i] = temp;
	}
}



void trimAllSpaces(string & s)
{   //	s.erase(s.begin(),std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));//l. only
    //	s.erase( std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),  s.end());//r. only
	for (int i = 0; i < s.length(); i++)
	{ if (s[i] == ' ') {  s.erase( i,1 );       i--;       }        }}




string NormalOperationsAndBrackets(string s)
{
	 s = "5+4+3(5*3)+5";




	int pos = s.find('(');
	if (pos != string::npos)
	{
		int pos2 = s.find(')');
		string temp = s.substr(pos + 1, s.length() - pos2);
		//here call again
		cout<<temp<<endl;
	}

	s = "5+4*3-6/5^9";
	//stringstream ss;
	//ss >> s;
	string operators[8] = { "^","*", "/","+","-" };
	for (int i = 0; i <9; i++)
	{
		int pos = s.find(operators[i]);
		if (pos != string::npos)
		{
			s.erase(pos, 1);
			double   Dafter, Dbefore, Dresult;
			string   Safter, Sbefore, Sresult;
			Safter = s.substr(pos, s.length() - pos);
			Sbefore = s.substr(0, pos);
			reverse(Sbefore);
			stringstream SSbefore, SSafter, ssresult;
			SSafter << Safter;
			SSafter >> Dafter;
			SSafter >> Safter;
			SSbefore << Sbefore;
			SSbefore >> Dbefore;
			SSbefore << Sbefore;
			switch (i) {
			case 0: Dresult = pow(Dbefore, Dafter); break;
			case 1: Dresult = Dbefore * Dafter; break;
			case 2: Dresult = Dbefore / Dafter; break;
			case 3: Dresult = Dbefore + Dafter; break;
			case 4: Dresult = Dbefore - Dafter; break;
				//case 6: result = before % after; break;
			}
			ssresult << Dresult;
			ssresult >> Sresult;
			s = Sbefore + Sresult + Safter;




			i--;
		}

	}







	return s;
}


string myfunction(string s)
{
	// trim at first
    trimAllSpaces(s);
	//make sure all operations are in the form expected
	//transform(s.begin(), s.end(), s.begin(), ::tolower);
    // look for sin cos tan
	string constants[3] = { "sin" , "cos" , "tan"  };
	for (int i = 0; i < 4 ; i++)
	{
		int pos = s.find(constants[i]);
		if (pos != string::npos)
		{

			string temp = s.substr(pos+3, s.length()-pos);
			int pos2 = temp.find(')');
			string temp2 = temp.substr(0, pos2+1);
			//string temp3 =  myfunction(temp2);
			string temp3 = "5"; // comment it




			s.replace(pos, temp2.length()+3, temp3);
			cout << s<<endl;

			i--;
		}

	s=	NormalOperationsAndBrackets(s);


	}


	return  s;
}

int main()
{
    string s = "dsd";
    s=	NormalOperationsAndBrackets(s);

cout<<"hello world";



    return 0;
}

