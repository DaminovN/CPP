#ifndef BIMAP_H
#define BIMAP_H

#include <bits/stdc++.h>

template<bool flag, typename T, typename TT>
struct get_right_type;
template<typename T, typename TT>
struct get_right_type<false, T, TT>
{
	typedef T type;
};
template<typename T, typename TT>
struct get_right_type<true, T, TT>
{
	typedef TT type;
};
template<typename T,typename TT>
struct node
{
    node<T, TT>* left_left;
    node<T, TT>* left_right;
    node<T, TT>* left_parent;
    node<T, TT>* right_left;
    node<T, TT>* right_right;
    node<T, TT>* right_parent;
    node() : left_left(nullptr), left_right(nullptr), left_parent(nullptr)
                        , right_left(nullptr), right_right(nullptr), right_parent(nullptr) {}

    virtual ~node() {}
    template<typename S,typename SS>
    friend node<S, SS>* getNext_left(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getNext_right(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getPrev_left(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getPrev_right(node<S, SS>* cur);
};
template<typename T, typename TT>
struct vnode : public node<T, TT>
{
    typedef T left_t;
    typedef TT right_t;
    left_t left_data;
    right_t right_data;
    vnode(left_t left, right_t right) : left_data(left), right_data(right) {}
    ~vnode() {}
};

template<typename T,typename TT>
node<T, TT>* getNext_left(node<T, TT>* cur)
{
	if (!cur->left_right)
    {
		while(cur->left_parent && (cur->left_parent)->left_right == cur)
			cur = cur->left_parent;
        cur = cur->left_parent;
    }
	else if(cur && cur->left_right)
	{
		cur = cur->left_right;
		while(cur->left_left)
			cur = cur->left_left;
	}
	return cur;
}
template<typename T,typename TT>
node<T, TT>* getNext_right(node<T, TT>* cur)
{
	if (!cur->right_right)
    {
		while(cur->right_parent && (cur->right_parent)->right_right == cur)
			cur = cur->right_parent;
        cur = cur->right_parent;
    }
	else if(cur && cur->right_right)
	{
		cur = cur->right_right;
		while(cur->right_left)
			cur = cur->right_left;
	}
	return cur;
}
template<typename T,typename TT>
node<T, TT>* getPrev_left(node<T, TT>* cur)
{
	if (!cur->left_left)
	{
        while(cur->left_parent && (cur->left_parent)->left_left == cur)
           cur = cur->left_parent;
        cur = cur->left_parent;
    }
	else if(cur && cur->left_left)
	{
		cur = cur->left_left;
		while(cur->left_right)
			cur = cur->left_right;
	}
	return cur;
}
template<typename T,typename TT>
node<T, TT>* getPrev_right(node<T, TT>* cur)
{
	if (!cur->right_left)
    {
		while(cur->right_parent && (cur->right_parent)->right_left == cur)
			cur = cur->right_parent;
        cur = cur->right_parent;
    }
	else if(cur && cur->right_left)
	{
		cur = cur->right_left;
		while(cur->right_right)
			cur = cur->right_right;
	}
	return cur;
}
template<typename T, typename TT>
struct BST
{
	node<T, TT>* root;
	typedef T left_t;
    typedef TT right_t;

	BST() : root(new node<T, TT>()) {}
    ~BST()
    {
        delete root;
    }
	node<T, TT>* insert_left(node<T, TT>* root, node<T, TT>* it)
    {
    	if (!root)
    	{
    		return it;
    	}
    	if (static_cast<vnode<T, TT>*>(it)->left_data < static_cast<vnode<T, TT>*>(root)->left_data)
    	{
            root->left_left = insert_left(root->left_left, it);
            (root->left_left)->left_parent = root;
            return root;
    	}
    	else 
    	{
    		root->left_right = insert_left(root->left_right, it);
    		(root->left_right)->left_parent = root;
            return root;
    	}
    }
    node<T, TT>* insert_right(node<T, TT>* root, node<T, TT>* it)
    {
    	if (!root)
    	{
    		return it;
    	}
    	if (static_cast<vnode<T, TT>*>(it)->right_data < static_cast<vnode<T, TT>*>(root)->right_data)
    	{
    		root->right_left = insert_right(root->right_left, it);
    		(root->right_left)->right_parent = root;
            return root;
    	}
    	else 
    	{
    		root->right_right = insert_right(root->right_right, it);
    		(root->right_right)->right_parent = root;
            return root;
    	}
    }
    node<T, TT>* check_left(node<T, TT>* root, left_t const& val) const
    {
    	if (!root)
    		return nullptr;
    	if (static_cast<vnode<T, TT>*>(root)->left_data > val)
    		return check_left(root->left_left, val);
    	else if (static_cast<vnode<T, TT>*>(root)->left_data < val)
    		return check_left(root->left_right, val);
    	else 
    		return root;
    }
    node<T, TT>* check_right(node<T, TT>* root, right_t const& val) const
    {
    	if (!root)
    		return nullptr;
    	if (static_cast<vnode<T, TT>*>(root)->right_data > val)
    		return check_right(root->right_left, val);
    	else if (static_cast<vnode<T, TT>*>(root)->right_data < val)
    		return check_right(root->right_right, val);
    	else 
    		return root;
    }
    node<T, TT>* insert(left_t const& lhs, right_t const& rhs)
    {
        if (root->left_left == nullptr)
        {
            node<T, TT>* it = new vnode<T, TT>(lhs, rhs);
            root->left_left = it;
            root->right_left = it;
            it->left_parent = root;
            it->right_parent = root;
            return it;
        }
    	if (check_left(root->left_left, lhs) != nullptr || check_right(root->right_left, rhs) != nullptr)
    		return root;
    	node<T, TT>* it = new vnode<T, TT>(lhs, rhs);
    	root->left_left = insert_left(root->left_left, it);
    	root->right_left = insert_right(root->right_left, it);
    	return it;
    }
    void erase_left(node<T, TT>* val)
    {
     	if (val->left_left && val->left_right)
		{
			node<T, TT>* left = val->left_left;
			node<T, TT>* right = val->left_right;
			node<T, TT>* temp = val;
			temp = getPrev_left(temp);
			if ((val->left_parent)->left_left == val)
				(val->left_parent)->left_left = left;
			else 
				(val->left_parent)->left_right = left;
			left->left_parent = val->left_parent;
			temp->left_right = right;
			right->left_parent = temp;
		}
		else if (val->left_left)
		{
			node<T, TT>* left = val->left_left;
			if ((val->left_parent)->left_left == val)
				(val->left_parent)->left_left = left;
			else 
				(val->left_parent)->left_right = left;
			left->left_parent = val->left_parent;
		}
		else if (val->left_right)
		{
			node<T, TT>* right = val->left_right;
			if ((val->left_parent)->left_left == val)
				(val->left_parent)->left_left = right;
			else 
				(val->left_parent)->left_right = right;
			right->left_parent = val->left_parent;
		}
        else 
        {
            if ((val->left_parent)->left_left == val)
                (val->left_parent)->left_left = nullptr;
            else 
                (val->left_parent)->left_right = nullptr;
        }
    }
    void erase_right(node<T, TT>* val)
    {
		if (val->right_left && val->right_right)
		{
			node<T, TT>* left = val->right_left;
			node<T, TT>* right = val->right_right;
			node<T, TT>* temp = val;
			temp = getPrev_right(temp);
			if ((val->right_parent)->right_left == val)
				(val->right_parent)->right_left = left;
			else 
				(val->right_parent)->right_right = left;
			left->right_parent = val->right_parent;
			temp->right_right = right;
			right->right_parent = temp;
		}
		else if (val->right_left)
		{
			node<T, TT>* left = val->right_left;
			if ((val->right_parent)->right_left == val)
				(val->right_parent)->right_left = left;
			else 
				(val->right_parent)->right_right = left;
			left->right_parent = val->right_parent;
		}
		else if (val->right_right)
		{
			node<T, TT>* right = val->right_right;
			if ((val->right_parent)->right_left == val)
				(val->right_parent)->right_left = right;
			else 
				(val->right_parent)->right_right = right;
			right->right_parent = val->right_parent;
		}
        else 
        {
            if ((val->right_parent)->right_left == val)
                (val->right_parent)->right_left = nullptr;
            else 
                (val->right_parent)->right_right = nullptr;
        }
		delete val;
    }
    void erase(node<T, TT>* val)
    {
        erase_left(val);
        erase_right(val);
    }
};

template <typename T, typename TT>
struct bimap
{
    typedef T left_t;
    typedef TT right_t;
	BST<left_t, right_t>* data;

    struct right_iterator;

    struct left_iterator
    {
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T const * pointer;
        typedef T const & reference;
        typedef std::bidirectional_iterator_tag iterator_category;
    	node<T, TT>* itData;

    	left_iterator() {}
    	left_iterator(node<T, TT>* _data): itData(_data) {}
		T const& operator*() const
    	{
    			return static_cast<vnode<T, TT>*>(itData)->left_data;
    	}
    	left_iterator& operator++()
	    {
	    		itData = getNext_left(itData);
	    	return (*this);
	    }
	    left_iterator operator++(int)
	    {
	    	left_iterator it2 = (*this);
	    	++(*this);
	    	return it2;
	    }
        left_iterator& operator=(left_iterator const& rhs)
        {
            itData = rhs.itData;
            return (*this);
        }
	    left_iterator& operator--()
	    {
	    		itData = getPrev_left(itData);
	    	return (*this);
	    }
	    left_iterator operator--(int)
	    {
	    	left_iterator it2 = (*this);
	    	--(*this);
	    	return it2;
	    }
	    right_iterator flip() const
	    {
	    	return right_iterator(itData);
	    }
        friend bool operator==(left_iterator const& lhs, left_iterator const& rhs)
        {
            return lhs.itData == rhs.itData;
        }
        friend bool operator!=(left_iterator const& lhs, left_iterator const& rhs)
        {
            return lhs.itData != rhs.itData;
        }
    };

    struct right_iterator
    {
        typedef std::ptrdiff_t difference_type;
        typedef TT value_type;
        typedef TT const * pointer;
        typedef TT const & reference;
        typedef std::bidirectional_iterator_tag iterator_category;
        node<T, TT>* itData;

        right_iterator() {}
        right_iterator(node<T, TT>* _data): itData(_data) {}
        TT const& operator*() const
        {
             return static_cast<vnode<T, TT>*>(itData)->right_data;
        }
        right_iterator& operator++()
        {
                itData = getNext_right(itData);
            return (*this);
        }
        right_iterator operator++(int)
        {
            right_iterator it2 = (*this);
            ++(*this);
            return it2;
        }
        right_iterator& operator=(right_iterator const& rhs)
        {
            itData = rhs.itData;
            return (*this);
        }
        right_iterator& operator--()
        {
            itData = getPrev_right(itData);
            return (*this);
        }
        right_iterator operator--(int)
        {
            right_iterator it2 = (*this);
            --(*this);
            return it2;
        }
        left_iterator flip() const
        {
            return left_iterator(itData);
        }
        friend bool operator==(right_iterator const& lhs, right_iterator const& rhs)
        {
            return lhs.itData == rhs.itData;
        }
        friend bool operator!=(right_iterator const& lhs, right_iterator const& rhs)
        {
            return lhs.itData != rhs.itData;
        }
    };

    bimap() : data(new BST<T, TT>()) {}
    bimap(bimap const&) = delete;
    bimap& operator=(bimap const&) = delete;
    ~bimap()
    {
    	while (begin_left() != end_left())
    	{
    		erase(begin_left());
    	}
        delete data;
    }
    left_iterator insert(left_t const& left, right_t const& right)
    {
    	return left_iterator(data->insert(left, right));
    }
    void erase(left_iterator it)
    {
    	data->erase(it.itData);
    }
    void erase(right_iterator it)
    {
    	data->erase(it.itData);
    }
    left_iterator find_left (left_t const& left) const
    {
        node<T, TT>* ans;
        ans = data->check_left(data->root->left_left, left);
        if (ans == nullptr)
            ans = data->root;
    	return left_iterator(ans);
    }
    right_iterator find_right(right_t const& right) const
    {
        node<T, TT>* ans;
        ans = data->check_right(data->root->right_left, right);
        if (ans == nullptr)
            ans = data->root;
    	return right_iterator(ans);
    }
    left_iterator begin_left() const
    {
    	node<T, TT>* tmp = data->root;
    	while (tmp->left_left)
    		tmp = tmp->left_left;
    	return left_iterator(tmp);
    }
    left_iterator end_left() const
    {
    	return left_iterator(data->root);
    }
    right_iterator begin_right() const
    {
    	node<T, TT>* tmp = data->root;
    	while (tmp->right_left)
    		tmp = tmp->right_left;
    	return right_iterator(tmp);
    }
    right_iterator end_right() const
    {
    	return right_iterator(data->root);
    }
};
#endif