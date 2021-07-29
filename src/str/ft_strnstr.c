/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:54:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/29 15:37:21 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strnstr(const char *hstk, const char *ndle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hstk_ptr;

	hstk_ptr = (char *)hstk;
	if (*ndle == '\0')
		return (hstk_ptr);
	i = 0;
	while (hstk[i] != '\0' && i < len)
	{
		if (hstk[i] == *ndle)
		{
			j = 0;
			while ((i + j < len) && (hstk_ptr[i + j] == ndle[j]))
			{
				j++;
				if (ndle[j] == '\0')
					return (&hstk_ptr[j]);
			}
		}
		i++;
	}
	return (NULL);
}
