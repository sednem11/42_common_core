#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    *this = copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &copy)
{
    if (this != &copy)
        *this = copy;
    return(*this);
}

int PmergeMe::set_arguments(char *arg)
{
    std::string str(arg);
    if (str.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cerr << "Error: " << str << " is not acceptable" << std::endl;
        return (-1);
    }
    if (!stack1.empty())
    {
        for (int i = 0; i < stack1.size(); i++)
        {
            if (std::stoi(str) == stack1[i])
            {
                std::cerr << stack1[i] << " already exists" << std::endl;
                return (-1);
            }
        }
    }
    stack1.push_back(std::stoi(str));
    stack2.push_back(std::stoi(str));
    return (0);
}

static int size = 0;
static int check = 1;
static double dur = 0;
static double dur1 = 0;

void PmergeMe::sorting_process()
{
    clock_t start1 = clock();
    sort_deque();
    clock_t end1 = clock();
    dur1 = double(end1 - start1) / CLOCKS_PER_SEC;
    size = 0;
    check = 1;
    clock_t start = clock();
    sort_vector();
    clock_t end = clock();
    dur = double(end - start) / CLOCKS_PER_SEC;
}

void PmergeMe::sort_vector()
{
    size = stack1.size() / check;
    if (stack1.size() % check != 0)
        size += 1;
    if (size < 2)
        return ;
    for (int i = 0; i < size; i++)
    {
        if(i + 1 < size && i % 2 == 0)
        {
            if (stack1[i] > stack1[i + 1])
            {
                stack1.insert(stack1.begin() + size, stack1[i]);
                stack1.erase(stack1.begin() + i);
            }
            else
            {
                stack1.insert(stack1.begin() + size, stack1[i + 1]);
                stack1.erase(stack1.begin() + i + 1);
            }
        }
    }
    check *= 2;
    int size2 = size;
    sort_vector();
    for (int j = size2 / 2; j < size2; j++)
    {
        for (int i = 0; i < j; i++)
        {
            if (stack1[i] > stack1[j])
            {
                stack1.insert(stack1.begin() + i, stack1[j]);
                stack1.erase(stack1.begin() + j + 1);
                break;
            }
        }

    }
}

void PmergeMe::sort_deque()
{
    size = stack2.size() / check;
    if (stack2.size() % check != 0)
        size += 1;
    if (size < 2)
        return ;
    for (int i = 0; i < size; i++)
    {
        if(i + 1 < size && i % 2 == 0)
        {
            if (stack2[i] > stack2[i + 1])
            {
                stack2.insert(stack2.begin() + size, stack2[i]);
                stack2.erase(stack2.begin() + i);
            }
            else
            {
                stack2.insert(stack2.begin() + size, stack2[i + 1]);
                stack2.erase(stack2.begin() + i + 1);
            }
        }
    }
    check *= 2;
    int size2 = size;
    sort_deque();
    for (int j = size2 / 2; j < size2; j++)
    {
        for (int i = 0; i < j; i++)
        {
            if (stack2[i] > stack2[j])
            {
                stack2.insert(stack2.begin() + i, stack2[j]);
                stack2.erase(stack2.begin() + j + 1);
                break;
            }
        }

    }
}

void PmergeMe::output(char **arguments)
{
    std::cout << "Before:     ";
    for (int i = 1; arguments[i]; i++)
        std::cout << arguments[i] << " ";
    std::cout << std::endl << "After:      ";
    for (int i = 0; i < stack2.size(); i++)
        std::cout << stack2[i] << " ";
    std::cout << std::endl;
    std::cout << "duration deque: " << std::fixed << std::setprecision(6) << dur1 << std::endl;
    std::cout << "duration vec: " << std::fixed << std::setprecision(6) << dur << std::endl;
}
