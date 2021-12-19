#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "./utils/utils.hpp"
# include "./utils/iterator.hpp"
# include "./utils/MapIterator.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = std::less<Key>,
	 typename Alloc = std::allocator<ft::pair<const Key, T> >
class map
{
	public:
		/** Member Types **/
		typedef Key							key_type;
		typedef T							mapped_type;
		typedef ft::pair<const Key, T>					value_type;
		typedef std::size_t						size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare							key_compare;
		typedef Allocator						allocator_type;
		typedef value_type&						reference;
		typedef const value_type&					const_reference;
		typedef Allocator::pointer					pointer;
		typedef Allocator::const_pointer				const_pointer;
		typedef MapIterator<ft::BstNode<value_type>, Compare>		iterator;
		typedef const MapIterator<ft::BstNode<value_type>, Compare>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		/** Member Class **/
		class value_compare
		{
			public:
				/** Member Types **/
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

			protected:
				/** Member Objects **/
				key_compare	comp;

				/** Constructor **/
				value_compare(Compare c) : comp(c) {}

			public:
				/** Member Function **/
				bool	operator()(const value_type& lhs, const value_tpye& rhs) const
				{
					return (comp(lhs.first, rhs.first));
				}
		};

	private:
		/** Member Attributes **/
		size_type			_size;
		key_compare			_comp;
		allocator_type			_allocator;
		ft::BstNode<value_type>		_node;
		ft::BstNode<value_type>		_beg;
		ft::BstNode<value_type>		_end;

	public:
		/** Constructors **/
		explicit map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{
			this->_size = 0;
			this->_comp = comp;
			this->_allocator = alloc;
			this->_beg = this->_node;
			this->_end = this->_node;
			return ;
		}

		map(const map& other);

		template < class InputIt >
			map(InputIt first, InputIt last,
			const key_compare& comp = key_compare();
			const allocator_type& alloc = allocator_type());

		/** Destructor **/
		~map(void);

		/** Assignation Operator **/
		map&	operator=(const map& other);

		/** Iterators **/
		iterator		begin(void)
		{
			return (BstIterator<value_type>(&this->_beg, &this->_beg, &this->_end));
		}

		const_iterator		begin(void) const
		{
			return (BstIterator<value_type>(&this->_beg, &this->_beg, &this->_end));
		}

		iterator		end(void)
		{
			return (BstIterator<value_type>(&this->_end, &this->_beg, &this->_end));
		}

		const_iterator		end(void) const
		{
			return (BstIterator<value_type>(&this->_end, &this->_beg, &this->_end));
		}

		reverse_iterator	rbegin(void)
		{
			return (reverse_iterator(&this->_end, &this->_beg, &this->_end));
		}

		const_reverse_iterator	rbegin(void) const
		{
			return (const_reverse_iterator(&this->_end, &this->_beg, &this->_end));
		}

		reverse_iterator	rend(void)
		{
			return (reverse_iterator(&this->_beg, &this->_beg, &this->_end));
		}

		const_reverse_iterator	rend(void) const
		{
			return (const_reverse_iterator(&this->_beg, &this->_beg, &this->_end));
		}

		/** Capacity **/
		bool		empty(void) const
		{
			return (this->_size == 0)
		}

		size_type	size(void) const
		{
			return (this->_size);
		}
		
		size_type	max_size(void) const
		{
			return (this->_allocator.max_size());
		}

		/** Observers **/
		key_compare	key_comp(void) const
		{
			return (this->_comp);
		}

		value_compare	value_comp(void) const
		{
			return (value_compare(this->_comp));
		}

		/** Allocator **/
		allocator_type	get_allocator(void) const
		{
			return (this->_allocator);
		}
};

}

#endif
