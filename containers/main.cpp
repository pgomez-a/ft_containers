#include "./utils/Bst.hpp"
#include "./utils/MapIterator.hpp"

void	leaks(void)
{
	std::cout << std::endl << std::endl << std::endl;
	system("leaks a.out");
}

int	main(void)
{
	//atexit(leaks);
	{
		ft::pair<char, char>		init(0, 0);
		Bst<char, char >		Tree;
		Bst<char, char >*		root = NULL;
		int				t;

		std::cout << "Number of nodes: ";
		std::cin >> t;
		while (t--)
		{
			char			tmp;
			std::cin >> tmp;

			ft::pair<char, char>	data(tmp, tmp);
			root = Tree.insert(root, data);
		}
		Tree.inorder(root);
		std::cout << std::endl;

		ft::MapIterator<Bst<char, char> >	itOne(root);

		std::cout << std::endl;
		while (itOne.root() != itOne.begin())
			itOne--;
		while (itOne.root() != itOne.end())
		{
			std::cout << itOne << std::endl;
			itOne++;
		}
		std::cout << itOne << std::endl;
		std::cout << std::endl;
		while (itOne.root() != itOne.begin())
		{
			std::cout << itOne << std::endl;
			itOne--;
		}
		std::cout << itOne << std::endl;

		Tree.clean(root);
	}
	return (0);
}
