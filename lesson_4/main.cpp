#include <iostream>
#include <iterator>
#include <fstream>
#include <experimental/filesystem>
#include <regex>
#include <chrono>
#include <random>
#include "json.hpp"

using nlohmann::json;

template<typename T>
T rand_uns(T min_, T max_) {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::mt19937 e(seed);
    std::uniform_int_distribution<T> d(min_, max_);
    return d(e);
}

class BankAcc{
public:
    std::string name,
                login,
                itn,
                password;
    int passport_series,
        passport_number;
    long long money;
    short pin;

    void save_data(){
        json data;
        data["name"] = this->name;
        data["login"] = this->login;
        data["password"] = this->password;
        data["itn"] = this->itn
        data["passport_series"] = this->passport_series;
        data["passport_number"] = this->passport_number;
        data["pin"] = this->pin;
        data["money"] = this->money;

        auto cpath = std::experimental::filesystem::current_path();
        std::experimental::filesystem::create_directory(cpath / "database");


        std::fstream file;
        file.open("database/" + name + ".json", std::ios::trunc | std::ios::out);
        file << data;

    }
public:
    BankAcc(){
        this->money = rand_uns<long long>(0, std::numeric_limits<short>::max());
    }
    ~BankAcc(){}
};

std::istream& operator>>(std::istream& in, BankAcc &acc){
    std::regex pattern_itn(R"(\d{12})"),
               pattern_series(R"(\d{4})"),
               pattern_number(R"(\d{6})"),
               pattern_pin(R"(\d{5})");

    std::cout << "Write down your name:" << std::endl;
    std::getline(in, acc.name);

    std::cout << "Create login:" << std::endl;
    std::getline(in, acc.login);

    std::cout << "Create password:" << std::endl;
    std::getline(in, acc.password);

    std::cout << "Write your Identifying Taxpayer Number:" << std::endl;
    while(true){
        in >> acc.itn;
        if(std::regex_match(acc.itn, pattern_itn)) break;
        else std::cout << "Error! False input format. Try again:" << std::endl;
    }

    std::cout << "Write your passport's series:" << std::endl;
    while(true){
        in >> acc.itn;
        if(std::regex_match(acc.itn, pattern_series)) break;
        else std::cout << "Error! False input format. Try again:" << std::endl;
    }

    std::cout << "Write your passport's number:" << std::endl;
    while(true){
        in >> acc.itn;
        if(std::regex_match(acc.itn, pattern_number)) break;
        else std::cout << "Error! False input format. Try again:" << std::endl;
    }

    std::cout << "Write your pin:" << std::endl;
    while(true){
        in >> acc.itn;
        if(std::regex_match(acc.itn, pattern_pin)) break;
        else std::cout << "Error! False input format. Try again:" << std::endl;
    }

    std::cout << "Thank you for your answers! Your current balance: " << acc.money << '$' << std::endl;

}

int main() {
    BankAcc person1;
    std::cin >> person1;

    return 0;
}
