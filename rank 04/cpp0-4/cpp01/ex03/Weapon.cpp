#include "Weapon.hpp"

        Weapon::Weapon(std::string type): type(type)
        {
        }

        Weapon::~Weapon()
        {
        }

        const   std::string&  Weapon::get_type(void)
        {
            return(this->type);
        }

        void    Weapon::set_type(std::string type)
        {
            this->type = type;
        }