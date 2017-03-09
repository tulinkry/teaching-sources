#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class CQuestion
{
	string text;
	public:
		CQuestion ( const string & txt ) : text ( txt )
		{}

		void print ( ostream & os ) const
		{
			os << text;
		}
};

class COption
{
	string text;
	int voted;
	int id;
	static int counter;
	public:
		COption(const string & txt)
		: text ( txt ), voted ( 0 ), id ( ++ counter )
		{}
		
		int getId() const
		{
			return id;
		}

		void vote ( void )
		{
			voted ++;
		}
		
		void print ( ostream & os, int totalVoted = 0 ) const
		{
			os << id << ") " << text;
			os << setw ( 30 - text . length() );
			os << setfill ( ' ' ) << voted;
			if ( totalVoted )
				os << ' ' << 100 * voted / totalVoted << '%';
		}
};

int COption::counter = 0;

class CPoll
{
	CQuestion question;
	vector<COption> v;
	int totalVoted;
	public:
		CPoll ( const string & txt )
		: question ( txt ), totalVoted ( 0 )
		{}
		
		void add ( const string & txt )
		{
			v . push_back ( COption ( txt ) );
		}

		bool vote ( const vector<int> & answers )
		{
			for ( unsigned int i = 0; i < v . size(); i ++ )
				for ( unsigned int j = 0; j < answers . size(); j ++ )
					if ( v[i].getId() == answers[j] )
					{
						v[i] . vote();
						totalVoted ++;
					}
			return true;
		}

		void print ( ostream & os ) const
		{
			question . print ( os );
			os << endl << endl;
			for ( unsigned int i = 0; i < v . size(); i ++ )
			{
				v[i] . print ( os, totalVoted );
				os << endl;
			}
		}
};

int main ( void )
{
	CPoll poll ( "What is your favourite meal?" );
	poll . add ( "Strawberry" );
	poll . add ( "Blueberry" );
	poll . add ( "Blackberry" );
	poll . add ( "Whiteberry" );
	poll . print ( cout );
	vector<int> vec;
	vec . push_back ( 1 );
	vec . push_back ( 3 );
	poll . vote ( vec );
	poll . print ( cout );
	return 0;
}
