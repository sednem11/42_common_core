/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:07:32 by yohan             #+#    #+#             */
/*   Updated: 2025/05/13 14:04:49 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"
#include "../includes/client.hpp"

Client::Client()
{
    role = USER;
    clientFd.fd = -1;
    clientFd.events = POLLIN;
    clientFd.revents = 0;
    nickname = "";
    username = "";
	realName = "";
	isPassSet = false;
	isUserSet = false;
	isNickSet = false;
	authenticated = false;
    cmd_handle = "";
}

Client::Client(int clientSocket)
{
    role = USER;
    clientFd.fd = clientSocket; // giving socket fd
    clientFd.events = POLLIN; // will be notified when something is to be read
    clientFd.revents = 0; // revents will be changed by poll()
    std::stringstream ss;
    ss << clientSocket;
    std::string socket = ss.str();
    nickname = "";
    username = "";
    isWelcomed = false;
	realName = " ";

	isPassSet = false;
	isUserSet = false;
	isNickSet = false;
	authenticated = false;
    cmd_handle = "";
}

Client::Client(const Client &copy) :
role(copy.role),
clientFd(copy.clientFd),   
nickname(copy.nickname),
username(copy.username),
isWelcomed(copy.isWelcomed),
realName(copy.realName),
isPassSet(copy.isPassSet),
isUserSet(copy.isUserSet),
isNickSet(copy.isNickSet),
authenticated(copy.authenticated)
{
    cmd_handle = copy.cmd_handle;
}

Client &Client::operator=(const Client &other)
{
    if (this != &other)
    {
        clientFd = other.clientFd;
        nickname = other.nickname;
        role = other.role;
        username = other.username;
        isWelcomed = other.isWelcomed;
		realName = other.realName;
		isPassSet = other.isPassSet;
		isUserSet = other.isUserSet;
		isNickSet = other.isNickSet;
		authenticated = other.authenticated;
        cmd_handle = other.cmd_handle;
    }
    return (*this);
}

Client::~Client()
{
}

// -------------------------------------------------------------------------------//

void    Client::setUsername(const std::string &newUsername)
{
    username = newUsername;
}

void    Client::setNickname(const std::string &newNickname)
{
    nickname = newNickname;
}

void	Client::setRealname(const std::string &newRealname)
{
	realName = newRealname;
}

void	Client::setRole(int i)
{
	role = i;
}

void	Client::setisNick()
{
	isNickSet = true;
}

void	Client::setisPass()
{
	isPassSet = true;
}

void 	Client::setisUser()
{
	isUserSet = true;
}

void	Client::setAuthenticated()
{
	authenticated = true;
}

void    Client::setHandle(std::string cmd)
{
    cmd_handle = cmd;
}

void    Client::setHandleNull()
{
    cmd_handle.clear();
}

std::string Client::getUsername() const
{
    return (username);
}

std::string  Client::getNickname() const
{
    return (nickname);
}

std::string  Client::getRealname() const
{
    return (realName);
}

bool		Client::getPassSet() const
{
	return(isPassSet);
}

bool		Client::getNickSet() const
{
	return(isNickSet);
}

bool		Client::getUserSet() const
{
	return(isUserSet);
}

bool		Client::getAuthenticated() const
{
	return (authenticated);
}

std::string Client::getHandle() const
{
    return (cmd_handle);
}

pollfd          &Client::getClientFd()
{
    return (clientFd);
}

bool    operator==(Client &lhs, Client &rhs)
{
        return lhs.getClientFd().fd == rhs.getClientFd().fd;
}

bool         Client::isOperator()
{
    return (role == OPERATOR);
}

void    Client::becomeOperator()
{
    role = OPERATOR;
}

const char   *Client::getClientIP()
{
    sockaddr_in address;
    socklen_t len = sizeof(address);

    if (getpeername(this->clientFd.fd, (sockaddr *)&address, &len) == 0)
        return (inet_ntoa(address.sin_addr));
    return (NULL);
}

bool         Client::sentWelcome()
{
    return isWelcomed;
}

void         Client::setWelcomed(bool value)
{
    isWelcomed = value;
}


