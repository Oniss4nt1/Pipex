/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:48:25 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 14:22:45 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*search_path(char **envp);
char	*test_cmd_path(char **dirs, char *cmd);

char	*build_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;

	if (!cmd || !*cmd)
		return (NULL);
	path = search_path(envp);
	dirs = ft_split(path, ':');
	return (test_cmd_path(dirs, cmd));
}

char	*search_path(char **envp)
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

char	*test_cmd_path(char **dirs, char *cmd)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	i = 0;
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
