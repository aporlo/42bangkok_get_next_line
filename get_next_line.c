/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 23:09:24 by lsomrat           #+#    #+#             */
/*   Updated: 2022/04/04 23:23:04 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
    static t_list   *buff;
    char            *line;

	if ((fd < 0 && fd > 999) || read(fd, '\0', 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    line = NULL;
    read_file(fd, &buff);
    if (buff == NULL)
        return (NULL);
    get_line(buff, &line);
    clear_buff(&buff);
    if (line[0] == '\0')
    {
        free_buff(buff);
        buff = NULL;
        free(line);
        return (NULL);
    }
    return (line);
}

char    *read_file(int fd, t_list **buff)
{
    char    *buffer;
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

char    *get_line(t_list *buff, char **line)
{
    int i;
    int j;

    // if (buff == NULL)
    //     return;
    generate_line(line, buff);
    if (*line == NULL)
        return (NULL);
    j = 0;
    while (buff)
    {
        i = 0;
        while(buff->content[i])
        {
            if (buff->content[i] == '\n')
            {
                (*line)[j++] = buff->content[i];
                break;
            }
            (*line)[j++] = buff->content[i++];
        }
        buff = buff->next;
    }
    (*line)[j] = '\0';
    return (*line);
}

void    clear_buff(t_list **buff)
{
    t_list  *last;
    t_list  *clear;
    int     i;
    int     j;

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
    clear->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
    if (!(clear->content))
        return;
    j = 0;
    while (last->content[i])
    {
        clear->content[j] = last->content[i];
        i++;
        j++;
    }
    clear->content[j] = '\0';
    free_buff(*buff);
    *buff = clear;
}