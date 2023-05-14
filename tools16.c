/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools16.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 10:21:10 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/14 18:25:00 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if ((argv[i] >= 58 && argv[i] <= 127) || (argv[i] >= 33
				&& argv[i] <= 42) || (argv[i] >= '.' && argv[i] <= '/')
			|| (argv[i] == ',') || (argv[i] == '+' && ((argv[i + 1] > '9'
						|| argv[i + 1] < '0') || (argv[i - 1] != '\0' && argv[i
							- 1] != ' ' && argv[i - 1] != 9))))
			return (1);
		i++;
	}
	return (0);
}
/**************************************************************/

int	check_nothing(char *argv, int i, int z)
{
	int	k;

	k = 0;
	z = 0;
	i = 0;
	while (argv[i])
	{
		if ((argv[i] >= '0' && argv[i] <= '9') && z == 0)
		{
			z = 1;
			k += 1;
		}
		else if (!(argv[i] >= '0' && argv[i] <= '9') && z == 1)
			z = 0;
		i++;
	}
	if (k != 1)
		return (1);
	return (0);
}

/**************************************************************/
char	*find_path(t_data *a)
{
	a->tmp = a->e;
	a->strenv = ft_strdup("PATH=");
	while (a->tmp)
	{
		a->strtmp2 = ft_strnstr(a->tmp->arg, a->strenv);
		if (a->strtmp2)
		{
			return (free(a->strenv), a->strtmp2);
		}
		a->tmp = a->tmp->next;
	}
	return (free(a->strenv), NULL);
}
/**************************************************************/

void	ft_return223(t_data *a)
{
	if ((a->input[a->end] == '<' && a->input[a->end + 1] == '<')
		|| (a->input[a->end] == '>' && a->input[a->end + 1] == '>'))
				a->end += 1;
	a->end++;
}
/**************************************************************/

char	*ft_withoutplus(char *str)
{
	int		i;
	int		lock;
	int		len;
	char	*tmp;

	i = 0;
	lock = 1;
	len = 0;
	tmp = malloc(ft_strlen(str)-1);
	if (!tmp)
		ft_abort(1);
	while (str[i])
	{
		if (str[i] == '+' && lock == 1)
			lock = 0;
		else
		{
			tmp[len] = str[i];
			len++;
		}
		i++;
	}
	tmp[len] = '\0';
	free(str);
	return (tmp);
}
