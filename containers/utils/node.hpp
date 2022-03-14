#ifndef NODE_HPP
# define NODE_HPP

namespace
{

template < typename T >
class	node
{
	public:
		/** Member Types **/
		typedef T	value_type;
		typedef T&	reference;
		typedef T*	pointer;

		/** Member Attributes **/
		value_type	data;
		pointer		left;
		pointer		right;
		pointer		parent;
		int		balance;

		/** Constructor **/
		node(void)
			: left(nullptr), right(nullptr), parent(nullptr), data(value_type(), balance(0)) {}
		node(const node& other)
			: left(other.left), right(other.right), parent(other.parent), data(other.data), balance(0) {}

		/** Destructor **/
		~node(void) {}

		/** Member Functions **/
		reference	getData(void) const
		{
			return (this->data);
		}

		pointer		getLeft(void) const
		{
			return (this->left);
		}

		pointer		getRight(void) const
		{
			return (this->right());
		}

		pointer		getParent(void) const
		{
			return (this->parent);
		}

		int		getBalance(void) const
		{
			return (this->balance);
		}
};

}

#endif
