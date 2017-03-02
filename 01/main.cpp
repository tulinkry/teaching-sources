#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

int main ( void )
{
	int input;
	int input2;

	scanf ( "%d", &input );
	printf ( "%+010d\n", input );

	if( ! ( cin >> input2 ) )
	{
		cout << "Nespravny vstup." << endl;
		return 1;
	}

	cout << setw ( 10 ) << setfill ( '0' ) << input2 << endl;

	return 0;
}