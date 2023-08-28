/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:28:28 by brunrodr          #+#    #+#             */
/*   Updated: 2023/08/25 16:46:16 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

//########################### STRUCTURES #######################################

typedef enum e_bool
{
	is_false,
	is_true
}			t_bool;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		cmd_count;
	char	**cmd_paths;
	char	***cmd_args;
}			t_pipex;

#endif

//########################### FUNCTIONS ########################################

void	init_pipex(t_pipex *pipex);

//########################### CHECKS ###########################################

t_bool	check_args(int argc, char **argv, t_pipex *pipex);

//########################### PARSING ##########################################

void	ft_parse_cmds(char **argv, t_pipex *pipex);

//########################### EXECUTION ########################################

void	exec_cmds(t_pipex *pipex);

//########################### FREE #############################################

void	cleanup(t_pipex *pipex);
void	free_strings(char **strs);
