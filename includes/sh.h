/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolabour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 04:26:44 by jolabour          #+#    #+#             */
/*   Updated: 2019/01/25 02:43:08 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <pwd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

# define OPTION_TEST 15
# define NB_INPUT_SELECT 8
# define NB_INPUT 17
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define HOME 4741915
# define END 4610843
# define CTRL_C 3
# define CTRL_D 4
# define DEL 127
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define TAB 9
# define OPT_B 11241698
# define OPT_F 37574
# define OPT_C 42947
# define OPT_X 8948194
# define OPT_V 10127586
# define OPT_UP 1096489755
# define OPT_DOWN 1113266971
# define SET_FG_RED		"\x1b[38;5;196m"
# define RESET_COLOR	"\x1b[0m"

# ifdef MINISHELL
#  define PROG_NAME "minishell"
# elif defined _21SH
#  define PROG_NAME "21sh"
# else
#  define PROG_NAME "21sh"
# endif

/*
** }}}
*/

typedef enum		e_errno_val
{
	_ENOMEM = 1,
	_ENAMETOOLONG,
	_ENOENV,
	_ENAMEENV,
	_ENOHOME,
	_ENOUSER,
	_ENOVAR,
	_ENOCMD,
	_ELOOP,
	_ENOTDIR,
	_EINVAL,
	_ENOENT,
	_ENOX,
	_ERRNO_VALUES
}					t_errno;

static t_errno		g_errno;
static const char	*g_errors[_ERRNO_VALUES];

typedef struct		s_env
{
	char			*str;
	struct s_env	*next;
}					t_env;

# define BUCKET_CONTENT	t_bucket_content

typedef struct		s_bucket_content
{
	struct s_bucket_content	*next;
	char					*name;
	char					*path;
	size_t					pathlen;
}					BUCKET_CONTENT;

# define BUCKET	t_bucket
typedef struct		s_bucket
{
	BUCKET_CONTENT	*first;
	uint8_t			length;
}					BUCKET;

typedef struct 		s_ht
{
# define INITIAL_HASHTABLE_SIZE (1U << 9)
	BUCKET		buckets[INITIAL_HASHTABLE_SIZE];
	uint16_t	used;
	uint16_t	capacity;
}					t_ht;

typedef struct termios	t_term;
typedef struct termios  t_reset;

typedef struct		s_stdin
{
	int				line_pos;
	int				len_line;
	char			*str_to_paste;
	int				nb_line;
	int				start_und;
	int				end_und;
	int				ctrlc;
	int				cursor_pos;
	int				save_pos;
	int				size_of_input;
	char			*input;
}					t_stdin;

enum				e_token
{
	WORD,
	OPERATOR,
	NEWLINE,
};

enum e_token				g_token;

enum				e_operator
{
	NONE,
	PIPE,
	SEMI,
	GREAT,
	LESS,
	GREATAND,
	DLESS,
	DGREAT,
};

enum e_operator			g_operator;

typedef struct		s_lexer
{
	char			*str;
	int				token_type;
	int				operator_type;
	int				quote;
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_history
{
	char			*str;
	struct s_history *next;
	struct s_history *prev;
}					t_history;

typedef struct		s_history_mark
{
	t_history		*begin;
	t_history		*last;
	t_history		*cur;
	char 			*last_str;
	int				pos;
	int				size;
	}					t_history_mark;

typedef struct		s_var_loc
{
	int				HISTSIZE;
}					t_var_loc;

typedef struct		s_argv
{
  char		**argv;
  int		pos_str;
  int		cur_str;
  int		error_code;
  int		size;
}			t_argv;

typedef struct		s_42sh
{
	char			**tokens;
	t_argv			*argv;
	char			*valide_path;
	int				winsize;
	int				prompt_len;
	char			*pwd;
	char			**bin_dirs;
	char			**copy_env;
	char			*path_history;
	int				token_nbr;
	bool			need_get_line;
	t_lexer			*lexer;
	int				lex_pos;
	t_stdin			*stdin;
	t_history_mark	*history_mark;
	char			*line_to_replace;
	int				substitute_on;
	t_env			*env;
  	t_term			term;
  t_reset			reset_term;
  	t_ht			hashtable;
	t_var_loc		*var_local;
}					t_42sh;

typedef				void(*t_ak)(t_42sh *sh);
typedef				void(*t_test)(t_42sh *sh, struct stat info);

/*****************************************************************************\
|                               SELECT_MODE                                   |
\*****************************************************************************/

/*
** select_mode
*/

void				select_mode(t_42sh *sh);
void				clean_print_select(t_42sh *sh);

/*
** keymap_select
*/

int					check_input_select(t_42sh *sh, long buf);

/*
** move_select_mode
*/

void				move_to_right_select(t_42sh *sh);
void				move_to_left_select(t_42sh *sh);

/*
** exit_select_mode
*/

void				exit_select_mode(t_42sh *sh, int pos);

/*
** action_select_mode
*/

void				copy_select(t_42sh *sh);
void				del_select(t_42sh *sh);
void				cut_select(t_42sh *sh);

/*****************************************************************************\
|                               LINE_EDITION                                  |
\*****************************************************************************/

/*
** stdin
*/

int				get_line(t_42sh *sh);
int				get_winsize(void);
void			ft_paste(t_42sh *sh);
void			clean_print(t_42sh *sh);
int				get_curent_line(t_42sh *sh);
void			up_input(t_42sh *sh);

/*
** check_input
*/

int				check_input(t_42sh *sh, long buf);

/*
** control_action
*/

void			ctrlc_action(t_42sh *sh);
void			ctrld_action(t_42sh *sh);
void			paste(t_42sh *sh);

/*
** insert_mode
*/

void				insert_mode_on(void);
void				insert_mode_off(void);

/*
** manip_input
*/

void				add_char(long input, t_42sh *sh);
void				delete_char(t_42sh *sh);
void				delete_input(t_42sh *sh);
void				delete_input_buf(t_42sh *sh);
void				delete_cut(t_42sh *sh);
void				delete_after_cursor(t_42sh *sh);
void				delete(void);

/*
** process
*/

void				process(t_42sh *sh);

/*
** move_arrows
*/

int					putchar_custom(int c);
void				move_to_right(t_42sh *sh);
void				move_to_left(t_42sh *sh);
void				move_to_start(t_42sh *sh);
void				move_to_end(t_42sh *sh);

/*
** move_word
*/

void				move_to_begin_word(t_42sh *sh);
void				move_to_end_word(t_42sh *sh);

/*
** move_line
*/

void				move_down(t_42sh *sh);
void				move_up(t_42sh *sh);


/*****************************************************************************\
|                                   LEXER                                     |
\*****************************************************************************/

void				get_word(t_42sh *sh);
void				get_operator(t_42sh *sh);
void				get_newline(t_42sh *sh);
void				ft_lexer(t_42sh *sh);
int					ft_is_blank(char c);
int					ft_is_newline(char c);
int					ft_is_operator(char c);
void				add_token(t_42sh *sh, char *str, int token_type, int operator_type, int quote);
void				del_lexer(t_lexer **lexer);
int					get_squote(t_42sh *sh, int i, int *quote);
int					get_dquote(t_42sh *sh, int i, int *quote);
void				print_lexer(t_42sh *sh);

/*****************************************************************************\
|                                  PROCESS                                    |
\*****************************************************************************/

/*
 ** process
 */

void			process(t_42sh *sh);

/*
** prompt
*/

void			prompt(t_env *list, t_42sh *sh);

/*
** hash_table
*/

BUCKET_CONTENT	*ht_lookup(const char *s, t_ht *ht);
BUCKET_CONTENT	*ht_insert(const char *path, const char *name, t_ht *ht);
void			ht_delete(const char *name, t_ht *ht);
void			init_hashtable(t_42sh *sh);
void			print_hashtable(t_ht ht);

/*****************************************************************************\
|                               INIT_SHELL                                    |
\*****************************************************************************/

/*
** list
*/

int					len_list(t_env *env);
char				**list_to_tab(t_env *env, char **copy_env);
t_env				*create_node(char *str);
void				lst_push(t_env **head, t_env *new);
t_env				*set_list(char **env);

/*
** getenv
*/

char				*ft_getenv(t_env *list, const char *name, size_t len);

/*
** init_shell
*/

void				get_term(t_42sh *sh);
void				init_shell(t_42sh *sh, char **env);
int					get_line(t_42sh *sh);
void				reset_term(t_42sh *sh);
/*
**  ERROR
*/

/*
** errno
*/

void				init_error_tab(void);
void				print_error(int code, bool is_fatal);
void				print_error_and_exit(int error_code);
void				print_error_first(int error_code);
int					ft_set_errno(int n);

/*
** Utils
*/

char				*ft_joinpath(const char *path, const char *name);

void				print_env_array(char **env);

/***************************************************************************** \
|                              HISTORY                                        |
\*****************************************************************************/

int			       substitute_history(t_42sh *sh);

//void				add_history(char *line, char *path_history);
//void				init_history(char	*path_history);
void				up_history(t_42sh *sh);
void				parser(t_42sh *sh);
/*
** Options
*/

void				history_p(t_42sh *sh);
void				clean_history(char *path);
//void				print_history(char *path, int start);
void				print_history_n(char *path);
void				print_history_r(char *path);
void				init_history(t_42sh *sh, char *line);
void				add_history(t_42sh *sh, char *line, char *path);
void				print_history(t_history_mark *history_mark);
void				del_history(t_history_mark *history);
void				add_to_list(t_42sh *sh, char *line);
void				up_histo(t_42sh *sh);
void				down_histo(t_42sh *sh);
void				check_substitute(t_42sh *sh);
void				modify_last_history(t_42sh *sh);
/***************************************************************************** \
|                              BUILTIN                                        |
\*****************************************************************************/

/*
**	test
*/

void				builtin_test(t_42sh *sh);
void				test_b(t_42sh *sh, struct stat info);
void				test_c(t_42sh *sh, struct stat info);
void				test_d(t_42sh *sh, struct stat info);
void				test_e(t_42sh *sh, struct stat info);
void				test_f(t_42sh *sh, struct stat info);
void				test_g(t_42sh *sh, struct stat info);
void				test_L(t_42sh *sh, struct stat info);
void				test_p(t_42sh *sh, struct stat info);
void				test_r(t_42sh *sh, struct stat info);
void				test_S(t_42sh *sh, struct stat info);
void				test_s(t_42sh *sh, struct stat info);
void				test_u(t_42sh *sh, struct stat info);
void				test_w(t_42sh *sh, struct stat info);
void				test_x(t_42sh *sh, struct stat info);
void				test_z(t_42sh *sh, struct stat info);

/*
**	echo
*/

void				builtin_echo(t_42sh *sh);

/***************************************************************************** \
|                          SUBSTITUTION                                        |
\*****************************************************************************/

/*
**	parser
*/

void				check_substitution(t_42sh *sh);
void				get_substitute(t_42sh *sh, int nb_del, char *substitute);

/***************************************************************************** \
|                            TABULATION                                        |
\*****************************************************************************/

void				show_suggest(t_42sh *sh);

#endif