#include <iostream>
#include <cstdlib>
#include <cmath>

#include "complex.h"

using namespace std;

int main ( void )
{
	CComplex a ( 1, 1 ), 
			 b ( 5.7, 10.4 ), 
			 c ( 4.3, 0.6 ); 
	CComplex d = a . mult ( b . add ( c ) );

	d . print ( cout );
	cout << endl;
	d = a . mult ( add ( b, c ) );
	d . print ( cout );
	cout << endl;

	CComplex1 a1 ( sqrt ( 2 ), atan2 ( 1, 1 ) ), 
			  b1 ( 5.7, 2 ),
			  c1 ( 4.3, -2 ); 
	CComplex1 d1 = a1 . mult ( b1 . add ( c1 ) );

	d1 . print1 ( cout );
	cout << endl;

	return 0;
}