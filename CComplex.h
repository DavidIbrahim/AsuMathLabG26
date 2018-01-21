#ifndef CCOMPLEX_H
#define CCOMPLEX_H
#include <string>

using namespace std;

class CComplex
{
    public:
        CComplex();
        virtual ~CComplex();
        CComplex(double R, double I);
        CComplex(CComplex& C);
        void copy(CComplex& C);
        string getString();
        double magnitude();
        double angle();
        void negative();
        double real();
        double imaginary();

        void add(CComplex& C);
        void sub(CComplex& C);

        CComplex operator=(const CComplex& C);
        CComplex operator=(double D);
        void operator+=(CComplex& C);
        void operator+=(double D);
        CComplex operator+(CComplex& C);
        CComplex operator+(double D);

    protected:

    private:
        double R;
        double I;
};

#endif // CCOMPLEX_H
