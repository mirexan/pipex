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

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_args
{
	int	fd_infile;
	int	fd_outfile;
	int	cmd_count;
	char	**cmd_paths;
	char	**cmd_args;
} t_args;

char	**ft_split(char const *s, char c);


