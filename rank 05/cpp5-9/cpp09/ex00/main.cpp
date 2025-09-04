#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    if(argc != 2){
        std::cerr << "Error: not right amount of agruments" << std::endl;
        return(1);
    }
    std::ifstream file("data.csv");
    if (!file){
        std::cerr << "Error: could not open file" << std::endl;
        return(1);
    }
    std::ifstream file2(argv[1]);
    if (!file2){
        std::cerr << "Error: could not open file" << std::endl;
        return(1);
    }
    std::string line;
    std::string line2;
    BitcoinExchange btc = BitcoinExchange();
    while (std::getline(file, line))
    {
        if(line != "date,exchange_rate")
            btc.Add_Date(line);
    }
    while(std::getline(file2, line2))
    {
        btc.check_price(line2);
        if (btc.get_check() == 1)
        {
            std::cerr << "Error: bad input => " << line2 << std::endl;
            btc.set_check(0);
        }
    }
    file.close();
    file2.close();
}
