/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:29:18 by bekhodad          #+#    #+#             */
/*   Updated: 2023/08/20 14:07:47 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*new_line[4096];
	char			*next_line;
	t_list			*temp;

	if (fd < 0 || fd > 4096)
		return (0);
	if (BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		while (new_line[fd])
		{
			temp = (new_line[fd])->next;
			free((new_line[fd])->line);
			free(new_line[fd]);
			new_line[fd] = temp;
		}
		new_line[fd] = NULL;
		return (0);
	}
	creat_line(new_line, fd);
	if (!new_line[fd])
		return (0);
	next_line = get_new_line(new_line[fd]);
	fix_line(&new_line[fd]);
	return (next_line);
}

void	creat_line(t_list **new_line, int fd)
{
	int		count;
	char	*buf;

	while (!found_new_line(new_line[fd]))
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
		append (new_line, buf, fd);
	}
}

int	append(t_list	**new_line, char	*buf, int fd)
{
	t_list	*newptr;
	t_list	*end;

	end = find_end(new_line[fd]);
	newptr = malloc (sizeof (t_list));
	if (!newptr)
		return (0);
	if (!end)
		new_line[fd] = newptr;
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

// int main(void)
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("Error opening file");
//         return 1;
//     }

//     char *line;

//     while ((line = get_next_line(fd1)) != NULL)
//     {
//         printf("fd1: %s\n", line);
//         free(line);
//     }

//     while ((line = get_next_line(fd2)) != NULL)
//     {
//         printf("fd2: %s\n", line);
//         free(line);
//     }

//     close(fd1);
//     close(fd2);

//     return 0;
// }

// int main(void)
// {
//     int fd1 = open("file1.txt", O_RDONLY);
//     int fd2 = open("file2.txt", O_RDONLY);
//     int fd_high = 5000;

//     // if (fd1 < 0 || fd2 < 0 || fd_high < 0)
//     // {
//     //     perror("Error opening file");
//     //     return 1;
//     // }

//     char *line;

// //     while ((line = get_next_line(fd1)) != NULL)
// //     {
// //         printf("fd1: %s\n", line);
// //         free(line);
// //     }

// //    while ((line = get_next_line(fd_high)) != NULL)
// //     {
// //         printf("fd_high: %s\n", line);
// //         free(line);
// //     }

// //     while ((line = get_next_line(fd2)) != NULL)
// //     {
// //         printf("fd2: %s\n", line);
// //         free(line);
// //     }
// 	line = get_next_line(fd1);
// 	printf("fd1: %s\n", line);
// 	line = get_next_line(fd2);
// 	printf("fd2: %s\n", line);
// 	line = get_next_line(fd_high);
// 	printf("fd_high: %s\n", line);
//     close(fd1);
//     close(fd2);
//     close(fd_high);

//     return 0;
// }
