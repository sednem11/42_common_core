#include "strings.hpp"

string::string(){
}

string::~string()
{
}

std::string string::filename(std::string str)
{
    std::string filename;

    filename.append(str);
    filename.append(".replace");
    return(filename);
}

std::string string::changed_string(std::string str, char **argv)
{
    int i = 0;
    int j = 0;
    std::string final;

    while (str[i] != '\0')
    {
        int  position = ((std::string)&str[i]).find(argv[2], 0);
        if (position >= 0)
        {
            if (position > 0)
            {
                final.append(&str[i], 0, position);
                position = position + i;
                while(i < position)
                    i++;
                position = ((std::string)&str[i]).find(argv[2], 0);
            }
            if (position == 0)
                final.append(argv[3]);
            while(j < ((std::string)argv[2]).length())
            {
                i++;
                j++;
            }
            j = 0;
        }
        if (position < 0)
        {
            final.append(&str[i]);
            break;
        }
    }
    return(final);
}

void string::change_str(std::string str, char **argv)
{
    std::ofstream   file(filename(argv[1]), std::ios::app);
    file << changed_string(str, argv) << std::endl;
}