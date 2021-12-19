#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

/**
 ** ft::enable_if
 **/

template < bool Cond, typename T = void >
struct enable_if {};

template < typename T >
struct enable_if<true, T>
{
	typedef T	type;
};

/**
 ** ft::is_integral
 **/

template < typename T >
struct is_integral
{
	/** Member Type **/
	static const bool	value = false;
};

template < >
struct is_integral<bool>
{
	static const bool	value = true;
};

template < >
struct is_integral<char>
{
	static const bool	value = true;
};

template < >
struct is_integral<char16_t>
{
	static const bool	value = true;
};

template < >
struct is_integral<char32_t>
{
	static const bool	value = true;
};

template < >
struct is_integral<wchar_t>
{
	static const bool	value = true;
};

template < >
struct is_integral<signed char>
{
	static const bool	value = true;
};

template < >
struct is_integral<short int>
{
	static const bool	value = true;
};

template < >
struct is_integral<int>
{
	static const bool	value = true;
};

template < >
struct is_integral<long int>
{
	static const bool	value = true;
};

template < >
struct is_integral<long long int>
{
	static const bool	value = true;
};

template < >
struct is_integral<unsigned char>
{
	static const bool	value = true;
};

template < >
struct is_integral<unsigned short int>
{
	static const bool	value = true;
};

template < >
struct is_integral<unsigned int>
{
	static const bool	value = true;
};

template < >
struct is_integral<unsigned long int>
{
	static const bool	value = true;
};

template < >
struct is_integral<unsigned long long int>
{
	static const bool	value = true;
};

/**
 ** ft::lexicographical_compare
 **/

template < typename ItOne, typename ItTwo >
bool	lexicographical_compare(ItOne firstOne, ItOne lastOne, ItTwo firstTwo, ItTwo lastTwo)
{
	while (firstOne != lastOne && firstTwo != lastTwo)
	{
		if (!(!(*firstOne < *firstTwo) && !(*firstTwo < *firstOne)))
			return (*firstOne < *firstTwo);
		firstOne++;
		firstTwo++;
	}
	if (firstTwo == lastTwo && firstOne != lastOne)
		return (false);
	return (true);
}

template < typename ItOne, typename ItTwo, typename Comp >
bool	lexicographical_compare(ItOne firstOne, ItOne lastOne, ItTwo firstTwo, ItTwo lastTwo, Comp comp)
{
	while (firstOne != lastOne && firstTwo != lastTwo)
	{
		if (!(!comp(*firstOne, *firstTwo) && !comp(*firstTwo, *firstOne)))
			return (comp(*firstOne, *firstTwo));
		firstOne++;
		firstTwo++;
	}
	if (firstTwo == lastTwo && firstOne != lastOne)
		return (false);
	return (true);
}

/**
 ** ft::BstNode
 **/

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

}

#endif
