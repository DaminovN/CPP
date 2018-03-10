#pragma once
#include <bits/stdc++.h>

template <typename T>
struct my_linked_ptr
{
	my_linked_ptr() = delete;

	my_linked_ptr(T* other) : ptr(other), prev(nullptr), next(nullptr) {}

	my_linked_ptr(my_linked_ptr const& other) noexcept : ptr(other.ptr), prev(&other), next(other.next)
	{
		normalize(*this);
	}
	my_linked_ptr(my_linked_ptr&& other) noexcept : ptr(other.ptr), prev(other.prev), next(other.next)
	{
		other.ptr = nullptr;
		other.prev = other.next = nullptr;
		normalize(*this);
	}

	my_linked_ptr& operator=(my_linked_ptr const& other) noexcept
	{
		my_linked_ptr temp(other);
		swap(temp);
		return *this;
	}
	my_linked_ptr& operator=(my_linked_ptr&& other) noexcept
	{
		swap(other);
		return *this;
	}
	T& operator *() const noexcept
	{
        return *ptr;
    }
    T* operator ->() const noexcept
	{
        return ptr;
    }
	explicit operator bool() const noexcept
	{
		return (ptr != nullptr);
	}

	void swap(my_linked_ptr& other) noexcept
	{
		if (ptr == other.ptr)
			return;
		std::swap(other.ptr, ptr);
		std::swap(other.next, next);
		std::swap(other.prev, prev);
		normalize(*this);
		normalize(other);
	}

	~my_linked_ptr() noexcept
	{
		erase();
	}

	friend bool operator == (my_linked_ptr const& a, my_linked_ptr const& b) noexcept 
	{
        return a.ptr == b.ptr;
    }

    friend bool operator != (my_linked_ptr const& a, my_linked_ptr const& b) noexcept 
    {
        return !(a == b);
    }

    friend bool operator == (my_linked_ptr const& a, std::nullptr_t) noexcept 
    {
        return !a.ptr;
    }

    friend bool operator != (my_linked_ptr const& a, std::nullptr_t) noexcept 
    {
        return a.ptr;
    }

    friend bool operator == (std::nullptr_t, my_linked_ptr const& a) noexcept 
    {
        return a.ptr == nullptr;
    }

    friend bool operator != (std::nullptr_t, my_linked_ptr const& a) noexcept 
    {
        return a.ptr != nullptr;
    }

private:
	T* ptr;
	mutable my_linked_ptr const* prev;
	mutable my_linked_ptr const* next;

	void erase() noexcept
	{
		if (prev == next)
			delete ptr;
		else 
		{
			if (prev)
				prev->next = next;
			if (next)
				next->prev = prev;
		}
	}
	void normalize(my_linked_ptr& p) noexcept
	{
		if (p.next)
		{
			p.next->prev = &p;
		}
		if (p.prev)
		{
			p.prev->next = &p;
		}
	}
};