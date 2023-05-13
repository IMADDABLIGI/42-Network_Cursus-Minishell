/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 15:48:31 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_global
{
	int				doc;
	int				save;
	int				status;
	int				intg;
	char			*home;
	char			*old_pwd;
	int				her;
	char			*new_pwd;
}					t_glb;

typedef struct t_shell
{
	char			*arg;
	int				tatto;
	int				split;
	struct t_shell	*next;

}					t_list;

typedef struct t_data
{
	int				doc;
	int				pipe;
	int				built;
	int				count;
	int				save;
	int				check;
	char			*path;
	char			**arg;
}					t_store;

typedef struct env
{
	char			*arg;
	struct env		*next;
}					t_env;

typedef struct data
{
	char			**env22;
	char			*input;
	char			*strenv;
	char			*ret;
	char			*strtmp2;
	char			*before;
	char			*ret1;
	char			*line;
	char			*strtmp;
	char			**tab;
	char			t;
	int				z;
	int				lock;
	int				lock1;
	int				check;
	int				pid;
	int				output;
	size_t			k;
	size_t			len;
	size_t			end;
	size_t			start;
	size_t			length;
	size_t			i;
	size_t			x;
	t_list			*p;
	t_list			*tmp1;
	t_list			*kp;
	t_env			*e;
	t_env			*tmp;
}					t_data;

t_glb				g_global;

/*parsing function*/
t_list				*ft_lstnew(t_data *a);
void				open_quote(t_data *a);
t_list				*ft_lstclear(t_list **lst);
void				tato(t_data *a);
char				*str(t_data *a, int *tatto);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				**ft_split22(t_data *a);
char				**free_all22(char **str, int max);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *s);
void				ft_echo(t_list *data);
char				*ft_strnstr(char *haystack, char *needle);
char				*ft_substr(char *s, unsigned int start, size_t len);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
t_env				*ft_lstnew_env(char *table);
size_t				ft_export2(t_data *a, char *arg, int i, int index);
char				*ft_strjoin22(char *s1, char s2);
void				ft_abort(int id);
size_t				ft_length(t_data *a, int *tatto);
int					ft_separit(t_data *a);
void				ft_create_env(t_data *a, char **env);
char				*expand_her(t_data *a);
char				*expand(t_data *a);
void				ft_expand2(t_data *a);
void				ft_export(t_list *data, t_data *a);
int					ft_isalnum(int c);
void				handler(int status);
void				ft_change(t_data *a, int index);
size_t				strlen_expand(char *str);
int					ft_check_n(char *str);
void				ft_env(t_data *a, t_list *data);
void				ft_unset(t_list *data, t_data *a);
void				ft_print(char *arg);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
void				ft_change_her(t_data *a);
char				**ft_return22(t_data *a);
size_t				nbr_of_words22(t_data *a);
size_t				ft_length1_her(t_data *a);
int					parse_check(t_data *a);
void				ft_pwd(t_list *data);
int					ft_check_builtins(t_list *data);
void				ft_execute_builtins(t_list *data, t_data *a);
size_t				ft_export2(t_data *a, char *arg, int i, int index);
void				check_tato(t_data *a, int *tatto);
/*new*/
void				ft_checkinput(t_list *data, int input, int i,
						t_store *store);
int					ft_checkoutput(t_list *data, t_store *store, int i,
						int output);
void				*ft_memcpy(void *dst, const char *src, int n);
char				**ft_split_cmd(char *s, char c, char *cmd);
char				*ft_getpath(char *cmd, char **p_cmd, int i);
void				ft_execution(t_list *data, t_store *store, t_data *a,
						int fd);
char				**ft_arg(t_list *data, t_list *ptr, char **arg, int i);
void				ft_printerror(char *str, char *cmd);
void				ft_print_error2(void);
void				ft_redirect(t_list *data, t_store *store, int i, t_data *a);
int					ft_check_arg(t_list *data, t_store *store, t_data *a);
void				ft_check_next(t_list *data);
int					ft_run_doc(t_list *data, t_store *store, t_data *a);
void				ft_here_doc(t_list *data, int doc, int num, t_data *a);
int					ft_strcmp(char *s1, char *s2);
char				*ft_itoa(int n);
char				*ft_strjoin(char *s1, char *s2, int index);
int					ft_get_heredoc(int count, int fd, int check);
int					ft_creatfile(t_list *data);
void				ft_cd(t_list *data, char *pwd, t_data *a);
char				*ft_strjoin2(char *s1, char *s2);
char				*ft_strjoin3(char *s1, char *s2);
int					ft_check_dr(char *path);
int					ft_cd_old_path(char *path, int check, int i, int j);
int					ft_check_redirections(t_list *data, t_store *store,
						int input);
int					ft_check_redirections2(t_list *data, int ot,
						t_store *store);
void				change1(t_data *a);
int					ft_nothing(char *a);
void				create_linked(t_data *a);
int					ft_check_red2(t_list *data, int fd);
t_list				*ft_get_tatto1(t_list *ptr);
void				ft_init_store(t_store *store);
char				*ft_get_path2(char *cmd);
#endif
