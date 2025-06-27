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
	char	*joined;
	char	*full_path;
	int	i;
	
	i = 0;
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");// "/usr/bin"+ "/"
		full_path = ft_strjoin(joined, cmd);
		free(joined);
		if (access(full_path,X_OK) == 0) ///es ejecutable
		{
			free_array(paths);//se libera el array de strings paths del split 
			return (full_path);//devolvemos ruta valida
		}
		free(full_path);//liberamos full_path no ejecutable
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char **paths;
	char *full_path;
	
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;// encontrar la linea que contiene PATH=/usr/local/bin:/usr/bin:/bin
	if(!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');//guardamos array de strings con los paths
	if (!paths)
		return (NULL);//array ={/usr/local/bin, /usr/bin , /bin, NULL}
	full_path = check_paths(cmd, paths);
	if(!full_path)
	{
		free_array(paths);
		return (NULL);
	}	
	return (full_path);
}

void	ft_parse_cmds(t_args *args, char **argv, char **envp)
{
	int i;
	
	i = 0;
	args->cmd_paths = malloc(sizeof(char *) * (args->cmd_count + 1));
	args->cmd_args = malloc(sizeof(char **) * (args->cmd_count + 1));
	while (i < args->cmd_count)
	{
		args->cmd_args[i] = ft_split(argv[i + 2], ' ');
		if(!args->cmd_args[i])
			handle_error("Malloc or split failed", args);
		args->cmd_paths[i] = get_cmd_path(args->cmd_args[i][0], envp);
		if(!args->cmd_paths[i])
			handle_error("Command not found: ", args->cmd_args[i][0],args);
		i++;
	}
	args->cmd_paths[i] = NULL;
	args->cmd_args[i] = NULL;
	
}
