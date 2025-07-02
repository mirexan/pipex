/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:05:50 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/21 16:32:05 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <sys/wait.h>
# include "ft_printf/ft_printf.h"

typedef struct s_args
{
	int		fd_infile;
	int		fd_outfile;
	int		cmd_count;
	int		pipes_fd[2];
	char	*outfile_name;
	char	**cmd_paths;
	char	***cmd_args;
	pid_t	*pid;
}	t_args;

char	**ft_split(char const *s, char c);

// utils_pipex
void	ft_cleanup(t_args *args);
void	ft_open_files(t_args *args, int argc, char **argv);
void	free_array(char **arr);
void	handle_error(char *error_text, char *detail, t_args *args);
void	print_error(char *file_name);

// utils_pipex_2
void	ft_parse_cmds(t_args *args, char **argv, char **envp);
char	*get_cmd_path(char *cmd, char **envp);

//ft_exec_cmd
void	ft_exec_cmd(t_args *args, char **envp, int i);

#endif
