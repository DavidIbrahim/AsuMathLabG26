
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

//Waiting for copy(string) implementation to test
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

void CMatrix::add(CMatrix& m) {
	if(nR!=m.nR||nC!=m.nC) 
		throw("Invalid matrix dimension");
	for(int iR=0;iR<nR;iR++) 
		for(int iC=0;iC<nC;iC++) 
			values[iR][iC] += m.values[iR][iC];
}

CMatrix CMatrix::operator=(CMatrix& m) { 
	copy(m); 
	return *this; 
}
void CMatrix::operator/=(double d) {
	for(int iR=0;iR<nR;iR++) 
		for(int iC=0;iC<nC;iC++) 
			values[iR][iC] /=d;
}

/*void CMatrix::addColumn(CMatrix& m) { 
	CMatrix n(max(nR, m.nR), nC+m.nC); 
	n.setMatrix(0, 0, *this); 
	n.setMatrix(0, nC, m); 
	*this = n; 
}*/

CMatrix CMatrix::operator--() { 
	add(CMatrix(nR, nC, MI_VALUE, -1.0));
	return *this; 
} 
CMatrix CMatrix::operator--(int) 
{ 
	CMatrix r = *this; 
	add(CMatrix(nR, nC, MI_VALUE, -1.0));
	return r;
}

//still need to check its functionality
CMatrix CMatrix::operator-() {
	for(int iR=0;iR<nR;iR++) 
		for(int iC=0;iC<nC;iC++) 
			values[iR][iC] = -values[iR][iC];
	return *this;
}

CMatrix CMatrix::operator++() { 
	add(CMatrix(nR, nC, MI_VALUE, 1.0));
	return *this; 
} 


//r and c are the beginning of where you want ur subMatrix
// nr and nc are the size of the subMatrix
CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc) {
	if((r+nr)>nR || (c+nc)>nC)
		throw("Invalid matrix dimension"); 
	CMatrix m(nr, nc); 
	for(int iR=0;iR<m.nR;iR++) 
		for(int iC=0;iC<m.nC;iC++) 
			m.values[iR][iC] = values[r+iR][c+iC]; 
	return m; 
}

void CMatrix::mul(CMatrix& m)
{
	if (nC != m.nR)
		throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);

	for (int iR = 0; iR<r.nR; iR++)
		for (int iC = 0; iC<r.nC; iC++)
		{
			r.values[iR][iC] = 0;
			for (int k = 0; k<m.nC; k++)
				r.values[iR][iC] += values[iR][k] * m.values[k][iC];
		}
	copy(r);
}
void CMatrix::operator*=(CMatrix& m)
{
	mul(m);
}
void CMatrix::operator*=(double d)
{
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			values[iR][iC] *= 9;
}
CMatrix CMatrix::operator*(CMatrix& m)
{
	CMatrix r = *this;
	r *= m;
	return r;
}
CMatrix CMatrix::operator*(double d)
{
	CMatrix r = *this;
	r *= d;
	return r;
}

void CMatrix::div(CMatrix& m)
{
	if (nC != m.nR)
		throw("Invalid matrix dimension");
	CMatrix r(nR, m.nC);

	for (int iR = 0; iR<r.nR; iR++)
		for (int iC = 0; iC<r.nC; iC++)
		{
			r.values[iR][iC] = 0;
			for (int k = 0; k<m.nC; k++)
				r.values[iR][iC] += values[iR][k] / m.values[k][iC];
		}
	copy(r);
}
void CMatrix::operator/=(CMatrix& m)
{
	div(m);
}
void CMatrix::operator/=(double d)
{
	for (int iR = 0; iR<nR; iR++)
		for (int iC = 0; iC<nC; iC++)
			values[iR][iC] /= 9;
}
CMatrix CMatrix::operator/(CMatrix& m)
{
	CMatrix r = *this;
	r /= m;
	return r;
}
CMatrix CMatrix::operator/(double d)
{
	CMatrix r = *this;
	r /= d;
	return r;
}