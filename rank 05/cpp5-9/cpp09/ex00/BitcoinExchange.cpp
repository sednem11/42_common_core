#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(): check(0)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    std::cout << "BitcoinExchange copied" << std::endl;
    *this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
    std::cout << "assignment operator called for BitcoinExchange" << std::endl;
    if (this != &copy)
        *this = copy;
    return(*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::Add_Date(std::string Data)
{
        std::string line = Data.substr(0, Data.find_first_of(','));
        std::string line2 = Data.substr(Data.find_first_of(',') + 1);
        float value = atof(line2.c_str());
        Map[line] = value;
}

void BitcoinExchange::check_price(std::string Data)
{
    if (Data.find('|') == std::string::npos || Data.find_first_of(' ') == std::string::npos || Data.find_first_of(' ') == Data.find_last_of(' '))
    {
        std::cerr << "Error: bad input => " << Data << std::endl;
        return ;
    }
    if (Data.find_first_of(' ') != std::string::npos)
    {
        std::string line = Data.substr(0, Data.find_first_of(' '));
        std::string line2 = Data.substr(Data.find_last_of(' ') + 1);
        std::string line3 = line;
        float value = atof(line2.c_str());
        if (value < 0)
        {
            std::cerr << "Error: not a positive value" << std::endl;
            return ;
        }
        if (value > 1000)
        {
            std::cerr << "Error: to large a number" << std::endl;
            return ;
        }
        for (int i = 0; i < 3; i++)
        {
            std::map<std::string, float>::iterator it = Map.find(line);
            if(it != Map.end())
            {
                std::cout << line3 << " => " << value << " => " << (value * it->second) << std::endl;
                return ;
            }
            line = change_Date(line);
        }
    }
    else
        std::cerr << "Error: bad input => " << Data << std::endl;
    set_check(1);
}

std::string BitcoinExchange::formatTwoDigits(int num)
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << num;
    return std::string(oss.str());
}

std::string BitcoinExchange::change_Date(std::string line)
{
    std::string line1 = line.substr(line.find_last_of('-') + 1);
    std::string line2 = line.substr(line.find_first_of('-') + 1, line.find_last_of('-'));
    std::string line3 = line.substr(0, line.find_first_of('-'));
    int Day = static_cast<int>(atof(line1.c_str()));
    int Month = static_cast<int>(atof(line2.c_str()));
    int year = static_cast<int>(atof(line3.c_str()));
    Day--;
    if (Day == 0)
    {
        Month--;
        if(Month == 0)
        {
            year--;
            Month = 12;
        }
        if (Month == 2)
            Day = 28;
        else if (Month % 2 == 0 && Month < 8)
            Day = 30;
        else if (Month % 2 == 1 && Month >= 8)
            Day = 30;
        else
            Day = 31;
    }
    std::string line4 = formatTwoDigits(year) + '-' + formatTwoDigits(Month) + '-' + formatTwoDigits(Day);
    return(line4);
}

bool BitcoinExchange::get_check()
{
    return check;
}

void BitcoinExchange::set_check(bool num)
{
    check = num;
}

std::map<std::string, float> BitcoinExchange::get_map()
{
    return Map;
}