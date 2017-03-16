#include <iostream>
#include <cstring>

using namespace std;

class String
{
	private:
		int m_Length;
		char * m_Array;
	public:
		String () :
			m_Length (0),
			m_Array (new char[1]) {
			m_Array[0] = 0;
		}

		String ( const char * cstring ) :
			m_Length (strlen (cstring)),
			m_Array (new char[strlen (cstring) + 1]) {
			strcpy (m_Array, cstring);
		}

		String ( const String & instring ) :
			m_Length (instring.m_Length),
			m_Array (new char[instring.m_Length + 1]) {
			strcpy (m_Array, instring.m_Array);
		}

		String ( const char x ) :
				m_Length (1),
				m_Array (new char[2]) {

			m_Array[0] = x;
			m_Array[1] = 0;
		}

		~String () {
			delete []m_Array;
		}

		String& operator = ( const String& x ) {
			if (&x == this)
				return *this;
			m_Length = x.m_Length;
			delete []m_Array;
			m_Array = new char[m_Length +1];
			strcpy (m_Array , x.m_Array);
			return * this;
		}

		char& operator [ ] ( const int x ) {
			if (x<0 || x>= m_Length){
				throw "mimo meze";
			}
			return (m_Array[x]);
		}

		const char& operator [ ] ( const int x ) const {
			if (x<0 || x>= m_Length){
				throw "mimo meze";
			}
			return (m_Array[x]);
		}

		String& operator += ( const String & x ) {
			char * tmp = new char[m_Length + x.m_Length + 1];
			strcpy ( tmp, m_Array );
			strcpy ( tmp + m_Length, x.m_Array );
			delete [] m_Array;
			m_Length = m_Length + x.m_Length;
			m_Array = tmp;
			return * this;
		}

		friend bool operator == ( const String & lhs,
								  const String & rhs ) {
			return strcmp(lhs.m_Array, rhs.m_Array) == 0;	
		}
		
		friend bool operator != ( const String & lhs,
								  const String & rhs ) {
			return !(lhs == rhs);	
		}

		friend ostream& operator << ( ostream &stream, 
									  const String &x ) 
		{
			stream << x.m_Array;
			return stream;
		}

		friend String operator + ( const String &lhs, 
								   const String &rhs ) {
			String out;
			out.m_Length = lhs.m_Length + rhs.m_Length;
			delete []out.m_Array;
			out.m_Array = new char[out.m_Length + 1]; 
			strcpy(out.m_Array, lhs.m_Array);
			strcpy(out.m_Array + lhs.m_Length, rhs.m_Array);

			return (out);
		}
};

int main ()
{
	String a ("slovo");
	String b = a;
	String c;
	String d = 'd' + a + 'd';
	const String e ("neco");
	
	cout << a << " " << b << " " << c << endl;
	c = a + b;
	cout << c << endl;
	cout << d << endl;
	d[0]='c';
	cout << d << endl;
	cout << e[2] << endl;
	cout << boolalpha << (a == c) << endl;
	a += a + a + a;
	cout << a << endl;
	// d[7]= 'e';
	cout << "konec" << endl;
	return 0;
}