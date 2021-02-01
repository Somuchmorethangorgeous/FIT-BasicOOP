#ifndef LAB4_TUPLE_PRINT_H
#define LAB4_TUPLE_PRINT_H
#include <ostream>


template<size_t n, class... Args>
struct Print{
    static void f(std::ostream& os, const std::tuple<Args...> &t){
        Print<n-1, Args...>::f(os,t);
        os << std::get<n>(t) << ",";
    }
};

template<class... Args>
struct Print<0, Args...>{
    static void f(std::ostream& os, const std::tuple<Args...> &t){
        os << std::get<0>(t) << ",";
    }
};


template <class Ch, class Tr, class... Args>
auto& operator<<(std::basic_ostream<Ch, Tr> &os, const std::tuple<Args...> &t){
    Print<std::tuple_size<std::tuple<Args...>>::value - 2, Args...>::f(os, t);
    os << std::get<sizeof...(Args) - 1>(t);
    return os;
}

#endif //LAB4_TUPLE_PRINT_H
