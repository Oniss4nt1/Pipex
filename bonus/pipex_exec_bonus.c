/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 15:23:40 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

/**
 * Function: exec_cmds
 * -----------------
 * This function create pipes for communication between the commands and creates
 * fork processes. Forks in a nutshell are used to create child processes. 
 * For each command, a child process and pipes are created. The child process 
 * executes the command, and the parent process waits for the child process 
 * to finish. Here, the parent process only controls the timing of the commands,
 * and the child processes execute the commands.
 *
 * @param: *pipex: pointer to the pipex struct.
 * @variables: fd[2]: array of two integers that will be used to store the file
 * @variables: input_fd: file descriptor of the input file,
	used for the infile and
 * for the output of the previous command.

	* @variables: pid: variable that will store the process id of the child process.
 * @variables: i: index of the command.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

void	exec_cmds(t_pipex *pipex)
{
	int		fd[2];
	int		input_fd;
	pid_t	pid;
	int		i;

	i = 0;
	input_fd = pipex->in_fd;
	while (i < pipex->cmd_count)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("Error: fork failed\n", 2);
			return ;
		}
		if (pid == 0)
			child_process(pipex, input_fd, fd, i);
		else
			parent_process(input_fd, fd);
		input_fd = fd[0];
		i++;
	}
	close(input_fd);
}

/**
 * Function: child_process
 * -----------------
 * This function is executed by the child process. It redirects the input and
 * output file descriptors to the pipe, and then executes the command. If the
 * command is the last one, the output file descriptor is redirected to the
 * outfile. When the command is executed, the child process exits.
 *
 * @param: *pipex: pointer to the pipex struct.
 * @var: input_fd: file descriptor of the input file, used for the infile and
 * for the output of the previous command.
 * @var: *fd: pointer to the array of two integers that will be used to store
 * the file descriptors of the pipe.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

void	child_process(t_pipex *pipex, int input_fd, int *fd, int i)
{
	dup2(input_fd, STDIN_FILENO);
	if (i != pipex->cmd_count - 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(pipex->out_fd, STDOUT_FILENO);
	close(fd[0]);
	execve(pipex->cmd_paths[i], pipex->cmd_args[i], NULL);
	exit(0);
}

/**
 * Function: parent_process
 * -----------------
 *
 * This function is executed by the parent process. It waits for the child 	
 * process to finish, and then closes the write end of the pipe. If the input 
 * file descriptor is not the standard input, it is closed. This is important 
 * because the input file descriptor is used for the infile at the beginning 
 * of the execution, and for the output of the previous command. This allows 
 * the execution of the commands in a sequential way.
 * 
 * @param: *pipex: pointer to the pipex struct.
 * @var: input_fd: file descriptor of the input file,
	used for the infile and
 * for the output of the previous command.
 * @variables: *fd: pointer to the array of two integers that will be used 
 * to store the file descriptors of the pipe.
 * @variables: i: index of the command.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

void	parent_process(int input_fd, int *fd)
{
	wait(NULL);
	close(fd[1]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
}
