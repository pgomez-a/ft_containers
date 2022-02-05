#include "map_tests.hpp"

void	leaks(void)
{
	char	val;

	std::cout << std::endl;
	std::cout << "\033[1m\033[31mLEAKS\033[39m\033[0m" << std::endl;
	system("leaks -_map_test");
	std::cout << "Press ENTER to continue...";
	val = getchar();
}

int	main(void)
{
	system("clear");
	atexit(leaks);
	std::cout << "\033[1m\033[33m- MAP TEST\033[39m\033[0m" << std::endl;
	{
		std::cout << "\033[1m\033[35mstd::map\033[39m\033[0m" << std::endl;
	}
	std::cout << std::endl;
	{
		std::cout << "\033[1m\033[35mft::map\033[39m\033[0m" << std::endl;
	}
	return (0);
}
