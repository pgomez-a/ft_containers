#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "./utils/traits.hpp"
# include "./utils/iterator.hpp"
# include "vector.hpp"

namespace ft
{

template < typename T, typename Container = ft::vector<T> >
class	stack
{
	public:
		/** Member Types **/
		typedef Container				container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	protected:
		container_type	_ctnr;

	public:
		/** Constuctor **/
		explicit stack(const container_type& other = container_type()) : _ctnr(other)
		{
			return ;
		}

		stack(const stack& other) : _ctnr(other._ctnr)
		{
			return ;
		}

		/** Destructor **/
		~stack(void) {};

		/** Assignation Operator **/
		stack&	operator=(const stack& other)
		{
			*(this->_ctnr) = *other;
			return (*this);
		}

		/** Member Functions **/
		bool			empty(void) const
		{
			return (this->_ctnr.empty());
		}

		size_type		size(void) const
		{
			return (this->_ctnr.size());
		}

		value_type&		top(void)
		{
			return (this->_ctnr.back());
		}

		const value_type&	top(void) const
		{
			return (this->_ctnr.back());
		}

		void			push(const value_type& val)
		{
			this->_ctnr.push_back(val);
		}

		void			pop(void)
		{
			this->_ctnr.pop_back();
		}

		friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr == rhs._ctnr);
		}

		friend bool	operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr != rhs._ctnr);
		}

		friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr < rhs._ctnr);
		}
		
		friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr <= rhs._ctnr);
		}
		
		friend bool	operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr > rhs._ctnr);
		}

		friend bool	operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
		{
			return (lhs._ctnr >= rhs._ctnr);
		}
};

}

#endif
