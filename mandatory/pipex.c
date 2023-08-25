/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:23 by brunrodr          #+#    #+#             */
/*   Updated: 2023/08/25 17:26:33 by brunrodr         ###   ########.fr       */
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


int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (!envp)
	{
		ft_putstr_fd("Error: no environment\n", 2);
		return (1);
	}
	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
		return (1);
	
	return (0);
}
