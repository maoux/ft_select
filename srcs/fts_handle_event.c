/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_handle_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 17:33:33 by heynard           #+#    #+#             */
/*   Updated: 2017/07/24 17:33:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		fts_select_current(t_shell *shell)
{
	t_lst_args	*tmp;

	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	if (tmp->selected)
		tmp->selected = 0;
	else
	{
		tmp->selected = 1;
		if (tmp->next != tmp)
		{
			tmp->next->current = 1;
			tmp->current = 0;
		}
	}
}

static void		fts_finish(t_shell *shell)
{
	t_lst_args	*tmp;
	int			test;

	test = 0;
	tmp = shell->list;
	tcsetattr(0, TCSADRAIN, shell->save);
	tputs(tgetstr("te", NULL), 1, ft_putcharint);
	tputs(tgetstr("ve", NULL), 1, ft_putcharint);
	if (tmp->selected)
	{
		ft_printf("%s", tmp->value);
		test = 1;
	}
	tmp = tmp->next;
	while (tmp != shell->list)
	{
		if (tmp->selected)
		{
			test ? ft_printf(" %s", tmp->value) : ft_printf("%s", tmp->value);
			test = 1;
		}
		tmp = tmp->next;
	}
	fts_free_shell(shell);
}

static void		fts_inner_handle_event(t_shell *shell, long key)
{
	if (key == ESC_KEY)
		fts_exit(shell);
	if (key == LEFT_ARROW_KEY)
		fts_move_left(shell);
	if (key == RIGHT_ARROW_KEY)
		fts_move_right(shell);
	if (key == SPACE_KEY)
		fts_select_current(shell);
	if (key == ENTER_KEY)
		fts_finish(shell);
}

static void		fts_search(t_shell *shell, char c)
{
	t_lst_args	*tmp;
	t_lst_args	*save;

	if (shell->list == shell->list->next)
		return ;
	tmp = shell->list;
	while (!tmp->current)
		tmp = tmp->next;
	save = tmp;
	tmp = tmp->next;
	while (tmp != save)
	{
		if (tmp->value[0] == c)
		{
			save->current = 0;
			tmp->current = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void			fts_handle_event(t_shell *shell, long key)
{
	if (shell->breaktime == 0)
	{
		fts_inner_handle_event(shell, key);
		if (key == DEL_KEY || key == DELETE_KEY)
		{
			if ((shell->list = fts_delete_elem(shell->list)) == NULL)
				fts_exit(shell);
		}
		if (key == TOP_ARROW_KEY)
			fts_move_top(shell);
		if (key == BOT_ARROW_KEY)
			fts_move_bot(shell);
		if (shell->realmode && key == ONE_KEY)
			fts_check_real_mode(shell);
		if ((key >= (int)'a' && key <= (int)'z') ||
			(key >= (int)'A' && key <= (int)'Z'))
			fts_search(shell, (char)key);
	}
}
