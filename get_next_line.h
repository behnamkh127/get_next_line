/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:59:20 by bekhodad          #+#    #+#             */
/*   Updated: 2023/08/20 14:17:57 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}					t_list;

void			fix_line(t_list	**newLine);
char			*get_new_line(t_list	*newLine);
int				append(t_list	**newLine, char	*buf);
void			creat_line(t_list **newLine, int fd);
char			*get_next_line(int fd);
t_list			*find_end(t_list *newLine);
void			copy_str(t_list	*newLine, char	*next_str);
int				found_new_line(t_list *newLine);
int				ft_strlen(t_list	*newLine);
void			do_free(t_list **new_line, t_list *finish, char	*end);

#endif