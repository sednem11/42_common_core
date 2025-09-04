/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajorge-p <ajorge-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by                   #+#    #+#             */
/*   Updated: 2025/05/08 10:31:16 by ajorge-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/library.h"
#include "../includes/channel.hpp"


class Client;

Channel::Channel(std::string &name, bool isInviteOnly, bool isPrivate, std::string password) :
inviteOnly(isInviteOnly),
privChannel(isPrivate),
password(password),
ChannelName(name),
members(),
operators(),
bannedMembers(),
userLimit(0),
topicChange(0)
{}

// Channel::Channel(std::string &name) : ChannelName(name)
// {
//     // if (requiresAuth)
//     //     createPassword();
// }

Channel::Channel(const Channel &copy) : inviteOnly(copy.inviteOnly),
privChannel(copy.privChannel),
password(copy.password),
ChannelName(copy.ChannelName),
members(copy.members),
operators(copy.operators),
bannedMembers(copy.bannedMembers),
userLimit(copy.userLimit),
topicChange(copy.topicChange)
{
    *this = copy;
}

Channel &Channel::operator=(const Channel &other)
{
    if (this != &other)
    {
        inviteOnly = other.inviteOnly;
		privChannel = other.privChannel;
		password = other.password;
		ChannelName = other.ChannelName;
		members = other.members;
        operators = other.operators;
        bannedMembers = other.bannedMembers;
		userLimit = other.userLimit;
        topicChange = other.topicChange;
        // this->requiresAuth = other.requiresAuth;
    }
    return (*this);
}

Channel::~Channel(){
	members.clear();
	operators.clear();
	bannedMembers.clear();
	invited.clear();
};

int    Channel::addMember(Client &newMember)
{
    for (size_t i = 0; i < members.size(); i++)
        if (this->members[i] == &newMember)
            return (0); // returns error since member is already part of channel but doesnt stop execution
    this->members.push_back(&newMember);
    return (1);
}

std::string     Channel::getName()
{
    return (ChannelName);
}

std::string Channel::getTopic()
{
    return (_Topic);
}

void Channel::sendMsg(std::string &message, Client &sender)
{
    int senderFd = sender.getClientFd().fd;
    std::string senderMessage = "\033[35m[You] \033[0m" + message + "\n";
    
    message = "\n[" + sender.getNickname() + "] " + message + "\n";

    for (size_t i = 0; i < this->members.size(); i++)
    {
        if (members[i]->getClientFd().fd == senderFd)
            send(senderFd, senderMessage.c_str(), senderMessage.size(), 0);
        else
            send(members[i]->getClientFd().fd, message.c_str(), message.size(), 0);
    }
}

int    Channel::becomeChanOperator(Client &newOperator, int user) //might take away the int return
{
    std::string message;

    if (!operators.empty() && this->isOperator(&newOperator))
    {
        message = newOperator.getUsername() + " is already a channel operator\n";
        send(user, message.c_str(), message.size(), 0);
        return (0); // returns error since member is already channel operator but doesnt stop execution
    }
    this->operators.push_back(&newOperator);
    message = newOperator.getUsername() + " successfully became operator of " + this->getName() + "\n";
    if (!this->isMember(&newOperator))
        this->addMember(newOperator);
    return (1);
}

bool   Channel::isMember(Client *user)
{
    for(size_t i = 0; i < members.size(); i++)
    {
        if (user == members[i])
            return (true);
    }
    return (false);
}

bool   Channel::isMember(std::string &user, int check)
{
    (void)check;
    for(size_t i = 0; i < members.size(); i++)
    {
        if (user == members[i]->getNickname())
            return (true);
    }
    return (false);
}

bool   Channel::isMember(std::string &user)
{
    for(size_t i = 0; i < members.size(); i++)
    {
        if (user == members[i]->getUsername())
            return (true);
    }
    return (false);
}

bool   Channel::isMember(int user)
{
    for(size_t i = 0; i < members.size(); i++)
    {
        if (user == members[i]->getClientFd().fd)
            return (true);
    }
    return (false);
}

bool   Channel::isOperator(Client *user)
{
    for(size_t i = 0; i < operators.size(); i++)
    {
        if (user == operators[i])
            return (true);
    }
    return (false);
}

bool   Channel::isOperator(std::string &user)
{
    for(size_t i = 0; i < operators.size(); i++)
    {
        if (user == operators[i]->getUsername())
            return (true);
    }
    return (false);
}

bool   Channel::isOperatorNick(std::string &nick)
{
    for(size_t i = 0; i < operators.size(); i++)
    {
        if (nick == operators[i]->getNickname())
            return (true);
    }
    return (false);
}

bool   Channel::isOperator(int user)
{
    for(size_t i = 0; i < operators.size(); i++)
    {
        if (user == operators[i]->getClientFd().fd)
            return (true);
    }
    return (false);
}

bool Channel::isOperatorOnly()
{
    return (topicChange);
}

bool   Channel::isBanned(Client *user)
{
    for(size_t i = 0; i < bannedMembers.size(); i++)
    {
        if (user == bannedMembers[i])
            return (true);
    }
    return (false);
}

bool   Channel::isBanned(std::string &user)
{
    for(size_t i = 0; i < bannedMembers.size(); i++)
    {
        if (user == bannedMembers[i]->getUsername())
            return (true);
    }
    return (false);
}

bool   Channel::isBanned(int user)
{
    for(size_t i = 0; i < bannedMembers.size(); i++)
    {
        if (user == bannedMembers[i]->getClientFd().fd)
            return (true);
    }
    return (false);
}

void   Channel::showMembers(pollfd &destination)
{
    std::string memberList = "Channel " + this->getName() + ":\n";
    for (size_t i = 0; i < this->members.size(); i++)
    {
        if (members[i]->getUsername() != members[i]->getNickname())
        {
            if (this->isOperator(members[i]))
                memberList += "@" + members[i]->getNickname() + "(" + members[i]->getUsername() + ")";
            else
                memberList += members[i]->getNickname() + "(" + members[i]->getUsername() + ")";
        }
        else
        {
            if (this->isOperator(members[i]))
                memberList += "@" + members[i]->getUsername();
            else
                memberList += members[i]->getUsername();
        }
        memberList += "\n";
    }
    send(destination.fd, memberList.c_str(), memberList.size(), 0);
}

void    Channel::showOps(pollfd &destination)
{
    std::string opList = "Channel " + this->getName() + ":\n";
    for (size_t i = 0; i < this->operators.size(); i++)
    {
        if (operators[i]->getUsername() != operators[i]->getNickname())
            opList += "[op] " + operators[i]->getNickname() + "(" + operators[i]->getUsername() + ")";
        else
            opList += "[op] " + operators[i]->getUsername();
        opList += "\n";
    }
    send(destination.fd, opList.c_str(), opList.size(), 0);
}

std::vector<Client*> &Channel::getMembers()
{
    return (this->members);
}

bool        Channel::isPrivChannel()
{
    return (privChannel);
}

bool        Channel::isInviteOnly()
{
    return (inviteOnly);
}

bool        Channel::isFull()
{
    if (userLimit == 0)
        return (false);
    return (members.size() >= userLimit);
}

bool        Channel::passwordMatched(const std::string &attempt)
{
    return (attempt == password);
}

void Channel::setInviteOnly(int i, const std::string mode)
{
    if (mode == "+i")
    {
        inviteOnly = true;
        std::string message = "Channel is now invite only\n";
        send(i, message.c_str(), message.size(), 0);
    }
    else
    {
        inviteOnly = false;
        std::string message = "Channel is now not invite only\n";
        send(i, message.c_str(), message.size(), 0);
    }
}

void Channel::changePassword(const std::string &flag, const std::string &pass, int i)
{
    if (flag == "-k")
    {
        privChannel = false;
        std::string message = "Channel <" + ChannelName + "> is now public\n";
        send(i, message.c_str(), message.size(), 0);
    }
    else if (pass.empty())
    {
        std::string message = "No password was provided. Channel will stay public\n";
        send(i, message.c_str(), message.size(), 0);
    }
    else
    {
        password = pass;
        privChannel = 1;
        std::string message = "Channel is now Private\nPassword changed to: " + pass + "\n";
        send(i, message.c_str(), message.size(), 0);
    }
}

void Channel::changeTopicPrivelage(const std::string mode, int i)
{
    if (mode == "-t")
    {
        if (topicChange == 1)
        {
            std::string message = "Topic is already public. Any user can change it.\n";
            send(i, message.c_str(), message.size(), 0);
        }
        else
        {
            std::string message = "Topic is now public. All users can change the topic.\n";
            send(i, message.c_str(), message.size(), 0);
            topicChange = 1;
        }
    }
    else
    {
        if (topicChange == 0)
        {
            std::string message = "Topic is already restricted. Only operators can change it.\n";
            send(i, message.c_str(), message.size(), 0);
        }
        else
        {
            std::string message = "Topic changes are now restricted to channel operators only.\n";
            send(i, message.c_str(), message.size(), 0);
            topicChange = 0;
        }
    }
}
void Channel::changeTopic(const std::string topic, int i)
{
    std::string message = "topic changed to: " + topic + "\n";
    send(i, message.c_str(), message.size(), 0);
    _Topic = topic;
}

void Channel::changeLimit(const std::string &flag, const std::string &lim, int i)
{
    if (flag == "+o")
    {
        if (lim.empty())
        {
            std::string message = "limit was not changed\n";
            send(i, message.c_str(), message.size(), 0);
        }
        else
        {
            std::string message;
            std::stringstream ss(lim);
            int num;
            ss >> num;
            if (num < 0)
                message = "Member limit must be a positive number\n";
            else
            {
                userLimit = num;
                message = "Member limit changed to: " + lim + "\n";
            }
            send(i, message.c_str(), message.size(), 0);
        }
    }
    else
        userLimit = 0;
}
void Channel::changeOperatorPrivelage(std::string client, int i, const std::string mode)
{
    if (client.empty())
    {
        std::string message = "no client was stated\n";
        send(i, message.c_str(), message.size(), 0);
    }
    else
    {
        bool check = 0;
        std::stringstream ss(client);
        int num;
        size_t n;
        ss >> num;
        // if (!operators.empty() && mode != "+o" && (isOperator(client) || isOperator(num) || isOperatorNick(client) == 1 || mode == "-o"))
        if (mode == "-o")
        {
            for (n = 0; n < operators.size(); n++)
            {
                if (operators[n]->getNickname() == client)
                {
                    removeOperator(operators[n]);
                    std::string message = "operator privileges have been taken away from: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
                else if (operators[n]->getUsername() == client)
                {
                    removeOperator(operators[n]);
                    std::string message = "operator privileges have been taken away from: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
                else if ((operators[n]->getClientFd().fd) == num)
                {
                    removeOperator(operators[n]);
                    std::string message = "operator privileges have been taken away from: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
                if (n + 1 == operators.size())
                    check = 1;
            }
            if (isMember(client, 1) == false && n > operators.size())
            {
                std::string message = "client: " + client + " is not a member\n";
                send(i, message.c_str(), message.size(), 0);
            }
            else if (n >= operators.size() && check == 1)
            {
                std::string message = "client: " + client + " is not an operator\n";
                send(i, message.c_str(), message.size(), 0);
            }
        }
        else
        {
            size_t n;
            for (n = 0; n < members.size(); n++)
            {
                if (members[n]->getNickname() == client && !isOperatorNick(client))
                {
                    operators.push_back(members[n]);
                    std::string message = "operator privileges have been granted to: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
                else if (members[n]->getUsername() == client && !isOperator(client))
                {
                    operators.push_back(members[n]);
                    std::string message = "operator privileges have been granted to: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
                else if ((members[n]->getClientFd().fd) == num && !isOperator(num))
                {
                    operators.push_back(members[n]);
                    std::string message = "operator privileges have been granted to: " + client + "\n";
                    send(i, message.c_str(), message.size(), 0);
                    break;
                }
            }
            if (n >= members.size())
            {
                for (n = 0; n < members.size(); n++)
                {
                    if (members[n]->getNickname() == client)
                    {
                        std::string message = client + " is already an operator\n";
                        send(i, message.c_str(), message.size(), 0);
                        break;
                    }
                    else if (members[n]->getUsername() == client)
                    {
                        std::string message = client + " is already an operator\n";
                        send(i, message.c_str(), message.size(), 0);
                        break;
                    }
                    else if ((members[n]->getClientFd().fd) == num)
                    {
                        std::string message = client + " is already an operator\n";
                        send(i, message.c_str(), message.size(), 0);
                        break;
                    }
                }
                if (n >= members.size())
                {
                    std::string message = "client not found\n";
                    send(i, message.c_str(), message.size(), 0);
                }
            }
        }
    }
}
void Channel::sendInvite(Client *client)
{
    invited.push_back(client);
}
void Channel::removeMember(Client *client)
{
    for (std::vector<Client *>::iterator it = members.begin(); it != members.end(); ++it)
    {
        if (*it == client)
        {
            members.erase(it);
            break;
        }
    }
}

void Channel::removeOperator(Client *client)
{
    for (std::vector<Client *>::iterator it = operators.begin(); it != operators.end(); ++it)
    {
        if (*it == client)
        {
            operators.erase(it);
            break;
        }
    }
}

bool    Channel::isInvited(Client *client)
{
    for (std::vector<Client*>::iterator it = invited.begin(); it != invited.end(); ++it)
    {
        if (*it == client)
        {
            invited.erase(it); // correct: erasing by iterator
            return true;
        }
    }
    return false;
}
