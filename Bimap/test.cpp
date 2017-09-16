#include <bits/stdc++.h>
#include <cstddef>
using namespace std;
template<typename T,typename TT>
struct node
{
	typedef T left_t;
	typedef TT right_t;
    left_t  left_data;
    node<T, TT>*   left_left;
    node<T, TT>*   left_right;
    node<T, TT>*   left_parent;

    right_t right_data;
    node<T, TT>*   right_left;
    node<T, TT>*   right_right;
    node<T, TT>*   right_parent;

    bool isEnd;
    node() {}
};
template<typename T,typename TT>
struct BST
{
	node<T, TT>* root;

	typedef T left_t;
    typedef TT right_t;
    BST()
	{
		root = new node<T, T>();
		root->isEnd = true;
	}

    ~BST()
    {
        delete root;
    }
};
template<typename T,typename TT>
struct bimap
{
    // Вы можете определить эти тайпдефы по вашему усмотрению.
    typedef T left_t;
    typedef TT right_t;
// private:
	BST<left_t, right_t>* data;
	bimap()
    {
    	data = new BST<T, TT>();
    }
    ~bimap()
    {
        cout << data->root->left_data << endl;
    	delete data;
    }
};
int main()
{
	bimap<int, int> a;
	
	return 0;
}



// #ifndef BIMAP_H
// #define BIMAP_H

// #include <bits/stdc++.h>

// template<bool flag, typename T, typename TT>
// struct get_right_type;

// template<typename T, typename TT>
// struct get_right_type<false, T, TT>
// {
// 	typedef T type;
// };

// template<typename T, typename TT>
// struct get_right_type<true, T, TT>
// {
// 	typedef TT type;
// };
// template<T, TT>
// struct node
// {
//     left_t  left_data;
//     node*   left_left;
//     node*   left_right;
//     node*   left_parent;

//     right_t right_data;
//     node*   right_left;
//     node*   right_right;
//     node*   right_parent;

//     bool isEnd;

//     node() : isEnd(true) {}
//     node(left_t const& lhs, right_t const& rhs) : left_data(lhs), right_data(rhs), isEnd(false) {}

//     void insert_left(node* it)
//     {
//     	if (!this)
//     	{
//     		this = it;
//     	}
//     	if (this->isEnd || it->left_data >= this->left_data)
//     	{
//     		left_left->insert_left(it);

//     		(left_left)->left_parent = this;
//     	}
//     	else 
//     	{
//     		left_right->insert_left(it);
//     		(left_right)->left_parent = this;
//     	}
//     }

//     void insert_right(node* it)
//     {
//     	if (!this)
//     	{
//     		this = it;
//     	}
//     	if (this->isEnd || it->right_data >= this->right_data)
//     	{
//     		right_left->insert_left(it);
//     		(right_left)->right_parent = this;
//     	}
//     	else 
//     	{
//     		right_right->insert_left(it);
//     		(right_right)->right_parent = this;
//     	}
//     }
//     node* check_left(left_t const& val) const
//     {
//     	if (!this)
//     		return NULL;
//     	else if (isEnd)
//     	{
//     		node* tmp = left_left->check_left(val);
//     		if (tmp)
//     			return tmp;
//     		return this;
//     	}
//     	else if (this->left_data > val)
//     		return left_left->check_left(val);
//     	else if (this->left_data < val)
//     		return left_right->check_left(val);
//     	else 
//     		return this;
//     }
//     node* check_right(right_t const& val) const
//     {
//     	if (!this)
//     		return NULL;
//     	else if (isEnd)
//     	{
//     		node* tmp = right_left->check_right(val);
//     		if (tmp)
//     			return tmp;
//     		return this;
//     	}
//     	else if (this->right_data > val)
//     		return right_left->check_right(val);
//     	else if (this->right_data < val)
//     		return right_right->check_right(val);
//     	else 
//     		return this;
//     }
//     node* insert(left_t const& lhs, right_t const& rhs)
//     {
//     	if (check_left(lhs)->isEnd == true || check_right(rhs)->isEnd == true)
//     		return this;
//     	node* it = new node(lhs, rhs);
//     	insert_left(it);
//     	insert_right(it);
//     	return it;
//     }
//     node* goNext_left()
//     {
//     	assert(this->isEnd == false);
//     	node* cur = this;
//     	if (!cur->left_right)
//     		while(cur->left_parent && (cur->left_parent)->left_right == cur)
//     			cur = cur->left_parent;
//     	else if(cur && cur->left_right)
//     	{
//     		cur = cur->left_right;
//     		while(this->left_left)
//     			cur = this->left_left;
//     	}
//     	return cur;
//     }
//     node* goNext_right()
//     {
//     	assert(this->isEnd == false);
//     	node* cur = this;
//     	if (!cur->right_right)
//     		while(cur->right_parent && (cur->right_parent)->right_right == cur)
//     			cur = cur->right_parent;
//     	else if(cur && cur->right_right)
//     	{
//     		cur = cur->right_right;
//     		while(cur->right_left)
//     			cur = cur->right_left;
//     	}
//     	return cur
//     }
//     node* goPrev_left()
//     {
//     	node* cur = this;
//     	if (!cur->left_left)
//     		while(cur->left_parent && (cur->left_parent)->left_left == cur)
//     			cur = cur->left_parent;
//     	else if(cur && cur->left_left)
//     	{
//     		cur = cur->left_left;
//     		while(cur->left_right)
//     			cur = cur->left_right;
//     	}
//     	return cur
//     }
//     node* goPrev_right()
//     {
//     	node* cur = this;
//     	if (!cur->right_left)
//     		while(cur->right_parent && (cur->right_parent)->right_left == cur)
//     			cur = cur->right_parent;
//     	else if(this && this->right_left)
//     	{
//     		cur = cur->right_left;
//     		while(cur->right_right)
//     			cur = cur->right_right;
//     	}
//     	return cur
//     }
//     void erase()
//     {
//     	erase_left();
//     	erase_right();
//     }
//     void erase_left()
//     {
//     	node* val = this;
//     	assert(val->isEnd == false);
// 		if (val->left_left && val->left_right)
// 		{
// 			node* left = val->left_left;
// 			node* right = val->left_right;
// 			node* par = val->left_parent;
// 			node* temp = val;
// 			temp->goPrev_left();
// 			if ((val->left_parent)->left_left == val)
// 				(val->left_parent)->left_left = left;
// 			else 
// 				(val->left_parent)->left_right = left;
// 			left->left_parent = val->left_parent;
// 			temp->left_right = right;
// 			right->left_parent = temp;
// 		}
// 		else if (val->left_left)
// 		{
// 			node* left = val->left_left;
// 			node* par = val->left_parent;
// 			if ((val->left_parent)->left_left == val)
// 				(val->left_parent)->left_left = left;
// 			else 
// 				(val->left_parent)->left_right = left;
// 			left->left_parent = val->left_parent;
// 		}
// 		else if (val->left_right)
// 		{
// 			node* right = val->left_right;
// 			node* par = val->left_parent;
// 			if ((val->left_parent)->left_left == val)
// 				(val->left_parent)->left_left = right;
// 			else 
// 				(val->left_parent)->left_right = right;
// 			right->left_parent = val->left_parent;
// 		}
//     }

//     void erase_right()
//     {
//     	node* val = this;
//     	assert(val->isEnd == false);
// 		if (val->right_left && val->left_right)
// 		{
// 			node* left = val->right_left;
// 			node* right = val->right_right;
// 			node* par = val->right_parent;
// 			node* temp = val;
// 			temp->goPrev_right();
// 			if ((val->right_parent)->right_left == val)
// 				(val->right_parent)->right_left = left;
// 			else 
// 				(val->right_parent)->right_right = left;
// 			left->right_parent = val->right_parent;
// 			temp->right_right = right;
// 			right->right_parent = temp;
// 		}
// 		else if (val->right_left)
// 		{
// 			node* left = val->right_left;
// 			node* par = val->right_parent;
// 			if ((val->right_parent)->right_left == val)
// 				(val->right_parent)->right_left = left;
// 			else 
// 				(val->right_parent)->right_right = left;
// 			left->right_parent = val->right_parent;
// 		}
// 		else if (val->right_right)
// 		{
// 			node* right = val->right_right;
// 			node* par = val->right_parent;
// 			if ((val->right_parent)->right_left == val)
// 				(val->right_parent)->right_left = right;
// 			else 
// 				(val->right_parent)->right_right = right;
// 			right->right_parent = val->right_parent;
// 		}
// 		delete val;
//     }
// };


// template <typename T, typename TT>
// struct bimap
// {
//     // Вы можете определить эти тайпдефы по вашему усмотрению.
//     typedef T left_t;
//     typedef TT right_t;
// private:
// 	struct node;


// public:
//     template<bool init_val>
//     struct iterator
//     {
//     	node* itData;
//     	// bool type = init_val;

//     	iterator() {}
//     	iterator(node* _data): itData(_data) {}
//     	// iterator(iterator<init_val> const& _data) : itData(_data.idData) {}
// 	    // Элемент на который сейчас ссылается итератор.
// 	    // Разыменование итератора end_left() неопределено.
// 	    // Разыменование невалидного итератора неопределено.
// 		typename get_right_type<init_val, T, TT>::type const& operator*() const
//     	{
//     		if (!init_val)
//     			return itData->left_data;
//     		else 
//     			return itData->right_data;
//     	}

// 	    // Переход к следующему по величине left'у.
// 	    // Инкремент итератора end_left() неопределен.
// 	    // Инкремент невалидного итератора неопределен.

//     	iterator& operator++()
// 	    {
// 	    	if (!init_val)
// 	    		itData->goNext_left();
// 	    	else 
// 	    		itData->goNext_right();
// 	    	return (*this);
// 	    }

// 	    iterator operator++(int)
// 	    {
// 	    	iterator<init_val> it2 = (*this);
// 	    	++(*this);
// 	    	return it2;
// 	    }


// 	    // Переход к предыдущему по величине left'у.
// 	    // Декремент итератора begin_left() неопределен.
// 	    // Декремент невалидного итератора неопределен.
// 	    iterator& operator--()
// 	    {
// 	    	if (!init_val)
// 	    		itData->goPrev_left();
// 	    	else 
// 	    		itData->goPrev_right();
// 	    	return (*this);
// 	    }
// 	    iterator operator--(int)
// 	    {
// 	    	iterator<init_val> it2 = (*this);
// 	    	--(*this);
// 	    	return it2;
// 	    }
// 	    bool equals(iterator<init_val> const& it) const
// 	    {
// 	    	return (itData == it.itData);
// 	    }
// 	    // left_iterator ссылается на левый элемент некоторой пары.
// 	    // Эта функция возвращает итератор на правый элемент той же пары.
// 	    // end_left().flip() возращает end_right().
// 	    // end_right().flip() возвращает end_left().
// 	    // flip() невалидного итератора неопределен.
// 	    iterator<init_val ^ 1> flip() const
// 	    {
// 	    	return iterator<init_val ^ 1> (itData);
// 	    }

//     };



//     typedef iterator<false> left_iterator;
//     typedef iterator<true> right_iterator;

//     // Создает bimap не содержащий ни одной пары.
//     bimap()
//     {
//     	data = new node();
//     }

//     // Деструктор. Вызывается при удалении объектов bimap.
//     // Инвалидирует все итераторы ссылающиеся на элементы этого bimap
//     // (включая итераторы ссылающиеся на элементы следующие за последними).
//     ~bimap()
//     {
//     	while (!(begin_left().equals(end_left())))
//     	{
//     		erase(begin_left());
//     	}
//     	delete data;
//     }

//     // Вставка пары (left, right), возвращает итератор на left.
//     // Если такой left или такой right уже присутствуют в bimap, вставка не
//     // производится и возвращается end_left().
//     left_iterator insert(left_t const& left, right_t const& right)
//     {
//     	return left_iterator(data->insert(left, right));
//     }

//     // Удаляет элемент и соответствующий ему парный.
//     // erase невалидного итератора неопределен.
//     // erase(end_left()) и erase(end_right()) неопределены.
//     // Пусть it ссылается на некоторый элемент e.
//     // erase инвалидирует все итераторы ссылающиеся на e и на элемент парный к e.
//     void erase(left_iterator it)
//     {
//     	assert(!it.itData);
//     	(it.itData)->erase();
//     }
//     void erase(right_iterator it)
//     {

//     	assert(!it.itData);
//     	(it.itData)->erase();
//     }

//     // Возвращает итератор по элементу. В случае если элемент не найден, возвращает
//     // end_left()/end_right() соответственно.
//     left_iterator  find_left (left_t  const& left)  const
//     {
//     	return left_iterator(check_left(left));
//     }
//     right_iterator find_right(right_t const& right) const
//     {
//     	return right_iterator(check_right(right));
//     }

//     // Возващает итератор на минимальный по величине left.
//     left_iterator begin_left() const
//     {
//     	node* tmp = data;
//     	while (tmp->left_left)
//     		tmp = tmp->left_left;
//     	return left_iterator(tmp);
//     }
//     left_iterator end_left() const
//     {
//     	return left_iterator(data);
//     }

//     // Возващает итератор на минимальный по величине right.
//     right_iterator begin_right() const
//     {
//     	node* tmp = data;
//     	while (tmp->right_left)
//     		tmp = tmp->right_left;
//     	return right_iterator(tmp);
//     }
//     // Возващает итератор на следующий за последним по величине right.
//     right_iterator end_right() const
//     {
//     	return right_iterator(data);
//     }
// private:
// 	node* data;
// };

// // template <typename T, typename TT>
// // void bimap<T, TT>::node::erase_left(node* val)
// // {
// // 	assert(val->isEnd == false)
// // 	if (val->left_left && val->left_right)
// // 	{
// // 		node* left = val->left_left;
// // 		node* right = val->left_right;
// // 		node* par = val->left_parent;
// // 		node* temp = val;
// // 		temp->goPrev_left();
// // 		if ((val->left_parent)->left_left == val)
// // 			(val->left_parent)->left_left = left;
// // 		else 
// // 			(val->left_parent)->left_right = left;
// // 		left->left_parent = val->left_parent
// // 		temp->left_right = right;
// // 		right->left_parent = temp;
// // 	}
// // 	else if (val->left_left)
// // 	{
// // 		node* left = val->left_left;
// // 		node* par = val->left_parent;
// // 		if ((val->left_parent)->left_left == val)
// // 			(val->left_parent)->left_left = left;
// // 		else 
// // 			(val->left_parent)->left_right = left;
// // 		left->left_parent = val->left_parent
// // 	}
// // 	else if (val->left_right)
// // 	{
// // 		node* right = val->left_right;
// // 		node* par = val->left_parent;
// // 		if ((val->left_parent)->left_left == val)
// // 			(val->left_parent)->left_left = right;
// // 		else 
// // 			(val->left_parent)->left_right = right;
// // 		right->left_parent = val->left_parent
// // 	}
// // }
// // template <typename T, typename TT>
// // void bimap<T, TT>::node::erase_right(node* val)
// // {
// // 	assert(val->isEnd == false)
// // 	if (val->right_left && val->left_right)
// // 	{
// // 		node* left = val->right_left;
// // 		node* right = val->right_right;
// // 		node* par = val->right_parent;
// // 		node* temp = val;
// // 		temp->goPrev_right();
// // 		if ((val->right_parent)->right_left == val)
// // 			(val->right_parent)->right_left = left;
// // 		else 
// // 			(val->right_parent)->right_right = left;
// // 		left->right_parent = val->right_parent
// // 		temp->right_right = right;
// // 		right->right_parent = temp;
// // 	}
// // 	else if (val->right_left)
// // 	{
// // 		node* left = val->right_left;
// // 		node* par = val->right_parent;
// // 		if ((val->right_parent)->right_left == val)
// // 			(val->right_parent)->right_left = left;
// // 		else 
// // 			(val->right_parent)->right_right = left;
// // 		left->right_parent = val->right_parent
// // 	}
// // 	else if (val->right_right)
// // 	{
// // 		node* right = val->right_right;
// // 		node* par = val->right_parent;
// // 		if ((val->right_parent)->right_left == val)
// // 			(val->right_parent)->right_left = right;
// // 		else 
// // 			(val->right_parent)->right_right = right;
// // 		right->right_parent = val->right_parent
// // 	}
// // 	delete val;
// // }
// #endif