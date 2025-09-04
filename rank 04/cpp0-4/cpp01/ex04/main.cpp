#include "strings.hpp"

int main(int argc, char **argv)
{
    int i = 0;
    std::string line;
    string str;

    if (argc != 4)
        return(1);
    std::ifstream file(argv[1]);
    if (!file.is_open()){
        std::cout << "file does not exist or does not have right permissions" << std::endl;
        return(1);
    }
    std::ofstream   filen(str.filename(argv[1]));
    while(std::getline(file, line)){
        str.change_str(line, argv);
    }
}