/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/01 20:22:15 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1,char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}
int parse_check(t_data *a)
{
	
	a->tmp1 = a->p;
	if (a->tmp1->tatto == 4)
		{
				printf("\e[1;31m parse error!\n\e[0m");
				return(1);
		}
	while (a->tmp1)
	{
		if (a->tmp1->tatto != 0 && !a->tmp1->next)
		{
				printf("\e[1;31m parse error!\n\e[0m");
				return(1);
		}
		else if (a->tmp1->tatto == 4 && (a->tmp1->next->tatto == 4))
		{
				printf("\e[1;31m parse error!\n\e[0m");
				return(1);
		}
		else if ((a->tmp1->tatto != 0 && a->tmp1->tatto != 4) && a->tmp1->next->tatto != 0)
		{
				printf("\e[1;31m parse error!\n\e[0m");
				return(1);
		}
		a->tmp1 = a->tmp1->next;
	}
	return(0);
}
void tato(t_data *a)
{
	a->tmp1 = a->p;
	while (a->tmp1)
	{
		if (a->tmp1->tatto == 0)
		{
			a->tmp1->tatto = 1;
			a->tmp1 = a->tmp1->next;
			while (a->tmp1 && a->tmp1->tatto == 0)
			{
				a->tmp1->tatto = 2;
				a->tmp1 = a->tmp1->next;
			}
		}
		else if (a->tmp1->tatto != 4)
		{
			a->tmp1 = a->tmp1->next;
			if (a->tmp1->tatto == 0)
				a->tmp1->tatto = 2;
			a->tmp1 = a->tmp1->next;
		}
		else
			a->tmp1 = a->tmp1->next;
	}
}

void check_tato(t_data *a,int *tatto)
{
	if (!ft_strcmp(a->tab[a->i],">>"))
		*tatto = 8;
	else if (!ft_strcmp(a->tab[a->i],"<<"))
		*tatto = 7;
	else if (!ft_strcmp(a->tab[a->i],"<"))
		*tatto = 5;
	else if (!ft_strcmp(a->tab[a->i],">"))
		*tatto = 6;
	else if (!ft_strcmp(a->tab[a->i],"|"))
		*tatto = 4;     
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

char	*ft_strnstr(char *haystack,char *needle)
{
	size_t		i;
	size_t		j;
	char		*p;

	p = haystack;
	j = 0;
	i = 0;
	
	while (p[i + j] && needle[j])
	{
		if (p[i + j] == needle[j])
			j++;
		else
		{
			i++;
			j = 0;
		}
	}
	if (needle[j] == '\0')
		return (p + j);
	else
		return (0);
}

size_t ft_expand(t_data *a)
{
	a->x++;
	a->strenv = NULL;
	char *tmp;
	while (a->tab[a->i][a->x] && (ft_isalnum(a->tab[a->i][a->x]) || a->tab[a->i][a->x] == '_'))
	{
	// printf("%s\n",a->strenv);
		a->strenv=ft_strjoin22(a->strenv,a->tab[a->i][a->x]);
		a->x++;
	}
	a->x--;
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (tmp)
			return(free(a->strenv),ft_strlen(tmp));
		a->tmp = a->tmp->next;
	}
	return(free(a->strenv),0);
}
void change1(t_data *a)
{
	int i;
	i=0;
	while (a->strtmp[i])
	{
		a->ret[a->k]=a->strtmp[i];
		a->k++;
		i++;
	}
 
}
void ft_change(t_data *a)
{
	a->x++;
	a->strenv = NULL;
	// printf("salam\n");
	
	while (a->tab[a->i][a->x] && (ft_isalnum(a->tab[a->i][a->x]) || a->tab[a->i][a->x] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,a->tab[a->i][a->x]);
		a->x++;
	}
	a->x--;
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (a->strtmp)
			change1(a);
		a->tmp = a->tmp->next;
	}
	free(a->strenv);
	return ;
}
size_t ft_length(t_data *a,int *tatto)
{
	size_t len;
	
	a->lock = 0;
	a->x = 0;
	len = 0;
	check_tato(a,tatto);
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
		else if (((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$' && ft_isdigit(a->tab[a->i][a->x + 1]))||(a->tab[a->i][a->x] == '$' && (a->tab[a->i][a->x+1] == 39 || a->tab[a->i][a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$' && a->tab[a->i][a->x + 1] && (ft_isalnum(a->tab[a->i][a->x+1]) || a->tab[a->i][a->x+1] == '_'))
			len += ft_expand(a);
		else
			len++;
		a->x++;
	}
	return (len);
}
char *str(t_data *a,int *tatto)
{
	a->ret = malloc(sizeof(char)*ft_length(a,tatto));
	if (!a->ret)
		ft_abort(1);
	a->k=0;
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
		else if (((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$' && ft_isdigit(a->tab[a->i][a->x + 1]))||(a->tab[a->i][a->x] == '$' && (a->tab[a->i][a->x+1] == 39 || a->tab[a->i][a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"' || !a->t) && a->tab[a->i][a->x] == '$' && a->tab[a->i][a->x + 1]&& (ft_isalnum(a->tab[a->i][a->x+1]) || a->tab[a->i][a->x+1] == '_'))
			ft_change(a);
		else
		{
			a->ret[a->k]=a->tab[a->i][a->x];
			a->k++;
		}
		a->x++;
	}
	a->ret[a->k]='\0';
	return(a->ret);
}
void create_linked(t_data *a)
{
	t_store store;
	
	a->i=0;
	a->p=NULL;
	while (a->tab[a->i])
	{
		a->tmp1 = ft_lstnew(a);
		if (!a->tmp1)
			ft_lstclear(&a->p); 
		ft_lstadd_back(&a->p,a->tmp1);
		a->i++;
	}
	if (parse_check(a))
		return;
	tato(a);
	a->tmp1=a->p;
	if (ft_check_arg(a->tmp1, &store) == 1)
		ft_execution(a->tmp1, &store);
	// o = a->p;
	// while (o)
	// {
	//     printf("%d\t",o->tatto);
	//    o = o->next;
	// }
	// printf("\n");
}

int ft_separit(t_data *a)
{
	if (!ft_split22(a))
		return(printf("problem in malloc !\n"));
	a->i = 0;
	create_linked(a);
	return(0);
}
void open_quote(t_data *a)
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
		else if ((a->input[a->i] == 39 || a->input[a->i] == 34 ) && (a->lock == 1))
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
			free_all22(a->tab,a->length);
		ft_lstclear(&a->p); 
	}
}

void  ft_create_env(t_data *a,char **env)
{
	a->i=0;
	while (env[a->i])
	{
		a->tmp = ft_lstnew_env(env[a->i]);
		if (!a->tmp)
			ft_abort(1);
		ft_lstadd_back_env(&a->e,a->tmp);
		a->i++;
	}
}

void ft_abort(int id)
{
	if (id == 1)
		printf("\e[1;31mmalloc problem\n\e[0m");
	else if (id == 2)
		printf("\e[1;31mno argument please!\n\e[0m");
	exit(1);
}

int main(int argc,char **argv,char **env){
	t_data a;
	if (argc != 1)
		ft_abort(2);
	ft_create_env(&a,env);
	
	
	// a.tmp=a.e;
	// while (a.tmp)
	// {
	//     printf("%s\n",a.tmp->arg);
	//     a.tmp=a.tmp->next;
	// }
	

	while (1)
	{
		a.input = readline("MINISHELL>> ");
		if (*(a.input))
		{
			add_history(a.input);
			open_quote(&a);
		}
		free(a.input);
	}
	return 0;
}