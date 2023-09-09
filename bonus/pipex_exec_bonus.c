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

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void exec_cmds(t_pipex *pipex)
{
    int i;
    int fd[2];
    pid_t pid;
    int current_in_fd;
    int status;
    int pipe_fds[pipex->cmd_count - 1];

    i = 0;
    current_in_fd = pipex->in_fd;
    
    while (i < pipex->cmd_count)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            exec_child(pipex, current_in_fd, fd, i);
            exit(1); // Make sure the child process exits after execution.
        }
        else if (pid < 0)
            exit(1);
        else
            exec_parent(pid, fd, &current_in_fd, &status);
        
        // Store the read end of the pipe in the array
        if (i > 0)
        {
            pipe_fds[i - 1] = fd[0];
        }
        i++;
    }
    
    // Close all the file descriptors stored in the array
    for (i = 0; i < pipex->cmd_count - 1; i++)
    {
        close(pipe_fds[i]);
    }
    
    close(current_in_fd);
}

void exec_child(t_pipex *pipex, int current_int_fd, int *fd, int i)
{
    dup2(current_int_fd, STDIN_FILENO);
    
    if (i + 1 != pipex->cmd_count)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); // Close the read end of the pipe
    }
    else
    {
        dup2(pipex->out_fd, STDOUT_FILENO);
        close(fd[1]); // Close the write end of the last pipe
    }
    
    execve(pipex->cmd_paths[i], pipex->cmd_args[i], NULL);
    
    // In case execve fails
    // perror("execve");
    exit(1);
}

void exec_parent(pid_t pid, int *fd, int *current_in_fd, int *status)
{
    close(fd[1]); // Close the write end of the pipe
    waitpid(pid, status, 0); // Wait for the child process to finish
    *current_in_fd = fd[0]; // Set the current input file descriptor for the next command
}
