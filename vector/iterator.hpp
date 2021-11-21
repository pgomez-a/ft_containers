#ifndef ITERATOR_HPP
# define ITERATOR_HPP

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
		pointer	_ptr_it;

	public:
		/** Constructors **/
		reverse_iterator(void) : _ptr_it(nullptr) {}
		explicit reverse_iterator(iterator_type it) : _ptr_it(*it) {}
		reverse_iterator(const reverse_iterator<iterator_type>& rev_it) : _ptr_it(rev_it._ptr_it) {}
		~reverse_iterator(void) {}

		/** Base **/
		iterator_type		base() const; // NOTE: HEYYY!

		/** Assignation Operator **/
		template < typename U >
		reverse_iterator&	operator=(const reverse_iterator<U>& other)
		{
			this->_ptr_it = other._ptr_it;
			return (*this);
		}

		/** Member Functions **/
		reference		operator*(void) const
		{
			iterator_type	aux(*this);

			aux--;
			return (*aux);
		}

		reference		operator[](difference_type n)
		{
			iterator_type	aux(*this);

			return (aux[-n - 1]);
		}

		pointer			operator->(void) const
		{
			return (this->_ptr_it);
		}

		reverse_iterator	operator+(difference_type n) const
		{
			iterator_type	aux(*this);

			aux -= n;
			return (reverse_iterator<iterator_type>(aux));
		}

		reverse_iterator&	operator++(void)
		{
			iterator_type	aux(*this);

			aux--;
			return (reverse_iterator<iterator_type>(aux));
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	aux(*this);

			++(*this);
			return (aux);
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			iterator_type	aux(*this);

			aux -= n;
			return (reverse_iterator<iterator_type>(aux));
		}

		reverse_iterator	operator-(difference_type n) const
		{
			iterator_type	aux(*this);

			aux += n;
			return (reverse_iterator<iterator_type>(aux));
		}

		reverse_iterator&	operator--(void)
		{
			iterator_type	aux(*this);

			aux++;
			return (reverse_iterator<iterator_type>(aux));
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	aux(*this);

			--(*this);
			return (aux);
		}

		reverse_iterator&	operator-=(difference_type n)
		{
			iterator_type	aux(*this);

			aux += n;
			return (reverse_iterator<iterator_type>(aux));
		}
};

/** Non-Member Functions **/

template < typename Iter >
bool			operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs == base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
bool			operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs != base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
bool			operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs > base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
bool			operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs >= base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
bool			operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs < base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
bool			operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	if (base_lhs <= base_rhs)
		return (true);
	return (false);
}

template < typename Iter >
reverse_iterator<Iter>	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it)
{
	return (rev_it + n);
}	

template < typename Iter >
typename reverse_iterator<Iter>::difference_type	operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	Iter	base_lhs(*lhs);
	Iter	base_rhs(*rhs);

	return (base_rhs - base_lhs);
}

#endif
