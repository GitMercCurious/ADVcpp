#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <chrono>
#include <vector>
#include <ostream>
#include <algorithm>


std::ostream& operator<<(std::ostream &out, std::vector<int> container){

    out << "[ ";
    std::copy(container.begin(), container.end(), std::ostream_iterator<int>(std::cout, " "));
    out << ']' << std::endl;

    return out;
}


bool is_prime(int a){
    if(a == 2) return true;

    for(int i = 2; i * i <= a; ++i)
        if(a % i == 0) return false;

    return true;
}


int main() {
    unsigned seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
    std::mt19937 engine(seed);
    std::uniform_int_distribution uniform(0, 50);
    typedef std::istream_iterator<int> in_iter;
    typedef std::ostream_iterator<int> ou_iter;

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);
    std::cout << "1. P1 = " << v << std::endl;


    std::cout << "Type sequence of int-s splited by \"space\" ended by any letter: " << std::endl;
    std::copy(in_iter(std::cin), in_iter(), std::back_inserter(v));
    std::cout << "2. P1 = " << v << std::endl; // 5 6 8 6 5 4 4 2 3 5 6 8 5 5 4 6 q


    std::shuffle(v.begin(), v.end(), engine);
    std::cout << "3. P1 = " << v << std::endl;


    v.erase(std::unique(v.begin(), v.end()), v.end());
    std::cout << "4. P1 = " << v << std::endl;


    std::cout << "5. Amount of dds in P1 = " << std::count_if(v.begin(), v.end(), [](int el){return el % 2 == 1;})
              << std::endl << std::endl;


    std::cout << "6. Min of P1 = " << *std::min_element(v.begin(), v.end())
              << "; Max of P1 = " << *std::max_element(v.begin(), v.end())
              << std::endl << std::endl;


    auto iter = std::find_if(v.begin(), v.end(), is_prime);
    std::cout << "7. " << ((iter != v.end()) ? "The prime number is " + std::to_string(*iter) : "There is no prime")
              << std::endl << std::endl;


    std::transform(v.begin(), v.end(), v.begin(), [](int a){return a * a;});
    std::cout << "8. P1 = " << v << std::endl;


    std::vector<int> w(v.size());
    for(auto &el: w) el = uniform(engine);
    std::cout << "9. P2 = " << w << std::endl;


    std::cout << "10. Sum of P2 = " << std::accumulate(w.begin(), w.end(), 0)
              << std::endl << std::endl;


    std::fill_n(w.begin(), 4, 1);
    std::cout << "11. P2 = " << w << std::endl;


    std::vector<int> vw(v.size());
    std::generate(vw.begin(), vw.end(), [v, w, i = 0]() mutable {return v[i] - w[i++];});
    std::cout << "12. P3 = " << vw << std::endl;


    std::transform(vw.begin(), vw.end(), vw.begin(), [](int el){return (el > 0) ? el : 0;});
    std::cout << "13. P3 = " << vw << std::endl;


    vw.erase(std::remove(vw.begin(), vw.end(), 0), vw.end());
    std::cout << "14. P3 = " << vw << std::endl;


    std::reverse(vw.begin(), vw.end());
    std::cout << "15. P3 = " << vw << std::endl;


    std::nth_element(vw.begin(), vw.end() - 3, vw.end());
    std::cout << "16. 3 Max-s in P3 = [ ";
    std::copy(vw.end() - 3, vw.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << ']' << std::endl << std::endl;


    std::sort(v.begin(), v.end());
    std::sort(w.begin(), w.end());
    std::cout << "17. P1 = " << v << "    P2 = " << w << std::endl;


    std::vector<int> ww;
    std::merge(v.begin(), v.end(), w.begin(), w.end(), std::back_inserter(ww));
    std::cout << "18. P4 = " << ww << std::endl;


    auto tmp = std::equal_range(ww.begin(), ww.end(), 1);
    std::cout << "19. Equal_range for 1 in P4 = [ ";
    std::copy(tmp.first, tmp.second, std::ostream_iterator<int>(std::cout, " "));
    std::cout << ']' << std::endl << std::endl;


    std::cout << "20. P1 = " << v
              << "    P2 = " << w
              << "    P3 = " << vw
              << "    P4 = " << ww;


    return 0;
}
