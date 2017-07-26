/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 15:01:16 by heynard           #+#    #+#             */
/*   Updated: 2017/07/24 15:01:17 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static size_t		fts_get_colsize(t_shell *shell)
{
	t_lst_args		*tmp;
	size_t			max;

	max = shell->list->len;
	tmp = shell->list->next;
	while (tmp != shell->list)
	{
		max = tmp->len > max ? tmp->len : max;
		tmp = tmp->next;
	}
	return (max + 4);
}

static void			fts_print_elem(t_lst_args *elem, size_t col_size,
									int i, int wbl)
{
	int				space;

	if (elem->selected)
		ft_putstr_fd(HIGHLIGHT, STDIN_FILENO);
	if (elem->current)
		ft_putstr_fd(UNDERLINED, STDIN_FILENO);
	fts_putname(elem);
	ft_putstr_fd("\033[0m", STDIN_FILENO);
	space = -1;
	while (++space < col_size - elem->len)
		ft_putchar_fd(' ', STDIN_FILENO);
	if (i % wbl == 0)
		ft_putchar_fd('\n', STDIN_FILENO);
}

static int			fts_wordsbyline(t_shell *shell)
{
	shell->col_size = fts_get_colsize(shell);
	return (shell->ws->ws_col / shell->col_size);
}

static int			fts_count_elem(t_lst_args *list)
{
	t_lst_args		*tmp;
	int				nbelem;

	nbelem = 1;
	tmp = list->next;
	while (tmp != list)
	{
		nbelem += 1;
		tmp = tmp->next;
	}
	return (nbelem);
}

int					fts_display_args(t_shell *shell)
{
	t_lst_args		*tmp;
	int				i;

	i = 1;
	tputs(tgetstr("cl", NULL), 1, ft_putcharint);
	shell->wbl = fts_wordsbyline(shell);
	shell->nbelem = fts_count_elem(shell->list);
	if (shell->wbl == 0 || shell->nbelem / shell->wbl >= shell->ws->ws_row)
	{
		shell->breaktime = 1;
		return (-1);
	}
	fts_display_feature(shell, 0);
	shell->breaktime = 0;
	tmp = shell->list->next;
	fts_print_elem(shell->list, shell->col_size, i, shell->wbl);
	i += 1;
	while (tmp != shell->list)
	{
		fts_print_elem(tmp, shell->col_size, i, shell->wbl);
		tmp = tmp->next;
		i++;
	}
	fts_display_feature(shell, 1);
	return (0);
}
