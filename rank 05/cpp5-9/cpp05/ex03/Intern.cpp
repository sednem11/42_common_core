#include "Intern.hpp"

Intern::Intern(void)
{
    std::cout << "an Intern was created" << std::endl;
}

Intern::~Intern()
{
    std::cout << "an Intern was Destroyed" << std::endl;
}

Intern::Intern(Intern &copy)
{
    std::cout << "an Intern was copied" << std::endl;
    *this = copy;
}

Intern const &Intern::operator=(const Intern &copy)
{
    std::cout << "an Assignment operator was called for an Intern" << std::endl;
    return(*this);
}

AForm *Intern::Makeform(std::string name, std::string target)
{
	std::string names[3] = {
		"PresidentialPardonForm",
		"RobotomyRequestForm",
		"ShrubberyCreationForm"
	};

	for(int i = 0; i < 3; i++)
	{
		if(name.compare(names[i]) == 0)
		{
			switch(i){
				case 0:
				return new PresidentialPardonForm(target);
				break;
				case 1:
				return new RobotomyRequestForm(target);
				break;
				case 2:
				return new ShrubberyCreationForm(target);
				break;
			}
		}
	}
	std::cout << "The Intern cant do magic, the Form doenst exist so maybe give a name that is correct" << std::endl;
	return NULL;
}
