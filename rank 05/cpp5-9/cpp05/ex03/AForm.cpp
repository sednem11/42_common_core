#include "AForm.hpp"

AForm::AForm(): _name("Undefined"), _execute_grade(150) , _validate(false), _sign_grade(150)
{
    std::cout << "AForm created with default values" << std::endl;
}

AForm::AForm(const AForm &copy): _name(copy.get_name() + ".copy"), _sign_grade(copy.get_sign_grade()), _execute_grade(copy.get_execute_grade())
{
    *this = copy;
    std::cout << "AForm: " << copy.get_name() <<  " copied" << std::endl;
}

AForm::AForm(int sign_grade, int execute_grade): _name("Default"), _sign_grade(sign_grade), _execute_grade(execute_grade)
{
    _validate = false;
    std::cout << "AForm: " << get_name() << " created with sign grade: " << get_sign_grade() << " and execute grade: " << get_execute_grade() << std::endl;
    if (_execute_grade > 150 || _sign_grade > 150)
        throw (GradeToLowException());
    else if (_execute_grade < 1 || _sign_grade < 1)
        throw (GradeToHighException());
}

AForm::AForm(const std::string name): _name(name), _execute_grade(150) , _validate(false), _sign_grade(150)
{
        std::cout << "AForm: " << get_name() <<  " created with default values" << std::endl;
}

AForm::AForm(const std::string name, int sign_grade, int execute_grade): _name(name), _execute_grade(execute_grade) , _validate(false), _sign_grade(sign_grade)
{
    std::cout << "AForm: " << get_name() << " created with sign grade: " << get_sign_grade() << " and execute grade: " << get_execute_grade() << std::endl;
    if (_execute_grade > 150 || _sign_grade > 150)
        throw (GradeToLowException());
    else if (_execute_grade < 1 || _sign_grade < 1)
        throw (GradeToHighException());
}

AForm::~AForm()
{
    std::cout << "Destructor for AForm: " << get_name() << " called" << std::endl;
}

AForm &AForm::operator=(const AForm &copy)
{
    std::cout << "AForm: " << copy.get_name() << " assigned" << std::endl;
    if (this == &copy)
        return *this;
    _validate = copy.get_validate();
    return(*this);
}

void AForm::be_signed(Bureaucrat &Bu)
{
    if (Bu.get_grade() >= get_sign_grade())
        throw (Bureaucrat::GradeTooLowException());
    else if (get_validate() == false)
    {
        _validate = true;
        std::cout << "AForm: " << get_name() << " was signed by " << Bu.get_name() << std::endl;
    }
    else
        std::cout << "AForm: " << get_name() << " was already signed " << std::endl;
}

const std::string AForm::get_name(void) const
{
    return (_name);
}

int AForm::get_sign_grade(void) const
{
    return _sign_grade;
}

int AForm::get_execute_grade(void) const
{
    return _execute_grade;
}

bool AForm::get_validate(void) const
{
    return _validate;
}

void AForm::execute(Bureaucrat const &executor)const
{
	(void)executor;
}

const char *AForm::GradeToLowException::what() const throw()
{
    return ("Grade to low");
}

const char *AForm::GradeToHighException::what() const throw()
{
    return ("Grade to high");
}

const char *AForm::FormNotSigned::what() const throw()
{
    return ("Form needs to be signed to be executed");
}

std::ostream &operator<<(std::ostream &o, AForm *a)
{
    o << "AForm: " << a->get_name() << std::endl << "sign Grade: " << a->get_sign_grade()
    << std::endl << "execute Grade: " << a->get_execute_grade() << std::endl << "Signed: " << a->get_validate() << std::endl;
    return(o);
}

