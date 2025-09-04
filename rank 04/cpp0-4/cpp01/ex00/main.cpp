#include "Zombie.hpp"

Zombie  *newZombie(std::string name);

void    randomChump(std::string name);

int main(void)
{
    Zombie  *z=newZombie("Mateus");
    z->announce();
    randomChump("Daphne");
    delete z;
}