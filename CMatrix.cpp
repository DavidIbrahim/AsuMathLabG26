#include <fstream>
#include "CMatrix.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>

CMatrix::CMatrix() {
  nR = nC = 0;
  values = NULL;
}



CMatrix::CMatrix(int nR, int nC, int initialization,
                 CComplex initializationValue) {
  this->nR = nR;
  this->nC = nC;
  if ((nR * nC) == 0) {
    values = NULL;
    return;
  }

  values = new CComplex *[nR];
  // Random seed
  srand(time(NULL));
  for (int iR = 0; iR < nR; iR++) {
    values[iR] = new CComplex[nC];
    for (int iC = 0; iC < nC; iC++) {
      switch (initialization) {
      case MI_ZEROS:
        values[iR][iC] = CComplex(0);
        break;
      case MI_ONES:
        values[iR][iC] = CComplex(1);
        break;
      case MI_EYE:
        values[iR][iC] = (iR == iC) ? CComplex(1) : CComplex(0);
        break;
      case MI_RAND:



        values[iR][iC] = CComplex( (rand() % (100-1))/20.0);


        break;
      case MI_VALUE:
        values[iR][iC] = initializationValue;
        break;
      }
    }
  }
}

void CMatrix::setSubMatrix(int r, int c, CMatrix &m) {/////////////////////////////////////////
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
CMatrix CMatrix::operator=(string s) {///////////////////////////////////////////////
  copy(s);
  return *this;
}

void CMatrix::copy(string s) {
  reset();
  char *buffer = new char[s.length() + 1];
  strcpy(buffer, s.c_str());
  const char *lineSeparators = ";\r\n";
  char *line = strtok(buffer, lineSeparators);
  char *remainlines = strtok(NULL, "");

  while (line) {
    CMatrix row;
    const char *separators = " [],";
    char *token = strtok(line, separators);
    while (token) {
      CMatrix item(1,1,MI_VALUE,CComplex(token));
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

CMatrix::CMatrix(double d) {//draft 94
  nR = nC = 0;
  values = NULL;
  copy(d);
}
CMatrix::CMatrix(const CComplex c){
  nR = nC = 0;
  values = NULL;
  copy(c);
}
void CMatrix::copy(const CComplex c) {
  reset();
  this->nR = 1;
  this->nC = 1;
  values = new CComplex *[1];
  values[0] = new CComplex[1];
  values[0][0] = c;
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

CMatrix::CMatrix(const CMatrix &m) { //draft 113
  nR = nC = 0;
  values = NULL;
  copy(m);
}
CMatrix CMatrix::operator=(double d) { //draft 119
  copy(d);
  return *this;
}
void CMatrix::operator+=(double d) {
  CMatrix C(nR, nC, MI_VALUE, CComplex(d));
  add(C);
}

CMatrix CMatrix::operator+(CMatrix &m) {//draft 139
  CMatrix r = *this;
  r += m;
  return r;
}

istream& operator >> (istream &is, CMatrix& m) { string s; getline(is, s, ']'); s+="]";
m = CMatrix(s);
return is;
}

ostream& operator << (ostream &os, CMatrix& m) { os<<m.getString(); return os; }

void CMatrix::operator-=(CMatrix &m)
{
   sub(m);
}

CMatrix operator/(double d,CMatrix &m){

    CMatrix ans(m.nR,m.nC);
    for (int iR = 0; iR<m.nR; iR++)
        for (int iC = 0; iC<m.nC; iC++){
            CComplex X=CComplex(d);
        ans.values[iR][iC] = X/m.values[iR][iC];
    }
    return ans;
}

CMatrix CMatrix:: operator-(CMatrix &m){
    CMatrix r=*this;
    r.sub(m);
    return r;
}

void CMatrix::copy(double d) {//draft 171
  reset();
  this->nR = 1;
  this->nC = 1;
  values = new CComplex *[1];
  values[0] = new CComplex[1];
  values[0][0] = CComplex(d);
}

CMatrix::~CMatrix() { reset(); }

void CMatrix::copy(const CMatrix &m) { //draft 182
  reset();
  this->nR = m.nR;
  this->nC = m.nC;
  if ((nR * nC) == 0) {
    values = NULL;
    return;
  }
  values = new CComplex *[nR];
  for (int iR = 0; iR < nR; iR++) {
    values[iR] = new CComplex[nC];
    for (int iC = 0; iC < nC; iC++) {
      values[iR][iC] = m.values[iR][iC];
    }
  }
}

string CMatrix::getString() { //draft 199
  string s;
  bool isReal=this->isReal();
      for (int iR = 0; iR < nR; iR++) {
        for (int iC = 0; iC < nC; iC++) {
          s += values[iR][iC].getString(isReal);
          s += "\t";
        }
        s += "\n";
      }
  return s;
}

void CMatrix::reset() { //draft 212
  if (values) {
    for (int i = 0; i < nR; i++)
      delete[] values[i];
    delete[] values;
  }
  nR = nC = 0;
  values = NULL;
}

void CMatrix::add(const CMatrix &m) { //draft 222
    CMatrix x = m;

  if (nR != m.nR || nC != m.nC)
    throw("Invalid matrix dimension");
  for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++)
      values[iR][iC] += m.values[iR][iC];
}

CMatrix CMatrix::operator=(const CMatrix &m) { //draft 230
  copy(m);
  return *this;
}

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
CMatrix CMatrix::operator-() {//////////////////////////////////////
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

CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{//r and c are the beginning of where you want ur subMatrix
 // nr and nc are the size of the subMatrix
        if((r+nr)>nR || (c+nc)>nC)
                throw("Invalid matrix dimension");
        CMatrix m(nr, nc);
        for(int iR=0;iR<m.nR;iR++)
                for(int iC=0;iC<m.nC;iC++)
                        m.values[iR][iC] = values[r+iR][c+iC];
        return m;
}

void CMatrix::operator+=(CMatrix &m) //draft 281
{
  add(m);
}
CMatrix CMatrix::operator++(int) {
  CMatrix C = *this;
  add(CMatrix(nR, nC, MI_VALUE, 1.0));
  return C;
}

CMatrix CMatrix::getCofactor(int r, int c)
{
    // r and c represents the index of the
    //element that we want to find its cofactor//tested
    if (nR <= 1 && nC <= 1)
        throw("Invalid matrix dimension");
    CMatrix m(nR - 1, nC - 1);
    for (int iR = 0; iR < m.nR; iR++)
        for (int iC = 0; iC < m.nC; iC++)
        {
            int sR = (iR < r) ? iR : iR + 1;
            int sC = (iC < c) ? iC : iC + 1;
            m.values[iR][iC] = values[sR][sC];
        }
    return m;
}

void CMatrix::sub(const CMatrix& m){ //tested and works - tuna
    if(nR!=m.nR||nC!=m.nC)
        throw("Invalid matrix dimension");
    for(int iR=0;iR<nR;iR++)
        for(int iC=0;iC<nC;iC++)
        values[iR][iC] -= m.values[iR][iC];
    }

void CMatrix::operator-=(double d){ //tested and works - tuna
    CMatrix x(nR,nC,MI_VALUE,d);
    sub(x);
    }
CMatrix CMatrix::operator+(double d){ //tested and works - tuna //draft 320
    CMatrix r = *this;
    r+=d;
    return r;
}
CMatrix CMatrix::operator-(double d){ //tested and works - tuna
    CMatrix r = *this;
    r-=d;
    return r;
    }

CMatrix CMatrix::getTranspose(){      //CMatrix in UML, void in header file!!
    if(nR==1&&nC==1){
        CMatrix m(values[0][0]);
        return m;
    }
    CMatrix m(nC, nR);

    for(int iR=0;iR<m.nR;iR++)
        for(int iC=0;iC<m.nC;iC++)
            m.values[iR][iC] = values[iC][iR];

    return m;
}

CMatrix CMatrix::getInverse(){
    if (nR != nC)
        throw("Invalid matrix dimension");
    CComplex det =getDeterminant();
//  if (det==0)
//      throw("Matrix has no Inverse");

    CMatrix cof(nC , nR);//to find cofactor matrix
    CMatrix trans (nC,nR);//to find transpose of matrix
    CMatrix Inv (nC,nR);
    int sign=1;
    for(int i=0;i<nR;i++)
    {
        for(int j=0;j<nC;j++)
        {
            cof.values[i][j]=CComplex(sign)*getCofactor(i,j).getDeterminant();
            sign*=-1;
        }
        if(nC%2==0) sign *= -1;
    }

    for(int i=0;i<nR;i++)
        for(int j=0;j<nC;j++)
            Inv.values[i][j]=cof.values[j][i] / det;

    return Inv;
}
void CMatrix::mul(const CMatrix& m)
{
        if (nC != m.nR)
                throw("Invalid matrix dimension");
        CMatrix r(nR, m.nC);

        for (int iR = 0; iR<r.nR; iR++)
                for (int iC = 0; iC<r.nC; iC++)
                {
                        r.values[iR][iC] = 0;
                        for (int k = 0; k<m.nR; k++)
                        {
                            r.values[iR][iC] += values[iR][k] *m.values[k][iC];
                        }

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
                        values[iR][iC] *= CComplex(d);
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
    CMatrix t;
    t=m.getInverse();
    mul(t);

//    if (nC != m.nR)
//        throw("Invalid matrix dimension");
//    CMatrix r(nR, m.nC);
//
//    for (int iR = 0; iR<r.nR; iR++)
//        for (int iC = 0; iC<r.nC; iC++)
//        {
//            r.values[iR][iC] = 0;
//            for (int k = 0; k<m.nC; k++)
//            r.values[iR][iC] += values[iR][k] / m.values[k][iC];
//        }
//    copy(r);
}
void CMatrix::operator/=(CMatrix& m)
{
        div(m);
}
/*void CMatrix::operator/=(double d)
{
        for (int iR = 0; iR<nR; iR++)
                for (int iC = 0; iC<nC; iC++)
                        values[iR][iC] /= CComplex(d);
}*/
void CMatrix::operator/=(double d) {
  for (int iR = 0; iR < nR; iR++)
    for (int iC = 0; iC < nC; iC++){
        CComplex x(d);
        values[iR][iC].div(x);
    }
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

string CMatrix::getString2(){

     if(nC==1 && nR==1)
     {
        return values[0][0];
     }
     string s="[";
     bool isReal=this->isReal();
     for (int iR = 0; iR < nR; iR++)
     {
            for (int iC = 0; iC < nC; iC++) {
                /*char buffer[200];
                sprintf(buffer, "%g ", values[iR][iC]);*/
                s += values[iR][iC].getString2()+" ";
            }
            s.erase(s.end()-1);
            s += ";";
     }
     s.erase(s.end()-1);//removes the last semicolon.
     s+="]";
     return s;

}

void CMatrix::writeMatrixInFile(string file) {

     std::ofstream out(file.c_str());
     out<<getString2();

     out.close();
}

//double CMatrix::getDeterminant2() //(waiting)
//{
//  if(nR!=nC)
//    throw("Invalid matrix dimension");
//  if(nR==1&&nC==1)return values[0][0];
//    double value = 0, m = 1;
//    for(int iR=0;iR<nR;iR++){
//         value+= m * values[0][iR] * getCofactor(0, iR).getDeterminant2();
//    m *= -1;
//    } return value;
//}
//double CMatrix::getDeterminant3(){
//
//    if(nR!=nC)
//    throw("Invalid matrix dimension");
//    if(nR==1) return(values[0][0]);
//    if(nR==2) return (values[0][0]*values[1][1]-values[0][1]*values[1][0]);
//    if (nR != nC)
//        throw("Invalid matrix dimension");
//   // CMatrix L(nR,nC);
//    CMatrix U(*this);
//    fixMatrix(U ,  -1,-1);
//   // double** l = L.values;
//    double** u = U.values;
//    double factor =0;
//   int i = 0, j = 0, k = 0;
//  double ans =1;
// if(checkIfZeroMatrix(U))return 0;
//
//  if(u[0][0]==0){
//    if(fixMatrix(U,0,0))
//       ans*=-1;
//  }
// if(u[0][0]!=1){
//    ans *= u[0][0];
//    double temp = u[0][0];
//    for(i=0; i<nC ; i++){
//        u[0][i]/=temp;
//    }
//  }
//   for(i= 0 ; i<nR;i++){
//
//         for(j = 0; j<i;j++){
//        if(u[j][j]==0){
//                CMatrix::fixMatrix(U,j,j)   ;
//                ans*=-1;
//                i-=2;
//                if(i<0) i=0;
//                break;
//              }
//        factor = u[i][j]/u[j][j];
//        for(k=0;k<nR;k++) {
//            if(factor==0)break;
//
//            double x = u[i][k]- (factor * u[j][k]);
//
//            if(x<0.000000000000001 && x>-0.00000000000001) x =0;
//
//            u[i][k]=x;
//            }
//    }
//   }
//   for(int i=0;i<nR; i++){
//        ans*=u[i][i];
//        if(ans==0) return ans;
//    }
//    return ans;
//
///*
//    for (i = 0; i < nR; i++)
//    {
//        for (j = 0; j < nR; j++)
//        {
//            if (j < i)
//                l[j][i] = 0;
//            else
//            {
//                l[j][i] = values[j][i];
//                for (k = 0; k < i; k++)
//                {
//                    l[j][i] = l[j][i] - l[j][k] * u[k][i];
//                }
//            }
//        }
//        for (j = 0; j < nR; j++)
//        {
//            if (j < i)
//                u[i][j] = 0;
//            else if (j == i)
//                u[i][j] = 1;
//            else
//            {
//                u[i][j] = values[i][j] / l[i][i];
//                for (k = 0; k < i; k++)
//                {
//                    u[i][j] = u[i][j] - ((l[i][k] * u[k][j]) / l[i][i]);
//                }
//            }
//        }
//    }
//
//    double ans =1;
//    cout<<U<<endl <<endl << L;
//    for(int i=0;i<nR; i++){
//        ans*=l[i][i];
//        if(ans==0) return ans;
//    }
//    return ans;
//*/
//}
//bool  CMatrix:: fixMatrix(CMatrix &m , int r,int c) {
//
//    int index =0;
//    static int fR=-1;
//    static int fC=-1;
//    static int fnR = 0;
//    if(r == -1 && c == -1){
//        fR=-1;
//        fC=-1;
//        return true;
//    }
//    if(r == fR && fC==c){
//        fnR-=1;
//    }
//    else {
//        fR = r ;
//        fC = c ;
//        fnR = m.nR;
//    }
//
//    for(int i = fnR-1; i>-1;i--){
//
//        if(i==r) continue;
//        if(m.values[r][i]!=CComplex(0)){
//                index = i;
//                break;
//        }
//    }
//    CComplex temp;
//    for(int j = 0 ; j<m.nC ; j++){
//                temp = m.values[j][c];
//                m.values[j][c] = m.values[j][index];
//                m.values[j][index] = temp;
//    }
//    return true;
//}
//bool CMatrix:: checkIfZeroMatrix(CMatrix &m){
//    bool zeroMatrix = false ;
//    for(int i = 0 ; i <m.nR ; i++){
//       for(int j = i+1; j<m.nR; j++ ){
//            if ((m.values[i][0]!=0 && m.values[j][0]==0)
//                ||(m.values[i][0]==0 && m.values[j][0]!=0)) continue;
//            CComplex factor = m.values[i][0]/m.values[j][0];
//            for(int k =1 ; k<m.nC ; k++){
//                zeroMatrix = true;
//                CComplex temp = m.values[i][k]/m.values[j][k];
//                if(!( (temp - factor) <CComplex(0.000000001) && (temp-factor)> - CComplex(0.000000001))){
//                    zeroMatrix = false;
//                    break;
//                }
//            }
//            if(zeroMatrix) return zeroMatrix;
//       }
//    }
//    for(int i = 0 ; i <m.nR ; i++){
//       for(int j = i+1; j<m.nR; j++ ){
//            if ((m.values[i][0]!=0 && m.values[j][0]==0)
//                ||(m.values[i][0]==0 && m.values[j][0]!=0)) continue;
//            CComplex factor = m.values[0][i]/m.values[0][j];
//            for(int k =1 ; k<m.nC ; k++){
//                zeroMatrix = true;
//                CComplex temp = m.values[k][i]/m.values[k][j];
//                if(!( (temp - factor) <0.000000001 && (temp-factor)> - 0.000000001)){
//                    zeroMatrix = false;
//                    break;
//                }
//            }
//            if(zeroMatrix) return zeroMatrix;
//       }
//    }
//return zeroMatrix;
//}

//function to getDeterminant (Intel research Paper)
CComplex CMatrix::getDeterminant(){


    int *ri = new int[nR];
    int i, j;

    CComplex det = CComplex(1.0);
    CMatrix M(*this);
    CComplex **m = M.values;

    //Initialize the pointer vector.
    for (i = 0 ; i < nR; i++)
        ri[i] = i;

    for (int p = 1 ; p <= nR - 1; p++)
    {
        // Find pivot element
        for (i = p + 1 ; i <= nR; i++)
        {
            if (m[ri[i-1]][p-1].magnitude() > m[ri[p-1]][p-1].magnitude())
            {
                // Switch the index for the p-1 pivot row if necessary.
                int t = ri[p-1];
                ri[p-1] = ri[i-1];
                ri[i-1] = t;
                det = -det;
            }
        }
        if (m[ri[p-1]][p-1] == CComplex(0))
        {// The matrix is singular.
                    return false;
        }
        // Multiply the diagonal elements.
        det = det * m[ri[p-1]][p-1];
        // Form multiplier.
        for (i = p + 1 ; i <= nR; i++)
        {
            m[ri[i-1]][p-1] /= m[ri[p-1]][p-1];
            // Eliminate [p-1].
            for (j = p + 1 ; j <= nR; j++)
                m[ri[i-1]][j-1] -= m[ri[i-1]][p-1] *m[ri[p-1]][j-1];
        }
    }
    det = det * m[ri[nR-1]][nR-1];
    return det;
}

/*****************************************************************************************************/

/** @brief this fn makes horizontal concatenation of 2 matrices
 *
 * @param m1 the first matrix
 * @param m2 the second matrix
 * @return the concatenated matrix
 *
 */

CMatrix CMatrix::horizontalConcatenation(CMatrix &m1,CMatrix &m2)
{
    if(m1.nR!=m2.nR)throw("invalid matrix dimension");
    CMatrix m(m1.nR,(m2.nC +m1.nC));

    for(int iR=0;iR<m1.nR;iR++)
    {
        for(int iC=0;iC<m1.nC;iC++)
            {m.values[iR][iC]= m1.values[iR][iC];}
    }
    for(int iR=0;iR<m2.nR;iR++)
        for(int iC=0;iC<m2.nC;iC++)
            m.values[iR][iC+m1.nC]= m2.values[iR][iC];
    return m;



}
/** @brief this fn makes vertical concatenation of 2 matrices
 *
 * @param m1 the first matrix
 * @param m2 the second matrix
 * @return the concatenated matrix
 *
 */
CMatrix CMatrix::verticalConcatenation(CMatrix &m1,CMatrix &m2)
{

    if(m1.nC!=m2.nC)throw("invalid matrix dimension");
    CMatrix m((m1.nR+m2.nR),m1.nC);

    for(int iR=0;iR<m1.nR;iR++)
    {
        for(int iC=0;iC<m1.nC;iC++)
            {m.values[iR][iC]= m1.values[iR][iC];}
    }
    for(int iR=0;iR<m2.nR;iR++)
        for(int iC=0;iC<m2.nC;iC++)
            m.values[iR+m1.nR][iC]= m2.values[iR][iC];
    return m;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///***********************************************************************************************************/


/** @brief this fn makes the sin dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with sin made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::sin_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=sin(values[iR][iC].real());//*cosh(values[iR][iC].imaginary());
          //  double I=sinh(values[iR][iC].real())*cos(values[iR][iC].imaginary());
          //  CComplex X(R,I);
            result.values[iR][iC] = R;
        }
        return result;
   }



/** @brief this fn makes the cos dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with cos made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::cos_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=cos(values[iR][iC].real())*cosh(values[iR][iC].imaginary());
            double I=sin(values[iR][iC].real())*sinh(values[iR][iC].imaginary());
            CComplex X(R,-I);
            result.values[iR][iC] = X;
        }
        return result;
   }


/** @brief this fn makes the tan dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with tan made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::tan_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=sin(2*values[iR][iC].real())/(cos(2*values[iR][iC].real())+cosh(2*values[iR][iC].imaginary()));
            double I=sinh(2*values[iR][iC].imaginary())/(cos(2*values[iR][iC].real())+cosh(2*values[iR][iC].imaginary()));
            CComplex X(R,I);
            result.values[iR][iC] = X;
        }
        return result;
   }


/** @brief this fn makes the sinh dot for each element in the matrix (the hypred functions)
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with sinh made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::sinh_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=sinh(values[iR][iC].real())*cos(values[iR][iC].imaginary());
            double I=cosh(values[iR][iC].real())*sin(values[iR][iC].imaginary());
            CComplex X(R,I);
            result.values[iR][iC] = X;
        }
        return result;
   }


/** @brief this fn makes the cosh dot for each element in the matrix (the hypred functions)
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with cosh made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::cosh_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=cosh(values[iR][iC].real())*cos(values[iR][iC].imaginary());
            double I=sinh(values[iR][iC].real())*sin(values[iR][iC].imaginary());
            CComplex X(R,I);
            result.values[iR][iC] = X;
        }
        return result;
   }


/** @brief this fn makes the tanh dot for each element in the matrix (the hypred functions)
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with tanh made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::tanh_element (void )
   {//tanh(z)=-i tan(iz)
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double I=sin(-2*values[iR][iC].imaginary())/(cos(-2*values[iR][iC].imaginary())+cosh(2*values[iR][iC].real()));
            double R=sinh(2*values[iR][iC].real())/(cos(-2*values[iR][iC].imaginary())+cosh(2*values[iR][iC].real()));
            CComplex X(R,-I);
            result.values[iR][iC] = X;
        }
        return result;
   }


///** @brief this fn makes the sin-1 dot for each element in the matrix
// *
// *  @param  the matrix that does the call ex: [30 30;60 60] //but practically the parameters are void
// *
// *  @return a matrix where each element with sin-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::asin_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = asin(values[iR][iC]);}
//        return result;
//   }
//
//
///** @brief this fn makes the cos-1 dot for each element in the matrix
// *
// *  @param  the matrix that does the call ex: [30 30;60 60] //but practically the parameters are void
// *
// *  @return a matrix where each element with cos-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::acos_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = acos(values[iR][iC]);}
//        return result;
//   }
//
///** @brief this fn makes the tan-1 dot for each element in the matrix
// *
// *  @param  the matrix that does the call ex: [30 30;60 60] //but practically the parameters are void
// *
// *  @return a matrix where each element with tan-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::atan_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = atan(values[iR][iC]);}
//        return result;
//   }
//
//
///** @brief this fn makes the sinh-1 dot for each element in the matrix (the hypred functions)
// *
// *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
// *
// *  @return a matrix where each element with sinh-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::asinh_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = asinh(values[iR][iC]);}
//        return result;
//   }
//
//
///** @brief this fn makes the cosh-1 dot for each element in the matrix (the hypred functions)
// *
// *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
// *
// *  @return a matrix where each element with cosh-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::acosh_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = acosh(values[iR][iC]);}
//        return result;
//   }
//
//
///** @brief this fn makes the tanh-1 dot for each element in the matrix (the hypred functions)
// *
// *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
// *
// *  @return a matrix where each element with tanh-1 made for it ex:
// *
// */
////this is according to oct.
//CMatrix  CMatrix::atanh_element (void )
//   {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = atanh(values[iR][iC]);}
//        return result;
//   }
//
//
///***********************************************************************************************************/

/** @brief this fn makes the abs dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [-30 -30;-60 -60]//but practically the parameters are void
 *
 *  @return a matrix where each element with abs made for it ex: [30 30;60 60]
 *
 */
//this is according to oct.
CMatrix CMatrix::abs_element   (void )
  {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(abs(values[iR][iC].real()),0);}
        return result;
  }

/** @brief
The ceil fn
Round up value
Rounds x upward, returning the smallest integral value that is not less than x in each element of matrix.

 *  @param  the matrix that does the call ex: [3.40 30.6;-60.4 -60.6]//but practically the parameters are void
 *
 *  @return a matrix where each element with abs made for it ex: [30 30;60 60]
 *
 */
//this is according to oct.
CMatrix CMatrix::ceil_element   (void )
 {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(ceil(values[iR][iC].real()),0);}
        return result;
 }

/** @brief
The floor fn

Round down value
Rounds x downward, returning the largest integral value that is not greater than x in each element of matrix.
 *  @param  the matrix that does the call ex: [3.40 30.6;-60.4 -60.6]//but practically the parameters are void
 *
 *  @return a matrix where each element with abs made for it ex: [30 30;60 60]
 *
 */
//this is according to oct.
CMatrix CMatrix::floor_element  (void )
  {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(floor(values[iR][iC].real()),0);}
        return result;


  }
/** @brief
The square root fn

Compute square root
Returns the square root of x in each element of matrix.
 *  @param  the matrix that does the call ex: [3.40 30.6;-60.4 -60.6]//but practically the parameters are void
 *
 *  @return a matrix where each element with abs made for it ex: [30 30;60 60]
 *
 */
//this is according to oct.
CMatrix CMatrix::sqrt_element  (void )
  {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(sqrt((values[iR][iC]).real()),0);}
        return result;
  }
///***********************************************************************************************************/
//
//
//
//
//
//
//
//
//
//
//
/** @brief this fn makes the exp dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with exp made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::exp_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
        {
            double R=cos(values[iR][iC].imaginary());
            double I=sin(values[iR][iC].imaginary());
            CComplex X(R,I);
            result.values[iR][iC] = X*exp(values[iR][iC].real());
        }
        return result;
   }



/** @brief this fn makes the log10 dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with log10 made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::log10_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(log10(values[iR][iC].real()),0);}
        return result;
   }


/** @brief this fn makes the log dot for each element in the matrix
 *
 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with log made for it ex:
 *
 */
//this is according to oct.
CMatrix  CMatrix::log_element (void )
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(log(values[iR][iC].real()),0);}
        return result;
   }

/** @brief Compute exponential minus one
Returns e raised to the power x minus one: ex-1.
For small magnitude values of x, expm1 may be more accurate than exp(x)-1.

 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with expm1 made for it ex:
 *
 */
//this is according to oct.
CMatrix CMatrix::expm1_element (void)
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(expm1(values[iR][iC].real()),0);}
        return result;

   }



/** @brief Compute logarithm plus one
Returns the natural logarithm of one plus x.

For small magnitude values of x, logp1 may be more accurate than log(1+x).

 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with log1p made for it ex:
 *
 */
//this is according to oct.
CMatrix CMatrix::log1p_element(void)
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(log1p(values[iR][iC].real()),0);}
        return result;

   }




/** @brief
Compute binary logarithm
Returns the binary (base-2) logarithm of x.


 *  @param  the matrix that does the call ex: [30 30;60 60]//but practically the parameters are void
 *
 *  @return a matrix where each element with log1p made for it ex:
 *
 */
//this is according to oct.
CMatrix CMatrix::log2_element(void)
   {
      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = CComplex(log2(values[iR][iC].real()),0);}
        return result;



   }


/***********************************************************************************************************/



///** @brief
//round
//Round to nearest
//Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
//
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::round_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = round(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//erfc
//Compute complementary error function
//complementary error function Returns the complementary error function value for x.
//
//The complementary error function is equivalent to:
//erfc(x) = 1-erf(x)
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::erfc_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = erfc(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//erf
//Compute error function
//error function Returns the error function value for x.
//
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::erf_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = erf(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//lgamma
//Compute log-gamma function
//log-gamma function Returns the natural logarithm of the absolute value of the gamma function of x.
//
//
//
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::lgamma_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = lgamma(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//cbrt
//
//Compute cubic root
//Returns the cubic root of x.
//
//
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::cbrt_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = cbrt(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//
//isfinite
//Is finite value
//Returns whether x is a finite value.
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::isfinite_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = isfinite(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//isinf
//
//Is infinity
//Returns whether x is an infinity value (either positive infinity or negative infinity).
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::isinf_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = isinf(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//isnan
//Is Not-A-Number
//Returns whether x is a NaN (Not-A-Number) value.
//
//The NaN values are used to identify undefined or non-representable values for floating-point elements, such as the square root of negative numbers or the result of 0/0.
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::isnan_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = isnan(values[iR][iC]);}
//        return result;
//
//
//  }
//
//
///** @brief
//signbit
//Returns whether the sign of x is negative.
//
//This can be also applied to infinites, NaNs and zeroes (if zero is unsigned, it is considered positive).
//
//
// *  @param  the matrix that does the call //but practically the parameters are void
// *
// *  @return a matrix where each element with log1p made for it
// *
// */
////this is according to oct.
//CMatrix CMatrix::signbit_element(void)
//  {
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = signbit(values[iR][iC]);}
//        return result;
//
//
//  }
//

/*****************noteeeeeeeeeeeeeeeeeeeeeeeeee when call this functions but catch for throw and remove
the comment from the throw*******************************************************************************************************************/

/** @brief it mul each element with its equiv. element
 *  @param1  the matrix that does the call
 *  @param2  another matrix as i/p
 *  @return a matrix where each element is mul with its equiv element
 *
 */
//this is according to oct.

  CMatrix CMatrix::dot_mult(const CMatrix &m )
  {

    if(m.nR!=nR || m.nC!=nC )
        {
       printf("error: quotient: nonconformant arguments (op1 is %dx%d, op2 is %dx%d)\n",nR,nC,m.nR,m.nC);
       // throw("error");
        CMatrix v (1,1,0) ;
        return v;
        }

      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = values[iR][iC] * m.values[iR][iC];}

  return result ;
  }

  /*****************noteeeeeeeeeeeeeeeeeeeeeeeeee when call this functions but catch for throw and remove
the comment from the throw*******************************************************************************************************************/

/** @brief it mul each element with its equiv. element
 *  @param1  the matrix that does the call
 *  @param2  another matrix as i/p
 *  @return a matrix where each element is mul with its equiv element
 *
 */
//this is according to oct.

  CMatrix CMatrix::dot_power(double d )
  {


      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] = values[iR][iC].power(d);}

  return result ;
  }


/** @brief it div each element with its equiv. element
 *  @param1  the matrix that does the call
 *  @param2  another matrix as i/p
 *  @return a matrix where each element is div with its equiv element @param2 / @param1
 *
 */
//this is according to oct.

  CMatrix CMatrix::dot_div1(const CMatrix &m )   /*   \    */
  {

    if(m.nR!=nR || m.nC!=nC )
        {
       printf("error: quotient: nonconformant arguments (op1 is %dx%d, op2 is %dx%d)\n",nR,nC,m.nR,m.nC);
       // throw("error");
        CMatrix v (1,1,0) ;
        return v;
        }

      CMatrix result( nR ,nC );
      for(int iR=0;iR<result.nR;iR++)
        for(int iC=0;iC<result.nC;iC++)
            {result.values[iR][iC] =  m.values[iR][iC]/ values[iR][iC];}

  return result ;
  }
///** @brief it div each element with its equiv. element
// *  @param1  the matrix that does the call
// *  @param2  another matrix as i/p
// *  @return a matrix where each element is div with its equiv element @param1 / @param2
// *
// */
////this is according to oct.
//
//  CMatrix CMatrix::dot_div2(const CMatrix &m )   /*   /    */
//  {
//
//    if(m.nR!=nR || m.nC!=nC )
//        {
//       printf("error: quotient: nonconformant arguments (op1 is %dx%d, op2 is %dx%d)\n",nR,nC,m.nR,m.nC);
//     //   throw("error");
//
//        CMatrix v (1,1,0) ;
//        return v;
//         }
//      CMatrix result( nR ,nC );
//      for(int iR=0;iR<result.nR;iR++)
//        for(int iC=0;iC<result.nC;iC++)
//            {result.values[iR][iC] = values[iR][iC] / m.values[iR][iC];}
//
//  return result ;
//  }
//
//
//
//
//
//
//
//
//
//
//
/***************************************************************************************************************/


CMatrix CMatrix::power(double number_double )
{
    if(number_double==-1)
    {
        CMatrix x( nR , nC );
        x  =  getInverse();
        return x;
    }

    int sign =1;
    if(  number_double<0 )
    {
        sign=-1;
        number_double*=-1;
    }
    CMatrix result( nR,nC,MI_EYE  );
    int number_int=number_double;
    if(number_double-number_int>0)
    {
       // cout<<"here "<<sign<<endl;
        //then num contains fraction so
        if(nR!=1 || nC!=1 )
        {
            printf("error: according to  the specs if the pow of the value was fraction then the matrix must be 1x1 \n");
            //   throw("error");
            CMatrix v (1,1) ;
            return v;
        }
        number_double*=sign;
        result.values[0][0] = values[0][0].power(number_double);
        return result;
    }
    else
    {

        while (number_int)
        {
            if (number_int & 1)
                result *= *this;
            number_int >>= 1;
            *this *= *this;
        }
    }


    if(sign==1)
        return result ;
    else
        return result.getInverse() ;





}


bool CMatrix::isReal()
{
    for(int iR=0; iR<nR; iR++)
        for(int iC=0; iC<nC; iC++)
            if (abs(values[iR][iC].imaginary())>0.0000001) return false;
    return true;
}

