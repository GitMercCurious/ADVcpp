#include <thread>
#include <numeric>
#include <iostream>
#include <fstream>
#include <vector>
#include "timer.hpp"


template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T &result) {
    result = std::accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, unsigned threads_amount) {
    // 1. Проверили длину
    auto length = distance(first, last);
    if (length < 4 * threads_amount) {
        return std::accumulate(first, last, init);
    }

    // 2. Длина достаточна, распараллеливаем
    //    Вычислили длину для одного потока
    auto length_per_thread = (length + threads_amount - 1) / threads_amount;

    // Векторы с потоками и результатами
    std::vector<std::thread> threads;
    std::vector<T> results(threads_amount - 1);

    // 3. Распределяем данные (концепция полуинтервалов!)
    auto beginning = first;
    auto ending = next(first, length_per_thread);
    for (int i = 0; i < threads_amount - 1; i++) {
        beginning = min(next(first, i * length_per_thread), last);
        ending = min(next(first, (i + 1) * length_per_thread), last);
        // 4. Запускаем исполнителей
        threads.push_back(std::thread(accumulate_block<Iterator, T>, beginning, ending, 0, std::ref(results[i])));
    }

    // Остаток данных -- в родительском потоке
    auto main_result = std::accumulate(min(next(first, (threads_amount - 1) * length_per_thread), last), last, init);

    // std::mem_fun_ref -- для оборачивания join().
    for_each(begin(threads),end(threads),mem_fun_ref(&std::thread::join));

    // 5. Собираем результаты
    return std::accumulate(begin(results), end(results), main_result);
}

int main() {
    std::vector<long long> test_sequence(1e8);
    long long result;
    Timer<std::chrono::nanoseconds> t;
    std::fstream data;
    data.open("../data.txt");

    for(int i = 1; i <= 30; ++i) {
        t.reset(); t.pause();
        for(int j = 0; j < 10; ++j){
            std::iota(test_sequence.begin(), test_sequence.end(), 0ll);
            t.play();
            result = parallel_accumulate(begin(test_sequence), end(test_sequence), 0ll, i);
            t.pause();
        }
        t.play(); t.finish();
        data << t.get_value()/10 << '\n';
    }

    data.close();
}