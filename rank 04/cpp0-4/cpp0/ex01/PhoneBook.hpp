#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <string>

class contact{
    public:
        contact(void);
        ~contact(void);

        std::string get_name(void) const;
        std::string get_lname(void) const;
        std::string get_nickname(void) const;
        std::string get_number(void) const;
        std::string get_secret(void) const;

        void    set_name(std::string str);
        void    set_lname(std::string str);
        void    set_nickname(std::string str);
        void    set_number(std::string str);
        void    set_secret(std::string str);

    private:
        std::string name;
        std::string lastname;
        std::string nickname;
        std::string number;
        std::string secret;
};

class PhoneBook{
    public:
        PhoneBook(void);
        ~PhoneBook(void);
        void        add(void);
        void        search(void);
        void        print(contact contact);
        void        printall(contact contact[8]);
        int         search_ui(contact contact[8]);

    private:
        contact contacts[8];
        int     index;
};


#endif