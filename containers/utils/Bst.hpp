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
		typedef Alloc					allocator_type;
		typedef value_type&				reference;
		typedef const value_type&			const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer		const_pointer;

		/** Member Attributes **/
		value_type	data;
		Bst*		left;
		Bst*		right;
		Bst*		parent;

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

		Bst*	insert(Bst* root, value_type data) // NOTE: use allocator instead of new
		{
			Bst*	tmp;

			if (root == nullptr)
				return (new Bst(data));
			if (this->_comp(data.first, root->data.first))
			{
				tmp = insert(root->left, data);
				root->left = tmp;
				tmp->parent = root;
			}
			else if (data.first != root->data.first)
			{
				tmp = insert(root->right, data);
				root->right = tmp;
				tmp->parent = root;
			}
			return (root);
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
				delete root;
				return (tmp);
			}
			else if (root->right == nullptr)
			{
				tmp = root->left;
				delete root;
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
				delete succ;
				return (root);
			}
		}

		void	inorder(Bst* root)
		{
			if (root == nullptr)
				return ;
			inorder(root->left);
			std::cout << root->data.first << " ";
			inorder(root->right);
			return ;
		}

		void	preorder(Bst* root)
		{
			if (root == nullptr)
				return ;
			std::cout << root->data.first << " ";
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
			delete *root;
			*root = nullptr;
			return ;
		}
};

#endif
