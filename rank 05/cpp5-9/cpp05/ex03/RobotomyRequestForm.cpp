#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("RobotomyRequestForm", 72, 45), _target("Default")
{
    std::cout << "RobotRequestForm created with target Default " << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("RobotomyRequestForm", 72, 45), _target(target)
{
    std::cout << "RobotRequestForm created with target: " << _target << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &copy): AForm("RobotomyRequestForm", 72, 45), _target(copy.get_target())
{
    std::cout << "copy constructor called to copy " <<  copy.get_name() << std::endl;
    *this = copy;
}

RobotomyRequestForm const &RobotomyRequestForm::operator=(const RobotomyRequestForm &copy)
{
    std::cout << "assignment operator called " << std::endl;
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
    std::cout << "Destructor called for RobotRequestForm with target: " << _target << std::endl;
}

static int robot_fail = 0;

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    if (executor.get_grade() >= get_execute_grade())
        throw(GradeToLowException());
    else if (get_validate() == false)
        throw(FormNotSigned());
	else if (robot_fail++ % 2)
		std::cout << "BRRRRRRRRRRRRRR\n" << get_target() << " was robotomized" << std::endl;
	else
		std::cout << "Robotomy failed" << std::endl;
}

std::string RobotomyRequestForm::get_target(void) const
{
    return _target;
}

std::ostream &operator<<(std::ostream &o, RobotomyRequestForm *a)
{
    o << "AForm: " << a->get_name() << std::endl << "sign Grade: " << a->get_sign_grade()
    << std::endl << "execute Grade: " << a->get_execute_grade() << std::endl << "Signed: " << a->get_validate() << std::endl;
    return(o);
}
