#include <iostream> 
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm> 
#include <iterator>

using namespace std;

class CFunctor
{
  public:
    CFunctor ( int & i, unordered_map<string, int> & r )
    : m_i ( i ), m_r ( r )
    {}

	void operator() ( const string & n )
	{
	   if ( ! m_r . insert ( make_pair ( n, m_i ++ ) ) . second ) 
		  cout << "Duplicated value " << n << endl;
	}

  private: 
  	int & m_i;
  	unordered_map<string, int> & m_r;
};

int main ( int argc, char * argv[] )
{
	if ( argc < 3 )
	{
		cout << "Usage: " << argv[0] << " <filename1> <filename2>" << endl;
		return 1;
	}

	ifstream ifr ( argv[1] );
	ifstream ifn ( argv[2] );

	if ( ifr . fail () || ifn . fail () )
	{

		cout << "Error opening file(s)" << endl;
		return 2;
	}

	unordered_map<string, int> regals;

	int i = 0;
	for_each ( istream_iterator<string> ( ifr ),
			   istream_iterator<string> (),
			   CFunctor ( i, regals ) );

	vector< pair <string, int> > shopping1;
	map<int, string> shopping2;


	for_each ( 
		istream_iterator<string> (ifn),
		istream_iterator<string> (), 
		[&shopping2, &shopping1, &regals] ( const string & n )
		{ 
			auto p = regals . find ( n );
			if ( p != regals . end () )	{
				shopping1 . push_back ( *p ); 
				shopping2 . insert ( make_pair ( p -> second, p -> first ) );
			} else {
				cout << n << " neni na sklade" << endl;
			}
		});

	sort ( shopping1 . begin (), shopping1 . end(), 
		[] ( const pair<string, int> & a, const pair<string, int> & b )
		{
			return a . second < b . second; 
		});

	for_each ( shopping1 . begin (), shopping1 . end (), 
		[] ( const pair<string, int> & n )
		{ 
			cout << n . first << ": " << n . second << endl;
		});

	for_each ( shopping2 . begin(), shopping2 . end(), 
		[] ( const pair<int, string> & n )
		{ 
			cout << n . second << ": " << n . first << endl;
		});

	return 0;
}