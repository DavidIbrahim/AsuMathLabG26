#include<stdio.h>
#include <iostream>
#include"CMatrix.h"

using namespace std;
int main(){



 CMatrix z;
 CMatrix x("[6 5 4;3 2 1]");
 CMatrix y("[1 2 3;4 5 6]");
 z = "[0 2 4;4 5 6]";
 cout<< "z =\n\n" << z.getString() << "\nx =\n\n" << x.getString() << "\ny =\n\n" << y.getString();
	 z= y+x;
	cout<< "\nz= x+y\n\n" << z.getString();

//////////////////////////////////////////////////////////////////
CMatrix f(x);

	 z=++f;
	 cout<<"\nf=x\nz = ++f\nz=\n\n"<<z.getString()<<endl<<"f=\n\n"<<f.getString() ;

//////////////////////////////////////////////////////////////////
	 CMatrix a(x);
	 z =a++;
	 cout<<"\na=x\nz = a++\nz=\n\n"<<z.getString()<<endl<<"a=\n\n"<<a.getString()<< endl ;

//////////////////////////////////////////////////////////////////
	 CMatrix b(x);
	 z =b--;
	 cout<<"\nb=x\nz = b--\nz=\n\n"<<z.getString()<<endl<<"b=\n\n"<<b.getString()<< endl ;

//////////////////////////////////////////////////////////////////
	 CMatrix c(x);
	 z =--c;
	 cout<<"\nc=x\nz = --c\nz=\n\n"<<z.getString()<<endl<<"c=\n\n"<<c.getString()<< endl ;

//////////////////////////////////////////////////////////////////

	 z = x.getCofactor(1,1);
	 cout<< "z= x.getCofactor(1,1)\nz=\n\n" << z.getString()<<endl<<"x=\n\n"<<x.getString() ;
//////////////////////////////////////////////////////////////////
	z = x;
	z+=y;
	cout<<"\nz= x\nz+=y\n\n"<<z.getString() ;
//////////////////////////////////////////////////////////////////
	z = -x;
	cout<<"\nz= -x\n\n"<<z.getString() ;
//////////////////////////////////////////////////////////////////
	z/=1;
	cout<< "\nz/=1\n\n" << z.getString() ;
/////////////////////////////////////////////////////////////////
	z = x;
	z.reset();
	cout<<z.getString() ;

	return 0;
}
