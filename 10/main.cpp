/* main.cpp */
#include <iostream>
#include "mybitset.h"

using namespace std;

template <typename _T>
void testFunc ( void )
{
  _T m1, m2;
  cout << "m1 = " << m1 << endl;         // []
  cout << "m2 = " << m2 << endl;         // []
  m1 . insert ( 20 );
  m1 . insert ( 2 );
  m1 . insert ( 7 );
  cout << "m1 = " << m1 << endl;         // [2 7 20]
  m2 . insert ( 6 );
  m2 . insert ( 2 );
  cout << "m2 = " << m2 << endl;         // [2 6]
  cout << "m1 + m2 = " << m1 + m2 << endl; // [2 6 7 20]
  cout << "m1 * m2 = " << m1 * m2 << endl; // [2]
  m2 = m1;
  m1 . del ( 2 );
  m1 . insert ( 13 );
  m2 . insert ( 15 );
  cout << "m1 = " << m1 << endl;         // [7 13 20]
  cout << "m2 = " << m2 << endl;         // [2 7 15 20]
  cout << "m1 + m2 = " << m1 + m2 << endl; // [2 7 13 15 20]
  cout << "m1 * m2 = " << m1 * m2 << endl; // [7 20]
  cout << "m1 == m2 = " << ( m1 == m2 ) << endl; // 0
  const _T m0 = m2;
  cout << "m0 = " << m0 << endl;         // [2 7 15 20]
  // m0 . ins ( 1 );   //chyba
  m1 = m0;
  cout << "m1 = " << m1 << endl;         // [2 7 15 20]
  m1 . insert ( 3 );
  m1 . insert ( 5 );
  m2 = m1;
  cout << "m1 = " << m1 << endl;         // [2 3 5 7 15 20]
  cout << "m2 = " << m2 << endl;         // [2 3 5 7 15 20]
  cout << "m1 == m2 = " << ( m1 == m2 ) << endl; // 1
  m2 . insert ( 8 );
  cout << "m2 = " << m2 << endl;         // [2 3 5 7 8 15 20]
  cout << "m1 <= m2 = " << ( m1 <= m2 ) << endl; // 1
  cout << "m2 <= m1 = " << ( m2 <= m1 ) << endl;  // 0
}

int main ( void )
{
  cout << "*********** MyBitSet  ***************\n";
  testFunc<MyBitSet<uint8_t> > ();
  return 0;
}

