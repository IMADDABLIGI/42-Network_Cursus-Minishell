# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:27:52 by hznagui           #+#    #+#              #
#    Updated: 2023/05/04 10:17:17 by idabligi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_FILE = 	main.c \
			tolls1.c\
			tolls2.c\
			ft_execution.c\
			ft_redirection.c\
			ft_split_cmd.c\
			mininshell_utils.c\
			mininshell_utils2.c\

COLOUR_GREEN=\033[1;32m

COLOUR_RED=\033[1;31m

COLOUR_RESET= \033[1;0m


OBJ_FILE = $(SRC_FILE:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ_FILE) minishell.h 
	@cc  -lreadline   $(OBJ_FILE)   -o $(NAME) 
	@echo  "$(COLOUR_GREEN)--->[mandatory part successfully created ✅]<---$(COLOUR_RESET)"

%.o: %.c minishell.h 
	@$(CC)    -c $< -o $@

clean :
	@rm -rf $(OBJ_FILE)
	@echo "$(COLOUR_RED)--->[obj file deleted successfully ✅]<---$(COLOUR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)--->[programs deleted successfully ✅]<---$(COLOUR_RESET)"


re : fclean all