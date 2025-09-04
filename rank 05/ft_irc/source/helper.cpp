/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:00 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/28 14:48:32 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/library.h"

inline void    trim(std::string &str)
{
    size_t start = 0;
    while (start < str.size() && (std::isspace(str[start]) || str[start] == '\r' || str[start] == '\n'))
        ++start;

    size_t end = str.size() - 1;
    while (end > start && (std::isspace(str[end]) || str[end] == '\r' || str[end] == '\n'))
        --end;
    str = str.substr(start, end - start + 1);
}

void trimNewline(std::string &cmd)
{
    while (!cmd.empty() && (cmd[cmd.size() - 1] == '\n' || cmd[cmd.size() - 1] == '\r'))
        cmd.erase(cmd.size() - 1, 1); // Remove last character
}

int isChannel(std::string channel)
{
	return (channel[0] == '#' || channel[0] == '!' || channel[0] == '@' || channel[0] == '+' || channel[0] == '$');
}


// ADD FUNCTIONS UNDER THIS TO UTILITY FILE //
std::vector<std::string> streamSplit(std::istream &ss, char separator)
{
    std::vector<std::string> result;
    std::string token;

    while (std::getline(ss, token, separator))
        result.push_back(token);
    return(result);
}

std::vector<std::string> split(const std::string &sentence, char separator)
{
    std::stringstream ss(sentence);
    std::vector<std::string> result;
    std::string token;

    while (std::getline(ss, token, separator))
        result.push_back(token);
    return(result);
}
