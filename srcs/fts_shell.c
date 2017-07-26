/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:05:25 by heynard           #+#    #+#             */
/*   Updated: 2017/07/20 15:05:26 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static t_shell		*fts_set_shell(void)
{
	t_shell			*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	if (!(shell->ws = (struct winsize *)malloc(sizeof(struct winsize))))
		return (fts_free_shell(shell));
	if (ioctl(0, TIOCGWINSZ, shell->ws) < 0)
		return (fts_free_shell(shell));
	if (!(shell->save = (struct termios *)malloc(sizeof(struct termios))))
		return (fts_free_shell(shell));
	if (!(shell->term = (struct termios *)malloc(sizeof(struct termios))))
		return (fts_free_shell(shell));
	if (tcgetattr(0, shell->save) < 0)
		return (fts_free_shell(shell));
	tcgetattr(0, shell->term);
	shell->term->c_lflag &= ~(ICANON);
	shell->term->c_lflag &= ~(ECHO);
	shell->term->c_cc[VMIN] = 1;
	shell->term->c_cc[VTIME] = 100;
	shell->breaktime = 0;
	return (shell);
}

void				fts_update_shell(t_shell *shell)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	shell->ws->ws_col = w.ws_col;
	shell->ws->ws_row = w.ws_row;
}

t_shell				*fts_handle_shell_struct(void)
{
	static t_shell	*shell = NULL;

	if (!shell)
	{
		shell = fts_set_shell();
		if (!shell)
			return (NULL);
	}
	fts_update_shell(shell);
	return (shell);
}

t_shell				*fts_free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->ws)
			free(shell->ws);
		if (shell->save)
			free(shell->save);
		if (shell->term)
			free(shell->term);
		if (shell->list)
			fts_free_args(shell->list);
		if (shell->path)
			free(shell->path);
		free(shell);
	}
	exit(0);
}
