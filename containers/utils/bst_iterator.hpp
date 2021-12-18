#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

namespace ft
{

# include "iterator.hpp"

template < typename T >
class BstNode
{
	public:
		/** Member Types **/
		typedef T		value_type;
		typedef T&		reference;
		typedef const T&	const_reference;
		typedef T*		pointer;
		typedef const T*	const_pointer;

		/** Member Attributes **/
		value_type	value;
		BstNode*	parent;
		BstNode*	left;
		BstNode*	right;

		/** Constructors **/
		explicit BstNode(const value_type& value = value_type())
		{
			this->value = value;
			this->parent = nullptr;
			this->left = nullptr;
			this->right = nullptr;
		}

		BstNode(const value_type& value, const BstNode* parent,
			const BstNode* left, const BstNode* right)
		{
			this->value = value;
			this->parent = parent;
			this->left = left;
			this->right = right;
			return ;
		}

		BstNode(const BstNode& other)
		{
			this->value = other.value;
			this->parent = other.parent;
			this->left = other.left;
			this->right = other.right;
			return ;
		}

		/** Destructor **/
		~BstNode(void)
		{
			this->parent = nullptr;
			this->left = nullptr;
			this->right = nullptr;
			return ;
		}

		/** Assignation Operator **/
		BstNode&	operator=(const BstNode& other)
		{
			if (this != &other)
			{
				this->value = other.value;
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
			}
			return (*this);
		}

		/** Overloads **/
		bool		operator==(const BstNode& other)
		{
			if (this->value == other.value)
				return (true);
			return (false);
		}

		bool		operator!=(const BstNode& other)
		{
			if (this->value != other.value)
				return (true);
			return (false);
		}

		reference	operator*(void)
		{
			return (this->value);
		}

		pointer		operator->(void)
		{
			return (&(this->value));
		}
};

template < typename T, typename Compare = std::less<T> >
class BstIterator : public ft::iterator_traits<T*>
{
	public:
		/** Member Types **/
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer		pointer;
		typedef typename ft::iterator_traits<T*>::const_pointer		const_pointer;
		typedef typename ft::iterator_traits<T*>::reference		reference;
		typedef typename ft::iterator_traits<T*>::const_reference	const_reference;

	private:
		/** Member Attributes **/
		value_type*	_node;
		value_type*	_beg;
		value_type*	_end;
		Compare		_compare;

	public:
		/** Constructors **/
		BstIterator(const Compare& comp = Compare())
		{
			this->_node = nullptr;
			this->_beg = nullptr;
			this->_end = nullptr;
			this->_compare = comp;
			return ;
		}

		BstIterator(value_type* node, value_type* beg,
			value_type* end, const Compare& comp = Compare())
		{
			this->_node = node;
			this->_beg= beg;
			this->_end = end;
			this->_compare = comp;
			return ;
		}

		BstIterator(const BstIterator& other)
		{
			this->_node = other._node;
			this->_beg = other._beg;
			this->_end = other._end;
			this->_compare = other._compare;
			return ;
		}

		/** Destructor **/
		~BstIterator(void)
		{
			this->_node = nullptr;
			this->_end = nullptr;
			this->_beg = nullptr;
			return ;
		}

		/** Assignation Operator **/
		BstIterator&	operator=(const BstIterator& other)
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
		bool					operator==(const BstIterator& other)
		{
			if (this->_node == other._node)
				return (true);
			return (false);
		}

		bool					operator!=(const BstIterator& other)
		{
			if (this->_node != other._node)
				return (true);
			return (false);
		}

		typename value_type::value_type&	operator*(void) const
		{
			return (this->_node->value);
		}

		typename value_type::value_type*	operator->(void) const
		{
			return (&(this->_node->value));
		}

		BstIterator&				operator++(void)
		{
			value_type*	output;

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

		BstIterator				operator++(int)
		{
			BstIterator	output(*this);

			++(*this);
			return (output);
		}

		BstIterator&				operator--(void)
		{
			value_type*	output;

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

		BstIterator				operator--(int)
		{
			BstIterator	output(*this);

			--(*this);
			return (output);
		}
};

}

#endif
