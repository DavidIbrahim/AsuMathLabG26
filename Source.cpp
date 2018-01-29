#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"
#include <exception>
#include <typeinfo>
/*
struct MyException : public exception{
const char * what () const throw(){
return "error occured!";}};
*/
using namespace std;
int main(int argc, char*argv[])
{
    /*
    	ifstream infile ("//home//samuel//Documents//CodeBlocks//Phase1_linux//example.m");
    */
    try
    {

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
    bool echo = true;


    //ifstream infile("D:\\Users\\samue\\Documents\\Code Blocks\\Phase1\\example.m");

    while(getline(*in,s))
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
            {
                s.erase( i,1 );
                i--;
            }
            else break;


        }
        int l = s.length();

        Matlab m;
        string result;
        if(s[l-1]=='\r' || s[l-1]=='\n') s.erase(l-1); //fixing new line issue between Windows and Linux
        if(s=="")continue;
        //mat = s;
        // cout<<s<<endl;
        if(s.find('[')!= string::npos || mat_cont)
            mat_intit = true;
        else
            mat_intit = false;

        if(mat_intit) mat+=s;
        if((m.findTheClosingBracket(mat,'[')==string::npos) && mat_intit)
        {
            mat_cont = true;
        }
        else
            mat_cont =false;



        if(mat_intit)
        {

            if(mat[mat.length()-1]!=';'&&mat[mat.length()-1]!='[' && mat_cont) mat+=';';

        }




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

//cout<< mat<<endl;
            m = m.executeInstruction(mat,data);

            mat= "";

        }
        else if(s.find("=")==string::npos)
        {
            bool found = false;
            for (int i = 0; i<data.size(); i++)
            {

                if(data[i].getName()==s)
                {
                    data[i].print();
                    found = true;
                }
            }
            if(!found) cout<< "Undefined variable "<<s<<endl;
        }
        else
        {
            if(s[s.length()-1]== ';')
            {
                s.erase(s.length()-1);
                echo = false;
            }
            else echo = true;

            m = m.executeInstruction(s,data);





        }
        if(echo)
        {
            m.print();

        }

        mat= "";
    }
    CMatrix A ( "[1 2 3;4 5 6;7 8 9;]");
    Matlab m,n,k;
    m = m.executeInstruction("A = 5.5 + 12 * sin(0.4) + 2.2^4",data);
    m = m.executeInstruction("B = [1.2 2.3 A;[1.3 2.4;4.6 1.3],[3.2;7.8]]",data);
    m = m.executeInstruction("C = [[B [3.4; 2.1; 3.5+9.1]];1.2^3 3+1.2 15/(2.1+10*sin(0.12))  1.2]",data);
    m = m.executeInstruction("D = rand(4,4)",data);
    m = m.executeInstruction("Y = (C^3 * sin(1./D))^(0.1)",data);

    data[4].print();

    //n.executeInstruction("A = [8.9 7.3 4.8 2.4; 2.3 6.5 8.9 1.2; 4.9 3.8 7.2 7.5; 9.8 3.4 7.5 8.9]",data).print();
//n.executeInstruction("X = 5",data).print();
//n.executeInstruction("L = -8",data).print();
    //cout<<n.getStringValue("(1.2+3.4-5.6)/(2.1*3.2+4.6)-12.1*3.1+(1.2+5.2)^(4/(3.2+5.6))");
    //data[0].getString();

    //cout<<n.calcSimpleExpression("-12.1*3.1");
    //CMatrix *pb =0;
    //typeid(*pb);
    }

    catch(const char* error)
    {
        cout<<error<<endl;
    }
    catch(exception &e)
    {
        cout<< "exception caught: "<< e.what()<<endl;
    }
    return 0;
}

