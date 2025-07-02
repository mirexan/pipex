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

static	void	waiting_for_children(t_args *args)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < args->cmd_count)
	{
		waitpid(args->pid[i], &status, 0);
		if (i == args->cmd_count - 1 && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);//esperamos
		i++;//el codigo de saluda del ultimo comando
	}
	ft_cleanup(args);
	exit(exit_code);
}

static void	init_args(t_args *args, int argc, char **argv)
{
	args->fd_infile = -1;
	args->fd_outfile = -1;
	args->outfile_name = argv[argc - 1];
	args->cmd_count = argc - 3;
	args->cmd_paths = NULL;
	args->cmd_args = NULL;
	args->pid = malloc(sizeof(pid_t *) * args->cmd_count); //un proceso hijo para cada comando
	if (!args->pid)
		handle_error("failure in malloc for pids", NULL, args);
	ft_memset(args->pid, 0, sizeof(pid_t *) * args->cmd_count);//los inicializamos en 0, para evitar elementos no inicializados cuando hay menos comandos
}

static void	manage_pipes(t_args *args, char **envp)
{
	int	i;

	i = 0;
	if (args->cmd_count == 1)// si solo hay un cmd
	{
		ft_exec_cmd(args, envp, i);
		waitpid(args->pid[0], NULL, 0);
		ft_cleanup(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (pipe(args->pipes_fd) < 0)
			handle_error("pipe failed", NULL, args);
		while (i < args->cmd_count)
		{
			if (i == 0 && args->fd_infile < 0)
				close(args->pipes_fd[1]);
			else
				ft_exec_cmd(args, envp, i);
			i++;
		}
		close(args->pipes_fd[0]);
		close(args->pipes_fd[1]);
		waiting_for_children(args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_args	args;

	if (argc < 4 || argc > 5)
		exit (1);
	init_args(&args, argc, argv);
	ft_open_files(&args, argc, argv);
	ft_parse_cmds(&args, argv, envp);
	manage_pipes(&args, envp);
}
