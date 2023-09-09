#include "pipex_bonus.h"

void	free_cmd_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		pipex->cmd_paths[i] = NULL;
		i++;
	}
	free(pipex->cmd_paths);
	pipex->cmd_paths = NULL;
}

void	free_cmd_args(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (pipex->cmd_args[i])
	{
		j = 0;
		while (pipex->cmd_args[i][j])
		{
			free(pipex->cmd_args[i][j]);
			pipex->cmd_args[i][j] = NULL;
			j++;
		}
		free(pipex->cmd_args[i]);
		pipex->cmd_args[i] = NULL;
		i++;
	}
	free(pipex->cmd_args);
	pipex->cmd_args = NULL;
}


void	cleanup(t_pipex *pipex)
{
	if (pipex->cmd_paths)
		free_cmd_paths(pipex);
	if (pipex->cmd_args)
		free_cmd_args(pipex);
}

void	free_strings(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
	}
}