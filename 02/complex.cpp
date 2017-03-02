#include <iostream>
#include <cstdlib>
#include <cmath>

#include "complex.h"

// -------------------- COMPLEX ---------------------------

CComplex::CComplex ( double re, double im )
{
	this -> im = im; // nutné použití this kvůli kolizi jmen
	this -> re = re;
}

double CComplex::getIm ( void ) const {
	return im;
}

double CComplex::getRe ( void ) const
{
	return re;
}

void CComplex::print( std::ostream& os ) const
{
	os << '[' << re << ',' << im << ']';
}

CComplex CComplex::add ( const CComplex & ad ) const
{
	return CComplex( re + ad . re,
					 im + ad . im );
}

CComplex CComplex::mult ( const CComplex & r ) const
{
	CComplex res;
	res . re = ( re * r . re ) - ( im * r . im );
	res . im = ( re * r . im ) + ( im * r . re );
	return res;
}

bool CComplex::equal ( const CComplex & com) const
{
	return re == com . re && im == com . im;
}

CComplex add ( const CComplex & a,const CComplex & b )
{
	return CComplex ( a . getRe() + b . getRe(),
					  a . getIm() + b . getIm() );
}

// -------------------- COMPLEX1 ---------------------------

CComplex1::CComplex1 ( double m, double fi )
{
	this -> m = m;
	this -> fi = fi;
}

double CComplex1::getIm ( void ) const
{
	return m * sin ( fi );
}

double CComplex1::getRe ( void ) const
{
	return m * cos ( fi );
}

void CComplex1::print1( std::ostream & os ) const
{
	os << '(' << m << ',' << fi << ')';
}

CComplex1 CComplex1::add ( const CComplex1 & r ) const
{
	double re = m * cos ( fi ) + r.m * cos ( r.fi );
	double im = m * sin ( fi ) + r.m * sin ( r.fi );
	return CComplex1(
		sqrt ( re * re + im * im ),
		atan2 ( im, re ) );
}

CComplex1 CComplex1::mult ( const CComplex1 & r ) const
{
	return CComplex1 ( m * r . m, fi + r . fi );
}

bool CComplex1::equal ( const CComplex1 & r ) const
{
	return m == r . m && fi == r . fi;
}
