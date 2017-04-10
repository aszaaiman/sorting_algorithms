#include <iostream>
#include <limits>
#include <math.h>
#include <random>
#include <vector>
#include <algorithm>

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

int calcDigits(int i)
{
	int digits = 0;
	while (i > 0)
	{
		i /= 10;
		digits++;
	}
	return digits;
}

int getDigit(int i, int idx)
{
	i /= pow(10,idx-1);
	return i % 10;
}

void clearBuckets(std::array<std::vector<int>, 10> *buckets)
{
	for (auto & b : *buckets)
	{
		b.clear();
	}
}

void radixSort(std::vector<int> *vec)
{
	std::array< std::vector<int>, 10> buckets = { {} };
	
	int longestNumber = 1;
	
	for (auto & n : *vec)
	{
		longestNumber = std::max(calcDigits(n), longestNumber);
		int d = getDigit(n,1);
		buckets[d].push_back(n);
	}
	
	vec->clear();
	
	for (int i = 0; i <= 9; i++)
	{
		auto &bucket = buckets[i];
		vec->insert(vec->end(), bucket.begin(), bucket.end());
	}
	
	clearBuckets(&buckets);
	
	for (int k = 1; k <= longestNumber; k++)
	{
		for (auto & n : *vec)
		{
			int d = getDigit(n,k);
			buckets[d].push_back(n);
		}
		
		vec->clear();
		
		for (int i = 0; i <= 9; i++)
		{
			auto &bucket = buckets[i];
			vec->insert(vec->end(), bucket.begin(), bucket.end());
		}
		
		clearBuckets(&buckets);		
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
	size_t n = 32*1024*1024;
	size_t printNMax = 1000;
	size_t printN = std::min(printNMax,n);	
	std::vector<int> *numbers = generate(n);
	std::cout << "Sorting" << std::endl;
	radixSort(numbers);
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
