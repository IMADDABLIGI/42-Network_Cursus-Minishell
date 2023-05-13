/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/13 12:21:05 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main2(t_data *a)
{
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
			main2(&a);
		free(a.input);
	}
	return (0);
}
