/* MyBitSet.cpp */

#include "MyBitSet.h"

MyBitSet::MyBitSet ( size_t size ) :
        m_Size(size), m_Cnt(idx(m_Size)), m_Arr(new carrier_t[m_Cnt])
    { for ( size_t i = 0; i < idx(size); i++ ) m_Arr[i] = 0; }
MyBitSet::MyBitSet ( const MyBitSet & rhs ) :
        m_Size(rhs.m_Size), m_Cnt(rhs.m_Cnt), m_Arr(new carrier_t[m_Cnt])
    { for (size_t i = 0; i < m_Cnt; i++ ) m_Arr[i] = rhs.m_Arr[i]; }

MyBitSet & MyBitSet::operator = ( const MyBitSet & rhs )
{
    if ( this == &rhs ) return *this;
    delete [] m_Arr;
    m_Size = rhs.m_Size;
    m_Cnt  = rhs.m_Cnt;
    m_Arr  = new carrier_t[m_Cnt];
    for (size_t i = 0; i < m_Cnt; i++ ) m_Arr[i] = rhs.m_Arr[i];
    return *this;
}

MyBitSet MyBitSet::operator+ ( const MyBitSet & rhs ) const
{
    MyBitSet res(0);
    if (m_Cnt > rhs.m_Cnt)
    {
        res = *this;
        for (size_t i = 0; i < rhs.m_Cnt; i++) res.m_Arr[i] |= rhs.m_Arr[i];
    }
    else
    {
        res = rhs;
        for (size_t i = 0; i < m_Cnt; i++) res.m_Arr[i] |= m_Arr[i];
    }
    return res;
}

MyBitSet MyBitSet::operator* ( const MyBitSet & rhs ) const
{
    MyBitSet res(0);
    if (m_Cnt < rhs.m_Cnt)
    {
        res = *this;
        for (size_t i = 0; i < m_Cnt; i++) res.m_Arr[i] &= rhs.m_Arr[i];
    }
    else
    {
        res = rhs;
        for (size_t i = 0; i < rhs.m_Cnt; i++) res.m_Arr[i] &= m_Arr[i];
    }
    return res;
}

bool MyBitSet::operator == ( const MyBitSet & rhs ) const
{
    size_t i = 0;
    if (m_Cnt < rhs.m_Cnt)
    {
        for ( ; i < m_Cnt; i ++ )
            if (m_Arr[i] != rhs.m_Arr[i]) return false;
        for ( ; i < rhs.m_Cnt; i++ )
            if ( rhs.m_Arr[i] != 0 ) return false;
    }
    else
    {
        for ( ; i < rhs.m_Cnt; i ++ )
            if (m_Arr[i] != rhs.m_Arr[i]) return false;
        for ( ; i < m_Cnt; i++ )
            if ( m_Arr[i] != 0 ) return false;
    }
    return true;
}
bool MyBitSet::operator <= ( const MyBitSet & rhs )  const
{
    return *this * rhs == *this;
}

std::ostream & operator << ( std::ostream & s, const MyBitSet & x )
{
    bool space = false;
    s << '[';
    for ( size_t i = 0, j = 0; i < x.size(); ++i )
    {   if (x.isSet(i))
        {   if ( j == 10 )
            {   j = 0;
                s << std::endl;
            }
            if (space) s << ' ';
            s << i; space = true; ++j;
        }
    }
    s << ']';
    return s;
}

