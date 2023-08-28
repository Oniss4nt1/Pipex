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
#include <stdio.h>

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

void	ft_parse_cmds(char **argv, t_pipex *pipex)
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



void	exec_cmds(t_pipex *pipex)
{
	int	pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		return ;
	}
	else if (pid == 0) // child
	{
		dup2(pipex->in_fd, STDIN_FILENO); // read from file
		dup2(pipefd[1], STDOUT_FILENO); // write to pipe
		close(pipefd[0]); // close read end of pipe
		execve(pipex->cmd_paths[0], pipex->cmd_args[0], NULL); // execute cmd
	}
	else // parent
	{
		wait(NULL); // wait for child to finish
		dup2(pipefd[0], STDIN_FILENO); // read from pipe
		dup2(pipex->out_fd, STDOUT_FILENO); // write to file
		close(pipefd[1]); // close write end of pipe
		execve(pipex->cmd_paths[1], pipex->cmd_args[1], NULL); // execute cmd
	}
}


int main(int argc, char **argv)
{
	t_pipex pipex;

	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
	{
		cleanup(&pipex);
		return (1);
	}

	ft_parse_cmds(argv, &pipex);
	printf("cmd_paths[0]: %s\n", pipex.cmd_paths[0]);
	printf("cmd_paths[1]: %s\n", pipex.cmd_paths[1]);
	printf("cmd_paths[2]: %s\n", pipex.cmd_paths[2]);

	printf("cmd_args[0][0]: %s\n", pipex.cmd_args[0][0]);
	printf("cmd_args[0][1]: %s\n", pipex.cmd_args[0][1]);
	printf("cmd_args[0][2]: %s\n", pipex.cmd_args[0][2]);

	printf("cmd_args[1][0]: %s\n", pipex.cmd_args[1][0]);
	printf("cmd_args[1][1]: %s\n", pipex.cmd_args[1][1]);
	printf("cmd_args[1][2]: %s\n", pipex.cmd_args[1][2]);
	exec_cmds(&pipex);
	cleanup(&pipex);
	return (0);
}