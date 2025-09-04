#include "MutantStack.hpp"

int main(void)
{
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	mstack.pop();
	mstack.push(3);
	mstack.push(737);

	MutantStack<int>::iterator s_it = mstack.begin();
	MutantStack<int>::iterator e_it = mstack.end();

	++s_it;
	--s_it;
	std::cout << "int Iterator: ";
	while (s_it != e_it)
	{
		std::cout << *s_it << ", ";
		++s_it;
	}
}