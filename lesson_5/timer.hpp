#include <chrono>
#include <cmath>


template<typename T>
class Timer {
public:
    Timer() {}

    //start the timer
    void start(){
        start_point = std::chrono::steady_clock::now();
    }

    //pause the timer
    void pause(){
        pause_point = std::chrono::steady_clock::now();
    }

    //resume the timer
    void play(){
        delta += std::chrono::steady_clock::now() - pause_point;
    }

    //finish the timer
    void finish(){
        finish_point = std::chrono::steady_clock::now();
    }

    //get value of timer in T(unit of time)
    long long get_value(){
        return (finish_point - start_point - delta).count();

    }

    //restart the Timer
    void reset(){
        delta = std::chrono::nanoseconds::zero();
        start_point = std::chrono::steady_clock::now();
    }

    ~Timer() {}

private:
    std::chrono::steady_clock::time_point start_point, pause_point, finish_point;
    std::chrono::nanoseconds delta = std::chrono::nanoseconds::zero();
};
