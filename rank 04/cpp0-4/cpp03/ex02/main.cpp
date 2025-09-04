#include "FragTrap.hpp"

void    Dapneturn(void)
{
    FragTrap D("Daphne");
    while(D.get_Health() > 0)
    {
        D.attack("Mateus");
        D.takeDamage(20);
        D.beRepaired(10);
    }
    D.HighFivesGuys();
}

int main (void)
{
    Dapneturn();
    std::cout << std::endl << std::endl << std::endl << std::endl;
    FragTrap M("Mateus");
    {
        M.attack("Dapne");
        M.takeDamage(20);
        M.beRepaired(10);
        M.HighFivesGuys();
    }
}