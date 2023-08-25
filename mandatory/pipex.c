/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:23 by brunrodr          #+#    #+#             */
/*   Updated: 2023/08/25 19:02:50 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
# include "../libft/src/ft_putstr_fd.c"

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

void	ft_parse_cmds(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	pipex->cmd_paths = malloc(sizeof(char *) * pipex->cmd_count);
	if (!pipex->cmd_paths)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	pipex->cmd_args = malloc(sizeof(char **) * pipex->cmd_count);
	if (!pipex->cmd_args)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return ;
	}
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmd_paths[i] = ft_strdup(argv[i + 2]);
		pipex->cmd_args[i] = ft_split(argv[i + 2], ' ');		
		i++;
	}
	pipex->cmd_paths[i] = NULL;
	pipex->cmd_args[i] = NULL;
}


void	cleanup(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
		return (1);
init_pipex(&pipex);
	if 
	
	
	return (0);
}
