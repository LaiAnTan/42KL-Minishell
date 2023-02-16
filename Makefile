NAME = minishell

SRCS_C =	srcs/msh_main.c		\
			srcs/builtins.c		\
			srcs/lexer.c		\
			srcs/utilities.c	\

SRCS_H = headers/minishell.h

SRCS_O = $(SRCS_C:.c=.o)

CFLAG = 
# -Wall -Wextra -Werror

LIB = -lreadline

all : $(NAME)

%.o: %.c
		@gcc $(CFLAG) -c $< -o $(<:.c=.o)

$(NAME): $(SRCS_O)
		@gcc $(CFLAG) -o $(NAME) $(SRCS_O) $(LIB)

vg :
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

clean :
		@rm -f ${SRCS_O}

fclean : clean
		@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re git $(NAME)