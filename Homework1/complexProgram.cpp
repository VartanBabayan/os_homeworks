#include <iostream>
#include <algorithm>
#include <vector>
#include "Complex.h"

int main()
{
	int size;
	std::cin >> size;

	std::vector<Complex> vcomplex;
	for (int i = 0; i < size; ++i)
	{
		double a, bi;
		std::cin >> a >> bi;
		vcomplex.emplace_back(a, bi);
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (vcomplex[j].get_absolute_value() > vcomplex[j].get_absolute_value())
			{
				std::swap(vcomplex[j], vcomplex[j + 1]);
			}
		}
	}

	for (int i = 0; i < size; ++i)
	{
		vcomplex[i].print();
	}
}