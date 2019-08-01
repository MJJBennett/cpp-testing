#ifndef NULLABLE_MONADS_HPP
#define NULLABLE_MONADS_HPP

#include <optional>
#include <type_traits>

struct empty_t
{};

template<typename T>
struct Nullable 
{
    Nullable(T t) : data(std::move(t)) {}
    Nullable() : data{} {}

    template<typename F, typename = std::enable_if_t<!std::is_same<typename std::result_of<F(T)>::type, void>::value>>
    auto then(F f) -> Nullable<decltype(f(T{}))>
    { 
        if (data) return f(*data);
        return {};
    }

    template<typename F, typename = std::enable_if_t<std::is_same<typename std::result_of<F(T)>::type, void>::value>>
    auto then(F f) -> Nullable<empty_t>
    { 
        if (data) f(*data);
        return {};
    }

    auto operator=(T t) -> Nullable<T>&
    {
        data = t;
        return *this;
    }

    auto operator*() -> decltype(*std::optional<T>{})
    {
        return *data;
    }
    
    std::optional<T> data;
};

#endif // NULLABLE_MONADS_HPP
