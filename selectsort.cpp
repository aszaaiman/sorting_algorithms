#include <iostream>
#include <limits>
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

void swap(std::vector<int> *vec, size_t i, size_t j)
{
	//std::cout << "swap vec->at(i) = " << vec->at(i) << " vec->at(j) = " << vec->at(j) << std::endl;
	int temp = vec->at(i);
	vec->at(i) = vec->at(j);
	vec->at(j) = temp;
	//std::cout << "swap vec->at(i) = " << vec->at(i) << " vec->at(j) = " << vec->at(j) << std::endl;
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

void selectionSort(std::vector<int> *vec)
{
	for (size_t i = 0; i < vec->size(); i++)
	{
		int current = vec->at(i);
		int minSelected = std::numeric_limits<int>::max();		
		int minIndex = -1;
		for (size_t j = i; j < vec->size(); j++)
		{
			int selected = vec->at(j);
			if (selected < minSelected)
			{
				minSelected = selected;
				minIndex = j;
			}			
		}
		if (minSelected < current && minIndex > -1)
		{
			swap(vec,i,minIndex);
		}
	}	
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
	size_t n = 32*1024;
	size_t printNMax = 1000;
	size_t printN = std::min(printNMax,n);	
	std::vector<int> *numbers = generate(n);
	std::cout << "Sorting" << std::endl;
	selectionSort(numbers);
	//print(numbers);	
	std::cout << "Done!" << std::endl;
	std::cout << "First " << printN << " numbers:" << std::endl;
	for (size_t i = 0; i < printN; i++)
	{
		std::cout << numbers->at(i) << " ";
	}
	std::cout << std::endl;
	test(numbers);
	delete numbers;
	return 0;
}
