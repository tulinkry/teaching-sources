#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

typedef pair<string, int> Shelf;

void vypis ( const vector<Shelf>::value_type & p )
{
	cout << "[" << p . first << ", " << p . second << "]" << endl;
}

class CFunctor
{
	private:
		vector<Shelf> & shopping;
		unordered_map<string, int> & mall;
		map<int, string> & ordered_shopping;
	public:
		CFunctor ( vector<Shelf> & a, 
				   unordered_map<string, int> & b, 
				   map<int, string> & c )
		 : shopping ( a ), mall ( b ), ordered_shopping ( c )
		 {}


		void operator() ( const string & s )
		{
		 	unordered_map<string, int>::iterator it;
		 	if ( ( it = mall . find ( s ) ) == mall . end () )
		 		cout << s << " nelze koupit." << endl;
		 	else {
		 		shopping . push_back ( *it );
		 		ordered_shopping . insert ( make_pair ( it -> second, it -> first ) );
		 	}
		}
};

int main ( int argc, char * argv[] )
{
	if ( argc < 3 ) {
		cout << "Usage: " << argv[0] << " <filename1> <filename2>" << endl;
		return 1;
	}

	ifstream f1 ( argv[1] ), f2 ( argv[2] );

	if ( ! f1 . is_open () || ! f2 . is_open () ) {
		cout << "Error opening file(s)" << endl;
		return 1;
	}


	int counter = 0;
	unordered_map<string, int> mall;

	for_each ( istream_iterator<string> ( f1 ),
			   istream_iterator<string> (),
			   [&counter, &mall] ( const string & s )
			   {
			       if ( ! mall . insert ( make_pair ( s, counter ++ ) ) . second )
			 	       cout << "Duplicitni zbozi (" << s << ")" << endl;
			   });

	for_each ( mall . begin (), mall . end (),
		[] ( const unordered_map<string, int>::value_type & p )
		{
			cout << "[" << p . first << ", " << p . second << "]" << endl;
		});

	vector<Shelf> shopping;
	map<int, string> ordered_shopping;

	for_each ( istream_iterator<string> ( f2 ),
			   istream_iterator<string> (),
			   CFunctor ( shopping, mall, ordered_shopping )
			  );

	for_each ( shopping . begin (), shopping . end (), vypis );

	sort ( shopping . begin (), shopping . end (),
		[] ( const vector<Shelf>::value_type & a, const vector<Shelf>::value_type & b )
		{
			return a . second < b . second;
		});

	cout << "Vektor:" << endl;
	for_each ( shopping . begin (), shopping . end (),
		[] ( const vector<Shelf>::value_type & p )
		{
			cout << "[" << p . first << ", " << p . second << "]" << endl;
		});

	cout << "Mapa:" << endl;
	for_each ( ordered_shopping . begin (), ordered_shopping . end (),
		[] ( const map<int, string>::value_type & p )
		{
			cout << "[" << p . second << ", " << p . first << "]" << endl;
		});
}