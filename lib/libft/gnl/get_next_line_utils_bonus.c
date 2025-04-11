/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:22:58 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 15:35:43 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	cstm_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*cstm_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

char	*cstm_strjoin(char *s1, char *s2)
{
	unsigned int	count_1;
	unsigned int	count_2;
	char			*ptr;

	count_1 = 0;
	count_2 = 0;
	ptr = (char *)malloc((cstm_strlen(s1) + cstm_strlen(s2) + 1) * sizeof (char));
	if (!ptr)
		return (NULL);
	while (s1[count_1])
	{
		ptr[count_1] = s1[count_1];
		count_1++;
	}
	while (s2[count_2])
		ptr[count_1++] = s2[count_2++];
	ptr[count_1] = '\0';
	free (s1);
	return (ptr);
}
