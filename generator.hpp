//
// Created by illidansr on 30.03.2021.
//

#ifndef PLAY_WITH_COROUTINES__GENERATOR_HPP_
#define PLAY_WITH_COROUTINES__GENERATOR_HPP_

#include <coroutine>

template <typename T> struct generator {
    struct promise_type {
        T current_value;
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object() { return coro_handle::from_promise(*this); }
        auto initial_suspend() { return std::suspend_always(); }
        auto final_suspend() { return std::suspend_always(); }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
        auto yield_value(T value) {
            current_value = value;
            return std::suspend_always{};
        }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    bool move_next() {
        return handle_ ? (handle_.resume(), !handle_.done()) : false;
    }
    T current_value() const { return handle_.promise().current_value; }
    generator(coro_handle h) : handle_(h) {}
    generator(generator const &) = delete;
    generator(generator &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
    ~generator() {
        if (handle_)
            handle_.destroy();
    }

private:
    coro_handle handle_;
};

#endif //PLAY_WITH_COROUTINES__GENERATOR_HPP_
