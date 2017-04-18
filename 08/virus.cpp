#include<iostream>
#include<vector>
#include<string>

using namespace std;

class CVirus;

class CPerson
{
	private:
		string name;
		int age;
		double health;
		vector<CVirus*> viruses;
	public:
		CPerson ( const string & n );
		~CPerson ( void );

		int getAge ( void ) const;
		double getHealth ( void ) const;
		void setHealth ( double change );
		void addVirus ( const CVirus & v );
		void progress ( void );

		friend ostream & operator << ( ostream & os, const CPerson & p );
};

class CVirus
{
	private:
		string name;
	public:
		CVirus ( const string & n );
		virtual ~CVirus ( void );
		virtual void progress ( CPerson & p ) const = 0;
		virtual CVirus * clone ( void ) const = 0;

		friend ostream & operator << ( ostream & os, const CVirus & v );
};

/** CPERSON IMPLEMENTATION */

CPerson::CPerson ( const string & n )
: name ( n ), age ( 0 ), health ( 100 )
{}

CPerson::~CPerson ( void )
{
	for ( const auto & v : viruses )
		delete v;
}

int CPerson::getAge ( void ) const
{
	return age;
}

double CPerson::getHealth ( void ) const
{
	return health;
}

void CPerson::setHealth ( double change )
{
	health = change;
}

void CPerson::addVirus ( const CVirus & v )
{
	viruses . push_back ( v . clone () );
}

void CPerson::progress ( void )
{
	age ++;
	for ( auto v:viruses )
		v -> progress ( *this );
}

ostream & operator << ( ostream & os, const CPerson & p )
{
	os << p . name << ",  "<< p . age << ", " << p . health << " :: ";
	int i = 0;
	for ( const auto & v: p . viruses ){
		if ( i != 0 )
			os << ", ";
		os << *v;
		i ++;
	}
	return os;
}

/** CVIRUS IMPLEMENTATION */

CVirus::CVirus ( const string & n )
: name ( n )
{}

CVirus::~CVirus ( void )
{}

ostream & operator << ( ostream & os, const CVirus & v ){
	os << v . name;
	return os; 
}



class CVirusLessAgressive : public CVirus
{
	public:
		CVirusLessAgressive ( const string & n ) : CVirus ( n ){}
		virtual void progress ( CPerson & p ) const;
		virtual CVirus* clone ( void ) const;
};

void CVirusLessAgressive::progress ( CPerson & p ) const
{
	p . setHealth ( p . getHealth () / 2 );
}

CVirus* CVirusLessAgressive::clone ( void ) const
{
	return new CVirusLessAgressive ( *this );
}

class CVirusAgressive : public CVirus
{
	public:
		CVirusAgressive ( const string & n ) : CVirus ( n ){}
		virtual void progress ( CPerson & p ) const;
		virtual CVirus* clone ( void ) const;
};

void CVirusAgressive::progress ( CPerson & p ) const
{
	p . setHealth ( p . getHealth () / 3 );
}

CVirus* CVirusAgressive::clone ( void ) const
{
	return new CVirusAgressive ( *this );
}



int main ( void ){
	CPerson p1 ( "James Bond" );
	CVirusLessAgressive v1 ( "Ryma" );
	CVirusAgressive v2 ( "Kasel" );

	p1 . addVirus ( v1 );
	p1 . addVirus ( v2 );


	while ( p1 . getHealth () > 1 )
	{
		p1 . progress ();
		cout << p1 << endl;
	}

	return 0;
}