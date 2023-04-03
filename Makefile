NAME = minishell

FLAGS = -Wall -Wextra -Werror 

SRC_FILE = 	main.c \
			split1.c\
			

COLOUR_GREEN=\033[1;32m

COLOUR_RED=\033[1;31m
	

OBJ_FILE = $(SRC_FILE:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ_FILE) minishell.h 
	@cc $(FLAGS) -lreadline  -L /Users/hznagui/.brew/opt/readline  $(OBJ_FILE)   -o $(NAME) 
	@echo  "$(COLOUR_GREEN)--->[mandatory part successfully created ✅]<---"

%.o: %.c minishell.h 
	@$(CC) $(FLAGS)   -c $< -o $@

clean :
	@rm -rf $(OBJ_FILE)
	@echo "$(COLOUR_RED)--->[obj file deleted successfully ✅]<---"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOUR_RED)--->[programs deleted successfully ✅]<---"


re : fclean all