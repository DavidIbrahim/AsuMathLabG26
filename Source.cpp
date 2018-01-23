#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"
#include<conio.h>

using namespace std;


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
void printVector( vector<Matlab>& myVector){
    for(int i =0; i<myVector.size(); i++) {
        cout<<myVector[i].getString()<<endl;
    }
}


int main(int argc, char*argv[])
{

CMatrix x ("[30 30;60 60]");

CMatrix y ;

/***********************************************************************************************************/
y = x.sin_element();
cout<<"for sin "<<y.getString()<<endl;

y = x.cos_element();
cout<<"for cos "<<y.getString()<<endl;

y = x.tan_element();
cout<<"for tan "<<y.getString()<<endl;

y = x.sinh_element();
cout<<"for sinh "<<y.getString()<<endl;

y = x.cosh_element();
cout<<"for cosh "<<y.getString()<<endl;

y = x.tanh_element();
cout<<"for tanh "<<y.getString()<<endl;

y = x.asin_element();
cout<<"for asin "<<y.getString()<<endl;

y = x.acos_element();
cout<<"for acos "<<y.getString()<<endl;

y = x.atan_element();
cout<<"for atan "<<y.getString()<<endl;

y = x.asinh_element();
cout<<"for asinh "<<y.getString()<<endl;

y = x.acosh_element();
cout<<"for acosh "<<y.getString()<<endl;

y = x.atanh_element();
cout<<"for atanh "<<y.getString()<<endl;

/************************************************************************************************************/


x = ("[30 30;60 60]");
/*************************************************************************************************************/
y = x.log_element();
cout<<"for log "<<y.getString()<<endl;

y = x.log10_element();
cout<<"for log10 "<<y.getString()<<endl;

y = x.exp_element();
cout<<"for exp "<<y.getString()<<endl;

y = x.expm1_element ();
cout<<"for expm1 "<<y.getString()<<endl;

y = x.log1p_element ();
cout<<"for log1p "<<y.getString()<<endl;

y = x.log2_element  ();
cout<<"for log2 "<<y.getString()<<endl;







/*************************************************************************************************************/
x = ("[-30 -30;-60 -60]");

y = x.abs_element();
cout<<"for abs "<<y.getString()<<endl;

x = ("[3.40 30.6;-60.4 -60.6]");

y = x.ceil_element  ();
cout<<"for ceil "<<y.getString()<<endl;

y = x.floor_element  ();
cout<<"for floor "<<y.getString()<<endl;

y = x.sqrt_element  ();
cout<<"for sqrt "<<y.getString()<<endl;


/*************************************************************************************************************/


x = ("[30 60.8;-6 -8.6]");


y = x. round_element();
cout<<"for round "<<y.getString()<<endl;
y = x.  erfc_element();
cout<<"for erfc "<<y.getString()<<endl;
y = x. erf_element();
cout<<"for erf "<<y.getString()<<endl;
y = x. lgamma_element();
cout<<"for lgamma "<<y.getString()<<endl;
y = x. cbrt_element();
cout<<"for cbrt "<<y.getString()<<endl;
y = x. isfinite_element();
cout<<"for isfinite "<<y.getString()<<endl;
y = x.isinf_element();
cout<<"for isinf "<<y.getString()<<endl;
y = x.isnan_element();
cout<<"for isnan "<<y.getString()<<endl;
y = x.signbit_element();
cout<<"for signbit "<<y.getString()<<endl;


/*************************************************************************************************************/

x = ("[30 60.8;-6 -8.6]");
CMatrix v  ("[1 2 33;2 1 33]");

y = x.dot_mult(v);
cout<<"for dot_mul "<<y.getString()<<endl;
y = x.dot_div1(v);
cout<<"for dot_div1 "<<y.getString()<<endl;
y = x.dot_div2(v);
cout<<"for dot_div2 "<<y.getString()<<endl;



/*************************************************************************************************************/


x = ("[2 2;2 2]");

//case0
y = x.power(-1);
cout<<"for power-1 "<<y.getString()<<endl;


//case1
y = x.power(5.5);
cout<<"for power double "<<y.getString()<<endl;



//case2
y = x.power(55);
cout<<"for power int "<<y.getString()<<endl;

/*************************************************************************************************************/
Matlab ttt;







cout<<"for checkInstructionForFunctions test "<<endl<<endl;
cout<<ttt.checkInstructionForFunctions("vdsbihbidb")<<endl;//0
cout<<ttt.checkInstructionForFunctions("sinbihbcosidb")<<endl;//1
cout<<ttt.checkInstructionForFunctions("vdsbicosidb")<<endl;//2
cout<<ttt.checkInstructionForFunctions("vdsbitanlidb")<<endl;//3
cout<<ttt.checkInstructionForFunctions("asinbihbcidb")<<endl;//4
cout<<ttt.checkInstructionForFunctions("vdsbiacosidb")<<endl;//5
cout<<ttt.checkInstructionForFunctions("vdsbiatanlidb")<<endl;//6
cout<<ttt.checkInstructionForFunctions("sinhbihbcidb")<<endl;//7
cout<<ttt.checkInstructionForFunctions("vdsbicoshidb")<<endl;//8
cout<<ttt.checkInstructionForFunctions("vdsbitanhlidb")<<endl;//9
cout<<ttt.checkInstructionForFunctions("asinhbihbcidb")<<endl;//10
cout<<ttt.checkInstructionForFunctions("vdsbiacoshidb")<<endl;//11
cout<<ttt.checkInstructionForFunctions("vdsbiatanhlidb")<<endl;//12
cout<<ttt.checkInstructionForFunctions("vdsbiabsdb")<<endl;//13
cout<<ttt.checkInstructionForFunctions("vdsbiceildb")<<endl;//14
cout<<ttt.checkInstructionForFunctions("vdsbifloordb")<<endl;//15
cout<<ttt.checkInstructionForFunctions("vdsbisqrtdb")<<endl;//16
cout<<ttt.checkInstructionForFunctions("vdsbilog db")<<endl;//18
cout<<ttt.checkInstructionForFunctions("vdsbilog10db")<<endl;//19
cout<<ttt.checkInstructionForFunctions("vdsbipowerdb")<<endl;//20
cout<<ttt.checkInstructionForFunctions("vdsbidb")<<endl;//0

cout<<"for extractStringInsideFunction test   "<<endl<<endl;
cout<<ttt.extractStringInsideFunction("vdsbihbidb")<<endl;//0
cout<<ttt.extractStringInsideFunction("sin(start test -1)bihbcosidb")<<endl;//1
cout<<ttt.extractStringInsideFunction("vdsbicos(here ;)idb")<<endl;//2
cout<<ttt.extractStringInsideFunction("vdsbitan (yoyo)lidb")<<endl;//3
cout<<ttt.extractStringInsideFunction("asin(now)bihbcidb")<<endl;//4
cout<<ttt.extractStringInsideFunction("vdsbiacos(are)idb")<<endl;//5
cout<<ttt.extractStringInsideFunction("vdsbiatan(we)lidb")<<endl;//6
cout<<ttt.extractStringInsideFunction("sinh(the re)bihbcidb")<<endl;//7
cout<<ttt.extractStringInsideFunction("vdsbicosh (yet)idb")<<endl;//8
cout<<ttt.extractStringInsideFunction("vdsbitanh (no)lidb")<<endl;//9
cout<<ttt.extractStringInsideFunction("asinh (they)bihbcidb")<<endl;//10
cout<<ttt.extractStringInsideFunction("vdsbiacosh(v(((are)))v)idb")<<endl;//11
cout<<ttt.extractStringInsideFunction("vdsbiatanh(((20)))lidb")<<endl;//12
cout<<ttt.extractStringInsideFunction("vdsbiabs(i)db")<<endl;//13
cout<<ttt.extractStringInsideFunction("vdsbiceil(am)db")<<endl;//14
cout<<ttt.extractStringInsideFunction("vdsbifloor(hate)db")<<endl;//15
cout<<ttt.extractStringInsideFunction("vdsbisqrt(testing)db")<<endl;//16
cout<<ttt.extractStringInsideFunction("vdsbiexp(what)db")<<endl;//17
cout<<ttt.extractStringInsideFunction("vdsbilog (about)db")<<endl;//18
cout<<ttt.extractStringInsideFunction("vdsbilog10(you)db")<<endl;//19
cout<<ttt.extractStringInsideFunction("vdsbipower(end test+1)db")<<endl;//20
cout<<ttt.extractStringInsideFunction("vdsbidb")<<endl;//0
cout<<"both functions had there first test you can add your own test"<<endl;//0

/*************************************************************************************************************/



  getch();


/*
Matlab x ;//-33333+5656+99+999-565-565-5656
string e = "99-356+985-8996+5632-965+545+51562-5566-3333-33333+5656+99+999-565-565-5656+5-55-55+100+3000-4000+200+200+200+200+200-200-200-200+2000+200-20000-2*-2+2-2-4000+200+200+200+200+200-200-200-200+2000+200-20000";
//cout<<x.checkStringForMatrix(e)<<"here"<<endl;
cout<<x.calcSimpleExpression(e)<<endl;
e = "8+2";
cout<<x.calcSimpleExpression(e)<<endl;
e = "8-2";
cout<<x.calcSimpleExpression(e)<<endl;
e = "-8+2";
cout<<x.calcSimpleExpression(e)<<endl;
e = "-8-2";
cout<<x.calcSimpleExpression(e)<<endl;
e = "-8-2+2*2";
cout<<x.calcSimpleExpression(e)<<endl;
*/
    /*  a brief example on how to use vectors  */
    vector<Matlab> myVector;   //initialized a vector  for matlab objects
    CMatrix m("[1 2 3;4 5 6]");// initialized a matrix  m
    myVector.push_back( Matlab("A",m));// put a new Matlab object with name A and matrix m in myVector;
    cout<<myVector[0].getString()<<endl;// the same as array myVector[0] will return the firstMatlab object pushed in myVector
   /*           Now I will add another Matlab objects for u to test           */
    myVector.push_back(Matlab("luffy",CMatrix("[1 2 3 ; 4 5 6 ; 7 8 9]")));
    myVector.push_back(Matlab("x",CMatrix("[0 0 0 0 ; 0 0 0 0 ; 0 0 0 0]")));
    cout<<endl<<"printing the Matlab Objects in the Vector"<<endl<<endl;
    printVector(myVector);
    return 0;
}
