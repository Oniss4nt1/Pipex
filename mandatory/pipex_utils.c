#include "pipex.h"
#include <stdio.h>
# include "../libft/src/ft_putstr_fd.c"
# include "../libft/src/ft_strdup.c"
# include "../libft/src/ft_split.c"
# include "../libft/src/ft_substr.c"
# include "../libft/src/ft_strlen.c"

void	free_strings(char **strs);

void	cleanup(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->cmd_paths)
	{
		while (pipex->cmd_paths[i])
		{
			free(pipex->cmd_paths[i]);
			i++;
		}
		free(pipex->cmd_paths);
	}
	i = 0;
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
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