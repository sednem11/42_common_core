/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:57:32 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/28 17:00:41 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"
#include "helper.cpp"

//_______________________________________________________________________//
//                                                                       //
//                                 BOT                                   //
//_______________________________________________________________________//

void    sendJoke(std::string joke, std::string punchLine, int fd)
{
    send(fd, joke.c_str(), joke.size(), 0);
    sleep(1);
    send(fd, ".\n", 2, 0);
    sleep(1);
    send(fd, ".\n", 2, 0);
    sleep(1);
    send(fd, punchLine.c_str(), punchLine.size(), 0);
}

void	Server::doJoke(int i)
{
	std::srand(std::time(0));

    int numero = std::rand() % 8;
	switch(numero)
	{
		case 0:
        sendJoke("Why was the code sad?\n", "Because it had to many Bugs\n\n", clientPollPtrs[i].fd);
		break;
		
		case 1:
        sendJoke("How many Programmers are needed to change a light bulb?\n", "None. Thats a hardware problem\n\n", clientPollPtrs[i].fd);
		break;
        
		case 2:
        sendJoke("Whats a Programmer in the beach?\n", "A Bug in Production\n\n", clientPollPtrs[i].fd);
		break;

		case 3:
        sendJoke("Whats the Devil's favorite Language?\n","Assembly... Because its always on the Hells low level\n\n", clientPollPtrs[i].fd);
		break;

		case 4:
        sendJoke("What did the compiler say to the Bad written Code?\n", "you dont even deserve the Main()\n\n", clientPollPtrs[i].fd);
		break;

		case 5:
        sendJoke("How does a programmer end his/her relationship?\n", "git commit -m \"It's not you, it's me\"\n\n", clientPollPtrs[i].fd);
		break;

		case 6:
        sendJoke("What did the HTML say to CSS?\n", "Without you I have no Style!!\n\n", clientPollPtrs[i].fd);
		break;
		
		case 7:
        sendJoke("What happens if you mix a programmer and a designer?\n", "A Commit full of conflicts\n\n", clientPollPtrs[i].fd);
		break;
	}
}

//_______________________________________________________________________//
//                                                                       //
//                             COMMAND HANDLER                           //
//_______________________________________________________________________//


void    Server::registerCmd(int i)
{
    char buffer[6000];

    int bytesReceived = recv(clientPollPtrs[i].fd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytesReceived == 0)
    {
        std::cerr << "[Server] Client " << clientPollPtrs[i].fd << " disconnected." << std::endl;
        removeUser(clientPollPtrs[i].fd);
        clientPollPtrs.erase(clientPollPtrs.begin() + i);
        i--;
    }
    else if (bytesReceived < 0)
    {
        std::cerr << "[Server] recv() error on socket " << clientPollPtrs[i].fd << std::endl << "Client may have been closed before full registration\n";
        close(clientPollPtrs[i].fd);
        clientPollPtrs.erase(clientPollPtrs.begin() + i);
        i--;
    }
    else
    {
        std::string cmd = buffer;
        buffer[bytesReceived] = '\0';
        if (!users[i - 1].getAuthenticated() && cmd.find("CAP LS 302") != std::string::npos)
        {
            std::string buf = buffer;
            handleHCClientInfo(buf, users[i - 1], i);
        }
        if(!users[i - 1].getNickname().empty() && !users[i - 1].getUsername().empty() && users[i - 1].getNickSet() && users[i - 1].getPassSet() && users[i - 1].getUserSet())
            users[i - 1].setAuthenticated();
        if (bytesReceived > 0 && cmd.find('\n') != std::string::npos)
        {
            if(cmd.find("\n") != std::string::npos)
            {
                users[i - 1].setHandle(users[i - 1].getHandle() + cmd);
                cmd = users[i - 1].getHandle();
                users[i - 1].setHandleNull();
            }
            trimNewline(cmd);
            std::istringstream ss(cmd);
            std::string command;
            ss >> command;
            
            std::transform(command.begin(), command.end(), command.begin(), ::toupper);
            if (command == "CAP")
                ;
            else if (command == "HELP")
            {
                const std::string helpMsg =
                "=============================\n"
                " IRC SERVER COMMANDS - HELP \n"
                "=============================\n"
                "\n"
                "General Commands:\n"
                "-----------------\n"
                "HELP        -> Show this help message\n"
                "EXIT        -> Leave the server\n"
                "QUIT        -> Disconnect from the server\n"
                "PROFILE     -> Show your username and nickname\n"
                "\n"
                "User Identity:\n"
                "--------------\n"
                "USER <name> -> Set your username\n"
                "NICK <name> -> Set your nickname\n"
                "\n"
                "Channel Management:\n"
                "-------------------\n"
                "CHANNELS    -> Show available channels\n"
                "ADD <#name> -> Create a new channel\n"
                "JOIN <#name> -> Join an existing channel\n"
                "MODE <#channel> <mode> [pass] -> Change channel mode\n"
                "TOPIC <#channel> [new_topic] -> View or set the channel topic (operator only)\n"
                "INVITE <#channel> <user> -> Invite a user to the channel (operator only)\n"
                "\n"
                "Communication:\n"
                "--------------\n"
                "PRIVMSG <#channel|user> :<message> -> Send a private message to a channel or user\n"
                "\n"
                "Information:\n"
                "------------\n"
                "LIST        -> List all available channels and their info\n"
                "NAMES <#channel> -> Show member nicknames and status in a channel\n"
                "WHO [name]  -> Show who is on the server or in a channel\n"
                "WHOIS <name> -> Get detailed information about a user\n"
                "\n"
                "Admin:\n"
                "------\n"
                "DIE         -> Shut down the server (server operators only)\n";            
                send(clientPollPtrs[i].fd, helpMsg.c_str(), helpMsg.size(), 0);
            }
            else if (command == "PONG")
            {
                std::string token;
                ss >> token;
                std::string message = "PONG " + token + "\r\n";
                if (token == ":" + ipAddress)
                    lastPongTime[i] = time(0);
                else
                {
                    message = "wrong Pong message\n";
                    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
                }
            }
            else if (command == "MODE" && users[i - 1].getAuthenticated())
            {
                std::string channel;
                ss >> channel;
                std::string mode;
                ss >> mode;
                std::string pass;
                ss >> pass;
                std::map<std::string, Channel>::iterator it = channels.find(channel);
                if (it != channels.end())
                    modeChange(it->second, mode, pass, i);
                else
                {
                    std::string message = "Error: could not find Channel\n";
                    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
                }
            }
            else if (command == "TOPIC" && users[i - 1].getAuthenticated())
            {
                std::string full;
                std::getline(ss, full);
                if (!full.empty())
                    handleTopic(full, i);
            }
            else if (command == "INVITE" && users[i - 1].getAuthenticated())
            {
                std::string channel;
                ss >> channel;
                std::string client;
                ss >> client;
                handleInvite(channel, client, i);
            }
            else if (command == "PROFILE" && users[i - 1].getAuthenticated())
            {
                std::string message = "USERNAME: " + users[i - 1].getUsername() + "\nNICKNAME: " + users[i - 1].getNickname() + "\n";
                send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
            }
            else if (command == "PASS" && !users[i - 1].getPassSet())
            {
                std::string password;
                ss >> password;
                if(password == _password)
                {
                    users[i - 1].setisPass();
                    send(clientPollPtrs[i].fd, "Welcome Mr.User\n", 16, 0);
                }
                else if(password == OPERATOR_PASSWORD)
                {
                    users[i - 1].setisPass();
                    users[i - 1].becomeOperator();
                    send(clientPollPtrs[i].fd, "Welcome Mr.Operator\n", 20, 0);
                }
                else
                {
                    std::string nickOrStar = users[i - 1].getNickSet() ? users[i - 1].getNickname() : "*";
                    std::string message = ":" + ipAddress + " 464 " + nickOrStar + " :Password incorrect\r\n";
                    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
                }
            }
            else if (command == "NICK" && users[i - 1].getPassSet())
            {
                std::string newNickname;
                ss >> newNickname;
                handleNick(newNickname, i);
            }
            else if (command == "USER" && users[i - 1].getPassSet()/*  && users[i - 1].getNickSet() */)
            {
                std::string newUsername;
                ss >> newUsername;
                std::string useless1;
                ss >> useless1;
                std::string useless2;
                ss >> useless2;
                std::string realName;
                ss >> realName;
                handleUser(newUsername, realName, i);
            }
            else if(command == "JOIN" && users[i - 1].getAuthenticated())
            {
                std::string full;
                std::getline(ss, full);
                joinChannel(full, i);
            }
            else if (command == "PART" && users[i - 1].getAuthenticated())
            {
                std::string channelLeft;
                std::getline(ss, channelLeft);
                leaveChannel(channelLeft, i);
            }
            else if (command == "PRIVMSG" && users[i - 1].getAuthenticated())
            {
                std::string destination, temp, message;
                ss >> destination;
                bool first = true;
                while (ss >> temp)
                {
                    if (temp[0] == ':' && first) // remove leading colon only once
                        temp = temp.substr(1);
                    if (!first)
                        message += " ";
                    message += temp;
                    first = false;
                }
                trim(message);
                handlePrivMsg(destination, message, i);
            }
            else if ((command == "WHO" || command == "WHOIS") && users[i - 1].getAuthenticated())
            {
                std::string full;
                std::getline(ss, full);
                handleWHOandWHOIS(command, full, i);
            }
            else if (command == "KICK" && users[i - 1].getAuthenticated())
            {
                std::string full;
                std::getline(ss, full);
                kickUser(full, i);
            }
            else if (command == "LIST" && users[i - 1].getAuthenticated())
            {
                std::string full;
                std::getline(ss, full);
                handleList(full, i);
            }
            else if (command == "NAMES" && users[i - 1].getAuthenticated()) // make sure private servers or invitation only svrs dont show members, only names and status
            {
                std::string channel;

                ss >> channel;
                handleNames(channel, i);
            }
            else if(command == "DIE" && users[i - 1].getAuthenticated())
            {
                if (!users[i - 1].isOperator())
                {
                    std::string message = "Only Server operators can use this command\n";
                    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
                }
                else
                    shutdownServer();
            }
            else if (command == "QUIT" && users[i - 1].getAuthenticated())
            {
                // removeUser(i - 1);
                std::cerr << "[Server] Client " << clientPollPtrs[i].fd << " disconnected." << std::endl;
                // close(clientPollPtrs[i].fd);
                removeUser(clientPollPtrs[i].fd);
                clientPollPtrs.erase(clientPollPtrs.begin() + i);
                i--; // Adjust loop index after removal
                
            }
            else if (command == "OPER" && users[i - 1].getAuthenticated()) // become server operator
            {
                if (!users[i - 1].isOperator())
                    operatorAuth(i);
                else
                {
                    std::string message = "You are already an Operator\n";
                    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
                }
            }
            else if (command == "JOKE" && users[i - 1].getAuthenticated())
                doJoke(i);
            else
            {
                std::string message = ":" + ipAddress + " 421 " + users[i - 1].getNickname() + " " + command + " :Unknown command\r\n";
                send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
            }
            memset(buffer, 0, sizeof(buffer));
        }
        else if(bytesReceived > 0 && cmd.find('\n') == std::string::npos)
        {
            std::string temp = users[i - 1].getHandle();
		    users[i - 1].setHandle(temp + cmd);
            memset(buffer, 0, sizeof(buffer));
            cmd.clear();
        }
    }
}
