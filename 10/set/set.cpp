/* set.cpp */

// set implementation by characteristic vector

#include <cstdarg>

#include "set.h"

Set::Set ( int indMax ) 
  : arr ( indMax + 1 ) 
{
  for ( int i = 0; i < arr.size ( ); i++ ) 
    arr[i] = false;
}

void Set::insert ( int x )
{
  if ( x >= arr.size ( ) ) 
  {
    int sz = arr.size (),
        newsz = std::max ( x + 1, 2 * arr.size ( ) );
    arr.extend ( newsz );
    for ( int i = sz; i < newsz; i++ ) 
      arr[i] = false; 
  }
  arr[x] = true;
}

void Set:: del ( int x )
{
  if ( x >= arr.size ( ) ) 
    return;
  arr[x] = false;
}

bool Set::isSet ( int x ) const
{
  if ( x >= arr.size ( ) ) 
    return false;
  return arr[x];
}

int Set::count ( int x ) const
{
  if ( x >= arr.size ( ) ) 
    return 0;
  return arr[x] ? 1 : 0;
}

Set Set::operator + ( const Set & y ) const
{
  int nx = arr.size ( ), ny = y.arr.size ( );
  if ( nx < ny ) 
    return y + *this;
  Set res = *this;
  for ( int i = 0; i < ny; i++ )
    if ( y.isSet ( i ) ) 
      res.insert ( i );
  return res;
}

Set Set::operator * ( const Set & y ) const
{
  int nx = arr.size ( ), ny = y.arr.size ( );
  if ( nx > ny ) 
    return y * *this;
  Set res ( nx );
  for ( int i = 0; i < nx; i++ )
    if (isSet ( i ) && y.isSet ( i ) ) 
      res.insert ( i );
  return res;
}

bool Set::operator == ( const Set & y) const
{
  int nx = arr.size ( ), ny = y.arr.size ( );
  if ( nx > ny ) 
    return y == *this;
  for ( int i = 0; i < nx; i++ )
    if ( arr[i] != y.arr[i] ) 
      return false;
  for ( int i = nx; i < ny; i++ )
    if ( y.arr[i] ) 
      return false;
  return true;
}

bool Set::operator <= ( const Set & y ) const
{
  int n = arr.size ( );
  for ( int i = 0; i < n; i++ )
    if ( arr[i] && ! y.isSet ( i ) ) 
      return false;
  return true;
}

std::ostream & operator << ( std::ostream & s, const Set & m)
{
  bool mezera = false;
  s << '[';
  for (int i = 0, j = 0, n = m.arr.size(); i < n; i++ ) 
    if ( m.arr[i] ) 
    { 
      if ( j++ == 10 ) 
      { 
        j = 1; 
        std::cout << std::endl; 
      }
      s << ( mezera ? " " : "" ) << i;
      mezera = true;
    }
  s << ']';
  return s;
}

Set setInitializer ( int x, ... )
{ // replace ... with initializer_list<int> in c++11
  va_list ppar;
  Set res;
  if ( x < 0 ) 
    return res;
  res.insert ( x );
  va_start ( ppar, x );
  for ( ; ; )
  {
    x = va_arg ( ppar, int );
    if ( x < 0 ) break;
    res.insert ( x );
  }
  va_end ( ppar );
  return res;
}

