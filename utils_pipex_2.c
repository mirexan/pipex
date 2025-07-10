/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:22:59 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/27 18:23:01 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_paths(char *cmd, char **paths)
{
	char	*joined = NULL;
	char	*full_path = NULL;
	int		i;

	i = 0;
	
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");// "/usr/bin"+ "/"
		//printf("MALLOC joined %p (%s)\n", joined, joined);
		full_path = ft_strjoin(joined, cmd);// /usr/bin/ls
		//printf("MALLOC full_path %p (%s)\n", full_path, full_path);
		if (joined != full_path)
		{
			free(joined);
			//printf("FREE joined %p\n", joined);
		}
		if (access(full_path, X_OK) == 0)//si es ejecutable
		{
			//printf("FREE_ARRAY paths %p\n", paths);
			free_array(paths, 0);//se libera el array de strings paths del split 
			//printf("RETURNING full_path %p\n", full_path);
			return (full_path);//devolvemos ruta valida
		}
		free(full_path);//liberamos full_path no ejecutable
		//printf("FREE full_path %p\n", full_path);
		i++;
	}
	return (NULL);
}
/*los printf son para el control de leaks tras los alocamientos de strjoin*/

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++; // situamos el puntero en la linea que contiene PATH=/usr/local/bin:/usr/bin:/bin
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');//guardamos array de strings con los paths
	if (!paths)//array ={/usr/local/bin, /usr/bin , /bin, NULL}
		return (NULL);
	full_path = check_paths(cmd, paths);
	if (!full_path)
	{
		free_array(paths, 0);
		return (NULL);
	}
	return (full_path);
}

void	ft_parse_cmds(t_args *args, char **argv, char **envp)
{
	int	i;

	i = 0;
	args->cmd_paths = malloc(sizeof(char *) * (args->cmd_count + 1));
	args->cmd_args = malloc(sizeof(char **) * (args->cmd_count + 1));
	while (i < args->cmd_count)
	{
		args->cmd_args[i] = ft_split(argv[i + 2], ' ');
		//printf("SPLIT cmd_args[%d]: %p\n", i, args->cmd_args[i]);
		if (!args->cmd_args[i])
		{
			print_error(argv[i + 2]);
			args->cmd_paths[i] = NULL;
		}
		else
		{
			args->cmd_paths[i] = get_cmd_path(args->cmd_args[i][0], envp);
			//printf("CMD_PATHS[%d]: %p (%s)\n", i, args->cmd_paths[i], args->cmd_paths[i]);
		}
		i++;
	}
	args->cmd_paths[i] = NULL;
	args->cmd_args[i] = NULL;
}
