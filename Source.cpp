#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"
#include "conio.h"



using namespace std;
int main(int argc, char*argv[])
{
    CMatrix q("[1 2;1 2]") ;

    cout<<q.getString();
    CMatrix v ;

    v = q.power(3);
    cout<<v.getString();

    Matlab x;
    string s="s s s [ [here no problem    at all ]]          hq               [ [here 2] ]  herenoway  [why ]  [ not  ] +[here]";
     cout<<s<<endl;
    x.trimAllSpacesExceptMatrix(s);
     cout<<s<<endl;
     getch();
    cout<<x.solvetrignometry("8-sqrt(2+2)+cos(5)+8")<<endl;


   //  x.findTheClosingBracketFromAspecificPostion( "85", 5,'[');





/*
CComplex a(1,0);
  cout<<a.getString(1);
CComplex l = a.power(-.2);
  cout<<l.getString(0);
*/










    getch();
    //Matlab x;
    //cout<<x.getStringMatrix("[[2 5] [2 5] [2 5]]");




    return 0;
}
