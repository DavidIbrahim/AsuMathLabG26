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
#include <boost/lexical_cast.hpp>


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

	 int poss = s.find('(');
	if (poss != string::npos)
	{
		int pos2 = s.find(')');
		string temp = s.substr(poss + 1, s.length() - pos2);
		//here call again
		cout<<temp<<endl;
	}

	s = "5656565+5656565-995656565659";

	string operators[8] = { "^","*", "/","+","-" };

	for (int i = 0; i <5; i++)
	{
		int pos = s.find(operators[i]);
		if (pos != string::npos)
		{
            s.erase(pos, 1);
			double   Dafter , Dbefore, Dresult;
			string   Safter, Sbefore, Sresult;
			Safter =  s.substr(pos, s.length() - pos);
			Sbefore = s.substr(0, pos);
/*
			int count =0,flag=0;
			for(int j=0;;j++)
                {

                 for(int d=0;d<11;d++)
                {
                    if(Safter[j]==numbers[d])
                    { count++;
                    Dafter = numberss[d] * pow(10,j);
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




*/










			stringstream SSbefore, SSafter, ssresult , temp;
		// for after
		//turn into double
			SSafter <<std::setprecision (std::numeric_limits<double>::digits10 + 1)<< Safter;//puts after in ss form
			SSafter >> std::fixed>>std::setprecision (std::numeric_limits<double>::digits10 + 1)>>Dafter;//takes double i want

	//turn into string
			ostringstream strss;
            strss << lexical_cast<string>(Dafter);
			string strr = strss.str();
            Safter.erase( 0,strr.length());

            // for before
            // turn into double
			reverse(Sbefore);
			SSbefore << Sbefore;
			SSbefore >> Dbefore;
// turn into string
			ostringstream strs;
            strs << Dbefore;
            string str = strs.str();
         // reverse back
            reverse(str);
// urn into actual double
            temp << std::fixed<<str;
            temp >> std::fixed>>Dbefore;

			Sbefore.erase(0,str.length());
			reverse(Sbefore);






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


cout<<s<<endl;



    return 0;
}

