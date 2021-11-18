#include <iostream>
#include <vector>
#include "vector.hpp"

void	leaks(void)
{
	system("leaks container");
}

int	main(void)
{
	atexit(leaks);

	{
		std::cout << "STD::VECTOR" << std::endl;
		std::size_t		val = 13;
		std::vector<int>	vct(val, 3);
		std::size_t		index = 3;

		std::cout << "Size: " << vct.size() << std::endl;
		std::cout << "Capa: " << vct.capacity() << std::endl;
		vct[val - 1] = 4;
		std::cout << "vct[" << index << "] --> " << vct.back() << std::endl;
		vct.back() = 10;
		std::cout << "vct[" << index << "] --> " << vct.back() << std::endl;
	}
	{
		std::cout << "FT::VECTOR" << std::endl;
		std::size_t		val = 13;
		ft::vector<int>		ft_vct(val, 3);
		std::size_t		index = 3;
		
		std::cout << "Size: " << ft_vct.size() << std::endl;
		std::cout << "Capa: " << ft_vct.capacity() << std::endl;
		ft_vct[val - 1] = 4;
		std::cout << "ft_vct[" << index << "] --> " << ft_vct.back() << std::endl;
		ft_vct.back() = 10;
		std::cout << "ft_vct[" << index << "] --> " << ft_vct.back() << std::endl;
	}
	return (0);
}
