#include <iostream>
#include <cstdlib>

using namespace std;

void sortArray ( int * array, int number )
{
	for ( int i = 0; i < number - 1; i ++ )
	{
		int min = array [ i ], minIndex = i;
		for (int j = i + 1; j < number; j ++ )
		{
			if ( array [ j ] < min )
			{
				minIndex = j;
				min = array [ j ];
			}
		}
		if ( minIndex != i )
		{
			array [ minIndex ] = array [ i ];
			array [ i ] = min;
		}
	}
}

void reallocArray ( int ** array, int * oldNumber )
{
	if ( ! *array )  
	{
		*array = new int [ *oldNumber = 2 ];
		return;
	}

	int * tmp = new int [ *oldNumber * 2 ];

	for ( int i = 0; i < *oldNumber; i ++ )
		tmp [ i ] = ( *array ) [ i ];

	*oldNumber *= 2;
	delete [] *array;
	*array = tmp;
}

bool readArray ( int ** array, int * number )
{
	int tmp, numberAllocated = 0;
	*number = 0;
	while ( cin >> tmp )  
	{
		if ( numberAllocated == *number )  
			reallocArray ( array, &numberAllocated );

		( *array )[ ( *number ) ++ ] = tmp;
	} 
	return cin . eof ();
}

void printArray ( int * array, int number )
{
	for ( int i = 0; i < number; i ++ )
		cout << array [ i ] << ' ';
	cout << endl;
}

int main ( void )
{
	int * array = NULL, cnt = 0;

	if ( ! readArray ( &array, &cnt ) )
	{
		cout << "Nespravny vstup" << endl;
		delete [] array;
		return 1;
	}

	printArray ( array, cnt ); 
	sortArray ( array, cnt );
	printArray ( array, cnt );
	
	delete[] array;
	return 0;
}