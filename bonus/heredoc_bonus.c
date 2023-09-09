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
