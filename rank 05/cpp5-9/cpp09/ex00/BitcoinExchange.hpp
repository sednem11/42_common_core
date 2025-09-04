#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <map>


class BitcoinExchange
{
    private:
        std::map<std::string, float> Map;
        bool check;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &copy);

        BitcoinExchange &operator=(const BitcoinExchange &copy);
        ~BitcoinExchange();
        void    Add_Date(std::string Data);  
        void    check_price(std::string Data);
        std::string formatTwoDigits(int num);
        std::string    change_Date(std::string line);
        bool    get_check();

        void    set_check(bool num);
        std::map<std::string, float> get_map();
};
