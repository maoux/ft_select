/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 14:34:22 by heynard           #+#    #+#             */
/*   Updated: 2017/07/24 14:34:23 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void					fts_free_arg(t_lst_args *to_free)
{
	if (to_free)
	{
		if (to_free->value)
			ft_strdel(&(to_free->value));
		free(to_free);
	}
}

t_lst_args					*malloc_arg(const char *value)
{
	t_lst_args				*ret;

	if (!(ret = malloc(sizeof(t_lst_args))))
		return (NULL);
	ret->next = NULL;
	ret->prev = NULL;
	ret->selected = 0;
	ret->current = 0;
	ret->len = ft_strlen(value);
	ret->value = ft_strdup(value);
	return (ret);
}

void						fts_free_args(t_lst_args *list)
{
	t_lst_args				*tmp;
	t_lst_args				*to_free;

	tmp = list->next;
	while (tmp != list)
	{
		to_free = tmp;
		tmp = tmp->next;
		fts_free_arg(to_free);
	}
	fts_free_arg(list);
}

t_lst_args					*fts_delete_elem(t_lst_args *list)
{
	t_lst_args				*tmp;

	if (list->current && list->next == list)
	{
		fts_free_arg(list);
		return (NULL);
	}
	else if (list->current)
	{
		tmp = list;
		list = tmp->next;
		list->prev = tmp->prev;
		list->prev->next = list;
		fts_free_arg(tmp);
		list->current = 1;
		return (list);
	}
	tmp = list;
	while (!tmp->current)
		tmp = tmp->next;
	tmp->next->current = 1;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	fts_free_arg(tmp);
	return (list);
}

t_lst_args					*fts_parse_argv(char **av)
{
	t_lst_args				*begin;
	t_lst_args				*tmp;
	int						i;

	i = 1;
	begin = malloc_arg(av[i++]);
	if (!begin)
		return (NULL);
	begin->current = 1;
	begin->next = begin;
	begin->prev = begin;
	tmp = begin;
	while (av[i])
	{
		tmp->next = malloc_arg(av[i]);
		tmp->next->prev = tmp;
		tmp = tmp->next;
		tmp->next = begin;
		begin->prev = tmp;
		i++;
	}
	return (begin);
}
