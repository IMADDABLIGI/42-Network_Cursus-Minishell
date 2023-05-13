/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 09:28:46 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_list *data, t_data *a)
{
	t_list	*k;

	k = data;
	k = k->next;
	a->tmp = a->e;
	if (k && k->tatto == 2)
	{
		while (k && k->tatto == 2)
		{
			a->i = 0;
			if (!ft_isalpha(k->arg[a->i]))
				ft_printerror("export", k->arg);
			else
			{
				while (k->arg[a->i] && (ft_isalnum(k->arg[a->i]) == 1
						|| k->arg[a->i] == '_'))
					a->i++;
				if (!k->arg[a->i])
				{
					if (!ft_export2(a, k->arg, 0, 0))
					{
						a->tmp = ft_lstnew_env(k->arg);
						if (!a->tmp)
							ft_abort(1);
						ft_lstadd_back_env(&a->e, a->tmp);
					}
				}
				else if (k->arg[a->i] == '+' && k->arg[a->i + 1] == '=')
				{
					if (!ft_export2(a, k->arg, 0, 2))
					{
						a->tmp = ft_lstnew_env(k->arg);
						if (!a->tmp)
							ft_abort(1);
						ft_lstadd_back_env(&a->e, a->tmp);
					}
				}
				else if (k->arg[a->i] != '=')
					ft_printerror("export", k->arg);
				else if (!ft_export2(a, k->arg, 0, 1))
				{
					a->tmp = ft_lstnew_env(k->arg);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e, a->tmp);
				}
			}
			k = k->next;
		}
	}
	else
	{
		while (a->tmp)
		{
			write(1, "declare -x ", 11);
			ft_print(a->tmp->arg);
			a->tmp = a->tmp->next;
		}
	}
}

int	parse_check(t_data *a)
{
	a->tmp1 = a->p;
	if (a->tmp1->tatto == 4)
	{
		printf("\e[1;31m parse error!\n\e[0m");
		return (1);
	}
	while (a->tmp1)
	{
		if (a->tmp1->tatto != 0 && !a->tmp1->next)
		{
			printf("\e[1;31m parse error!\n\e[0m");
			return (1);
		}
		else if (a->tmp1->tatto == 4 && (a->tmp1->next->tatto == 4))
		{
			printf("\e[1;31m parse error!\n\e[0m");
			return (1);
		}
		else if ((a->tmp1->tatto != 0 && a->tmp1->tatto != 4)
				&& a->tmp1->next->tatto != 0)
		{
			printf("\e[1;31m parse error!\n\e[0m");
			return (1);
		}
		a->tmp1 = a->tmp1->next;
	}
	return (0);
}

size_t	ft_length(t_data *a, int *tatto)
{
	size_t	len;

	a->lock = 0;
	a->x = 0;
	len = 0;
	check_tato(a, tatto);
	while (a->tab[a->i][a->x])
	{
		if ((a->tab[a->i][a->x] == 39 || a->tab[a->i][a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->tab[a->i][a->x];
		}
		else if (a->t == a->tab[a->i][a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		else if (((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$'
						&& ft_isdigit(a->tab[a->i][a->x + 1]))
						|| (a->tab[a->i][a->x] == '$' && (a->tab[a->i][a->x
						+ 1] == 39 || a->tab[a->i][a->x + 1] == 34)
						&& !a->lock))
			a->x++;
		else
			len++;
		a->x++;
	}
	return (len);
}
char	*str(t_data *a, int *tatto)
{
	a->ret = malloc(sizeof(char) * ft_length(a, tatto));
	if (!a->ret)
		ft_abort(1);
	a->k = 0;
	a->lock = 0;
	a->x = 0;
	while (a->tab[a->i][a->x])
	{
		if ((a->tab[a->i][a->x] == 39 || a->tab[a->i][a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->tab[a->i][a->x];
		}
		else if (a->t == a->tab[a->i][a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		else if (((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$'
						&& ft_isdigit(a->tab[a->i][a->x + 1]))
						|| (a->tab[a->i][a->x] == '$' && (a->tab[a->i][a->x
						+ 1] == 39 || a->tab[a->i][a->x + 1] == 34)
						&& !a->lock))
			a->x++;
		else
		{
			a->ret[a->k] = a->tab[a->i][a->x];
			a->k++;
		}
		a->x++;
	}
	a->ret[a->k] = '\0';
	return (a->ret);
}

size_t	ft_export2(t_data *a, char *arg, int i, int index)
{
	char	*tmp;
	char	*before;

	a->strenv = NULL;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
	{
		a->strenv = ft_strjoin22(a->strenv, arg[i]);
		i++;
	}
	before = ft_strdup(a->strenv);
	if (index == 1)
		a->strenv = ft_strjoin22(a->strenv, '=');
	else if (index == 2)
		before = ft_strjoin(before, "+=", 1);
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (tmp || !(ft_strcmp(before, a->tmp->arg)))
		{
			if (index == 1)
			{
				free(a->tmp->arg);
				a->tmp->arg = ft_strdup(arg);
			}
			else if (index == 2)
				a->tmp->arg = ft_strjoin(a->tmp->arg, ft_strnstr(arg, before),
						1);
			return (free(a->strenv), free(before), 1);
		}
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), free(before), 0);
}
/**************************************************************/

void	change2(t_data *a)
{
	size_t	i;
	size_t	lock;

	lock = 0;
	i = 0;
	while (a->strtmp[i])
	{
		if (a->strtmp[i] != 32 && lock == 0)
		{
			a->ret[a->k] = '"';
			a->k++;
			lock = 1;
		}
		else if (a->strtmp[i] == 32 && lock == 1)
		{
			a->ret[a->k] = '"';
			a->k++;
			lock = 0;
		}
		else
		{
			a->ret[a->k] = a->strtmp[i];
			a->k++;
			i++;
		}
	}
	if (lock == 1)
	{
		a->ret[a->k] = '"';
		a->k++;
	}
}
void	ft_change(t_data *a, int index)
{
	a->x++;
	a->strenv = NULL;
	while (a->input[a->x] && (ft_isalnum(a->input[a->x])
			|| a->input[a->x] == '_'))
	{
		a->strenv = ft_strjoin22(a->strenv, a->input[a->x]);
		a->x++;
	}
	a->x--;
	a->strenv = ft_strjoin22(a->strenv, '=');
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp && index == 0)
			change1(a);
		else if (a->strtmp && index == 1)
			change2(a);
		a->tmp = a->tmp->next;
	}
	free(a->strenv);
	return ;
}
size_t	strlen_expand(char *str)
{
	size_t	i;
	size_t	len;
	int		lock;

	lock = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != 32 && lock == 0)
		{
			lock = 1;
			len += 2;
		}
		else if (str[i] == 32 && lock == 1)
			lock = 0;
		i++;
		len++;
	}
	return (len);
}
size_t	ft_expand_length(t_data *a, int index)
{
	char	*tmp;

	a->x++;
	a->strenv = NULL;
	while (a->input[a->x] && (ft_isalnum(a->input[a->x])
			|| a->input[a->x] == '_'))
	{
		a->strenv = ft_strjoin22(a->strenv, a->input[a->x]);
		a->x++;
	}
	a->x--;
	a->strenv = ft_strjoin22(a->strenv, '=');
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg, a->strenv);
		if (tmp && index == 0)
			return (free(a->strenv), ft_strlen(tmp));
		else if (tmp && index == 1)
			return (free(a->strenv), strlen_expand(tmp));
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), 0);
}
size_t	ft_length1(t_data *a)
{
	size_t	len;

	a->lock = 0;
	a->x = 0;
	a->t = '\0';
	len = 0;
	while (a->input[a->x])
	{
		if ((a->input[a->x] == 39 || a->input[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->input[a->x];
		}
		else if (a->t == a->input[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		if (((a->t == '"' || !a->t) && a->input[a->x] == '$'
					&& ft_isdigit(a->input[a->x + 1])) || (a->input[a->x] == '$'
					&& (a->input[a->x + 1] == 39 || a->input[a->x + 1] == 34)
					&& !a->lock))
			a->x++;
		else if ((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1]
					&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_'))
			len += ft_expand_length(a, 0);
		else if ((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1]
				&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_'))
			len += ft_expand_length(a, 1);
		else
			len++;
		a->x++;
	}
	return (len);
}
char	*expand(t_data *a)
{
	a->ret = malloc(sizeof(char) * ft_length1(a) + 1);
	if (!a->ret)
		ft_abort(1);
	a->k = 0;
	a->lock = 0;
	a->x = 0;
	while (a->input[a->x])
	{
		if ((a->input[a->x] == 39 || a->input[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->input[a->x];
		}
		else if (a->t == a->input[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		if (((a->t == '"' || !a->t) && a->input[a->x] == '$'
					&& ft_isdigit(a->input[a->x + 1])) || (a->input[a->x] == '$'
					&& (a->input[a->x + 1] == 39 || a->input[a->x + 1] == 34)
					&& !a->lock))
			a->x++;
		else if ((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1]
					&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_'))
			ft_change(a, 0);
		else if ((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1]
				&& (ft_isalnum(a->input[a->x + 1]) || a->input[a->x
					+ 1] == '_'))
			ft_change(a, 1);
		else
		{
			a->ret[a->k] = a->input[a->x];
			a->k++;
		}
		a->x++;
	}
	a->ret[a->k] = '\0';
	return (free(a->input), a->ret);
}

/**************************************************************/
int	ft_separit(t_data *a)
{
	if (!ft_split22(a))
		return (ft_abort(1), 1);
	a->i = 0;
	create_linked(a);
	return (0);
}
void	open_quote(t_data *a)
{
	a->z = 0;
	a->i = 0;
	a->lock = 0;
	a->t = '\0';
	while (a->input[a->i])
	{
		if ((a->input[a->i] == 39 || a->input[a->i] == 34) && a->lock == 0)
		{
			a->lock = 1;
			a->z = 1;
			a->t = a->input[a->i];
		}
		else if ((a->input[a->i] == 39 || a->input[a->i] == 34)
				&& (a->lock == 1))
		{
			if (a->input[a->i] == a->t)
			{
				a->z = 0;
				a->lock = 0;
			}
		}
		a->i++;
	}
	if (a->z == 1)
		printf("\e[1;31m open quotes!\n\e[0m");
	else
	{
		if (!ft_separit(a))
			free_all22(a->tab, a->length);
		ft_lstclear(&a->p);
	}
}

void	ft_create_env(t_data *a, char **env)
{
	a->i = 0;
	while (env[a->i])
	{
		a->tmp = ft_lstnew_env(env[a->i]);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e, a->tmp);
		a->i++;
	}
}

void	ft_abort(int id)
{
	if (id == 1)
		printf("\e[1;31mmalloc problem\n\e[0m");
	else if (id == 2)
		printf("\e[1;31mno argument please!\n\e[0m");
	exit(1);
}
void	handler(int status)
{
	(void)status;
	if (global.her)
	{
		rl_getc_function = getc;
	}
	else
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data a;

	if (argc != 1)
		ft_abort(2);
	(void)argv;
	ft_create_env(&a, env);
	// rl_set_signals();
	signal(SIGQUIT, (void *)sigignore);
	a.env22 = env;
	while (1)
	{
		signal(SIGINT, handler);
		rl_catch_signals = 0;
		a.input = readline("MINISHELL>> ");
		if (a.input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (*(a.input))
		{
			add_history(a.input);
			expand(&a);
			a.input = a.ret;
			// printf("%s  \n",a.input);
			if (!ft_nothing(a.input))
				open_quote(&a);
		}
		free(a.input);
	}
	return (0);
}