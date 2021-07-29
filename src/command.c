/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 22:32:10 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 15:57:08 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_parent(int input, int output, int pid)
{
	close(input);
	close(output);
	waitpid(pid, NULL, 0);
}

static void	duptwo(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
		throw_error(NULL);
}

static void	do_child(int input, int output, char **cmd, char **env)
{
	char	*path_to_bin;

	duptwo(input, STDIN_FILENO);
	duptwo(output, STDOUT_FILENO);
	path_to_bin = get_path(cmd, env);
	if (path_to_bin == NULL)
		throw_error("Command not found.\n");
	if (execve(path_to_bin, cmd, env) < 0)
		throw_error(NULL);
}

void	run_command(int io[2], char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		throw_error(NULL);
	else if (pid == 0)
		do_child(io[P_READ], io[P_WRITE], cmd, env);
	else
		do_parent(io[P_READ], io[P_WRITE], pid);
}
