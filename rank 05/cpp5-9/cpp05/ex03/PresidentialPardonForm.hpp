#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class PresidentialPardonForm: public AForm
{
    private:
        const std::string _target;

        PresidentialPardonForm(void);
    public:
        PresidentialPardonForm(std::string target);
        PresidentialPardonForm(PresidentialPardonForm &copy);
        PresidentialPardonForm const &operator=(const PresidentialPardonForm &copy);
        ~PresidentialPardonForm();

        void execute(Bureaucrat const &executor)const;

        std::string get_target(void) const;
};

std::ostream    &operator<<(std::ostream &o, PresidentialPardonForm *a);
