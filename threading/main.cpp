#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <iostream>
#include <mutex>

using namespace std::chrono_literals;

void producer( std::queue<int>& q, std::condition_variable& cond, std::mutex& mut)
{
    // no data coming initially
    std::this_thread::sleep_for(3s);

    // then 5 messages at once
    for( int n = 0; n < 5; n++ )
    {
       // std::unique_lock ul(mut);
        q.push(n);

        //ul.unlock();
        cond.notify_all();
        std::this_thread::sleep_for(1ms);

        std::cout << "Th1: writing " << n << std::endl;
    }

    std::cout << "Th1: finished " << std::endl;
}

void processor( std::queue<int>& q, std::condition_variable& cond, std::mutex& mut, std::atomic_bool& run)
{
    while(run)
    {
        std::cout << "Th2: waiting... ";
        std::unique_lock ul(mut);
        cond.wait(ul);
        std::cout << "done" << std::endl;

        if( !q.empty() )
        {
            // processing takes 500 ms
            std::this_thread::sleep_for(1000ms);

            std::cout << "Th2: processing " << q.front() << std::endl;
            std::cout.flush();
            q.pop();
        }
        else
        {
            std::cout << std::endl;
        }
    }

}


int main()
{
    std::condition_variable cond;
    std::mutex mut;
    std::queue<int> q;
    std::atomic_bool doRun = true;
    std::thread prod( producer, std::ref(q), std::ref(cond), std::ref(mut) );
    std::thread proc( processor, std::ref(q), std::ref(cond), std::ref(mut), std::ref(doRun) );


    prod.join();

    while(true)
    {
        std::lock_guard lg(mut);

        if( q.empty() )
        {
            doRun = false;
            cond.notify_all();
            break;
        }

        cond.notify_all();

    }

    proc.join();
}