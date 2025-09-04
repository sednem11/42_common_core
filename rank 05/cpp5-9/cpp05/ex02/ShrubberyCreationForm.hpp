#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include <iostream>
#include <string>

class ShrubberyCreationForm: public AForm
{
private:
    const std::string _target;

    ShrubberyCreationForm();
public:
    ShrubberyCreationForm(std::string target);
    ShrubberyCreationForm(ShrubberyCreationForm &copy);
    ShrubberyCreationForm const &operator=(const ShrubberyCreationForm &copy);
    ~ShrubberyCreationForm();

    void execute(Bureaucrat const &executor)const;

    std::string get_target(void) const;
};

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm *a);