/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyung-ki <kyung-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by kyung-ki          #+#    #+#             */
/*   Updated: 2024/01/23 19:48:00 by kyung-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	left_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	left_dobule_redir(char **args, int i)
{
	(void)args;
	(void)i;
}

void	right_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	right_double_redir(char **args, int i)
{
	int	fd;

	args[i] = NULL;
	fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}
