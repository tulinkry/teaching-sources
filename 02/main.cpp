#include <iostream>

#include "complex.h"

int main ( void ) {

	CComplex a (1, 1 );
	CComplex b (1, 2 );
	CComplex c (2, 1 );
    
    CComplex1 d ( b );
    d . print ( std::cout );

	std::cout << std::endl; 
	( a . mul ( b . add ( c ) ) ) . print ( std::cout );
	std::cout << std::endl;
	( a . mul ( add ( b, c ) ) ) . print ( std::cout );
	std::cout << std::endl;

	CComplex1 x ( 1, 1 );
	CComplex1 y ( 1, 2 );
	CComplex1 z ( 2, 1 );

	CComplex e ( y );
	e . print ( std::cout );
	std::cout << std::endl;

	( x . mul ( y . add ( z ) ) ) . print ( std::cout );
	std::cout << std::endl;
	return 0;
}