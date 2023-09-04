#include "pipex_bonus.h"
#include <stdio.h>

void exec_cmds(t_pipex *pipex)
{
    int i;
    int pipefd[2];
    pid_t pid;

    i = 0;
    while (i < pipex->cmd_count)
    {
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
        if (pid == 0)
            exec_child(pipex, pipefd, i);
        else
        {
            exec_parents(pipex, pipefd, i, pid);
            if (i != pipex->cmd_count - 1)
                close(pipefd[1]);
        }
        i++;
    }
    close(pipex->in_fd);
    close(pipex->out_fd);
}

void    exec_child(t_pipex *pipex, int pipefd[2], int i)
{
    if (i == 0)
    {
        if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
        {
            ft_putstr_fd("Error: dup2 failed\n", 2);
            return ;
        }
    }
    if (i != pipex->cmd_count -1)
    {
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("Error: dup2 failed\n", 2);
            return ;
        }
    }
    else
    {
        if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("Error: dup2 failed\n", 2);
            return ;
        }
    }
    close(pipefd[0]);
    close(pipefd[1]);
    execve(pipex->cmd_paths[i], pipex->cmd_args[i], NULL);
}

void exec_parents(t_pipex *pipex, int pipefd[2], int i, pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);

    if (i != 0)
        close(pipefd[0]);
    if (i != pipex->cmd_count - 1)
        close(pipefd[1]);
    pipex->in_fd = pipefd[0];
}