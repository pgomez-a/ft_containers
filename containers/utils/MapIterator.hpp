#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"
# include "Bst.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = std::less<Key>,
	 typename Alloc = std::allocator<ft::pair<Key, T> > >
class MapIterator
{
	public:
		/** Member Types **/
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef ft::pair<Key, T>			value_type;
		typedef Compare					key_compare;
		typedef std::ptrdiff_t				difference_type;
		typedef Alloc					allocator_type;
		typedef Bst<Key, T, Compare, Alloc>*		pointer;
		typedef const Bst<Key, T, Compare, Alloc>*	const_pointer;
		typedef ft::pair<Key, T>&			reference;
		typedef const ft::pair<Key, T>&			const_reference;

	private:
		/** Private Member Attributes **/
		pointer	_node;
		pointer	_beg;
		pointer	_end;

	public:
		/** Constructors **/
		MapIterator(void) : _node(nullptr), _beg(nullptr), _end(nullptr) {}

		MapIterator(pointer node) : _node(node)
		{
			pointer	tmp(node);

			if (tmp != nullptr)
			{
				while (tmp->parent != nullptr)
					tmp = tmp->parent;
				while (tmp->left != nullptr)
					tmp = tmp->left;
				this->_beg = tmp;
				tmp = node;
				while (tmp->parent != nullptr)
					tmp = tmp->parent;
				while (tmp->right != nullptr)
					tmp = tmp->right;
				this->_end = tmp->right;
			}
			else
			{
				this->_beg = nullptr;
				this->_end = nullptr;
			}
			return ;
		}

		MapIterator(pointer node, pointer beg, pointer end) : _node(node), _beg(beg), _end(end) {}
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
		pointer	root(void) const
		{
			return (this->_node);
		}

		pointer	begin(void) const
		{
			return (this->_beg);
		}

		pointer	end(void) const
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

		reference	operator*(void) const
		{
			return (this->_node->data);
		}

		value_type*	operator->(void) const
		{
			return (&(this->_node->data));
		}

		MapIterator&	operator++(void)
		{
			pointer	output;

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
			pointer	output;

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

template < typename Key, typename T>
std::ostream&	operator<<(std::ostream& out, const MapIterator<Key, T>& other)
{
	out << (*other).first << ", " << (*other).second;
	return (out);
}

}

#endif
