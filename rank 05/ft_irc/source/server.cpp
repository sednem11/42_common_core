/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:11:36 by yohan             #+#    #+#             */
/*   Updated: 2025/05/28 17:01:14 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"
#include "handleCommand.cpp"

Server::Server(std::string Port, std::string attempt) : 
serverSocket(-1), 
Sentry(), 
ipAddress(), 
channels(), 
users(), 
clientPollPtrs()
{
        Sentry.validatePort(Port);
        port = Sentry.getPort();
		_password = attempt;
}

Server::Server(const Server &copy)
{
    *this = copy;
}

Server &Server::operator=(const Server &other)
{
    if (this != &other)
    {
        this->port = other.port;
        this->serverSocket = other.serverSocket;
        this->Sentry = other.Sentry;
        this->serverPollfd = other.serverPollfd;
        this->channels = other.channels;
        this->users = other.users;
        this->clientPollPtrs = other.clientPollPtrs;
        this->ipAddress = other.ipAddress;
    }
    return (*this);
}

Server::~Server()
{
    for (size_t i = 0; i < clientPollPtrs.size(); i++)
    {
        close(clientPollPtrs[i].fd);
        clientPollPtrs.erase(clientPollPtrs.begin() + i);
        i--; // Adjust loop index after removal
    }
    std::cout << "Thank you for using this server. Come again soon!\n";
}

//_______________________________________________________________________//
//                                                                       //
//                         SERVER INITIALIZATION                         //
//_______________________________________________________________________//


void Server::initializeServer()
{
    struct sockaddr_in serverAddress;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) // Fix: socket() returns -1 on failure, not 0
    {
        std::cerr << "[initializeServer] Socket creation failed: " << std::endl;
        throw std::runtime_error("Socket error");
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "[initializeServer] setsockopt failed: " << std::endl;
        close(serverSocket);
        throw std::runtime_error("setsockopt error");
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT_ID);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        std::cerr << "[initializeServer] Binding failed: " << std::endl;
        close(serverSocket);
        throw std::runtime_error("Binding error");
    }

    if (listen(serverSocket, SOMAXCONN) < 0)
    {
        std::cerr << "[initializeServer] Listening failed: " << std::endl;
        close(serverSocket);
        throw std::runtime_error("Listening error");
    }
    std::cout << "[initializeServer] Server started on port " << PORT_ID << std::endl;

    serverPollfd.fd = serverSocket;
    serverPollfd.events = POLLIN;
    serverPollfd.revents = 0;
    clientPollPtrs.push_back(serverPollfd);

    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    if (getsockname(clientPollPtrs[0].fd, (struct sockaddr *)&local_addr, &addr_len) == -1)
        perror("getsockname failed");
    else
    {
        ipAddress = inet_ntoa(local_addr.sin_addr);
        std::cout << "Server is bound to " << ipAddress << ":" << ntohs(local_addr.sin_port) << std::endl;
    }
    while (1)
    {
        int event = poll(clientPollPtrs.data(), clientPollPtrs.size(), 1000);
        if (event < 0)
        {
            std::cerr << "[initializeServer] Poll error: " << std::endl;
            continue;
        }
        if (clientPollPtrs[0].revents & POLLIN)
        {
            acceptNewClient();
            std::cout << clientPollPtrs.back().fd << " Joined\n";
		}
        for (size_t i = 1; i < clientPollPtrs.size(); i++)
        {
            sendPing(i);
            if (clientPollPtrs[i].revents & POLLIN)
                registerCmd(i);
        }
    }
}

void    Server::acceptNewClient()
{
    struct sockaddr_in newClientAddr;
    socklen_t          addr_len = sizeof(newClientAddr);

    int socket = accept(serverSocket, (struct sockaddr *)&newClientAddr, &addr_len);
    if (socket < 0)
        throw std::runtime_error("Error accepting inbound connection");
    Client newClient(socket);
    
    std::string welcome = "Welcome!\n";
    send(newClient.getClientFd().fd, welcome.c_str(), welcome.size(), 0);
    users.push_back(newClient);
    clientPollPtrs.push_back(newClient.getClientFd());
}

void    Server::removeUser(int fd)
{
    for (size_t i = 0; i < users.size(); i++)
	{
        if (fd == users[i].getClientFd().fd)
        {
            std::map<std::string, Channel>::iterator it;
            for (it = channels.begin(); it != channels.end(); ++it)
            {
                it->second.removeOperator(&users[i]);
                it->second.removeMember(&users[i]);
            }
            close(users[i].getClientFd().fd);
			users.erase(users.begin() + i);

            return ;
        }
	}
}

void Server::shutdownServer()
{
    std::cout << "Closing all client connections..." << std::endl;
    for (size_t i = 0; i < clientPollPtrs.size(); i++)
        close(clientPollPtrs[i].fd);

    close(serverSocket);
    std::cout << "Server shut down successfully." << std::endl;
	Server::~Server();
	exit(0);
}

//_______________________________________________________________________//
//                                                                       //
//                         HEXCHAT COMPATIBILITY                         //
//_______________________________________________________________________//


void Server::handleJoin(Client &newClient, Channel *channel)
{
    std::vector<Client *> members = channel->getMembers();
    std::string channelName = channel->getName();
    std::string nick = newClient.getNickname();
    std::string user = newClient.getUsername();
    std::string host = newClient.getClientIP();
    int clientFd = newClient.getClientFd().fd;

    std::string joinMsg = ":" + nick + "!" + user + "@" + host + " JOIN :" + channelName + "\r\n";
    for (size_t i = 0; i < members.size(); ++i)
    {
        send(members[i]->getClientFd().fd, joinMsg.c_str(), joinMsg.size(), 0);
    }

    std::string nameList;
    for (size_t i = 0; i < members.size(); ++i)
    {
        std::string addition = channel->isOperator(members[i]->getClientFd().fd) ? "@" + members[i]->getNickname() : members[i]->getNickname();
        nameList += addition;
        if (i != members.size() - 1)
            nameList += " ";
    }
    std::string namesReply = ":" + ipAddress + " 353 " + nick + " = " + channelName + " :" + nameList + "\r\n";
    send(clientFd, namesReply.c_str(), namesReply.size(), 0);
    std::string endNames = ":" + ipAddress + " 366 " + nick + " " + channelName + " :End of /NAMES list.\r\n";
    send(clientFd, endNames.c_str(), endNames.size(), 0);
}


void    Server::handleHCClientInfo(std::string &buffer, Client &client, int i)
{
    std::vector<std::string> prompts = split(buffer, '\n');
    
    for (size_t j = 0; j < prompts.size(); j++)
    {
        std::vector<std::string> indiv = split(prompts[j], ' ');
        if (indiv.size() < 2)
            continue ;
        trimNewline(indiv[1]);
        if (indiv[0] == "USER")
		{
            client.setUsername(indiv[1]);
			client.setisUser();
		}
        if (indiv[0] == "NICK")
		{
            handleNick(indiv[1], i);
			client.setisNick();
		}
		if (indiv[0] == "PASS")
			checkPassword(indiv[1], client);
    }
}

void    Server::handleMode(Channel &channel, const std::string &mode, std::string pass, int fd)
{
    Client *client;
    
    for (size_t i = 0; i < users.size(); i++)
        if (users[i].getClientFd().fd == fd)
            client = &users[i];
    if (!client)
        return ;    

    std::string full = ":" + client->getNickname() + "!" + client->getUsername() + "@" + ipAddress
        + " MODE " + channel.getName() + " " + mode;
    if (!pass.empty())
        full += (" " + pass);
    full += "\r\n";
    
    std::vector <Client *> *it = &channel.getMembers();
    for (size_t i = 0; i < it->size(); i++)
        send(it->at(i)->getClientFd().fd, full.c_str(), full.size(), 0);
}

void Server::handleNick(std::string &newNickname, int i)
{
    std::string message;
    Client &currentClient = getClientByFd(clientPollPtrs[i].fd);

    if (newNickname.empty())
    {
        std::string nickOrStar = currentClient.getNickname().empty() ? "*" : currentClient.getNickname();
        message = ":" + ipAddress + " 431 " + nickOrStar + " :No nickname given\r\n";
        send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
        return;
    }
    for (std::deque<Client>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (it->getClientFd().fd == currentClient.getClientFd().fd)
            continue; // skip self
        if (it->getNickname() == newNickname)
        {
            std::string nickOrStar = currentClient.getNickname().empty() ? "*" : currentClient.getNickname();
            message = ":" + ipAddress + " 433 " + nickOrStar + " " + newNickname + " :Nickname is already in use\r\n";
            send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
            return;
        }
    }
    std::string oldNick = currentClient.getNickname();
    currentClient.setNickname(newNickname);

    std::string nickSource = (oldNick.empty() ? newNickname : oldNick);
    message = ":" + nickSource + "!" + currentClient.getUsername() + "@" + ipAddress + " NICK :" + newNickname + "\r\n";
    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);

    if (!currentClient.sentWelcome() && !currentClient.getUsername().empty())
    {
        message = ":" + ipAddress + " 001 " + newNickname + " :Welcome to the Internet Relay Network " + newNickname + "!" + currentClient.getUsername() + "@" + ipAddress + "\r\n";
        send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
        currentClient.setWelcomed(true);
    }
    if (!users[i - 1].getNickSet())
        users[i - 1].setisNick();
}

void	Server::handleUser(std::string &newUsername, std::string &realName,int i)
{
	bool isRepeated = false;
	std::string message;
	std::deque<Client>::iterator it;
	
	if(newUsername == "" || realName[0] != ':')
	{
		if(newUsername == "")
		{
			message = "UserName can't be Empty\n";
			send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
		}
		else
		{
			message = "RealName has to start with ':'\nUsage: USER <username> <*> <*> :<Realname>\n";
			send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
		}
	}
	else
	{
		for(it = users.begin(); it != users.end(); ++it)
		{
			if(newUsername == it->getUsername())
			{
				isRepeated = true;
				break ;
			}
		}
		if(!isRepeated)
		{
			users[i - 1].setUsername(newUsername);
			users[i - 1].setRealname(realName);
            users[i - 1].setisUser();
			message = "Successfully set UserName to " + users[i - 1].getUsername() + "\nSuccessfully set RealName to " + users[i - 1].getRealname() + "\n";
			send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
		}
		else
		{
			message = "UserName Already in Use\n";
			send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
		}
	}
}

void	Server::handlePrivMsg(std::string &destination, std::string &message, int i)
{
	if (isChannel(destination))
    {
        std::map<std::string, Channel>::iterator channel = channels.find(destination);
        if (channel == channels.end())
        {
            std::string msg = "Error: Channel not found\n";
            send(users[i - 1].getClientFd().fd, msg.c_str(), msg.size(), 0);
        }
        else
        {
            if (users[i - 1].isOperator() || channel->second.isMember(users[i - 1].getClientFd().fd))
                sendMsg(users[i - 1], channel->second, message);
            else
            {
                std::string msg = "Error: You are not part of this channel\n";
                send(users[i - 1].getClientFd().fd, msg.c_str(), msg.size(), 0);
            }
        }
    }
    else
    {
        for (size_t receiver = 0; receiver < users.size(); receiver++)
        {
            if (users[receiver].getNickname() == destination || users[receiver].getUsername() == destination)
                sendMsg(users[i - 1], users[receiver], message);
            if (receiver == users.size())
            {
                std::string msg = "Error: User not found\n";
                send(users[i - 1].getClientFd().fd, msg.c_str(), msg.size(), 0);
            }
        }
    }
}

void Server::handleWHOIS(Client *requestedUser, Client *requester)
{
    std::string threeEleven = ":" + ipAddress + " 311 " + requester->getNickname() + " " + requestedUser->getNickname() + " "
        + requestedUser->getUsername() + " " + requestedUser->getClientIP() + " * :" + requestedUser->getUsername() + "\r\n";
    std::string threeTwelve = ":" + ipAddress + " 312 " + requester->getNickname() + " " + requestedUser->getNickname() + " "
        + ipAddress + " :IRC look-alike\r\n";
    std::string threeThirteen = ":" + ipAddress + " 313 " + requester->getNickname() + " " + requestedUser->getNickname()
        + " :is an IRC operator\r\n";
    std::string chan;
    for (std::map<std::string, Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (it->second.isMember(requestedUser))
        {
            chan += it->second.getName();
            chan += " ";
        }
    }
    std::string threeNineteen = ":" + ipAddress + " 319 " + requester->getNickname() + " " + requestedUser->getNickname() + " :"
        + chan  + "\r\n";
    std::string threeEighteen = ":" + ipAddress + " 318 " + requester->getNickname() + " " + requestedUser->getNickname()
        + " :End of /WHOIS list\r\n";
    std::string full = threeEleven + threeTwelve;
    if (requestedUser->isOperator())
        full += threeThirteen;
    full += threeNineteen + threeEighteen;
    send(requester->getClientFd().fd, full.c_str(), full.size(), 0);
}

void    Server::handleWHO(Channel *requestedChannel, Client *requester)
{
    std::string full;
    std::string info;

    if (requestedChannel->isPrivChannel() && !requestedChannel->isMember(requester))
        return;

    std::vector<Client*> members = requestedChannel->getMembers();
    for (size_t i = 0; i < members.size(); i++)
    {
        info = "H";
        if (members[i]->isOperator())
            info += "*";
        if (requestedChannel->isOperator(members[i]))
            info += "@";
        info += " :0 ";
        
        full += (":" + ipAddress + " 352 " + requester->getNickname() + " " + requestedChannel->getName() + " "
            + members[i]->getUsername() + " " + members[i]->getClientIP() + " IRC look-alike " + members[i]->getNickname() + " "
            + info + members[i]->getUsername() + "\r\n");
    }
    full += (":" + ipAddress + " 315 " + requester->getNickname() + " " + requestedChannel->getName()
    + " :End of /WHO list\r\n");
    send(requester->getClientFd().fd, full.c_str(), full.size(), 0);
}


void    Server::handleList(std::string &input, int user)
{
    std::string message;
    Client *requester = &users[user - 1];

    if (!input.empty())
    {
        message = "Error: List does not require arguments\n";
        send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
        return ;
    }
    std::string threeTwentyOne = ":" + ipAddress + " 321 " + requester->getNickname() + " Channel :Users name\r\n";
    std::string threeTwentyTwo;
    std::map<std::string, Channel>::iterator chan;
    for (chan = channels.begin(); chan != channels.end(); ++chan)
    {
        size_t userCount = chan->second.getMembers().size();
        std::stringstream ss;
        ss << userCount;
        std::string userCountStr = ss.str();
        threeTwentyTwo += (":" + ipAddress + " 322 " + requester->getNickname() + " "
            + chan->second.getName() + " " + userCountStr + " :" + chan->second.getTopic() + "\r\n");
    }
    std::string threeTwentyThree = ":" + ipAddress + " 323 " + requester->getNickname() + " :End of /LIST\r\n";
    message = threeTwentyOne + threeTwentyTwo + threeTwentyThree;
    send(requester->getClientFd().fd, message.c_str(), message.size(), 0);
}

void    Server::sendMsg(Client &sender, Client &receiver, const std::string &msg) //for client
{
    std::string fullMsg = ":" + sender.getUsername() + "!" + sender.getNickname() + "@"
    + sender.getClientIP() + " PRIVMSG " + receiver.getNickname() + " :" + msg + "\r\n";
    send(receiver.getClientFd().fd, fullMsg.c_str(), fullMsg.size(), 0);
}

void    Server::sendMsg(Client &sender, Channel &receiver, const std::string &msg) //for channel
{
    std::vector< Client *> members = receiver.getMembers();

    std::string fullMsg = ":" + sender.getNickname() + "!" + sender.getUsername() + "@"
    + sender.getClientIP() + " PRIVMSG " + receiver.getName() + " :" + msg + "\r\n";

    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i]->getClientFd().fd == sender.getClientFd().fd)
            continue ;
        send(members[i]->getClientFd().fd, fullMsg.c_str(), fullMsg.size(), 0);
    }
}


//_______________________________________________________________________//
//                                                                       //
//                                 OTHER                                 //
//_______________________________________________________________________//


void Server::handleCC(int signal)
{
	(void)signal;
	std::cout << std::endl;
	shutdownServer();
}


void Server::sendPing(int i)
{
    if (i >= (int)lastPingTime.size())
    {
        lastPingTime.resize(i + 1, 0);
        elapsed.resize(i + 1, -1);
    }
    if (i >= (int)lastPongTime.size())
        lastPongTime.resize(i + 1, 0);
    time_t now = time(0);
    if (lastPingTime[i] != 0)
        elapsed[i] = difftime(now, lastPingTime[i]);
    if (lastPongTime[i] < lastPingTime[i] && elapsed[i] >= 300)
    {
        std::string message = "you are Dead\n";
        std::cout << "[Server] Client " <<  clientPollPtrs[i].fd << " disconnected." << std::endl;
        send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
        // removeUser(i - 1);
        // close(clientPollPtrs[i].fd);
        removeUser(clientPollPtrs[i].fd);
        lastPingTime.clear();
        lastPongTime.clear();
        clientPollPtrs.erase(clientPollPtrs.begin() + i);
        lastPingTime[i] = 0;
        lastPongTime[i] = 0;
    }
    if (elapsed[i] == -1 || elapsed[i] >= 300)
    {
        std::string message = "PING :" + ipAddress + "\r\n";
        send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
        lastPingTime[i] = time(0);
    }
}

void	Server::checkPassword(std::string &pass, Client &client)
{
	if(pass == _password)
	{
		client.setisPass();
		client.setRole(USER);
	}
	else
	{
		std::string message = "Wrong Password";
		send(client.getClientFd().fd, message.c_str(), message.size(), 0);
	}
}

void Server::modeChange(Channel &channel, const std::string &mode, const std::string pass, int i)
{
    Client *client;
    int fd = clientPollPtrs[i].fd;
    
    for (size_t i = 0; i < users.size(); i++)
        if (users[i].getClientFd().fd == fd)
            client = &users[i];
    if(channel.isOperator(clientPollPtrs[i].fd))
    {
        if (mode == "+i" || mode == "-i")
        {
            channel.setInviteOnly(fd, mode);
            handleMode(channel, mode, "", fd);
        }
        else if (mode == "-t" || mode == "+t")
        {
            channel.changeTopicPrivelage(mode, fd);
            handleMode(channel, mode, "", fd);
        }
        else if (mode == "+k" || mode == "-k")
        {
            channel.changePassword(mode, pass, fd);
            handleMode(channel, mode, pass, fd);
        }
        else if (mode == "+o" || mode == "-o")
        {
            channel.changeOperatorPrivelage(pass, fd, mode);
            handleMode(channel, mode, pass, fd);
        }
        else if (mode == "+l" || mode == "-l")
        {
            channel.changeLimit(mode, pass, fd);
            handleMode(channel, mode, pass, fd);
        }
        else
        {
            std::string message = ":" + ipAddress + " 472 " + client->getNickname() + " " + channel.getName() + " " + mode + " :Unknown mode\r\n";
            send(fd, message.c_str(), message.size(), 0);
        }
    }
    else
    {
        std::string message = ":" + ipAddress + " 482 " + client->getNickname() + " " + channel.getName() + " :You are not a channel operator\r\n";
        send(fd, message.c_str(), message.size(), 0);
    }
}

void    Server::operatorAuth(int user)
{
    std::string prompt = "Enter password: ";
    send(clientPollPtrs[user].fd, prompt.c_str(), prompt.size(), 0);

    char buffer[6000];
    memset(buffer, 0, sizeof(buffer));

    int bytesReceived = recv(clientPollPtrs[user].fd, buffer, sizeof(buffer) - 1, 0);
    std::string cmd = buffer;
    if (bytesReceived > 0) 
    {
        std::string prompt;
        trimNewline(cmd);
        if (cmd == OPERATOR_PASSWORD)
        {
            users[user - 1].becomeOperator();
            prompt = "Successfully changed role to: Server operator\n";
        }
        else
            prompt = "Invalid password\n";
        send(clientPollPtrs[user].fd, prompt.c_str(), prompt.size(), 0);
    }
}

Client &Server::getClientByFd(int fd)
{
    for (size_t j = 0; j < users.size(); ++j)
    {
        if (users[j].getClientFd().fd == fd)
            return users[j];
    }
    throw std::runtime_error("Client with fd not found");
}

void    Server::joinChannel(std::string &ss, int user)
{
 
    std::vector<std::string> connections = split(ss, ',');
    if (connections.empty())
        return ;
    std::string message;
    for (size_t i = 0; i < connections.size(); i++)
    {
        trim(connections[i]);
        message.clear();
        std::vector<std::string> con = split(connections[i], ' ');
        if (con.empty())
            return ;
        if (con.size() == 1)
        {
            std::map<std::string, Channel>::iterator it = channels.find(con[0]);
            if (it != channels.end())
            {
                if (it->second.isInvited(&users[user - 1]))
                {
                    it->second.addMember(users[user - 1]);
                    handleJoin(users[user - 1], &it->second);
                    message = "Succesfully joined channel <" + con[0] + ">\n";
                }
                else if (it->second.isInviteOnly())
                    message = "Channel <" + con[0] + "> can only be joined through invitation\n";
                else if (it->second.isPrivChannel())
                    message = "Channel <" + con[0] + "> requires authentication. Please try again\n";
                else if (it->second.isFull())
                    message = "Channel <" + con[0] + "> is full\n";
                else
                {
                    it->second.addMember(users[user - 1]);
                    handleJoin(users[user - 1], &it->second);
                    message = "Succesfully joined channel <" + con[0] + ">\n";
                }
            }
            else
            {
                if (isChannel(con[0]))
                {
                    std::pair<std::map <std::string, Channel>::iterator, bool> chan = channels.insert(std::make_pair(con[0], Channel(con[0])));
                    std::map<std::string, Channel>::iterator newChannel = chan.first;
                    newChannel->second.becomeChanOperator(users[user - 1], clientPollPtrs[i].fd);
                    message = "Successfully added channel <" + con[0] + ">\n";
                    handleJoin(users[user - 1], &newChannel->second);
                }
                else
                    message = "Error: New channel name must start with #, $, + , ! or &\n";
            }
            send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
        }
        else if (con.size() == 2)
        {
            std::map<std::string, Channel>::iterator it = channels.find(con[0]);
            if (it != channels.end())
            {
                if (it->second.isInvited(&users[user - 1]))
                {
                    it->second.addMember(users[user - 1]);
                    handleJoin(users[user - 1], &it->second);
                    message = "Succesfully joined channel <" + con[0] + ">\n";
                }
                else if (it->second.isInviteOnly())
                    message = "Channel <" + con[0] + "> can only be joined through invitation\n";
                else if (it->second.isFull())
                    message = "Channel <" + con[0] + "> is full\n";
                else if (!it->second.isPrivChannel())
                    message = "Channel <" + con[0] + "> is not private\n";
                else if (!it->second.passwordMatched(con[1]))
                    message = "Invalid password\n";
                else
                {
                    it->second.addMember(users[user - 1]);
                    handleJoin(users[user - 1], &it->second);
                    message += "Succesfully joined channel <" + con[0] + ">\n";
                }
            }
            else
            {
                    if (isChannel(con[0]))
                {
                    std::pair<std::map <std::string, Channel>::iterator, bool> chan = channels.insert(std::make_pair(con[0], Channel(con[0])));
                    std::map<std::string, Channel>::iterator newChannel = chan.first;
                    newChannel->second.becomeChanOperator(users[user - 1], clientPollPtrs[i].fd);
                    message = "Successfully added channel <" + con[0] + ">\n";
                    handleJoin(users[user - 1], &newChannel->second);
                }
                else
                    message = "Error: New channel name must start with #, $, + , ! or &\n";
            }
            send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
        }
        else
        {
            std::string message = "Invalid connection request to: " + con[0] + "\n";
            send(users[user - 1].getClientFd().fd, message.c_str(), message.size(), 0);
        }
    }
}


void    Server::handleLeave(Client &leavingClient, Channel *leaving)
{
    std::string message;
    std::vector<Client *> members = leaving->getMembers();

    message = ":" + leavingClient.getNickname() + "!" + leavingClient.getUsername()
        + "@" + ipAddress + " PART " + leaving->getName() + "\r\n";
    for (size_t i = 0; i < members.size(); i++)
        send(members[i]->getClientFd().fd, message.c_str(), message.size(), 0);
}

void    Server::leaveChannel(std::string &input, int user)
{
    if (input.empty())
    {
        std::string message = "Error: No channel specified\n";
        send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
        return ;
    }
    std::vector<std::string> splitted = split(input, ':');
    trim(splitted[0]);
    std::map<std::string, Channel>::iterator it = channels.find(splitted[0]);
    if (it != channels.end())
    {
        handleLeave(users[user - 1], &it->second);
        it->second.removeMember(&users[user - 1]);
    }
    else
    {
        std::string message = "Error: Channel not found\n";
        send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
    }
}

Client     *Server::getClientByUserOrNick(std::string &userOrNick)
{
    for (size_t i = 0; i < users.size(); i++)
        if (userOrNick == users[i].getNickname() || userOrNick == users[i].getUsername())
            return (&users[i]);
    return NULL;
}

void    Server::handleNoArgs(std::string &cmd, Client *requester)
{
    if (cmd == "WHO")
    {
        std::map<std::string, Channel>::iterator channel;
        for (channel = channels.begin(); channel != channels.end(); ++channel)
            handleWHO(&channel->second, requester);
    }
    else
    {
        std::deque<Client>::iterator client;
        for (client = users.begin(); client != users.end(); ++client)
            handleWHOIS(&(*client), requester);
    }
}

void    Server::handleWHOandWHOIS(std::string &cmd, std::string &input, int user)
{
    Client *requester = &users[user - 1];
    std::string message;

    std::vector<std::string> requests = split(input, ',');
    if (requests.empty())
        handleNoArgs(cmd, requester);
    for (size_t i = 0; i < requests.size(); i++)
    {
        trim(requests[i]);
        std::vector<std::string> con = split(requests[i], ' ');
        if (con.empty())
            return ;
        if (con.size() != 1)
        {
            message = "Error: invalid command syntax for :" + cmd + "\n";
            send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
            continue ;
        }
        if (cmd == "WHOIS")
        {
            Client *requested = getClientByUserOrNick(con[0]);
            if (!requested)
            {
                message = "Error: User <" + con[0] + "> not found\n";
                send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
                continue ;
            }
            handleWHOIS(requested, requester);
        }
        else
        {
            std::map<std::string, Channel>::iterator chan = channels.find(con[0]);
            if (chan != channels.end())
                handleWHO(&chan->second, requester);
            else
            {
                message = "Error: Channel <" + con[0] + "> not found\n";
                send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
                continue ;
            }
        }
    }
}


void	Server::handleTopic(std::string &full, int i)
{
    std::string message;
    std::vector<std::string> topicRequest = split(full, ' ');
    for(size_t i = 0; i < topicRequest.size(); i++)
        if (!topicRequest[i].empty() && topicRequest[i][0] == ':')
            topicRequest[i].erase(0, 1);
    std::map<std::string, Channel>::iterator it = channels.find(topicRequest[1]);
    if (it == channels.end())
        message = "Error: Channel '" + topicRequest[1] + "' does not exist.\n";
    else if (topicRequest.size() == 2)
    {
        if (!it->second.getTopic().empty())
            message = "Current topic for " + topicRequest[1] + ": " + it->second.getTopic() + "\n";
        else
            message = "There is no topic set for channel '" + topicRequest[1] + "'.\n";
    }
    else if (topicRequest.size() == 3)
    {
        if (it->second.isOperator(clientPollPtrs[i].fd) || it->second.isOperatorOnly() == 1)
			it->second.changeTopic(topicRequest[2], clientPollPtrs[i].fd);
        else
            message = "Error: Only channel operators can change the topic in '" + topicRequest[1] + "'.\n";
    }
    else
        message = "Error: No channel specified. Usage: TOPIC <#channel> [new_topic]\n";
    send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
}

void	Server::handleInvite(std::string &channel, std::string &client, int i)
{
	std::map<std::string, Channel>::iterator it = channels.find(channel);
	if (it != channels.end())
	{
		std::deque<Client>::iterator it2;
		std::stringstream ss(client);
		int num;
		ss >> num;
		for (it2 = users.begin(); it2 != users.end(); ++it2)
		{
			if (it2->getNickname() == client || it2->getUsername() == client || it2->getClientFd().fd == num)
			{
				it->second.sendInvite(&(*it2));
				std::string message = "You have been invited to channel: " + channel + "\n";
				send(it2->getClientFd().fd, message.c_str(), message.size(), 0);
				break;
			}
		}
		if (it2 == users.end())
		{
			std::string message = "Error: could not find User\n";
			send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
		}
	}
	else
	{
		std::string message = "Error: could not find Channel\n";
		send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
	}
}

void	Server::handleNames(std::string &channel, int i)
{
	if (channel.empty())
    {
        std::map<std::string, Channel>::iterator it;
        for (it = channels.begin(); it != channels.end(); ++it)
            it->second.showMembers(clientPollPtrs[i]);
    }
    else
    {
        std::map<std::string, Channel>::iterator it = channels.find(channel);
        if (it != channels.end())
            it->second.showMembers(clientPollPtrs[i]);
        else
        {
            std::string message = "Channel " + channel + " doesn't seem to exist in our database. Please try another name\n";
            send(clientPollPtrs[i].fd, message.c_str(), message.size(), 0);
        }
    }
}

void    Server::kickUser(std::string &input, int user)
{
    std::vector<std::string> userInput = split(input, ' ');
    std::string message, chan, kickedOut;
    if (userInput.size() == 3)
    {
        chan = userInput[1];
        kickedOut = userInput[2];
    }
    else if (userInput.size() == 4) //hexchat
    {
        chan = userInput[2];
        kickedOut = userInput[3];
        if (kickedOut[0] == ':')
            kickedOut.erase(0, 1);
    }
    else
    {
        message = "Error: Syntax: KICK #channel user\n";
        send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
        return ;
    }
    std::map<std::string, Channel>::iterator channel = channels.find(chan);
    if (channel == channels.end())
        message = "Error: Channel not found\n";
    else if (!channel->second.isOperator(clientPollPtrs[user].fd))
        message = "Error: Only operators can Kick members\n";
    else
    {
        std::vector< Client *> members = channel->second.getMembers();
        for (size_t i = 0; i < members.size(); i++)
        {
            if (members.at(i)->getNickname() == kickedOut || members.at(i)->getUsername() == kickedOut)
            {
                channel->second.removeMember(members.at(i));
                message = ":" + users[user - 1].getNickname() + " KICK " + channel->second.getName() + " "
                    + members.at(i)->getNickname() + " :\r\n"; //no reason of kick implementation
                for (size_t j = 0; j < members.size(); j++)   
                    send(members.at(j)->getClientFd().fd, message.c_str(), message.size(), 0);
                return ;
            }
        }
        message = "Error: user <" + kickedOut + "> is not in this channel\n";
    }
    send(clientPollPtrs[user].fd, message.c_str(), message.size(), 0);
}
