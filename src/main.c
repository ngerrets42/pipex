/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:06:23 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 20:10:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc <= 4)
	{
		ft_putstr_fd("Pipex needs at least 4 args.\n", STDERR_FILENO);
		return (1);
	}
	if (str_is_str(argv[1], "here_doc"))
	{
		if (argc <= 5)
		{
			ft_putstr_fd("Need at least 5 args with here_doc\n", STDERR_FILENO);
			return (1);
		}
		heredoc(argc, argv, env);
	}
	else
		pipex(argc, argv, env);
	return (0);
}
