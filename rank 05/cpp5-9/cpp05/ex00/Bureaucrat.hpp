#pragma once

#include <iostream>
#include <string>

class Bureaucrat
{
private:
    const std::string _name;
    int         _grade;
    void    set_grade(int grade);
public:
    Bureaucrat();
    Bureaucrat(std::string const &name, int grade);
    Bureaucrat(std::string const &name);
    Bureaucrat(int grade);
    Bureaucrat(Bureaucrat const &copy);
    Bureaucrat const &operator=(const Bureaucrat &copy);
    const std::string &get_name(void) const;
    ~Bureaucrat();
    int     get_grade(void) const;
    void    IncrementGrade(void);
    void    DecreaseGrade(void);
    class GradeTooHighException: public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
    class GradeTooLowException: public std::exception
    {
        public:
            virtual const char *what() const throw();
    };
    
};

std::ostream	&operator<<(std::ostream &o, Bureaucrat *a);