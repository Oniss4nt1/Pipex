#include "pipex_bonus.h"
#include "../libft/include/libft.h"
#include "../libft/src/ft_split.c"
#include "../libft/src/ft_strjoin.c"
#include "../libft/src/ft_strncmp.c"
#include "../libft/src/ft_putstr_fd.c"
#include "../libft/src/ft_substr.c"
#include "../libft/src/ft_strlen.c"
#include "../libft/src/ft_strdup.c"









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
	exec_cmds(&pipex);
	cleanup(&pipex);
	return (0);
}
