/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:30:40 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 16:33:55 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

void	throw_error(const char *err)
{
	if (err != NULL)
		ft_putstr_fd(err, FD_STDOUT);
	else
		perror(NULL);
	exit(1);
}
