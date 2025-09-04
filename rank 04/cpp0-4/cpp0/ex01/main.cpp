#include "PhoneBook.hpp"

int main(void)
{
    PhoneBook   ph1;
    std::string str;

    while(str != "EXIT")
    {
        std::cout<< "enter command> ";
        std::getline(std::cin, str);
        if (str == "ADD")
            ph1.add();
        else if (str == "SEARCH")
            ph1.search();
        if (std::cin.eof())
		{
			std::cout << std::endl;
			return (0);
		}
    }
}