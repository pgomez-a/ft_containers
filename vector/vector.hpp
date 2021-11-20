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

		difference_type	operator-(const VectorIterator& other) const
		{
			return (this->_ptr_it - other._ptr_it);
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
			this->_size = 0;
			this->_capacity = 0;
			this->_allocator = alloc;
			this->_vector_ptr = nullptr;
			this->assign(count, value);
			return ;
		}
		
		template < typename InputIt >
		vector(InputIt first, InputIt last,
			const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			this->_capacity = 0;
			this->_allocator = alloc;
			this->_vector_ptr = nullptr;
			this->assign(first, last);
			return ;
		}

		vector(const vector& other)
		{
			if (this != &other)
			{
				this->_size = 0;
				this->_capacity = 0;
				this->_allocator = other._allocator;
				this->_vector_ptr = nullptr;
				this->assign(other.begin(), other.end());
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
			if (this != &other)
				this->assign(other.begin(), other.end());
			return (*this);
		}

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
			return (this->_allocator.max_size() / sizeof(value_type));
		}

		size_type		capacity(void) const
		{
			return (this->_capacity);
		}

		void			resize(size_type count, value_type value = value_type())
		{
			iterator	begin;
			iterator	end;
			pointer		modify_ptr;

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
				this->_size = count;
			}
			else
			{
				if (this->_capacity * 2 > count)
					this->reserve(this->_capacity * 2);
				else
					this->reserve(count);
				begin = this->begin() + this->_size - 1;
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
				return (false);
			return (true);
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
		void			assign(InputIt first, InputIt last)
		{
			size_type	capacity;
			pointer		modify_ptr;

			capacity = last - first;
			if (capacity > this->_capacity)
				this->resize(capacity);
			this->_size = capacity;
			modify_ptr = this->_vector_ptr;
			while (first != last)
			{
				this->_allocator.destroy(modify_ptr);
				this->_allocator.construct(modify_ptr, *first);
				modify_ptr++;
				first++;
			}
			return ;
		}

		void			assign(size_type count, const_reference value)
		{
			pointer		modify_ptr;

			if (count > this->_capacity)
				this->resize(count);
			this->_size = count;
			modify_ptr = this->_vector_ptr;
			while (count > 0)
			{
				this->_allocator.destroy(modify_ptr);
				this->_allocator.construct(modify_ptr, value);
				modify_ptr++;
				count--;
			}
			return ;
		}

		void			push_back(const_reference value)
		{
			if (this->_size == this->_capacity)
				this->resize(this->_size + 1);
			else
				this->_size += 1;
			this->_allocator.construct(this->_vector_ptr + this->_size - 1, value);
			return ;
		}

		void			pop_back(void)
		{
			if (this->_size > 0)
			{
				this->_size -= 1;
				this->_allocator.destroy(this->_vector_ptr + this->_size);
			}
			return ;
		}

		iterator		insert(iterator pos, const_reference value)
		{
			difference_type	diff;
			iterator	end;
			pointer		modify_ptr;
			

			diff = pos - this->begin();
			if (this->_size == this->_capacity)
				this->resize(this->_size + 1);
			else
				this->_size += 1;
			end = this->end() - 1;
			modify_ptr = this->_vector_ptr + this->_size - 1;
			while (end != this->begin() + diff)
			{
				*modify_ptr = *(modify_ptr - 1);
				modify_ptr--;
				end--;
			}
			*modify_ptr = value;
			return (this->begin() + diff);
		}

		iterator		insert(iterator pos, size_type count, const_reference value)
		{
			difference_type	diff;
			iterator	end;
			pointer		modify_ptr;

			diff = pos - this->begin();
			if (this->_size + count > this->_capacity)
				this->resize(this->_size + count);
			else
				this->_size += count;
			end = this->end() - 1;
			modify_ptr = this->_vector_ptr + this->_size - 1;
			while (end != this->begin() + diff + count - 1)
			{
				*modify_ptr = *(modify_ptr - count);
				modify_ptr--;
				end--;
			}
			while (end != this->begin() + diff - 1)
			{
				*modify_ptr = value;
				modify_ptr--;
				end--;
			}
			return (this->begin() + diff);
		}

		template < typename InputIt >
		iterator			insert(iterator pos, InputIt first, InputIt last)
		{
			difference_type	diff;
			difference_type	count;
			iterator	end;
			pointer		modify_ptr;

			diff = pos - this->begin();
			count = last - first;
			if (this->_size + count > this->_capacity)
				this->resize(this->_size + count);
			else
				this->_size += count;
			end = this->end() - 1;
			modify_ptr = this->_vector_ptr + this->_size - 1;
			while (end != this->begin() + diff + count - 1)
			{
				*modify_ptr = *(modify_ptr - count);
				modify_ptr--;
				end--;
			}
			while (end != this->begin() + diff - 1)
			{
				*modify_ptr = *(last - 1);
				last--;
				modify_ptr--;
				end--;
			}
			return (this->begin() + diff);
		}

		iterator		erase(iterator pos)
		{
			difference_type	diff;
			iterator	end;
			pointer		modify_ptr;

			diff = pos - this->begin();
			end = this->end() - 1;
			modify_ptr = this->_vector_ptr + diff;
			while (pos != end)
			{
				*modify_ptr = *(modify_ptr + 1);
				modify_ptr++;
				pos++;
			}
			this->_allocator.destroy(modify_ptr);
			this->_size -= 1;
			return (this->begin() + diff);
		}

		iterator		erase(iterator first, iterator last)
		{
			difference_type	count;
			difference_type	diff;
			iterator	begin;
			pointer		modify_ptr;

			count = last - first;
			diff = this->end() - last;
			modify_ptr = this->_vector_ptr + (first - this->begin());
			begin = first;
			while (diff > 0)
			{
				*modify_ptr = *(modify_ptr + count);
				modify_ptr++;
				begin++;
				diff--;
			}
			while (begin != this->end())
			{
				this->_allocator.destroy(modify_ptr);
				modify_ptr++;
				begin++;
			}
			this->_size -= count;
			return (first);
		}

		void			swap(vector& other)
		{
			vector	tmp;

			tmp = *this;
			*this = other;
			other = tmp;
			return ;
		}

		void			clear(void)
		{
			this->resize(0);
			return ;
		}

		/** Allocator **/
		allocator_type		get_allocator(void) const
		{
			return (this->_allocator);
		}
};

}

#endif
