#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

struct A : public exception
{
};

void foo2 ( void )
{
	throw logic_error("nejhorsi problem");
}

void foo ( void )
{
	int * x = new int[50];
	try {
		foo2 ();
	} catch ( ... ) {
		delete [] x;
		cout << "vyjimka y ve foo" << endl;
		throw;
	}
	delete [] x;
}

int main ( int argc, char const *argv[] )
{
	int * x = new int[20];

	try {
		foo ();
	} catch ( const A & y ) {
		cout << "vyjimka y" << endl;
	} catch ( int a ) {
		cout << "vyjimka int" << endl;
	} catch ( const exception & b ) {
		cout << "vyjimka: " << b . what () << endl;
	} catch ( ... ) {
		cout << "nejaka vyjimka" << endl;
	}
	
	delete [] x;

	return 0;
}