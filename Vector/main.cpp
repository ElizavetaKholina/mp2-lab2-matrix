#include "Vector.h"
#include <iostream>
using namespace std;

int main()
{
	int n = 3;
	TVector<int> a(n);
	
	for (int i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}

    TVector<int> b = a;

	TVector<int> c;
	c = a + b;

	cout << c;

	for (auto i = c.begin(); i != c.end(); ++i)
	{
		cout << *i << " ";
	}
}