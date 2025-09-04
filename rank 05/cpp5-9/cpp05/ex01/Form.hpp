#pragma once

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
    private:
        const std::string _name;
        bool    _validate;
        const int   _sign_grade;
        const int   _execute_grade;
    public:
        Form();
        Form(const Form &copy);
        Form(int sign_grade, int execute_grade);
        Form(const std::string name);
        Form(const std::string name, int sign_grade, int execute_grade);
        ~Form();

        Form &operator=(const Form &copy);

        void    be_signed(Bureaucrat &Bu);

        const std::string get_name(void)const;
        int   get_sign_grade(void)const;
        int   get_execute_grade(void)const;
        bool        get_validate(void)const;

        class GradeToLowException: public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class GradeToHighException: public std::exception{
            public:
                virtual const char *what() const throw();
        };
};

std::ostream    &operator<<(std::ostream &o, Form *a);
