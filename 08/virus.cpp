#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CPerson;

class CVirus
{
	private:
		string m_Name;
	public:
		CVirus ( const string & s );
		virtual ~CVirus ( void );
		virtual void progress ( CPerson & x ) const = 0;
		virtual CVirus * clone ( void ) const = 0;
		virtual void print ( ostream & stream ) const;
		friend ostream & operator << ( ostream & stream, const CVirus & x );
};

class CPerson
{
	private:
		string m_Name;
		int m_Age;
		double m_Health;
		vector <CVirus *> m_Viruses;
	public:
		CPerson ( const string & s );
		~CPerson ( void );
		void addVirus ( const CVirus & a );
		void progress ( void );
		int & Age ( void );
		double & Health ( void );
		friend ostream & operator << ( ostream & stream, const CPerson & x );
};

/** CPERSON IMPLEMENTATION */


CPerson::CPerson ( const string & s ) :
	m_Name ( s ),
	m_Age ( 0 ),
	m_Health ( 100 )
{
}

CPerson::~CPerson ( void )
{
	for ( size_t i = 0; i < m_Viruses . size(); i ++ )
		delete m_Viruses[i];
}

void CPerson::addVirus ( const CVirus & a )
{
	m_Viruses . push_back ( a . clone () );
}

void CPerson::progress ( void )
{
	m_Age ++;
	for ( size_t i = 0; i < m_Viruses . size(); i ++ )
		m_Viruses[i] -> progress ( *this );
}

double & CPerson::Health ( void )
{
	return m_Health;
}

int & CPerson::Age ( void )
{
	return m_Age;
}


ostream & operator << ( ostream & stream, const CPerson & x )
{
	stream << x . m_Name << " " << x . m_Age << " let, " << x . m_Health << " zdravi, virusy: [";
	int i = 0;
	for ( const auto & v : x . m_Viruses ) {
		if ( i != 0 )
			stream << ", ";
		stream << *v;
		i ++;
	}
	stream << "]";
	return stream;
}

/** CVIRUS IMPLEMENTATION */

CVirus::CVirus ( const string & s ) :
m_Name ( s )
{}

CVirus::~CVirus ( void )
{}

void CVirus::print ( ostream & stream ) const
{
	stream << "Virus: " << m_Name;	
}

ostream & operator << ( ostream & stream, const CVirus & x )
{
	x . print(stream);
	return stream;
}

class CVirusHealing : public CVirus
{
	public:
		CVirusHealing ( const string & x ) :
		CVirus ( x ) 
		{}

		virtual void progress ( CPerson & x ) const
		{
			x . Health() += 10;
		}

		virtual CVirus * clone () const
		{
			return ( new CVirusHealing ( *this ) );
		}
};

class CVirusSlow : public CVirus
{
	public:
		CVirusSlow ( const string & x ) :
		CVirus ( x ) 
		{}

		virtual void progress ( CPerson & x ) const
		{
			if ( x . Age() % 5 == 0 ) x . Health() -= 3;
		}

		virtual CVirus * clone () const
		{
			return ( new CVirusSlow ( *this ) );
		}

		virtual void print ( ostream & stream ) const
		{
			// volání metody předka
			CVirus::print ( stream );
			stream << " Slow";
		}
};

class CVirusAgressive : public CVirus
{
	public:
		CVirusAgressive ( const string & x ) :
		CVirus ( x ) 
		{}

		virtual void progress ( CPerson & x ) const
		{
			x . Health() /= 3;
		}

		virtual CVirus * clone () const
		{
			return ( new CVirusAgressive ( *this ) );
		}
};


int main ( void )
{
	CPerson clovek ("Pepa");
	CVirusHealing a ("ryma"); 
	CVirusSlow b ("kasel");
	CVirusAgressive c ("cukrovka");
	clovek . addVirus ( b );
	clovek . addVirus ( c );

	while ( clovek . Health () > 1 )
	{
		clovek . progress ();
		cout << clovek << endl;
	}

	return 0;
}