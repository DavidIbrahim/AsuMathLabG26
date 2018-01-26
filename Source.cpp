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
int main(int argc, char*argv[])
{
    /*
    	ifstream infile ("//home//samuel//Documents//CodeBlocks//Phase1_linux//example.m");
    */
    bool file_input = false;
    istream* in = &cin;
    ifstream infile;
    if (argc == 2)
    {
        infile.open(argv[1]);
        in = &infile;
        file_input = true;
    }

    vector<Matlab> data;
    string s;
    string mat ="";
    bool mat_intit = false;
    bool mat_cont = false;
    bool echo = false;


    //ifstream infile("D:\\Users\\samue\\Documents\\Code Blocks\\Phase1\\example.m");

    while(getline(*in,s))
    {
        int l = s.length();

        Matlab m;
        if(s[l-1]=='\r' || s[l-1]=='\n') s.erase(l-1); //fixing new line issue between Windows and Linux
        if(s=="")continue;
        //mat = s;
        // cout<<s<<endl;
        if(s.find('[')!= string::npos || mat_cont)
            mat_intit = true;
        else
            mat_intit = false;


        if(mat_intit)
        {
            mat+=s;
            if(mat[mat.length()-1]!=';'&&mat[mat.length()-1]!='[') mat+=';';

        }

        if((m.findTheClosingBracket(mat,'[')==string::npos) && mat_intit)
        {
            mat_cont = true;
        }
        else
            mat_cont =false;


        if(mat_cont)continue;
        //if(mat_cont) continue;

        if (mat.length() >0)
        {
            //cout<<mat<<endl;
            if(mat[mat.length()-1]== ';')
            {
                mat.erase(mat.length()-1);
                echo = false;
            }
            else echo = true;

cout<< mat<<endl;
            mat= "";

        }
        else if(s.find("=")==string::npos)
        {
            Matlab::getMatlabFromVector(s,data).getString();
        }
        else
        {
            if(s[s.length()-1]== ';')
            {
                s.erase(s.length()-1);
                echo = false;
            }
            else echo = true;

if(echo)
{


}


cout<<s<<endl;

}


}
    CMatrix A ( "[1 2 3;4 5 6;7 8 9;]");
    cout<<A.getString();
    return 0;
}
