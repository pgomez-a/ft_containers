#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

template < typename T1, typename T2 >
struct pair
{
	public:
		/** Member Types **/
		typedef T1	first_type;
		typedef T2	second_type;

		/** Member Variables **/
		first_type	first;
		second_type	second;

		/** Constructors **/
		pair(void) : first(), second() {}
		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		template < typename U, typename V >
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		/** Destructor **/
		~pair(void) {}

		/** Assignation Operator **/
		pair&	operator=(const pair& pr)
		{
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		}
};

/** Non-Member Functions **/
template < typename T1, typename T2 >
pair<T1, T2>	make_pair(T1 x, T2 y)
{
	return (pair<T1, T2>(x, y));
}

template < typename T1, typename T2 >
bool		operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	if (lhs.first == rhs.first && lhs.second == rhs.second)
		return (true);
	return (false);
}

template < typename T1, typename T2 >
bool		operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return (!(lhs == rhs));
}

template < typename T1, typename T2 >
bool		operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	if (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second))
		return (true);
	return (false);
}

template < typename T1, typename T2 >
bool		operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return (!(rhs < lhs));
}

template < typename T1, typename T2 >
bool		operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return (rhs < lhs);
}

template < typename T1, typename T2 >
bool		operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return (!(lhs < rhs));
}

}

#endif
