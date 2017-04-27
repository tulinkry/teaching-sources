#include <iostream>

template <typename T>
class MyBitSet 
{
  public:

	MyBitSet ( size_t n = 100 )
	: m_size ( n ), 
	  m_itemSize ( ( m_size + sizeof ( T ) - 1 ) / sizeof ( T ) ), 
	  m_itemArray ( new T[m_itemSize] ) 
	{
		for ( size_t i = 0; i < m_itemSize; i ++ )
			m_itemArray[i] = 0;
	}

	MyBitSet ( const MyBitSet<T> & other )
	: m_size ( other . m_size ), 
	  m_itemSize ( other . m_itemSize),
	  m_itemArray ( new T[m_itemSize] )
	{
		for ( size_t i = 0; i < m_itemSize; i ++ )
			m_itemArray[i] = other . m_itemArray[i];
	}

	~MyBitSet ( void )
	{
		delete [] m_itemArray;
	}

	MyBitSet<T> & operator = ( const MyBitSet<T> & other ) 
	{
		if ( this == &other )
			return *this;

		delete [] m_itemArray;
		
		m_size = other . m_size;
		m_itemSize = other . m_itemSize;
		m_itemArray = new T [m_itemSize];

		for ( size_t i = 0; i < m_itemSize; i ++ )
			m_itemArray[i] = other . m_itemArray[i];

		return *this;
	}

	void insert ( size_t el )
	{
		m_itemArray[getIndex ( el )] |= getMask ( el );
	}

	void del ( size_t el ) 
	{
		m_itemArray[getIndex ( el )] &= ~(getMask ( el ));
	}

	bool isSet ( size_t el ) const
	{
		return ( m_itemArray[getIndex ( el )] & getMask ( el ) );
	}

	size_t getSize ( void ) const
	{
		return m_size;
	}

	MyBitSet<T> operator + ( const MyBitSet<T> & right ) const
	{
		MyBitSet<T> ret(m_itemSize > right . m_itemSize ? *this : right);
		if ( m_itemSize > right . m_itemSize )
		{
		  for ( size_t i = 0; i < right . m_itemSize; i ++ )
		  	ret . m_itemArray[i] |= right . m_itemArray[i];
		}
		else
		{
		  for ( size_t i = 0; i < m_itemSize; i ++ )
		  	ret . m_itemArray[i] |= m_itemArray[i];
		}

		/*
		 * More readable code doing the same as above
		 * 
		 * const MyBitSet<T> & biggerSet = m_itemSize > right . m_itemSize ? *this : right;
		 * const MyBitSet<T> & smallerSet = m_itemSize > right . m_itemSize ? right : *this;
		 * MyBitSet<T> ret ( biggerSet );
		 *
		 * for ( size_t i = 0; i < smallerSet . m_size; i ++ )
		 * 	  ret . m_itemArray[i] |= smallerSet . m_itemArray[i];
		 */

		return ret;
	}

	MyBitSet<T> operator * ( const MyBitSet<T> & right ) const
	{
		MyBitSet<T> ret ( m_itemSize < right . m_itemSize ? *this : right );
		if ( m_itemSize > right . m_itemSize )
		{
		  for ( size_t i = 0; i < m_itemSize; i ++ )
		  	ret . m_itemArray[i] &= m_itemArray[i];
		}
		else
		{
		  for ( size_t i = 0; i < right . m_itemSize; i ++ )
		  	ret . m_itemArray[i] &= right . m_itemArray[i];
		}

		return ret;
	}

	bool operator == ( const MyBitSet<T> & right ) const
	{
		const MyBitSet<T> & biggerSet = m_itemSize > right . m_itemSize ? *this : right;
		const MyBitSet<T> & smallerSet = m_itemSize > right . m_itemSize ? right : *this;

		/*
		 * Check same content
		 */
		for ( size_t i = 0; i < smallerSet . m_size; i ++ )
			if ( smallerSet . m_itemArray[i] != biggerSet . m_itemArray[i] )
				return false;
		/*
		 * The rest in the bigger set must be 0 to make the sets equal at this point
		 */
		for ( size_t i = smallerSet . m_size; i < biggerSet . m_size; i ++ )
			if ( biggerSet . m_itemArray[i] != 0 )
				return false;

		return true;
	}

	bool operator <= ( const MyBitSet<T> & right ) const
	{
		return (*this) * right == *this;
	}

  private:
  	static size_t getIndex ( size_t index )
  	{
  		return index / sizeof ( T );
  	}

  	static size_t getMask ( size_t index )
  	{
  		size_t ind = index % sizeof ( T );
  		return ( 1 << ind );
  	}

  	size_t m_size;
  	size_t m_itemSize;
  	T * m_itemArray;
};

template<typename T> 
std::ostream & operator << ( std::ostream & os, const MyBitSet<T> & set )
{
		os << "[";
		for ( size_t i = 0, first = true; i < set . getSize (); i ++ )
		{
			if ( set . isSet ( i ) )
			{
				os << ( first ? "" : ", " ) << i;
				first = false;
			}
		}
		return os << "]";
}