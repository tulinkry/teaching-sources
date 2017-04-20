#include <iostream>
#include <stdexcept>
	
using namespace std;

struct A {

};

void foo2 ( void )
{
	throw out_of_range("mimo meze");
}

void foo ( void ) 
{
	int * x = new int [50];

	try {
		foo2 ();
	} catch ( ... ) {
		cout << "zachycena vyjimka y ve foo()" << endl;
		delete [] x;
		throw;
	} 

	delete [] x;
}

int main(int argc, char const *argv[])
{
	int * x = new int[10];

	try {
		foo ();
	} catch ( const A & y ) {
		cout << "zachycena vyjimka y v main ()" << endl;
	} catch ( const int & z ) {
		cout << "zachycena vyjimka z v main ()" << endl;
	} catch ( const exception & w ) {
		cout << "zachycena vyjimka z v main (): " << w . what () << endl;
	} catch ( const out_of_range & w ) {
		cout << "zachycena vyjimka out_of_range z v main (): " << w . what () << endl;
	} catch ( ... ) {

	}

	delete [] x;

	return 0;
}