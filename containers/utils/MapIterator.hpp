/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:25:25 by pgomez-a          #+#    #+#             */
/*   Updated: 2022/03/17 11:56:34 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"
# include "Bst.hpp"

namespace ft
{

template < typename Node, typename T>
class MapIterator
{
	public:
		/** Member Types **/
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef typename ft::iterator_traits<Node>::value_type		node;
		typedef typename ft::iterator_traits<Node>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Node>::pointer			nodePtr;
		typedef typename ft::iterator_traits<Node>::reference		nodeRef;
		typedef T													value_type;
		typedef T*													pointer;
		typedef T&													reference;

	private:
		/** Private Member Attributes **/
		nodePtr	_node;
		nodePtr	_beg;
		nodePtr	_end;

	public:
		/** Constructors **/
		MapIterator(nodePtr node = 0) : _node(node)
		{
			nodePtr	tmp(node);

			if (node && (tmp || tmp == this->_end))
			{
				while (tmp->parent && tmp->parent->parent)
					tmp = tmp->parent;
				while (tmp->left)
					tmp = tmp->left;
				this->_beg = tmp;
				tmp = node;
				while (tmp->parent)
					tmp = tmp->parent;
				this->_end = tmp;
			}
			else
			{
				this->_beg = 0;
				this->_end = 0;
			}
			return ;
		}

		template < typename UNode, typename U >
		MapIterator(const MapIterator<UNode, U>& other)
			: _node(other.root()), _beg(other.begin()), _end(other.end())
		{
			return ;
		}

		/** Destructor **/
		~MapIterator(void) {}

		/** Assignation Operator **/
		MapIterator&	operator=(const MapIterator& other)
		{
			this->_node = other.root();
			this->_beg = other.begin();
			this->_end = other.end();
			return (*this);
		}

		/** Member Functions **/
		nodePtr	root(void) const
		{
			return (this->_node);
		}

		nodePtr	begin(void) const
		{
			return (this->_beg);
		}

		nodePtr	end(void) const
		{
			return (this->_end);
		}

		/** Member Functions **/
		reference		operator*(void) const
		{
			return (this->_node->data);
		}

		pointer			operator->(void) const
		{
			return (&(this->_node->data));
		}

		MapIterator&	operator++(void)
		{
			nodePtr	output;

			output = this->_node;
			if (output && output->right)
			{
				output = output->right;
				while (output->left)
					output = output->left;
			}
			else if (output != this->_end)
			{
				while (output->parent && output != output->parent->left)
					output = output->parent;
				output = output->parent;
			}
			this->_node = output;
			return (*this);
		}

		MapIterator		operator++(int)
		{
			MapIterator	output(*this);

			++(*this);
			return (output);
		}

		MapIterator&	operator--(void)
		{
			nodePtr	output;

			output = this->_node;
			if (output->left)
			{
				output = output->left;
				while (output->right)
					output = output->right;
			}
			else if (output != this->_beg)
			{
				while (output->parent && output != output->parent->right)
					output = output->parent;
				output = output->parent;
			}
			this->_node = output;
			return (*this);
		}

		MapIterator		operator--(int)
		{
			MapIterator	output(*this);

			--(*this);
			return (output);
		}
};

/** Relational Operators **/
template < typename TNode, typename T, typename UNode, typename U >
bool	operator==(const MapIterator<TNode, T>& lhs, const MapIterator<UNode, U> rhs)
{
	return (lhs.root() == rhs.root());
}

template < typename TNode, typename T, typename UNode, typename U >
bool	operator!=(const MapIterator<TNode, T>& lhs, const MapIterator<UNode, U> rhs)
{
	return (lhs.root() != rhs.root());
}

}

#endif
