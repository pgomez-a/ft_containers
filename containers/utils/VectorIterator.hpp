#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{

template < typename T >
class	VectorIterator
{
	public:
		/** Member Types **/
		typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<T>::value_type		value_type;
		typedef typename ft::iterator_traits<T>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T>::pointer		pointer;
		typedef typename ft::iterator_traits<T>::reference		reference;

	private:
		/** Member Attributes **/
		pointer	_ptr_it;

	public:
		/** Constructors **/
		VectorIterator(void) : _ptr_it(nullptr) {}
		VectorIterator(pointer ptr_it) : _ptr_it(ptr_it) {}

		template < typename U >
		VectorIterator(const VectorIterator<U>& other) : _ptr_it(other.base()) {}

		~VectorIterator(void) {}

		/** Assignation Operator **/
		template < typename U >
		VectorIterator&		operator=(const VectorIterator<U>& other)
		{
			this->_ptr_it = other.base();
			return (*this);
		}

		/** Base **/
		pointer	base(void) const
		{
			return (this->_ptr_it);
		}

		/** Member Functions **/
		reference	operator*(void) const
		{
			return (*this->_ptr_it);
		}

		reference	operator[](difference_type n)
		{
			return (*(this->_ptr_it + n));
		}

		pointer		operator->(void) const
		{
			return (this->_ptr_it);
		}

		VectorIterator	operator+(difference_type n) const
		{
			return (VectorIterator(this->_ptr_it + n));
		}

		VectorIterator&	operator++(void)
		{
			this->_ptr_it++;
			return (*this);
		}

		VectorIterator	operator++(int)
		{
			VectorIterator	output_it;

			output_it = *this;
			this->_ptr_it++;
			return (output_it);
		}

		VectorIterator&	operator+=(difference_type n)
		{
			this->_ptr_it += n;
			return (*this);
		}

		VectorIterator	operator-(difference_type n) const
		{
			return (VectorIterator(this->_ptr_it - n));
		}

		VectorIterator&	operator--(void)
		{

			this->_ptr_it--;
			return (*this);
		}

		VectorIterator	operator--(int)
		{
			VectorIterator	output_it;

			output_it = *this;
			this->_ptr_it--;
			return (output_it);
		}

		VectorIterator&	operator-=(difference_type n)
		{
			this->_ptr_it -= n;
			return (*this);
		}
};

template < typename T, typename U >
bool	operator==(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename T, typename U >
bool	operator!=(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() != rhs.base());
}

template < typename T, typename U >
bool	operator<(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename T, typename U >
bool	operator<=(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template < typename T, typename U >
bool	operator>(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename T, typename U >
bool	operator>=(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template < typename T >
VectorIterator<T>	operator+(typename VectorIterator<T>::difference_type n, const VectorIterator<T>& it)
{
	return (it.base() + n);
}

template < typename T, typename U >
typename VectorIterator<T>::difference_type	operator-(const VectorIterator<T>& lhs, const VectorIterator<U>& rhs)
{
	return (lhs.base() - rhs.base());
}

}

#endif
