/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:48:21 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 16:52:29 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
 *  * 
 * @param: pipex: pointer to the pipex struct.
 *
 * @return: Returns is_true if the arguments are valid, is_false otherwise.
 *
 */

void	exec_cmds(t_pipex *pipex)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		close(pipex->in_fd);
		close(pipex->out_fd);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipex->in_fd);
		close(pipex->out_fd);
		exit(1);
	}
	else if (pid == 0)
		exec_child(pipex, pipefd);
	else
		exec_parents(pipex, pipefd);
}

/**
 * Function: exec_child
 * -----------------
 * Function to be executed by the child process. This function redirects the
 * standard input to the input file and the standard output to the pipe. Then
 * it executes the first command.
 *
 * @param: *pipex: pointer to the pipex struct.
 * @param: pipefd: array of two integers that will be used to store the file
 *
 * @return: Is a void function, but this function uses the execve() function,
 * that is responsible for executing the command, changing the process image of
 * my program.
 *
 */

void	exec_child(t_pipex *pipex, int pipefd[2])
{
	dup2(pipex->in_fd, STDIN_FILENO);
	close(pipex->in_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipex->out_fd);
	close(pipefd[0]);
	if (!pipex->cmd_paths[0])
	{
		ft_putstr_fd("Error: command not found\n", 2);
		return ;
	}
	execve(pipex->cmd_paths[0], pipex->cmd_args[0], NULL);
}

/**
 * Function: exec_parents
 * -----------------
 * Function to be executed by the parent process. This function redirects the
 * standard input to the pipe and the standard output to the output file. Then
 * it executes the second command. 
 * 
 * @param: *pipex: pointer to the pipex struct.
 * @param: pipefd: array of two integers that will be used to store the file
 *
 * @return: Is a void function, but this function uses the execve() function,
 * that is responsible for executing the command, changing the process image of
 * my program.
 *
 */

void	exec_parents(t_pipex *pipex, int pipefd[2])
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	if (pid == -1)
	{
		ft_putstr_fd("Error: wait failed\n", 2);
		return ;
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipex->out_fd);
	if (!pipex->cmd_paths[1])
	{
		ft_putstr_fd("Error: command not found\n", 2);
		command_not_found(pipex);
	}
	execve(pipex->cmd_paths[1], pipex->cmd_args[1], NULL);
}
