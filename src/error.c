/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:30:40 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 16:23:51 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "str.h"
#include <stdlib.h>

void	throw_error(const char *err)
{
	if (err != NULL)
		ft_putstr_fd(err, STDERR_FILENO);
	else
		perror(NULL);
	exit(1);
}
