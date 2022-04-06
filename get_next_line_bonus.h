/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:43:12 by lsomrat           #+#    #+#             */
/*   Updated: 2022/04/06 22:59:44 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include<sys/types.h>
# include<sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*read_file(int fd, t_list **buff);
char	*get_line(t_list *buff, char **line);
void	save_readed(t_list **buff, char *buf, int readed);
void	generate_line(char **line, t_list *buff);
void	clear_buff(t_list **buff);
void	free_buff(t_list *buff);
int		get_newline(t_list *buff);
size_t	ft_strlen(const char *s);
t_list	*get_last(t_list *buff);
#endif
