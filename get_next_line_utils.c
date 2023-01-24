/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:37:51 by tayou             #+#    #+#             */
/*   Updated: 2023/01/24 15:36:14 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copy_s1;
	int		size;
	int		i;

	size = ft_strlen(s1);
	copy_s1 = (char *) malloc(sizeof(char) * size + 1);
	if (copy_s1 == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		copy_s1[i] = s1[i];
		i++;
	}
	copy_s1[i] = '\0';
	return (copy_s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	new_string = (char *) malloc(sizeof(char) * total_len + 1);
	if (new_string == 0)
		return (0);
	while (*s1 != '\0')
	{
		*new_string = *s1;
		s1++;
		new_string++;
	}
	while (*s2 != '\0')
	{
		*new_string = *s2;
		s2++;
		new_string++;
	}
	*new_string = '\0';
	return (new_string - s1_len - s2_len);
}

static char	*fill_sub(char *string, char *s, size_t start, size_t actual_size)
{
	size_t	i;

	i = 0;
	while (i < actual_size)
	{
		string[i] = s[start];
		start++;
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	necessary_size;
	size_t	actual_size;

	s_len = ft_strlen(s);
	necessary_size = s_len - start;
	if (necessary_size <= len)
		actual_size = necessary_size;
	else
		actual_size = len;
	substring = (char *) malloc(sizeof(char) * actual_size + 1);
	if (substring == 0)
		return (0);
	substring = fill_sub(substring, (char *) s, (size_t) start, actual_size);
	return (substring);
}
