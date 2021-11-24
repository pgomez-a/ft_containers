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

template < typename T >
typename ft::enable_if<ft::is_integral<T>::value, void>::type	function(void)
{
	std::cout << "is_integral" << std::endl;
	return ;
}

template < typename T >
typename ft::enable_if<!ft::is_integral<T>::value, void >::type	function(void)
{
	std::cout << "not_integral" << std::endl;
	return ;
}

int main ()
{
	ft::vector<char>	vct(4, 5);
	std::cout << std::endl;
	return 0;
}
