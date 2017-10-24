#include<stdio.h>
#include <iostream>
#include"CMatrix.h"

using namespace std;
int main(){ 

	CMatrix C = CMatrix (3, 3,CMatrix :: MI_VALUE, 5);
  cout<<C.getString();
  return 0;
}
