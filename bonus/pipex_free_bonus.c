#include "pipex_bonus.h"

/**
 * Function: free_cmd_paths
 * -----------------
 * This function is used to free the memory allocated for the cmd_paths array.
 * cmd_paths is an array of strings that contains the paths of the commands.
 * 
 * @param: *pipex: pointer to the pipex struct.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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

/**
 * Function: free_cmd_args
 * -----------------
 * This function is used to free the memory allocated for the cmd_args array.
 * cmd_args is an array of arrays of strings that contains the arguments of the
 * commands.
 * 
 * @param: *pipex: pointer to the pipex struct.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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

/**
 * Function: cleanup
 * -----------------
 * This is a function that is called at the end of the program or when an error
 * occurs. If the cmd_paths and cmd_args arrays are not NULL, it calls the
 * free_cmd_paths() and free_cmd_args() functions to free the memory allocated
 * for the cmd_paths and cmd_args arrays.
 * 
 * @param: *pipex: pointer to the pipex struct.
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

void	cleanup(t_pipex *pipex)
{
	if (pipex->cmd_paths)
		free_cmd_paths(pipex);
	if (pipex->cmd_args)
		free_cmd_args(pipex);
}

/**
 * Function: free_strings
 * -----------------
 * This is a function that is called by the build_cmd_path() function to free
 * the memory allocated for the array of strings that contains the directories
 * of the PATH variable. It receives the array of strings as an argument, and
 * iterates through the array of strings, freeing each string and then freeing
 * the array of strings.
 * 
 * @param: **strs: pointer to the array of strings that contains the directories
 *
 * @return: This is a void function, so it does not return a value.
 *
 */

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
