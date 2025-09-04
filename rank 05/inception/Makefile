# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macampos <macampos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 18:38:11 by macampos          #+#    #+#              #
#    Updated: 2025/06/17 18:52:15 by macampos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

up:
	mkdir -p /home/macampos/data
	docker compose -f ./srcs/docker-compose.yml up --build

upd:
	mkdir -p /home/macampos/data
	docker compose -f ./srcs/docker-compose.yml up --build -d

start:
	docker compose -f ./srcs/docker-compose.yml  start

re: down all

down:
	docker compose -f ./srcs/docker-compose.yml down -v

stop:
	docker compose -f ./srcs/docker-compose.yml  stop

fclean: down
		sudo rm -rf /home/macampos/data
		docker system prune -a -f --volumes
		docker volume prune -f
		docker rmi -f srcs-mariadb || true
		docker rmi -f srcs-nginx || true
		docker rmi -f srcs-wordpress || true
		docker image prune -f

logs:
	docker compose -f ./srcs/docker-compose.yml logs -f
	
status:
		docker ps -a
		@echo
		docker image ls
		@echo
		docker volume ls
		@echo
		docker network ls --filter "name=inception"

.PHONY: all up down start stop re logs fclean