/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/05 17:51:33 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/executor.h"
#include "../../headers/builtins.h"

int	tk_exec(t_exc *data);
int	test_exec(t_exc *data);
int	ms_is_builtin(char *s);

int	ast_executor(t_ast *tokens, int *stat, char **env)
{
	t_exc	data;

	(data.token) = tokens;
	(data.i_fd) = STDIN_FILENO;
	(data.o_fd) = STDOUT_FILENO;
	(data.envp) = env;
	(data.stat) = stat;
	(data.cmd) = NULL;
	(data.paths) = ms_paths();
	while (data.token->left && !tk_is_rd(data.token->left->type))
		(data.token) = (data.token->left);
	return (tk_exec(&data));
}

int	tk_exec(t_exc *data)
{
	t_ast	*tmp;

	tmp = (data->token);
	if (!data->token)
		return (0);
	while (data->token)
	{
		if (ms_get_output(data->token, &data->o_fd) == -1)
			return (-1);
		if (ms_get_input(data->token, &data->i_fd) == -1)
		{
			close(data->o_fd);
			return (-1);
		}
		if (data->token->type == E_PIPE)
			tmp = (data->token->right);
		(data->stat) = ms_is_builtin(((char **)(tmp->data))[0]);
		if (data->stat == -1 && tmp->type != E_UNDEF && ms_newcmd(&((char **)(tmp->data))[0], data->paths))
		{
			(data->cmd) = (char **)(tmp->data);
			test_exec(data);
		}
		else if (data->stat == -1)
		{
			close(data->i_fd);
			close(data->o_fd);
		}
		(data->token) = (data->token->prev);
	}
	ft_free_m(data->paths);
	return (0);
}

int	test_exec(t_exc *data)
{
	t_ast	*cur;
	
	cur = data->token;
	if (data->token->type != E_CMD)
		cur = data->token->right;
	cur->pid = fork();
	if (cur->pid == -1)
		return (-1);
	if (cur->pid == 0)
	{
		dup2(data->i_fd, STDIN_FILENO);
		dup2(data->o_fd, STDOUT_FILENO);
		execve((data->cmd)[0], data->cmd, data->envp);
		close(data->i_fd);
		close(data->o_fd);
		exit(0); // free stuff
	}
	else
	{
		close(data->i_fd);
		close(data->o_fd);
		wait(0);
	}
	return (0);
}

int	ms_is_builtin(char *s)
{
	close(data->i_fd);
	if (ft_strncmp(s, "exit", 5) == 0)
		return (ft_exit());
	return (-1);
}

/*




	(P)
(C)		(C)


*/