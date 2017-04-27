/* arrset.h */

// set implementation by unsorted array

#ifndef _ARRSET_
#define _ARRSET_

#include "array.h"

template <class T>
class ArrSet
{
  public:
    explicit ArrSet ( int size = 8 );
    void insert ( const T & );
    bool del ( const T & );
    bool isSet ( const T & ) const;
    int count ( const T & ) const;
    ArrSet operator + ( const ArrSet & ) const;
    ArrSet operator * ( const ArrSet &) const;
    bool operator == ( const ArrSet & ) const;
    bool operator<= ( const ArrSet & ) const;
    template <class X>
    friend std::ostream& operator << ( std::ostream& s, const ArrSet<X> & m );
  private:
    Array<T> m_EArr;                // extendable array
    int m_Cnt;                      // number of elements in set
    int search ( const T & ) const; // ret: index or -1 (not found)
};

template <class T>
ArrSet<T>::ArrSet ( int m ) 
  : m_EArr ( m ), 
    m_Cnt ( 0 ) 
{ 
}

template <class T>
int ArrSet<T>::search ( const T & x ) const
{
  for ( int i = 0; i < m_Cnt; i++ )
    if ( m_EArr[i] == x ) 
      return i;
  return -1;
}

template <class T>
void ArrSet<T>::insert ( const T & x )
{
  if ( search ( x ) >= 0 ) return;
  if ( m_Cnt >= m_EArr.size ( ) ) 
    m_EArr.extend ( 2 * m_EArr.size ( ) );
  m_EArr[m_Cnt++] = x;
}

template <class T>
bool ArrSet<T>::del ( const T & x )
{
  int k = search ( x );
  if ( k < 0 ) return false; // not found
  for ( k++; k < m_Cnt; k++ )
    m_EArr[k-1] = m_EArr[k];
  m_Cnt--;
  return true;
}

template <class T>
bool ArrSet<T>::isSet ( const T & x) const
{
  return search ( x ) >= 0;
}
template <class T>
int ArrSet<T>::count ( const T & x) const
{
  return search ( x ) >= 0 ? 1 : 0;
}

template <class T>                  // union
ArrSet<T> ArrSet<T>::operator + ( const ArrSet<T> & y) const
{
  ArrSet<T> res = *this;
  for ( int i = 0; i < y.m_Cnt; i++ )
    res.insert ( y.m_EArr[i] );
  return res;
}

template <class T>                  // intersection
ArrSet<T> ArrSet<T>::operator * ( const ArrSet<T> & y) const
{
  ArrSet res;
  for ( int i = 0; i < m_Cnt; i++ )
    if ( y.isSet( m_EArr[i] ) ) 
      res.insert ( m_EArr[i] );
  return res;
}

template <class T>                   // equality
bool ArrSet<T>::operator == ( const ArrSet<T>& y ) const
{
  if ( m_Cnt != y.m_Cnt ) 
    return false;
  for ( int i = 0; i < m_Cnt; i++ )
    if ( ! y.isSet ( m_EArr[i] ) ) 
      return false;
  return true;
}

template <class T>                    // inclusion
bool ArrSet<T>::operator <= ( const ArrSet<T> & y ) const
{
  for (int i = 0; i < m_Cnt; i++ )
    if ( ! y.isSet (m_EArr[i] ) ) 
      return false;
  return true;
}

template <class T>
std::ostream& operator << ( std::ostream& s, const ArrSet<T> & x )
{
  bool space = false;
  s << '[';
  for ( int i = 0, j = 0; i < x.m_Cnt; i++ )
  {
    if ( j++ ==  10 )
    { 
      j = 1;
      std::cout << std::endl;
    }
    s << (space ? " " : "") << x.m_EArr[i];
    space = true;
  }
  s<<']';
  return s;
}

#endif
