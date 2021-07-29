/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:25:13 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 15:41:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include "str.h"
# include "sys/wait.h"
# include <stdlib.h>
# include <stdio.h>

# define P_READ 0
# define P_WRITE 1

void	pipex(int argc, char **argv, char **env);
char	*get_path(char **cmd, char **env);
void	run_command(int io[2], char **cmd, char **env);
//void	run_heredoc(int argc, char **argv);
void	throw_error(const char *err);

#endif
