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
		std::vector<char> foo (3,'1');   // three ints with a value of 100
		std::vector<char> bar (5,'2');   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (std::vector<char>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (std::vector<char>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << std::endl << std::endl;;
	{
		ft::vector<char> foo (3,'1');   // three ints with a value of 100
		ft::vector<char> bar (5,'2');   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo contains:";
		for (ft::vector<char>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		std::cout << "bar contains:";
		for (ft::vector<char>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << std::endl;

	return 0;
}
