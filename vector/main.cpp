#include <iostream>
#include <vector>
#include "vector.hpp"

void	leaks(void)
{
	system("leaks a.out");
}

int	main(void)
{
	std::size_t			val = 3;
	ft::vector<int>			vct(val, 2);
	ft::vector<int>::iterator	begin;
	ft::vector<int>::iterator	end;

	atexit(leaks);

	begin = vct.begin();
	end = vct.end();
	while (begin != end)
	{
		std::cout << *begin << std::endl;
		begin++;
	}
	return (0);
}
