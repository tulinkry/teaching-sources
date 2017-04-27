/* srtarrset.h */

// set implementation by sorted array

#ifndef _SRTARRSET_
#define _SRTARRSET_

#include "array.h"

template <class T>
class SrtArrSet
{
  public:
    explicit SrtArrSet ( int = 8 );
    void insert ( const T & );
    void del ( const T & );
    bool isSet ( const T & ) const;
    int count ( const T & ) const;
    SrtArrSet operator+(const SrtArrSet&) const;
    SrtArrSet operator*(const SrtArrSet&) const;
    bool operator==(const SrtArrSet&) const;
    bool operator<=(const SrtArrSet&) const;
    std::ostream& print(std::ostream&) const;
  private:
    Array<T> arr;   // rozsiritelne pole
    int num;          // pocet prvku v mnozine
    // search vrati index prvku a ve funkcni hodnote zda nalezl
    bool search(const T&, int &) const; 
    // incrNum inkrementuje num, je-li treba provede prodlouzeni pole
    void incrNum(void);
};

template <class T>
SrtArrSet<T>::SrtArrSet(int m) 
  : arr(m), 
    num(0) 
{
}

template <class T>
bool SrtArrSet<T>::search(const T& x, int& i) const 
{
  int d=0, h=num, k;
  while (d<h) 
  {
    k = (d+h)/2;
    if (x<arr[k]) 
      h = k;
    else if (x>arr[k]) 
      d = k+1;
    else 
    { 
      i=k; 
      return true; 
    }
  }
  i=d; 
  return false;
}

template <class T>
void SrtArrSet<T>::incrNum(void) 
{
  if (num>=arr.size()) 
    arr.extend(2*arr.size());
  num++;
}
     
template <class T>
void SrtArrSet<T>::insert (const T& x) 
{
  int j;
  if (search(x,j)) 
    return;
  incrNum();
  for(int i=num-1; i>j; i--) 
    arr[i]=arr[i-1];
  arr[j] = x;
}

template <class T>
void SrtArrSet<T>::del(const T& x) 
{
  int j;
  if (!search(x,j)) 
    return;
  num--;
  for(int i=j; i<num; i++) 
    arr[i]=arr[i+1];
}

template <class T>
bool SrtArrSet<T>::isSet ( const T & x ) const
{
  int j;
  return search ( x , j );
}

template <class T>
int SrtArrSet<T>::count ( const T & x ) const
{
  int j;
  return search ( x , j ) ? 1 : 0;
}

template <class T>
SrtArrSet<T> SrtArrSet<T>::operator+(const SrtArrSet<T>& y) const 
{
  SrtArrSet<T> res;
  int i=0, j=0;
  while (i<num && j<y.num) 
  {
    res.incrNum();
    if (arr[i]<y.arr[j])      
      res.arr[res.num-1]=arr[i++];  
    else if (arr[i]>y.arr[j]) 
      res.arr[res.num-1]=y.arr[j++];
    else                    
    { 
      res.arr[res.num-1]=arr[i++]; 
      j++; 
    }
  }
  while (i<num)   
  { 
    res.incrNum(); 
    res.arr[res.num-1]=arr[i++]; 
  }
  while (j<y.num) 
  { 
    res.incrNum(); 
    res.arr[res.num-1]=y.arr[j++]; 
  }
  return res;
}

template <class T>
SrtArrSet<T> SrtArrSet<T>::operator*(const SrtArrSet<T>& y) const 
{
  SrtArrSet<T> res;
  int i=0, j=0;
  while (i<num && j<y.num) 
  {
    if (arr[i]<y.arr[j])      
      i++;
    else if (arr[i]>y.arr[j]) 
      j++;
    else 
    { 
      res.incrNum(); 
      res.arr[res.num-1]=arr[i++]; 
      j++; 
    }
  }
  return res;
}

template <class T>
bool SrtArrSet<T>::operator==(const SrtArrSet<T>& y) const 
{
  if (num!=y.num) 
    return false;
  for (int i=0; i<num; i++)
    if (arr[i]!=y.arr[i]) 
      return false;
  return true;
}

template <class T>
bool SrtArrSet<T>::operator<=(const SrtArrSet<T>& y) const 
{
  if (num>y.num) 
    return false;
  int j=0;   
  for (int i=0; i<num; i++) 
  {
    while (j<y.num && arr[i]!=y.arr[j]) 
      j++;
    if (j==y.num) 
      return false;
    j++;
  }
  return true;
}

template <class T> 
std::ostream& SrtArrSet<T>::print(std::ostream& s) const 
{
  bool mezera = false;
  s << '[';
  for (int i=0, j=0; i<num; i++) 
  { 
    if (j++==10) 
      { 
        j=1; 
        s<<std::endl; 
      }
    s << (mezera ? " " : "") << arr[i];
    mezera = true;
  }
  s<<']';
  return s;
}
  
template <class T>
std::ostream& operator<<(std::ostream& s, const SrtArrSet<T>& m) 
{
  return m.print(s);
}

#endif
