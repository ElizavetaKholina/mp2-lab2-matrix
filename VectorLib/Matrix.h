#include <iostream>
#include <cmath>
#include "Vector.h"

template <class T>

class TMatrix
{
private:
	size_t N;
	TVector<T> data;
public:
	TMatrix(size_t _N);
	~TMatrix();
	TMatrix(const TMatrix& m);
	TMatrix(TMatrix&& m) noexcept;

	int GetSize() const;
	TMatrix(const TVector<T>& v);

	

	TMatrix& operator=(const TMatrix& m);
	TMatrix& operator=(TMatrix&& m) noexcept;

	bool operator==(const TMatrix& m);
	bool operator!=(const TMatrix& m);

	TMatrix operator+(T elem);
	TMatrix operator-(T elem);
	TMatrix operator*(T elem);

	TMatrix operator+(const TMatrix& m);
	TMatrix operator-(const TMatrix& m);
	TMatrix operator*(const TMatrix& m);

	TMatrix operator[](int j);

	template<class T>
	friend istream& operator>>(istream& istr, TMatrix<T>& v);

	template<class T>
	friend ostream& operator<<(ostream& ostr, const TMatrix<T>& v);
};

template<class T>
inline TMatrix<T>::TMatrix(size_t _N)
{
	if (_N < 0)
	{
		throw "_N < 0";
	}

	N = _N;

	data.Resize(_N * _N);
	
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
	N = 0;
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix& m)
{
	data = m.data;
	N = m.N;
}

template<class T>
inline TMatrix<T>::TMatrix(TMatrix&& m)
{
	N = m.N;
	data = m.data;
	
	m.N = 0;
	m.data = 0;
}

template<class T>
int TMatrix<T>::GetSize() const
{
	return N;
}

template<class T>
inline TMatrix<T>::TMatrix(const TVector<T>& v)
{
	if (sqrt(v.size()) != static_cast<int>(sqrt(v.size()))
	{
		throw "Vector size not allowed";
	}
	N = sqrt(v.size());
	data = v;
}


template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix& m)
{
	if (this != &m)
	{
		N = m.N;
		data = m.data;
	}
	return *this;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(TMatrix&& m) noexcept
{
	if (this != &v)
	{
		data = m.data;
		N = m.N;

		m.N = 0;
		m.data = 0;
	}
	return *this;

}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix& m)
{
	return data == m.data;
}

template<class T>
inline bool TMatrix<T>::operator!=(const TMatrix& m)
{
	return !(*this == m);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(T elem)
{
	return TMatrix(data + elem);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(T elem)
{
	return TMatrix(data - elem);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(T elem)
{
	return TMatrix(data * elem);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix& m)
{
	if (N != m.N)
	{
		throw "Sizes should be equal";
	}
	return TMatrix(data + m.data);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix& m)
{
	if (N != m.N)
	{
		throw "Sizes should be equal";
	}
	return TMatrix(data - m.data);
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const TMatrix& m)//?
{
	if (N != m.N)
	{
		throw "Sizes should be equal";
	}

	TMatrix res(N);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				res[i * N + j] += data[i * N + k] * m.data[k * N + j];
			}
		}
	}
	return res;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator[](int j)
{
	if (j < 0 || j >= N)
	{
		throw "operator[] j < 0 || j >= N "
	}
	return TVector<T>(&data[j*N], N);
}
template<class T>
ostream& operator<<(ostream& ostr, const TMatrix<T>& m)
{
	for (int i = 0; i < m.N; i++)
	{
		for (int j = 0; j < m.N; j++)
		{
			ostr << m.data[i * m.N + j] << " ";
		}
		
		ostr << '\n';
		
	}
	
	
	return ostr;
}

template<class T>
istream& operator>>(istream& istr, TMatrix<T>& m)
{
	for (int i = 0; i < m.N * m.N; i++)
	{
		istr >> m.data[i];
	}
	return istr;
}

