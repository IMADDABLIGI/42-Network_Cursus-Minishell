/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hznagui <hznagui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:16:18 by hznagui           #+#    #+#             */
/*   Updated: 2023/05/12 10:49:00 by hznagui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glb	global;

int	ft_strcmp(char *s1, char *s2)
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
int ft_check_n(char *str)
{
	int i;
	i = 0;
	if (str[i] != '-')
		return(0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return(0);
		i++;
	}
	return(1);
}
void ft_echo(t_list *data)
{
	t_list *k;
	int a;
	a=0;
	k=data;
	k=k->next;
	while (k && ft_check_n(k->arg))
	{
		k=k->next;
		a=1;
	}
	while (k && k->tatto == 2)
	{
		printf("%s",k->arg);
		k = k->next;
		if (k && k->tatto == 2)
			printf(" ");
	}
	if (!a)
		printf("\n");
}

int find_(char *a)
{
	int p;
	p=0;
	while (a[p])
	{
		if (a[p]=='=')
			return(1);
		p++;
	}
	return(0);
}
void ft_env(t_data *a,t_list *data)
{
	t_list *k;
	k=data;
	k=k->next;
	if ( k && k->tatto == 2)
		printf("env: %s :No such file or directory\n",k->arg);
	else 
	{	
		a->tmp = a->e;
		while (a->tmp)
		{
			if (find_(a->tmp->arg))
	 	   		printf("%s\n",a->tmp->arg);
			a->tmp=a->tmp->next;
		}
	}
}
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
void ft_print(char *arg)
{
	int i;
	int z;
	z=0;
	i=0;
	char p='"';
	while (arg[i])
	{
		write(1,&arg[i],1);
		if (arg[i]== '=')
		{
			write(1,&p,1);
			z=1;
		}
		i++;
	}
	if (z==1)
		write(1,&p,1);
	write(1,"\n",1);
}
int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
size_t ft_unset2(t_data *a,t_list *data)
{
	t_env *before;
	char *tmp;
	char *c;
	before=NULL;
	a->strenv=ft_strdup(data->arg);
	c =ft_strdup(data->arg);
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg,a->strenv);
		
		if (tmp || !(ft_strcmp(c,a->tmp->arg)))
		{
			if (before)
				before->next = a->tmp->next;
			a->tmp->next = NULL;
			return (free(a->strenv),free(c),free(a->tmp->arg),free(a->tmp),1);
		}
		before = a->tmp;
		a->tmp = a->tmp->next;
	}
	return(free(a->strenv),free(c),0);
}
void ft_unset(t_list *data, t_data *a)
{
	t_list *k;
	k=data;
	k=k->next;
	a->tmp = a->e;
	while (k && k->tatto == 2)
		{
	a->i=0;
			if (!ft_isalpha(k->arg[a->i]))
					printf("unset: `%s': not a valid identifier\n",k->arg);
			while (k->arg[a->i] && (ft_isalnum(k->arg[a->i]) == 1 || k->arg[a->i] == '_'))
				a->i++;
			if (!k->arg[a->i])
				ft_unset2(a,k);
			else
					printf("unset: `%s': not a valid identifier\n",k->arg);
			k=k->next;
		}
}

void ft_export(t_list *data, t_data *a)
{
	t_list *k;
	k=data;
	k=k->next;
	a->tmp = a->e;
	if (k && k->tatto == 2)
	{
		while (k && k->tatto == 2)
		{
			a->i=0;
			if (!ft_isalpha(k->arg[a->i]))
					printf("export: `%s': not a valid identifier\n",k->arg);
			else
			{
			while (k->arg[a->i] && (ft_isalnum(k->arg[a->i]) == 1 || k->arg[a->i] == '_'))
				a->i++;
			if (!k->arg[a->i])
			{
				if (!ft_export2(a,k,0,0))
				{
					a->tmp = ft_lstnew_env(k->arg);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e,a->tmp);
				}
			}
			else if (k->arg[a->i] == '+' && k->arg[a->i+1] == '=')
			{
				if (!ft_export2(a,k,0,2))
				{
					a->tmp = ft_lstnew_env(k->arg);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e,a->tmp);
				}
			}
			else if (k->arg[a->i] != '=')
					printf("export: `%s': not a valid identifier\n",k->arg);
			else if (!ft_export2(a,k,0,1))
			{
					a->tmp = ft_lstnew_env(k->arg);
					if (!a->tmp)
						ft_abort(1);
					ft_lstadd_back_env(&a->e,a->tmp);
			}
			} 
		k=k->next;
		}
	}
	else
	{
		while (a->tmp)
		{
			write(1,"declare -x ",11);
			ft_print(a->tmp->arg);
			a->tmp =a->tmp->next;
		}
	}
}

void ft_pwd(t_list *data)
{
	char *cwd;
	t_list *k;
	k = data;
	k=k->next;

    cwd = getcwd(NULL,0);
    if (!cwd)
        printf("%s\n", global.new_pwd);
    else
        printf("%s\n",cwd);
    if (cwd)
		free(cwd);
}

void ft_execute_builtins(t_list *data, t_data *a)
{
	while(data && (data->tatto != 1))
		data = data->next;
	if (!ft_strcmp(data->arg,"cd"))
		ft_cd(data, 0, NULL, NULL);
	else if (!ft_strcmp(data->arg,"echo"))
		ft_echo(data);
	else if (!ft_strcmp(data->arg,"export"))
		ft_export(data,a);	
	else if (!ft_strcmp(data->arg,"exit"))
		exit(0);
	else if (!ft_strcmp(data->arg,"env"))
		ft_env(a,data);
	else if (!ft_strcmp(data->arg,"pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(data->arg,"unset"))
		ft_unset(data,a);
}

int ft_check_builtins(t_list *data)
{
	if (!ft_strcmp(data->arg,"echo") || !ft_strcmp(data->arg,"cd") || !ft_strcmp(data->arg,"pwd") || !ft_strcmp(data->arg,"export") || !ft_strcmp(data->arg,"unset")  || !ft_strcmp(data->arg,"env") || !ft_strcmp(data->arg,"exit"))
		return(1);
	return(0);
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
		else if (p[i+j] == '=')
			return (0);
		else
			return(0);
	}
	if (needle[j] == '\0')
		return (p + j);
	else
		return (0);
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
int ft_nothing(char *a)
{
	int i=0;
	while (a[i])
	{
		if (a[i] != 32)
			return (0);
		i++;
	}
	return(1);
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
	if (!ft_nothing(a->tmp1->arg))
	{
			ft_check_arg(a->tmp1, &store,a);
			ft_execution(a->tmp1, &store, a, 0);
	}
	else 
		printf(" %s: command not found\n",a->tmp1->arg);
}

size_t ft_export2(t_data *a,t_list *data,int i,int index)
{
	a->strenv = NULL;
	char *tmp;
	char *before;
	while (data->arg[i] && (ft_isalnum(data->arg[i]) || data->arg[i] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,data->arg[i]);
		i++;
	}
	before = ft_strdup(a->strenv);
	if (index == 1)
		a->strenv=ft_strjoin22(a->strenv,'=');
	else if (index == 2)
		before = ft_strjoin(before,"+=",1);
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (tmp || !(ft_strcmp(before,a->tmp->arg)))
		{
			if (index == 1)
			{
			free(a->tmp->arg);
			a->tmp->arg = ft_strdup(data->arg);
			}
			else if (index == 2)
				a->tmp->arg = ft_strjoin(a->tmp->arg,ft_strnstr(data->arg,before),1);
			return (free(a->strenv),free(before),1);
		}
		a->tmp = a->tmp->next;
	}
	return(free(a->strenv),free(before),0);
}
/**************************************************************/
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
void change2(t_data *a)
{
	size_t i;
	size_t lock;
	lock = 0;
	i = 0;
	while (a->strtmp[i])
	{
		if (a->strtmp[i] != 32 && lock == 0)
		{
			a->ret[a->k]='"';
			a->k++;
			lock=1;
		}
		else if(a->strtmp[i] == 32 && lock == 1)
		{
			a->ret[a->k]='"';
			a->k++;
			lock=0;
		}
		else
		{
			a->ret[a->k]=a->strtmp[i];
			a->k++;
			i++;	
		}
	}
	if (lock == 1)
	{
			a->ret[a->k]='"';
			a->k++;
	}
}
void ft_change(t_data *a,int index)
{
	a->x++;
	a->strenv = NULL;
	
	while (a->input[a->x] && (ft_isalnum(a->input[a->x]) || a->input[a->x] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,a->input[a->x]);
		a->x++;
	}
	a->x--;
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		a->strtmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (a->strtmp && index ==0)
			change1(a);
		else if (a->strtmp&& index == 1)
			change2(a);
		a->tmp = a->tmp->next;
	}
	free(a->strenv);
	return ;
}
size_t strlen_expand(char *str)
{
	size_t i;
	size_t len;
	int lock;
	lock =0;
	i=0;
	len=0;

	while (str[i])
	{
		if (str[i] != 32 && lock == 0)
		{
			lock=1;
			len+=2;
		}
		else if (str[i] == 32 && lock == 1)
			lock=0;
		i++;
		len++;
	}
	return(len);
}
size_t ft_expand_length(t_data *a,int index)
{
	a->x++;
	a->strenv = NULL;
	char *tmp;
	while (a->input[a->x] && (ft_isalnum(a->input[a->x]) || a->input[a->x] == '_'))
	{
		a->strenv=ft_strjoin22(a->strenv,a->input[a->x]);
		a->x++;
	}
	a->x--;
	
	a->strenv=ft_strjoin22(a->strenv,'=');
	a->tmp = a->e;
	while (a->tmp)
	{
		tmp = ft_strnstr(a->tmp->arg,a->strenv);
		if (tmp && index == 0)
			return(free(a->strenv),ft_strlen(tmp));
		else if (tmp && index == 1)
			return(free(a->strenv),strlen_expand(tmp));
		a->tmp = a->tmp->next;
	}
	return(free(a->strenv),0);
} 
size_t ft_length1(t_data *a)
{
	size_t len;
	
	a->lock = 0;
	a->x = 0;
	a->t='\0';
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
		if (((a->t == '"' || !a->t) && a->input[a->x] == '$' && ft_isdigit(a->input[a->x + 1]))||(a->input[a->x] == '$' && (a->input[a->x+1] == 39 || a->input[a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1] && (ft_isalnum(a->input[a->x+1]) || a->input[a->x+1] == '_'))
			len += ft_expand_length(a,0);		
		else if ((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1] && (ft_isalnum(a->input[a->x+1]) || a->input[a->x+1] == '_'))
			len += ft_expand_length(a,1);
		else
			len++;
		a->x++;
	}
	return (len);
}
char *expand(t_data *a)
{
	a->ret = malloc(sizeof(char)*ft_length1(a)+1);
	if (!a->ret)
		ft_abort(1);
	a->k=0;
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
		if (((a->t == '"' || !a->t) && a->input[a->x] == '$' && ft_isdigit(a->input[a->x + 1]))||(a->input[a->x] == '$' && (a->input[a->x+1] == 39 || a->input[a->x+1] == 34) && !a->lock))
			a->x++;
		else if ((a->t == '"') && a->input[a->x] == '$' && a->input[a->x + 1]&& (ft_isalnum(a->input[a->x+1]) || a->input[a->x+1] == '_'))
			ft_change(a,0);
		else if ((!a->t) && a->input[a->x] == '$' && a->input[a->x + 1]&& (ft_isalnum(a->input[a->x+1]) || a->input[a->x+1] == '_'))
			ft_change(a,1);
		else
		{
			a->ret[a->k]=a->input[a->x];
			a->k++;
		}
		a->x++;
	}
	a->ret[a->k]='\0';
	return(free(a->input),a->ret);
}
/**************************************************************/
int ft_separit(t_data *a)
{
	if (!ft_split22(a))
		return(ft_abort(1),1);
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
void handler(int status) {
	(void)status;
	global.gbl_doc = 0;
    if (!global.gbl_check_doc)
    {
        printf("\n"); // Move to a new line
        rl_replace_line("", 0);
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_redisplay();
    }
    else
    {
        printf("\n"); // Move to a new line
        rl_redisplay();
        rl_on_new_line(); // Regenerate the prompt on a newline
        rl_replace_line("MINISHELL>> ", 0);
    }
}

int main(int argc,char **argv,char **env){
	t_data a;
    global.gbl_check_doc = 0;
    
	if (argc != 1)
		ft_abort(2);
	(void)argv;
	ft_create_env(&a,env);
	signal(SIGINT, handler);
	signal(SIGQUIT, (void*)sigignore);
	a.env22=env;
	while (1)
	{
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
		a.input=a.ret;
		// printf("%s  \n",a.input);
			if (!ft_nothing(a.input))
				open_quote(&a);
		}
		free(a.input);
		

	}
	return 0;
}