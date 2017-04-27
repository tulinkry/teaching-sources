/* set.h */

// set implementation by characteristic vector

#ifndef _SET_
#define _SET_

#include "array.h"

class Set
{
  public:
    explicit Set ( int size = 15 );
    void insert ( int );
    void del ( int );
    bool isSet( int ) const;
    int count ( int ) const;
    Set operator + ( const Set & ) const;
    Set operator * ( const Set & ) const;
    bool operator == ( const Set & ) const;
    bool operator <= ( const Set &) const;
    friend std::ostream& operator << ( std::ostream &, const Set & );
  private:
    Array<bool> arr;
};

Set setInitializer ( int = -1, ... );

#endif

