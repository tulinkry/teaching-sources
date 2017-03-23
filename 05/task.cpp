#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cassert>

using namespace std;

// https://github.com/tulinkry/teaching-sources/blob/12_45/05

class CPage
{
	private:
		int m_Size, m_Cnt;
		string ** m_Lines;
	public:
		CPage ( const char * fname ) : m_Size ( 0 ), m_Cnt ( 0 ), m_Lines ( NULL )
		{
			ifstream iff ( fname );
			string line;
			while ( getline ( iff, line ) )
			{
				if ( m_Size >= m_Cnt ) {
					m_Size = m_Size < 100 ? m_Size + 10 : m_Size * 1.5;
					string ** tmp = new string*[m_Size];
					memcpy ( tmp, m_Lines, m_Cnt * sizeof ( string * ) );
					delete [] m_Lines;
					m_Lines = tmp;
				}

				m_Lines [ m_Cnt ++ ] = new string ( line );
			}

			if ( ! iff . eof () ) {
				delete this;
				throw "Invalid input";
			}

			iff . close ();
		}


		string & operator [] ( int index )
		{
			if ( index < 0 || index >= m_Cnt )
				throw "Out of bounds";
			return *m_Lines [ index ];
		}

		const string & operator [] ( int index ) const
		{
			if ( index < 0 || index >= m_Cnt )
				throw "Out of bounds";
			return *m_Lines [ index ];
		}

		friend ostream & operator << ( ostream & os, const CPage & page )
		{
			for ( int i = 0; i < page . m_Cnt; i ++ ) {
				os << *page . m_Lines [ i ] << endl;
			}
			return os;
		}		
};


class CBook
{
	private:
		CPage ** m_Pages;
		int m_Cnt, m_Size;
	public:

		CBook & addPage ( const CPage & page )
		{
			if ( m_Cnt >= m_Size )
				throw "Out of bounds";
			m_Pages [ m_Cnt ++ ] = new CPage ( page );
			return *this;
		}

		CPage & operator [] ( int index )
		{
			if ( index < 0 || index >= m_Cnt )
				throw "Out of bounds";
			return *m_Pages [ index ];
		}

		const CPage & operator [] ( int index ) const
		{
			if ( index < 0 || index >= m_Cnt )
				throw "Out of bounds";
			return *m_Pages [ index ];
		}

		friend ostream & operator << ( ostream & os, const CBook & book )
		{
			for ( int i = 0; i < book . m_Cnt; i ++ )
				os << *book . m_Pages [ i ] << endl;
			return os;
		}

};



int main(int argc, char const *argv[])
{
	CBook a ( 250 );
	a 
	  . addPage ( "page1.txt" )
	  . addPage ( "page2.txt" )
	  . addPage ( "page3.txt" )
	  ;
	a
	  . addPage ( a[0] )
	  . addPage ( a[1] )
	  . addPage ( a[2] )
	  . addPage ( a[0] )
	  . addPage ( a[1] )
	  . addPage ( a[2] )
	  . addPage ( a[0] )
	  . addPage ( a[1] )
	  . addPage ( a[2] )
	  ;

	a = a;

	cout << a;

	assert ( a[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( a[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );

	assert ( a[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( a[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( a[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( a[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	CBook b ( a );

	assert ( b[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( b[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );

	assert ( b[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( b[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( b[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( b[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	CBook c ( b );
	CBook d;
	d = b;


	b[0][0] = "Změna první věty";
	b[1][1] = "Změna druhé věty";
	b[2][0] = "Změna třetí věty";
	d[0][1] = "Blueberry";

	assert ( b[2][0] == "Změna třetí věty" );
	assert ( b[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	assert ( a[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( a[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );

	assert ( a[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( a[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( a[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( a[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	

	assert ( b[0][0] == "Změna první věty" );
	assert ( b[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );

	assert ( b[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( b[1][1] == "Změna druhé věty" );

	assert ( b[2][0] == "Změna třetí věty" );
	assert ( b[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );


	assert ( c[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( c[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );

	assert ( c[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( c[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( c[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( c[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	

	assert ( d[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( d[0][1] == "Blueberry" );

	assert ( d[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( d[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( d[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( d[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	c[0] = c[1];
	c[1] = c[2];

	assert ( c[0][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( c[0][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );

	assert ( c[1][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( c[1][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	

	assert ( c[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( c[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	d[0] = c[1];
	d[1] = a[2];

	assert ( d[0][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( d[0][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	

	assert ( d[1][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( d[1][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	

	assert ( d[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( d[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );

	const CBook x ( a ); // will not trigger detach ()

	assert ( x[0][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( x[0][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );
	assert ( x[1][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( x[1][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );
	assert ( x[2][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( x[2][1] == "že ta meta je někde výš než přihlásit se na českou školu." );
	assert ( x[3][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( x[3][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );
	assert ( x[4][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( x[4][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );
	assert ( x[5][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( x[5][1] == "že ta meta je někde výš než přihlásit se na českou školu." );	
	assert ( x[6][0] == "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod" );
	assert ( x[6][1] == "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam," );
	assert ( x[7][0] == "Prodám AngelSounds Fetal Doppler na poslouchání tlukotu srdce miminka v břiše matky." );
	assert ( x[7][1] == "Používán je krátce, cca 15x. Roh krabice trochu otlačen, ale na funkci to nemá žádný vliv." );
	assert ( x[8][0] == "Nicméně drtivou většinu absolutně nenapadne," );
	assert ( x[8][1] == "že ta meta je někde výš než přihlásit se na českou školu." );		

	return 0;
}
