#include <cstring>
#include <iostream>

using namespace std;

class String
{
	private:
		size_t m_Len;
		char * m_Str;
	public:
		String ( void ) : m_Len ( 0 ), m_Str ( new char[1] )
		{
			m_Str[0] = '\0';
		}

		String ( const char * cstr ) : m_Len ( strlen ( cstr ) ), m_Str ( new char[m_Len + 1] )
		{
			strcpy ( m_Str, cstr );
		}

		String ( const char c ) : m_Len ( 1 ), m_Str ( new char[2] )
		{
			m_Str[0] = c;
			m_Str[1] = '\0';
		}

		String ( const String & rstr ) : m_Len ( rstr . m_Len ), m_Str ( new char[m_Len + 1] )
		{
			strcpy ( m_Str, rstr . m_Str );
		}

		~String ( void )
		{
			delete [] m_Str;
		}

		String & operator= ( const String & rstr )
		{
			if ( this == &rstr )
				return *this;

			delete [] m_Str;
			m_Len = rstr . m_Len;
			m_Str = new char[m_Len + 1];
			strcpy ( m_Str, rstr . m_Str );
			return *this;
		}

		char & operator[] ( size_t idx )
		{
			if ( idx >= m_Len )
				throw "Out of bounds!";

			return m_Str[idx];
		}

		const char & operator[] ( size_t idx ) const
		{
			if ( idx >= m_Len )
				throw "Out of bounds!";

			return m_Str[idx];
		}

		friend ostream & operator << ( ostream & os, const String & str )
		{
			os << str . m_Str;
			return os;
		}

		friend String operator+ ( const String & lstr, const String & rstr )
		{ 
			String nstr;
			delete [] nstr . m_Str;
			nstr . m_Len = lstr . m_Len + rstr . m_Len;
			nstr . m_Str = new char[nstr . m_Len + 1];
			strcpy ( nstr . m_Str, lstr . m_Str );
			strcpy ( nstr . m_Str + lstr . m_Len, rstr . m_Str );
			return nstr;
		}
};

int main ( void )
{
	String a, b ( "Hello World!" );
	String c = b;
	String d = "Prvni veta.";
	String e;
	String f;
	f = "Dalsi veta.";
	d = e = d + (b + b);


	cout << a << ';' << endl << b << ';' << endl;
	cout << c << ';' << endl;
	cout << d + b + "Treti veta." << endl;
	cout << 'a' + e + 'b' << endl;
	cout << b[1] << endl;
	b[1] = 'o';
	cout << b << endl;
	try {
		cout << b[50] << endl;
	} catch (const char * ex) {
		cout << ex << endl;
	}
	cout << "Konec!" << endl;
	return 0;
}