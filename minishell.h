/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:17:32 by hznagui           #+#    #+#             */
/*   Updated: 2023/04/27 17:53:15 by hznagui          ###   ########.fr       */
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
	int				exec;
	int				count;
}					t_store;

typedef struct data
{
	char			*input;
	char			**tab;
	char			**env1;
	int				z;
	int				lock;
	size_t			length;
	int				lock1;
	size_t			k;
	char			t;
	size_t			i;
	t_list			*p;
	t_list			*tmp;
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
/*new*/
void				*ft_memcpy(void *dst, void *src, int n);
char				**ft_split(char *s, char c, char *cmd);
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
int					ft_check_cmd(t_list *data);

#endif
