/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:21:40 by pgomez-a          #+#    #+#             */
/*   Updated: 2022/03/17 11:49:21 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

# include <iostream>
# include "utils.hpp"
# include "pair.hpp"

template < typename T, typename Compare, typename Alloc >
class	Bst
{
	public:
		/** Member Types **/
		typedef T											value_type;
		typedef Compare										key_compare;
		typedef typename Alloc::template rebind<Bst>::other	allocator_type;
		typedef typename Alloc::reference					reference;
		typedef typename Alloc::const_reference				const_reference;
		typedef typename Alloc::pointer						pointer;
		typedef typename Alloc::const_pointer				const_pointer;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;

		/** Member Attributes **/
		value_type	data;
		Bst*		left;
		Bst*		right;
		Bst*		parent;
		int			balance;

	private:
		/** Private Member Attributes **/
		key_compare		_comp;
		allocator_type	_alloc;

	public:
		/** Constructor **/
		explicit Bst(value_type d = value_type(),
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : data(d)
		{
			this->left = 0;
			this->right = 0;
			this->parent = 0;
			this->balance = 0;
			this->_comp = comp;
			this->_alloc = alloc;
			return ;
		}

		Bst&	operator=(const Bst other)
		{
			this->data = other.data;
			this->left = other.left;
			this->right = other.right;
			this->parent = other.parent;
			this->balance = other.balance;
			this->_comp = other.key_comp();
			this->_alloc = other.get_allocator();
			return (*this);
		}

		/** Destructor **/
		~Bst(void) {}

		/** Member Functions **/
		int			get_height(Bst* root) const
		{
			int	lheight;
			int	rheight;

			if (!root)
				return (-1);
			lheight = get_height(root->left);
			rheight = get_height(root->right);
			if (lheight < rheight)
				return (rheight + 1);
			return (lheight + 1);
		}

		int			get_balance(Bst* root) const
		{
			if (!root)
				return (-1);
			return (get_height(root->left) - get_height(root->right));
		}

		size_type	max_size(void) const
		{
			return (this->_alloc.max_size());
		}

		key_compare	key_comp(void) const
		{
			return (this->_comp);
		}

		Bst*		search(Bst* root, value_type data) const
		{
			if (!root || root->data.first == data.first)
				return (root);
			if (this->_comp(root->data.first, data.first))
				return (search(root->right, data));
			return (search(root->left, data));
		}

		Bst*&		insert(Bst*& root, value_type data)
		{
			if (!root)
			{
				root = this->_alloc.allocate(1);
				this->_alloc.construct(root, Bst(data));
				return (root);
			}
			if (this->_comp(data.first, root->data.first))
			{
				root->left = insert(root->left, data);
				root->left->parent = root;
			}
			else if (data.first != root->data.first)
			{
				root->right = insert(root->right, data);
				root->right->parent = root;
			}
			root->balance = get_balance(root);
			if (root->balance > 1 && this->_comp(data.first, root->left->data.first))
				root = rotateLeftLeft(root);
			else if (root->balance < -1 && this->_comp(root->right->data.first, data.first))
				root = rotateRightRight(root);
			else if (root->balance > 1 && this->_comp(root->left->data.first, data.first))
			{
				root->left = rotateRightRight(root->left);
				root = rotateLeftLeft(root);
			}
			else if (root->balance < -1 && this->_comp(data.first, root->right->data.first))
			{
				root->right = rotateLeftLeft(root->right);
				root = rotateRightRight(root);
			}
			return (root);
		}

		Bst*		deleteNode(Bst* root, value_type data)
		{
			Bst*	tmp;
			Bst*	parent;
			Bst*	succ;

			if (!root)
				return (root);
			else if (this->_comp(root->data.first, data.first))
				root->right = deleteNode(root->right, data);
			else if (this->_comp(data.first, root->data.first))
				root->left = deleteNode(root->left, data);
			else
			{
				if (!root->left)
				{
					tmp = root->right;
					if (tmp)
						tmp->parent = root->parent;
					this->_alloc.destroy(root);
					this->_alloc.deallocate(root, 1);
					return (tmp);
				}
				else if (!root->right)
				{
					tmp = root->left;
					if (tmp)
						tmp->parent = root->parent;
					this->_alloc.destroy(root);
					this->_alloc.deallocate(root, 1);
					return (tmp);
				}
				else
				{
					parent = root;
					succ = root->right;
					while (succ->left)
					{
						parent = succ;
						succ = succ->left;
					}
					if (parent != root)
						parent->left = succ->right;
					else
						parent->right = succ->right;
					if (succ->right)
						succ->right->parent = parent;
					root->data = succ->data;
					this->_alloc.destroy(succ);
					this->_alloc.deallocate(succ, 1);
				}
			}
			root->balance = get_balance(root);
			return (root);
		}

		Bst*&		rotateLeftLeft(Bst*& root)
		{
			Bst*	tmp;
			Bst*	tmp_succ;

			tmp = root->left;
			tmp_succ = root;
			root->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = root;
			tmp->right = root;
			tmp->parent = root->parent;
			if (root->parent && root->parent->left == root)
				root->parent->left = tmp;
			else if (root->parent)
				root->parent->right = tmp;
			tmp_succ->parent = tmp;
			return (root);
		}

		Bst*&		rotateRightRight(Bst*& root)
		{
			Bst*	tmp;
			Bst*	tmp_succ;

			tmp = root->right;
			tmp_succ = root;
			root->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = root;
			tmp->left = root;
			tmp->parent = root->parent;
			if (root->parent && root->parent->left == root)
				root->parent->left = tmp;
			else if (root->parent)
				root->parent->right = tmp;
			tmp_succ->parent = tmp;
			return (root);
		}

		void		inorder(Bst* root)
		{
			if (!root)
				return ;
			inorder(root->left);
			std::cout << "> " << root->data.first << ", " << root->data.second << std::endl;
			inorder(root->right);
			return ;
		}

		void		preorder(Bst* root)
		{
			if (!root)
				return ;
			std::cout << "> " << root->data.first << ", " << root->data.second << std::endl;
			preorder(root->left);
			preorder(root->right);
			return ;
		}

		void		postorder(Bst* root)
		{
			if (!root)
				return ;
			postorder(root->left);
			postorder(root->right);
			std::cout << "> " << root->data.first << ", " << root->data.second << std::endl;
			return ;
		}

		void		clean(Bst** root)
		{
			if (!(*root))
				return ;
			if ((*root)->left)
				clean(&((*root)->left));
			if ((*root)->right)
				clean(&((*root)->right));
			(*root)->left = 0;
			(*root)->right = 0;
			this->_alloc.destroy(*root);
			this->_alloc.deallocate(*root, 1);
			*root = 0;
			return ;
		}

		/** Allocator **/
		allocator_type	get_allocator(void) const
		{
			return (this->_alloc);
		}
};

#endif
