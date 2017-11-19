#ifndef MATLAB_H
#define MATLAB_H
#include"CMatrix.h"
#include<vector>


class Matlab
{
    private:
        CMatrix matrix;
        char name;

        bool checkIfSpecialMatrix(string instruction);

    public:
        Matlab();
        Matlab(string instruction,vector<Matlab>& myVector);
        virtual ~Matlab();

    protected:


};

#endif // MATLAB_H
