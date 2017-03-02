#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;



int main ( void )
{
 	int a, b;
 	
 	scanf ( "%d", &a );
 	printf ( "Toto je nase cislo: %+05d \n", a );
    
    cin >> b;
    cout << "Toto je nase cislo: " << setw ( 5 ) << setfill ( '0' ) << b << endl; 

    return 0;
}