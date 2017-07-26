/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_putname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 15:47:34 by heynard           #+#    #+#             */
/*   Updated: 2017/07/26 15:47:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static char			fts_check_type(char *name)
{
	struct stat		content;

	if (stat(name, &content) < 0)
		return (' ');
	if (S_ISREG(content.st_mode))
		return ('r');
	if (S_ISDIR(content.st_mode))
		return ('d');
	if (S_ISLNK(content.st_mode))
		return ('l');
	if (S_ISBLK(content.st_mode))
		return ('b');
	if (S_ISFIFO(content.st_mode))
		return ('f');
	if (S_ISSOCK(content.st_mode))
		return ('s');
	if (S_ISWHT(content.st_mode))
		return ('w');
	return (' ');
}

static void			fts_check_regular_file(char *name)
{
	char			*ext;

	ext = ft_strchr(name, '.');
	if (ext != NULL)
	{
		if (!ft_strcmp(ext, ".o"))
			ft_putstr_fd(MAGENTA, STDIN_FILENO);
		else if (!ft_strcmp(ext, ".c"))
			ft_putstr_fd(RED, STDIN_FILENO);
		else
			ft_putstr_fd(GREEN, STDIN_FILENO);
	}
}

void				fts_putname(t_lst_args *elem)
{
	char			type;

	type = fts_check_type(elem->value);
	if (type == 'd')
		ft_putstr_fd(BLUE, STDIN_FILENO);
	if (type == 'l')
		ft_putstr_fd(YELLOW, STDIN_FILENO);
	if (type == 'b')
		ft_putstr_fd(RED3, STDIN_FILENO);
	if (type == 'w')
		ft_putstr_fd(GREEN2, STDIN_FILENO);
	if (type == 's')
		ft_putstr_fd(GREEN3, STDIN_FILENO);
	if (type == 'f')
		ft_putstr_fd(BLUE2, STDIN_FILENO);
	if (type == 's')
		ft_putstr_fd(BLUE3, STDIN_FILENO);
	if (type == 'r')
		fts_check_regular_file(elem->value);
	ft_putstr_fd(elem->value, STDIN_FILENO);
	if (type != ' ')
		ft_putstr_fd(CLEAR, STDIN_FILENO);
}
