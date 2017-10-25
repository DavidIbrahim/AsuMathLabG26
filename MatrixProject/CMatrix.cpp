
#include"CMatrix.h"
#include <iomanip>
#include<iostream>


CMatrix::CMatrix()
{
	nR = nC = 0;
	values = NULL;
}
CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue)
{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0)
	{
		values = NULL;
		return;
	}
	values = new double*[nR];
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new double[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			switch (initialization)
			{
			case MI_ZEROS:values[iR][iC] = 0; break;
			case MI_ONES: values[iR][iC] = 1; break;
			case MI_EYE: values[iR][iC] = (iR == iC) ? 1 : 0; break;
			case MI_RAND: values[iR][iC] = (rand() % 1000000) / 1000000.0; break;
			case MI_VALUE:values[iR][iC] = initializationValue; break;
			}
		}
	}
}
CMatrix::CMatrix(CMatrix& m)
{
	nR = nC = 0;
	values = NULL;
	copy(m);
}
CMatrix::CMatrix(string s)
{
	nR = nC = 0;
	values = NULL;
	//copy(s);
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

CMatrix :: ~CMatrix()
{
	reset();
}

void CMatrix::copy(CMatrix& m)
{
	reset();
	this->nR = m.nR;
	this->nC = m.nC;
	if ((nR*nC) == 0) { values = NULL; return; }
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

string CMatrix::getString() {
	string s;
	for (int iR = 0; iR<nR; iR++)
	{
		for (int iC = 0; iC<nC; iC++)
		{
			char buffer[50]; sprintf_s(buffer, 50, "%g\t", values[iR][iC]);
			s += buffer;
		}
		s += "\n";
	}
	return s;
}
void CMatrix::reset() {
	if (values) { 
		for (int i = 0; i<nR; i++) 
			delete[] values[i]; 
		delete[] values; 
	}
	nR = nC = 0; values = NULL;
}


