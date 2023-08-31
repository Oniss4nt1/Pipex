#include "pipex_bonus.h"
#include <stdio.h>

void exec_cmds(t_pipex *pipex)
{
    int i;
    int pipefd[2];
    pid_t pid;
    int status;

    for (i = 0; i < pipex->cmd_count; i++)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (i != 0)
            {
                if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            if (i != pipex->cmd_count - 1)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // Redirecionar a saída para o arquivo de saída
                if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);

            if (execve(pipex->cmd_paths[i], pipex->cmd_args[i], NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);

            if (i != 0)
            {
                close(pipex->in_fd);
            }

            if (i != pipex->cmd_count - 1)
            {
                close(pipefd[1]);
            }

            pipex->in_fd = pipefd[0];
        }
    }

    close(pipex->in_fd);
    close(pipex->out_fd);
}
