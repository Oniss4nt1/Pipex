/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:23 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 14:14:06 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * Function: init_pipex
 * -----------------
 * Initializes the pipex struct.
 *
 * @param: pipex: pointer to the pipex struct.
 *
 * @return: Is a void function.
 *
 */

void	init_pipex(t_pipex *pipex)
{
	pipex->in_fd = 0;
	pipex->out_fd = 0;
	pipex->cmd_count = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->here_doc = NULL;
}

/**
 * Function: check_args
 * -----------------
 * Checks if the arguments are valid.
 *
 * @param: argc: number of arguments.
 * @param: argv: array of arguments.
 * @param: pipex: pointer to the pipex struct.
 *
 * @return: Returns is_true if the arguments are valid, is_false otherwise.
 *
 */

t_bool	check_args(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (is_false);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc = argv[2];
		pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (pipex->out_fd == -1)
		{
			ft_putstr_fd("Error: can't open output file\n", 2);
			return (is_false);
		}
		pipex->cmd_count = argc - 4;
		return (is_true);
	}
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd == -1)
	{
		ft_putstr_fd("Error: can't open input file\n", 2);
		return (is_false);
	}
	pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd == -1)
	{
		ft_putstr_fd("Error: can't open output file\n", 2);
		return (is_false);
	}
	pipex->cmd_count = argc - 3;
	return (is_true);
}

	// else if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	// {
	// 	pipex->here_doc = ft_strdup(argv[2]);
	// 	pipex->in_fd = 
	// 	pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (pipex->out_fd == -1)
	// 	{
	// 		ft_putstr_fd("Error: can't open output file\n", 2);
	// 		return (is_false);
	// 	}
	// 	pipex->cmd_count = argc - 4;
	// 	return (is_true);
	// }

/**
 * Function: check_args
 * -----------------
 * Checks if the arguments are valid.
 *
 * @param: argc: number of arguments.
 * @param: argv: array of arguments.
 * @param: pipex: pointer to the pipex struct.
 *
 * @return: Returns is_true if the arguments are valid, is_false otherwise.
 *
 */

void	ft_parse_cmds(char **argv, t_pipex *pipex, char **envp)
{
	int	i;
	int arg_index;

	i = 0;
	pipex->cmd_paths = malloc(sizeof(char **) * pipex->cmd_count + 1);
	pipex->cmd_args = malloc(sizeof(char **) * pipex->cmd_count + 1);
	if (!pipex->cmd_paths || !pipex->cmd_args)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	while (i < pipex->cmd_count)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			arg_index = pipex->cmd_count - i + 2;
		else
			arg_index = i + 2;

		pipex->cmd_args[i] = ft_split(argv[arg_index], ' ');
		pipex->cmd_paths[i] = build_cmd_path(pipex->cmd_args[i][0], envp);
		i++;
	}
	pipex->cmd_paths[i] = NULL;
	pipex->cmd_args[i] = NULL;

	if (pipex->cmd_paths[0] == NULL)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		cleanup(pipex);
		close(pipex->in_fd);
		close(pipex->out_fd);
		exit(1);
	}
}
