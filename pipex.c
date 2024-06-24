/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:20:52 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/17 11:27:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/usr/bin/", cmd_args[0]);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

char	**parse_cmds(int argc, char **argv)
{
	char	**cmds;
	int		len;
	int		i;
	int		j;

	cmds = malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		return (NULL);
	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		len = ft_strlen(argv[i]);
		cmds[j] = malloc(sizeof(char) * (len + 1));
		if (!cmds[j])
		{
			free_2D_arr(cmds, j - 1);
			return (NULL);
		}
		ft_strlcpy(cmds[j++], argv[i++], (len + 1));
	}
	cmds[j] = NULL;
	return (cmds);
}

int	**allocate_pipe_fd(int cmd_count)
{
	int	i;
	int	**pipe_fd;

	pipe_fd = malloc(sizeof(int *) * (cmd_count + 1));
	i = 0;
	while (i < cmd_count)
		pipe_fd[i++] = malloc(sizeof(int) * 2);
	pipe_fd[cmd_count] = NULL;
	return (pipe_fd);
}

int	main(int argc, char **argv)
{
	int		fd_in;
	int		fd_out;
	int		**pipe_fd;
	char	**cmds;
	int		i;

	cmds = parse_cmds(argc, argv);
	if (!cmds)
		return (-1);
	check_input(argc, argv, cmds);
	pipe_fd = allocate_pipe_fd(ft_2D_arrlen(cmds));
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc -1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pipe_infile_to_cmd(pipe_fd[0], fd_in, cmds[0]);
	i = 1;
	while (cmds[i + 1])
	{
		wait(0);
		pipe_cmd_to_cmd(pipe_fd, cmds[i], i);
		i++;
	}
	pipe_cmd_to_outfile(pipe_fd[i - 1], fd_out, cmds[i]);
}
