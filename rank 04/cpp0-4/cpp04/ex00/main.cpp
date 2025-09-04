#include "cat.hpp"
#include "dog.hpp"
#include "Wrong.hpp"

int	main(void)
{
    const Animal* meta = new Animal("szonja");
    const Animal* j = new Dog("Dog");
    const Animal* i = new Cat();
    const WrongAnimal	*k = new WrongCat("test");
    
    std::cout << "-------------------" << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); 
    std::cout << "-------------------" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << j->getType() << " " << std::endl;
    j->makeSound();
    std::cout << "-------------------" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << meta->getType() << " " << std::endl;
    meta->makeSound();
    std::cout << "-------------------" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << k->getType() << " " << std::endl;
    k->makeSound();
    std::cout << "-------------------" << std::endl;


	delete meta;
	delete i;
	delete j;
	delete k;
    return 0;
}