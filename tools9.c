/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 10:05:07 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 15:59:10 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----------------------------------------------------------------*/
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*----------------------------------------------------------------*/
char	*ft_strjoin22(char *s1, char s2)
{
	size_t	i;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + 2));
	if (str == NULL)
		ft_abort(1);
	i = -1;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	free(s1);
	str[i++] = s2;
	str[i] = '\0';
	return (str);
}
/*----------------------------------------------------------------*/

void	expand_her2(t_data *a)
{
	if ((a->t == '"' || !a->t) && a->line[a->x] == '$'
		&& a->line[a->x + 1] == '?')
	{
		ft_copie_nb(a, 0);
		a->x++;
	}
	else if (((a->t == '"' || !a->t) && a->line[a->x] == '$'
			&& ft_isdigit(a->line[a->x + 1])) || (a->line[a->x] == '$'
			&& (a->line[a->x + 1] == 39 || a->line[a->x + 1] == 34)
			&& !a->lock))
		a->x++;
	else if ((a->t == '"' || !a->t) && a->line[a->x] == '$' && a->line[a->x + 1]
		&& (ft_isalnum(a->line[a->x + 1]) || a->line[a->x + 1] == '_'))
		ft_change_her(a);
	else
	{
		a->ret1[a->k] = a->line[a->x];
		a->k++;
	}
}

char	*expand_her(t_data *a)
{
	a->ret1 = malloc(sizeof(char) * ft_length1_her(a) + 1);
	if (!a->ret1)
		ft_abort(1);
	a->k = 0;
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
		expand_her2(a);
		a->x++;
	}
	a->ret1[a->k] = '\0';
	return (free(a->line), a->ret1);
}
/*----------------------------------------------------------------*/

void	ft_abort(int id)
{
	if (id == 1)
		printf("\e[1;31mmalloc problem\n\e[0m");
	else if (id == 2)
		printf("\e[1;31mno argument please!\n\e[0m");
	else if (id == 3)
		printf("\e[1;31mno Error Fork!\n\e[0m");
	exit(1);
}
