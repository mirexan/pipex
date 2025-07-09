/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:29:10 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/28 11:29:35 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_outfile_argument(char **cmd_args, char *outfile)// Evitar que pipex sobrescriba el archivo de salida si ya se está utilizando como argumento del comando.
{
	int	i;

	i = 0;
	if (!cmd_args)
		return (0);
	while (cmd_args[i + 1])
		i++;
	return (ft_strcmp(cmd_args[i], outfile) == 0);
}

static void	child_process(t_args *args, int i)
{
	if (i == 0)
	{
		if (args->fd_infile >= 0)
			dup2(args->fd_infile, STDIN_FILENO);
		else
		{
			args->fd_infile = open("/dev/null", O_RDONLY);
			if (args->fd_infile < 0)
				print_error("infile");
			dup2(args->fd_infile, STDIN_FILENO);
		}
		dup2(args->pipes_fd[1], STDOUT_FILENO);
	}
	else if (i == args->cmd_count - 1)
	{
		dup2(args->pipes_fd[0], STDIN_FILENO);
		if (!is_outfile_argument(args->cmd_args[i], args->outfile_name))
			dup2(args->fd_outfile, STDOUT_FILENO);
	}
	close(args->pipes_fd[0]);
	close(args->pipes_fd[1]);
}

static void	check_parameters(t_args *args, int i, char **envp)
{
	if (!args->cmd_paths[i] || !args->cmd_args[i]
		|| !args->cmd_args[i][0] || !envp || !envp[0])
	{
		print_error(args->cmd_args[i][0]);
		exit(127);
	}
}

void	ft_exec_cmd(t_args *args, char **envp, int i)
{
	args->pid[i] = fork();
	if (args->pid[i] < 0)
		handle_error("fork failed", NULL, args);
	if (args->pid[i] == 0)//proceso hijo
	{
		if (args->cmd_count == 1)//si solo tenemos un cmd
		{
			if (args->fd_infile < 0)
			{
				args->fd_infile = open("/dev/null", O_RDONLY);
				if (args->fd_infile < 0)
					print_error("infile");
			}
			dup2(args->fd_infile, STDIN_FILENO);
			dup2(args->fd_outfile, STDOUT_FILENO);
			close(args->fd_infile);
			close(args->fd_outfile);
		}
		else
			child_process(args, i);
		check_parameters(args, i, envp);
		execve(args->cmd_paths[i], args->cmd_args[i], envp);
		perror("pipex: Command not found");
		exit (127);
	}
}
