/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 18:52:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 21:00:31 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
