#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**dirs;
	char	*cmd_path;

	i = 0;
	path = get_path(envp);
	dirs = ft_split(path, ':');
	while (dirs[i])
	{
		cmd_path = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_strings(dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_strings(dirs);
	return (NULL);
}

void	cleanup(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (i < pipex->cmd_count)
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	i = 0;
	if (pipex->cmd_args)
	{
		while (i < pipex->cmd_count)
		{
			free_strings(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
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
