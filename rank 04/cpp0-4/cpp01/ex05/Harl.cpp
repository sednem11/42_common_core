#include "Harl.hpp"

Harl::Harl()
{
    std::cout << "Harl the fat kid enters the chat" << std::endl;
}

Harl::~Harl()
{
    std::cout << DEFAULT << "dies of diabetes and high colestorol levels" << std::endl;
}

void Harl::debug(void)
{
    std::cout << MAGENTA << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}

void Harl::warning(void)
{
    std::cout << YELLOW << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::info(void)
{
    std::cout << RED << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::error(void)
{
    std::cout << GRAY << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(std::string level)
{
    void    (Harl::*complain[4])(void) = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
    std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

    for (int i = 0; i < 4; i++)
    {
        if(levels[i] == level)
        {
            (this->*complain[i])();
            break;
        }
    }
}