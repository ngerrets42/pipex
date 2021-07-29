/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_file.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/29 19:28:10 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 20:17:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../lib/get_next_line/get_next_line.h"

void	heredoc_delete(char *fname)
{
	if (unlink(fname) != 0)
		throw_error(NULL);
}

char	*heredoc_get_fname(void)
{
	char	*fname;

	fname = HEREDOC_NAME;
	if (access(fname, F_OK) == 0)
	{
		if (unlink(fname) != 0)
			throw_error("Heredoc already exists and can't be removed.\n");
	}
	return (fname);
}

void	heredoc_write(char *fname, char *delimiter)
{
	int		ret;
	int		fd;
	char	*line;

	line = NULL;
	fd = open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0)
		throw_error(NULL);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
			throw_error("get_next_line returned -1\n");
		if (str_is_str(line, delimiter))
		{
			free(line);
			break ;
		}
		if (write(fd, ft_strjoin(line, "\n"),
				(ft_strlen(line) + 1) * sizeof(char)) < 0)
			throw_error(NULL);
		free(line);
	}
	close(fd);
}
