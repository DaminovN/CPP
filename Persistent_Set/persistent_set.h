#pragma once
#include <bits/stdc++.h>
#include "my_shared_ptr.h"
#include "my_linked_ptr.h"

template <typename T, template<typename> class U = my_shared_ptr>
struct persistent_set
{
    // Вы можете определить этот тайпдеф по вашему усмотрению.
    typedef T value_type;

    // Bidirectional iterator.
    struct iterator;

    // Создает пустой persistent_set.
    persistent_set() noexcept : root(new base_node()) {}

    // Создает копию указанного persistent_set-а.
    persistent_set(persistent_set const& other) noexcept : root(other.root) {}
    persistent_set(persistent_set&& other) noexcept : root(std::move(other.root)) {}

    // Изменяет this так, чтобы он содержал те же элементы, что и rhs.
    // Инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    persistent_set& operator=(persistent_set const& rhs) noexcept
    {
    	root = rhs.root;
    	return *this;
    }
    persistent_set& operator=(persistent_set&& rhs) noexcept
    {
    	root = std::move(rhs.root);
    	return *this;
    }
    void swap(persistent_set& rhs) noexcept
    {
    	root.swap(rhs.root);
    }

    // Деструктор. Вызывается при удалении объектов persistent_set.
    // Инвалидирует все итераторы ссылающиеся на элементы этого persistent_set
    // (включая итераторы ссылающиеся на элемент следующий за последним).
    ~persistent_set() = default;

    // Поиск элемента.
    // Возвращает итератор на найденный элемент, либо end(), если элемент
    // с указанным значением отсутвует.
    iterator find(value_type const& val) const noexcept
    {
    	pointer temp(root->left);
    	while(temp != nullptr)
    	{
    		if (*temp->key > val)
    			temp = temp->left;
    		else if (*temp->key < val)
    			temp = temp->right;
    		else 
    			return iterator(temp, root);
    	}
    	return end();
    }

    // Вставка элемента.
    // 1. Если такой ключ уже присутствует, вставка не производиться, возвращается итератор
    //    на уже присутствующий элемент и false.
    // 2. Если такого ключа ещё нет, производиться вставка, возвращается итератор на созданный
    //    элемент и true.
    // Если вставка произведена, инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    std::pair<iterator, bool> insert(value_type const& val)
    {
    	iterator fnd = find(val);
    	if (fnd != end())
    		return {fnd, false};
    	pointer temp(new base_node());
    	std::pair<pointer, pointer> p = ins(root->left, val);
    	temp->left = p.first;
    	root.swap(temp);
    	return {iterator(p.second, root), true};
    }

    // Удаление элемента.
    // Инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
    void erase(iterator const& it)
    {
    	if(empty() || (it == end()) || (find(*it) == end()))
    		return;
    	pointer temp(new base_node());
    	temp->left = remove(root->left, *it);
    	root.swap(temp);
    }

    // Возващает итератор на элемент с минимальный ключом.
    iterator begin() const noexcept
    {
    	pointer tmp = root;
    	while (tmp->left)
    		tmp = tmp->left;
    	return iterator(tmp, root);
    }
    // Возващает итератор на элемент следующий за элементом с максимальным ключом.
    iterator end() const noexcept
    {
    	return iterator(root, root);
    }

    bool empty() const noexcept
    {
    	return (begin() == end());
    }

private:

	struct base_node;

	typedef U<base_node> pointer;

	struct base_node
	{
		base_node() : left(nullptr), right(nullptr), key(nullptr) {}
		~base_node() = default;

		pointer left;
		pointer right;
		T* key;
	};

	pointer root;

	std::pair<pointer, pointer> ins(pointer& old_root, value_type const& val)
	{
		if (!old_root)
		{
	    	pointer new_root = pointer(new base_node());
			new_root->key = new value_type(val);
			return {new_root, new_root};
		}
		if (*old_root->key > val)
		{	
	    	pointer new_root = pointer(new base_node());
		    new_root->key = new value_type(*old_root->key);
	    	new_root->right = old_root->right;
	    	std::pair<pointer, pointer> p = ins(old_root->left, val);
	    	new_root->left = p.first;
	    	return {new_root, p.second};
		}
		else if (*old_root->key < val)
		{
	    	pointer new_root = pointer(new base_node());
		    new_root->key = new value_type(*old_root->key);
	    	new_root->left = old_root->left;
	    	std::pair<pointer, pointer> p = ins(old_root->right, val);
	    	new_root->right = p.first;
	    	return {new_root, p.second};
		}
	}
	pointer remove(pointer old_root, value_type const& val)
	{
		if (*old_root->key == val)
		{
			if (old_root->left && old_root->right)
			{
		    	pointer new_root = pointer(new base_node());
		    	new_root->key = new value_type(*old_root->key);
		    	new_root->left = old_root->left;
		    	std::pair<pointer, pointer> p = go_left(old_root->right);
		    	new_root->right = p.first;
		    	std::swap(new_root->key, p.second->key);
		    	new_root->right = just_remove(new_root->right, val);
		    	return new_root;
			}
			else if (old_root->left)
				return old_root->left;	
			else if (old_root->right)
				return old_root->right;
			else 
				return nullptr;
		}
		if (*old_root->key > val)
		{	
	    	pointer new_root = pointer(new base_node());
	    	new_root->key = new value_type(*old_root->key);
	    	new_root->right = old_root->right;
	    	new_root->left = remove(old_root->left, val);
	    	return new_root;
		}
		else if (*old_root->key < val)
		{
	    	pointer new_root = pointer(new base_node());
	    	new_root->key = new value_type(*old_root->key);
	    	new_root->left = old_root->left;
	    	new_root->right = remove(old_root->right, val);
	    	return new_root;
		}
	}
	pointer just_remove(pointer root, value_type const& val)
	{
		if (*root->key == val)
		{
			return nullptr;
		}
		else if (*root->key > val)
		{
			root->left = just_remove(root->left, val);
		}
		else 
		{
			root->right = just_remove(root->right, val);
		}
		return root;
	}
	std::pair<pointer, pointer> go_left(pointer& old_root)
	{
		if (!old_root->left)
		{
			pointer new_root = pointer(new base_node());
	    	new_root->key = new value_type(*old_root->key);
	    	new_root->right = old_root->right;
	    	return {new_root, new_root};
		}
		pointer new_root = pointer(new base_node());
	    new_root->key = new value_type(*old_root->key);
    	new_root->right = old_root->right;
    	std::pair<pointer, pointer> p = go_left(old_root->left);
    	new_root->left = p.first;
    	return {new_root, p.second};
	}
};

template<typename T, template<typename> class U>
void swap(persistent_set<T, U>& a, persistent_set<T, U>& b) noexcept
{
	a.swap(b);
}

template<typename T, template<typename> class U>
struct persistent_set<T, U>::iterator
{
	iterator() noexcept : cur(nullptr), root(nullptr) {}

	iterator(pointer const& x, pointer const& y) noexcept : cur(x), root(y) {}

	iterator(iterator const& other) noexcept : cur(other.cur), root(other.root) {}
    // Элемент на который сейчас ссылается итератор.
    // Разыменование итератора end() неопределено.
    // Разыменование невалидного итератора неопределено.
    value_type const& operator*() const
    {
		return *cur->key;
	}

    // Переход к элементу со следующим по величине ключом.
    // Инкремент итератора end() неопределен.
    // Инкремент невалидного итератора неопределен.
    iterator& operator++()
    {
    	cur = next(root->left, cur).first;
    	return *this;
    }
    iterator operator++(int)
    {
    	iterator temp = *this;
    	++(*this);
    	return temp;
    }

    // Переход к элементу с предыдущим по величине ключом.
    // Декремент итератора begin() неопределен.
    // Декремент невалидного итератора неопределен.
    iterator& operator--()
    {
    	if (cur == root)
    	{
    		cur = cur->left;
    		while (cur->right)
    			cur = cur->right;
    	}
    	else 
    		cur = prev(root->left, cur).first;
    	return *this;
    }
    iterator operator--(int)
    {
    	iterator temp = *this;
    	--(*this);
    	return temp;
    }


	// Сравнение. Итераторы считаются эквивалентными если они ссылаются на один и тот же элемент.
	// Сравнение с невалидным итератором не определено.
	// Сравнение итераторов двух разных контейнеров не определено.
    friend bool operator==(iterator const& a, iterator const& b) noexcept
	{
		return ((a.cur == b.cur) && (a.root == b.root));
	}

	friend bool operator!=(iterator const& a, iterator const& b) noexcept
	{
		return ((a.cur != b.cur) || (a.root != b.root));
	}

private:
	pointer cur;
	pointer root;
	std::pair<pointer, bool> next(pointer& root, pointer cur)
	{
		if (!root)
			return {nullptr, false};
		if (*root->key > *cur->key)
		{
			std::pair<pointer, bool> nxt = next(root->left, cur);
			if (nxt.second)
				return nxt;
			return {root, true};
		}
		else 
		{
			return next(root->right, cur);
		}
	}
	std::pair<pointer, bool> prev(pointer& root, pointer cur)
	{
		if (!root)
			return {nullptr, false};
		if (*root->key < *cur->key)
		{
			std::pair<pointer, bool> prv = prev(root->right, cur);
			if (prv.second)
				return prv;
			return {root, true};
		}
		else 
		{
			return prev(root->left, cur);
		}
	}
};