//
// Created by daminovn on 9/26/18.
//

#ifndef VARIANT_STORAGE_H
#define VARIANT_STORAGE_H
#include <type_traits>
#include <iostream>
#include <utility>
#include <typeinfo>

inline constexpr std::size_t variant_npos = -1;

template <size_t I>
using build_const = std::integral_constant <size_t, I>;

template <bool, typename ... Ts>
struct storage;

template <typename ... Ts>
using storage_t = storage <std::conjunction_v <std::is_trivially_destructible <Ts>...>, Ts...>;

template <bool is_trivially_destructible, typename ... Ts>
struct storage {
    template <typename T>
    void constructor(size_t id, T&& other)
    {}

    template <typename ... Args>
    void implace_constructor(size_t id, Args&& ... args);

    void clear(size_t)
    {}
};

template <typename T0, typename ... Ts>
struct storage<1, T0, Ts...> {

    union {
        T0 head;
        storage_t<Ts...> tail;
    };

    constexpr storage() noexcept(std::is_nothrow_constructible_v<T0>) : head() {}

    template<typename ... Args>
    constexpr storage(build_const<0>, Args&& ... args) noexcept(std::is_nothrow_constructible_v<T0, Args...>) : head(std::forward<Args>(args)...) {}

    template<size_t I, typename ... Args>
    constexpr storage(build_const<I>, Args&& ... args) noexcept(std::is_nothrow_constructible_v<storage_t<Ts...>, build_const<I - 1>, Args...>)
            : tail(build_const<I - 1>{}, std::forward<Args>(args)...) {}

    template <typename T>
    void constructor(size_t id, T&& other) {
        if (id == 0) {
            new (&head) T0(std::forward<T>(other).head);
        } else {
            tail.constructor(id - 1, std::forward<T>(other).tail);
        }
    }

    template <typename ... Args>
    void implace_constructor(size_t id, Args&& ... args) {
        if (id == 0) {
            new (&head) T0(std::forward<Args>(args)...);
        } else {
            tail.implace_constructor(id - 1, std::forward<Args>(args)...);
        }
    }

    void clear(size_t id) noexcept {
        if (id == 0) {
            head.~T0();
        } else {
            tail.clear(id - 1);
        }
    }
};

template <typename T0, typename ... Ts>
struct storage<0, T0, Ts...> {

    union {
        T0 head;
        storage_t<Ts...> tail;
    };

    constexpr storage() noexcept(std::is_nothrow_constructible_v<T0>) : head() {}

    template<typename ... Args>
    constexpr storage(build_const<0>, Args&& ... args) noexcept(std::is_nothrow_constructible_v<T0, Args...>) : head(std::forward<Args>(args)...) {}

    template<size_t I, typename ... Args>
    constexpr storage(build_const<I>, Args&& ... args) noexcept(std::is_nothrow_constructible_v<storage_t<Ts...>, build_const<I - 1>, Args...>)
            : tail(build_const<I - 1>{}, std::forward<Args>(args)...) {}

    template <typename T>
    void constructor(size_t id, T&& other) {
        if (id == 0) {
            new (&head) T0(std::forward<T>(other).head);
        } else {
            tail.constructor(id - 1, std::forward<T>(other).tail);
        }
    }

    template <typename ... Args>
    void implace_constructor(size_t id, Args&& ... args) {
        if (id == 0) {
            new (&head) T0(std::forward<Args>(args)...);
        } else {
            tail.implace_constructor(id - 1, std::forward<Args>(args)...);
        }
    }

    void clear(size_t id) noexcept {
        if (id == 0) {
            head.~T0();
        } else {
            tail.clear(id - 1);
        }
    }
    ~storage() noexcept {};
};

template <typename S>
constexpr decltype(auto) get_storage_value(build_const<0>, S&& s) {
    return (std::forward<S>(s).head);
}

template <typename S>
constexpr decltype(auto) get_storage_value(build_const<I>, S&& s) {
    return get_storage_value(build_const<I - 1>{}, std::forward<S>(s).tail);
}

template <>
void swap_value(size_t id, storage_t<>& a, storage_t<>& b) {}

template <typename ...Ts>
void swap_value(size_t id, storage_t<Ts...>& a, storage_t<Ts...>& b) {
    if (id == 0) {
        std::swap(a.head, b.head);
    } else {
        swap_value(id - 1, a.tail, b.tail);
    }
}

template <bool is_trivially_destructible, typename ...Ts>
struct destroyable_storage : storage_t<Ts...> {
    size_t id;
    using base = storage_t<Ts...>;
    using base::base;
    destroyable_storage() = default;

    template<size_t I, typename ... Args>
    constexpr destroyable_storage(build_const<I>, Args&& ... args) noexcept(std::is_nothrow_constructible_v<base, build_const<I>, Args...>)
            : base(build_const<I>{}, std::forward<Args>(args)...), id(I) {}

    constexpr void set_id(size_t rhs_id) {
        id = rhs_id;
    }
    constexpr size_t get_id() const noexcept {
        return id;
    }
    constexpr bool valueless_by_exception() const noexcept {
        return (get_id() == variant_npos);
    }
    constexpr base& get_storage() & noexcept {
        return *this;
    }
    constexpr const base& get_storage() const & noexcept {
        return *this;
    }
    constexpr base&& get_storage() && noexcept {
        return std::move(*this);
    }
    constexpr const base&& get_storage() const && noexcept {
        return std::move(*this);
    }
};

template <typename ...Ts>
struct destroyable_storage<false, Ts...> : destroyable_storage<true, Ts...> {
    using destroyable_storage<true, Ts...>::destroyable_storage;
    using destroyable_storage<true, Ts...>::operator=;
    using destroyable_storage<true, Ts...>::id;
    using destroyable_storage<true, Ts...>::set_id;
    using destroyable_storage<true, Ts...>::get_id;
    using destroyable_storage<true, Ts...>::valueless_by_exception;
    using destroyable_storage<true, Ts...>::get_storage;
    using destroyable_storage<true, Ts...>::base;
    using destroyable_storage<true, Ts...>::reset;

    ~destroyable_storage() noexcept {
        if (!valueless_by_exception()) {
            reset(id);
        }
    }
};

template <typename ...Ts>
using destroyable_storage_t<Ts...> = destroyable_storage<std::conjunction_v<std::is_trivially_destructible<Ts>...>, Ts...>;

template <bool is_move_constructible, typename ...Ts>
struct moveable_storage : destroyable_storage_t<Ts...> {
	using movable_base = destroyable_storage_t<Ts...>;
	using movable_base::movable_base;

	moveable_storage(const moveable_storage& other) = default;
	moveable_storage(moveable_storage&& other) {
		movable_base::id = other.id;
		if (!movable_base::valueless_by_exception()) {
			movable_base::constructor(movable_base::id, std::move(other));
		}
	}
};

template <typename ...Ts>
struct moveable_storage<false, Ts...> : moveable_storage<true, Ts...> {
	using movable_base = moveable_storage<true, Ts...>;
	using movable_base::movable_base;

	moveable_storage(moveable_storage&& other) = delete;
};

template <typename ...Ts>
using moveable_storage_t<Ts...> = moveable_storage<std::conjunction_v<std::is_move_constructible<Ts>...>, Ts...>;

template <bool is_copy_constructible, typename ...Ts>
struct copyable_storage : moveable_storage_t<Ts...> {
	using copyable_base = moveable_storage_t<Ts...>;
	using copyable_base::copyable_base;

	copyable_storage(const copyable_storage& other) {
		copyable_base::id = other.id;
		if (!copyable_base::valueless_by_exception()) {
			copyable_base::constructor(copyable_base::id, other);
		}
	}

	moveable_storage(moveable_storage&& other) = default;
};

template <typename ...Ts>
struct copyable_storage<false, Ts...> : copyable_storage<true, Ts...> {
	using copyable_base = copyable_storage<true, Ts...>;
	using copyable_base::copyable_base;

	copyable_storage(const copyable_storage& other) = delete;
};

template <typename ...Ts>
using copyable_storage_t<Ts...> = copyable_storage<std::conjunction_v<std::is_copy_constructible<Ts>...>, Ts...>;

template <bool is_move_assignable, typename ...Ts>
struct move_assignable_storage : copyable_storage_t<Ts...> {
	using move_assignable_base = copyable_storage_t<Ts...>;
	using move_assignable_base::move_assignable_base;

	move_assignable_storage(const move_assignable_storage& other) = default;
	move_assignable_storage(move_assignable_storage&& other) = default;

	move_assignable_storage& operator=(const move_assignable_storage&) = default;

	move_assignable_storage& operator=(move_assignable_storage&& other) {
		if (move_assignable_base::valueless_by_exception() && other.valueless_by_exception()) {
			return *this;
		} else if(!(move_assignable_base::valueless_by_exception()) && other.valueless_by_exception()) {
			move_assignable_base::reset(move_assignable_base::get_id());
			move_assignable_base::id = variant_npos;
			return *this;
		} else if(move_assignable_base::get_id() == other.get_id()) {
			move_assignable_base::constructor(other.id, std::move(other));
			return *this;
		}
		try {
			move_assignable_base::reset(move_assignable_base::get_id());
			move_assignable_base::id = other.id;
			move_assignable_base::constructor(move_assignable_base::get_id(), std::move(other));
		} catch(...) {
			move_assignable_base::id = variant_npos;
		}
		return *this;
	}
};

template <typename ...Ts>
struct move_assignable_storage<false, Ts...> : move_assignable_storage<true, Ts...> {
	using move_assignable_base = move_assignable_storage<true, Ts...>;
	using move_assignable_base::move_assignable_base;

	move_assignable_storage& operator=(move_assignable_storage&&) = delete;

};

template <typename ...Ts>
using move_assignable_storage_t<Ts...> = move_assignable_storage<std::conjunction_v<std::is_move_assignable<Ts>...>, Ts...>;

template <bool is_copy_assignable, typename ...Ts>
struct copy_assignable_storage : move_assignable_storage_t<Ts...> {
	using copy_assignable_base = move_assignable_storage_t<Ts...>;
	using copy_assignable_base::copy_assignable_base;

	move_assignable_storage& operator=(const move_assignable_storage& other) {
		if (copy_assignable_base::valueless_by_exception() && other.valueless_by_exception()) {
			return *this;
		} else if(!(copy_assignable_base::valueless_by_exception()) && other.valueless_by_exception()) {
			copy_assignable_base::reset(copy_assignable_base::get_id());
			copy_assignable_base::id = variant_npos;
			return *this;
		} else if(copy_assignable_base::get_id() == other.get_id()) {
			copy_assignable_base::constructor(other.id, other);
			return *this;
		}
		try {
			copy_assignable_base::reset(copy_assignable_base::get_id());
			copy_assignable_base::id = other.id;
			copy_assignable_base::constructor(copy_assignable_base::get_id(), other);
		} catch(...) {
			copy_assignable_base::id = variant_npos;
			return (*this).operator=(copy_assignable_storage(other));
		}
		return *this;
	}
};

template <typename ...Ts>
struct copy_assignable_storage<false, Ts...> : copy_assignable_storage<true, Ts...> {
	using copy_assignable_base = copy_assignable_storage<true, Ts...>;
	using copy_assignable_base::copy_assignable_base;

	copy_assignable_storage& operator=(const copy_assignable_storage&) = delete;

};

template <typename ...Ts>
using copy_assignable_storage_t<Ts...> = copy_assignable_storage<std::conjunction_v<std::is_copy_assignable<Ts>...>, Ts...>;

#endif //VARIANT_STORAGE_H
