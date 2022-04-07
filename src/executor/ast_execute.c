/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:04:54 by rafernan          #+#    #+#             */
/*   Updated: 2022/04/07 11:00:20 by rafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/executor.h"
#include "../../headers/builtins.h"

t_ast	*ast_root(t_ast *token)
{
	t_ast	*tmp;

	if (!token)
		return (NULL);
	tmp = token;
	while (tmp->prev)
		(tmp) = (tmp->prev);
	return (tmp);
}

void	tk_close(void *tk_ptr)
{
	t_ast	*token;

	token = ast_root((t_ast *)(tk_ptr));
	// while (token == E_PIPE)
	// {
	// 	if (token->right->type == E_CMD)
	// 	{
	// 		if ((token->right->p)[0] > 2)
	// 			close((token->right->p)[0]);
	// 		if ((token->right->p)[1] > 2)
	// 			close((token->right->p)[1]);
	// 	}
	// }
	if (token->type == E_PIPE)
	{
		if ((token->p)[0] > 2)
			close((token->right->p)[0]);
		if ((token->p)[1] > 2)
			close((token->right->p)[1]);
	}
}

int	tk_exec(t_exc *data);
int	test_exec(t_exc *data);
int	ms_is_builtin(t_exc *data, char **s);

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
		if (tmp->type != E_UNDEF && ms_newcmd(&((char **)(tmp->data))[0], data->paths))
		{
			(data->cmd) = (char **)(tmp->data);
			test_exec(data);
		}
		else
		{
			close(data->i_fd);
			close(data->o_fd);
		}
		(data->token) = (data->token->prev);
	}
	ast_iter(ast_root(tmp), tk_close);
	waitpid(tmp->pid, NULL, 0);
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
		close(data->i_fd);
		close(data->o_fd);
		execve((data->cmd)[0], data->cmd, data->envp);
		ast_iter(ast_root(cur), tk_close);
		ast_iter(ast_root(cur), tk_free);
		exit(0); // free stuff
	}
	else
	{
		close(data->i_fd);
		close(data->o_fd);
	}
	return (0);
}

/*




	(P)
(C)		(C)


*/
