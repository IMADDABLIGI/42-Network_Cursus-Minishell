/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:21:29 by idabligi          #+#    #+#             */
/*   Updated: 2023/05/14 21:23:25 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//---------------------------------------------------------------------------//

int	ft_creatfile(t_list *data)
{
	int	input;
	int	output;
	
	if ((data->tatto == 5 || data->tatto == 6) && !ft_strcmp(data->next->arg,
			"/dev/stdout"))
		return (1);
	unlink("/tmp/input");
	unlink("/tmp/output");
	input = open("/tmp/input", O_CREAT, 0644);
	if (input < 0)
	{
		perror("Error Creating input file");
		exit(1);
	}
	output = open("/tmp/output", O_CREAT, 0644);
	if (output < 0)
	{
		perror("Error Creating output file");
		exit(1);
	}
	close (input);
	close (output);
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_exec(t_list *data, t_store *store, int i, t_data *a)
{
	int	fd[2];
	int save;
	
	save = dup(STDIN_FILENO);
	while ((i <= store->count) && (data))
	{
		pipe(fd);
		a->pid = fork();
		if (a->pid == -1)
			ft_abort(3);
		if (a->pid == 0)
			ft_redirect(data, store, i, a, fd);
		else
		{
			dup2(fd[0], STDIN_FILENO);
			close (fd[0]);
			close (fd[1]);

			if (data->tatto == 5)
				data = data->next;
			data = data->next;
			data = ft_get_cmd(data);
			if ((data) && (data->tatto == 4))
				data = data->next;

			if (i == store->count)
			{
				waitpid(a->pid, &g_global.intg, 0);
				if (WIFEXITED(g_global.intg))
					g_global.status = WEXITSTATUS(g_global.intg);
				else if (WIFSIGNALED(g_global.intg))
					ft_handle_sig(WTERMSIG(g_global.intg));
			}
			i++;
		}
	}
	while (wait(NULL) >= 0)
		;
	dup2(save, STDIN_FILENO);
	close(save);
}

//---------------------------------------------------------------------------//

int	ft_check_built_input(t_list *data, int input)
{
	while (data)
	{
		if (data->tatto == 5)
		{
			input = open(data->next->arg, O_RDONLY);
			if (input < 0)
				return (0);
			else
				close(input);
		}
		data = data->next;
	}
	return (1);
}

//---------------------------------------------------------------------------//

void	ft_execution(t_list *data, t_store *store, t_data *a, int fd)
{
	if (!(store->count))
		return ;
	if ((store->built) && !(store->pipe))
	{
		if (ft_check_built_input(data, 0))
		{
			fd = ft_check_redirections2(data, 0, store);
			if (fd)
			{
				if (fd == -1)
					return ;
				store->save = dup(STDOUT_FILENO);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			ft_execute_builtins(data, a);
			dup2(store->save, STDOUT_FILENO);
			close(store->save);
		}
	}
	else
		ft_exec(data, store, 1, a);
}
