/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 12:47:32 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 20:56:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_input(int i, char **argv, int pipes[2][2])
{
	int	fd;

	if (i == 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			throw_error(NULL);
		return (fd);
	}
	return (pipes[PREVIOUS][P_READ]);
}

static int	get_output(int i, int argc, char **argv, int pipes[2][2])
{
	int	fd;

	if (i == argc - 4)
	{
		fd = open(argv[argc - 1], O_CREAT |O_WRONLY,
				S_IRUSR | S_IWUSR);
		if (fd < 0)
			throw_error(NULL);
		return (fd);
	}
	return (pipes[CURRENT][P_WRITE]);
}

void	pipex(int argc, char **argv, char **env)
{
	int		pipes[2][2];
	int		io[2];
	int		i;
	char	**cmd;

	i = 0;
	while (i < argc - 3)
	{
		if (i < argc - 4)
			pipe(pipes[CURRENT]);
		cmd = ft_split(argv[2 + i], ' ');
		io[P_READ] = get_input(i, argv, pipes);
		io[P_WRITE] = get_output(i, argc, argv, pipes);
		run_command(io, cmd, env);
		pipes[PREVIOUS][P_READ] = pipes[CURRENT][P_READ];
		pipes[PREVIOUS][P_WRITE] = pipes[CURRENT][P_WRITE];
		i++;
	}
	while (wait(NULL) == 0)
		;
}
