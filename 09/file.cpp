#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <cerrno>


using namespace std;

class NullPointerException : public exception
{
	public:
		NullPointerException ( void )
		{};
		~NullPointerException ( void ) throw()
		{};
		virtual const char * what (void) const throw()
		{
			return "NullPointerException";
		}
};

class IOException : public exception
{
	public:
		IOException ( const string & ex ) : m_Exception ( ex )
		{};
		~IOException ( void ) throw()
		{};
		virtual const char * what (void) const throw()
		{
			return m_Exception . c_str ();
		}
	private:
		string m_Exception;
};

class FileNotFoundException : public IOException
{
	public:
		FileNotFoundException ( const string & ex ) : IOException ( "File not found: " + ex )
		{};
		~FileNotFoundException ( void ) throw()
		{};
};

class BadPermissionException : public IOException
{
	public:
		BadPermissionException ( const string & ex ) : IOException ( "Bad Permission: " + ex )
		{};
		~BadPermissionException ( void ) throw()
		{};
};


class CFile
{
	public:
		CFile ( const char * filename )
		{
			if ( filename == NULL )
				throw NullPointerException ();
			m_Filename = filename;
		}

		string Read ( void ) const
		{
			if ( access ( m_Filename . c_str (), F_OK ) != 0 )
				throw FileNotFoundException ( m_Filename + " : " + strerror ( errno ) );

			if ( access ( m_Filename . c_str (), R_OK ) != 0 )
				throw BadPermissionException ( m_Filename + " : " + strerror ( errno ) );

			ifstream f(m_Filename . c_str ());
			if (!f.is_open())
				throw FileNotFoundException ( m_Filename );

			string line;
			string out;

			while ( getline ( f, line ) ) {
				out += line;
				out += '\n';
			}

			return out;
		}
	private:
		string m_Filename;
};



int main ( int argc, const char * argv[] )
{

	if ( argc < 2 )
	{
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	string file = argv[1];

	while ( 1 )
	{
		CFile a ( file . c_str () );
		try {
			cout << a . Read() << endl;
			break;
		} catch ( const FileNotFoundException & e ) {
			cout << e . what() << endl;
			cout << "Oprav jmeno souboru: ";
			cin >> file;
		} catch ( const IOException & e ) {
			cout << e . what() << endl;
			break;
		}		
	}
	
	try {
		CFile b ( NULL );
	} catch ( const NullPointerException & e ) {
		cout << e . what() << endl;
	}
	

	return 0;

}