#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "./utils/utils.hpp"
# include "./utils/iterator.hpp"
# include "./utils/VectorIterator.hpp"

namespace ft
{

template < typename T, typename Allocator = std::allocator<T> >
class	vector
{
	public:
		/** Member Types **/
		typedef T 					value_type;
		typedef Allocator				allocator_type;
		typedef typename Allocator::reference		reference;
		typedef typename Allocator::const_reference	const_reference;
		typedef typename Allocator::pointer		pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef VectorIterator<pointer>			iterator;
		typedef VectorIterator<const_pointer>		const_iterator;
		typedef ft::reverse_iterator<iterator>		reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef std::ptrdiff_t				difference_type;
		typedef std::size_t				size_type;

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

		explicit vector(size_type count,
			const_reference value = value_type(),
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
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
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
			if (this->_size > 0)
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
			return (iterator(this->_vector_ptr));
		}

		const_iterator		begin(void) const
		{
			return (const_iterator(this->_vector_ptr));
		}

		iterator		end(void)
		{
			return (iterator(this->_vector_ptr + this->_size));
		}

		const_iterator		end(void) const
		{
			return (const_iterator(this->_vector_ptr + this->_size));
		}

		reverse_iterator	rbegin(void)
		{
			return (reverse_iterator(this->_vector_ptr + this->_size));
		}

		const_reverse_iterator	rbegin(void) const
		{
			return (const_reverse_iterator(this->_vector_ptr + this->_size));
		}

		reverse_iterator	rend(void)
		{
			return (reverse_iterator(this->_vector_ptr));
		}

		const_reverse_iterator	rend(void) const
		{
			return (const_reverse_iterator(this->_vector_ptr));
		}

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
				begin = this->end();
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
				modify_ptr = this->_vector_ptr + this->_size;
				while (this->_size < count)
				{
					this->_allocator.construct(modify_ptr, value);
					modify_ptr++;
					this->_size++;
				}
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
			return (this->_size == 0);
		}

		/** Element Access **/
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
			if (pos >= this->_size)
				throw std::out_of_range("out of range");
			return (*(this->_vector_ptr + pos));
		}

		const_reference		at(size_type pos) const
		{
			if (pos >= this->_size)
				throw std::out_of_range("out of range");
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

		template < typename InputIt >
		void			assign(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
		{
			size_type	capacity;
			pointer		modify_ptr;
			InputIt		tmp_first;

			capacity = 0;
			tmp_first = first;
			while (tmp_first != last)
			{
				capacity++;
				tmp_first++;
			}
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
		iterator		insert(iterator pos, InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
		{
			difference_type	diff;
			difference_type	count;
			iterator	end;
			pointer		modify_ptr;
			InputIt		tmp_first;

			count = 0;
			tmp_first = first;
			while (tmp_first != last)
			{
				count++;
				tmp_first++;
			}
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
				*modify_ptr = *(--last);
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
			pointer		tmp_ptr;
			size_type	tmp_siz;
			size_type	tmp_cap;
			allocator_type	tmp_alc;

			tmp_ptr = other._vector_ptr;
			tmp_siz = other._size;
			tmp_cap = other._capacity;
			tmp_alc = other._allocator;
			other._vector_ptr = this->_vector_ptr;
			other._size = this->_size;
			other._capacity = this->_capacity;
			other._allocator = this->_allocator;
			this->_vector_ptr = tmp_ptr;
			this->_size = tmp_siz;
			this->_capacity = tmp_cap;
			this->_allocator = tmp_alc;
			return ;
		}

		void			clear(void)
		{
			if (this->_size > 0)
				this->resize(0);
			return ;
		}

		/** Allocator **/
		allocator_type		get_allocator(void) const
		{
			return (this->_allocator);
		}
};

/** Relational Operators **/
template < typename T, typename Alloc >
bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	typename ft::vector<T, Alloc>::const_iterator	beg_lhs;
	typename ft::vector<T, Alloc>::const_iterator	beg_rhs;

	if (lhs.size() == rhs.size())
	{
		beg_lhs = lhs.begin();
		beg_rhs = rhs.begin();
		while (beg_lhs != lhs.end())
		{
			if (*beg_lhs != *beg_rhs)
				return (false);
			beg_lhs++;
			beg_rhs++;
		}
		return (true);
	}
	return (false);
}

template < typename T, typename Alloc >
bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template < typename T, typename Alloc >
bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	typename ft::vector<T, Alloc>::const_iterator	beg_lhs;
	typename ft::vector<T, Alloc>::const_iterator	beg_rhs;

	beg_lhs = lhs.begin();
	beg_rhs = rhs.begin();
	while (beg_lhs != lhs.end() && beg_rhs != rhs.end())
	{
		if (*beg_lhs > *beg_rhs)
			return (false);
		if (*beg_lhs < *beg_rhs)
			return (true);
		beg_lhs++;
		beg_rhs++;
	}
	if (beg_lhs == lhs.end() && beg_rhs != rhs.end())
		return (true);
	return (false);
}

template < typename T, typename Alloc >
bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template < typename T, typename Alloc >
bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template < typename T, typename Alloc >
bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

/** Swap non-member function **/
template < typename T, typename Alloc >
void	swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y)
{
	x.swap(y);
	return ;
}

}

#endif
