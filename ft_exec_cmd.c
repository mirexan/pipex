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

static void	child_process(t_args *args,char **envp, int i)
{
	if (i == 0)//volcar contenido de infile en stdin
	{
		if (args->fd_infile >= 0)
			dup2(args->fd_infile, STDIN_FILENO);
		else
		{
			args->fd_infile = open("/dev/null", O_RDONLY);
			if (args->fd_infile < 0)
				handle_error("open /dev/null failed", NULL, args);
			dup2(args->fd_infile, STDIN_FILENO);
			close(args->fd_infile);
		}
		dup2(args->pipes_fd[1], STDOUT_FILENO);
	}	
	else if (i == args->cmd_count - 1)
	{
		dup2(args->pipes_fd[0], STDIN_FILENO);
		dup2(args->fd_outfile, STDOUT_FILENO);
	}
	close(args->pipes_fd[0]);
	close(args->pipes_fd[1]);
	execve(args->cmd_paths[i], args->cmd_args[i], envp);
	handle_error("execve failed", NULL, args);//si execve funciona termina el proceso
}

void ft_exec_cmd(t_args *args,char **envp, int i)
{	
	args->pid[i] = fork();
	if (args->pid[i] < 0)
		handle_error("fork failed", NULL,args);
	if (args->pid[i] == 0)//proceso hijo, se pasa por ambos, ya que 
	//uno tendra pid == 0 y el otro no, pero se ejecuta el codigo por cada proceso
	{
		child_process(args, envp, i);
	}
}
