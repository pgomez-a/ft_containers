#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"
# include "Bst.hpp"

namespace ft
{

template < typename T >
class MapIterator : public ft::iterator_traits<T*>
{
	public:
		/** Member Types **/
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		node;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer		nodePtr;
		typedef typename ft::iterator_traits<T*>::const_pointer		nodeConstPtr;
		typedef typename ft::iterator_traits<T*>::reference		nodeRef;
		typedef typename ft::iterator_traits<T*>::const_reference	nodeConstRef;

		typedef typename node::value_type				value_type;
		typedef typename node::reference				reference;
		typedef typename node::const_reference				const_reference;
		typedef typename node::pointer					pointer;
		typedef typename node::const_pointer				const_pointer;

	private:
		/** Member Attributes **/
		nodePtr	_node;
		nodePtr	_beg;
		nodePtr	_end;

	public:
		/** Constructors **/
		MapIterator(void) : _node(nullptr), _beg(nullptr), _end(nullptr) {}

		MapIterator(nodePtr node) : _node(node)
		{
			nodePtr	tmp(node);

			while (tmp->left != nullptr)
				tmp = tmp->left;
			this->_beg = tmp;
			tmp = node;
			while (tmp->right != nullptr)
				tmp = tmp->right;
			this->_end = tmp;
			return ;
		}

		MapIterator(nodePtr node, nodePtr beg, nodePtr end) : _node(node), _beg(beg), _end(end) {}
		MapIterator(const MapIterator& other) : _node(other._node), _beg(other._beg), _end(other._end) {}

		/** Destructor **/
		~MapIterator(void) {}

		/** Assignation Operator **/
		MapIterator&	operator=(const MapIterator& other)
		{
			if (this != &other)
				this->_node = other._node;
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

		/** Overloads **/
		bool		operator==(const MapIterator& other)
		{
			if (this->_node == other._node)
				return (true);
			return (false);
		}

		bool		operator!=(const MapIterator& other)
		{
			if (this->_node != other._node)
				return (true);
			return (false);
		}

		value_type&	operator*(void) const
		{
			return (this->_node->data);
		}

		nodePtr		operator->(void) const
		{
			return (this->_node);
		}

		MapIterator&	operator++(void)
		{
			nodePtr	output;

			output = this->_node;
			if (output->right != nullptr)
			{
				output = output->right;
				while (output->left != nullptr)
					output = output->left;
			}
			else if (output != this->_end)
			{
				while (output->parent != nullptr && output != output->parent->left)
					output = output->parent;
				output = output->parent;
			}
			this->_node = output;
			return (*this);
		}

		MapIterator	operator++(int)
		{
			MapIterator	output(*this);

			++(*this);
			return (output);
		}

		MapIterator&	operator--(void)
		{
			nodePtr	output;

			output = this->_node;
			if (output->left != nullptr)
			{
				output = output->left;
				while (output->right != nullptr)
					output = output->right;
			}
			else if (output != this->_beg)
			{
				while (output->parent != nullptr && output != output->parent->right)
					output = output->parent;
				output = output->parent;
			}
			this->_node = output;
			return (*this);
		}

		MapIterator	operator--(int)
		{
			MapIterator	output(*this);

			--(*this);
			return (output);
		}
};

template < typename T >
std::ostream&	operator<<(std::ostream& out, const MapIterator<T>& other)
{
	out << (*other).first << ", " << (*other).second;
	return (out);
}

}

#endif
