#include <iostream>
#include <typeinfo>
#include <map>
#include <memory>

#ifndef BOX_H
#define BOX_H
//https://www.foonathan.net/2022/05/recursive-variant-box/
template <typename T>
class box
{
    // Wrapper over unique_ptr.
    std::unique_ptr<T> _impl;

public:
    // Automatic construction from a `T`, not a `T*`.
    box(T &&obj) : _impl(new T(std::move(obj))) {}
    box(const T &obj) : _impl(new T(obj)) {}

    // Copy constructor copies `T`.
    box(const box &other) : box(*other._impl) {}
    box &operator=(const box &other)
    {
        *_impl = *other._impl;
        return *this;
    }

    // unique_ptr destroys `T` for us.
    ~box() = default;

    // Access propagates constness.
    T &operator*() { return *_impl; }
    const T &operator*() const { return *_impl; }

    T *operator->() { return _impl.get(); }
    const T *operator->() const { return _impl.get(); }
};
#endif