//Const and dest
//rogina is HERE 
#include"CMatrix.h"
#include<iostream>

using namespace std;

CMatrix :: CMatrix ()
{
nR = nC = 0;
values = NULL;
}
CMatrix::CMatrix(CMatrix& m)
{ nR = nC = 0;
values = NULL;
copy(m);
}
CMatrix::CMatrix(string s)
{ nR = nC = 0;
values = NULL;
copy(s);
}
CMatrix::CMatrix(double d)
{
	nR = nC = 0;
	values = NULL;
	copy(d);
}
void CMatrix::copy(double d)
{
	reset();
	this->nR = 1;
	this->nC = 1;
	values = new double*[1];
	values[0] = new double[1];
	values[0][0] = d;
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
void CMatrix::copy(CMatrix& m)
{
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if ((nR*nC) == 0){ values = NULL; return; }
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			values[iR][iC] = m.values[iR][iC];
		}
	}
}
