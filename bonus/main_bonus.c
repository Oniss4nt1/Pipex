/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:45:50 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/04 17:45:51 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
