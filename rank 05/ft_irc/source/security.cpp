/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Security.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohan <yohan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:05:49 by yohan             #+#    #+#             */
/*   Updated: 2025/03/12 18:06:08 by yohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

Security::Security() : port() {};

Security::Security(std::string &port)
{
    try
    {
        validatePort(port);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

Security::Security(const Security &copy)
{
    *this = copy;
}

Security &Security::operator=(const Security &other)
{
    if (this != &other)
    {
        this->port = other.port;
        this->role = other.role;
    }
    return *this;
}

Security::~Security() {}

//----------------------------------------------------------------------//

bool            isNum(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

void            Security::validatePort(std::string &Port)
{
    char *end;
    if (Port.size() > 10 || !isNum(Port))
        throw std::runtime_error("Invalid Port");
    port = (unsigned int)std::strtol(Port.c_str(), &end, 10);
    if (port < 1024 || port > 49151)
        throw std::runtime_error("Port busy");
    else if (port != PORT_ID)
        throw std::runtime_error("Invalid port");
}

void            Security::validatePassword(const std::string &attempt)
{
	
    if (attempt == NETWORK_PASSWORD)
    {
        role = USER;
        std::cout << "Authenticated as User." << std::endl;
    }
    else if (attempt == OPERATOR_PASSWORD)
    {
        role = OPERATOR;
        std::cout << "Authenticated as Admin." << std::endl;
    }
    else 
        throw std::runtime_error("Invalid password");
}

unsigned int    Security::getPort()
{
    return(port);
}

int    Security::getRole()
{
    return(role);
}