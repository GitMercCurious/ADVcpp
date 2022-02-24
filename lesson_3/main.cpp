#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <chrono>
#include <vector>
#include <ostream>


std::ostream& operator<<(std::ostream &out, std::vector<int> container){

    out << "[ ";
    for(auto el: container)
        out << el << ' ';
    out << ']' << std::endl;

    return out;
}


int main() {
    unsigned seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 engine(seed);
    std::uniform_int_distribution uniform(1, 4);

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);
    std::cout << v;

    int rand = uniform(engine);
    for(int i = 0; i < rand; ++i) {
        int a;
        std::cin >> a;
        std::fill_n(std::back_inserter(v), 1, a);
    }
    std::cout << v;

    return 0;
}
