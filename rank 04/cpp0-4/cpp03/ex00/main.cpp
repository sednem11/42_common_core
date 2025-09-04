#include "ClapTrap.hpp"

int main (void)
{
    ClapTrap S("Stephan");
    while(S.get_Health() >= 0)
    {
        S.attack("Mateus");
        S.takeDamage(2);
        S.beRepaired(1);
    }
}