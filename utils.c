/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:03:22 by eamsalem          #+#    #+#             */
/*   Updated: 2024/07/07 15:03:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**parse_path_var(char **envp)
{
	char	**file_paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			file_paths = ft_split(envp[i], ':');
		i++;
	}
	file_paths[0] = ft_strtrunc_front(file_paths[0], 5);
	return (file_paths);
}

char	*find_cmd_path(char *cmd, char **envp)
{
	char	**file_paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	file_paths = parse_path_var(envp);
	i = 0;
	while (file_paths[i])
	{
		tmp = ft_strjoin(file_paths[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(cmd_path, F_OK) != -1)
		{
			free_2d_arr((void **)file_paths, ft_2d_arrlen((void **)file_paths));
			return (cmd_path);
		}
		i++;
	}
	free_2d_arr((void **)file_paths, ft_2d_arrlen((void **)file_paths));
	return (NULL);
}

char	**parse_cmds(int argc, char **argv, int i)
{
	char	**cmds;
	int		len;
	int		j;

	cmds = malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		return (NULL);
	j = 0;
	while (i < argc - 1)
	{
		len = ft_strlen(argv[i]);
		cmds[j] = malloc(sizeof(char) * (len + 1));
		if (!cmds[j])
		{
			free_2d_arr((void *)cmds, j - 1);
			return (NULL);
		}
		ft_strlcpy(cmds[j++], argv[i++], (len + 1));
	}
	cmds[j] = NULL;
	return (cmds);
}

void	ft_exec(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	**allocate_pipe_fd(int size)
{
	int	i;
	int	**pipe_fd;

	if (size < 1)
		return (NULL);
	pipe_fd = malloc(sizeof(int *) * (size + 1));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
		{
			free_2d_arr((void *)pipe_fd, i - 1);
			return (NULL);
		}
		i++;
	}
	pipe_fd[size] = NULL;
	return (pipe_fd);
}
