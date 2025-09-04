/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:39:14 by yohan             #+#    #+#             */
/*   Updated: 2025/05/13 14:50:48 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/library.h"

Server *g_Server = NULL;

void handleSigInt(int signal)
{
	if(g_Server)
		g_Server->handleCC(signal);
	exit(0);
}

int main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	try
	{
		Server myDiscord(argv[1], argv[2]);
		g_Server = &myDiscord;
		std::signal(SIGINT, handleSigInt);
		myDiscord.initializeServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
    return (0);
}

// Somehow the authentication verification is making valgrind say that we have uninitialized values :D
// add active bans from channels to make sure users cant enter after ban



// make the pass nick and user thing actually work for netcat

//make std::map of functions instead of huge function