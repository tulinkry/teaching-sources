/* sieve.cpp */
// Sieve of Eratosthenes - count the number of primes up to N

#include <set>
#include <bitset>
#include <unordered_set>
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include "set.h"
#include "arrset.h"
#include "srtarrset.h"
#include "MyBitSet.h"

using namespace std;

const int N = 30000;

template <typename _T>
void sieve ( const char * setImpl )
{
  clock_t start = clock ();

  _T a;
  int p = 2,
      pmax = (int) sqrt ( N ),
      cnt = 0;  // count of primes

  do
  {
    cnt++;
    // remove multiples of p
    for ( int i = p * p; i <= N; i += p)
      a.insert ( i );

    // search for next prime
    do p++; while ( a.count ( p ) );
  } while ( p <= pmax );

  // primes between the last removed composite & end of the interval
  for ( ; p<=N; p++ )
    if ( ! a.count ( p ) )
      cnt ++;

  cout << "Prime sieve-" << setImpl << '(' << N <<  "), "
    << cnt << ", time: "
    << ((double)(clock() - start))/CLOCKS_PER_SEC << " sec" << endl;
}

template <int _N>
void sieve ( void )
{
  clock_t start;
  start = clock ( );

  bitset<_N+1> a;
  int p = 2,
      pmax = (int) sqrt ( _N ),
      cnt = 0;  // count of primes

  do
  {
    cnt++;

    // remove multiples of p
    for ( int i = p * p; i <= _N; i += p)
      a.set ( i );

    // search for next prime
    do p++; while ( a.test ( p ) );
  } while ( p <= pmax );

  // primes between the last removed composite & end of the interval
  for ( ; p<=N; p++ )
    if ( ! a.test ( p ) )
      cnt ++;

  cout << "Prime sieve-bitset            (" << _N <<  "), " << cnt
    << ", time: "
    << ((double)(clock() - start))/CLOCKS_PER_SEC << " sec" << endl;
}


void sieveMyBitSet ( size_t n )
{
  clock_t start;
  start = clock ( );

  MyBitSet a ( n + 1 );
  size_t p = 2,
      pmax = (int) sqrt ( n ),
      cnt = 0;  // count of primes

  do
  {
    cnt++;

    // remove multiples of p
    for ( size_t i = p * p; i <= n; i += p)
      a.insert ( i );

    // search for next prime
    do p++; while ( a.isSet ( p ) );
  } while ( p <= pmax );

  // primes between the last removed composite & end of the interval
  for ( ; p<=n; p++ )
    if ( ! a.isSet ( p ) )
      cnt ++;

  cout << "Prime sieve-MySetBit          (" << a.size()-1 <<  "), "
    << cnt << ", time: "
    << ((double)(clock() - start))/CLOCKS_PER_SEC << " sec" << endl;
}

int main()
{
  sieve<ArrSet<int> > ( "ArrSet<int>       " );
  sieve<SrtArrSet<int> > ( "SrtArrSet<int>    " );
  sieve<set<int> > ( "std::set<int>     " );
  sieve<unordered_set<int>  > ( "unordered_set<int>" );
  sieve<N> ();
  sieve<Set > ( "Set (char. vector)" );

  sieveMyBitSet(30000);
  cout <<"---------------------------------------------------------\n";
  sieveMyBitSet(300000);
  sieveMyBitSet(3000000);
  sieveMyBitSet(30000000);
  sieveMyBitSet(300000000);

  return 0;
}
