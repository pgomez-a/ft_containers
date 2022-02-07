#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

template < typename Iter >
struct iterator_traits
{
	public:
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type		value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer			pointer;
		typedef typename Iter::const_pointer		const_pointer;
		typedef typename Iter::reference		reference;
		typedef typename Iter::const_reference		const_reference;
};

template < typename T >
struct iterator_traits<T*>
{
	public:
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T				value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef T*				pointer;
		typedef const T*			const_pointer;
		typedef T&				reference;
		typedef const T&			const_reference;
};

template < typename T >
struct iterator_traits<const T*>
{
	public:
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T				value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef T*				pointer;
		typedef const T*			const_pointer;
		typedef T&				reference;
		typedef const T&			const_reference;
};

template < typename Iter >
class reverse_iterator : public iterator_traits<Iter>
{
	public:
		/** Member Types **/
		typedef Iter							iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iter>::value_type		value_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::pointer			pointer;
		typedef typename iterator_traits<Iter>::const_pointer		const_pointer;
		typedef typename iterator_traits<Iter>::reference		reference;
		typedef typename iterator_traits<Iter>::const_reference		const_reference;

	private:
		/** Member Attributes **/
		iterator_type	_iter;

	public:
		/** Constructors **/
		reverse_iterator(void) : _iter(nullptr) {}
		explicit reverse_iterator(iterator_type it) : _iter(it) {}
		reverse_iterator(const reverse_iterator<iterator_type>& rev_it) : _iter(rev_it._iter) {}
		~reverse_iterator(void) {}

		/** Base **/
		iterator_type		base() const
		{
			return (iterator_type(this->_iter));
		}

		/** Assignation Operator **/
		template < typename U >
		reverse_iterator&	operator=(const reverse_iterator<U>& other)
		{
			this->_iter = other._iter;
			return (*this);
		}

		/** Member Functions **/
		reference		operator*(void) const
		{
			return (*(--(iterator_type(this->_iter))));
		}

		reference		operator[](difference_type n)
		{
			return (iterator_type(this->_iter + n));
		}

		pointer			operator->(void) const
		{
			return (&(*(*this)));
		}

		reverse_iterator	operator+(difference_type n) const
		{
			return (reverse_iterator(this->_iter - n));
		}

		reverse_iterator	operator++(void)
		{
			--(this->_iter);
			return (*this);
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	aux(this->_iter);

			++(*this);
			return (aux);
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			(*this) = (*this) + n;
			return (*this);
		}

		reverse_iterator	operator-(difference_type n) const
		{
			return (reverse_iterator(this->_iter + n));
		}

		reverse_iterator	operator--(void)
		{
			++(this->_iter);
			return (*this);
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	aux(this->_iter);

			--(*this);
			return (aux);
		}

		reverse_iterator&	operator-=(difference_type n)
		{
			(*this) = (*this) - n;
			return (*this);
		}
};

/** Non-Member Functions **/

template < typename Iter >
bool			operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename Iter >
bool			operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() != rhs.base());
}

template < typename Iter >
bool			operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename Iter >
bool			operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template < typename Iter >
bool			operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename Iter >
bool			operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template < typename Iter >
reverse_iterator<Iter>	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it)
{
	return (rev_it.base() + n);
}	

template < typename Iter >
typename reverse_iterator<Iter>::difference_type	operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (rhs.base() - lhs.base());
}

}

#endif
