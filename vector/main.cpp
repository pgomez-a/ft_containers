#include <iostream>
#include <vector>
#include "vector.hpp"

void	leaks(void)
{
	system("leaks container");
}

template < typename Iter >
void	show_elems(Iter begin, Iter end)
{
	while (begin != end)
	{
		std::cout << *begin << "  ";
		begin++;
	}
	std::cout << std::endl;
}

int main ()
{
	atexit(leaks);
	{
		std::vector<char> 	myvector;

		// set some initial content:
		for (int i=1;i<10;i++) myvector.push_back(i + 'A');

		myvector.reserve(30);
		show_elems(myvector.begin(), myvector.end());
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capa: " << myvector.capacity() << std::endl;
		myvector.resize(20, '7');
		show_elems(myvector.begin(), myvector.end());
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capa: " << myvector.capacity() << std::endl;
	}
	std::cout << std::endl;
	{
		ft::vector<char> 	myvector;

		// set some initial content:
		for (int i=1;i<10;i++) myvector.push_back(i + 'A');

		myvector.reserve(30);
		show_elems(myvector.begin(), myvector.end());
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capa: " << myvector.capacity() << std::endl;
		myvector.resize(20, '7');
		show_elems(myvector.begin(), myvector.end());
		std::cout << "size: " << myvector.size() << std::endl;
		std::cout << "capa: " << myvector.capacity() << std::endl;
	}
	std::cout << std::endl;

	return 0;
}
