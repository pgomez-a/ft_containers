#include "./utils/Bst.hpp"
#include "./utils/MapIterator.hpp"
#include "map.hpp"
#include <map>

void	leaks(void)
{
	std::cout << std::endl << std::endl << std::endl;
	system("leaks a.out");
}

int	main(void)
{
	//atexit(leaks);

	std::map<char, int>	it;
	ft::map<char, int>	mymap;

	std::cout << it.max_size() << std::endl;
	std::cout << mymap.max_size() << std::endl;
	return 0;
}
