/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:27:49 by heynard           #+#    #+#             */
/*   Updated: 2017/07/20 14:28:09 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../libft/includes/libft.h"
# include <sys/ioctl.h>
# include <term.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>

# define ESC_KEY			27
# define SPACE_KEY			32
# define ENTER_KEY			10
# define RIGHT_ARROW_KEY	4414235
# define LEFT_ARROW_KEY		4479771
# define TOP_ARROW_KEY		4283163
# define BOT_ARROW_KEY		4348699
# define DEL_KEY			127
# define DELETE_KEY			2117294875
# define ONE_KEY			49

# define UNDERLINED			"\033[4m"
# define HIGHLIGHT			"\033[7m"
# define YELLOW				"\033[33m"
# define YELLOW2			"\033[33;1m"
# define YELLOW3			"\033[33;2m"
# define YELLOW4			"\033[33;3m"
# define RED				"\033[31m"
# define RED2				"\033[31;1m"
# define RED3				"\033[31;2m"
# define RED4				"\033[31;3m"
# define GREEN				"\033[32m"
# define GREEN2				"\033[32;1m"
# define GREEN3				"\033[32;2m"
# define GREEN4				"\033[32;3m"
# define BLUE				"\033[34m"
# define BLUE2				"\033[34;1m"
# define BLUE3				"\033[34;2m"
# define BLUE4				"\033[34;3m"
# define MAGENTA			"\033[35m"
# define MAGENTA2			"\033[35;1m"
# define MAGENTA3			"\033[35;2m"
# define MAGENTA4			"\033[35;3m"
# define CLEAR				"\033[0m"

typedef struct		s_shell
{
	size_t				col_size;
	char				*path;
	int					realmode;
	int					wbl;
	int					nbelem;
	short int			breaktime;
	struct winsize		*ws;
	struct termios		*save;
	struct termios		*term;
	struct s_lst_args	*list;
}					t_shell;

typedef struct		s_lst_args
{
	char				*value;
	size_t				len;
	short int			selected;
	short int			current;
	struct s_lst_args	*prev;
	struct s_lst_args	*next;
}					t_lst_args;

t_shell				*fts_handle_shell_struct();
t_lst_args			*fts_parse_argv(char **av);
t_shell				*fts_free_shell(t_shell *shell);
int					ft_putcharint(int c);
void				fts_activate_select(t_shell *shell);
void				fts_exit(t_shell *shell);
int					fts_display_args(t_shell *shell);
void				fts_free_args(t_lst_args *list);
void				fts_handle_event(t_shell *shell, long key);
t_lst_args			*fts_delete_elem(t_lst_args *list);
void				fts_update_shell(t_shell *shell);
int					fts_display_feature(t_shell *shell, int option);
void				fts_putname(t_lst_args *elem);
t_lst_args			*malloc_arg(const char *value);
t_lst_args			*fts_parse_rep(t_shell *shell, char *path);
void				fts_check_real_mode(t_shell *shell);
/*
** MOVING FUNCTION
*/

void				fts_move_right(t_shell *shell);
void				fts_move_left(t_shell *shell);
void				fts_move_top(t_shell *shell);
void				fts_move_bot(t_shell *shell);

/*
** SIGNAL HANDLER
*/

void				fts_check_signal(int signum);

#endif
