/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_signal_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 19:39:30 by heynard           #+#    #+#             */
/*   Updated: 2017/07/24 19:39:31 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		fts_signal_ws_change(void)
{
	t_shell		*save;

	save = fts_handle_shell_struct();
	fts_update_shell(save);
	tputs(tgetstr("cl", NULL), 1, ft_putcharint);
	fts_display_args(save);
}

static void		fts_quit(void)
{
	t_shell		*save;

	save = fts_handle_shell_struct();
	fts_exit(save);
}

static void		fts_suspended(int signum)
{
	char		buf[2];
	t_shell		*save;

	save = fts_handle_shell_struct();
	buf[1] = 0;
	buf[0] = save->save->c_cc[VSUSP];
	tcsetattr(0, TCSADRAIN, save->save);
	tputs(tgetstr("te", NULL), 1, ft_putcharint);
	tputs(tgetstr("ve", NULL), 1, ft_putcharint);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, buf);
	ft_printf(" ");
}

static void		fts_continued(int signum)
{
	t_shell		*save;

	signal(SIGTSTP, fts_suspended);
	signal(SIGCONT, fts_continued);
	save = fts_handle_shell_struct();
	tcsetattr(0, TCSADRAIN, save->term);
	tputs(tgetstr("ti", NULL), 1, ft_putcharint);
	tputs(tgetstr("vi", NULL), 1, ft_putcharint);
	tputs(tgetstr("cl", NULL), 1, ft_putcharint);
	fts_display_args(save);
}

void			fts_check_signal(int signum)
{
	if (signum == SIGWINCH)
		fts_signal_ws_change();
	if (signum == SIGINT)
		fts_quit();
	if (signum == SIGKILL)
		fts_quit();
	if (signum == SIGQUIT)
		fts_quit();
	if (signum == SIGTERM)
		fts_quit();
	if (signum == SIGSTOP)
		fts_suspended(signum);
	if (signum == SIGCONT)
		fts_continued(signum);
	if (signum == SIGTSTP)
		fts_suspended(signum);
	if (signum == SIGHUP)
		fts_quit();
}
