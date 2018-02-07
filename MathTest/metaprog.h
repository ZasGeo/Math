#ifndef _METAPROG_
#define _METAPROG_
/*
parametr pack comparison
*/
template<bool...> struct bool_pack;
template<bool... bs>
using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

template<class R, class... Ts>
using are_all_same = all_true<std::is_same<Ts, R>::value...>;
/*
----------------------------------------------------
*/

/*
parametr pack count
---------------------------------------------------
*/
template<typename... Args> struct count;

template<>
struct count<> {
	static const int value = 0;
};

template<typename T, typename... Args>
struct count<T, Args...> {
	static const int value = 1 + count<Args...>::value;
};
/*
----------------------------------------------------
*/

#endif