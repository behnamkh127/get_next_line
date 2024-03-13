/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:54:25 by bekhodad          #+#    #+#             */
/*   Updated: 2023/08/20 14:09:08 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*new_line;
	char			*next_line;
	t_list			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		while (new_line)
		{
			temp = (new_line)->next;
			free((new_line)->line);
			free(new_line);
			new_line = temp;
		}
		new_line = NULL;
		return (0);
	}
	creat_line(&new_line, fd);
	if (!new_line)
		return (0);
	next_line = get_new_line(new_line);
	fix_line(&new_line);
	return (next_line);
}

void	creat_line(t_list **new_line, int fd)
{
	int		count;
	char	*buf;

	while (!found_new_line(*new_line))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		count = read(fd, buf, BUFFER_SIZE);
		if (!count)
		{
			free(buf);
			return ;
		}
		buf[count] = '\0';
		if (!append (new_line, buf))
			return ;
	}
}

int	append(t_list **new_line, char *buf)
{
	t_list	*newptr;
	t_list	*end;

	end = find_end(*new_line);
	newptr = malloc(sizeof(t_list));
	if (!newptr)
		return (0);
	if (!end)
		*new_line = newptr;
	else
		end->next = newptr;
	newptr->line = buf;
	newptr->next = NULL;
	return (1);
}

char	*get_new_line(t_list	*new_line)
{
	int		len;
	char	*next_str;

	if (!new_line)
		return (0);
	len = ft_strlen(new_line);
	next_str = malloc (len + 1);
	if (!next_str)
		return (0);
	copy_str(new_line, next_str);
	return (next_str);
}

void	fix_line(t_list	**new_line)
{
	int		i;
	int		j;
	t_list	*end;
	t_list	*finish;
	char	*new;

	i = 0;
	new = (char *)malloc(BUFFER_SIZE + 1);
	if (!new)
		return ;
	finish = malloc(sizeof(t_list));
	if (!finish)
		return ;
	end = find_end(*new_line);
	while (end->line[i] && end->line[i] != '\n')
		++i;
	j = 0;
	while (end->line[i] && end->line[++i])
		new[j++] = end->line[i];
	new[j] = '\0';
	finish->line = new;
	finish->next = NULL;
	do_free(new_line, finish, new);
}

// int main(void){
//     int fd;
//     char *line;
//     int lines;

//     lines = 1;
//     fd = open ("test.txt", O_RDONLY);
//     while ((line = get_next_line(fd)))
//         printf("%d->%s", lines++, line);
// 	close(fd);
// }