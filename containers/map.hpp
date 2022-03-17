/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:11:17 by pgomez-a          #+#    #+#             */
/*   Updated: 2022/03/17 12:05:56 by pgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	private:
		/** Member Type **/
		typedef Bst<ft::pair<Key, T>, Compare, Alloc>	BTree;
	public:
		/** Member Types **/
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<Key, T>							value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename Alloc::reference					reference;
		typedef typename Alloc::const_reference				const_reference;
		typedef typename Alloc::pointer						pointer;
		typedef typename Alloc::const_pointer				const_pointer;
		typedef MapIterator<BTree*, value_type>				iterator;
		typedef MapIterator<const BTree*, const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;

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

		/** Member Attributes **/
		BTree			_Tree;
		BTree*			_root;
		BTree*			_end;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_alloc;

	public:
		/** Constructors **/
		explicit map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		{
			this->_root = 0;
			this->_end = 0;
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
			this->_root = 0;
			this->_end = 0;
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
			const_iterator	first(other.begin());

			this->_root = 0;
			this->_end = 0;
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
			const_iterator	first(other.begin());

			if (this != &other)
			{
				if (this->_size > 0)
					this->_Tree.clean(&(this->_root));
				this->_end->left = 0;
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
			iterator	it;
			
			if (this->_size == 0)
				it = iterator(this->_end);
			else
				it = iterator(this->_root);
			return (iterator(it.begin()));
		}

		const_iterator		begin(void) const
		{
			const_iterator	it;

			if (this->_size == 0)
				it = iterator(this->_end);
			else
				it = iterator(this->_root);
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

		reverse_iterator	rbegin(void)
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator	rbegin(void) const
		{
			return (reverse_iterator(this->end()));
		}

		reverse_iterator	rend(void)
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator	rend(void) const
		{
			return (reverse_iterator(this->begin()));
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
			return (this->_Tree.max_size());
		}

		/** Element access **/
		mapped_type&		operator[](const key_type& k)
		{
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		mapped_type&		at(const key_type& k)
		{
			BTree*	comp;

			comp = this->_Tree.search(this->_root, ft::pair<key_type, mapped_type>(k, mapped_type()));
			if (!comp)
				throw std::out_of_range("out of range");
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		const mapped_type&	at(const key_type& k) const
		{
			BTree*	comp;

			comp = this->_Tree.search(this->_root, ft::pair<key_type, mapped_type>(k, mapped_type()));
			if (!comp)
				throw std::out_of_range("out of range");
			return ((*((this->insert(ft::pair<key_type, mapped_type>(k,mapped_type()))).first)).second);
		}

		/** Modifiers **/
		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			BTree*	comp;

			comp = 0;
			if (this->_size > 0)
				comp = this->_Tree.search(this->_root, val);
			if (comp)
				return (ft::pair<iterator, bool>(iterator(comp), false));
			this->_size += 1;
			this->_root = this->_Tree.insert(this->_root, val);
			while (this->_root->parent && this->_root->parent->parent)
				this->_root = this->_root->parent;
			if (this->_size == 1)
			{
				this->_end->left = this->_root;
				this->_root->parent = this->_end;
			}
			comp = this->_Tree.search(this->_root, val);
			return (ft::pair<iterator, bool>(iterator(comp), true));
		}

		iterator					insert(iterator position, const value_type& val)
		{
			BTree*	comp;

			(void)position;
			comp = this->_Tree.search(this->_root, val);
			if (!comp)
			{
				this->_size += 1;
				this->_root = this->_Tree.insert(this->_root, val);
				while (this->_root->parent && this->_root->parent->parent)
					this->_root = this->_root->parent;
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
		void						insert(InputIt first, InputIt last)
		{
			BTree*		comp;
			size_type	init;

			init = this->_size;
			while (first != last)
			{
				comp = this->_Tree.search(this->_root, *first);
				if (!comp)
				{
					this->_size += 1;
					this->_root = this->_Tree.insert(this->_root, *first);
					while (this->_root->parent && this->_root->parent->parent)
						this->_root = this->_root->parent;
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

		size_type					erase(const key_type& k)
		{
			BTree*	comp;

			if (this->_size > 0)
			{
				comp = this->_Tree.search(this->_root, value_type(k, mapped_type()));
				if (!comp)
					return (0);
				this->_root = this->_Tree.deleteNode(this->_root, value_type(k, mapped_type()));
				while (this->_root && this->_root->parent && this->_root->parent->parent)
					this->_root = this->_root->parent;
				this->_size -= 1;
				if (this->_size == 0)
					this->_end->left = 0;
				else
				{
					this->_end->left = this->_root;
					this->_root->parent = this->_end;
				}
				return (1);
			}
			return (0);
		}

		void						erase(iterator position)
		{
			this->erase(position->first);
			return ;
		}

		void						erase(iterator first, iterator last)
		{
			int			len;
			int			count;
			iterator	ite;
			
			ite = first;
			len = 0;
			while (ite != last)
			{
				len++;
				ite++;
			}

			key_type	tmp_list[len];

			count = 0;
			ite = first;
			while (count < len)
			{
				tmp_list[count] = ite->first;
				count++;
				ite++;
			}
			count = 0;
			while (count < len)
				this->erase(tmp_list[count++]);
			return ;
		}

		void						swap(map& x)
		{
			BTree*			tmp_rot;
			BTree*			tmp_end;
			size_type		tmp_siz;
			key_compare		tmp_cmp;
			allocator_type	tmp_alc;

			tmp_rot = x._root;
			tmp_end = x._end;
			tmp_siz = x._size;
			tmp_cmp = x._comp;
			tmp_alc = x._alloc;
			x._root = this->_root;
			x._end = this->_end;
			x._size = this->_size;
			x._comp = this->_comp;
			x._alloc = this->_alloc;
			this->_root = tmp_rot;
			this->_end = tmp_end;
			this->_size = tmp_siz;
			this->_comp = tmp_cmp;
			this->_alloc = tmp_alc;
			return ;
		}

		void						clear(void)
		{
			if (this->_size > 0)
				this->_Tree.clean(&(this->_root));
			this->_end->left = 0;
			this->_root = 0;
			this->_size = 0;
			return ;
		}

		/** Observers **/
		key_compare		key_comp(void) const
		{
			return (this->_comp);
		}

		value_compare	value_comp(void) const
		{
			return (value_compare(this->_comp));
		}

		/** Operations **/
		iterator		find(const key_type& k)
		{
			iterator	output(this->_Tree.search(this->_root, value_type(k, mapped_type())));

			if (!output.root())
				return (this->end());
			return (output);
		}

		const_iterator	find(const key_type& k) const
		{
			const_iterator	output(this->_Tree.search(this->_root, value_type(k, mapped_type())));

			if (!output.root())
				return (this->end());
			return (output);
		}

		size_type		count(const key_type& k) const
		{
			BTree*	comp;

			comp = this->_Tree.search(this->_root, value_type(k, mapped_type()));
			if (!comp)
				return (0);
			return (1);
		}

		iterator		lower_bound(const key_type& k)
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

		const_iterator	lower_bound(const key_type& k) const
		{
			const_iterator	beg(this->begin());

			while (beg != this->end())
			{
				if (!this->_comp(beg.root()->data.first, k))
					return (beg);
				beg++;
			}
			return (beg);
		}

		iterator		upper_bound(const key_type& k)
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

		const_iterator	upper_bound(const key_type& k) const
		{
			const_iterator	beg(this->begin());

			while (beg != this->end())
			{
				if (!this->_comp(beg.root()->data.first, k) && beg.root()->data.first != k)
					return (beg);
				beg++;
			}
			return (beg);
		}

		ft::pair<iterator, iterator>				equal_range(const key_type& k)
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

/** Relational Operators **/
template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	beg_lhs;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	beg_rhs;

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

template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	beg_lhs;
	typename ft::map<Key, T, Compare, Alloc>::const_iterator	beg_rhs;

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

template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!(rhs < lhs));
}
template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (rhs < lhs);
}

template < typename Key, typename T, typename Compare, typename Alloc >
bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

/** Swap non-member functions **/
template < typename Key, typename T, typename Compare, typename Alloc >
void	swap(const ft::map<Key, T, Compare, Alloc>& x, const ft::map<Key, T, Compare, Alloc>& y)
{
	x.swap(y);
	return ;
}


}

#endif
