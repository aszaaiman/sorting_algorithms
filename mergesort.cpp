#include <iostream>
#include <random>
#include <vector>

void print(std::vector<int> &vec)
{
	for (auto &v : vec)
	{
		std::cout << v << " ";
	}
	std::cout << std::endl;
}

std::vector<int>* generate(size_t n)
{
	std::cout << "Generating random numbers" << std::endl;
	
	std::random_device seeder;
	std::mt19937 rng(seeder());
	std::uniform_int_distribution<int> gen(0, 1000*1000);

	auto *v = new std::vector<int>();
	v->reserve(n);
	for (size_t i = 0; i < n; i++)
	{
		v->push_back(gen(rng));
	}
	
	std::cout << "Done!" << std::endl;
	
	return v;	
}

void merge(std::vector<int> *v1, std::vector<int> *v2, std::vector<int> *dest)
{
	auto it1 = v1->begin();
	auto it2 = v2->begin();	
	auto itdest = dest->begin();
	while (it1 < v1->end() && it2 < v2->end())
	{
		if (*it1 <= *it2)
		{
			*itdest = *it1;
			it1++;
		}
		else
		{
			*itdest = *it2;
			it2++;
		}
		itdest++;
	}
	for (;it1 < v1->end();it1++)
	{
		*itdest = *it1;
		itdest++;
	}
	for (;it2 < v2->end();it2++)
	{
		*itdest = *it2;
		itdest++;
	}
}

void mergeSort(std::vector<int> *vec)
{
	if (vec->size() == 1)
	{
		return;
	}
	std::size_t const halfSize = vec->size() / 2;
	auto *left = new std::vector<int>(vec->begin(), vec->begin() + halfSize);
	auto *right = new std::vector<int>(vec->begin() + halfSize, vec->end());
	mergeSort(left);
	mergeSort(right);
	merge(left, right, vec);
	delete left;
	delete right;
}

void test(std::vector<int> *vec)
{
	std::cout << "Testing" << std::endl;
	auto it = vec->begin();
	auto end = vec->end();
	int n = *it;
	it++;
	while (it < end)
	{
		if (n > *it)
		{
			std::cout << "Fail!" << std::endl;
			return;
		}
		n = *it;
		it++;
	}
	std::cout << "OK!" << std::endl;	
}

int main()
{
	std::vector<int> *numbers = generate(32*1024*1024);
	std::cout << "Sorting" << std::endl;
	mergeSort(numbers);
	//print(numbers);	
	std::cout << "Done!" << std::endl;
	std::cout << "First 1000 numbers:" << std::endl;
	for (size_t i = 0; i < 1000; i++)
	{
		std::cout << numbers->at(i) << " ";
	}
	std::cout << std::endl;
	test(numbers);
	delete numbers;
	return 0;
}
