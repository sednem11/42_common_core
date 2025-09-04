#include "Form.hpp"

Form::Form(): _name("Undefined"), _execute_grade(150) , _validate(false), _sign_grade(150)
{
    std::cout << "Form created with default values" << std::endl;
}

Form::Form(const Form &copy): _name(copy.get_name() + ".copy"), _sign_grade(copy.get_sign_grade()), _execute_grade(copy.get_execute_grade())
{
    *this = copy;
    std::cout << "Form: " << copy.get_name() <<  " copied" << std::endl;
}

Form::Form(int sign_grade, int execute_grade): _name("Default"), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
    _validate = false;
    std::cout << "Form: " << get_name() << " created with sign grade: " << get_sign_grade() << " and execute grade: " << get_execute_grade() << std::endl;
    if (_execute_grade > 150 || _sign_grade > 150)
        throw (GradeToLowException());
    else if (_execute_grade < 1 || _sign_grade < 1)
        throw (GradeToHighException());
}

Form::Form(const std::string name): _name(name), _execute_grade(150) , _validate(false), _sign_grade(150)
{
        std::cout << "Form: " << get_name() <<  " created with default values" << std::endl;
}

Form::Form(const std::string name, int sign_grade, int execute_grade): _name(name), _execute_grade(execute_grade) , _validate(false), _sign_grade(sign_grade)
{
    std::cout << "Form: " << get_name() << " created with sign grade: " << get_sign_grade() << " and execute grade: " << get_execute_grade() << std::endl;
    if (_execute_grade > 150 || _sign_grade > 150)
        throw (GradeToLowException());
    else if (_execute_grade < 1 || _sign_grade < 1)
        throw (GradeToHighException());
}

Form::~Form()
{
    std::cout << "destructor for Form: " << get_name() << " called" << std::endl;
}

Form &Form::operator=(const Form &copy)
{
    std::cout << "Form: " << copy.get_name() << " assigned" << std::endl;
    if (this == &copy)
        return *this;
    _validate = copy.get_validate();
    return(*this);
}

void Form::be_signed(Bureaucrat &Bu)
{
    if (Bu.get_grade() >= get_sign_grade())
        throw (Bureaucrat::GradeTooLowException());
    else if (get_validate() == false)
    {
        _validate = true;
        std::cout << "Form: " << get_name() << " was signed by " << Bu.get_name() << std::endl;
    }
    else
        std::cout << "Form: " << get_name() << "was already signed " << std::endl;
}

const std::string Form::get_name(void) const
{
    return (_name);
}

int Form::get_sign_grade(void) const
{
    return _sign_grade;
}

int Form::get_execute_grade(void) const
{
    return _execute_grade;
}

bool Form::get_validate(void) const
{
    return _validate;
}

const char *Form::GradeToLowException::what() const throw()
{
    return ("Grade to low");
}

const char *Form::GradeToHighException::what() const throw()
{
    return ("Grade to high");
}

std::ostream &operator<<(std::ostream &o, Form *a)
{
    o << "Form: " << a->get_name() << std::endl << "sign Grade: " << a->get_sign_grade()
    << std::endl << "execute Grade: " << a->get_execute_grade() << std::endl << "Signed: " << a->get_validate() << std::endl;
    return(o);
}
