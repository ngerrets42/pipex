/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 13:33:22 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/28 17:41:46 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static size_t	ft_count_words(char const *str, char c)
{
	char	*ptr;
	size_t	word_length;
	size_t	words;

	words = 1;
	ptr = (char *)str;
	while (*ptr == c)
		ptr++;
	while (*ptr != '\0')
	{
		word_length = 0;
		while (ptr[word_length] != c && ptr[word_length] != '\0')
			word_length++;
		ptr += word_length;
		while (*ptr == c && *ptr != '\0')
			ptr++;
		if (word_length > 0)
			words++;
	}
	return (words);
}

static void	ft_split_free_alloc(char **result, size_t last_index)
{
	if (last_index == 0)
	{
		free(result);
		return ;
	}
	while (last_index > 0)
	{
		free(result[last_index]);
		last_index--;
	}
	free(result);
}

static char	**ft_split_loop(char *ptr, char **res, char c)
{
	size_t	word_length;
	size_t	word;

	word = 0;
	while (*ptr != '\0')
	{
		word_length = 0;
		while (ptr[word_length] != c && ptr[word_length] != '\0')
			word_length++;
		res[word] = ft_substr(ptr, 0, word_length);
		if (res[word] == NULL)
		{
			ft_split_free_alloc(res, word - 1);
			return (NULL);
		}
		ptr += word_length;
		while (*ptr == c && *ptr != '\0')
			ptr++;
		word++;
	}
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	*ptr;
	size_t	words;
	char	**result;

	if (str == NULL)
		return (NULL);
	words = ft_count_words(str, c);
	result = malloc(sizeof(char *) * words);
	if (result == NULL)
		return (NULL);
	if (words == 1 || (c == '\0' && ft_strlen(str) == 0))
	{
		result[0] = NULL;
		return (result);
	}
	ptr = (char *)str;
	while (*ptr == c)
		ptr++;
	result = ft_split_loop(ptr, result, c);
	if (result == NULL)
		return (NULL);
	result[words - 1] = NULL;
	return (result);
}
