#ifndef BIMAP_H
#define BIMAP_H

#include <bits/stdc++.h>

// using namespace std;




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
    node<T, TT>*   left_left;
    node<T, TT>*   left_right;
    node<T, TT>*   left_parent;

    node<T, TT>*   right_left;
    node<T, TT>*   right_right;
    node<T, TT>*   right_parent;

    node() : left_left(nullptr), left_right(nullptr), left_parent(nullptr)
                        , right_left(nullptr), right_right(nullptr), right_parent(nullptr) {}

    //all are friend
    template<typename S,typename SS>
    friend node<S, SS>* getNext_left(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getNext_right(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getPrev_left(node<S, SS>* cur);
    template<typename S,typename SS>
    friend node<S, SS>* getPrev_right(node<S, SS>* cur);
    // template<typename S,typename SS>
    // friend void printTree(node<S, SS>* cur); 
};
template<typename T, typename TT>
struct vnode : public node<T, TT>
{
    typedef T left_t;
    typedef TT right_t;
    left_t  left_data;
    right_t right_data;
    vnode(left_t left, right_t right) : left_data(left), right_data(right) {}
};
// template<typename T,typename TT>
// void printTree(node<T, TT>* cur)
// {
//     if (!cur)
//         return;
//     if (cur->left_left)
//     {
//         cout << cur->left_data << " LEFT " << (cur->left_left)->left_data << endl;
//     }
//     if (cur->left_right)
//     {
//         cout << cur->left_data << " RIGHT " << (cur->left_right)->left_data << endl;
//     }
//     printTree(cur->left_left);
//     printTree(cur->left_right);
// }

template<typename T,typename TT>
node<T, TT>* getNext_left(node<T, TT>* cur)
{
	// assert(cur->isEnd == false);
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
    // cout << "INHERE" << " " << cur->left_data << endl;
    // if (cur->left_left)
    //     cout << "CAN\n";
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
    // cout << "OUTHERE" << " " << cur->left_data << endl;
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

	//DONE
	BST() : root(new node<T, TT>()) {}

    ~BST() { }

	//DONE
	node<T, TT>* insert_left(node<T, TT>* root, node<T, TT>* it)
    {
        // std:://cout << root->left_data << "\n";
    	if (!root)
    	{
    		return it;
    	}
    	if (static_cast<vnode<T, TT>*>(it)->left_data < static_cast<vnode<T, TT>*>(root)->left_data)
    	{
            // std:://cout << "HERE\n";
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
    //DONE
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
    //DONE
    node<T, TT>* check_left(node<T, TT>* root, left_t const& val) const
    {
        // if (root)
        // {
        //     if (root->isEnd)
        //         std:://cout << "END\n";
        //     else 
        //         std:://cout << root->left_data << "\n";
        // }
    	if (!root)
    		return nullptr;
    	if (static_cast<vnode<T, TT>*>(root)->left_data > val)
    		return check_left(root->left_left, val);
    	else if (static_cast<vnode<T, TT>*>(root)->left_data < val)
    		return check_left(root->left_right, val);
    	else 
    		return root;
    }
    //DONE
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
    //DONE
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
        // cout << "HERE\n";
    	node<T, TT>* it = new vnode<T, TT>(lhs, rhs);
        // std:://cout << "START INSERT\n";
    	root->left_left = insert_left(root->left_left, it);
        // std:://cout<< "RIGHT\n";
    	root->right_left = insert_right(root->right_left, it);
    	return it;
    }
    //DONE
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
            // std::cout << "HERE@!\n";
            if ((val->left_parent)->left_left == val)
                (val->left_parent)->left_left = nullptr;
            else 
                (val->left_parent)->left_right = nullptr;
        }
    }
    //DONE
    void erase_right(node<T, TT>* val)
    {
		if (val->right_left && val->left_right)
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
    //DONE
    void erase(node<T, TT>* val)
    {
        // cerr << "HERE\n";
        // cerr << "GOIND IN TO ERASE_LEFT\n";
        // if (root->left_left == val)
            //cout << "ISLEFT\n";
        // std::cout << "HERE\n";
        erase_left(val);
        // std::cout << "HERE\n";
        erase_right(val);
        //cout << val->left_data << endl;
        // if (root->left_left)
        //     //cout << "NOT ERASED\n";
        // if (val)
            //cout << "NOT ERASED\n";
    }

};






template <typename T, typename TT>
struct bimap
{
    // Вы можете определить эти тайпдефы по вашему усмотрению.
    typedef T left_t;
    typedef TT right_t;
// private:
	BST<left_t, right_t>* data;


public:
    template<bool init_val>
    struct iterator
    {
    	node<T, TT>* itData;
    	// bool type = init_val;

    	iterator() {}
    	iterator(node<T, TT>* _data): itData(_data) {}
    	// iterator(iterator<init_val> const& _data) : itData(_data.idData) {}
	    // Элемент на который сейчас ссылается итератор.
	    // Разыменование итератора end_left() неопределено.
	    // Разыменование невалидного итератора неопределено.
		typename get_right_type<init_val, T, TT>::type const& operator*() const
    	{
    		if (!init_val)
    			return static_cast<vnode<T, TT>*>(itData)->left_data;
    		else 
    			return static_cast<vnode<T, TT>*>(itData)->right_data;
    	}

	    // Переход к следующему по величине left'у.
	    // Инкремент итератора end_left() неопределен.
	    // Инкремент невалидного итератора неопределен.

    	iterator& operator++()
	    {
	    	if (!init_val)
	    		itData = getNext_left(itData);
	    	else 
	    		itData = getNext_right(itData);
	    	return (*this);
	    }

	    iterator operator++(int)
	    {
	    	iterator<init_val> it2 = (*this);
	    	++(*this);
	    	return it2;
	    }

        iterator& operator=(iterator const& rhs)
        {
            iterator<init_val> it2 = (*this);
            ++(*this);
            return it2;
        }


	    // Переход к предыдущему по величине left'у.
	    // Декремент итератора begin_left() неопределен.
	    // Декремент невалидного итератора неопределен.
	    iterator& operator--()
	    {
            // cout << "in to --\n";
	    	if (!init_val)
	    		itData = getPrev_left(itData);
	    	else 
	    		itData = getPrev_right(itData);
	    	return (*this);
	    }
	    iterator operator--(int)
	    {
	    	iterator<init_val> it2 = (*this);
	    	--(*this);
	    	return it2;
	    }
	    bool equals(iterator<init_val> const& it) const
	    {
            // std:://cout << itData->isEnd << " " << (it.itData)->isEnd << "\n";
	    	return (itData == it.itData);
	    }
	    // left_iterator ссылается на левый элемент некоторой пары.
	    // Эта функция возвращает итератор на правый элемент той же пары.
	    // end_left().flip() возращает end_right().
	    // end_right().flip() возвращает end_left().
	    // flip() невалидного итератора неопределен.
	    iterator<init_val ^ 1> flip() const
	    {
	    	return iterator<init_val ^ 1> (itData);
	    }
        friend bool operator==(iterator const& lhs, iterator const& rhs)
        {
            return lhs.itData == rhs.itData;
        }

    };



    typedef iterator<false> left_iterator;
    typedef iterator<true> right_iterator;

    // Создает bimap не содержащий ни одной пары.
    bimap() : data(new BST<T, TT>())
    {
    	// data = new BST<T, TT>();
    }

    // Деструктор. Вызывается при удалении объектов bimap.
    // Инвалидирует все итераторы ссылающиеся на элементы этого bimap
    // (включая итераторы ссылающиеся на элементы следующие за последними).
    ~bimap()
    {
        // std:://cout << "DESTRUCTOR\n";
        // std::cout << (begin_left().equals(end_left())) << "\n";
    	while (!(begin_left().equals(end_left())))
    	{
            // cout << "WORKING " << *begin_left() << "\n";
    		erase(begin_left());
    	}
    }

    // Вставка пары (left, right), возвращает итератор на left.
    // Если такой left или такой right уже присутствуют в bimap, вставка не
    // производится и возвращается end_left().
    left_iterator insert(left_t const& left, right_t const& right)
    {
    	return left_iterator(data->insert(left, right));
    }

    // Удаляет элемент и соответствующий ему парный.
    // erase невалидного итератора неопределен.
    // erase(end_left()) и erase(end_right()) неопределены.
    // Пусть it ссылается на некоторый элемент e.
    // erase инвалидирует все итераторы ссылающиеся на e и на элемент парный к e.
    void erase(left_iterator it)
    {
    	// assert(it.itData);
    	data->erase(it.itData);
    }
    void erase(right_iterator it)
    {
    	assert(it.itData);
    	data->erase(it.itData);
    }

    // Возвращает итератор по элементу. В случае если элемент не найден, возвращает
    // end_left()/end_right() соответственно.
    left_iterator  find_left (left_t  const& left)  const
    {
    	return left_iterator(data->check_left(data->root, left));
    }
    right_iterator find_right(right_t const& right) const
    {
    	return right_iterator(data->check_right(data->root, right));
    }

    // Возващает итератор на минимальный по величине left.
    left_iterator begin_left() const
    {
        // std::cout << "HERE\n";
        // if (!data)
    	node<T, TT>* tmp = data->root;
    	while (tmp->left_left)
    		tmp = tmp->left_left;
        // std:://cout << "returning begin_left " << tmp->left_data << "\n";
    	return left_iterator(tmp);
    }
    left_iterator end_left() const
    {
        // std:://cout << "returning end_left " << (data->root)->isEnd << "\n";
    	return left_iterator(data->root);
    }

    // Возващает итератор на минимальный по величине right.
    right_iterator begin_right() const
    {
    	node<T, TT>* tmp = data->root;
    	while (tmp->right_left)
    		tmp = tmp->right_left;
    	return right_iterator(tmp);
    }
    // Возващает итератор на следующий за последним по величине right.
    right_iterator end_right() const
    {
    	return right_iterator(data->root);
    }
};
#endif