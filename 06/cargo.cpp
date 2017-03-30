#include <iostream>
#include <cassert>

/**
 * File cargo.cpp
 */

// forward deklarace generické třídy
template <typename vehicleType>
class CCargo;

// forward deklarace generické funkce
template <typename vehicleType>
std::ostream & operator << ( std::ostream & out, const CCargo<vehicleType> & cargo );

/**
 * Šabloná má na generický typ následující omezení:
 * 1) Vyžaduje kopírující konstruktor
 * 2) Vyžaduje operátor násobení s číslem double
 * 3) Vyžaduje schopnost vypsat se do streamu
 */
template <typename vehicleType>
class CCargo
{
	double m_weight;
	vehicleType m_vehicle;

	void print ( std::ostream & out ) const
	{
		out << "weight: " << m_weight << " t\n";
		out << "price:  " << m_vehicle << " CZK/(km * t)";
	}
public:
	// deklarace vnořené šablony pro friend funkci - <>
	friend std::ostream & operator << <> ( std::ostream & out, const CCargo<vehicleType> & cargo);

	CCargo ( int weight, const vehicleType & vehicle );

	template <typename src_T, typename dst_T>
	double transfer ( src_T & src, dst_T & dst, double km ) const;
};

template <typename vehicleType>
CCargo<vehicleType>::CCargo ( int weight, const vehicleType & vehicle ) :
		m_weight ( weight ),
		m_vehicle ( vehicle )
{}

template <typename vehicleType>
template <typename src_T, typename dst_T>
double CCargo<vehicleType>::transfer ( src_T & src, dst_T & dst, double km ) const
{
	src -= m_weight;
	dst += m_weight;

	return m_vehicle * m_weight * km;
}

template <typename vehicleType>
std::ostream & operator << ( std::ostream & out, const CCargo<vehicleType> & cargo )
{
	cargo . print ( out );
	return out;
}

class CCar
{
	static const int PRICE = 5;

public:
	double operator * ( double num ) const
	{
		return PRICE * num;
	}

	friend std::ostream & operator << ( std::ostream & out, const CCar & car )
	{
		out << "car " << PRICE;
		return out;
	}
};

class CTrain
{
	int car_cnt;
	static const int PRICE_PER_CAR = 5;

public:
	CTrain ( int cars ) : car_cnt ( cars )
	{}

	double operator * ( double num ) const
	{
		return PRICE_PER_CAR * car_cnt * num;
	}

	friend std::ostream & operator << ( std::ostream & out, const CTrain & train )
	{
		out << "train " << PRICE_PER_CAR * train.car_cnt;
		return out;
	}
};

using namespace std;

int main()
{
	CCargo<int> test ( 10, 5 );

	int sklad_a = 1000;
	int sklad_b = 0;

	assert ( test . transfer ( sklad_a, sklad_b, 100 ) == 5000 );
	assert ( sklad_a == 990 );
	assert ( sklad_b == 10  );

	cout << test << endl;

	CCargo<CCar> test2 ( 10, CCar() );

	sklad_a = 1000;
	sklad_b = 0;

	assert ( test2 . transfer ( sklad_a, sklad_b, 100 ) == 5000 );
	assert ( sklad_a == 990 );
	assert ( sklad_b == 10  );

	cout << test2 << endl;

	CCargo<CTrain> test3 ( 10, CTrain ( 2 ) );

	sklad_a = 1000;
	sklad_b = 0;

	assert ( test3 . transfer ( sklad_a, sklad_b, 100 ) == 10000 );
	assert ( sklad_a == 990 );
	assert ( sklad_b == 10  );

	cout << test3 << endl;

	CCargo<CTrain> test4 ( 10, CTrain ( 2 ) );

	float  sklad_1 = 1000;
	double sklad_2 = 0;

	assert ( ( test4 . transfer<float, double> ( sklad_1, sklad_2, 100 ) ) == 10000 );
	assert ( sklad_1 == 990 );
	assert ( sklad_2 == 10  );

	cout << test4 << endl;

	return 0;
}