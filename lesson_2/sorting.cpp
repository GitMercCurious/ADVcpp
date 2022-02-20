#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>

#define SIZE 10000
#define TURNS 1000

template<typename T>
class Timer {
public:
    Timer() {};

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
        std::cout << (finish_point - start_point - delta).count() / (TURNS * 1000)
                  << " microseconds" << std::endl;
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


int main(){


    std::array<int, SIZE> array = {};
    std::vector<int> vector(SIZE, 0);
    std::deque<int> deque(SIZE, 0);
    std::list<int> list(SIZE, 0);
    std::forward_list<int> forward_list(SIZE, 0);

    Timer<std::chrono::microseconds> t;
    std::random_device r;
    std::mt19937 engine(r());
    std::uniform_int_distribution<int> uniform_dist(1, 100);

    t.start(); t.pause();
    for(int i = 0; i < TURNS; ++i){
        for(int j = 0; j < SIZE; ++j)
            array[j] = uniform_dist(engine);
        t.play();
        std::sort(array.begin(), array.end());
        t.pause();
    }
    t.play(); t.finish();

    std::cout << "Average time to sort STD::ARRAY of size 10000 int:            ";
    t.get_value();

    t.reset(); t.pause();
    for(int i = 0; i < TURNS; ++i){
        for(int j = 0; j < SIZE; ++j)
            vector[j] = uniform_dist(engine);
        t.play();
        std::sort(vector.begin(), vector.end());
        t.pause();
    }
    t.play(); t.finish();

    std::cout << "Average time to sort STD::VECTOR of size 10000 int:           ";
    t.get_value();

    t.reset(); t.pause();
    for(int i = 0; i < TURNS; ++i){
        for(int j = 0; j < SIZE; ++j)
            deque[j] = uniform_dist(engine);
        t.play();
        std::sort(deque.begin(), deque.end());
        t.pause();
    }
    t.play(); t.finish();

    std::cout << "Average time to sort STD::DEQUE of size 10000 int:            ";
    t.get_value();

    t.reset(); t.pause();
    for(int i = 0; i < TURNS; ++i){
        for(auto j = list.begin(); j != list.end(); ++j)
            *j = uniform_dist(engine);
        t.play();
        list.sort();
        t.pause();
    }
    t.play(); t.finish();

    std::cout << "Average time to sort STD::LIST of size 10000 int:             ";
    t.get_value();

    t.reset(); t.pause();
    for(int i = 0; i < TURNS; ++i){
        for(auto j = forward_list.begin(); j != forward_list.end(); ++j)
            *j = uniform_dist(engine);
        t.play();
        forward_list.sort();
        t.pause();
    }
    t.play(); t.finish();

    std::cout << "Average time to sort STD::FORWARD_LIST of size 10000 int:     ";
    t.get_value();

return 0;
}