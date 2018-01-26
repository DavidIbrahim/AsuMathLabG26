#ifndef CCOMPLEX_H
#define CCOMPLEX_H
#include <string>

using namespace std;

class CComplex
{
    public:
        CComplex();
        virtual ~CComplex();
        CComplex(double R);
        CComplex(double R, double I);
        CComplex(const CComplex& C);
        CComplex(string s);
        void copy(string s);
        string getString(bool isReal);
        double magnitude();
        double angle();
        void negative();
        double real();
        double imaginary();
        CComplex conjugate();
        CComplex power(double d);

        void add(const CComplex& C);
        void sub(const CComplex& C);

        CComplex operator=(const CComplex& C);
        CComplex operator=(double D);
        void operator+=(const CComplex& C);
        void operator+=(double D);
        CComplex operator+(CComplex& C);
        CComplex operator+(double D);

        void operator-=(const CComplex& C);
        void operator-=(double D);
        CComplex operator-(CComplex& C);
        CComplex operator-(double D);


        CComplex operator-();
        operator const string();
        friend istream& operator >> (istream &is, CComplex& C);
        friend ostream& operator << (ostream &os, CComplex& C);

        CComplex operator++(); //Pre Increment
        CComplex operator++(int); //Post Increment, int is not used

        friend CComplex operator+(double D, const CComplex& C); //For double + complex
        friend CComplex operator-(double D, const CComplex& C); //For double - complex

        void mul(const CComplex& C);
        void operator *=(const CComplex& C);
        friend CComplex operator*(const CComplex& A, const CComplex& B);

        void div( CComplex& C);
        void operator /=(CComplex& C);
        friend CComplex operator/(CComplex& A, CComplex& B);

        friend bool operator==(const CComplex& A, const CComplex& B);
        friend bool operator!=(const CComplex& A, const CComplex& B);
        //friend bool operator>(const CComplex& A, const CComplex& B);
        //friend bool operator<(const CComplex& A, const CComplex& B);



    protected:

    private:
        double R;
        double I;
};

#endif // CCOMPLEX_H
