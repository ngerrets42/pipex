/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:55:42 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/08/10 15:18:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	length1;
	size_t	length2;
	size_t	i;
	char	*result;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < length1 + length2)
	{
		result[i] = str2[i - length1];
		if (i < length1)
			result[i] = str1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	size_t	length1;
	size_t	length2;
	size_t	i;
	char	*result;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	length1 = ft_strlen(str1);
	length2 = ft_strlen(str2);
	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < length1 + length2)
	{
		result[i] = str2[i - length1];
		if (i < length1)
			result[i] = str1[i];
		i++;
	}
	result[i] = '\0';
	free(str1);
	free(str2);
	return (result);
}
