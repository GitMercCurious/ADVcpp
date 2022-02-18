#include <iostream>
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
    void get_value(){
        std::cout << std::chrono::duration_cast<T>(finish_point - start_point - delta).count()
                  << std::endl;
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

int main() {
    double result = 0.;
    {
        Timer<std::chrono::microseconds> t;

        t.start();
        for(auto i = 0u; i < 10000000u; i++) {
            result += std::sin(i) + std::cos(i);
        }
        t.finish();
        std::cout << "The whole time: ";
        t.get_value();
        std::cout << "First result is " << result << std::endl << std::endl;

        result = 0.;
        t.reset();
        t.pause();
        for(auto i = 0u; i < 10000000u; i++) {
            if(i%2 == 0) {
                result += std::sin(i) + std::cos(i);
            }else{
                t.play();
                result += std::sin(i) + std::cos(i);
                t.pause();
            }
        }
        t.play();
        t.finish();
        std::cout << "The time for only odd turns: ";
        t.get_value();
        std::cout << "Second result is " << result;
    }
    return 0;
}