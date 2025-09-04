/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:33:40 by yohan             #+#    #+#             */
/*   Updated: 2025/05/13 13:34:55 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "library.h"

class Client
{
    private:
            int                 role;
            struct pollfd       clientFd;   
            std::string         nickname;
            std::string         username;
            bool                isWelcomed;
			std::string			realName;
			//check on registerCmd if this 3 are set or not
			bool				isPassSet;
			bool				isUserSet;
			bool				isNickSet;
			bool				authenticated;
            std::string  cmd_handle;
            
    public:
            
			Client ();
            Client (int clientSocket);
            Client (const Client &copy);
            Client &operator=(const Client &other);
            ~Client();

            void         setUsername(const std::string &newUsername);
            void         setNickname(const std::string &newNickname);
			void		 setRealname(const std::string &newRealName);
			void		 setAuthenticated();
			void		 setisPass();
			void		 setisUser();
			void		 setisNick();
			void		 setRole(int i);
            void         setHandle(std::string cmd);
            void         setHandleNull();

			
        //     void         setOriginalNick(const std::string &newOriginal);
            std::string  getUsername() const;
            std::string  getNickname() const;
			std::string	 getRealname() const;
			bool	 	 getPassSet() const;
			bool	 	 getUserSet() const;
			bool	 	 getNickSet() const;
			bool		 getAuthenticated() const;
            std::string  getHandle() const;
			
        //     std::string  getOriginalNick() const;
            pollfd       &getClientFd();
            bool         isOperator();
            bool         sentWelcome();
            void         setWelcomed(bool value);
            void         becomeOperator();
            const char   *getClientIP();
};

bool    operator==(Client &lhs, Client &rhs);