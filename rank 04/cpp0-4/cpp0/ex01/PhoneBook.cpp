#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
    this->index = 0;

    std::cout << "PhoneBook iniciated pls enter a command" << std::endl;
}

PhoneBook::~PhoneBook(void)
{
    std::cout << "PhoneBook deleted" << std::endl;
}

void    PhoneBook::add(void)
{
    std::string str;

    str = "";
    if (this->index > 7)
        std::cout << "replacing oldest contact" << std::endl;
    while(!std::cin.eof() && str == "")
    {
        std::cout << "enter first name" << std::endl;
        if(std::getline(std::cin, str) && str != "")
            this->contacts[this->index % 8].set_name(str);
    }
    str = "";
    while(!std::cin.eof() && str == "")
    {
        std::cout << "enter last name" << std::endl;
        if(std::getline(std::cin, str) && str != "")
            this->contacts[this->index % 8].set_lname(str);
    }
    str = "";
    while(!std::cin.eof() && str == "")
    {
        std::cout << "enter nickname" << std::endl;
        if(std::getline(std::cin, str) && str != "")
            this->contacts[this->index % 8].set_nickname(str);
    }
    str = "";
    while(!std::cin.eof() && str == "")
    {
        std::cout << "enter number" << std::endl;
        if(std::getline(std::cin, str) && str != "")
            this->contacts[this->index % 8].set_number(str);
    }
    str = "";
    while(!std::cin.eof() && str == "")
    {
        std::cout << "enter darkest secret" << std::endl;
        if(std::getline(std::cin, str) && str != "")
        {
            this->contacts[this->index % 8].set_secret(str);
            std::cout << "contact added successfully" << std::endl;
        }
    }
    this->index++;
}

std::string	add_spaces(int n)
{
	std::string	str;

	while (n--)
		str.append(" ");
	return (str);
}

std::string	fix_width(std::string str, long unsigned max)
{
	if (str.size() > max)
	{
		str.resize(max);
		str[str.size() - 1] = '.';
	}
	return (str);
}


int     PhoneBook::search_ui(contact contact[8])
{
    int i;
    char c;
    std::string str;

    c = '0';
    i = 0;
    while (++c <= '8')
    {
        if (contacts[c - 1 - '0'].get_name().size() && ++i)
        {
            str = c;
            str = fix_width(str, 10);
            std::cout << "|" << add_spaces(10 - str.size()) << str;
            str = fix_width(contact[c - 1 - '0'].get_name(), 10);
            str = fix_width(str, 10);
            std::cout << "|" << add_spaces(10 - str.size()) << str;
            str = fix_width(contact[c - 1 - '0'].get_lname(), 10);
            str = fix_width(str, 10);
            std::cout << "|" << add_spaces(10 - str.size()) << str;
            str = fix_width(contact[c - 1 - '0'].get_nickname(), 10);
            str = fix_width(str, 10);
            std::cout << "|" << add_spaces(10 - str.size()) << str;
            std::cout << "|" << std::endl;
        }
    }
    std::cout << " -------------------------------------------" << std::endl;
    return(i);
}
void    PhoneBook::printall(contact contact[8])
{
    std::string str;

    if(!search_ui(contact))
    {
		std::cout << std::endl << "Phonebook is empty!" << std::endl;
		return ;
	}
    while (!std::cin.eof())
	{
		std::cout << "Select an index: ";
		if (std::getline(std::cin, str) && str != "")
		{
			if (str.size() == 1 && str[0] >= '1' && str[0] <= '8' && \
					contact[str[0] - 1 - '0'].get_name().size())
				break ;
		}
		if (str != "")
			std::cout << "Invalid index!" << std::endl;
	}
	if (!std::cin.eof())
		print(contact[str[0] - 1 - '0']);
}

void    PhoneBook::search(void)
{
    std::cout << "____________________________________________" << std::endl;
    std::cout << "|   Index  |First Name| Last Name| Nickname |" << std::endl;
    std::cout << "|__________|__________|__________|__________|" << std::endl;
    printall(this->contacts);
}


void    PhoneBook::print(contact contact)
{
    	std::cout << std::endl << "Requesting contact information..." << std::endl;
	if (!contact.get_name().size())
	{
		std::cout << "Failed to get info for this contact" << std::endl;
		return ;
	}
	std::cout << "First Name: " << contact.get_name() << std::endl;
	std::cout << "Last Name: " << contact.get_lname() << std::endl;
	std::cout << "Nickname: " << contact.get_nickname() << std::endl;
	std::cout << "Phone Number: " << contact.get_number() << std::endl;
	std::cout << "Darkest Secret: " << contact.get_secret() << std::endl;
}