#include "Bst.hpp"

void	leaks(void)
{
	std::cout << std::endl << std::endl << std::endl;
	system("leaks a.out");
}

int	main(void)
{
	atexit(leaks);
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
		Tree.clean(root);
	}
	return (0);
}
