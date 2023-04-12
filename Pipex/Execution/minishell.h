/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:03:42 by idabligi          #+#    #+#             */
/*   Updated: 2023/04/12 01:10:06 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct t_data
{
	int				exec;
	int				count;
}				t_store;


typedef struct t_shell
{
	char			*arg;
	int				tatto;
	struct t_shell	*next;

}					t_list;

char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, int n);
char	**ft_split(char const *s, char c);
void	ft_write_error(char *str);
int		ft_strlen(const char *s);
void	ft_write_error2(char *str);
int		ft_atoi(char *str);
char	*ft_access(char **p_cmd, char *s_cmd);
void	ft_firstcmd(char *infile, char *cmd);
void	ft_midcmd(char *cmd, int check);
void	ft_lastcmd(char *outfile, char *cmd, int check);
char	*ft_getpath(char *cmd);
void	ft_execution(t_list *data, t_store *store);
void	ft_exec1(t_list *data);
char	**ft_arg(char **arg, char *path);
void	ft_pipefirstcmd(t_list *data);
void	ft_pipemidllecmd(t_list *data, int i);
void	ft_pipelastcmd(t_list *data, int i);
void	ft_exec2(t_list *data, t_store *store);
void	ft_printerror(char *str, char *cmd);

t_list	*ft_lstnew(char *arg, char *tatto);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list *lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstdel(t_list **head);

#endif