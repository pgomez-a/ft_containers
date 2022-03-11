#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{

template < typename T >
class	VectorIterator : public ft::iterator_traits<T*>
{
	public:
		/** Member Types **/
		typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer		pointer;
		typedef typename ft::iterator_traits<T*>::const_pointer		const_pointer;
		typedef typename ft::iterator_traits<T*>::reference		reference;
		typedef typename ft::iterator_traits<T*>::const_reference	const_reference;

	private:
		/** Member Attributes **/
		pointer	_ptr_it;

	public:
		/** Constructors **/
		VectorIterator(void) : _ptr_it(nullptr) {}
		VectorIterator(pointer ptr_it) : _ptr_it(ptr_it) {}
		VectorIterator(const VectorIterator& other) : _ptr_it(other._ptr_it) {}
		~VectorIterator(void) {}

		/** Assignation Operator **/
		VectorIterator&		operator=(const VectorIterator& other)
		{
			if (this != &other)
				this->_ptr_it = other._ptr_it;
			return (*this);
		}

		const VectorIterator&	operator=(const VectorIterator& other) const
		{
			VectorIterator*	tmp;

			if (this != &other)
			{
				tmp = const_cast<VectorIterator*>(this);
				tmp->_ptr_it = other._ptr_it;
			}
			return (*this);
		}

		/** Member Functions **/
		bool		operator==(const VectorIterator& other) const
		{
			if (this->_ptr_it == other._ptr_it)
				return (true);
			return (false);
		}

		bool		operator!=(const VectorIterator& other) const
		{
			if (this->_ptr_it != other._ptr_it)
				return (true);
			return (false);
		}

		bool		operator<(const VectorIterator& other) const
		{
			if (this->_ptr_it < other._ptr_it)
				return (true);
			return (false);
		}

		bool		operator<=(const VectorIterator& other) const
		{
			if (this->_ptr_it <= other._ptr_it)
				return (true);
			return (false);
		}

		bool		operator>(const VectorIterator& other) const
		{
			if (this->_ptr_it > other._ptr_it)
				return (true);
			return (false);
		}

		bool		operator>=(const VectorIterator& other) const
		{
			if (this->_ptr_it >= other._ptr_it)
				return (true);
			return (false);
		}

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

		VectorIterator	operator+(difference_type n)
		{
			VectorIterator	output_it;

			output_it._ptr_it = this->_ptr_it + n;
			return (output_it);
		}

		VectorIterator	operator++(void)
		{
			VectorIterator	output_it;

			this->_ptr_it++;
			output_it = *this;
			return (output_it);
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

		VectorIterator	operator-(difference_type n)
		{
			VectorIterator	output_it;

			output_it._ptr_it = this->_ptr_it - n;
			return (output_it);
		}

		difference_type	operator-(const VectorIterator<T>& other)
		{
			return (this->_ptr_it - other._ptr_it);
		}

		VectorIterator	operator--(void)
		{
			VectorIterator	output_it;

			this->_ptr_it--;
			output_it = *this;
			return (output_it);
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

}

#endif
