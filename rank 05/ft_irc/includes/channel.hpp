/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:32:17 by yohan             #+#    #+#             */
/*   Updated: 2025/05/05 17:41:40 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "library.h"
class Client;

class Channel
{
    private:
            bool                   inviteOnly;
            bool                   privChannel;
            std::string            password;

            std::string            ChannelName;
            std::string            _Topic; //not added yet

            std::vector<Client *>  members;
            std::vector<Client *>  operators; //not implemented yet (will use same idea as server op)
            std::vector<Client *>  bannedMembers; //not implemented yet
            std::vector<Client *>  invited;
            size_t                 userLimit;
            bool                   topicChange;
    public:
            Channel(std::string &name, bool isInviteOnly = false, bool isPrivate = false, std::string password = "");
            Channel(const Channel &copy);
            Channel &operator=(const Channel &other);
            ~Channel();

            int                     addMember(Client &newMember);
            void                    sendMsg(std::string &message, Client &sender);
            std::string             getName();
            std::string             getTopic();
            void                    showMembers(pollfd &destination);
            void                    showOps(pollfd &destination);
            std::vector<Client*>&   getMembers();
            int                     becomeChanOperator(Client &newOperator, int user);

            bool                    isMember(Client *user);
            bool                    isMember(std::string &user, int check);
            bool                    isMember(std::string &user);
            bool                    isMember(int user);

            bool                    isBanned(Client *user);
            bool                    isBanned(std::string &user);
            bool                    isBanned(int user);

            bool                    isOperator(Client *user);
            bool                    isOperator(std::string &user);
            bool                    isOperatorNick(std::string &nick);
            bool                    isOperator(int user);
            
            bool                    isOperatorOnly();

            bool                    isPrivChannel();
            bool                    isInviteOnly();
            bool                    isFull();
            bool                    passwordMatched(const std::string &attempt);
            
            void                    setInviteOnly(int i, const std::string mode);
            // void        changePassword(const std::string pass, int i);
            void                    changePassword(const std::string &flag, const std::string &pass, int i);
            void                    changeTopicPrivelage(const std::string mode, int i);
            void                    changeTopic(const std::string topic, int i);
        //     void        changeLimit(const std::string lim, int i);
            void                    changeLimit(const std::string &flag, const std::string &lim, int i);
            void                    changeOperatorPrivelage(std::string client, int i, const std::string mode);
            void                    sendInvite(Client *client);
            bool                    isInvited(Client *client);

            void                    removeMember(Client *client);
            void                    removeOperator(Client *client);
};