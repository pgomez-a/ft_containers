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
		VectorIterator(void) : _ptr_it(nullptr) {}
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
		size_type	_size;
		size_type	_capacity;
		allocator_type	_allocator;
		pointer		_vector_ptr;
	
	public:

		/** Constructors **/
		explicit vector(const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			this->_capacity = 0;
			this->_allocator = alloc;
			this->_vector_ptr = nullptr;
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
			this->_vector_ptr = this->_allocator.allocate(this->_capacity);
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
			const allocator_type& alloc = allocator_type())
		{
			iterator	begin;
			iterator	end;
			pointer		construct_ptr;

			this->_size = last - first;
			this->_capacity = last - first;
			this->_allocator = alloc;
			this->_vector_ptr = this->_allocator.allocate(this->_capacity);
			begin = this->begin();
			end = this->end();
			construct_ptr = this->_vector_ptr;
			while (begin != end)
			{
				this->_allocator.construct(construct_ptr, *first);
				first++;
				construct_ptr++;
				begin++;
			}
		}

		vector(const vector& other) //NOTE: Consider with assignation operator
		{
			if (this != &other)
			{
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_allocator = other._allocator;
				*this = other;
			}
			return ;
		}

		/** Destructor **/
		~vector(void)
		{
			this->resize(0);
			this->_allocator.deallocate(this->_vector_ptr, this->_capacity);
			return ;
		}

		/** Assignation Operator **/
		vector&			operator=(const vector& other)
		{
			iterator	begin;
			iterator	end;
			iterator	tmp;
			pointer		modify_ptr;

			if (this != &other)
			{
				begin = this->begin();
				end = this->end();
				modify_ptr = this->_vector_ptr;
				while (begin != end)
				{
					this->_allocator.destroy(modify_ptr);
					modify_ptr++;
					begin++;
				}
				this->_allocator.deallocate(this->_vector_ptr, this->_capacity);
				this->_size = other.size();
				this->_capacity = other.capacity();
				this->_vector_ptr = this->_allocator.allocate(this->_capacity);
				begin = this->begin();
				end = this->end();
				tmp = other.begin();
				modify_ptr = this->_vector_ptr;
				while (begin != end)
				{
					this->_allocator.construct(modify_ptr, *tmp);
					tmp++;
					modify_ptr++;
					begin++;
				}
			}
			return (*this);
		} // NOTE: What happens for different sizes?

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

		void			resize(size_type count, value_type value = value_type())
		{
			iterator		begin;
			iterator		end;
			pointer			modify_ptr;

			if (count < this->_size)
			{
				begin = this->begin() + count;
				end = this->end();
				modify_ptr = this->_vector_ptr + count;
				while (begin != end)
				{
					this->_allocator.destroy(modify_ptr);
					modify_ptr++;
					begin++;
				}
				this->_size = count;
			}
			else if (count > this->_size && count <= this->_capacity)
			{
				begin = this->begin() + this->_size;
				end = this->begin() + count;
				modify_ptr = this->_vector_ptr + this->_size;
				while (begin != end)
				{
					this->_allocator.construct(modify_ptr, value);
					modify_ptr++;
					begin++;
				}
			}
			else
			{
				if (this->_capacity * 2 > count)
					this->reserve(this->_capacity * 2);
				else
					this->reserve(count);
				begin = this->begin() + this->_size;
				end = this->end();
				modify_ptr = this->_vector_ptr + this->_size;
				while (begin != end)
				{
					this->_allocator.construct(modify_ptr, value);
					modify_ptr++;
					begin++;
				}
				this->_size = count;
			}
			return ;
		}

		void			reserve(size_type new_cap)
		{
			iterator	begin;
			iterator	end;
			pointer		reallocate_ptr;
			size_type	aux;

			if (this->_capacity < new_cap)
			{
				reallocate_ptr = this->_allocator.allocate(new_cap);
				begin = this->begin();
				end = this->end();
				aux = 0;
				while (begin != end)
				{
					this->_allocator.construct(reallocate_ptr + aux, *begin);
					this->_allocator.destroy(this->_vector_ptr + aux);
					aux++;
					begin++;
				}
				this->_allocator.deallocate(this->_vector_ptr, this->_capacity);
				this->_capacity = new_cap;
				this->_vector_ptr = reallocate_ptr;
			}
			return ;
		}

		bool			empty(void) const
		{
			if (this->_size > 0)
				return false;
			return true;
		}

		/** Element access **/
		reference		operator[](size_type pos)
		{
			return (*(this->_vector_ptr + pos));
		}

		const_reference		operator[](size_type pos) const
		{
			return (*(this->_vector_ptr + pos));
		}

		reference		at(size_type pos)
		{
			return (*(this->_vector_ptr + pos));
		}

		const_reference		at(size_type pos) const
		{
			return (*(this->_vector_ptr + pos));
		}

		reference		front(void)
		{
			return (*(this->_vector_ptr));
		}

		const_reference		front(void) const
		{
			return (*(this->_vector_ptr));
		}

		reference		back(void)
		{
			return (*(this->_vector_ptr + this->_size - 1));
		}

		const_reference		back(void) const
		{
			return (*(this->_vector_ptr + this->_size - 1));
		}

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
