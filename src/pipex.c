/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 12:47:32 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 14:12:01 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include "str.h"
#include "sys/wait.h"
#include <stdlib.h>
#include <stdio.h>

# define READ 0
# define WRITE 1

char	**env_get(char **env)
{
	static char	**stored_env = NULL;

	if (env != NULL)
		stored_env = env;
	return (stored_env);
}

void	do_parent(int i, int pid, int argc, int pipe_prev[2], int pipe_curr[2])
{
	printf("Doing parent... i = %d\n", i);
	if (i == 0)
		close(pipe_prev[WRITE]);
	else if (i == argc - 4)
	{
		close(pipe_prev[READ]);
	}
	else
	{
		close(pipe_prev[READ]);
		close(pipe_curr[WRITE]);
	}
	while(wait(NULL) > 0);
}

void	do_child(int i, int argc, int pipe_prev[2], int pipe_curr[2], char **cmd)
{
	printf("Doing child... i = %d\n", i);
	if (i == 0)
	{
		printf("STDOUT to current pipe WRITE\n");
		dup2(pipe_prev[WRITE], STDOUT_FILENO);
	}
	else if (i == argc - 4)
	{
		printf("STDIN to current pipe READ\n");
		dup2(pipe_prev[READ], STDIN_FILENO);
	}
	else
	{
		dup2(pipe_prev[READ], STDIN_FILENO);
		dup2(pipe_curr[WRITE], STDOUT_FILENO);
	}
	if (execve(cmd[0], cmd, env_get(NULL)) < 0)
		throw_error("Something went wrong");
}

void	run_pipex(int argc, char **argv, char **env)
{
	int	pid;
	int	pipe_prev[2];
	int	pipe_curr[2];
	int	i;
	char	**cmd;
	
	env_get(env);
	i = 0;
	while (i < argc - 3)
	{
		if (i == 0)
		{
			pipe(pipe_prev);
		}
		else if (i < argc - 4)
		{
			pipe(pipe_curr);
		}
		cmd = ft_split(argv[2 + i], ' ');
		pid = fork();
		if (pid < 0)
			throw_error(NULL);
		else if (pid == 0)
			do_child(i, argc, pipe_prev, pipe_curr, cmd);
		else
			do_parent(i, pid, argc, pipe_prev, pipe_curr);
		if (i > 0)
		{
			pipe_prev[0] = pipe_curr[0];
			pipe_prev[1] = pipe_curr[1];
		}
		i++;
	}
	printf("Done!\n");
}
