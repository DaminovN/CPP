#pragma once
#include <bits/stdc++.h>

template <typename T>
struct my_shared_ptr
{
	my_shared_ptr() = delete;

	my_shared_ptr(T* other) : cnt(nullptr), ptr(other)
	{
		if (ptr)
		{
			try
			{
				cnt = new size_t(1);
			}
			catch(...)
			{
				delete ptr;
				throw;
			}
		}
	}

	my_shared_ptr(my_shared_ptr const& other) noexcept : cnt(other.cnt), ptr(other.ptr)
	{
		if (ptr)
			++(*cnt);
	}
	my_shared_ptr(my_shared_ptr&& other) noexcept : cnt(other.cnt), ptr(other.ptr)
	{
		other.ptr = nullptr;
	}

	my_shared_ptr& operator=(my_shared_ptr const& other) noexcept
	{
		my_shared_ptr temp(other);
		swap(temp);
		return *this;
	}
	my_shared_ptr& operator=(my_shared_ptr&& other) noexcept
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

	void swap(my_shared_ptr& other) noexcept
	{
		std::swap(other.ptr, ptr);
		std::swap(other.cnt, cnt);
	}

	~my_shared_ptr() noexcept
	{
		erase();
	}

	friend bool operator == (my_shared_ptr const& a, my_shared_ptr const& b) noexcept 
	{
        return a.ptr == b.ptr;
    }

    friend bool operator != (my_shared_ptr const& a, my_shared_ptr const& b) noexcept 
    {
        return !(a == b);
    }

    friend bool operator == (my_shared_ptr const& a, std::nullptr_t) noexcept 
    {
        return !a.ptr;
    }

    friend bool operator != (my_shared_ptr const& a, std::nullptr_t) noexcept 
    {
        return a.ptr;
    }

    friend bool operator == (std::nullptr_t, my_shared_ptr const& a) noexcept 
    {
        return a.ptr == nullptr;
    }

    friend bool operator != (std::nullptr_t, my_shared_ptr const& a) noexcept 
    {
        return a.ptr != nullptr;
    }

private:
	size_t* cnt;
	T* ptr;

	void erase() noexcept
	{
		if (ptr)
		{
			if (*cnt == 1)
			{
				delete cnt;
				delete ptr;
			}
			else 
				--(*cnt);
		}
	}
};