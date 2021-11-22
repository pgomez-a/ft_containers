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
		std::vector<char> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i + 'A');

		typedef std::vector<char>::iterator iter_type;

		iter_type from (myvector.begin());                     //   ^

		iter_type until (myvector.end());                      //                       ^


		std::reverse_iterator<iter_type> rev_until (from);     // ^

		std::reverse_iterator<iter_type> rev_from (until);     //                     ^

		std::cout << "myvector:";
		while (rev_from != rev_until)
			std::cout << ' ' << *rev_from++;
		std::cout << '\n';
	}
	std::cout << std::endl;
	{
		ft::vector<char> myvector;
		for (int i=0; i<10; i++) myvector.push_back(i + 'A');

		typedef ft::vector<char>::iterator iter_type;

		iter_type from (myvector.begin());                     //   ^

		iter_type until (myvector.end());                      //                       ^


		ft::reverse_iterator<iter_type> rev_until (from);     // ^

		ft::reverse_iterator<iter_type> rev_from (until);     //                     ^

		std::cout << "myvector:";
		while (rev_from != rev_until)
			std::cout << ' ' << *rev_from++;
		std::cout << '\n';
	}
	return 0;
}
