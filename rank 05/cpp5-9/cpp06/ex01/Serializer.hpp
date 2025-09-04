#pragma once

#include <iostream>
#include <string>
#include <stdint.h>

typedef struct Data
{
	std::string	name;
	size_t		age;
	Data		*next;
}   Data;

class   Serializer
{
    private:

    public:
        Serializer();
        Serializer(const Serializer &copy);
        Serializer &operator=(const Serializer &copy);
        ~Serializer();

        uintptr_t serialize(Data* ptr);
        Data* deserialize(uintptr_t raw);
};