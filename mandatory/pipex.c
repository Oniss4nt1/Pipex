/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:23 by brunrodr          #+#    #+#             */
/*   Updated: 2023/08/28 17:15:24 by brunrodr         ###   ########.fr       */
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

void	ft_parse_cmds(char **argv, t_pipex *pipex, char **envp)
{
	int	i;

	pipex->cmd_paths = malloc(sizeof(char **) * pipex->cmd_count);
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
		pipex->cmd_args[i] = ft_split(argv[i + 2], ' ');
		pipex->cmd_paths[i] = build_cmd_path(pipex->cmd_args[i][0], envp);
		printf("cmd_paths[%d]: %s\n", i, pipex->cmd_paths[i]);
		i++;
	}
}

/**
 * Function: exec_cmds
 * -----------------
 * Function that executes the commands. This function uses fork() to create a
 * child process and then uses execve() to execute the commands. The parent
 * process waits for the child process to finish, and then executes the second
 * command.
 * 
 * The function uses the following variables:
 * - pipefd: array of two integers that will be used to store the file
 * descriptors of the pipe.
 * 
 * - pid: variable that will store the process id of the child process.
 * 
 * - STDIN_FILENO: macro that represents the file descriptor of the standard
 * input.
 * 
 * - STDOUT_FILENO: macro that represents the file descriptor of the standard
 * output.
 *
 * - pipe: function that creates a pipe.
 * 
 * - fork: function that creates a child process.
 * 
 * - dup2: function that duplicates a file descriptor and redirects it to
 * another file descriptor.
 * 
 * - execve: function that executes a command.
 * 
 * @param: pipex: pointer to the pipex struct.
 *
 * @return: Returns is_true if the arguments are valid, is_false otherwise.
 *
 */

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
		if (!pipex->cmd_paths[0])
		{
			ft_putstr_fd("Error: command not found\n", 2);
			return ;
		}
		execve(pipex->cmd_paths[0], pipex->cmd_args[0], NULL);
		free(pipex->cmd_paths[0]);
	}
	else // parent
	{
		wait(NULL); // wait for child to finish
		dup2(pipefd[0], STDIN_FILENO); // read from pipe
		dup2(pipex->out_fd, STDOUT_FILENO); // write to file
		close(pipefd[1]); // close write end of pipe
		if (!pipex->cmd_paths[1])
		{
			ft_putstr_fd("Error: command not found\n", 2);
			return ;
		}
		execve(pipex->cmd_paths[1], pipex->cmd_args[1], NULL);
		free(pipex->cmd_paths[1]);
	}
}





