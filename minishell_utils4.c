/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:42:51 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/15 10:19:49 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

void	ft_check_redirections(t_list *data, t_store *store, int input)
{
	while (data && (data->tatto != 4))
	{
		if (data->tatto == 5)
		{
			input = open(data->next->arg, O_RDONLY);
			if (input < 0)
				exit(0);
			dup2(input, STDIN_FILENO);
			close(input);
		}
		else if (data->tatto == 7)
		{
			store->doc++;
			input = ft_get_heredoc(store->doc, 0, 0);
			dup2(input, STDIN_FILENO);
			close(input);
		}
		data = data->next;
	}
	return ;
}

//---------------------------------------------------------------------------//

int	ft_check_redirections2(t_list *data, int ot, t_store *store)
{
	while ((data) && (data->tatto != 4))
	{
		if (ot && ((data->tatto == 6) || (data->tatto == 8)))
			close(ot);
		if (data->tatto == 6)
		{
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				ot = 0;
			else
				ot = open(data->next->arg, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
		else if (data->tatto == 8)
		{
			if (!ft_strcmp(data->next->arg, "/dev/stdout"))
				ot = 0;
			else
				ot = open(data->next->arg, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		if ((ot < 0) && ((store->built) && !(store->pipe)))
			return (-1);
		if (ot < 0)
			exit(1);
		data = data->next;
	}
	return (ot);
}

//---------------------------------------------------------------------------//

char	*ft_strjoin3(char *s1, char *s2)
{
	char	*string;
	int		lens1;
	int		lens2;
	int		mix;

	if (!s1 && !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	mix = ft_strlen(s1) + ft_strlen(s2);
	string = malloc((mix + 1) * sizeof(char));
	if (!string)
		ft_abort(1);
	ft_memcpy(string, s1, lens1);
	ft_memcpy(string + lens1, (s2 + 1), lens2);
	string[mix] = '\0';
	return (string);
}

//---------------------------------------------------------------------------//

int	ft_check_dr(char *path)
{
	struct stat	sb;

	stat(path, &sb);
	if (S_ISREG(sb.st_mode))
	{
		printf("cd: %s: Not a directory\n", path);
		return (0);
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_print_error2(void)
{
	write(1, "cd: error retrieving current directory:", 40);
	write(1, " getcwd: cannot access parent directories:", 43);
	write(1, " No such file or directory\n", 28);
}
