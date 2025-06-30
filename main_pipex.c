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

static void	init_args(t_args *args, int argc, char **argv)
{
	args->fd_infile =  -1;
	args->fd_outfile =  -1;
	args->outfile_name = argv[argc - 1];
	args->cmd_count = argc - 3;
	args->cmd_paths = NULL;
	args->cmd_args = NULL;
	args->pid = malloc(sizeof(pid_t *) * args->cmd_count);
	if (!args->pid)
		handle_error("failure in malloc for pids", NULL, args);
	ft_memset(args->pid, 0, sizeof(pid_t *) * args->cmd_count);//para evitar elementos 
	// no inicializados cuando hay menos cmds
}

static void	manage_pipes(t_args *args, char **envp)
{
	int	i;
	
	i = 0;
	if (args->cmd_count == 1)
	{
		ft_exec_cmd(args, envp, i);
		waitpid(args->pid[0], NULL, 0);
	}
	else 
	{
		if (pipe(args->pipes_fd) < 0)
				handle_error("pipe failed", NULL, args);
		while (i < args->cmd_count)
		{
			ft_exec_cmd(args, envp, i);
			i++;
		}
			close(args->pipes_fd[0]);
			close(args->pipes_fd[1]);
			waitpid(args->pid[0], NULL, 0);
			waitpid(args->pid[1], NULL, 0);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_args	 args;
	
	init_args(&args, argc, argv);
	ft_open_files(&args, argc, argv);
	ft_parse_cmds(&args, argv, envp);
	manage_pipes(&args, envp);
	ft_cleanup(&args);
}
