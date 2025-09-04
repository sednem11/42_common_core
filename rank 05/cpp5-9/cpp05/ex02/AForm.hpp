#pragma once

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    protected:
        const std::string _name;
        bool        _validate;
        const int   _sign_grade;
        const int   _execute_grade;

        AForm();
        AForm(int sign_grade, int execute_grade);
        AForm(const std::string name);
        AForm(const std::string name, int sign_grade, int execute_grade);
    public:
        virtual ~AForm();

        AForm(const AForm &copy);
        AForm &operator=(const AForm &copy);

        void    be_signed(Bureaucrat &Bu);

        const std::string get_name(void)const;
        int   get_sign_grade(void)const;
        int   get_execute_grade(void)const;
        bool        get_validate(void)const;

        virtual void execute(Bureaucrat const &executor) const = 0;


        class GradeToLowException: public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class GradeToHighException: public std::exception{
            public:
                virtual const char *what() const throw();
        };
        class FormNotSigned: public std::exception{
            public:
                virtual const char *what() const throw();
        };
};

std::ostream    &operator<<(std::ostream &o, AForm *a);
