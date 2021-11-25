#include <iostream>
#include <vector>
#include "./containers/ft_containers.hpp"

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
	ft::vector<int>	vct(4, 4);
	ft::vector<int>	tmp(vct.begin(), vct.end());

	return 0;
}
