/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:37 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/05 18:49:02 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void    exec_cmds(t_pipex *pipex)
{
    int i;
    int fd[2];
    pid_t pid;
    int current_in_fd;
    int status;

    i = 0;
    current_in_fd = pipex->in_fd;
    while (i < pipex->cmd_count)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
            exec_child(pipex, current_in_fd, fd, i);
        else if (pid < 0)
            exit(1);
        else
            exec_parent(pid, fd, &current_in_fd, &status);
        i++;
    }
}

void exec_child(t_pipex *pipex, int current_int_fd, int *fd, int i)
{
    dup2(current_int_fd, STDIN_FILENO);
    if (i + 1 != pipex->cmd_count)
        dup2(fd[1], STDOUT_FILENO);
    else
        dup2(pipex->out_fd, STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    execve(pipex->cmd_paths[i], pipex->cmd_args[i], NULL);
    exit(1);
}

void    exec_parent(pid_t pid, int *fd, int *current_in_fd, int *status)
{
    waitpid(pid, status, WNOHANG);
    close(fd[1]);
    *current_in_fd = fd[0];
}