#include <iostream>
#include <regex>
#include <vector>
#include <iterator>

std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}

int main(){
    std::string database = " 22:12:43 "
                           " 12:02:23 "
                           " 01:10:01 "
                           " 7:08:56 "
                           " 33:54:12 "
                           " 29:54:12 "
                           " 1975.12.01 "
                           " 41.06.22 "
                           " 123 ";

    std::regex pattern_time(R"(([0-1][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9])"); // HH:MM:SS
    std::regex pattern_date(R"(\d+\.(0\d|1[0-2])\.([0-2]\d|3[0-1]))");       // YYYY:MM:DD, Y == 1 AC -> inf AC
    auto result = search(pattern_time, database);
    std::copy(std::begin(result), std::end(result),
              std::ostream_iterator<std::string>(std::cout, "\n"));
    result = search(pattern_date, database);
    std::copy(std::begin(result), std::end(result),
              std::ostream_iterator<std::string>(std::cout, "\n"));
    return 0;
}
