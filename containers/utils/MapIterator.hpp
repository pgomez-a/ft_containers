#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{

template < typename T, typename Compare = std::less<T> >
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
		Compare	_compare;

	public:
		/** Constructors **/
		MapIterator(const Compare& comp = Compare())
		{
			this->_node = nullptr;
			this->_beg = nullptr;
			this->_end = nullptr;
			this->_compare = comp;
			return ;
		}

		MapIterator(nodePtr root, nodePtr beg,
			nodePtr end, const Compare& comp = Compare())
		{
			this->_node = root;
			this->_beg= beg;
			this->_end = end;
			this->_compare = comp;
			return ;
		}

		MapIterator(const MapIterator& other)
		{
			this->_node = other._node;
			this->_beg = other._beg;
			this->_end = other._end;
			this->_compare = other._compare;
			return ;
		}

		/** Destructor **/
		~MapIterator(void)
		{
			this->_node = nullptr;
			this->_end = nullptr;
			this->_beg = nullptr;
			return ;
		}

		/** Assignation Operator **/
		MapIterator&	operator=(const MapIterator& other)
		{
			if (this != &other)
			{
				this->_node = other._node;
				this->_beg = other._beg;
				this->_end = other._end;
				this->_compare = other._compare;
			}
			return (*this);
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
			return (this->_node->value);
		}

		pointer		operator->(void) const
		{
			return (&(this->_node->value));
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

}

#endif
