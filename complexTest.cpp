#include <stdio.h>
#include <iostream>
#include "CComplex.h"
#include "CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main()
{
    /*CMatrix A("[1 1;2+i 2-i]");
    cout<<"A= \n"<<A.getString2()<<endl;*/

    /*//Test 11 string copy, getDeterminant
    CMatrix A;
    A.copy("[3+2i 4+5i; 5+2i 6]");
    cout<<"A= \n"<<A.getString()<<endl;
    CMatrix B("[5+2i 6; 8+3i 5]");
    cout<<"B= \n"<<B.getString()<<endl;
    cout<<"B="<<(string)B.getDeterminant()<<endl;
    CMatrix C=string("[5+2i 6 7+2i; 8+3i 5 6]");
    cout<<"C= \n"<<C.getString()<<endl;
    cout<<"C="<<(string)C.getDeterminant()<<endl;
    CMatrix D = A.getInverse();
    cout<<"D= \n"<<D.getString()<<endl;
    D = B;
    cout<<"D= \n"<<D.getString()<<endl;
    B/=A;
    cout<<"B= \n"<<B.getString()<<endl;
    D=D/A;
    cout<<"D= \n"<<D.getString()<<endl;*/

    /*//Test 10 multiplication
    CMatrix A(1,2,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"A= \n"<<A.getString()<<endl;
    CMatrix B(2,1,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"B= \n"<<B.getString()<<endl;
    A=A*B;
    cout<<"A= \n"<<A.getString()<<endl;
    A=A*5;
    cout<<"A= \n"<<A.getString()<<endl;*/

    /*//Test 9 addRow, addColumn
    CMatrix A(1,2,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"A= \n"<<A.getString()<<endl;
    CMatrix B(2,1,CMatrix::MI_VALUE,CComplex(2,2));
    cout<<"B= \n"<<B.getString()<<endl;
    CMatrix C(B);
    cout<<"C= \n"<<C.getString()<<endl;
    B.addColumn(A);
    cout<<"B= \n"<<B.getString()<<endl;
    C.addRow(A);
    cout<<"C= \n"<<C.getString()<<endl;*/

    //Test 8 subtraction
    CMatrix A(2,2,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"A= \n"<<A.getString()<<endl;
    CMatrix B(2,2,CMatrix::MI_RAND);
    cout<<"B= \n"<<B.getString()<<endl;
    CMatrix C = A;
    cout<<"C= \n"<<C.getString()<<endl;
    C.sub(B);
    cout<<"C= \n"<<C.getString()<<endl;
    CMatrix D = A;
    cout<<"D= \n"<<D.getString()<<endl;
    D-=B;
    cout<<"D= \n"<<D.getString()<<endl;
    D = A - B;
    cout<<"D= \n"<<D.getString()<<endl;
    D = A - 5;
    cout<<"D= \n"<<D.getString()<<endl;

    /*//Test 7 aggregation basics + addition
    CMatrix A(2,2,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"A= \n"<<A.getString()<<endl;
    cout<<A.isReal()<<endl;
    CMatrix B(2,2,CMatrix::MI_RAND);
    cout<<"B= \n"<<B.getString()<<endl;
    CMatrix C = -A;
    cout<<"C= \n"<<C.getString()<<endl;
    C+=B;
    cout<<"C= \n"<<C.getString()<<endl;
    C =5;
    cout<<"C= \n"<<C.getString()<<endl;
    cout<<C.isReal()<<endl;
    C+=10;
    cout<<"C= \n"<<C.getString()<<endl;
    C = A + B;
    cout<<"C= \n"<<C.getString()<<endl;
    CMatrix D = A+B;
    cout<<"D= \n"<<D.getString()<<endl;
    CMatrix E = C+10;
    cout<<"E= \n"<<E.getString()<<endl;
    E = D-- + C;
    cout<<"E= \n"<<E.getString()<<endl;
    cout<<"D= \n"<<D.getString()<<endl;
    E = --D + C;
    cout<<"E= \n"<<E.getString()<<endl;
    cout<<"D= \n"<<D.getString()<<endl;*/

    /*//Test 6
    CMatrix A(2,2,CMatrix::MI_VALUE,CComplex(3,2));
    cout<<"A= \n"<<A.getString()<<endl;
    CMatrix B(2,2,CMatrix::MI_RAND);
    cout<<"B= \n"<<B.getString()<<endl;
    CMatrix C(B);
    cout<<"C= \n"<<C.getString()<<endl;
    CMatrix D(1);
    cout<<"D= \n"<<D.getString()<<endl;*/

    /*//Test5
    CComplex A(2, 3), B(4, 5), C, D;
    cout<<"A = "<<A<<endl;
    cout<<"B = "<<B<<endl;
    C = A * B;
    cout<<"C = "<<C<<endl;
    D=C.conjugate();
    cout<<"D = "<<D<<endl;
    D/=C;
    cout<<"D = "<<D<<endl;
    C=CComplex("9+i");
    cout<<"C = "<<C<<endl;
    C-=A;
    cout<<"C = "<<C<<endl;*/

    /*//Test4
    CComplex A(2.1, 3.2), C;
    cout<<"A = "<<A.getString()<<endl;
    C = A++;
    cout<<"A = "<<A<<endl;
    cout<<"C = "<<C<<endl;
    C = ++A;
    cout<<"A = "<<A<<endl;
    cout<<"C = "<<C<<endl;*/

    /*//Test3
    CComplex A(2.1, 3.2), B(1.4, -1.2), C, D;
    cout<<"A = "<<(string)A<<endl;
    cout<<"B = "<<(string)B<<endl;
    cout<<"Enter Complex Value EX (3+6i) : "<<endl;
    cin>>C;
    cout<<"C = "<<C<<endl;
    //cout<<"A>B = "<<(A>B)<<endl;
    D = -A;cout<<"D = "<<D<<endl;*/

    /*//Test2
    CComplex A(6.7, 8.9), B(1.4, -1.2), C;
    cout<<"A = "<<A.getString()<<endl;
    cout<<"B = "<<B.getString()<<endl;
    C = A;
    cout<<"C = "<<C.getString()<<endl;
    C += B;
    cout<<"C = "<<C.getString()<<endl;
    CComplex D(A-B);
    cout<<"D = "<<D.getString()<<endl;
    C = A - B + D;
    cout<<"C = "<<C.getString()<<endl;
    C = D = CComplex(12.1, 3.2);
    cout<<"C = "<<C.getString()<<endl;
    cout<<"D = "<<D.getString()<<endl;
    C = 5 + A;C -= 10;D = 5;
    cout<<"C = "<<C.getString()<<endl;
    cout<<"D = "<<D.getString()<<endl;*/

    /*//Test1
    CComplex A(5, 5), B, C(5, -5), D(-5, 5), E(5, 0), F(0, 5);
    cout<<"A = "<<A.getString()<<endl;
    cout<<"B = "<<B.getString()<<endl;
    cout<<"C = "<<C.getString()<<endl;
    cout<<"D = "<<D.getString()<<endl;
    cout<<"E = "<<E.getString()<<endl;
    cout<<"F = "<<F.getString()<<endl;*/

    return 0;
}
