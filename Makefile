NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 

LDFLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib -Llibs/Libft -lft
CPPFLAGS = -I${HOME}/.brew/opt/readline/include

INCLUDE_DIR	=	./include

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -s -C libs/Libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
	@make clean -s -C libs/Libft
	@rm -rf $(OBJS)

debug : fclean $(OBJS)
	@make debug -s -C libs/Libft
	$(CC) $(CFLAGS) -g -fsanitize=thread -Wno-unused-parameter $(LDFLAGS) $(OBJS) -o $(NAME)


fclean : clean
	@make fclean -s -C libs/Libft
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re