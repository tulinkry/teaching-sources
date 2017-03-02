#include <iostream>
#include <cstdlib>

class CComplex
{
	private:
		double im, re;
	public:
		CComplex ( void )
		{}
		CComplex ( double re, double im );
		double getIm ( void ) const;
		double getRe ( void ) const;
		void print ( std::ostream & ) const;
		CComplex add ( const CComplex & ) const;
		CComplex mult ( const CComplex & ) const;
		bool equal ( const CComplex & ) const;
		bool notEq ( const CComplex & r ) const
		{
			return !equal ( r );
		}
};

/* obyčejná funkce přetížená pro náš typ */
CComplex add ( const CComplex &, const CComplex & );

class CComplex1
{
	private:
		double m, fi;
	public:
		CComplex1 ( void )
		{}
		CComplex1 ( double m, double fi );

		double getIm ( void ) const;
		double getRe ( void ) const;
		void print1 ( std::ostream & ) const;
		CComplex1 add ( const CComplex1 & ) const;
		CComplex1 mult ( const CComplex1 & ) const;
		bool equal ( const CComplex1 & ) const;
		bool notEq ( const CComplex1 & r ) const
		{
			return !equal ( r );
		}
};
