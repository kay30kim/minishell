/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by lcouturi          #+#    #+#             */
/*   Updated: 2024/01/16 18:17:38 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("ctrl + c\n");
	rl_on_new_line();
	//rl_replace_line("", 1);
	rl_redisplay();
}

static void	cmd_exit(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	exit(EXIT_SUCCESS);
}

static void	cmd_exec(char **args, char **envp)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		execve(args[0], args, envp);
		printf("minishell: %s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, 0, 0);
}

static void	parser(char *str, char **envp)
{
	char	**args;
	int		i;

	args = ft_split(str, ' ');
	if (!args)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	if (args[0])
	{
		if (!ft_strncmp(args[0], "exit\0", 5))
			cmd_exit(args);
		else
			cmd_exec(args, envp);
	}
	add_history(str);
	free(str);
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("input> ");
		if (line)
		{
			if (ft_strncmp(line, "\0", 1))
				parser(line, envp);
		}
		else
			printf("ctrl + d\n");
	}
	return (0);
}
