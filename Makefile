# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nschilli <nschilli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/03 13:29:20 by dsousa            #+#    #+#              #
#    Updated: 2015/04/03 15:05:33 by nschilli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export	CC	=	g++

NAME		=	n-puzzle

CFLAGS		= -Wall -Wextra -Werror

INC			+=	-I includes

INC_DIR		=	includes/

INC_FILES	=	

INC_SRC		=	$(addprefix $(INC_DIR), $(INC_FILES))

SRC_DIR		=	srcs/

FILES		=	main.cpp\

SRC			=	$(addprefix $(SRC_DIR), $(FILES))

OBJ			=	$(SRC:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo ""
	@echo "\033[33m"compilation of $(NAME) : "\033[32m"Success"\033[0m"

$(OBJ):			$(INC_SRC)

%.o:			%.cpp $(INC_SRC)
	@echo -n .
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "\033[31m"Objects of $(NAME) : deleted"\033[0m"

fclean:			clean
	@/bin/rm -f $(NAME)
	@echo "\033[31m"$(NAME) : deleted"\033[0m"
re:				fclean all

.PHONY:			all clean fclean re
