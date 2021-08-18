/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 18:52:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 12:47:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Returns the filedescriptor for the input. opens a file if i equals 0.
**	i is the iteration, only the first (i == 0) reads from the input file.
*/
static int	get_input(int i, int pipes[2][2], char *fname)
{
	int	fd;

	if (i == 0)
	{
		fd = open(fname, O_RDWR);
		if (fd < 0)
			throw_error(NULL);
		return (fd);
	}
	return (pipes[PREVIOUS][P_READ]);
}

/*
**	Returns the filescriptor for the output. Opens a file if i equals argc - 5.
**	i is the iteration, only the last (i == argc - 5) opens the output file.
*/
static int	get_output(int i, int argc, char **argv, int pipes[2][2])
{
	int	fd;

	if (i == argc - 5)
	{
		fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR);
		if (fd < 0)
			throw_error(NULL);
		return (fd);
	}
	return (pipes[CURRENT][P_WRITE]);
}

/*
**	heredoc is very similar to the pipex function, it however first creates a
**	temporary heredoc file to write to before using this file as the input. it
**	deletes the temporary file after the function is completed.
*/
void	heredoc(int argc, char **argv, char **env)
{
	int		pipes[2][2];
	int		io[2];
	int		i;
	char	**cmd;
	char	*fname;

	fname = heredoc_get_fname();
	heredoc_write(fname, argv[2]);
	i = 0;
	while (i < argc - 4)
	{
		if (i < argc - 5)
			pipe(pipes[CURRENT]);
		cmd = ft_split(argv[3 + i], ' ');
		io[P_READ] = get_input(i, pipes, fname);
		io[P_WRITE] = get_output(i, argc, argv, pipes);
		run_command(io, cmd, env);
		pipes[PREVIOUS][P_READ] = pipes[CURRENT][P_READ];
		pipes[PREVIOUS][P_WRITE] = pipes[CURRENT][P_WRITE];
		i++;
	}
	while (wait(NULL) > 0)
		;
	heredoc_delete(fname);
}
