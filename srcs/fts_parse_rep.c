/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_parse_rep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 16:29:44 by heynard           #+#    #+#             */
/*   Updated: 2017/07/26 16:29:45 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static t_lst_args			*set_begin(void)
{
	t_lst_args				*begin;

	begin = malloc_arg("..");
	if (!begin)
		return (NULL);
	begin->current = 1;
	begin->next = begin;
	begin->prev = begin;
	return (begin);
}

t_lst_args					*fts_parse_rep(t_shell *shell, char *path)
{
	DIR						*ptr;
	struct dirent			*current;
	t_lst_args				*begin;
	t_lst_args				*tmp;

	if ((ptr = opendir(path)) == NULL)
		fts_exit(shell);
	begin = set_begin();
	tmp = begin;
	while ((current = readdir(ptr)) != NULL)
	{
		if ((!ft_strcmp(current->d_name, ".")) ||
			(!ft_strcmp(current->d_name, "..")))
			;
		else
		{
			tmp->next = malloc_arg(current->d_name);
			tmp->next->prev = tmp;
			tmp = tmp->next;
			tmp->next = begin;
			begin->prev = tmp;
		}
	}
	closedir(ptr);
	return (begin);
}

void						fts_check_real_mode(t_shell *shell)
{
	t_lst_args				*tmp;
	t_lst_args				*to_free;
	struct stat				buffer;
	char					*join;

	tmp = shell->list->next;
	while (!tmp->current)
		tmp = tmp->next;
	if (!stat(tmp->value, &buffer))
	{
		if (S_ISDIR(buffer.st_mode))
		{
			join = ft_strjoin(shell->path, "/");
			free(shell->path);
			shell->path = ft_strjoin(join, tmp->value);
			free(join);
			to_free = shell->list;
			shell->list = fts_parse_rep(shell, shell->path);
			fts_free_args(to_free);
		}
	}
}
