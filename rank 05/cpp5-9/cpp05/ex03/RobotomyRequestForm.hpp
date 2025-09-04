#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class RobotomyRequestForm: public AForm
{
private:
    const std::string _target;

    RobotomyRequestForm();
public:
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(RobotomyRequestForm &copy);
    RobotomyRequestForm const &operator=(const RobotomyRequestForm &copy);
    ~RobotomyRequestForm();

    void execute(Bureaucrat const &executor)const;

    std::string get_target(void) const;
};

std::ostream    &operator<<(std::ostream &o, RobotomyRequestForm *a);
