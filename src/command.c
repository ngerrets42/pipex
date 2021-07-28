/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 22:32:10 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 23:19:09 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "pipex.h"
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "str.h"

t_command	*command_create(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		throw_error("Malloc failed.");
	command->fd[FD_IN] = 0;
	command->fd[FD_OUT] = 0;
	command->args = NULL;
	command->next = NULL;
	return (command);
}

static void	pipe_connect(int *in, int *out)
{
	int	fd[2];

	if (pipe(fd) == -1)
		throw_error(NULL);
	*in = fd[0];
	*out = fd[1];
}

t_command	*command_chain(int argc, char **argv)
{
	t_command	*initial_command;
	t_command	*current_command;
	int			i;

	current_command = command_create();
	initial_command = current_command;
	initial_command->fd[FD_IN] = open(argv[1], O_RDONLY);
	i = 2;
	while (i < argc - 1)
	{
		current_command->next = command_create();
		pipe_connect(&current_command->fd[FD_OUT],
			&current_command->next->fd[FD_IN]);
		current_command->args = ft_split(argv[i], ' ');
		current_command = current_command->next;
		i++;
	}
	current_command->fd[FD_OUT] = open(argv[argc - 1], O_WRONLY);
	current_command->args = ft_split("END", ' ');
	return (initial_command);
}

#include <stdio.h>
void	command_print(t_command *command)
{
	t_command	*curr;

	curr = command;
	while (curr != NULL)
	{
		printf("Command IN: %d, ARG0: %s, OUT: %d, NEXT: %p\n",
			curr->fd[FD_IN], curr->args[0], curr->fd[FD_OUT], curr->next);
		curr = curr->next;
	}
}
