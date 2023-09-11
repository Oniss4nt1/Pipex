/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:33:35 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/11 10:33:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_bool	check_heredoc(int argc, char **argv, t_pipex *pipex)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc = argv[2];
		pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (pipex->out_fd == -1)
		{
			ft_putstr_fd("Error: can't open output file\n", 2);
			return (is_false);
		}
		pipex->cmd_count = argc - 4;
		return (is_true);
	}
	return (is_false);
}

t_bool	check_files(int argc, char **argv, t_pipex *pipex)
{
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

t_bool	check_args(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (is_false);
	}
	if (check_heredoc(argc, argv, pipex) == is_true)
		return (is_true);
	if (check_files(argc, argv, pipex) == is_true)
		return (is_true);
	return (is_false);
}
