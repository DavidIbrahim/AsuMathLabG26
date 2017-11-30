#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"

using namespace std;
string test(string instruction)
{
      CMatrix m2;
    size_t Begin,End;
    size_t start=0;
while(true)
    {

     Begin =instruction.find("[",start);
     if(Begin==std::string::npos)
        break;
     End =instruction.find("]",start+1);
    string s=instruction.substr(Begin,(End+1)-Begin);

   if(start==0)
    {
    m2=(s);
    }

    else
    {
        CMatrix m1(s);
        string s1=instruction.substr(start,(Begin-start));
        if ((s1.find(";"))!=std::string::npos||(s1.find("\r\n"))!=std::string::npos||(s1.find("\n"))!=std::string::npos)
        {m2=m1.verticalConcatenation(m2,m1);}
        else {m2=m1.horizontalConcatenation(m2,m1);}
    }
    start=End;
}
    return m2.getString2();//returns the string with  concatinations removed.

}


void stressTesting(){

while(true){
        CMatrix B(32,32,CMatrix::MI_RAND);
        //cout<<B.getString2()<<"  ";
         float ans1 = B.getDeterminant();
        float ans2 = B.getDeterminant3();

        if(abs(ans1-ans2)<0.001)
            cout<<" test is ok"<<endl;
        else {
            cout<<endl<<"testFailed"<<endl;
            cout<<"Det 1 = "<<ans1<<endl<<"Det 2 = "<<ans2<<endl;
            B.writeMatrixInFile("error.txt");
            break;
        }


    }

}


bool replaceString(string& mainString , string& replacedString , string& replacingString){

    size_t start_pos = mainString.find(replacedString);
    if(start_pos == std::string::npos)
        return false;
    mainString.replace(start_pos, replacedString.length(), replacingString);
    return true;

}

int main(int argc, char*argv[])
{
  Matlab matlab;
string s ="[[1.2 2.4 ; 3.2 , 1.1]  [2.6 0;2 4]]";
   string r="[1.2 3.2],[2.2];[2.0 2.0 2.0]";
    string A="[[1.2 3.2], [2.2] \n [2.0 2.0 2.0] ]";
  /* expected output
    1.20000   2.40000   2.60000   0.00000
   3.20000   1.10000   2.00000   4.00000

   found : 1.2 2.4
           2    4

  */
    //cout<<matlab.getInstructionWithoutConcatenation(r);
cout<<test(A)<<endl;


//stressTesting();//


    return 0;
}

