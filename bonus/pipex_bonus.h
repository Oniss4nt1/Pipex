/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:28:28 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/08 14:08:04 by brunrodr         ###   ########.fr       */
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
	char	*here_doc;
}			t_pipex;

//########################### FUNCTIONS ########################################

void		init_pipex(t_pipex *pipex);

//########################### CHECKS ###########################################

t_bool		check_args(int argc, char **argv, t_pipex *pipex);
void		command_not_found(t_pipex *pipex);


//########################### PARSING AND PATHS ###############################

void		ft_parse_cmds(char **argv, t_pipex *pipex, char **envp);
char		*get_path(char **envp);
char		*build_cmd_path(char *cmd, char **envp);

//########################### EXECUTION ########################################

void		exec_cmds(t_pipex *pipex);
void 		exec_child(t_pipex *pipex, int current_int_fd, int *fd, int i);
void    	exec_parent(pid_t pid, int *fd, int *current_in_fd, int *status);

//########################### HEREDOC ##########################################

void	handle_heredoc(t_pipex *pipex);

//########################### FREE #############################################

void		cleanup(t_pipex *pipex);
void		free_strings(char **strs);

#endif