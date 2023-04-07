# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 16:26:10 by idabligi          #+#    #+#              #
#    Updated: 2023/04/07 16:30:29 by idabligi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC
FLAGS = -Wall -Wextra -Werror
RM = rm -f
HEADER = minishell.h

FLS = main ft_execution ft_split ft_get_path mininshell_utils lst_functions\

FO = $(FLS:=.o)

all : $(NAME)

$(NAME) : $(FO) $(HEADER)
	$(CC) $(FLAGS) $(FO) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) -c $(FLAGS) $<

clean :
	$(RM) $(FO)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re