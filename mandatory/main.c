#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_pipex(&pipex);
	if (!check_args(argc, argv, &pipex))
	{
		cleanup(&pipex);
		return (1);
	}
	ft_parse_cmds(argv, &pipex, envp);
	if (!pipex.cmd_paths)
	{
		cleanup(&pipex);
		return (1);
	}
	exec_cmds(&pipex);
	cleanup(&pipex);
	return (0);
}
