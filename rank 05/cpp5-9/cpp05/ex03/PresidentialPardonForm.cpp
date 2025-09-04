#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): AForm("PresidentialPardonForm", 25, 5), _target("Default")
{
    std::cout << "PresidentialPardonForm created with target Default " << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(std::string target): AForm("PresidentialPardonForm", 25, 5), _target(target)
{
    std::cout << "PresidentialPardonForm created with target: " << _target << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &copy): AForm("PresidentialPardonForm", 25, 5), _target(copy.get_target())
{
    std::cout << "copy contructor called to copy " << copy.get_name() << std::endl;
    *this = copy;
}

PresidentialPardonForm const &PresidentialPardonForm::operator=(const PresidentialPardonForm &copy)
{
    std::cout << "assignment operator called " << std::endl;
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "Destructor called for PresidentialPardonForm with target: " << _target << std::endl;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    if (executor.get_grade() >= get_execute_grade())
        throw(GradeToLowException());
    else if (get_validate() == false)
        throw(FormNotSigned());
    else
        std::cout << get_target() << " Has been Pardoned by Zaphod Beeblebrox" << std::endl;
}

std::string PresidentialPardonForm::get_target(void) const
{
    return _target;
}

std::ostream &operator<<(std::ostream &o, PresidentialPardonForm *a)
{
    o << "AForm: " << a->get_name() << std::endl << "sign Grade: " << a->get_sign_grade()
    << std::endl << "execute Grade: " << a->get_execute_grade() << std::endl << "Signed: " << a->get_validate() << std::endl;
    return(o);
}
