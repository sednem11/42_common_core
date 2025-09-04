#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyCreationForm", 145, 137), _target("Default")
{
    std::cout << "ShrubberyCreationForm created with target Default " << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137), _target(target)
{
    std::cout << "ShrubberyCreationForm created with target: " << _target << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &copy): AForm("ShrubberyCreationForm", 145, 137), _target(copy.get_target())
{
    std::cout << "copy constructor called to copy " << copy.get_name() << std::endl;
    *this = copy;
}

ShrubberyCreationForm const &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &copy)
{
    std::cout << "assignment operator called" << std::endl;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "Destructor called for ShrubberyCreationForm with target: " << _target << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    if (executor.get_grade() >= get_execute_grade())
        throw(GradeToLowException());
    else if (get_validate() == false)
        throw(FormNotSigned());
    else
    {
		std::ofstream outfile (get_target().append("_shrubbery").c_str());

		for (int i = 0; i < 5; i++)
		{
			outfile <<
			"         v" << std::endl <<
			"        >X<" << std::endl <<
			"         A" << std::endl <<
			"        d$b" << std::endl <<
			"      .d\\$$b." << std::endl <<
			"    .d$i$$\\$$b." << std::endl <<
			"       d$$@b" << std::endl <<
			"      d\\$$$ib" << std::endl <<
			"    .d$$$\\$$$b" << std::endl <<
			"  .d$$@$$$$\\$$ib." << std::endl <<
			"      d$$i$$b" << std::endl <<
			"     d\\$$$$@$b" << std::endl <<
			"  .d$@$$\\$$$$$@b." << std::endl <<
			".d$$$$i$$$\\$$$$$$b." << std::endl <<
			"        ###" << std::endl <<
			"        ###" << std::endl <<
			"        ###" << std::endl <<
		std::endl;
		}
		outfile.close();
    }
}

std::string ShrubberyCreationForm::get_target() const
{
    return _target;
}

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm *a)
{
    o << "AForm: " << a->get_name() << std::endl << "sign Grade: " << a->get_sign_grade()
    << std::endl << "execute Grade: " << a->get_execute_grade() << std::endl << "Signed: " << a->get_validate() << std::endl;
    return(o);
}
