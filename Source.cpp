#include<stdio.h>
#include <iostream>
#include"CMatrix.h"
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include "Matlab.h"



using namespace std;
int main(int argc, char*argv[])
{
      Matlab x;
        cout<<x.getStringMatrix("[[2 5] [2 5] [2 5]]");
    return 0;
}
