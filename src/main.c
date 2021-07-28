/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:06:23 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 16:45:48 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "pipex.h"

int	main(int argc, char **argv)
{
	if (argc <= 4)
	{
		ft_putstr_fd("Pipex needs at least 4 args.", FD_STDOUT);
		return (1);
	}
	if (str_is_str(argv[1], "here_doc"))
	{
		if (argc <= 5)
		{
			ft_putstr_fd("Need at least 5 args with here_doc", FD_STDOUT);
			return (1);
		}
		run_heredoc(argc, argv);
	}
	else
		run_pipex(argc, argv);
	return (0);
}