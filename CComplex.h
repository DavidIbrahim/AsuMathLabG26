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
        CComplex(const CComplex& C);
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

        CComplex operator-();
        operator const string();
        //friend istream& operator >> (istream &is, CComplex& C);
        friend ostream& operator << (ostream &os, CComplex& C);

        CComplex operator++(); //Pre Increment
        CComplex operator++(int); //Post Increment, int is not used
        //double operator[](string name); //Index
        //double operator()(string name, string info = ""); //Argument

    protected:

    private:
        double R;
        double I;
};

#endif // CCOMPLEX_H
