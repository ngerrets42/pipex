/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 22:32:10 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 12:46:56 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Performs the steps that the parent process is supposed to do. Currently
**	thats only to close the input and output descriptors (of the pipes).
*/
static void	do_parent(int input, int output)
{
	close(input);
	close(output);
}

/*
**	dup2 but throws an error if something went wrong.
*/
static void	duptwo(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
		throw_error(NULL);
}

/*
**	Perform the steps that the child process is supposed to do.
**	This includes duplicating the STDIN/OUT to/from the pipes, getting the path
**	to the binary of the command and replacing itself with a process of the
**	binary.
*/
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

/*
**	This functions only "forks" and checks if the process is the parent or
**	the child, then executes the corresponding function.
*/
void	run_command(int io[2], char **cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		throw_error(NULL);
	else if (pid == 0)
		do_child(io[P_READ], io[P_WRITE], cmd, env);
	else
		do_parent(io[P_READ], io[P_WRITE]);
}
