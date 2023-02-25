NAME = minishell

CDIR = srcs

ODIR = obj

SRCS_C =	srcs/msh_main.c		\
			srcs/struct.c		\
			srcs/builtins.c		\
			srcs/lexer.c		\
			srcs/expander.c		\
			srcs/parser.c		\
			srcs/path.c			\
			srcs/cmd.c			\
			srcs/environment.c	\
			srcs/list.c			\
			srcs/ft_split.c		\
			srcs/utilities.c	\


SRCS_H = headers/minishell.h

SRCS_O = $(SRCS_C:.c=.o)

CFLAG =
#-Wall -Wextra -Werror

LIB = -lreadline

all : $(NAME) move

%.o:%.c
		@gcc $(CFLAG) -c $< -o $(<:.c=.o)

$(NAME): $(SRCS_O)
		@gcc $(CFLAG) -o $(NAME) $(SRCS_O) $(LIB)

$(ODIR) :
	@echo "Folder $(ODIR) does not exist, making a new one..."
	@mkdir $@

move : $(ODIR)
	@echo "Storing object files into $(ODIR)..."
	@mv $(SRCS_O) $(ODIR)

vg :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean :
		@echo "Removing object files..."
		@rm -f $(ODIR)/*.o

fclean : clean
		@echo "Removing executable $(NAME) and folder $(ODIR)..."
		@rm -f $(NAME)
		@rmdir $(ODIR)

re : fclean all

.PHONY: all clean fclean re git $(NAME)