#ifndef STRINGS_HPP
# define STRINGS_HPP

#include <iostream>
#include <fstream>
#include <string>

class   string{
    private:
    public:
        string(void);
        ~string(void);
        void    change_str(std::string str, char **argv);
        std::string filename(std::string str);
        std::string changed_string(std::string str, char **argv);
};

#endif