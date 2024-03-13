/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:59:47 by bekhodad          #+#    #+#             */
/*   Updated: 2023/08/19 12:25:52 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(t_list	*new_line)
{
	int	len;
	int	i;

	if (!new_line)
		return (0);
	len = 0;
	while (new_line)
	{
		i = 0;
		while (new_line->line[i])
		{
			if (new_line->line[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		new_line = new_line->next;
	}
	return (len);
}

int	found_new_line(t_list *new_line)
{
	int	i;

	if (!new_line)
		return (0);
	while (new_line)
	{
		i = 0;
		while (new_line->line[i] && i < BUFFER_SIZE)
		{
			if (new_line->line[i] == '\n')
				return (1);
			++i;
		}
		new_line = new_line->next;
	}
	return (0);
}

void	copy_str(t_list	*new_line, char	*next_str)
{
	int	i;
	int	j;

	if (!next_str)
		return ;
	j = 0;
	while (new_line)
	{
		i = 0;
		while (new_line->line[i])
		{
			if (new_line->line[i] == '\n')
			{
				next_str[j++] = '\n';
				next_str[j] = '\0';
				return ;
			}
			next_str[j++] = new_line->line[i++];
		}
		new_line = new_line->next;
	}
	next_str[j] = '\0';
}

t_list	*find_end(t_list *new_line)
{
	if (!new_line)
		return (0);
	while (new_line->next)
		new_line = new_line->next;
	return (new_line);
}

void	do_free(t_list **new_line, t_list *finish, char	*new)
{
	t_list	*temp;

	if (!*new_line)
		return ;
	while (*new_line)
	{
		temp = (*new_line)->next;
		free((*new_line)->line);
		free(*new_line);
		*new_line = temp;
	}
	*new_line = 0;
	if (finish->line[0])
		*new_line = finish;
	else
	{
		free(new);
		free(finish);
	}
}
