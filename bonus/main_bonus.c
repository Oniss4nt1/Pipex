/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:50 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/11 14:55:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
	{
		cleanup(&pipex);
		return (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		handle_heredoc(&pipex);
	parse_cmds(argv, &pipex, envp);
	exec_cmds(&pipex);
	close(pipex.in_fd);
	close(pipex.out_fd);
	cleanup(&pipex);
	return (0);
}
