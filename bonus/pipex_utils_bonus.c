/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:42 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/13 11:24:51 by brunrodr         ###   ########.fr       */
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
 * of the command and the environment variables. First, this function checks
 * if the command is valid, if it is not, it returns NULL. Then, it calls the
 * function search_path, which returns the PATH variable, and splits it into
 * an array of strings. Then, it calls the function test_cmd_path, which tests
 * if the command exists in any of the directories of the PATH variable. If the
 * command exists, it returns the path of the command, if it does not, it returns
 * NULL.
 * 
 * @param: *cmd: pointer to the string that contains the name of the command.
 * @param: **envp: pointer to the array of strings that contains the environment
 * variables.
 * @var: *path: pointer to the string that contains the PATH variable.
 * @var: **dirs: pointer to the array of strings that contains the directories, 
 * aka the result of splitting the PATH variable.
 *
 * @return: Returns a pointer to the string that contains the path of the command
 * if the command exists, or NULL if it does not.
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

/**
 * Function: search_path
 * -----------------
 * This function is used to get the PATH variable from the environment variables.
 * It iterates through the environment variables, and compares each one with the
 * string "PATH=". If the string is found, the function returns a pointer to the
 * string that contains the PATH variable. Note that the function returns the
 * string without the "PATH=" part.
 * 
 * @param: **envp: pointer to the array of strings that contains the environment
 * variables.
 * @var: i: integer that is used to iterate through the environment variables.
 *
 * @return: Returns a pointer to the string that contains the PATH variable or
 * NULL if it does not exist.
 *
 */

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

/**
 * Function: test_cmd_path
 * -----------------
 * This function is used to test if the command exists in any of the directories
 * of the PATH variable. It receives an array of strings that contains the directories
 * splitted from the PATH variable, and the name of the command. It iterates through
 * the array of strings, and joins each directory with the command. Then, it tests
 * if the command exists in the directory. If it does, it returns the path of the
 * command, if it does not, it returns NULL.
 * 
 * @param: **dirs: pointer to the array of strings that contains the directories,
 * aka the result of splitting the PATH variable.
 * @param: *cmd: pointer to the string that contains the name of the command.
 * @var: i: integer that is used to iterate through the environment variables.
 * @var: *temp: pointer to the string that contains the directory, this is used
 * to join the directory with the '/' character. After that, it is freed.
 * @var: *cmd_path: This is used to join the directory with the command. After
 * that, this is tested if it exists. If it does, it is returned, if it does not,
 * it is freed.
 *
 * @return: Returns a pointer to the string that contains the PATH variable or
 * NULL if it does not exist.
 *
 */

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
