/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_runtermconfig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 17:21:55 by heynard           #+#    #+#             */
/*   Updated: 2017/07/20 17:21:56 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void				fts_activate_select(t_shell *shell)
{
	tcsetattr(0, TCSADRAIN, shell->term);
	tputs(tgetstr("ti", NULL), 1, ft_putcharint);
	tputs(tgetstr("vi", NULL), 1, ft_putcharint);
	tputs(tgetstr("cl", NULL), 1, ft_putcharint);
}

void				fts_exit(t_shell *shell)
{
	tcsetattr(0, TCSADRAIN, shell->save);
	tputs(tgetstr("te", NULL), 1, ft_putcharint);
	tputs(tgetstr("ve", NULL), 1, ft_putcharint);
	fts_free_shell(shell);
}
