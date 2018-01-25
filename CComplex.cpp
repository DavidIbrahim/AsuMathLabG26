#include "CComplex.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

CComplex::CComplex()
{
    R = I = 0.0;
}

CComplex::~CComplex()
{
    //dtor
}
CComplex::CComplex(double R)
{
    this->R = R; this->I = 0.0;
}

CComplex::CComplex(double R, double I)
{
    this->R = R; this->I = I;
}

CComplex::CComplex(const CComplex& C)
{
    R = C.R; I = C.I;
}

string CComplex::getString()
{
    char text[100];
    /*if(I==0)sprintf(text, "%g", R);
    else if(R==0)sprintf(text, "%gi", I);
    else */if(I>=0)sprintf(text, "%8g + %8gi", R, I);
    else if(I<0)sprintf(text, "%8g - %8gi", R, -I);
    return string(text);
}

double CComplex::magnitude()
{
    return sqrt(R*R+I*I);
}
double CComplex::angle()
{
    return atan2(I, R);
}

void CComplex::negative()
{
    R*=-1; I*=-1;
}

double CComplex::real()
{
    return R;
}

double CComplex::imaginary()
{
    return I;
}

void CComplex::add(const CComplex& C)
{
    R += C.R;I += C.I;
}

void CComplex::sub(const CComplex& C)
{
    R -= C.R;I -= C.I;
}

CComplex CComplex::conjugate()
{
    return CComplex(R,-I);
}

CComplex CComplex::operator=(const CComplex& C)
{
    R = C.R; I = C.I;
    return *this;
}
CComplex CComplex::operator=(double D)
{
    R = D;I = 0;
    return *this;
}
void CComplex::operator+=(const CComplex& C)
{
    add(C);
}
void CComplex::operator+=(double D)
{
    R += D;
}
CComplex CComplex::operator+(CComplex& C)
{
    CComplex X=*this;
    X+=C;
    return X;
}
CComplex CComplex::operator+(double D)
{
    CComplex X=*this;
    X+=D;
    return X;
}

void CComplex::operator-=(const CComplex& C)
{
    sub(C);
}
void CComplex::operator-=(double D)
{
    R -= D;
}
CComplex CComplex::operator-(CComplex& C)
{
    CComplex X=*this;
    X-=C;
    return X;
}
CComplex CComplex::operator-(double D)
{
    CComplex X=*this;
    X-=D;
    return X;
}

CComplex CComplex::operator-()
{
    return CComplex(-R, -I);
}
CComplex::operator const string()
{
    return getString();
}

istream& operator >> (istream &is, CComplex& C)
{
    string s;
    getline(is, s);
    C= CComplex(s);
    return is;
}
ostream& operator << (ostream& os, CComplex& C)
{
    os<<C.getString();
    return os;
}

CComplex CComplex::operator++()
{
    R++;
    return *this;
}
CComplex CComplex::operator++(int)
{
    CComplex C = *this;
    R+=1;
    return C;
}

CComplex operator+(double D, const CComplex& C)
{
    CComplex X=C;
    X+=D;
    return X;
}
CComplex operator-(double D, const CComplex& C)
{
    CComplex X=C;
    X-=D;
    return X;
}
void CComplex::mul(const CComplex& C)
{
    double R = this->R*C.R - this->I*C.I;
    double I = this->R*C.I + this->I*C.R;
    this->R=R;this->I=I;
}
void CComplex::operator *=(const CComplex& C)
{
    mul(C);
}
CComplex operator*(const CComplex& A, const CComplex& B)
{
    CComplex X=A;
    X*=B;
    return X;
}
void CComplex::div(CComplex& C)
{
    mul(C.conjugate());
    R/=(C.R*C.R + C.I*C.I);
    I/=(C.R*C.R + C.I*C.I);
}
void CComplex::operator /=(CComplex& C)
{
    div(C);
}
CComplex operator/(CComplex& A, CComplex& B)
{
    CComplex X=A;
    X.div(B);
    return X;
}
CComplex::CComplex(string s)
{
    copy(s);
}
void CComplex::copy(string s)
{
    for(int i=0; i<s.length(); i++)
        if(s[i] == ' ') s.erase(i,1);
    int plusPos, minusPos, i_Pos;
    bool real, imag;

    plusPos = s.rfind('+');
    minusPos = s.rfind('-');
    i_Pos = s.find('i');

    real = i_Pos < 0; // real number won't contain the character i
    imag = i_Pos>=0 && ((minusPos < 0 && plusPos < 0)||(plusPos < 0 && minusPos==0)); // pure imag number if no + or -

    if (real) {
        R = atof(s.c_str());
        I = 0.0;
    }

    else if (imag) {
        R = 0.0;
        string imagNum;
        imagNum=s.substr(0,i_Pos);
        I = atof(imagNum.c_str());
        if (I == 0) // i, -i
        {
            I = 1;
            if (s[0] == '-') I = -I;
        }
    }

    else //real+imag
    {
        if(minusPos>0) //No spaces in the beg
        {
            string realNum=s.substr(0,minusPos);
            R = atof(realNum.c_str());
            s=s.substr(minusPos);
        }
        else if (plusPos>=0)
        {
            string realNum=s.substr(0,plusPos);
            R = atof(realNum.c_str());
            s=s.substr(plusPos);
        }
        I = atof(s.c_str());
        if (I == 0) // 1 + i, 1 - i
        {
            I = 1;
            if (s[0] == '-') I = -I;
        }
    }
}
bool operator==(const CComplex& A, const CComplex& B){ return (A.R==B.R)&&(A.I==B.I); }
//bool operator>(const CComplex& A, const CComplex& B){ return (A.magnitude()>B.magnitude()); }
//bool operator<(const CComplex& A, const CComplex& B){ return (A.magnitude()<B.magnitude()); }
