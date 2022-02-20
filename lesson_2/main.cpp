#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <map>
#include <random>
#include <chrono>

// Class for the future upgrade
class Name{
public:
    std::string surname;
    std::string first_name, second_name;
    std::string parents_name;

    Name(std::string surname){
        this->surname = surname;
    }
};

std::ofstream& operator<<(std::ofstream& s, std::map<std::string, std::string> container){
    for(auto m: container)
        std::cout << m.first << ' ' << m.second << std::endl;

    return s;
}


class PhoneBook{
private:
    std::map<std::string, std::string> phones, names;

public:
    PhoneBook() {};

    // add new name and number to the phonebook
    void add_member(std::pair<std::string, std::string> data){
        this->names[data.first] = data.second;
        this->phones[data.second] = data.first;
    }

    void check(){
        std::cout << "phones" << std::endl;
        for(auto s: this->phones){
            std::cout << s.first << ' ' << s.second << std::endl;
        }
        std::cout << std::endl << "names" << std::endl;
        for(auto s: this->names){
            std::cout << s.first << ' ' << s.second << std::endl;
        }
    }

    // The whole list of names and numbers for typography
    void whole_list(){
        std::cout << "-------------------------------------------------------------" << std::endl;
        for(auto data: this->names){
            std::cout << data.first << std::setw(std::max(20 - (int)data.first.size(), 1)) << ' ' << data.second << std::endl;
        }
        std::cout << "-------------------------------------------------------------" << std::endl;
    }

    void random_member(){
        unsigned seed = static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count());
        std::mt19937 engine(seed);
        std::uniform_int_distribution<int> uniform_dist(0, (int) this->names.size() - 1);

        std::map<std::string, std::string> :: iterator iter = this->names.begin();
        std::advance(iter, uniform_dist(engine));

        std::cout << iter->first << std::setw(std::max(20 - (int)iter->first.size(), 1)) <<  ' ' << iter->second << std::endl;
    }

    void find_member(std::string name){
        std::map<std::string, std::string> :: iterator finder;
        finder = this->names.find(name);

        if(finder == this->names.end())
            std::cout << "There is no member with surname " << name << " in our phonebook." << std::endl;
        else
            std::cout << "The phone number of " << name << " is " << finder->second << std::endl;
    }

    ~PhoneBook() {};
};


int main() {
    PhoneBook phonebook;
    phonebook.add_member(std::make_pair("Mallaev", "+32395660114"));
    phonebook.add_member(std::make_pair("Mallaevs", "+78062309422"));
    phonebook.add_member(std::make_pair("Motygin", "+79802345252"));
    phonebook.add_member(std::make_pair("Dronova", "+79190342372"));
    phonebook.add_member(std::make_pair("Popov", "+9095824567234"));
    phonebook.add_member(std::make_pair("Schevtsov", "+4589145880"));
    phonebook.add_member(std::make_pair("Fakhrutdinov", "+91824619846"));

    std::cout << "The whole phonebook for typography" << std::endl;
    phonebook.whole_list();

    std::cout << std::endl;
    std::cout << "Random human for advertising agency" << std::endl;
    phonebook.random_member();

    std::cout << std::endl;
    std::cout << "Trial to find number by surname" << std::endl;
    phonebook.find_member("Nesterov");
    phonebook.find_member("Motygin");

    std::cout << std::endl;
    std::cout << "Add Nesterov" << std::endl;
    phonebook.add_member(std::make_pair("Nesterov", "+937429384701"));

    std::cout << std::endl;
    std::cout << "The whole phonebook for typography" << std::endl;
    phonebook.whole_list();

    std::cout << std::endl;
    std::cout << "Random human for advertising agency" << std::endl;
    phonebook.random_member();

    std::cout << std::endl;
    std::cout << "Trial to find number by surname" << std::endl;
    phonebook.find_member("Nesterov");
    phonebook.find_member("Motygin");

    return 0;
}
