/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:40:05 by yohan             #+#    #+#             */
/*   Updated: 2025/05/28 14:50:05 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <istream>
#include <csignal>
#include <sstream>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <ctime>
#include <unistd.h>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

#include ".config.h"
#include "security.hpp"
#include "client.hpp"
#include "channel.hpp"
#include "server.hpp"

enum role
{
    USER,
    OPERATOR
};
