/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:28:28 by brunrodr          #+#    #+#             */
/*   Updated: 2023/09/11 14:55:30 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
t_bool		check_heredoc(int argc, char **argv, t_pipex *pipex);
t_bool		check_files(int argc, char **argv, t_pipex *pipex);
void		command_not_found(t_pipex *pipex);

//########################### PARSING AND PATHS ###############################

void		allocate_memory(t_pipex *pipex);
void		parse_cmds(char **argv, t_pipex *pipex, char **envp);
char		*get_path(char **envp);
char		*build_cmd_path(char *cmd, char **envp);
char		*search_path(char **envp);
char		*test_cmd_path(char **dirs, char *cmd);

//########################### EXECUTION ########################################

void		exec_cmds(t_pipex *pipex);
void		child_process(t_pipex *pipex, int input_fd, int *fd, int i);
void		parent_process(int input_fd, int *fd);

//########################### HEREDOC ##########################################

void		handle_heredoc(t_pipex *pipex);

//########################### FREE #############################################

void		cleanup(t_pipex *pipex);
void		free_strings(char **strs);

#endif