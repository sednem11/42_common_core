#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(): _name("Default"), _grade(150)
{
    std::cout << "Bureaucrat named " << get_name() << " was created with grade " <<  get_grade() << std::endl;
}

Bureaucrat::Bureaucrat(std::string const &name, int grade): _name(name), _grade(grade)
{
    std::cout << "Bureaucrat named " << get_name() << " was created with grade " <<  get_grade() << std::endl;
}

Bureaucrat::Bureaucrat(std::string const &name): _grade(150), _name(name)
{
    std::cout << "Bureaucrat named " << get_name() << " was created with grade " <<  get_grade() << std::endl;
}

Bureaucrat::Bureaucrat(int grade): _name("Default")
{
    std::cout << "Bureaucrat named " << get_name() << " was created with grade " <<  grade << std::endl;
    set_grade(grade);
}

Bureaucrat::Bureaucrat(Bureaucrat const &copy): _name(copy.get_name() + ".copy")
{
    *this = copy;
    std::cout << "Bureaucrat named " << copy.get_name() << " copied" << std::endl;
}

Bureaucrat const &Bureaucrat::operator=(const Bureaucrat &copy)
{
    std::cout << "Bureaucrat named " << copy.get_name() << " assigned" << std::endl;
    if (this == &copy)
		return *this;
    _grade = copy.get_grade();
    return (*this);
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat named " << get_name() << " Destroyed" << std::endl;
}

const std::string &Bureaucrat::get_name() const
{
    return (this->_name);
}

int Bureaucrat::get_grade(void) const
{
    return (this->_grade);
}

void Bureaucrat::set_grade(int grade)
{
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    else if (grade < 0)
        throw Bureaucrat::GradeTooHighException();
    else
        this->_grade = grade;
}

void Bureaucrat::IncrementGrade(void)
{
    std::cout << "Incrementing " << _name << " Grade by 1" << std::endl;
    set_grade(_grade - 1);
}

void Bureaucrat::DecreaseGrade(void)
{
    std::cout << "Decreasing " << _name << " Grade by 1" << std::endl;
    set_grade(_grade + 1);
}

void Bureaucrat::sign_Form(Form &Form)
{
    Form.be_signed(*this);
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low");
};

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high");
};

std::ostream &operator<<(std::ostream &o, Bureaucrat *a)
{
    o << "Bureaucrat " << a->get_name() << " grade: " << a->get_grade() << std::endl << std::endl;
	return (o);
}
