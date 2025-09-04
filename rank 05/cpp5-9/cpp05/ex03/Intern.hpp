#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <iostream>
#include <string>

class Intern
{
    public:
        Intern(void);
        ~Intern();
        Intern(Intern &copy);
        Intern const &operator=(const Intern &copy);

        AForm *Makeform(std::string name, std::string target);
};
