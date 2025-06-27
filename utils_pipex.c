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
static void free_array(t_args *args)
{
	int i;
	
	i = 0;
	while (args->cmd_paths[i])
		{
			free(*args->cmd_paths[i]);
			i++;
		}
		free(args->cmd_paths);
}

void	ft_cleanup(t_args *args)
{
	int i;
	
	i = 0;
	if(args->fd_infile != -1)
		close(args->fd_infile);
	if(args->fd_outfile != -1)
		close(args->fd_outfile);
	if(args->cmd_paths)
		free_array(args);
	if(args->cmd_args)
	{
		while(args->cmd_args[i])
		{
			free_array(cmd_args[i]);
			i++;
		}
		free(args->cmd_args);
	}
}
