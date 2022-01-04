#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "./utils/utils.hpp"
# include "./utils/pair.hpp"
# include "./utils/iterator.hpp"
# include "./utils/MapIterator.hpp"

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
		key_compare	comp;
		allocator_type	alloc;

		/** Constructor **/
		explicit Bst(value_type d = value_type(),
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : data(d)
		{
			this->left = NULL;
			this->right = NULL;
			this->parent = NULL;
			this->comp = comp;
			this->alloc = alloc;
			return ;
		}

		/** Destructor **/
		~Bst(void) {}

		/** Member Functions **/
		Bst*	search(Bst* root, value_type data)
		{
			if (root == NULL || root->data.first == data.first)
				return (root);
			if (comp(root->data.first, data.first))
				return (search(root->right, data));
			return (search(root->left, data));
		}

		Bst*	insert(Bst* root, value_type data)
		{
			Bst*	tmp;

			if (root == NULL)
				return (new Bst(data));
			if (comp(data.first, root->data.first))
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

			if (root == NULL)
				return (root);
			if (comp(root->data.first, data.first))
			{
				root->right = deleteNode(root->right, data);
				return (root);
			}
			else if (root->data.first != data.first)
			{
				root->left = deleteNode(root->left, data);
				return (root);
			}
			if (root->left == NULL)
			{
				tmp = root->right;
				delete root;
				return (tmp);
			}
			else if (root->right == NULL)
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
				while (succ->left != NULL)
				{
					parent = succ;
					succ = succ->left;
				}
				if (parent != root)
					parent->left = succ->right;
				else
					parent->right = succ->right;
				root->data = succ->data;
				delete succ;
				return (root);
			}
		}

		void	inorder(Bst* root)
		{
			if (root == NULL)
				return ;
			inorder(root->left);
			std::cout << root->data.first << " ";
			inorder(root->right);
			return ;
		}

		void	preorder(Bst* root)
		{
			if (root == NULL)
				return ;
			std::cout << root->data.first << " ";
			preorder(root->left);
			preorder(root->right);
			return ;
		}

		void	postorder(Bst* root)
		{
			if (root == NULL)
				return ;
			postorder(root->left);
			postorder(root->right);
			std::cout << root->data.first << " ";
			return ;
		}

		void	clean(Bst* root)
		{
			if (root == NULL)
				return ;
			clean(root->left);
			clean(root->right);
			delete root;
			return ;
		}
};

#endif
