#pragma once
#include <string>

template <typename T>
void    Iter(T *Array, int size, void (*func)(T &))
{
    if (Array == NULL || func == NULL)
        return;
    for (int i = 0; i < size; i++)
        func(Array[i]);
}