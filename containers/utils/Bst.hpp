#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "utils.hpp"
# include "pair.hpp"

template < typename Key, typename T, typename Compare = std::less<Key>,
	typename Alloc = std::allocator<ft::pair<Key, T> > >
class	Bst
{
	public:
		/** Member Types **/
		typedef Key					key_type;
		typedef T					mapped_type;
		typedef ft::pair<Key, T>			value_type;
		typedef Compare					key_compare;
		typedef std::ptrdiff_t				difference_type;
		typedef std::allocator<Bst>			allocator_type;
		typedef value_type&				reference;
		typedef const value_type&			const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer		const_pointer;

		/** Member Attributes **/
		value_type	data;
		Bst*		left;
		Bst*		right;
		Bst*		parent;
		int		balance;

	private:
		/** Private Member Attributes **/
		key_compare	_comp;
		allocator_type	_alloc;

	public:
		/** Constructor **/
		explicit Bst(value_type d = value_type(),
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : data(d)
		{
			this->left = nullptr;
			this->right = nullptr;
			this->parent = nullptr;
			this->balance = 0;
			this->_comp = comp;
			this->_alloc = alloc;
			return ;
		}

		/** Destructor **/
		~Bst(void) {}

		/** Member Functions **/
		Bst*	search(Bst* root, value_type data)
		{
			if (root == nullptr || root->data.first == data.first)
				return (root);
			if (this->_comp(root->data.first, data.first))
				return (search(root->right, data));
			return (search(root->left, data));
		}

		Bst*&	insert(Bst*& root, value_type data)
		{
			int	next_bal;
			Bst*	tmp;

			next_bal = -999;
			if (root == nullptr)
			{
				tmp = this->_alloc.allocate(1);
				this->_alloc.construct(tmp, Bst(data));
				root = tmp;
				return (root);
			}
			if (this->_comp(data.first, root->data.first))
			{
				if (root->left != nullptr)
					next_bal = root->left->balance;
				tmp = insert(root->left, data);
				root->left = tmp;
				tmp->parent = root;
				if (!((root->left->balance < 0 && next_bal <= root->left->balance && root->left->balance < 0)
					|| (root->left->balance > 0 && 0 < root->left->balance && root->left->balance <= next_bal)
					|| (root->left->balance == 0 && root->left->data.first != data.first)))
					root->balance -= 1;
			}
			else if (data.first != root->data.first)
			{
				if (root->right != nullptr)
					next_bal = root->right->balance;
				tmp = insert(root->right, data);
				root->right = tmp;
				tmp->parent = root;
				if (!((root->right->balance < 0 && next_bal <= root->right->balance && root->right->balance < 0)
					|| (root->right->balance > 0 && 0 < root->right->balance && root->right->balance <= next_bal)
					|| (root->right->balance == 0 && root->right->data.first != data.first)))
					root->balance += 1;
			}
			return (this->rebalance(root));
		}

		Bst*	deleteNode(Bst* root, value_type data)
		{
			Bst*	tmp;

			if (root == nullptr)
				return (root);
			if (this->_comp(root->data.first, data.first))
			{
				root->right = deleteNode(root->right, data);
				return (root);
			}
			else if (root->data.first != data.first)
			{
				root->left = deleteNode(root->left, data);
				return (root);
			}
			if (root->left == nullptr)
			{
				tmp = root->right;
				if (tmp != nullptr)
					tmp->parent = root->parent;
				this->_alloc.destroy(root);
				this->_alloc.deallocate(root, 1);
				return (tmp);
			}
			else if (root->right == nullptr)
			{
				tmp = root->left;
				if (tmp != nullptr)
					tmp->parent = root->parent;
				this->_alloc.destroy(root);
				this->_alloc.deallocate(root, 1);
				return (tmp);
			}
			else
			{
				Bst*	parent;
				Bst*	succ;

				parent = root;
				succ = root->right;
				while (succ->left != nullptr)
				{
					parent = succ;
					succ = succ->left;
				}
				if (parent != root)
					parent->left = succ->right;
				else
					parent->right = succ->right;
				root->data.first = succ->data.first;
				root->data.second = succ->data.second;
				root->parent = succ->parent;
				this->_alloc.destroy(succ);
				this->_alloc.deallocate(succ, 1);
				return (root);
			}
		}

		Bst*&	rebalance(Bst*& root)
		{
			if (root->balance == -2 && root->left != nullptr && root->left->balance == -1)
				return (this->rotateRight(0, root));
			else if (root->balance == 2 && root->right != nullptr && root->right->balance == 1)
				return (this->rotateLeft(0, root));
			else if (root->balance == -2 && root->left != nullptr && root->left->balance == 1)
				return (this->rotateLeftRight(root));
			else if (root->balance == 2 && root->right != nullptr && root->right->balance == -1)
				return (this->rotateRightLeft(root));
			return (root);
		}

		Bst*&	rotateRight(int mode, Bst*& root)
		{
			Bst*	tmp;

			tmp = root;
			root = root->left;
			root->parent = tmp->parent;
			if (root->parent != nullptr)
				root->parent->left = root;
			tmp->parent = root;
			tmp->left = root->right;
			if (tmp->left != nullptr)
				tmp->left->parent = tmp;
			root->right = tmp;
			root->balance = 0;
			if (mode != 1)
				root->right->balance = 0;
			return (root);
		}

		Bst*&	rotateLeft(int mode, Bst*& root)
		{
			Bst*	tmp;

			tmp = root;
			root = root->right;
			root->parent = tmp->parent;
			if (root->parent != nullptr && root->parent->parent != nullptr)
				root->parent->right = root;
			else if (root->parent != nullptr)
				root->parent->left = root;
			tmp->parent = root;
			tmp->right = root->left;
			if (tmp->right != nullptr)
				tmp->right->parent = tmp;
			root->left = tmp;
			root->balance = 0;
			if (mode != 1)
				root->left->balance = 0;
			return (root);
		}

		Bst*&	rotateLeftRight(Bst*& root)
		{
			int	mode;
			Bst*	tmp;

			mode = 0;
			if (root->left->right->balance == 1)
				root->left->balance = -1;
			else if (root->left->right->balance == -1)
			{
				root->balance = 1;
				root->left->balance = 0;
				mode = 1;
			}
			else
				root->left->balance = 0;
			tmp = root->left;
			root->left = tmp->right;
			root->left->parent = root;
			tmp->right = root->left->left;
			if (tmp->right != nullptr)
				tmp->right->parent = tmp;
			root->left->left = tmp;
			tmp->parent = root->left;
			return (this->rotateRight(mode, root));
		}

		Bst*&	rotateRightLeft(Bst*& root)
		{
			int	mode;
			Bst*	tmp;

			mode = 0;
			if (root->right->left->balance == 1)
				root->right->balance = -1;
			else if (root->right->left->balance == -1)
			{
				root->balance = 1;
				root->right->balance = 0;
				mode = 1;
			}
			else
				root->right->balance = 0;
			tmp = root->right;
			root->right = tmp->left;
			root->right->parent = root;
			tmp->left = root->right->right;
			if (tmp->left != nullptr)
				tmp->left->parent = tmp;
			root->right->right = tmp;
			tmp->parent = root->right;
			return (this->rotateLeft(mode, root));
		}

		void	inorder(Bst* root)
		{
			if (root == nullptr)
				return ;
			inorder(root->left);
			std::cout << "(" << root->data.first << ") -> " << root->balance << std::endl;
			inorder(root->right);
			return ;
		}

		void	preorder(Bst* root)
		{
			if (root == nullptr)
				return ;
			std::cout << "(" << root->data.first << ") -> " << root->balance << std::endl;
			preorder(root->left);
			preorder(root->right);
			return ;
		}

		void	postorder(Bst* root)
		{
			if (root == nullptr)
				return ;
			postorder(root->left);
			postorder(root->right);
			std::cout << root->data.first << " ";
			return ;
		}

		void	clean(Bst** root)
		{
			if (*root == nullptr)
				return ;
			if ((*root)->left != nullptr)
				clean(&((*root)->left));
			if ((*root)->right != nullptr)
				clean(&((*root)->right));
			(*root)->left = nullptr;
			(*root)->right = nullptr;
			this->_alloc.destroy(*root);
			this->_alloc.deallocate(*root, 1);
			*root = nullptr;
			return ;
		}
};

#endif
