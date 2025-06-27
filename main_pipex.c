/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:24 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/18 19:48:43 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_args(t_args *args, int argc)
{
	args->fd_infile =  -1;
	args->fd_outfile =  -1;
	args->cmd_count = argc - 3;
	args->cmd_paths = NULL;
	args->cmd_args = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_args	 args;
	
	if (argc < 5)
		write(2, "Missing arguments, partial execution\n",38); 
	init_args(&args, argc);
	ft_open_files(&args, argc, argv);
	ft_parse_cmds(&args, argv, envp)
	ft_cleanup(&args);
}
