#ifndef VECTOR_HPP
# define VECTOR_HPP

template < typename T >
struct	VectorIterator
{
	public:
		/** Member Types **/
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T				value_type;
		typedef std::ptrdiff_t			difference_type;
		typedef T*				pointer;
		typedef const T*			const_pointer;
		typedef T&				reference;
		typedef const T&			const_reference;

	private:
		/** Member Attributes **/
		pointer	_ptr_it;

	public:
		/** Constructors **/
		VectorIterator(void) : _ptr_it(nullptr) {} //must be private
		VectorIterator(pointer ptr_it) : _ptr_it(ptr_it) {}
		VectorIterator(const VectorIterator& other) : _ptr_it(other._ptr_it) {}
		~VectorIterator(void) {}

		/** Assignation Operator **/
		VectorIterator&	operator=(const VectorIterator& other)
		{
			this->_ptr_it = other._ptr_it;
			return (*this);
		}

		/** Operations **/
		bool		operator==(const VectorIterator& other) const
		{
			if (this->_ptr_it == other._ptr_it)
				return true;
			return false;
		}

		bool		operator!=(const VectorIterator& other) const
		{
			if (this->_ptr_it != other._ptr_it)
				return true;
			return false;
		}

		bool		operator<(const VectorIterator& other) const
		{
			if (this->_ptr_it < other._ptr_it)
				return true;
			return false;
		}

		bool		operator<=(const VectorIterator& other) const
		{
			if (this->_ptr_it <= other._ptr_it)
				return true;
			return false;
		}

		bool		operator>(const VectorIterator& other) const
		{
			if (this->_ptr_it > other._ptr_it)
				return true;
			return false;
		}

		bool		operator>=(const VectorIterator& other) const
		{
			if (this->_ptr_it >= other._ptr_it)
				return true;
			return false;
		}

		reference	operator*(void) const // NOTE: Review syntax
		{
			return (*this->_ptr_it);
		}

		reference	operator[](difference_type n)
		{
			return (*this->_ptr_it + n);
		}

		pointer		operator->(void) const // NOTE: Review syntax
		{
			return (this->_ptr_it);
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

		VectorIterator	operator+(difference_type n)
		{
			VectorIterator	output_it;

			output_it._ptr_it = this->_ptr_it + n;
			return (output_it);
		}

		VectorIterator	operator-(difference_type n)
		{
			VectorIterator	output_it;

			output_it._ptr_it = this->_ptr_it - n;
			return (output_it);
		}

		VectorIterator	operator+=(difference_type n)
		{
			this->_ptr_it += n;
			return (*this);
		}

		VectorIterator	operator-=(difference_type n)
		{
			this->_ptr_it -= n;
			return (*this);
		}
};

namespace ft
{

template < typename T, typename Allocator = std::allocator<T> >
class	vector
{
	public:
		/** Member Types **/
		typedef T 					value_type;
		typedef Allocator				allocator_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef T&					reference;
		typedef const T&				const_reference;
		typedef typename Allocator::pointer		pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef VectorIterator<T>			iterator;
		typedef const VectorIterator<T>			const_iterator;
		typedef std::reverse_iterator<iterator>		reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		/** Member Attributes **/
		pointer		_vector_ptr;
		allocator_type	_allocator;
		size_type	_size;
		size_type	_capacity;
	
	public:

		/** Constructors **/
		explicit vector(const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			this->_capacity = 0;
			this->_allocator = alloc;
			return ;
		}

		explicit vector(size_type count, const_reference value = value_type(),
			const allocator_type& alloc = allocator_type())
		{
			iterator	begin;
			iterator	end;
			pointer		construct_ptr;

			this->_size = count;
			this->_capacity = count;
			this->_allocator = alloc;
			this->_vector_ptr = this->_allocator.allocate(count);
			begin = this->begin();
			end = this->end();
			construct_ptr = this->_vector_ptr;
			while (begin != end)
			{
				this->_allocator.construct(construct_ptr, value);
				construct_ptr++;
				begin++;
			}
			
		}
		
		template < typename InputIt >
		vector(InputIt first, InputIt last,
			const allocator_type& alloc = allocator_type());

		vector(const vector& other);

		/** Destructor **/
		~vector(void)
		{
			iterator	begin;
			iterator	end;
			pointer		destroy_ptr;

			begin = this->begin();
			end = this->end();
			destroy_ptr = this->_vector_ptr;
			while (begin != end)
			{
				this->_allocator.destroy(destroy_ptr);
				destroy_ptr++;
				begin++;
			}
			this->_allocator.deallocate(this->_vector_ptr, this->_capacity);
			this->_size = 0;
			this->_capacity = 0;
			return ;
		}

		/** Assignation Operator **/
		vector&			operator=(const vector& other);

		/** Iterators **/
		iterator		begin(void)
		{
			return (VectorIterator<value_type>(this->_vector_ptr));
		}

		const_iterator		begin(void) const
		{
			return (VectorIterator<value_type>(this->_vector_ptr));
		}

		iterator		end(void)
		{
			return (VectorIterator<value_type>(this->_vector_ptr + this->_size));
		}

		const_iterator		end(void) const
		{
			return (VectorIterator<value_type>(this->_vector_ptr + this->_size));
		}

		reverse_iterator	rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator	rend(void);
		const_reverse_iterator	rend(void) const;

		/** Capacity **/
		size_type		size(void) const
		{
			return (this->_size);
		}

		size_type		max_size(void) const
		{
			return (this->_allocator.max_size());
		}

		size_type		capacity(void) const
		{
			return (this->_capacity);
		}

		void			resize(size_type count, value_type value = value_type());
		void			reserve(size_type new_cap);
		bool			empty(void) const
		{
			if (this->_size > 0)
				return false;
			return true;
		}

		/** Element access **/
		reference		operator[](size_type pos);
		const_reference		operator[](size_type pos) const;
		reference		at(size_type pos);
		const_reference		at(size_type pos) const;
		reference		front(void);
		const_reference		front(void) const;
		reference		back(void);
		const_reference		back(void) const;

		/** Modifiers **/
		template < typename InputIt >
		void			assign(InputIt first, InputIt last);

		void			assign(size_type count, const_reference value);
		void			push_back(const_reference value);
		void			pop_back(void);
		iterator		insert(iterator pos, const_reference value);
		void			insert(iterator pos, size_type count, const_reference value);

		template < typename InputIt >
		void			insert(iterator pos, InputIt first, InputIt last);

		iterator		erase(iterator pos);
		iterator		erase(iterator first, iterator last);
		void			swap(vector& other);
		void			clear(void);

		/** Allocator **/
		allocator_type		get_allocator(void) const
		{
			return (this->_allocator);
		}
};

}

#endif
