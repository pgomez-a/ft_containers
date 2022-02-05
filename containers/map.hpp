#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <stdexcept>
# include "./utils/utils.hpp"
# include "./utils/pair.hpp"
# include "./utils/iterator.hpp"
# include "./utils/Bst.hpp"
# include "./utils/MapIterator.hpp"

namespace ft
{

template < typename Key, typename T, typename Compare = std::less<Key>,
	 typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
		/** Member Types **/
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>				value_type;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t					difference_type;
		typedef Compare						key_compare;
		typedef Alloc						allocator_type;
		typedef typename Alloc::reference			reference;
		typedef typename Alloc::const_reference			const_reference;
		typedef typename Alloc::pointer				pointer;
		typedef typename Alloc::const_pointer			const_pointer;
		typedef MapIterator<Key, T, Compare, Alloc>		iterator;
		typedef const MapIterator<Key, T, Compare, Alloc>	const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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


			public:
				/** Constructor **/
				value_compare(Compare c) : comp(c) {}

				/** Member Function **/
				bool	operator()(const value_type& lhs, const value_type& rhs) const
				{
					return (comp(lhs.first, rhs.first));
				}
		};

	private:
		/** Member Attributes **/
		Bst<key_type, mapped_type, key_compare, allocator_type >	_Tree;
		Bst<key_type, mapped_type, key_compare, allocator_type >*	_root;
		Bst<key_type, mapped_type, key_compare, allocator_type >*	_end;
		size_type							_size;
		key_compare							_comp;
		allocator_type							_alloc;

	public:
		/** Constructors **/
		explicit map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{
			this->_root = nullptr;
			this->_end = nullptr;
			this->_end = this->_Tree.insert(this->_end, value_type());
			this->_size = 0;
			this->_comp = comp;
			this->_alloc = alloc;
			return ;
		}

		template < class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{
			this->_root = nullptr;
			this->_end = nullptr;
			this->_end = this->_Tree.insert(this->_end, value_type());
			this->_size = 0;
			this->_comp = comp;
			this->_alloc = alloc;
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
			return ;
		}

		map(const map& other)
		{
			iterator	first(other.begin());

			this->_root = nullptr;
			this->_end = nullptr;
			this->_end = this->_Tree.insert(this->_end, value_type());
			this->_size = 0;
			this->_comp = other._comp;
			this->_alloc = other._alloc;
			if (other._size > 0)
			{
				while (first != other.end())
				{
					this->insert(*first);
					first++;
				}
			}
			return ;
		}

		/** Destructor **/
		~map(void)
		{
			this->_Tree.clean(&(this->_end));
			return ;
		}

		/** Assignation Operator **/
		map&	operator=(const map& other)
		{
			iterator	first(other.begin());

			if (this != &other)
			{
				if (this->_size > 0)
					this->_Tree.clean(&(this->_root));
				this->_end->left = nullptr;
				this->_size = 0;
				this->_comp = other._comp;
				this->_alloc = other._alloc;
				if (other.size() > 0)
				{
					while (first != other.end())
					{
						this->insert(value_type(first->first, first->second));
						first++;
					}
				}
			}
			return (*this);
		}

		/** Iterators **/
		iterator		begin(void)
		{
			iterator	it(this->_root);

			return (iterator(it.begin()));
		}

		const_iterator		begin(void) const
		{
			const_iterator	it(this->_root);

			return (const_iterator(it.begin()));
		}

		iterator		end(void)
		{
			return (iterator(this->_end));
		}

		const_iterator		end(void) const
		{
			return (const_iterator(this->_end));
		}

		reverse_iterator	rbegin(void) // NOTE: don't work
		{
			iterator	end(this->_root);

			return (reverse_iterator(end.end()));
		}

		const_reverse_iterator	rbegin(void) const
		{
			iterator	end(this->_root);

			return (reverse_iterator(end.end()));
		}

		reverse_iterator	rend(void)
		{
			iterator	beg(this->_root);

			return (reverse_iterator(beg.begin()));
		}

		const_reverse_iterator	rend(void) const
		{
			iterator	beg(this->_root);

			return (reverse_iterator(beg.begin()));
		}

		/** Capacity **/
		bool		empty(void) const
		{
			return (this->_size == 0);
		}

		size_type	size(void) const
		{
			return (this->_size);
		}
		
		size_type	max_size(void) const
		{
			return (this->_alloc.max_size());
		}

		/** Element access **/
		mapped_type&		operator[](const key_type& k)
		{
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		mapped_type&		at(const key_type& k)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;

			comp = this->_Tree.search(this->_root, ft::pair<key_type, mapped_type>(k, mapped_type()));
			if (comp == nullptr)
				throw std::out_of_range("out of range");
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		const mapped_type&	at(const key_type& k) const
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;

			comp = this->_Tree.search(this->_root, ft::pair<key_type, mapped_type>(k, mapped_type()));
			if (comp == nullptr)
				throw std::out_of_range("out of range");
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		/** Modifiers **/
		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp = nullptr;

			if (this->_size > 0)
				comp = this->_Tree.search(this->_root, val);
			if (comp != nullptr)
				return (ft::pair<iterator, bool>(iterator(comp), false));
			this->_size += 1;
			this->_root = this->_Tree.insert(this->_root, val);
			comp = this->_Tree.search(this->_root, val);
			if (this->_size == 1)
			{
				this->_end->left = this->_root;
				this->_root->parent = this->_end;
			}
			return (ft::pair<iterator, bool>(iterator(comp), true));
		}

		iterator			insert(iterator position, const value_type& val)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;

			(void)position;
			comp = this->_Tree.search(this->_root, val);
			if (comp == nullptr)
			{
				this->_size += 1;
				this->_root = this->_Tree.insert(this->_root, val);
				comp = this->_Tree.search(this->_root, val);
				if (this->_size == 1)
				{
					this->_end->left = this->_root;
					this->_root->parent = this->_end;
				}
			}
			return (iterator(comp));
		}

		template < typename InputIt >
		void				insert(InputIt first, InputIt last)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;
			size_type							init;

			init = this->_size;
			while (first != last)
			{
				comp = this->_Tree.search(this->_root, *first);
				if (comp == nullptr)
				{
					this->_size += 1;
					this->_root = this->_Tree.insert(this->_root, *first);
				}
				first++;
			}
			if (init == 0 && this->_size > 0)
			{
				this->_end->left = this->_root;
				this->_root->parent = this->_end;
			}
			return ;
		}

		size_type			erase(const key_type& k)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;

			if (this->_size > 0)
			{
				comp = this->_Tree.search(this->_root, value_type(k, mapped_type()));
				if (comp == nullptr)
					return (0);
				this->_root = this->_Tree.deleteNode(this->_root, value_type(k, mapped_type()));
				this->_size -= 1;
				if (this->_size == 0)
					this->_end->left = nullptr;
				else
				{
					this->_end->left = this->_root;
					this->_root->parent = this->_end;
				}
				return (1);
			}
			return (0);
		}

		void				erase(iterator position)
		{
			this->erase(position->first);
			return ;
		}

		void				erase(iterator first, iterator last)
		{
			while (first != last)
			{
				this->erase(first);
				first++;
			}
			return ;
		}

		void				swap(map& x)
		{
			map<key_type, mapped_type, key_compare, allocator_type>	tmp;

			tmp = *this;
			*this = x;
			x = tmp;
			return ;
		}

		void				clear(void)
		{
			if (this->_size > 0)
				this->_Tree.clean(&(this->_root));
			this->_size = 0;
			return ;
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

		/** Operations **/
		iterator					find(const key_type& k)
		{
			iterator	output(this->_Tree.search(this->_root, value_type(k, mapped_type())));

			if (output.root() == nullptr)
				return (this->end());
			return (output);
		}

		const_iterator					find(const key_type& k) const
		{
			const_iterator	output(this->_Tree.search(this->_root, value_type(k, mapped_type())));

			if (output.root() == nullptr)
				return (this->end());
			return (output);
		}

		size_type					count(const key_type& k)
		{
			Bst<key_type, mapped_type, key_compare, allocator_type>*	comp;

			comp = this->_Tree.search(this->_root, value_type(k, mapped_type()));
			if (comp == nullptr)
				return (0);
			return (1);
		}

		iterator					lower_bound(const key_type& k)
		{
			iterator	beg(this->begin());

			while (beg != this->end())
			{
				if (!this->_comp(beg.root()->data.first, k))
					return (beg);
				beg++;
			}
			return (beg);
		}

		const_iterator					lower_bound(const key_type& k) const
		{
			return (lower_bound(k));
		}

		iterator					upper_bound(const key_type& k)
		{
			iterator	beg(this->begin());

			while (beg != this->end())
			{
				if (!this->_comp(beg.root()->data.first, k) && beg.root()->data.first != k)
					return (beg);
				beg++;
			}
			return (beg);
		}

		const_iterator					upper_bound(const key_type& k) const
		{
			return (upper_bound(k));
		}

		ft::pair<iterator, iterator>			equal_range(const key_type& k)
		{
			return (ft::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
		}

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
		{
			return (ft::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
		}

		/** Allocator **/
		allocator_type	get_allocator(void) const
		{
			return (this->_alloc);
		}
};

}

#endif
