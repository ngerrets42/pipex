/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:26:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 23:07:02 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include "str.h"
#include "sys/wait.h"
#include "command.h"

#include <stdlib.h>

char	**env_get(char **env)
{
	static char	**stored_env = NULL;

	if (env != NULL)
		stored_env = env;
	return (stored_env);
}

static int	is_child(int pid)
{
	return (pid == 0);
}

static int	fork_create(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		throw_error(NULL);
	return (pid);
}

static void	fork_handle(int *fd, int fd_inout, char *arg_str)
{
	char	**args;
	char	*path_to_bin;

	args = ft_split(arg_str, ' ');
	path_to_bin = args[0];
	if (access(path_to_bin, F_OK | X_OK) < 0)
		throw_error("Access denied.");
	if (fd_inout == FD_STDIN)
	{
		if (dup2(fd[0], FD_STDIN) < 0)
			throw_error("Dup2 failed.");
	}
	else if (fd_inout == FD_STDOUT)
	{
		if (dup2(fd[1], FD_STDOUT) < 0)
			throw_error("Dup2 failed.");
	}
	close(fd[0]);
	close(fd[1]);
	if (execve(path_to_bin, args, env_get(NULL)) < 0)
		throw_error(NULL);
}

void	forked(int index, char **argv)
{
	int		pid[2];
	int		fd[2];

	if (pipe(fd) == -1)
		throw_error(NULL);
	pid[0] = fork_create();
	if (is_child(pid[0]))
		fork_handle(fd, FD_STDOUT, argv[index]);
	index++;
	pid[1] = fork_create();
	if (is_child(pid[1]))
		fork_handle(fd, FD_STDIN, argv[index]);
	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid[0], NULL, 0) < 0)
		throw_error(NULL);
	if (waitpid(pid[1], NULL, 0) < 0)
		throw_error(NULL);
}

void	run_pipex(int argc, char **argv, char **env)
{
	//int	fd_in;
	//int	fd_out;

	env_get(env);
	//forked(2, argv);
	command_print(command_chain(argc, argv));
}
