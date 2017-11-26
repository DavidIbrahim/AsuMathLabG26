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
        static CComplex addComplex(CComplex& A, CComplex& B);
        void add(CComplex& C);

        static CComplex subComplex(CComplex& A, CComplex& B);
        void sub(CComplex& C);


    protected:

    private:
        double R;
        double I;
};

#endif // CCOMPLEX_H
