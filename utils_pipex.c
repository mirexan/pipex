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
{
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
//imprime error y cierra con 1

void	free_array(char **arr, int size)
{
	int	i;
	
	i = 0;
	if (!arr)
		return ;
	if (size == 0)
		while (arr[i])
		{
			//printf("FREE arr[%d] %p (%s)\n", i, arr[i], arr[i]);
			free(arr[i++]);
		}
	else
		while (i < size)
		{
			if (arr[i])
			{
				//printf("FREE arr[%d] %p (%s)\n", i, arr[i], arr[i]);
				free(arr[i]);
			}
			i++;
		}
	//printf("FREE arr %p\n", arr);
	free(arr);
}
/*todos los printf son para el control de leaks, se ha modificado esta funcion para que
borre el contenido de un array en funcion del tamano indicado en size excepto si se indica
que este es 0, cuyo caso interpreta que tenemos que realizar free hasta encontrar null*/

void	ft_cleanup(t_args *args)
{
	int	i;

	i = 0;
	if (args->fd_infile != -1)
		close(args->fd_infile);
	if (args->fd_outfile != -1)
		close(args->fd_outfile);
	if (args->cmd_paths)
		free_array(args->cmd_paths, args->cmd_count);
	if (args->pid)
		free(args->pid);
	if (args->cmd_args)
	{
		while (args->cmd_args[i])
		{
			free_array(args->cmd_args[i],0);
			i++;
		}
		//printf("FREE cmd_args %p \n", args->cmd_args);
		free(args->cmd_args);
	}
}

void	print_error(char *file_name)
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
		print_error(argv[1]);
	args->fd_outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (args->fd_outfile < 0)
	{
		print_error(argv[argc - 1]);
		ft_cleanup(args);
		exit(EXIT_FAILURE);
	}
}
