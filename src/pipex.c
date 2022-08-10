/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 12:47:32 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/08/10 15:29:21 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Returns the filedescriptor for the input. opens a file if i equals 0.
**	i is the iteration, only the first (i == 0) reads from the input file.
*/
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

/*
**	Returns the filescriptor for the output. Opens a file if i equals argc - 4.
**	i is the iteration, only the last (i == argc - 4) opens the output file.
*/
static int	get_output(int i, int argc, char **argv, int pipes[2][2])
{
	int	fd;

	if (i == argc - 4)
	{
		fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR);
		if (fd < 0)
			throw_error(NULL);
		return (fd);
	}
	return (pipes[CURRENT][P_WRITE]);
}

static void	free_split(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

/*
**	This is where the magic happens. Creates two pipes and uses them to chain
**	through the commands, "piping" them together and executing them. The pipes
**	switch places with every iteration (CURRENT becomes PREVIOUS). At the end
**	wait for all child processes.
*/
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
		free_split(cmd);
		pipes[PREVIOUS][P_READ] = pipes[CURRENT][P_READ];
		pipes[PREVIOUS][P_WRITE] = pipes[CURRENT][P_WRITE];
		i++;
	}
	while (wait(NULL) == 0)
		;
}
