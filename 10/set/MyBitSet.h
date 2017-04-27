/* MyBitSet.h */

#ifndef _MYBITSET_
#define _MYBITSET_

#include <iostream>

// set implementation by bit string

class MyBitSet
{
  public:
    explicit MyBitSet ( size_t size = 100 );
             MyBitSet ( const MyBitSet & );
            ~MyBitSet ()           { delete [] m_Arr; }
             MyBitSet & operator = (const MyBitSet &);

    size_t size()           const  { return m_Size; }
    void   insert ( size_t i )     { m_Arr[idx(i)] |= pow(i); }
    void   del    ( int i )        { m_Arr[idx(i)] &= ~pow(i); }
    bool   isSet  ( int i ) const  { return ((m_Arr[idx(i)] & pow(i)) != 0); }
    size_t count  ( int i ) const  { return (size_t)isSet(i); }
    MyBitSet operator+ ( const MyBitSet & ) const;
    MyBitSet operator* ( const MyBitSet & ) const;
    bool operator ==   ( const MyBitSet & ) const;
    bool operator <=   ( const MyBitSet & ) const;
  private:
    typedef uint64_t carrier_t;

    static const size_t lng = sizeof(carrier_t);

    static size_t    idx(size_t i) { return (i + (lng - 1)) / lng; }
    static carrier_t pow(size_t i) { return (carrier_t)1 << i % lng; }

    size_t     m_Size; // number of bits in MyBitSet
    size_t     m_Cnt;  // number of carriers
    carrier_t *m_Arr;  // array of carriers
};

std::ostream& operator << ( std::ostream & s, const MyBitSet & x );

#endif // _MYBITSET_

