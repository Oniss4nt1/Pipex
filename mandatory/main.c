#include "pipex.h"
#include <stdio.h>


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
	int	i;
	char *path;
	char **dirs;
	char *cmd_path;

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



int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
	{
		cleanup(&pipex);
		return (1);
	}

	ft_parse_cmds(argv, &pipex, envp);

	// printf("cmd_paths[0]: %s\n", pipex.cmd_paths[0]);
	// printf("cmd_paths[1]: %s\n", pipex.cmd_paths[1]);
	// printf("cmd_paths[2]: %s\n", pipex.cmd_paths[2]);

	// printf("cmd_args[0][0]: %s\n", pipex.cmd_args[0][0]);
	// printf("cmd_args[0][1]: %s\n", pipex.cmd_args[0][1]);
	// printf("cmd_args[0][2]: %s\n", pipex.cmd_args[0][2]);

	// printf("cmd_args[1][0]: %s\n", pipex.cmd_args[1][0]);
	// printf("cmd_args[1][1]: %s\n", pipex.cmd_args[1][1]);
	// printf("cmd_args[1][2]: %s\n", pipex.cmd_args[1][2]);

	exec_cmds(&pipex);
	cleanup(&pipex);
	return (0);
}




