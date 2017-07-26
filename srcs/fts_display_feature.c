/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_display_feature.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 13:57:46 by heynard           #+#    #+#             */
/*   Updated: 2017/07/26 13:57:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			display_top_inner(void)
{
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(RED3, STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putendl_fd("\n", STDIN_FILENO);
}

static void			display_top(t_shell *shell)
{
	int				i;

	i = -1;
	ft_putstr_fd(RED3, STDIN_FILENO);
	ft_putchar_fd('/', STDIN_FILENO);
	while (++i < shell->ws->ws_col - 3)
		ft_putchar_fd('*', STDIN_FILENO);
	ft_putendl_fd("\\", STDIN_FILENO);
	i = -1;
	ft_putstr_fd(RED3, STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(YELLOW, STDIN_FILENO);
	while (++i < (shell->ws->ws_col - 12) / 2)
		ft_putchar_fd('-', STDIN_FILENO);
	i = -1;
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(RED, STDIN_FILENO);
	ft_putstr_fd("FT_SELECT", STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(YELLOW, STDIN_FILENO);
	while (++i < (shell->ws->ws_col - 11) / 2)
		ft_putchar_fd('-', STDIN_FILENO);
	display_top_inner();
}

static void			display_bot(t_shell *shell)
{
	int				i;

	ft_putendl_fd("\n", STDIN_FILENO);
	i = -1;
	ft_putstr_fd(RED3, STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(YELLOW, STDIN_FILENO);
	while (++i < (shell->ws->ws_col - 3))
		ft_putchar_fd('-', STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
	ft_putstr_fd(RED3, STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	ft_putchar_fd('\n', STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	i = -1;
	while (++i < (shell->ws->ws_col - 3))
		ft_putchar_fd('_', STDIN_FILENO);
	ft_putchar_fd('|', STDIN_FILENO);
	ft_putstr_fd(CLEAR, STDIN_FILENO);
}

int					fts_display_feature(t_shell *shell, int option)
{
	int				nbl;

	nbl = shell->nbelem / shell->wbl;
	if (nbl + 8 > shell->ws->ws_row || shell->ws->ws_col < 16)
		return (1);
	if (option == 0)
		display_top(shell);
	if (option == 1)
		display_bot(shell);
	return (0);
}
