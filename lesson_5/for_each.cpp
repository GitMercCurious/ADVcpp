#include <future>
#include <iostream>
#include <numeric>
#include <vector>


template<typename Iter, typename Func>
void for_each_p(Iter beg, Iter end, Func f){
    std:size_t distance = std::distance(beg, end);

    std::size_t max_distance = 8;

    if(distance <= max_distance)
        for_each(beg, end, f);
    else{
        Iter mid = beg;
        std::advance(mid, distance / 2);

        std::future<void> half_res = std::async(for_each_p<Iter, Func>, beg, mid, f);

        for_each_p(mid, end, f);

        half_res.get();
    }
}

int main() {
    std::vector<int> test_seq(1e2);
    std::iota(test_seq.begin(), test_seq.end(), 0);

    for(auto p: test_seq)
        std::cout << p << " ";
    for_each_p(test_seq.begin(), test_seq.end(), [](int &x){x *= x * x;});
    std::cout << std::endl;
    for(auto p: test_seq)
        std::cout << p << " ";

    return 0;
}
