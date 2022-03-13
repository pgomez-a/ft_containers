#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{

template < typename Iter >
struct iterator_traits
{
	public:
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type		value_type;
		typedef typename Iter::pointer			pointer;
		typedef typename Iter::reference		reference;
		typedef typename Iter::iterator_category	iterator_category;
};

template < typename T >
struct iterator_traits<T*>
{
	public:
		typedef std::ptrdiff_t			difference_type;
		typedef T				value_type;
		typedef T*				pointer;
		typedef T&				reference;
		typedef std::random_access_iterator_tag	iterator_category;
};

template < typename T >
struct iterator_traits<const T*>
{
	public:
		typedef std::ptrdiff_t			difference_type;
		typedef T				value_type;
		typedef const T*			pointer;
		typedef const T&			reference;
		typedef std::random_access_iterator_tag	iterator_category;
};

template < typename Iter >
class reverse_iterator
{
	public:
		/** Member Types **/
		typedef Iter							iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iter>::value_type		value_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::pointer			pointer;
		typedef typename iterator_traits<Iter>::reference		reference;

	private:
		/** Member Attributes **/
		iterator_type	_iter;

	public:
		/** Constructors **/
		reverse_iterator(void) : _iter(nullptr) {}
		explicit reverse_iterator(iterator_type it) : _iter(it) {}

		template < typename U >
		reverse_iterator(const reverse_iterator<U>& rev_it) : _iter(rev_it.base()) {}

		~reverse_iterator(void) {}

		/** Assignation Operator **/
		template < typename U >
		reverse_iterator&	operator=(const reverse_iterator<U>& other)
		{
			this->_iter = other.base();
			return (*this);
		}

		/** Base **/
		iterator_type		base(void) const
		{
			return (this->_iter);
		}

		/** Member Functions **/
		reference		operator*(void) const
		{
			return (*(--(iterator_type(this->_iter))));
		}

		reference		operator[](difference_type n)
		{
			return (this->base()[-n - 1]);
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

/** Relational Operators **/
template < typename T, typename U>
bool	operator==(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename T, typename U>
bool	operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() != rhs.base());
}

template < typename T, typename U>
bool	operator<(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename T, typename U>
bool	operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template < typename T, typename U>
bool	operator>(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename T, typename U>
bool	operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (lhs.base() <= rhs.base());
}

/** Arithmetic Operators **/
template < typename T >
reverse_iterator<T>	operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T>& rev_it)
{
	return (rev_it + n);
}	

template < typename T, typename U>
typename reverse_iterator<T>::difference_type	operator-(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs)
{
	return (rhs.base() - lhs.base());
}

}

#endif
