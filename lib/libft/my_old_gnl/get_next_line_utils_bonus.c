/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbui-quo <tbui-quo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:20:19 by tbui-quo          #+#    #+#             */
/*   Updated: 2023/02/23 18:27:12 by tbui-quo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc_complete(size_t count, size_t size)
{
	void				*ptr;
	size_t				tot_size;
	unsigned char		*temp;

	tot_size = count * size;
	if (count && size != (tot_size / count))
		return (NULL);
	ptr = malloc(tot_size);
	if (!ptr)
	{
		return (0);
	}
	temp = ptr;
	while (tot_size--)
		*temp++ = 0;
	return (ptr);
}

//char	*ft_strchr(const char *s, int c)
//{
//	while (*s != '\0' && (unsigned char)c != *s)
//		s++;
//	if ((unsigned char)c == *s)
//		return ((char *)s);
//	return (0);
//}

char	*initialize_line_read_if_null(char *line_read)
{
	char	*tmp;

	if (!line_read)
	{
		tmp = ft_calloc_complete(1, sizeof(char));
		if (!tmp)
			return (NULL);
		line_read = tmp;
	}
	return (line_read);
}

//size_t	ft_strlen(const char *s)
//{
//	size_t	strlen;
//
//	strlen = 0;
//	while (s[strlen] != '\0')
//	{
//		strlen++;
//	}
//	return (strlen);
//}

size_t	find_newline_pos(const char *str)
{
	size_t	char_index;

	char_index = 0;
	while (str[char_index] && str[char_index] != '\n')
		char_index++;
	return (char_index);
}

void	*free_and_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	*ft_strjoin_and_free(char *previous_read, char *current_read)
{
	char	*complete_line;
	int		total_length;
	int		char_index;
	int		char_index2;

	total_length = ft_strlen(previous_read) + ft_strlen(current_read);
	complete_line = malloc((total_length + 1) * sizeof(char));
	if (complete_line == NULL)
		return (NULL);
	char_index = 0;
	char_index2 = 0;
	while (previous_read[char_index] != '\0')
		complete_line[char_index2++] = previous_read[char_index++];
	char_index = 0;
	while (current_read[char_index] != '\0')
		complete_line[char_index2++] = current_read[char_index++];
	complete_line[char_index2] = '\0';
	free(previous_read);
	return (complete_line);
}
