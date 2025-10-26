#include <iostream>
#include <algorithm>


using namespace std;

template<class T>
class TVectorIterator;

template <class T>
class TVector
{
private:
	size_t sz;
	T* pMem;

public:
	TVector(size_t size); 
	TVector();
	TVector(T* arr, size_t size);
	TVector(const TVector& v); 
	TVector(TVector&& v) noexcept;
	~TVector();
	TVector& operator=(const TVector& v);
	TVector& operator=(TVector&& v) noexcept;
	TVector Resize(size_t newsize);

	size_t size() const noexcept;

	//индексация
	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	//индексация с контролем
	T& at(size_t index);
	const T& at(size_t index) const;



	//сравнение
	bool operator==(const TVector& v) const noexcept;
	bool operator!=(const TVector& v) const noexcept;

	//скалярные операции
	TVector operator+(T elem);
	TVector operator-(T elem);
	TVector operator*(T elem);

	//векторные операции
	TVector operator+(const TVector& v);
	TVector operator-(const TVector& v);
	T operator*(const TVector& v) noexcept(noexcept(T()));
	
	TVectorIterator<T> begin();
	TVectorIterator<T> end();

	template<class T>
	friend istream& operator>>(istream& istr, TVector<T>& v); 

	template<class T>
	friend ostream& operator<<(ostream& ostr, const TVector<T>& v); 
};

template<class T>
inline TVector<T>::TVector(size_t size)
{
	if (size <= 0)
	{
		throw "Size should be >= 0";
	}
	else
	{
		sz = size;
		pMem = new T[size];
	}
}

template<class T>
inline TVector<T>::TVector()
{
	sz = 0;
	pMem = nullptr;
}



template<class T>
inline TVector<T>::TVector(T* arr, size_t size)
{
	if (size <= 0)
	{
		throw "Size should be >= 0";
	}
	if (arr == nullptr)
	{
		throw "Arr should be != 0";
	}
	sz = size;
	pMem = new T[size];

	for (int i = 0; i < sz; i++)
	{
		pMem[i] = arr[i];
	}

}

template<class T>
inline TVector<T>::TVector(const TVector& v)
{
	if (v.pMem == nullptr)
	{
		sz = 0;
		pMem = nullptr;
	}
	else
	{
		sz = v.sz;
		pMem = new T[sz];
		for (int i = 0; i < sz; i++)
		{
			pMem[i] = v.pMem[i];
		}
	}
}

template<class T>
inline TVector<T>::TVector(TVector&& v) noexcept
{
	sz = v.sz;
	pMem = v.pMem;

	v.pMem = nullptr;
	v.sz = 0;
}

template<class T>
inline TVector<T>::~TVector()
{
	if (pMem != nullptr)
	{
      delete[] pMem;
	  sz = 0;
	}
}

template<class T>
inline TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{
	if (this != &v)
	{
		if (pMem != nullptr)
		{
			delete[] pMem;
		}

		if (v.pMem == nullptr)
		{
			sz = 0;
			pMem = nullptr;
		}
		else
		{
			sz = v.sz;
			pMem = new T[sz];
			for (int i = 0; i < sz; i++)
			{
				pMem[i] = v.pMem[i];
			}
		}
	}
	return *this;
}

template<class T>
inline TVector<T>& TVector<T>::operator=(TVector&& v) noexcept
{
	if (this != &v)
	{
		if (pMem != nullptr)
		{
			delete[] pMem;
		}
		sz = v.sz;
	    pMem = v.pMem;

	    v.pMem = nullptr;
	    v.sz = 0;
	}
	return *this;
	
}

template<class T>
inline TVector<T> TVector<T>::Resize(size_t newsize)
{
	if (newsize == 0)
	{
		sz = 0;
		delete[] pMem;
		pMem = nullptr;
	}
	else
	{
		T* _pMem = new T[newsize];
		for (int i = 0; i < min(sz, newsize); i++)
		{
			_pMem[i] = pMem[i];	
		}
		delete[] pMem;
		pMem = _pMem;
		sz = newsize;

	}
	return *this;
}

template<class T>
inline size_t TVector<T>::size() const noexcept
{
	return sz;
}

template<class T>
inline T& TVector<T>::operator[](size_t index)
{
	return pMem[index];
}

template<class T>
inline const T& TVector<T>::operator[](size_t index) const
{
	return pMem[index];
}

template<class T>
inline T& TVector<T>::at(size_t index)
{
	if (pMem == nullptr)
	{
		throw "operator[] pMem == nullptr";
	}
	if (index >= sz)
	{
		throw "operator[] index >= sz";
	}
	return pMem[index];
}

template<class T>
inline const T& TVector<T>::at(size_t index) const
{
	if (pMem == nullptr)
	{
		throw "operator[] pMem == nullptr";
	}
	if (index >= sz)
	{
		throw "operator[] index >= sz";
	}
	return pMem[index];
}

template<class T>
inline bool TVector<T>::operator==(const TVector& v) const noexcept
{
	if (sz != v.sz)
	{
		return false;
	}
	for (int i = 0; i < sz; i++)
	{
		if (pMem[i] != v.pMem[i])
		{
			return false;
		}
	}
	return true;
}

template<class T>
inline bool TVector<T>::operator!=(const TVector& v) const noexcept
{
	return !(*this == v);
}

template<class T>
inline TVector<T> TVector<T>::operator+(T elem)
{
	TVector res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] = res.pMem[i] + elem;
	}
	return res;
}

template<class T>
inline TVector<T> TVector<T>::operator-(T elem)
{
	TVector res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] = res.pMem[i] - elem;
	}
	return res;
}

template<class T>
inline TVector<T> TVector<T>::operator*(T elem)
{
	TVector res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] = res.pMem[i] * elem;
	}
	return res;
}

template<class T>
inline TVector<T> TVector<T>::operator+(const TVector& v)
{
	if (sz != v.sz)
	{
		throw "operator + size should be equal";
	}

	TVector res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] = res.pMem[i] + v.pMem[i];
	}
	return res;
}

template<class T>
inline TVector<T> TVector<T>::operator-(const TVector& v)
{
	if (sz != v.sz)
	{
		throw "operator - size should be equal";
	}

	TVector res(*this);
	for (int i = 0; i < sz; i++)
	{
		res.pMem[i] = res.pMem[i] - v.pMem[i];
	}
	return res;
}

template<class T>
inline T TVector<T>::operator*(const TVector& v) noexcept(noexcept(T()))
{
	if (sz != v.sz)
	{
		throw "operator * size should be equal";
	}

	T res = T();
	for (int i = 0; i < sz; i++)
	{
		res += pMem[i] * v.pMem[i];
	}
	return res;
}

template<class T>
ostream& operator<<(ostream& ostr, const TVector<T>& v)
{
	ostr << "(";
	if (v.sz > 0)
	{
		for (int i = 0; i < v.sz - 1; i++)
		{
			ostr << v[i] << ", ";
		}
		ostr << v[v.sz - 1];
	}
	
	ostr << ")";
	return ostr;
}

template<class T>
istream& operator>>(istream& istr, TVector<T>& v)
{
	for (int i = 0; i < v.sz; i++)
	{
		istr >> v.pMem[i];
	}
	return istr;
}

template<class T>
inline TVectorIterator<T> TVector<T>::begin()
{
	return TVectorIterator<T>(*this, 0);
}

template<class T>
inline TVectorIterator<T> TVector<T>::end()
{
	return TVectorIterator<T>(*this, sz);
}

template <class T>
class TVectorIterator
{
private:
	TVector<T>& vector;
	int index;
public:
	TVectorIterator(TVector<T>& v);
	TVectorIterator(TVector<T>& v, int ind);
	TVectorIterator(const TVectorIterator<T>& iv);

	T& operator*();
	TVectorIterator<T>& operator++ ();
	TVectorIterator<T>& operator-- ();

	bool operator==(const TVectorIterator<T>& v);
	bool operator!=(const TVectorIterator<T>& v);


};

template<class T>
inline TVectorIterator<T>::TVectorIterator(TVector<T>& v) : vector(v)
{
	index = 0;
}

template<class T>
inline TVectorIterator<T>::TVectorIterator(TVector<T>& v, int ind) : vector(v)
{
	index = ind;
}

template<class T>
inline TVectorIterator<T>::TVectorIterator(const TVectorIterator<T>& iv) : vector(iv.vector), index(iv.index)
{
}

template<class T>
inline T& TVectorIterator<T>::operator*()
{
	return vector[index];
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator++()
{
	if (index < vector.size())
	{
		index ++;
	}
	return *this;
}

template<class T>
inline TVectorIterator<T>& TVectorIterator<T>::operator--()
{
	if (index > 0)
	{
		index--;
	}
	return *this;
}

template<class T>
inline bool TVectorIterator<T>::operator==(const TVectorIterator<T>& v)
{
	if (&vector == &(v.vector) && index == v.index)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
inline bool TVectorIterator<T>::operator!=(const TVectorIterator<T>& v)
{
	return !(*this == v);
}

