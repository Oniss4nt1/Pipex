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

/**
 * Function: get_path
 * -----------------
 * This function is used to get the PATH variable from the environment variables.
 * It iterates through the environment variables, and compares each one with the
 * string "PATH=". If the string is found, the function returns a pointer to the
 * string that contains the PATH variable.
 * 
 * @param: **envp: pointer to the array of strings that contains the environment
 * variables.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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

/**
 * Function: build_cmd_path
 * -----------------
 * This function is used to build the path of the command. It receives the name
 * of the command and the environment variables. It gets the PATH variable from
 * the environment variables, and splits it into an array of strings. Then, it
 * iterates through the array of strings, and joins each string with the command
 * name. If the command works, it returns the path of the command. If the command
 * does not work, it frees the memory and returns NULL.
 * 
 * @param: *cmd: pointer to the string that contains the name of the command.
 * @param: **envp: pointer to the array of strings that contains the environment
 * variables.
 * @var: i: index of the array of strings.
 * @var: *path: pointer to the string that contains the PATH variable.
 * @var: **dirs: pointer to the array of strings that contains the directories, 
 * aka the result of splitting the PATH variable.
 * @var: *temp: pointer to the string that contains the temporary path of the
 * command, this is the command path without the command name.
 * @var: *cmd_path: pointer to the string that contains the path of the command,
 * this is the command path with the command name.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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
