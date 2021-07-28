/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/28 16:09:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 17:14:01 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdlib.h>

int	ft_putstr_fd(const char *str, int fd)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (write(fd, str, length));
}

int	str_is_str(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *str)
{
	size_t	length;
	size_t	i;
	char	*cpy;

	length = 0;
	while (str[length] != '\0')
		length++;
	length++;
	cpy = malloc(length * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		cpy[i] = str[i];
		i++;
	}
	return (cpy);
}
