/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:28:59 by lsomrat           #+#    #+#             */
/*   Updated: 2022/04/07 02:37:22 by lsomrat          ###   ########.fr       */
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
		new->content[i++] = buf[i++];
	new->content[i] = '\0';
	if (*buff == NULL)
	{
		*buff = new;
		return ;
	}
	last = buff;
	while (last && last->next)
		last = last->next;
	last->next = new;
}

int	get_newline(t_list *buff)
{
	int		i;
	t_list	*current;

	if (buff == NULL)
		return (0);
	current = buff;
	while (current && current->next)
		current = current->next;
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	generate_line(char **line, t_list *buff)
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
}

void	free_buff(t_list *buff)
{
	t_list	*current;
	t_list	*next;

	current = buff;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
