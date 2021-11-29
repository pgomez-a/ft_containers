#ifndef BENCHMARKS_HPP

#	include <ctime>

class Timer
{

	std::clock_t _start;

public:
	Timer();
	Timer(const Timer &ref);
	Timer &operator=(const Timer &ref);
	~Timer();
	void start();
	std::clock_t stop();
};

#	include "../../containers/vector.hpp"
#	include <iostream>
#	include <vector>

// Vector benchmark
// Vector must be a vector of ints
template <typename VectorType>
std::clock_t v_insert_growing(size_t times, VectorType vector)
{
	Timer t;
	t.start();

	int tmp = 0;

	for (size_t i = 0; i < times; i++)
	{
		vector.push_back(i); // insert a constantly growing range of integers
		tmp = vector[i];
	}

	{

		VectorType newVector(vector); // copy and destruction
	}

	vector.erase(vector.begin(), vector.end()); // erase

	return t.stop();
}

void benchmark_vector();

#endif // !BENCHMARKS_HPP
