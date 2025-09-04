/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Security.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohan <yohan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:42:09 by yohan             #+#    #+#             */
/*   Updated: 2025/03/12 17:42:53 by yohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "library.h"

class Security
{
    private:
            int             role;
            unsigned int    port;
    public:
            Security();
            Security(std::string &port);
            Security(const Security &copy);
            Security &operator=(const Security &other);
            ~Security();

            void            validatePort(std::string &Port);
            void            validatePassword(const std::string &attempt);
            unsigned int    getPort();
            int             getRole();
};