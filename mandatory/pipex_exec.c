/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:48:21 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/11 10:36:06 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Function: exec_cmds
 * -----------------
 * This function is resposible for create pipes for communication between the
 * commands and creates fork processes. Forks in a nutshell are used to create
 * child processes. In this case, child process executes the first command and
 * the parent process executes the second command.
 *
 * @param: *pipex: pointer to the pipex struct.
 * @variables: fd[2]: array of two integers that will be used to store the file

	* @variables: pid: variable that will store the process id of the child process.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

void	exec_cmds(t_pipex *pipex)
{
	int		pipefd[2];
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
	else if (pid == 0)
		child_process(pipex, pipefd);
	else
		parent_process(pipex, pipefd);
}

/**
 * Function: child_process
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

void	child_process(t_pipex *pipex, int pipefd[2])
{
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	execve(pipex->cmd_paths[0], pipex->cmd_args[0], NULL);
}

/**
 * Function: parent_process
 * -----------------
 * Function to be executed by the parent process. This function waits for the
 * child process to finish, and then redirects the standard output to the
 * output file and the standard input to the pipe. Then it executes the second
 * command.
 * 
 * @param: *pipex: pointer to the pipex struct.
 * @param: pipefd: array of two integers that will be used to store the file
 *
 * @return: Is a void function, but this function uses the execve() function,
 * that is responsible for executing the command, changing the process image of
 * my program.
 *
 */

void	parent_process(t_pipex *pipex, int pipefd[2])
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	if (pid == -1)
	{
		ft_putstr_fd("Error: wait failed\n", 2);
		return ;
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipefd[1]);
	execve(pipex->cmd_paths[1], pipex->cmd_args[1], NULL);
}
