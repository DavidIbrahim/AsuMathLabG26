#include<stdio.h>
#include <iostream>
#include"CMatrix.h"

using namespace std;
int main(){ 

	CMatrix D = CMatrix (3, 3,CMatrix :: MI_VALUE, 5);
	CMatrix C = CMatrix(5);
	CMatrix z(2,3,CMatrix :: MI_VALUE,3);
	cout<<z.getnR()<<endl;
	cout<<z.getn()<<endl;
	cout<<z.getnC()<<endl;
	z = D;
	cout<<z.getnR()<<endl;

	z/=3;
	D=-z;
	cout<<z.getString();
  return 0;
}
