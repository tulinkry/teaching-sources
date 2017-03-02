#include <cmath>

#include "complex.h"

// -------------------- COMPLEX ---------------------------

CComplex::CComplex ( const CComplex1 & c )
{
	m_Re = c . getRe();
	m_Im = c . getIm();
}

CComplex CComplex::add ( const CComplex & r ) const
{
	return CComplex ( m_Re + r . m_Re, m_Im + r . m_Im );
}

CComplex CComplex::mul ( const CComplex & r ) const
{
	double newRe = m_Re * r . m_Re - m_Im * r . m_Im;
	double newIm = m_Re * r . m_Im + r . m_Re * m_Im;
	return CComplex ( newRe, newIm );
}
bool CComplex::eq ( const CComplex & r ) const
{
	return m_Re == r . m_Re && m_Im == r . m_Im;
}

void CComplex::print ( std::ostream & os ) const
{
	os << '[' << m_Re << ", " << m_Im << ']';
}

// -------------------- COMPLEX1 ---------------------------

CComplex1::CComplex1 ( const CComplex & c )
{
	// poněkud netypické, ale možné
	*this = CComplex1 ( c . getRe (), c . getIm () );
}

CComplex1::CComplex1 ( double r, double i )
{
	m_Mod = sqrt(r*r + i*i);
	m_Arg = atan2(i, r);
}

CComplex1 CComplex1::add ( const CComplex1 & r ) const
{
	return CComplex1 ( getRe () + r . getRe (),
					   getIm () + r . getIm () );
}

CComplex1 CComplex1::mul ( const CComplex1 & r ) const
{
	CComplex1 tmp;

	tmp . m_Mod = m_Mod * r.m_Mod;
	tmp . m_Arg = m_Arg + m_Arg;

	if 		( tmp . m_Arg >  M_PI ) tmp . m_Arg -= M_PI;
	else if ( tmp . m_Arg < -M_PI ) tmp . m_Arg += M_PI;

	return tmp;
}

bool CComplex1::eq ( const CComplex1 & r ) const
{
	return m_Mod == r . m_Mod && m_Arg == r . m_Arg;
}

double CComplex1::getRe () const
{
	return m_Mod * cos ( m_Arg );
}
double CComplex1::getIm () const
{
	return m_Mod * sin ( m_Arg );
}

void CComplex1::print ( std::ostream & os ) const
{
	os << '(' << getRe () << ", " << getIm () << ')';
}

CComplex add ( const CComplex & a, const CComplex & b )
{
	return CComplex ( a . getRe () + b . getRe (), a . getIm () + b . getIm () );
}