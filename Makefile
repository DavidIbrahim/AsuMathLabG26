all: matrix

matrix: Source.o CMatrix.o Matlab.o CComplex.o
	g++ Source.o CMatrix.o Matlab.o CComplex.o -o matrix

Source.o: Source.cpp
	g++ -c Source.cpp

CMatrix.o: CMatrix.cpp
	g++ -c CMatrix.cpp
	
Matlab.o: Matlab.cpp
	g++ -c Matlab.cpp	

	
CComplex.o: CComplex.cpp
	g++ -c CComplex.cpp
		
clean:
	rm *o matrix
	
