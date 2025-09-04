#include "Serializer.hpp"

Serializer::Serializer()
{
    std::cout << "Serializer iniciated" << std::endl;
}

Serializer::Serializer(const Serializer &copy)
{
    std::cout << "Serializer copied" << std::endl;
    *this = copy;
}

Serializer &Serializer::operator=(const Serializer &copy)
{
    std::cout << "Serializer operator copied" << std::endl;
    return (*this);
}

Serializer::~Serializer()
{
    std::cout << "Serializer destroyed" << std::endl;
}

uintptr_t Serializer::serialize(Data *ptr)
{
    return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw)
{
    return (reinterpret_cast<Data *>(raw));
}
