#include <iostream>
#include <coroutine>
#include <concepts>

//** Coroutines **/
struct ReturnObject
{
    struct promise_type
    {
        ReturnObject get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() noexcept {}
    };
};

struct Awaiterr
{
    std::coroutine_handle<> *hp_;
    constexpr bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> h) { *hp_ = h; }
    constexpr void await_resume() const noexcept {}
};

ReturnObject counter(std::coroutine_handle<> *continuation_out)
{
    Awaiterr a{continuation_out};
    for (unsigned i = 0;; ++i) // Does not end
    {
        co_await a;
        std::cout << "counter: " << i << std::endl;
        co_await a;
        std::cout << "Additional wait" << std::endl;

    }
}

//******


int main()
{
    {
        // three-way comparison
        auto k = 3;
        auto q = 2;

        auto cmpRes = k <=> q;
        if( cmpRes > 0)
            std::cout << "k larger q" << std::endl;
        else if( cmpRes < 0 )
            std::cout << "k smaller q" << std::endl;
        else
            std::cout << "k and q are equal" << std::endl;
    }

    {
        // coroutines
        std::coroutine_handle<> h;
        counter(&h);
        for (int i = 0; i < 6; ++i)
        {
            std::cout << "In main1 function: " << i << std::endl;
            h();
        }
        h.destroy();
    }

    return 0;
}
