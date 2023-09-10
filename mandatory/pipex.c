/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:23 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 17:28:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	command_not_found(t_pipex *pipex);

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
	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (is_false);
	}
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd == -1)
	{
		ft_putstr_fd("Error: can't open input file\n", 2);
		return (is_false);
	}
	pipex->out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd == -1)
	{
		ft_putstr_fd("Error: can't open output file\n", 2);
		return (is_false);
	}
	pipex->cmd_count = argc - 3;
	return (is_true);
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

void	allocate_memory(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd_paths = malloc(sizeof(char *) * (pipex->cmd_count + 1));
	pipex->cmd_args = malloc(sizeof(char **) * (pipex->cmd_count + 1));
	if (!pipex->cmd_paths || !pipex->cmd_args)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	while (i < pipex->cmd_count + 1)
	{
		pipex->cmd_paths[i] = NULL;
		pipex->cmd_args[i] = NULL;
		i++;
	}
}

void	ft_parse_cmds(char **argv, t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	allocate_memory(pipex);
	while (i < pipex->cmd_count)
	{
		pipex->cmd_args[i] = ft_split(argv[i + 2], ' ');
		pipex->cmd_paths[i] = build_cmd_path(pipex->cmd_args[i][0], envp);
		if (!pipex->cmd_paths[i])
		{
			command_not_found(pipex);
			exit(1);
		}
		i++;
	}
	pipex->cmd_paths[i] = NULL;
	pipex->cmd_args[i] = NULL;
}

/**
 * Function: command_not_found
 * -----------------
 * This function is called when the command is not found.
 * It prints an error message, frees the memory, closes the
 * file descriptors and exits the program.
 *
 * @param: *pipex: pointer to the pipex struct.
 *
 * @return: Returns is_true if the arguments are valid, is_false otherwise.
 *
 */

void	command_not_found(t_pipex *pipex)
{
	ft_putstr_fd("Error: command not found\n", 2);
	cleanup(pipex);
	close(pipex->in_fd);
	close(pipex->out_fd);
	exit(1);
}
