#include "CComplex.h"
#include <string>
#include <math.h>
#include <stdio.h>

CComplex::CComplex()
{
    R = I = 0.0;
}

CComplex::~CComplex()
{
    //dtor
}

CComplex::CComplex(double R, double I)
{
    this->R = R; this->I = I;
}

CComplex::CComplex(CComplex& C)
{
    copy(C);
}

void CComplex::copy(CComplex& C)
{
    R = C.R; I = C.I;
}

string CComplex::getString()
{
    char text[100];
    if(I==0)sprintf(text, "%g", R);
    else if(R==0)sprintf(text, "%g * i", I);
    else if(I>0)sprintf(text, "%g + %g * i", R, I);
    else if(I<0)sprintf(text, "%g - %g * i", R, -I);
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

CComplex CComplex::addComplex(CComplex& A, CComplex& B)
{
    CComplex C;
    C.R = A.R + B.R;
    C.I = A.I + B.I;
    return C;
}

void CComplex::add(CComplex& C)
{
    R += C.R;I += C.I;
}

CComplex CComplex::subComplex(CComplex& A, CComplex& B)
{
    CComplex C;
    C.R = A.R - B.R;
    C.I = A.I - B.I;
    return C;
}

void CComplex::sub(CComplex& C)
{
    R -= C.R;I -= C.I;
}
