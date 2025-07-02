/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:24:26 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/21 16:24:31 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(char *error_text, char *detail, t_args *args)
{//imprime error y cierra con 1
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(error_text, 2);
	if (detail)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(detail, 2);
	}
	ft_putstr_fd("\n", 2);
	ft_cleanup(args);
	exit(1);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_cleanup(t_args *args)
{
	int	i;

	i = 0;
	if (args->fd_infile != -1)
		close(args->fd_infile);
	if (args->fd_outfile != -1)
		close(args->fd_outfile);
	if (args->cmd_paths)
		free_array(args->cmd_paths);
	if (args->pid)
		free(args->pid);
	if (args->cmd_args)
	{
		while (args->cmd_args[i])
		{
			free_array(args->cmd_args[i]);
			i++;
		}
		free(args->cmd_args);
	}
}

void	print_error(char *file_name)//imprime error
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_open_files(t_args *args, int argc, char **argv)
{
	args->fd_infile = open(argv[1], O_RDONLY);
	if (args->fd_infile < 0)
		print_error(argv[1]); // imprime error pero no cerramos
	args->fd_outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (args->fd_outfile < 0)//en cambio si falla outfile
	{//si que se trata de un error critico
		print_error(argv[argc - 1]);
		ft_cleanup(args);
		exit(EXIT_FAILURE);
	}
}
