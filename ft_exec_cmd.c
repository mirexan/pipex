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

static int	is_outfile_argument(char **cmd_args, char *outfile)
{
	int i;// en el caso de que en cmd shell no redireccionemos outfile y sea un argumento

	i = 0;
	if (!cmd_args)
		return 0;
	while (cmd_args[i + 1])
		i++;
	return (ft_strcmp(cmd_args[i], outfile) == 0);
}

static void	child_process(t_args *args, int i)
{
	if (i == 0)//volcar contenido de infile en stdin
	{
		if (args->fd_infile >= 0)
			dup2(args->fd_infile, STDIN_FILENO);//fd de infile se guarda en stdin
		else
		{
			args->fd_infile = open("/dev/null", O_RDONLY);//infile vacio, asign. null
			if (args->fd_infile < 0)
				handle_error("open /dev/null failed", NULL, args);
			dup2(args->fd_infile, STDIN_FILENO);
		}
		dup2(args->pipes_fd[1], STDOUT_FILENO);//el lado de escritura del pipe se guarda
	}//en el stdout del proceso
	else if (i == args->cmd_count - 1)
	{
		dup2(args->pipes_fd[0], STDIN_FILENO);
		if (!is_outfile_argument(args->cmd_args[i], args->outfile_name))
			dup2(args->fd_outfile, STDOUT_FILENO);
	}
	close(args->pipes_fd[0]);
	close(args->pipes_fd[1]);
}

void ft_exec_cmd(t_args *args,char **envp, int i)
{	
	args->pid[i] = fork();
	if (args->pid[i] < 0)
		handle_error("fork failed", NULL,args);
	if (args->pid[i] == 0)//proceso hijo, se pasa por ambos, ya que 
	//uno tendra pid == 0 y el otro no, pero se ejecuta el codigo por cada proceso
	{
		if (args->cmd_count == 1)
		{
			dup2(args->fd_infile, STDIN_FILENO);
			dup2(args->fd_outfile, STDOUT_FILENO);
			close(args->fd_infile);
			close(args->fd_outfile);
		}
		else
			child_process(args, i);
		execve(args->cmd_paths[i], args->cmd_args[i], envp);
		handle_error("execve failed", NULL, args);//si execve funciona termina el proceso
	}
}
