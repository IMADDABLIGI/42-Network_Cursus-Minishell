/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools15.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:55:02 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/13 18:22:48 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_strlencmd(t_list *ptr, int i)
{
	while ((ptr) && (ptr->tatto != 4))
	{
		if ((ptr->tatto == 5) || (ptr->tatto == 6) || (ptr->tatto == 7)
			|| (ptr->tatto == 8))
			ptr = ptr->next->next;
		else
		{
			ptr = ptr->next;
			i++;
		}
	}
	return (i);
}
/**************************************************************/

void	ft_unset6(t_data *a)
{
	g_global.status = 1;
	write(2, "unset: `", 9);
	write(2, a->kp->arg, ft_strlen(a->kp->arg));
	write(2, "': not a valid identifier\n", 27);
}

/**************************************************************/
void	ft_exit(t_list *data, t_data *a)
{
	a->kp = data;
	a->kp = a->kp->next;
	if (a->kp->next)
	{
		g_global.status = 1;
		write(2, "bash: exit: too many arguments", 31);
	}
	else if (check(a->kp->arg) || check_nothing(a->kp->arg, 0, 0))
	{
		write(2, "bash: exit: ", 13);
		write(2, a->kp->arg, ft_strlen(a->kp->arg));
		write(2, "numeric argument required", 26);
		exit(255);
	}
	printf(" salam\n");
}
/**************************************************************/

static int	ft_return(int c)
{
	if (c == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		c;
	size_t	z;
	int		i;

	i = 0;
	z = 0;
	c = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == '\n' || str[i] == '\v' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		z = 10 * z + (str[i] - '0');
		if (z > 9223372036854775807)
			return (ft_return(c));
		i++;
	}
	return (z * c);
}
/**************************************************************/

int	check(char *argv)
{
	int	i;
	
	i = 0;
	while (argv[i])
	{
		if ((argv[i] >= 58 && argv[i] <= 127) ||
			(argv[i] >= 33 && argv[i] <= 42) ||
			(argv[i] >= '.' && argv[i] <= '/') ||
			(argv[i] == ',') || (argv[i] == '+' && ((argv[i
							+ 1] > '9' || argv[i + 1] < '0')
						|| (argv[i - 1] != '\0' && argv[i
							- 1] != ' '))))
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
