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
		//typedef ft::pair<Key, T>			value_type;
		typedef Bst<Key, T, Compare, Alloc>		value_type;
		typedef Compare					key_compare;
		typedef std::ptrdiff_t				difference_type;
		typedef Alloc					allocator_type;
		typedef ft::pair<Key, T>*			pointer;
		typedef const ft::pair<Key, T>*			const_pointer;
		typedef Bst<Key, T, Compare, Alloc>*		node_pointer;
		typedef const Bst<Key, T, Compare, Alloc>*	const_node_pointer;
		typedef ft::pair<Key, T>&			reference;
		typedef const ft::pair<Key, T>&			const_reference;

	private:
		/** Private Member Attributes **/
		node_pointer	_node;
		node_pointer	_beg;
		node_pointer	_end;

	public:
		/** Constructors **/
		MapIterator(node_pointer node = nullptr) : _node(node)
		{
			node_pointer	tmp(node);

			if (node != nullptr && (tmp != nullptr || tmp == this->_end))
			{
				while (tmp->parent != nullptr && tmp->parent->parent != nullptr)
					tmp = tmp->parent;
				while (tmp->left != nullptr)
					tmp = tmp->left;
				this->_beg = tmp;
				tmp = node;
				while (tmp->parent != nullptr)
					tmp = tmp->parent;
				this->_end = tmp;
			}
			else
			{
				this->_beg = nullptr;
				this->_end = nullptr;
			}
			return ;
		}

		MapIterator(node_pointer node, node_pointer beg, node_pointer end)
			: _node(node), _beg(beg), _end(end) {}

		MapIterator(const MapIterator& other)
			: _node(other._node), _beg(other._beg), _end(other._end) {}

		/** Destructor **/
		~MapIterator(void) {}

		/** Assignation Operator **/
		MapIterator&		operator=(const MapIterator& other)
		{
			if (this != &other)
			{
				this->_node = other._node;
				this->_beg = other._beg;
				this->_end = other._end;
			}
			return (*this);
		}

		const MapIterator&	operator=(const MapIterator& other) const
		{
			MapIterator*	tmp;

			if (this != &other)
			{
				tmp = const_cast<MapIterator*>(this);
				tmp->_node = other._node;
				tmp->_beg = other._beg;
				tmp->_end = other._end;
			}
			return (*this);
		}

		/** Member Functions **/
		node_pointer	root(void) const
		{
			return (this->_node);
		}

		node_pointer	begin(void) const
		{
			return (this->_beg);
		}

		node_pointer	end(void) const
		{
			return (this->_end);
		}

		/** Overloads **/
		bool		operator==(const MapIterator& other) const
		{
			if (this->_node == other._node)
				return (true);
			return (false);
		}

		bool		operator!=(const MapIterator& other) const
		{
			if (this->_node != other._node)
				return (true);
			return (false);
		}

		reference	operator*(void) const
		{
			return (this->_node->data);
		}

		pointer		operator->(void) const
		{
			return (&(this->_node->data));
		}

		MapIterator&	operator++(void)
		{
			node_pointer	output;

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
			node_pointer	output;

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
