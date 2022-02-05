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
	atexit(leaks);

	int psize;
	std::map<char,int> mymap;
	std::pair<char,int>* p;

	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(std::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);
	return 0;
}
