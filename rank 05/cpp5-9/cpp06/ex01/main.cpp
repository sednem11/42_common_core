#include "Serializer.hpp"

int main(void)
{
    Data ptr2;
    ptr2.name = "Mateus Mendes2";
    ptr2.age = 202;
    ptr2.next = NULL;

    Data ptr;
    ptr.name = "Mateus Mendes";
    ptr.age = 20;
    ptr.next = &ptr2;

    std::cout << "Original ptr"
                << "\nAdress: " << &ptr
                << "\nName: " << ptr.name
                << "\nAge: " << ptr.age
                << "\nNext Adress" << ptr.next << std::endl;

    std::cout << "Original ptr2"
                << "\nAdress: " << &ptr2
                << "\nName: " << ptr2.name
                << "\nAge: " << ptr2.age
                << "\nNext Adress" << ptr2.next << std::endl;
    
    Serializer a;

    std::cout << std::endl << std::endl;
    std::cout << a.serialize(&ptr) << std::endl;
    std::cout << a.serialize(&ptr2) << std::endl << std::endl << std::endl;

    Data *newptr = a.deserialize(a.serialize(&ptr));
    Data *newptr2 = a.deserialize(a.serialize(&ptr2));

    std::cout << "deserialized newptr"
                << "\nAdress: " << newptr
                << "\nName: " << newptr->name
                << "\nAge: " << newptr->age
                << "\nNext Adress" << newptr->next << std::endl;

    std::cout << "deserialized newptr2"
                << "\nAdress: " << newptr2
                << "\nName: " << newptr2->name
                << "\nAge: " << newptr2->age
                << "\nNext Adress" << newptr2->next << std::endl;

}