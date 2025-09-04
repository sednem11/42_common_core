#include "PhoneBook.hpp"

contact::contact(void)
{
}

contact::~contact(void)
{
}

std::string contact::get_name(void) const
{
    return (this->name);
}

std::string contact::get_lname(void) const
{
    return (this->lastname);
}

std::string contact::get_nickname(void) const
{
    return (this->nickname);
}

std::string contact::get_secret(void) const
{
    return (this->secret);
}

std::string contact::get_number(void) const
{
    return (this->number);
}

void    contact::set_name(std::string str)
{
    this->name = str;
}

void    contact::set_lname(std::string str)
{
    this->lastname = str;
}

void    contact::set_nickname(std::string str)
{
    this->nickname = str;
}

void    contact::set_number(std::string str)
{
    this->number = str;
}

void    contact::set_secret(std::string str)
{
    this->secret = str;
}