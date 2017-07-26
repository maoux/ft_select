/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:40:13 by heynard           #+#    #+#             */
/*   Updated: 2017/07/20 14:42:11 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			fts_handle_signal(void)
{
	signal(SIGWINCH, fts_check_signal);
	signal(SIGINT, fts_check_signal);
	signal(SIGQUIT, fts_check_signal);
	signal(SIGTERM, fts_check_signal);
	signal(SIGKILL, fts_check_signal);
	signal(SIGSTOP, fts_check_signal);
	signal(SIGCONT, fts_check_signal);
	signal(SIGTSTP, fts_check_signal);
	signal(SIGHUP, fts_check_signal);
}

static void			fts_handle_arguments(t_shell *shell, char **av, int ac)
{
	if (!ft_strcmp(av[1], "--real-mode") && ac == 2)
	{
		if (!(shell->list = fts_parse_rep(shell, ".")))
			fts_exit(shell);
		shell->realmode = 1;
		shell->path = ft_strdup(".");
	}
	else
	{
		if (!(shell->list = fts_parse_argv(av)))
			fts_exit(shell);
		shell->realmode = 0;
		shell->path = NULL;
	}
}

static void			ft_select(char **av, int ac)
{
	t_shell			*shell;
	char			*line;
	long			c;

	if (!(shell = fts_handle_shell_struct()))
	{
		ft_putendl_fd("ft_select: memory allocation failed", STDERR_FILENO);
		return ;
	}
	fts_handle_arguments(shell, av, ac);
	fts_activate_select(shell);
	fts_handle_signal();
	while (1)
	{
		c = 0;
		fts_display_args(shell);
		read(0, &c, 8);
		fts_handle_event(shell, c);
	}
	fts_exit(shell);
}

int					ft_putcharint(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

int					main(int ac, char **av)
{
	char			*term_value;

	if (ac < 2)
	{
		ft_putstr_fd("ft_select: usage: ", STDERR_FILENO);
		ft_putendl_fd("./ft_select choix1 [choix2 choix3 ...]", STDERR_FILENO);
		return (-1);
	}
	if ((term_value = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("ft_select: please set env ", STDERR_FILENO);
		ft_putendl_fd("variable TERM to use ft_select", STDERR_FILENO);
		return (-1);
	}
	if (tgetent(NULL, term_value) <= 0)
	{
		ft_putendl_fd("ft_select: incorrect variable TERM", STDERR_FILENO);
		return (-1);
	}
	ft_select(av, ac);
	return (0);
}
