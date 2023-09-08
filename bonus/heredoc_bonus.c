/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:49:34 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 11:21:58 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <string.h>
#include <stdio.h>

void	handle_heredoc(t_pipex *pipex)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, pipex->here_doc, ft_strlen(pipex->here_doc)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = get_next_line(0);
	}
	close(fd[1]);
	pipex->in_fd = fd[0];
}

// void	handle_heredoc(t_pipex *pipex)
// {
// 	int fd[2];
// 	char *line;
// 	pid_t pid;

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		while (1)
// 		{
// 			line = get_next_line(STDIN_FILENO);
// 			if (ft_strncmp(line, pipex->here_doc, ft_strlen(pipex->here_doc)) == 0)
// 			{
// 				free(line);
// 				close(pipex->out_fd);
// 				exit(EXIT_SUCCESS);
// 			}
// 			ft_putstr_fd(line, fd[1]);
// 			ft_putstr_fd("\n", fd[1]);
// 			free(line);
// 		}
// 		// close(fd[1]);
// 		// exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[1]);
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// }

// void	handle_heredoc(t_pipex *pipex)
// {
// 	char *line;
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			line = get_next_line(STDIN_FILENO);
// 			if (ft_strncmp(line, pipex->here_doc, ft_strlen(pipex->here_doc)) == 0)
// 			{
// 				free(line);
// 				close(pipex->out_fd);
// 				exit(EXIT_SUCCESS);
// 			}
// 			ft_putstr_fd(line, pipex->out_fd);
// 			ft_putstr_fd("\n", pipex->out_fd);
// 			free(line);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// }

