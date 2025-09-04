#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main(void)
{
    Bureaucrat *a = new Bureaucrat("Mateus", 150);
    Bureaucrat *b = new Bureaucrat("Mateus");
    Bureaucrat *c = new Bureaucrat("Mateus Mendes", 4);
    Bureaucrat *d = new Bureaucrat;
    Bureaucrat *e = new Bureaucrat(*d);
    Bureaucrat *f = d;
    Intern     *i = new Intern();
    AForm *test = i->Makeform("PresidentialPardonForm", "test");
    RobotomyRequestForm *test2 = new RobotomyRequestForm("test2");
    ShrubberyCreationForm *test3 = new ShrubberyCreationForm("test3");

    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << a;
    try
    {
        a->IncrementGrade();
    }
    catch(Bureaucrat::GradeTooHighException &e){
        std::cerr << "Impossible to Increase Grade" << std::endl;
    }
    std::cout << a;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << b;
    try{
    b->DecreaseGrade();
    }
    catch(Bureaucrat::GradeTooLowException &e){
        std::cerr << "Impossible to Decrease Grade" << std::endl;
    }
    std::cout << b;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << c;
    try{
    c->IncrementGrade();
    }
    catch(Bureaucrat::GradeTooHighException &e){
        std::cerr << "Impossible to Increase Grade" << std::endl;
    }
    std::cout << c;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << d;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << e;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << f;
    std::cout << "-----------------" << std::endl <<std::endl;

    std::cout << test;
    try{
        a->sign_Form((*test));
    }
    catch(Bureaucrat::GradeTooLowException &e){
        std::cerr << "could not sign AForm: " << e.what() << std::endl;
    }
    c->sign_Form(*test);
    std::cout << test;
    test->execute(*c);
    delete test;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << test2;
    c->sign_Form(*test2);
    std::cout << test2;
    test2->execute(*c);
    test2->execute(*c);
    delete test2;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << test3;
    try{
        test3->execute(*c);
    }
    catch(AForm::FormNotSigned &e)
    {
        std::cerr << e.what() << std::endl;
    }
    c->sign_Form((*test3));
    std::cout << test3;
    test3->execute(*c);
    c->sign_Form(*test3);
    delete test3;
    std::cout << "-----------------" << std::endl <<std::endl;

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    delete i;
}