#include "ScavTrap.hpp"

void    Dapneturn(void)
{
    ScavTrap D("Daphne");
    while(D.get_Health() > 0)
    {
        D.attack("Mateus");
        D.takeDamage(20);
        D.beRepaired(10);
    }
    D.GuardGate();
}

int main (void)
{
    Dapneturn();
    std::cout << std::endl << std::endl << std::endl << std::endl;
    ScavTrap M("Mateus");
    {
        M.attack("Dapne");
        M.takeDamage(20);
        M.beRepaired(10);
        M.GuardGate();
    }
}