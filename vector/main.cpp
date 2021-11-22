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

  std::reverse_iterator<std::vector<char>::iterator> from,until;

  from = myvector.rbegin();
  until = myvector.rend();

  std::cout << "myvector has " << (until-from) << " elements.\n";
	}
	std::cout << std::endl;
	{
				  ft::vector<char> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i + 'A');

  ft::reverse_iterator<ft::vector<char>::iterator> from,until;

  from = myvector.rbegin();
  until = myvector.rend();

  std::cout << "myvector has " << (until-from) << " elements.\n";
	}
	return 0;
}
