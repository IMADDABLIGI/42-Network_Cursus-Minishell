/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:49:33 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/12 10:10:23 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void change1_her(t_data *a)
{
	int i;
	i=0;
	while (a->strtmp[i])
	{
		a->ret1[a->k]=a->strtmp[i];
		a->k++;
		i++;
	}
 
}
void ft_change_her(t_data *a)
{
	a->x++;
	a->strenv = NULL;
	
	while (a->line[a->x] && (ft_isalnum(a->line[a->x]) || a->line[a->x] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,a->line[a->x]);
		a->x++;
	}
	a->x--;
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (a->strtmp)
			change1_her(a);
		a->tmp = a->tmp->next;
	}
	free(a->strenv);
	return ;
}

size_t ft_expand_length_her(t_data *a)
{
	a->x++;
	a->strenv = NULL;
	char *tmp;
	while (a->line[a->x] && (ft_isalnum(a->line[a->x]) || a->line[a->x] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,a->line[a->x]);
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
size_t ft_length1_her(t_data *a)
{
	size_t len;
	
	a->lock = 0;
	a->x = 0;
	a->t='\0';
	len = 0;
	while (a->line[a->x])
	{
		if ((a->line[a->x] == 39 || a->line[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->line[a->x];
		}
		else if (a->t == a->line[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		if (((a->t == '"' || !a->t) && a->line[a->x] == '$' && ft_isdigit(a->line[a->x + 1]))||(a->line[a->x] == '$' && (a->line[a->x+1] == 39 || a->line[a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"'||!a->t) && a->line[a->x] == '$' && a->line[a->x + 1] && (ft_isalnum(a->line[a->x+1]) || a->line[a->x+1] == '_'))
			len += ft_expand_length_her(a);		
		else
			len++;
		a->x++;
	}
	return (len);
}
char *expand_her(t_data *a)
{
	a->ret1 = malloc(sizeof(char)*ft_length1_her(a)+1);
	if (!a->ret1)
		ft_abort(1);
	a->k=0;
	a->lock = 0;
	a->x = 0;
	while (a->line[a->x])
	{
		if ((a->line[a->x] == 39 || a->line[a->x] == 34) && !a->lock)
		{
			a->lock = 1;
			a->t = a->line[a->x];
		}
		else if (a->t == a->line[a->x] && a->lock)
		{
			a->lock = 0;
			a->t = '\0';
		}
		if (((a->t == '"' || !a->t) && a->line[a->x] == '$' && ft_isdigit(a->line[a->x + 1]))||(a->line[a->x] == '$' && (a->line[a->x+1] == 39 || a->line[a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"' || !a->t) && a->line[a->x] == '$' && a->line[a->x + 1]&& (ft_isalnum(a->line[a->x+1]) || a->line[a->x+1] == '_'))
			ft_change_her(a);
		else
		{
			a->ret1[a->k]=a->line[a->x];
			a->k++;
		}
		a->x++;
	}
	a->ret1[a->k]='\0';
	return(free(a->line),a->ret1);
}