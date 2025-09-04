#include "cat.hpp"
#include "dog.hpp"
#include "Wrong.hpp"

#define N_ANIMALS 10

int	main(void)
{
    const Animal *Animals[N_ANIMALS];

    for(int i = 0; i < N_ANIMALS; i++)
    {
        if (i < N_ANIMALS / 2)
            Animals[i] = new Dog();
        else
            Animals[i] = new Cat();
    }
    Brain *brain;
    brain = &Animals[0]->getBrain();
    brain->set_ideas("aaaaaaaaaaaa", 0);
    brain->set_ideas("bbbbbbbbbbbb", 1);
    brain->set_ideas("cccccccccccc", 2);
    std::cout << Animals[0]->getBrain().get_ideas(0) << std::endl;
    std::cout << Animals[0]->getBrain().get_ideas(1) << std::endl;
    std::cout << Animals[0]->getBrain().get_ideas(2) << std::endl;
    for (int i = 0; i < N_ANIMALS; i++)
        delete Animals[i];
    std::cout << "-------------------------------------\n";
	{
		std::cout << "Check deep copy of Dog class using copy constructor:\n" << std::endl;
		Dog *dogA = new Dog("weird");
		Dog *dogB = new Dog(*dogA);
        std::cout << std::endl;

		delete dogA;
		delete dogB;
	}
    return 0;
}