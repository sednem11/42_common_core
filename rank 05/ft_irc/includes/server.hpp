/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:56:04 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/13 16:25:06 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "library.h"
class Client;

class Server
{
    private:
        //  security:
            unsigned int            port;
            int                     serverSocket;
            Security                Sentry;
            std::string             ipAddress;
			std::string				_password;

        //  channel and user management:
            pollfd                              serverPollfd;
            std::map<std::string, Channel>      channels;
            std::deque<Client>                  users; // using deque to avoid invalid pointers when std::vector resizes itself
            std::vector<pollfd>                 clientPollPtrs;
            std::vector<time_t>                 lastPingTime;
            std::vector<double>                 elapsed;
            std::vector<time_t>                 lastPongTime;

    public:
            Server(std::string port, std::string attempt);
            Server(const Server &copy);
            Server &operator=(const Server &other);
            ~Server();

            void    initializeServer();
            void    acceptNewClient();
            bool    isRegisteredUser(int user);
            void    registerCmd(int i);
            void    joinChannel(std::string &ss, int user);
            void    leaveChannel(std::string &input, int user);
            void    kickUser(std::string &input, int user);
            void    removeUser(int fd);
            void    shutdownServer();

            void    modeChange(Channel &chanel, const std::string &mode, const std::string pass, int i);
            void    operatorAuth(int user);
            
            void    sendMsg(Client &sender, Client &receiver, const std::string &msg); //for client
            void    sendMsg(Client &sender, Channel &receiver, const std::string &msg); //for channel
        
            Client  *getClientByUserOrNick(std::string &userOrNick);
            Client  &getClientByFd(int fd);


            void    handleWHOandWHOIS(std::string &cmd, std::string &input, int user);
            void    handleWHOIS(Client *requestedUser, Client *requester);
            void    handleWHO(Channel *requestedChannel, Client *requester);
            void    handleNoArgs(std::string &cmd, Client *requester);

            void    sendPing(int i);

            void    handleList(std::string &input, int user);
            void    handleJoin(Client &newClient, Channel *channel);
            void    handleLeave(Client &leavingClient, Channel *leaving);
            void    handleHCClientInfo(std::string &buffer, Client &client, int i);
            void    handleMode(Channel &channel, const std::string &mode, std::string pass, int fd);
            void	handleTopic(std::string &full, int i);
			void	handleInvite(std::string &channel, std::string &client, int i);
			void	handleNick(std::string  &newNickname, int i);
			void	handleNickHC(std::string  &newNickname, int i);
			void	handleUser(std::string &newUsername, std::string &realName,int i);
			void	handlePrivMsg(std::string &destination, std::string &message, int i);
			void	handleNames(std::string &channel, int i);
			void	handleCC(int signal);

			void	doJoke(int i);
			void	checkPassword(std::string &pass, Client &client);	
};