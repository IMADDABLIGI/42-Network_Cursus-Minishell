/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/04 10:00:14 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_shell
{
	char			*arg;
	int				tatto;
	struct t_shell	*next;

}					t_list;

typedef struct t_data
{
	int				num;
	int				num2;
	int				exec;
	int				count;
	int				check;
	char			*path;
	char			**arg;
}					t_store;

typedef struct env
{
	char *			arg;
	struct env		*next;
}		t_env;

typedef struct data
{
	char			*input;
	char *strenv;
	char *ret;
	char *strtmp;
	char			**tab;
	char			**env1;
	char			t;
	int				z;
	int				lock;
	int				lock1;
	size_t			k;
	size_t			length;
	 size_t			i;
	  size_t x;
	t_list			*p;
	t_list			*tmp1;
	t_env *e;
	t_env *tmp;
}					t_data;

/*parsing function*/
t_list				*ft_lstnew(t_data *a);
t_list				*ft_lstclear(t_list **lst);
void				tato(t_data *a);
char				*str(t_data *a, int *tatto);
void				ft_lstadd_back(t_list **lst, t_list *new);
char				**ft_split22(t_data *a);
char				**free_all22(char **str, int max);
char				*ft_strdup(char *s1);
size_t				ft_strlen(char *s);
char				*ft_substr(char *s, unsigned int start, size_t len);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *table);
char	*ft_strjoin22(char *s1, char s2);
void ft_abort(int id);
/*new*/
void				*ft_memcpy(void *dst, void *src, int n);
char				**ft_split(char *s, char c);
char				**ft_split_cmd(char *s, char c, char *cmd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_getpath(char *cmd);
void				ft_execution(t_list *data, t_store *store);
char				**ft_arg(t_list *data);
void				ft_pipefirstcmd(t_list *data);
void				ft_pipemidllecmd(t_list *data, int i);
void				ft_pipelastcmd(t_list *data, int i);
void				ft_printerror(char *str, char *cmd);
void				ft_redirect(t_list *data, t_store *store, int i);
void				ft_check_arg(t_list *data, t_store *store);
int					ft_checkpr(t_list *data);
void				ft_nocmd(t_list *data);

#endif
