all: matrix

matrix: Source.o CMatrix.o Matlab.o
	g++ Source.o CMatrix.o Matlab.o -o matrix

Source.o: Source.cpp
	g++ -c Source.cpp

CMatrix.o: CMatrix.cpp
	g++ -c CMatrix.cpp
	
Matlab.o: Matlab.cpp
	g++ -c Matlab.cpp	
	
clean:
	rm *o matrix
	
