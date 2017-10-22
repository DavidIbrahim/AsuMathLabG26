//Const and dest
#include"CMatrix.h"
#include<iostream>

using namespace std;

CMatrix :: CMatrix ()
{
nR = nC = 0;
values = NULL;
}

CMatrix :: ~CMatrix ()
{
reset();
}
CMatrix :: CMatrix (int nR, int nC, int initialization, double initializationValue)
{
	this->nR = nR;
	this->nC = nC;
	if((nR*nC)==0)
	{
		values=NULL;
		return;
	}
	values = new double*[nR];
	for(int iR=0;iR<nR;iR++)
	{
		values[iR] = new double[nC];
		for(int iC=0;iC<nC;iC++)
		{
			switch(initialization)
			{
			case MI_ZEROS:values[iR][iC] = 0;break;
			case MI_ONES: values[iR][iC] = 1;break;
			case MI_EYE: values[iR][iC] = (iR==iC)?1:0;break; 
			case MI_RAND: values[iR][iC] = (rand()%1000000)/1000000.0;break;
			case MI_VALUE:values[iR][iC] = initializationValue;break;
			}
		}
	}
}
