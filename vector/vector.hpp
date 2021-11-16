#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

template < typename T, typename Allocator = std::allocator<T> >
class	vector
{
	private:
		/** Member Types **/
		typedef T 					value_type;
		typedef Allocator				allocator_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef value_type&				reference;
		typedef const value_type&			const_reference;
		typedef typename Allocator::pointer		pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef value_type				iterator;
		typedef const value_type			const_iterator;
		typedef std::reverse_iterator<iterator>		reverse_iterator;
		typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

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
			const allocator_type& alloc = allocator_type());
		
		template < typename InputIt >
		vector(InputIt first, InputIt last,
			const allocator_type& alloc = allocator_type());

		vector(const vector& other);

		/** Destructor **/
		~vector(void)
		{
			// Destruir objectos con alloc.destroy()
			// Liberar memoria con alloc.deallocate()
			this->_size = 0;
			this->_capacity = 0;
			return ;
		}

		/** Assignation Operator **/
		vector&			operator=(const vector& other);

		/** Iterators **/
		iterator		begin(void);
		const_iterator		begin(void) const;
		iterator		end(void);
		const_iterator		end(void) const;
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

#endif
