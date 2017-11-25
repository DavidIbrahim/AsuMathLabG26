all: matrix

matrix: Source.o CMatrix.o
	g++ Source.o CMatrix.o -o matrix

Source.o: Source.cpp
	g++ -c Source.cpp

CMatrix.o: CMatrix.cpp
	g++ -c CMatrix.cpp
	
clean:
	rm *o matrix
	
