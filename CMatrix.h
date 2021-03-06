#include <fstream>
#include <string>
#include "CComplex.h"
#ifndef CMatrix_H
#define CMatrix_H

using namespace std;
class CMatrix {

private:
  int nR, nC;

  CComplex **values;
  //static bool fixMatrix(CMatrix &m,int r,int c);
  //static bool checkIfZeroMatrix(CMatrix &m);

  public:
  CMatrix();
  //double getDeterminant2();
  //double getDeterminant3();
  ~CMatrix();
  enum MI { MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
  bool isReal();

  CMatrix(int nR, int nC, int initialization = MI_ZEROS,
          CComplex initializationValue = CComplex(0.0));
  //CMatrix(int nR, int nC, double first, ...);
  CMatrix(const CMatrix &m);
  CMatrix(double d);
  CMatrix(const CComplex c);
  CMatrix(string s);
  void copy(const CMatrix &m);
  void copy(double d);
  void copy(const CComplex c);
  void copy(string s);
  void reset();
  string getString();
  CMatrix operator=(const CMatrix &m);
  CMatrix operator=(double d);
  CMatrix operator=(string s);
  static CMatrix horizontalConcatenation(CMatrix &m1,CMatrix &m2);
  static CMatrix verticalConcatenation(CMatrix &m1,CMatrix &m2);
/**********************************************************here is the new functions********************************************/
  CMatrix sin_element (void);//modified and tested //complex numbers
  CMatrix cos_element (void);//modified and tested //complex numbers
  CMatrix tan_element (void);//modified and tested //complex numbers
  CMatrix sinh_element (void);//modified and tested//complex numbers
  CMatrix cosh_element (void);//modified and tested//complex numbers
  CMatrix tanh_element (void);//modified and tested//complex numbers
  CMatrix asin_element (void);
  CMatrix acos_element (void);
  CMatrix atan_element (void);
  CMatrix asinh_element (void);
  CMatrix acosh_element (void);
  CMatrix atanh_element (void);
/************************************************************************************************************************/
  CMatrix abs_element    (void);//only real
  CMatrix ceil_element   (void);//only real
  CMatrix floor_element  (void);//only real
  CMatrix sqrt_element   (void);//only real
/************************************************************************************************************************/
  CMatrix exp_element   (void);//complex numbers
  CMatrix log_element   (void);//only real
  CMatrix log10_element (void);
  CMatrix expm1_element (void);
  CMatrix log1p_element (void);
  CMatrix log2_element  (void);
/************************************************************************************************************************/
  CMatrix round_element(void);
  CMatrix erfc_element(void);
  CMatrix erf_element(void);
  CMatrix lgamma_element(void);
  CMatrix cbrt_element(void);
  CMatrix isfinite_element(void);
  CMatrix isinf_element(void);
  CMatrix isnan_element(void);
  CMatrix signbit_element(void);
/************************************************************************************************************************/
  // the dot add and dot subtract are the same as the normal add and subtract
  CMatrix dot_power(double d );
  CMatrix dot_mult(const CMatrix &m );
  CMatrix dot_div1(const CMatrix &m );/*   \    */
  CMatrix dot_div2(const CMatrix &m );/*   /    */
/************************************************************************************************************************/
  CMatrix power(double num );
/*******************************    till here           *************************************************************************/
  void add(const CMatrix &m);
  void operator+=(CMatrix &m);
  void operator+=(double d);
  CMatrix operator+(CMatrix &m);
  CMatrix operator+(double d);

  void sub(const CMatrix &m);
  void operator-=(CMatrix &m);
  void operator-=(double d);
  CMatrix operator-(CMatrix &m);
  CMatrix operator-(double d);

  void mul(const CMatrix &m);
  void operator*=(CMatrix &m);
  void operator*=(double d);
  CMatrix operator*(CMatrix &m);
  CMatrix operator*(double d);

  void div(CMatrix &m);
  void operator/=(CMatrix &m);
  void operator/=(double d);
  CMatrix operator/(CMatrix &m);
  CMatrix operator/(double d);

  CMatrix operator++();    // Pre Increment
  CMatrix operator++(int); // Post Increment, int is not used
  CMatrix operator--();    // Pre Increment
  CMatrix operator--(int); // Post Increment, int is not used

  CMatrix operator-();
  CMatrix operator+();


  friend istream& operator >> (istream &is, CMatrix& C);  //TO BE TESTED-TUNA
  friend ostream& operator << (ostream &os, CMatrix& C);  //TO BE TESTED-TUNA
  friend CMatrix operator /(double d ,CMatrix &m);      //PROBLEM-TUNA

  CMatrix getCofactor(int r, int c);
  CMatrix getSubMatrix(int r, int c, int nr, int nc);

  void setSubMatrix(int iR, int iC, CMatrix &m);
  void addColumn(CMatrix &m);
  void addRow(CMatrix& m);

  CComplex &operator[](int i) { return values[i / nC][i % nC]; }
  CComplex &operator()(int i) { return values[i / nC][i % nC]; };
  CComplex &operator()(int r, int c) { return values[r][c]; };
  int getn() { return nR * nC; };
  int getnR() { return nR; };
  int getnC() { return nC; };

  CComplex getDeterminant();
  CMatrix getTranspose(); //TO BE TESTED-TUNA
  CMatrix getInverse();
  string getString2();
  void writeMatrixInFile(string file);

};

#endif
