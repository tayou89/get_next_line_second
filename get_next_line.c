/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:19:27 by tayou             #+#    #+#             */
/*   Updated: 2023/01/24 22:48:19 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_newline(t_list *backup)
{
	int		i;
	char	*str;

	while (backup->next != NULL)
	{
		i = 0;
		while ((backup->content)[i] != '\0')
		{
			if ((backup->content)[i] == '\n')
				return (i);
			i++;
		}
		backup = backup->next;
	}
	return (-1);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*copy;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		copy = (*lst)->next;
		(*lst)->content = NULL;
		free(*lst);
		*lst = copy;
	}
	*lst = NULL;
}

void	malloc_fill_content(char **string, char *buf)
{
	int	size;
	int	i;

	i = 0;
	while (buf[i] != '\0')
		i++;
	size = i;
	*string = (char *) malloc(sizeof(char) * size + 1);
	if (*string == 0)
		return ;
	i = 0;
	while (buf[i] != '\0')
	{
		(*string)[i] = buf[i];
		i++;
	}
	(*string)[i] = '\0';
}

void	ft_lstnew(t_list **lst, char *content)
{
	*lst = (t_list *) malloc(sizeof(t_list));
	if (*lst == NULL)
		return ;
	(*lst)->content = content;
	(*lst)->next = NULL;
}

void	ft_lstadd_back(t_list **backup, char *buf)
{
	t_list	*new_list;
	t_list	*copy_backup;

	new_list = (t_list *) malloc(sizeof(t_list));
	if (new_list == NULL)
	{
		ft_lstclear(backup);
		return ;
	}
	malloc_fill_content(&(new_list->content), buf);
	if (new_list->content == 0)
	{
		ft_lstclear(backup);
		return ;
	}
	new_list->next = NULL;
	if (*backup == NULL)
	{
		*backup = new_list;
		return ;
	}
	copy_backup = *backup;
	while (copy_backup->next != NULL)
		copy_backup = copy_backup->next;
	copy_backup->next = new_list;
}

int	get_size(t_list *backup)
{
	int		size;
	int		i;

	i = 0;
	while (backup->next != NULL)
	{
		while ((backup->content)[i] != '\0' && (backup->content)[i] != '\n')
			i++;
		backup = backup->next;
	}
	if ((backup->content)[i] == '\n')
		size = i + 1;
	else
		size = i;
	return (size);
}

void	get_line(char **line, t_list *backup)
{
	int		size;
	int		line_index;
	int		i;

	size = get_size(backup);
	*line = (char *) malloc(sizeof(char) * size + 1);
	if (*line == 0)
		return ;
	line_index = 0;
	while (backup->next != NULL)
	{
		i = 0;
		while ((backup->content)[i] != '\0')
		{
			(*line)[line_index] = (backup->content)[i];
			if ((backup->content)[i] == '\n')
				break ;
			line_index++;
			i++;
		}
		backup = backup->next;
	}
}

void	renewal_backup(t_list **backup)
{
	t_list	*copy;
	int		newline_point;
	int		i;

	while ((*backup)->next != NULL)
	{
		copy = (*backup)->next;
		free((*backup)->content);
		*backup = copy;
	}
	newline_point = check_newline(*backup);
	if (newline_point >= 0)
	{
		i = 0;
		while (((*backup)->content)[newline_point] != '\0')
		{
			((*backup)->content)[i] = ((*backup)->content)[newline_point + 1];
			i++;
			newline_point++;
		}
	}
}

char	*get_next_line(int fd)
{
	int				read_size;
	char			buf[BUFFER_SIZE + 1];
	static t_list	*backup;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	ft_lstnew(&backup, NULL);
	if (backup == NULL)
		return (NULL);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		ft_lstadd_back(&backup, buf);
		if (backup == NULL)
			return (NULL);
		if (check_newline(backup) >= 0)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	get_line(&line, backup);
	renewal_backup(&backup);
	return (line);
}		
