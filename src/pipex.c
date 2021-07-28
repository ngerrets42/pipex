/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:26:21 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 17:42:57 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include "str.h"

#include <stdlib.h>

extern char **environ;

void	run_pipex(int argc, char **argv)
{
	int	fd_in;
	int	fd_out;

	/*fd_in = open(argv[1], O_RDONLY);
	if (fd_in <= 2)
		throw_error("Error - Make sure the input file exists!");
	fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY);
	if (fd_out <= 2)
		throw_error("Error - Something went wrong when opening output file.");
		*/
	if (execve("/bin/cat", arg, environ) == -1)
		throw_error(NULL);
}

void	forked(int index, char *argv)
{
	pid_t	pid;
	char	**arg;

	pid = fork();
	if (pid == 0)
	{
		arg = ft_split(argv[index], ' ');
	}
}
