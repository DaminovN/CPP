#pragma once
#include <bits/stdc++.h>

template<typename T, T ... values>
struct integer_sequence {};

template<typename T, typename Seq, T t>
struct append;

template<typename T, T ... values, T arg>
struct append<T, integer_sequence<T, values...>, arg>
{
	typedef integer_sequence<T, values..., arg> type;
};

template<typename T, T N, typename Q = void>
struct make_integer_sequence
{
	typedef typename append<T, typename make_integer_sequence<T, N - 1>::type, N - 1>::type type;
};

template<typename T, T N>
struct make_integer_sequence<T, N, typename std::enable_if<N == 0>::type>
{
	typedef integer_sequence<T> type;
};


template<int N>
struct placeholder
{};

constexpr placeholder<1> _1;
constexpr placeholder<2> _2;
constexpr placeholder<3> _3;

template<typename F, typename ... As>
struct bind_t;

template<int N>
using int_sequence = typename make_integer_sequence<int, N>::type;

template<typename S1, typename S2>
struct combine;

template<int ... seq1, int ... seq2>
struct combine<integer_sequence<int, seq1...>, integer_sequence<int, seq2...>>
{
	typedef integer_sequence<int, seq1..., seq2...> value;
};

template<typename ... TAIL>
struct id_list;

template<typename T>
struct id 
{
	typedef int_sequence<0> value;
};

template<int N>
struct id<placeholder<N>>
{
	typedef integer_sequence<int, N> value;
};

template <typename F, typename ... As>
struct id<bind_t<F, As...>>
{
	typedef typename id_list<std::decay_t<As>...>::value value;
};

template<typename T, typename ... TAIL>
struct id_list<T, TAIL...>
{
	typedef typename combine<typename id<T>::value, typename id_list<TAIL...>::value>::value value;
};

template<>
struct id_list<>
{
	typedef int_sequence<0> value;
};


template<typename ... T>
using id_list_t = typename id_list<std::decay_t<T>...>::value; 

template<int X, typename Seq>
struct get_nmb;

template<int X, int N, int ... seq>
struct get_nmb<X, integer_sequence<int, N, seq...>>
{
	static constexpr int cnt = static_cast<int>(X == N) + get_nmb<X, integer_sequence<int, seq...>>::cnt;
};

template<int X>
struct get_nmb<X, integer_sequence<int>>
{
	static constexpr int cnt = 0;
};

template<int X, typename Seq>
constexpr bool unique = (get_nmb<X, Seq>::cnt <= 1);

template<typename T, bool f>
struct get_type
{
	typedef T& type;
};

template<typename T>
struct get_type<T, 1>
{
	typedef T&& type;
};

template<typename T, bool f>
using get_type_t = typename get_type<T, f>::type;

template<typename T>
struct cleaner
{
	typedef T type;
};

template<int N>
struct cleaner<const placeholder<N>&>
{
	typedef placeholder<N> type;
};

template<int N>
struct cleaner<placeholder<N>&>
{
	typedef placeholder<N> type;
};

template<int N>
struct cleaner<placeholder<N>&&>
{
	typedef placeholder<N> type;
};

template<typename T>
using cleaner_t = typename cleaner<T>::type;

template<typename T>
struct bind_cleaner
{
	typedef T value;
};

template<typename F, typename ... As>
struct bind_cleaner<bind_t<F, As...>&&>
{
	typedef bind_t<F, As...> value;
};

template<typename F, typename ... As>
struct bind_cleaner<bind_t<F, As...>&>
{
	typedef bind_t<F, As...> value;
};

template<typename F, typename ... As>
struct bind_cleaner<const bind_t<F, As...>&>
{
	typedef bind_t<F, As...> value;
};

template<typename T>
using bind_cleaner_t = typename bind_cleaner<T>::value;

template<typename A>
struct G
{
	template<typename AA>
	G(AA&& a) : a(std::forward<AA>(a)) {};

	template<typename ... Bs>
	A operator()(Bs&& ...)
	{
		return static_cast<A>(a);
	}
private:
	std::remove_reference_t<A> a;
};

template<>
struct G<placeholder<1>>
{
	G(placeholder<1>) {}

	template<typename B1, typename ... Bs>
	decltype(auto) operator()(B1&& b1, Bs&& ...)
	{
		return std::forward<B1>(b1);
	}
};

template<int N>
struct G<placeholder<N>>
{
	G(placeholder<N>) {}

	template<typename B1, typename ... Bs>
	decltype(auto) operator()(B1&& b1, Bs&& ... bs)
	{
		G<placeholder<N - 1>> next((placeholder<N - 1>()));
		return next(std::forward<Bs>(bs)...);
	}
};

template<typename F, typename ... As>
struct G<bind_t<F, As...>>
{

	G(const bind_t<F, As...>& func) : func(func) {}

	G(bind_t<F, As...>&& func) : func(std::move(func)) {}

	template<typename ... Bs>
	decltype(auto) operator()(Bs&& ... bs)
	{
		return func(std::forward<Bs>(bs)...);
	}
private:
	bind_t<F, As...> func;
};

template<typename F, typename ... As>
struct bind_t
{
	template<typename F1, typename ... As1>
	bind_t(F1&& f, As1&& ... as) : f(std::forward<F1>(f)), g(std::forward<As1>(as)...) {};

	template<typename ... Bs>
	decltype(auto) operator()(Bs&& ... bs)
	{
		return call(int_sequence<sizeof...(As)>(), int_sequence<sizeof...(Bs)>(), id_list_t<As...>(), std::forward<Bs>(bs)...);
	}
private:
	template <int ... ks, int ... ind, int ... pls, typename ... Bs>
	decltype(auto) call(integer_sequence<int, ks...> a, integer_sequence<int, ind...> b, integer_sequence<int, pls...> c, Bs&& ... bs)
	{
		return f(std::get<ks>(g)(static_cast<get_type_t<Bs, unique<ind + 1, decltype(c)>>>(bs)...)...);
	}
	F f;
	std::tuple<G<bind_cleaner_t<As>>...> g;
};

template <typename F, typename ... As>
decltype(auto) bind(F&& f, As&& ... as)
{
    return bind_t<F, cleaner_t<std::decay_t<As>&>...>(std::forward<F>(f), std::forward<As>(as)...);
}


