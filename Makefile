NAME = minishell
CC = gcc
CFLAGS = -Werror -Wall -Wextra 

LDFLAGS = -lreadline -L/opt/homebrew/opt/readline/lib -L${HOME}/.brew/opt/readline/lib -Llibs/Libft -lft
CPPFLAGS = -I${HOME}/.brew/opt/readline/include -I/opt/homebrew/opt/readline/include

INCLUDE_DIR	=	./include

SRCS = main.c signal.c cmd/cd.c cmd/echo.c cmd/env.c cmd/exec.c cmd/exit.c cmd/export.c cmd/pwd.c cmd/unset.c parser/arg_splitter.c parser/expand_envvar.c parser/expand_wildcard.c parser/parser.c \
		redirection/exec_redir.c redirection/utils_redir.c redirection/cmd_redir.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make bonus -s -C libs/Libft
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean :
	@make clean -s -C libs/Libft
	@rm -rf $(OBJS)

debug : fclean $(OBJS)
	@make debug -s -C libs/Libft
	$(CC) $(CFLAGS) -g -fsanitize=thread $(LDFLAGS) $(OBJS) -o $(NAME)


fclean : clean
	@make fclean -s -C libs/Libft
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
