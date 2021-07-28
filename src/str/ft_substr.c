/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:55:16 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 21:59:44 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	remaining_len;
	size_t	i;
	char	*result;

	if (str == NULL)
		return (NULL);
	remaining_len = 0;
	if (start >= ft_strlen(str))
		len = 0;
	else
		while (str[start + remaining_len] != '\0')
			remaining_len++;
	if (remaining_len < len)
		len = remaining_len;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
