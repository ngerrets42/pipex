/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 22:32:10 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 12:39:21 by ngerrets      ########   odam.nl         */
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
	command->pid = -1;
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

//pipex infile->cmd1->cmd2->cmd3->outfile
//  0      1     2     3      4      5     6
t_command	*command_chain(int argc, char **argv, int fd_std[2])
{
	t_command	*initial_command;
	t_command	*current_command;
	int			i;

	current_command = command_create();
	current_command->args = ft_split(argv[2], ' ');
	initial_command = current_command;
	i = 3;
	while (i < argc - 1)
	{
		current_command->next = command_create();
		pipe_connect(&current_command->fd[FD_OUT],
			&current_command->next->fd[FD_IN]);
		current_command->next->args = ft_split(argv[i], ' ');
		current_command = current_command->next;
		i++;
	}
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
