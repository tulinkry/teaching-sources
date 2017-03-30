#include <iostream>
#include <cassert>

using namespace std;

// forward deklarace třídy s šablonou
template <class T> class CCargo;
// forward deklarace funkce s šablonou
template <class T> ostream & operator << ( ostream & os, const CCargo<T> &tmp );

class CCar
{
	private:
		const static int PRICE	= 10;
	public:

		double operator * ( const double cislo ) const
		{
			return PRICE * cislo;
		}

		friend ostream & operator << ( ostream & os, const CCar &car )
		{
			os << "car "<< PRICE;
			return os;
		}
};

class CTrain
{
	private:
		const static int PRICE	= 5;
		int pocet_vagonu;
	public:
		CTrain(int pocet):pocet_vagonu(pocet){}

		double operator * (const double cislo) const
		{
			return PRICE * cislo * pocet_vagonu;
		}

		friend ostream & operator << ( ostream & os, const CTrain &train)
		{
			os << "train "<< PRICE * train . pocet_vagonu;
			return os;
		}
};

template <class T>

class CCargo
{
	private:
		double m_weight;
		T m_vehicle;
	public:
		CCargo ( double weight, const T &vehicle );
		
		template <class X, class Y = int>
		double transfer ( X &src, Y &dest, int km ) const;
		
		friend ostream & operator << <> ( ostream & os, const CCargo<T> &tmp );
};

template <class T>
CCargo<T>::CCargo ( double weight, const T &vehicle )
 : m_weight ( weight ), m_vehicle ( vehicle )
{}

template <class T>
template <class X, class Y>
double CCargo<T>::transfer ( X &src, Y &dest, int km ) const
{
	src -= m_weight;
	dest += m_weight;
	return m_vehicle * km * m_weight;
}

template <class T>
ostream & operator << ( ostream & os, const CCargo<T> &tmp )
{
	os << tmp . m_weight << " " << tmp . m_vehicle;
	return os;
}

int main()
{
	int src = 100;
	int dest = 0;
	CCargo<int> cargo ( 5, 10 );

	assert( cargo . transfer ( src, dest, 10 ) == 500 );
	assert( src == 95 && dest == 5 );

	cout << cargo << endl;

	src = 100;
	dest = 0;

	CCargo<CCar> newcargo ( 5, CCar() );

	assert( newcargo . transfer ( src, dest, 10 ) == 500 );
	assert( src == 95 && dest == 5 );

	cout << newcargo << endl;

	double src2 = 100.0;
	float dest2 = 0.0f;

	CCargo<CTrain> traincargo ( 5, CTrain ( 2 ) );

	assert( ( traincargo . transfer <double, float> ( src2, dest2, 10 ) ) == 500 );
	assert( src2 == 95 && dest2 == 5 );

	cout << traincargo << endl;

	return 0;
}