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

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <sys/wait.h>
#include "ft_printf/ft_printf.h"

typedef struct s_args
{
	int	fd_infile;
	int	fd_outfile;
	int	cmd_count;
	char	**cmd_paths;//array de strings ej. {"cat", "-e", NULL}
	char	***cmd_args; //array de array strings ej. {"cat", "-e", NULL}
} t_args;

char	**ft_split(char const *s, char c);

// utils_pipex
void	ft_cleanup(t_args *args);
void	ft_open_files(t_args *args, int argc, char **argv);

// utils_pipex_2
void	ft_parse_cmds(t_args *args, char ** argv, char **envp);
char	*get_cmd_path(char *cmd, char **envp);

// utils_libft
int	ft_strncmp(const char *s1, const char *s2, size_t contador);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
