#include <iostream>
#include <random>
#include <vector>

void swap(std::vector<int> *vec, size_t i, size_t j)
{
	//std::cout << "swap vec->at(i) = " << vec->at(i) << " vec->at(j) = " << vec->at(j) << std::endl;
	int temp = vec->at(i);
	vec->at(i) = vec->at(j);
	vec->at(j) = temp;
	//std::cout << "swap vec->at(i) = " << vec->at(i) << " vec->at(j) = " << vec->at(j) << std::endl;
}

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

void bubbleSort(std::vector<int> *vec)
{
	if (vec->size() < 2)
	{
		return;
	}
	
	for (size_t i = 0; i < vec->size()-1; i++)
	{
		bool swapped = false;
		for (size_t j = 0; j < vec->size()-1-i; j++)
		{
			if (vec->at(j) > vec->at(j+1))
			{
				swap(vec, j, j+1);
				swapped = true;
			}
		}
		if (!swapped)
		{
			break;
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
	std::vector<int> *numbers = generate(32*1024);
	std::cout << "Sorting" << std::endl;
	bubbleSort(numbers);
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
