//
// Created by daminovn on 9/26/18.
//

#ifndef VARIANT_H
#define VARIANT_H
#include <iostream>
#include <utility>
#include <typeinfo>
#include <type_traits>
#include <functional>
#include "storage.h"

template <typename T0, typename ... Ts> struct variant;

template<size_t I, typename T, bool ok = 1>
struct variant_alternative;

template<size_t I, typename T>
struct variant_alternative<I, const T>
{
    typedef std::add_const_t<typename variant_alternative<I, T>::type> type;
};

template<size_t I, typename T>
struct variant_alternative<I, volatile T>
{
    typedef std::add_volatile_t<typename variant_alternative<I, T>::type> type;
};

template<size_t I, typename T>
struct variant_alternative<I, const volatile T>
{
    typedef std::add_volatile_t<std::add_const_t<typename variant_alternative<I, T>::type>> type;
};

template<size_t I, typename T0, typename ... Ts>
struct variant_alternative<I, variant<T0, Ts...>, 1>
{
    typedef typename variant_alternative<I - 1, variant<Ts...>, (I <= sizeof...(Ts))>::type type;
};

template<typename T0, typename ... Ts>
struct variant_alternative<0, variant<T0, Ts...>>
{
    typedef T0 type;
};

struct empty;

template<size_t I, typename ... Ts>
struct variant_alternative<I, variant<Ts...>, 0>
{
    typedef empty type;
};


template <size_t I, typename T>
using variant_alternative_t = typename variant_alternative<I, T>::type;

struct monostate {};

constexpr bool operator<(monostate, monostate) noexcept { return false; }
constexpr bool operator>(monostate, monostate) noexcept { return false; }
constexpr bool operator<=(monostate, monostate) noexcept { return true; }
constexpr bool operator>=(monostate, monostate) noexcept { return true; }
constexpr bool operator==(monostate, monostate) noexcept { return true; }
constexpr bool operator!=(monostate, monostate) noexcept { return false; }

template <typename T>
struct variant_size;

template <typename ...Ts>
struct variant_size<variant<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <typename T>
struct variant_size<const T> : variant_size<T> {};

template <typename T>
struct variant_size<volatile T> : variant_size<T> {};

template <typename T>
struct variant_size<const volatile T> : variant_size<T> {};

template <typename T>
inline constexpr size_t variant_size_v = variant_size<T>::value

template <typename U, typename ...Ts>
struct count_type {};

template <typename U, typename V, typename ...Ts>
struct count_type<U, V, Ts...> {
	static constexpr size_t value = std::is_same<U, V>::value + count_type<U, Ts...>::value;
};

template <typename U>
struct count_type<U> {
	static constexpr size_t value = 0;
};
// MAYBE FOR <U, T> needed but I think not (????)

template <typename T, typename ...Ts>
inline constexpr bool is_unique_v = count_type<T, Ts...>::value == 1;

template <typename T>
struct single_type {
	static T f(T);
};

template <typename T, typename ...Ts>
struct choose_type : single_type<T>, choose_type<Ts...> {
	using single_type<T>::f;
	using choose_type<Ts...>::f;
};

template <typename T>
struct choose_type<T> : single_type<T> {
	using single_type<T>::f;
};

template <typename U, typename T, typename ...Ts>
using choose_type_t = decltype(choose_type<T, Ts...>::f(declval<U>()));

template <typename U, typename... Ts>
struct get_type_id {};

template <typename U, typename T, typename... Ts>
struct get_type_id<U, T, Ts...> {
    static constexpr size_t value = get_type_id<U, Ts...>::value + 1;
};

template <typename U, typename ...Ts>
struct get_type_id<U, U,Ts...> {
    static constexpr size_t value = 0;
};

template <typename U>
struct get_type_id<U> {
    static constexpr size_t value = 0;
};
class bad_variant_access : public std::exception {};

template <size_t I, typename ...Ts>
constexpr decltype(auto) get(variant<Ts...>& a) {
	static_assert(I < sizeof...(Ts), "Type index out of range");
    if (a.get_id() != I){
        throw bad_variant_access();
    }
    return get_storage_value(build_const<I>{}, a.get_storage());
}

template <size_t I, typename ...Ts>
constexpr decltype(auto) get(const variant<Ts...>& a) {
	static_assert(I < sizeof...(Ts), "Type index out of range");
    if (a.get_id() != I){
        throw bad_variant_access();
    }
    return get_storage_value(build_const<I>{}, a.get_storage());
}

template <size_t I, typename ...Ts>
constexpr decltype(auto) get(variant<Ts...>&& a) {
	static_assert(I < sizeof...(Ts), "Type index out of range");
    if (a.get_id() != I){
        throw bad_variant_access();
    }
    return get_storage_value(build_const<I>{}, std::move(a).get_storage());
}

template <size_t I, typename ...Ts>
constexpr decltype(auto) get(const variant<Ts...>&& a) {
	static_assert(I < sizeof...(Ts), "Type index out of range");
    if (a.get_id() != I){
        throw bad_variant_access();
    }
    return get_storage_value(build_const<I>{}, std::move(a).get_storage());
}

template <typename T, typename ...Ts, size_t I = get_type_id<T, Ts...>::value, typename = std::enable_if_t<is_unique_v<T, Ts...>>>
constexpr decltype(auto) get(variant<Ts...>& a) {
	return get<I>(a);
}

template <typename T, typename ...Ts, size_t I = get_type_id<T, Ts...>::value, typename = std::enable_if_t<is_unique_v<T, Ts...>>>
constexpr decltype(auto) get(const variant<Ts...>& a) {
    return get<I>(a);
}

template <typename T, typename ...Ts, size_t I = get_type_id<T, Ts...>::value, typename = std::enable_if_t<is_unique_v<T, Ts...>>>
constexpr decltype(auto) get(variant<Ts...>&& a) {
    return get<I>(std::move(a));
}

template <typename T, typename ...Ts, size_t I = get_type_id<T, Ts...>::value, typename = std::enable_if_t<is_unique_v<T, Ts...>>>
constexpr decltype(auto) get(const variant<Ts...>&& a) {
    return get<I>(std::move(a));
}

template <typename T0, typename ...Ts>
struct variant : copy_assignable_storage_t<T0, Ts...> {
private:
	using variant_data = copy_assignable_storage_t<T0, Ts...>;
	using variant_data::valueless_by_exception_stor;
	using variant_data::set_id;
	using variant_data::get_id;
	using variant_data::reset;
	using variant_data::constructor;
	using variant_data::implace_constructor;

	template <size_t I>
	using get_type_t = variant_alternative_t<I, variant>;

	static inline constexpr size_t invalid_type_id() {
        return variant_npos;
    }
public:
	template<typename = std::enable_if_t<std::is_default_constructible_v<T0>>>
    		constexpr variant() noexcept(std::is_nothrow_default_constructible_v<T0>) :variant_data(build_const<0>{}) {}

    variant(const variant&) = default;
	variant(variant&&) = default;

    template <typename T, typename varT = choose_type_t<T, T0, Ts...>,
              typename = std::enable_if_t<
                  !std::is_same_v<std::decay_t<T>, variant> &&
                  std::is_constructible_v<varT, T>  &&
                  is_unique_v<varT, T0, Ts...> >,
              size_t I = get_type_id<varT, T0, Ts...>::value
              > constexpr variant(T&& t) noexcept(std::is_nothrow_constructible_v<varT, T>) : data(build_const<I>{}, std::forward<T>(t)) {}

    template <typename T, typename ...Args,
              size_t I = get_type_id<T, T0, Ts...>::value,
              typename = std::enable_if_t<
                  (I != invalid_type_id()) &&
                  std::is_constructible_v<T, Args...> &&
                  is_unique_v<T, T0, Ts...> >>
    constexpr variant(std::in_place_type_t<T> t, Args&&... args) : data(build_const<I>{}, std::forward<Args>(args)...) {}

    template< std::size_t I, class... Args, typename T = get_type_t<I>
    			typename = std::enable_if_t<
                  (I < sizeof...(Ts) + 1) &&
                  std::is_constructible_v<T, Args...> > >
	constexpr explicit variant(std::in_place_index_t<I>, Args&&... args) : data(build_const<I>{}, std::forward<Args>(args)...) {}

	variant& operator=(variant const&) = default;
	variant& operator=(variant&&) = default;


	template <typename T, typename... Args, size_t I = get_type_id<T, T0, Ts...>::value,
		typename = enable_if_t<std::is_constructible_v<T, Args...> && is_unique_v<T, T0, Ts...>>>
	T& emplace(Args&&... args) {
		reset(get_id());
		implace_constructor(get_id(), std::forward<Args>(args)...);
		return get_storage_value(build_const<I>{}, *this);
	}
	template <size_t I, typename ...Args, typename T = get_type_t<I>,
              typename = std::enable_if_t<std::is_constructible_v<T, Args...>>>
    variant_alternative_t<I, variant>& emplace(Args&&... args){
        return emplace<T>(std::forward<Args>(args)...);
    }

	template <typename T, typename varT = choose_type_t<T, T0, Ts...>,
				typename = enable_if_t<std::is_constructible_v<T, varT> && is_unique_v<varT, T0, Ts...> && std::is_assignable<varT&, T>>, 
					size_t I = get_type_id<varT, T0, Ts...>::value>
	variant& operator=(T&& t) noexcept {
		if (I == get_id()) {
			get<I>(*this) = std::forward<T>(t);
		} else {
			if constexpr(std::is_nothrow_constructible_v<varT, T> || !std::is_nothrow_move_constructible_v<varT>) {
				this->emplace<I>(std::forward<T>(t));
			} else {
				return (*this).operator=(variant(std::forward<T>(t)));
			}
		}
		return *this;
	}
	constexpr std::size_t index() const noexcept{
        return std::min(get_id(), invalid_type_id());
    }
    constexpr bool valueless_by_exception() const noexcept {
    	return valueless_by_exception_stor();
    }

    void swap(variant& rhs) noexcept(std::conjunction_v<std::is_nothrow_move_constructible<Ts>..., std::is_nothrow_move_constructible<T0>,
                                     std::is_nothrow_swappable<Ts>..., std::is_nothrow_swappable<T0>>) {
    	if (valueless_by_exception() && rhs.valueless_by_exception()) {
    		return;
    	} else if (index() == rhs.index()) {
    		swap_value(index(), *this, rhs);
    		return;
    	}
    	variant tmp(std::move(rhs));
    	if(!rhs.valueless_by_exception()){
            rhs.reset(rhs.index());
        }
        rhs.set_id(index());
        if(!valueless_by_exception()){
            rhs.constructor(index(), std::move(*this));
        }

        if(valueless_by_exception()){
            reset(index());
        }
        set_id(buf.index());
        if(!buf.valueless_by_exception()){
            constructor(index(), std::move(buf));
        }
    }
};

template <typename ...Ts, std::enable_if_t<std::conjunction_v<std::is_move_constructible<Ts>...>
					&& std::conjunction_v<std::is_move_constructible<Ts>...>>>
void swap(variant<Ts...>& a, variant<Ts...>& b) noexcept(noexcept(a.swap(b))) {
	a.swap(b);
}
template <typename T, typename ...Types>
constexpr bool holds_alternative(const variant<Types...>& a) noexcept {
    return !a.valueless_by_exception() && a.index() == get_type_id<T, Types...>::value;
}

template <size_t I, class... Types>
constexpr decltype(auto) get_if(std::variant<Types...>* pv) noexcept {
	if (I >= sizeof...(Types)) {
		throw bad_variant_access();
	}
	if (pv != nullptr && pv->index() == I) {
		return &get<I>(*pv);
	}
	return nullptr;
}

template <size_t I, class... Types>
constexpr decltype(auto) get_if(const std::variant<Types...>* pv) noexcept {
	if (I >= sizeof...(Types)) {
		throw bad_variant_access();
	}
	if (pv != nullptr && pv->index() == I) {
		return &get<I>(*pv);
	}
	return nullptr;
}

template <typename T, class... Types, typename = enable_if_t<is_unique_v<T, Types...>>>
constexpr decltype(auto) get_if(std::variant<Types...>* pv) noexcept {
	constexpr size_t I = get_type_id<T, Types...>;
	return get_if<I>(pv);
}

template <typename T, class... Types, typename = enable_if_t<is_unique_v<T, Types...>>>
constexpr decltype(auto) get_if(const std::variant<Types...>* pv) noexcept {
	constexpr size_t I = get_type_id<T, Types...>;
	return get_if<I>(pv);
}

#endif //VARIANT_H