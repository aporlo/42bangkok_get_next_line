/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:41:15 by lsomrat           #+#    #+#             */
/*   Updated: 2022/04/06 23:09:34 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list   *buff[1000];
	char            *line;

	if ((fd < 0 && fd > 999) || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_file(fd, &buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	get_line(buff[fd], &line);
	clear_buff(&buff[fd]);
	if (line[0] == '\0')
	{
		free_buff(buff[fd]);
		buff[fd] = NULL;
		free(line);
		return (NULL);
       	}
	return (line);
}

char	*read_file(int fd, t_list **buff)
{
	char	*buffer;
	int         readed_ptr;

    	readed_ptr = 1;
    	while (!get_newline(*buff) && readed_ptr != 0)
   	{
        	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        	if (!buffer)
            		return (NULL);
        	readed_ptr = read(fd, buffer, BUFFER_SIZE);
        	if (readed_ptr == -1)
        	{
            		free(buffer);
            		return (NULL);
        	}
        	buffer[readed_ptr] = '\0';
        	save_readed(buff, buffer, readed_ptr);
        	free(buffer);
    	}
    	return (buffer);
}

void    get_line(t_list *buff, char **line)
{
	int	i;
	int	j;

    	generate_line(line, buff);
    	if (*line == NULL)
        	return (NULL);
    	j = 0;
    	while (buff)
    	{
        	i = 0;
        	while (buff->content[i])
        	{
            		if (buff->content[i] == '\n')
            		{
                		(*line)[j++] = buff->content[i];
                		break ;
            		}
            		(*line)[j++] = buff->content[i++];
        	}
        	buff = buff->next;
    	}
    	(*line)[j] = '\0';
}

void    clear_buff(t_list **buff)
{
	t_list  *last;
	t_list  *clear;
	int     	i;
	int     	j;

    	clear = malloc(sizeof(t_list));
    	if (!clear && !buff)
        	return;
    	clear->next = NULL;
	last = get_last(*buff);
	i = 0;
    	while (last->content[i] && last->content[i] != '\n')
        	i++;
    	if (last->content && last->content[i] == '\n')
        	i++;
    	clear->content = malloc(sizeof(char)
			* ((ft_strlen(last->content) - i) + 1));
    	if (!(clear->content))
        	return;
    	j = 0;
    	while (last->content[i])
    	{
        	clear->content[j++] = last->content[i++];
    	}
    	clear->content[j] = '\0';
    	free_buff(*buff);
    	*buff = clear;
}
