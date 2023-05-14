/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idabligi <idabligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/14 20:16:12 by idabligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main2(t_data *a)
{
	a->pid = 1;
	add_history(a->input);
	expand(a);
	a->input = a->ret;
	if (!ft_nothing(a->input))
		open_quote(a);
}

/**************************************************************/

int	main(int argc, char **argv, char **env)
{
	t_data	a;

	if (argc != 1)
		ft_abort(2);
	(void)argv;
	ft_create_env(&a, env);
	signal(SIGQUIT, (void *)sigignore);
	a.env22 = env;
	g_global.status = 0;
	while (1)
	{
		signal(SIGINT, handler);
		rl_catch_signals = 0;
		a.input = readline("MINISHELL>> ");
		if (a.input == NULL)
		{
			printf("exit\n");
			exit(g_global.status);
		}
		if (*(a.input))
			main2(&a);
		free(a.input);
	}
	return (0);
}
