/* array.h */

#ifndef _ARRAY_
#define _ARRAY_
  
#include <iostream>

template <class Elem>
class Array
{
  public:
    explicit Array ( int size = 2 ) 
      : m_Data ( new Elem[size] ),
        m_Size ( size ) 
    { 
    }
    Array ( const Array<Elem> & src ) 
    { 
      copy ( src ); 
    }
    ~Array ( ) 
    { 
      delete [] m_Data; 
    }
    int size() const 
    { 
      return m_Size; 
    }
    Elem& operator [] ( int );
    const Elem & operator [] ( int ) const;
    Array<Elem> & operator = ( const Array<Elem> & );
    void extend ( int );
  private:
    Elem* m_Data;
    int m_Size;
    void copy ( const Array<Elem> & );
};

template <class Elem>
Elem& Array<Elem>::operator [] ( int idx )
{
  if (idx < 0 || idx >= m_Size) 
    throw "index out of range";
  return m_Data[idx];
}
  
template <class Elem>
const Elem & Array<Elem>::operator [] ( int idx ) const
{
  if (idx < 0 || idx >= m_Size) 
    throw "index out of range";
  return m_Data[idx];
}

template <class Elem>
Array<Elem> & Array<Elem>::operator = ( const Array<Elem> & src )
{
  if ( this == & src ) 
    return *this;
  delete [] m_Data;
  copy ( src );
  return *this;
}

template <class Elem>
void Array<Elem>::extend ( int newSize )
{
  if ( newSize <= m_Size ) return; // do not shrink !
  Elem *newData = new Elem[newSize];
  for ( int i = 0; i < m_Size; i++ ) 
    newData[i] = m_Data[i];
  delete [] m_Data;
  m_Data = newData;
  m_Size = newSize;
}

template <class Elem>
void Array<Elem>::copy ( const Array<Elem> & src )
{
  m_Size = src.m_Size;
  m_Data = new Elem[m_Size];
  for ( int i = 0; i < m_Size; i++ ) 
    m_Data[i] = src.m_Data[i];
}

#endif


