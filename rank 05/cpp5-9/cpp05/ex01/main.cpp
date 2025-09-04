#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
    Bureaucrat *a = new Bureaucrat("Mateus", 150);
    Bureaucrat *b = new Bureaucrat("Mateus");
    Bureaucrat *c = new Bureaucrat(4);
    Bureaucrat *d = new Bureaucrat;
    Bureaucrat *e = new Bureaucrat(*d);
    Bureaucrat *f = d;
    Form *test = new Form("test", 3, 3);
    Form *test2 = new Form();

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
        c->sign_Form((*test));
    }
    catch(Bureaucrat::GradeTooLowException &e){
        std::cerr << "could not sign Form" << std::endl;
    }
    std::cout << test;
    std::cout << "-----------------" << std::endl <<std::endl;
    std::cout << test2;
    c->sign_Form((*test2));
    std::cout << test2;

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;
    delete test;
    delete test2;
}