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

/**
 * Function: handle_heredoc
 * -----------------
 * This function is used to handle the here_doc argument. It reads from the
 * standard input until the here_doc string (aka EOF or end of file) is found.
 * The function uses get_next_line() to read from the standard input. The
 * function uses a pipe to store the input from the standard input, and then
 * 
 *
 * @param: *pipex: pointer to the pipex struct.
 * @var: *line: pointer to the string that will store the input from the 
 * standard input.
 * @var: fd[2]: array of two integers that will be used to store
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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
