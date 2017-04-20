#include <iostream>
#include <exception>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <fstream>

using namespace std;

class NullPointerException : public exception
{
	public:
		NullPointerException ( void )
		{}

		virtual const char * what ( void ) const throw()
		{
			return "NullPointerException";
		}
};

class FileNotFoundException : public exception
{
	public:
		FileNotFoundException ( const string & a ) :
		m_Error ( "FileNotFoundException: " + a) 
		{}
		virtual const char * what ( void ) const throw()
		{
			return m_Error . c_str ();
		}
		virtual ~FileNotFoundException ( void ) throw()
		{}
	private:
		string m_Error;
};

class BadPermissionException : public exception
{
	public:
		BadPermissionException ( const string & a ) :
		m_Error ( "BadPermissionException: " + a) 
		{}
		virtual const char * what ( void ) const throw()
		{
			return m_Error . c_str ();
		}
		virtual ~BadPermissionException ( void ) throw()
		{}
	private:
		string m_Error;
};

class CFile
{
	public:
		CFile ( const char * name )
		{
			if ( name == 0 )
				throw NullPointerException ();
			m_Name = name;
		}
		string GetFile ( void ) const
		{
			if (access(m_Name . c_str (), F_OK) == -1) {
				throw FileNotFoundException ( m_Name + ": " + strerror ( errno ) );
			}
			if (access(m_Name . c_str (), R_OK) == -1) {
				throw BadPermissionException ( m_Name + ": " + strerror ( errno ) );
			}

			ifstream in (m_Name . c_str ());
			string result, line;
			if ( ! in . is_open () )
				throw FileNotFoundException ( m_Name );

			while ( getline ( in, line ) )
			{
				result += line;
				result += '\n';
			}

			return result;
		}
	private:
		string m_Name;
};

int main ( int argc, char const *argv[] )
{
	if ( argc < 2 ) 
	{
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	CFile a ( argv[1] );
	try { 
		cout << a . GetFile();
	} catch ( const exception & a ) {
		cout << a . what() << endl;
	}

	try { 
		CFile b ( NULL );
	} catch ( const exception & a ) {
		cout << a . what() << endl;
	}
	return 0;
}