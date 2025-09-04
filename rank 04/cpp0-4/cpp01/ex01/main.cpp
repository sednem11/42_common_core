#include "Zombie.hpp"

Zombie *zombieHorde( int N, std::string name );

int main(void)
{
    int size = 5;
    Zombie  *horde = zombieHorde(size, "Zom");
    for (int i = 0; i < size; i++)
        horde[i].announce();
    delete [] horde;    
}