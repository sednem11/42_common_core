#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
    int	i;

	i = 1;
    if (argc == 1)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" ;
    else if (argc > 1)
    {
        while(argv[i])
		{
			std::string argument = argv[i];

			for (char& c : argument)
				c = toupper(c);
			std::cout << argument << " ";
			i++;
		}
    }
	std::cout << std::endl;
	return(1);
}