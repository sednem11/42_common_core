#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <cstdio>

static Base * generate(void)
{
    switch (rand() % 3)
    {
    case 0:
        return (new A());
        break;
    case 1:
        return (new B());
        break;
    case 2:
        return (new C());
        break;
    default:
        std::cout << "random is not working" << std::endl;
        return(NULL);
    }
}

static void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "is A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "is B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "is C" << std::endl;
    else
        std::cout << "unknown" << std::endl;
}

static int i = 0;
static std::string classes[] = {"A", "B", "C"};

static void identify(Base &p)
{
	while (i < 3)
	{
		void *foo = NULL;
		Base &unused = (Base &)foo;
		try
		{
			if (i == 0)
				unused = dynamic_cast<A &>(p);
			else if (i == 1)
				unused = dynamic_cast<B &>(p);
			else if (i == 2)
				unused = dynamic_cast<C &>(p);
			else
				std::cout << "unknow type" << std::endl;
			(void)unused;
		}
		catch (std::exception &e)
		{
			i++;
			identify(p);
			return;
		}
		std::cout << classes[i] << " is the identified type" << std::endl;
		i = 0;
		break;
	}
}


int main(void)
{
    srand(time(NULL));
    Base *test = generate();
    if (test == NULL)
        return (1);
    identify(test);
    identify(*test);
    delete(test);
    return (0);
}