
#include "CMatrix.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

CMatrix::CMatrix() {
  nR = nC = 0;
  values = NULL;
}

CMatrix::CMatrix(int nR, int nC, int initialization,
                 double initializationValue) {
  this->nR = nR;
  this->nC = nC;
  if ((nR * nC) == 0) {
    values = NULL;
    return;
  }

  values = new double *[nR];
  // Random seed
  srand(time(NULL));
  for (int iR = 0; iR < nR; iR++) {
    values[iR] = new double[nC];
    for (int iC = 0; iC < nC; iC++) {
      switch (initialization) {
      case MI_ZEROS:
        values[iR][iC] = 0;
        break;
      case MI_ONES:
        values[iR][iC] = 1;
        break;
      case MI_EYE:
        values[iR][iC] = (iR == iC) ? 1 : 0;
        break;
      case MI_RAND:
        values[iR][iC] = (rand() % 1000000) / 1000.0;
        break;
      case MI_VALUE:
        values[iR][iC] = initializationValue;
        break;
      }
    }
  }
}

void CMatrix::setSubMatrix(int r, int c, CMatrix &m) {
  if ((r + m.nR) > nR || (c + m.nC) > nC)
    throw("Invalid matrix dimension");
  for (int iR = 0; iR < m.nR; iR++)
    for (int iC = 0; iC < m.nC; iC++)
      values[r + iR][c + iC] = m.values[iR][iC];
}

CMatrix::CMatrix(string s) {
  nR = nC = 0;
  values = NULL;
  copy(s);
}
CMatrix CMatrix::operator=(string s) {
  copy(s);
  return *this;
}
void CMatrix::copy(string s) {
  reset();
  char *buffer = new char[s.length() + 1];
  strcpy(buffer, s.c_str());
  char *lineContext;
  const char *lineSeparators = ";\r\n";
  char *line = strtok(buffer, lineSeparators);
  char* remainlines = strtok(NULL, "");

  while (line) {
    CMatrix row;
    char *context;
    const char *separators = " []";
    char *token = strtok(line, separators);
    while (token) {
      CMatrix item(atof(token));
      row.addColumn(item);
      token = strtok(NULL, separators);
    }
    if (row.nC > 0 && (row.nC == nC || nR == 0))
      addRow(row);
    line = strtok(remainlines, lineSeparators);
    remainlines = strtok(NULL,"");
  }
  delete[] buffer;
}
///
CMatrix::CMatrix(double d) {
  nR = nC = 0;
  values = NULL;
  copy(d);
}

void CMatrix::addColumn(CMatrix &m) {
  CMatrix n(max(nR, m.nR), nC + m.nC);
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(0, nC, m);
  *this = n;
}

void CMatrix::addRow(CMatrix &m) {
  CMatrix n(nR + m.nR, max(nC, m.nC));
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(nR, 0, m);
  *this = n;
}
CMatrix::CMatrix(CMatrix &m) {
  nR = nC = 0;
  values = NULL;
  copy(m);
}

CMatrix CMatrix::operator=(double d) {
  copy(d);
  return *this;
}
void CMatrix::operator+=(double d) {
  CMatrix C(nR, nC, MI_VALUE, d);
  add(C);
}
double CMatrix::getDeterminant() //(waiting)
{
  if (nR != nC)
    throw("Invalid matrix dimension");
  if (nR == 1 && nC == 1)
    return values[0][0];
  double value = 0, m = 1;
  for (int iR = 0; iR < nR; iR++) {
    //	value += m * values[0][iR] * getCofactor(0,iR).getDeterminant(); m *=
    //-1;
  }
  return value;
}

CMatrix CMatrix::operator+(CMatrix &m) {
  CMatrix r = *this;
  r += m;
  return r;
}
istream& operator >> (istream &is, CMatrix& m) { string s; getline(is, s, ']'); s+="]";
m = CMatrix(s);
return is;
}

ostream& operator << (ostream &os, CMatrix& m) { os<<m.getString(); return os; }
void CMatrix::operator-=(CMatrix &m) //(waiting)
{
  // sub(m);
}
/*

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
*/
void CMatrix::copy(double d) {
  reset();
  this->nR = 1;
  this->nC = 1;
  values = new double *[1];
  values[0] = new double[1];
  values[0][0] = d;
}

CMatrix::~CMatrix() { reset(); }

void CMatrix::copy(const CMatrix &m) {
  reset();
  this->nR = m.nR;
  this->nC = m.nC;
  if ((nR * nC) == 0) {
    values = NULL;
    return;
  }
  values = new double *[nR];
  for (int iR = 0; iR < nR; iR++) {
    values[iR] = new double[nC];
    for (int iC = 0; iC < nC; iC++) {
      values[iR][iC] = m.values[iR][iC];
    }
  }
}

string CMatrix::getString() {
  string s;
  for (int iR = 0; iR < nR; iR++) {
    for (int iC = 0; iC < nC; iC++) {
      char buffer[200];
      sprintf(buffer, "%g\t", values[iR][iC]);
      s += buffer;
    }
    s += "\n";
  }
  return s;
}

void CMatrix::reset() {
  if (values) {
    for (int i = 0; i < nR; i++)
      delete[] values[i];
    delete[] values;
  }
  nR = nC = 0;
  values = NULL;
}

void CMatrix::add(const CMatrix &m) {
  if (nR != m.nR || nC != m.nC)
    throw("Invalid matrix dimension");
  for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++)
      values[iR][iC] += m.values[iR][iC];
}

CMatrix CMatrix::operator=(const CMatrix &m) {
  copy(m);
  return *this;
}
void CMatrix::operator/=(double d) {
  for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++)
      values[iR][iC] /= d;
}
/*
void CMatrix::addColumn(CMatrix& m) {
        CMatrix n(max(nR, m.nR), nC+m.nC);
        n.setMatrix(0, 0, *this);
        n.setMatrix(0, nC, m);
        *this = n;
}
*/
CMatrix CMatrix::operator--() {
  add(CMatrix(nR, nC, MI_VALUE, -1.0));
  return *this;
}
CMatrix CMatrix::operator--(int) {
  CMatrix r = *this;

  add(CMatrix(nR, nC, MI_VALUE, -1.0));
  return r;
}

// tested
CMatrix CMatrix::operator-() {
  CMatrix C = *this;
  for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++)
      C.values[iR][iC] = -values[iR][iC];
  return C;
}

CMatrix CMatrix::operator++() {
  CMatrix C(nR, nC, MI_VALUE, 1.0);
  add(C);
  return *this;
}

/*
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
*/
void CMatrix::operator+=(CMatrix &m) // tested
{
  add(m);
}
/*
/*CMatrix CMatrix :: operator-(CMatrix& m)// this function needs (-=)operator to
work
{
        CMatrix r = *this;
        r-=m;
        return r;
}
/*CMatrix CMatrix::operator*(double d)//this function needs (*=) operator to
work
{
        CMatrix r = *this;
        r*=d;
        return r;
}
CMatrix CMatrix::operator/ (double d)
{
        CMatrix r = *this;
        r/=d;
        return r;
}*/
CMatrix CMatrix::operator++(int) {
  CMatrix C = *this;
  add(CMatrix(nR, nC, MI_VALUE, 1.0));
  return C;
}
CMatrix CMatrix::getCofactor(int r,
                             int c) // r and c represents the index of the
//	element that we want to find its cofactor//tested
{
  if (nR <= 1 && nC <= 1)
    throw("Invalid matrix dimension");
  CMatrix m(nR - 1, nC - 1);
  for (int iR = 0; iR < m.nR; iR++)
    for (int iC = 0; iC < m.nC; iC++) {
      int sR = (iR < r) ? iR : iR + 1;
      int sC = (iC < c) ? iC : iC + 1;
      m.values[iR][iC] = values[sR][sC];
    }
  return m;
}

/*
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
                                r.values[iR][iC] += values[iR][k] *
m.values[k][iC];
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
                                r.values[iR][iC] += values[iR][k] /
m.values[k][iC];
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
*/
