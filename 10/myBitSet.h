#include <iostream>
#include <string>

template <typename _T>
class MyBitSet
{
	public:
		MyBitSet(size_t size = 100) : m_Size ( size ), 
								m_RealSize ( ( m_Size + sizeof ( _T ) - 1 ) / sizeof ( _T ) ),
								m_Array ( new _T[m_RealSize] ) 
		{
			for ( size_t i = 0; i < m_RealSize; ++ i )
				m_Array[i] = 0;
		}

		MyBitSet ( const MyBitSet & other ) : m_Size ( other . m_Size ), 
								m_RealSize ( other . m_RealSize ),
								m_Array ( new _T[m_RealSize] )
		{
			for ( size_t i = 0; i < m_RealSize; ++ i )
				m_Array[i] = other.m_Array[i];
		}

		~MyBitSet ( void )
		{
			delete[] m_Array;
		}

		bool isSet ( size_t el ) const
		{
			return m_Array[getIndex ( el )] & getMask ( el );
		}

		bool insert ( size_t el )
		{
			if ( isSet ( el ) )
				return false;

			m_Array[getIndex ( el )] |= getMask ( el );
			return true;
		}

		bool del ( size_t el )
		{
			if ( ! isSet ( el ) )
				return false;

			m_Array[getIndex ( el )] &= ~getMask ( el );
			return true;
		}

		MyBitSet<_T> & operator = ( const MyBitSet<_T> & rS )
		{
			if ( this == &rS )
				return *this;

			delete[] m_Array;

			m_Array = new _T[rS . m_RealSize];
			m_Size = rS . m_Size;
			m_RealSize = rS . m_RealSize;
			for ( size_t i = 0; i < m_RealSize; ++ i )
				m_Array[i] = rS . m_Array[i];

			return *this;
		}

		MyBitSet<_T> operator + (const MyBitSet<_T> & rS) const
		{
			if ( m_RealSize > rS . m_RealSize )
			{
				MyBitSet<_T> result ( m_Size );
				for ( size_t i = 0; i < rS . m_RealSize; ++ i )
					result . m_Array[i] = m_Array[i] | rS . m_Array[i];
				return result;
			}
			else
			{
				MyBitSet<_T> result ( rS . m_Size );
				for ( size_t i = 0; i < m_RealSize; ++ i )
					result . m_Array[i] = m_Array[i] | rS . m_Array[i];
				return result;
			}
		}

		MyBitSet<_T> operator * (const MyBitSet<_T> & rS) const
		{
			if ( m_RealSize < rS . m_RealSize )
			{
				MyBitSet<_T> result ( m_Size );
				for ( size_t i = 0; i < rS . m_RealSize; ++ i )
					result . m_Array[i] = m_Array[i] & rS . m_Array[i];
				return result;
			}
			else
			{
				MyBitSet<_T> result ( rS . m_Size );
				for ( size_t i = 0; i < m_RealSize; ++ i )
					result . m_Array[i] = m_Array[i] & rS . m_Array[i];
				return result;
			}
		}

		bool operator == ( const MyBitSet<_T> & rS ) const
		{
			const MyBitSet<_T> & biggerSet = m_RealSize > rS . m_RealSize ? *this : rS;
			for ( size_t i = 0; i < std::max( m_RealSize, rS . m_RealSize ); ++ i )
			{
				if (i < std::min ( m_RealSize, rS . m_RealSize ) ) {
					if ( m_Array[i] != rS . m_Array[i] )
						return false;
				} else {
					if ( biggerSet . m_Array[i] != 0 )
						return false;
				}
			}
			return true;
		}

		bool operator <= (const MyBitSet<_T> & rS) const
		{
			return *this * rS == *this;
		}

		friend std::ostream & operator << (std::ostream & os, const MyBitSet<_T> & out)
		{
			os << "[ ";
			for ( size_t i = 0; i < out.m_Size; ++ i )
			{
				os << ( out . isSet ( i ) ? std::to_string ( i ) + ", " : "" );
			}
			os << " ]";
			return os;
		} 

	private:
		static size_t getIndex ( size_t el )
		{
			return el / sizeof ( _T );
		}

		static _T getMask ( size_t el )
		{
			size_t bit = el % sizeof ( _T );
			return 1 << bit;
		}

		size_t m_Size;
		size_t m_RealSize;
		_T * m_Array;
};

