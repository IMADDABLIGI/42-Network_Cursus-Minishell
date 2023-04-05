# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 14:26:36 by idabligi          #+#    #+#              #
#    Updated: 2023/04/01 15:10:16 by idabligi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = CC
FLAGS = -Wall -Wextra -Werror
RM = rm -f
HEADER = pipex.h

FLS = pipex ft_split ft_cmd pipex_utils ft_access ft_write_error\

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