/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:25:13 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/03 17:30:29 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include "str.h"

# define P_READ 0
# define P_WRITE 1
# define PREVIOUS 0
# define CURRENT 1
# define HEREDOC_NAME ".heredoc_"

# ifndef BONUS
#  define BONUS 0
# endif

void	pipex(int argc, char **argv, char **env);
char	*get_path(char **cmd, char **env);
void	run_command(int io[2], char **cmd, char **env);
void	throw_error(const char *err);
void	heredoc(int argc, char **argv, char **env);
void	heredoc_delete(char *fname);
char	*heredoc_get_fname(void);
void	heredoc_write(char *fname, char *delimiter);

#endif
