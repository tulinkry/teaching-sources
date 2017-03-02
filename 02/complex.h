#ifndef HCOMPLEX // zabránění několikanásobnému includu
#define HCOMPLEX

#include <iostream>

class CComplex1; // forward deklarace

class CComplex
{
	private:
		double m_Re;
		double m_Im;
	public:

		CComplex() {}
		CComplex (const CComplex1 &c);
		CComplex(double r, double i): m_Re(r), m_Im(i) {}
		CComplex add(const CComplex & r) const;
		CComplex mul(const CComplex & r) const;
		bool eq(const CComplex & r) const;
		bool neq(const CComplex & r) const { return !eq(r); }
		double getRe () const { return m_Re; } 
		double getIm () const { return m_Im; }
		void print(std::ostream & os) const;

};

/* obyčejná funkce přetížená pro náš typ */
CComplex add(const CComplex & a, const CComplex & b); 

class CComplex1
{
	private:
		double m_Mod;
		double m_Arg;
	public:
		CComplex1() {}
		CComplex1 (const CComplex & c );
		CComplex1(double r, double i);

		CComplex1 add(const CComplex1 & r) const;
		CComplex1 mul(const CComplex1 & r) const;
		bool eq(const CComplex1 & r) const;
		bool neq(const CComplex1 & r) const { return !eq(r); }
		double getRe () const;
		double getIm () const;
		void print(std::ostream & os) const;
};

#endif