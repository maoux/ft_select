/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 13:58:07 by heynard           #+#    #+#             */
/*   Updated: 2017/07/25 13:58:08 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			fts_move_left(t_shell *shell)
{
	t_lst_args	*tmp;

	if (shell->list->next == shell->list)
		return ;
	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	tmp->prev->current = 1;
	tmp->current = 0;
}

void			fts_move_right(t_shell *shell)
{
	t_lst_args	*tmp;

	if (shell->list->next == shell->list)
		return ;
	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	tmp->next->current = 1;
	tmp->current = 0;
}

void			fts_move_top(t_shell *shell)
{
	t_lst_args	*tmp;
	t_lst_args	*save;
	int			i;

	if (shell->list->next == shell->list)
		return ;
	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	i = 0;
	save = tmp;
	while (i < shell->wbl)
	{
		tmp = tmp->prev;
		i++;
		if (tmp == shell->list && i < shell->wbl)
			return ;
	}
	if (save == shell->list)
		return ;
	save->current = 0;
	tmp->current = 1;
}

void			fts_move_bot(t_shell *shell)
{
	t_lst_args	*tmp;
	t_lst_args	*save;
	int			i;

	if (shell->list->next == shell->list)
		return ;
	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	i = 0;
	save = tmp;
	while (i < shell->wbl)
	{
		tmp = tmp->next;
		i++;
		if (tmp == shell->list)
			return ;
	}
	save->current = 0;
	tmp->current = 1;
}
