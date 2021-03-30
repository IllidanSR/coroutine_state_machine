//
// Created by illidansr on 30.03.2021.
//

#ifndef PLAY_WITH_COROUTINES__COROUTINE_RESUMABLE_HPP_
#define PLAY_WITH_COROUTINES__COROUTINE_RESUMABLE_HPP_

#include <cassert>
#include <coroutine>

struct resumable_no_wait {
    struct promise_type {
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object() { return coro_handle::from_promise(*this); }
        auto initial_suspend() { return std::suspend_never(); }
        auto final_suspend() { return std::suspend_always(); }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable_no_wait(coro_handle handle) : handle_(handle) { assert(handle); }
    resumable_no_wait(resumable_no_wait &) = delete;
    resumable_no_wait(resumable_no_wait &&rhs) noexcept : handle_(rhs.handle_) {
        rhs.handle_ = nullptr;
    }
    bool resume() {
        if (!handle_.done())
            handle_.resume();
        return !handle_.done();
    }
    ~resumable_no_wait() {
        if (handle_)
            handle_.destroy();
    }

private:
    coro_handle handle_;
};

struct resumable_noinc {
    struct promise_type {
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object() { return coro_handle::from_promise(*this); }
        auto initial_suspend() { return std::suspend_always(); }
        auto final_suspend() { return std::suspend_always(); }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable_noinc(coro_handle handle) : handle_(handle) { assert(handle); }
    resumable_noinc(resumable_noinc &) = delete;
    resumable_noinc(resumable_noinc &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
    bool resume() {
        if (!handle_.done())
            handle_.resume();
        return !handle_.done();
    }
    ~resumable_noinc() {
        if (handle_)
            handle_.destroy();
    }
    coro_handle handle() {
        coro_handle h = handle_;
        handle_ = nullptr;
        return h;
    }

private:
    coro_handle handle_;
};

#endif //PLAY_WITH_COROUTINES__COROUTINE_RESUMABLE_HPP_
