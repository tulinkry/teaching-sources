#include <iostream>

using namespace std;

bool readArray ( int *& arr, int & n )
{
	int tmp;
	int max = 0;
	while ( cin >> tmp )
	{
		if ( max == n )
		{
			if( max == 0 )
				arr = new int [ max = 2 ];
			else
			{
				int newmax = 1.5 * max;
				int * tmparr = new int [ newmax ];
				for( int i = 0; i < max; i ++ )
					tmparr [ i ] = arr [ i ];
				max = newmax;
				delete [] arr;
				arr = tmparr;
			}	
		}
		arr [ n ++ ] = tmp;
	}
	return cin . eof ();
}

void printArray ( int * arr , int n )
{
	for ( int i = 0; i < n; i ++ )
		cout << arr [ i ] << ' ';
	cout << endl;
}

void swap ( int & a, int & b )
{
	int c = a;
	a = b;
	b = c;
}

void bubbleSort ( int * arr, int n )
{
	for ( int i = 0; i < n - 1; i ++ )
		for ( int j = 0; j < n - i - 1; j ++ )
			if ( arr [ j ] > arr [ j + 1 ] )
				swap ( arr [ j ], arr [ j + 1 ] );
}

int main(){
	int size = 0;
	int * array = NULL;

	if ( ! readArray ( array, size ) )
	{
		cout << "Nespravny vstup." << endl;
		delete [] array;
		return 1;
	}

	printArray ( array, size );
	bubbleSort ( array, size );
	printArray ( array, size );	

	delete[] array;
	return 0;
}