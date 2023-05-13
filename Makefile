# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 18:27:52 by hznagui           #+#    #+#              #
#    Updated: 2023/05/13 09:30:11 by hznagui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC_FILE = 	main.c\
			tools1.c\
			tools2.c\
			tools3.c\
			tools4.c\
			tools5.c\
			tools6.c\
			tools7.c\
			ft_split_cmd.c\
			ft_execution.c\
			ft_redirection.c\
			minishell_utils.c\
			minishell_utils2.c\
			minishell_utils3.c\
			minishell_utils4.c\
			minishell_utils5.c\

COLOUR_GREEN=\033[1;32m

COLOUR_RED=\033[1;31m

COLOUR_RESET= \033[1;0m


OBJ_FILE = $(SRC_FILE:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ_FILE) minishell.h 
	@cc $(FLAGS)  -L $(shell brew --prefix readline)/lib -lreadline $(OBJ_FILE)   -o $(NAME) 
	@echo  "$(COLOUR_GREEN)--->[mandatory part successfully created ✅]<---$(COLOUR_RESET)"

%.o: %.c minishell.h 
	@cc $(FLAGS) -I $(shell brew --prefix readline)/include  -c $< -o $@ 

clean :
	@rm -rf $(OBJ_FILE)
	@echo "$(COLOUR_RED)--->[obj file deleted successfully ✅]<---$(COLOUR_RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)--->[programs deleted successfully ✅]<---$(COLOUR_RESET)"


re : fclean all