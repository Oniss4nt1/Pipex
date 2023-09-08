/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/07 14:54:46 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*temp;

	i = 0;
	path = get_path(envp);
	dirs = ft_split(path, ':');
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
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

//refatorar
void	cleanup(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (i < pipex->cmd_count)
		{
			free(pipex->cmd_paths[i]);
			pipex->cmd_paths[i] = NULL;
			i++;
		}
		free(pipex->cmd_paths);
		pipex->cmd_paths = NULL;
	}
	i = 0;
	if (pipex->cmd_args)
	{
		while (i < pipex->cmd_count)
		{
			free_strings(pipex->cmd_args[i]);
			pipex->cmd_args[i] = NULL;
			i++;
		}
		free(pipex->cmd_args);
		pipex->cmd_args = NULL;
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
