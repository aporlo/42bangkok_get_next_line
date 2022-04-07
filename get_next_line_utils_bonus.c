/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:33:21 by lsomrat           #+#    #+#             */
/*   Updated: 2022/04/07 22:49:16 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	save_readed(t_list **buff, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if (new->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (*buff == NULL)
	{
		*buff = new;
		return ;
	}
	last = get_last(*buff);
	last->next = new;
}

int	get_newline(t_list *buff)
{
	int		i;
	t_list	*current;

	if (buff == NULL)
		return (0);
	current = get_last(buff);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*generate_line(char **line, t_list *buff)
{
	int	i;
	int	len;

	len = 0;
	while (buff)
	{
		i = 0;
		while (buff->content[i])
		{
			if (buff->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		buff = buff->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
	if (*line == NULL)
		return (NULL);
	return (*line);
}

t_list	*get_last(t_list *buff)
{
	t_list	*current;

	current = buff;
	while (current && current->next)
		current = current->next;
	return (current);
}
