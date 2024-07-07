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

int	get_here_doc_input(char *limiter)
{
	pid_t	pid;
	char	input[4096];
	int		bytes_read;
	int		pipe_fd[2];

	pid = pipe_fork(pipe_fd);
	if (!pid)
	{
		close(pipe_fd[0]);
		while (1)
		{
			write(1, "> ", 2);
			bytes_read = read(STDIN_FILENO, input, 4096);
			if (ft_strncmp(input, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(pipe_fd[1], input, bytes_read);
		}
	}
	close(pipe_fd[1]);
	wait(0);
	return (pipe_fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	int		**pipe_fd;
	char	**cmds;
	int		i;

	check_input(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		cmds = parse_cmds(argc, argv, 3);
		pipe_fd = allocate_pipe_fd(ft_2d_arrlen((void *)cmds));
		fd_in = get_here_doc_input(argv[2]);
		fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		cmds = parse_cmds(argc, argv, 2);
		pipe_fd = allocate_pipe_fd(ft_2d_arrlen((void *)cmds));
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	pipe_infile_to_cmd(pipe_fd[0], fd_in, cmds[0], envp);
	i = 1;
	while (cmds[i + 1])
		pipe_cmd_to_cmd(pipe_fd, cmds, i++, envp);
	pipe_cmd_to_outfile(pipe_fd[i - 1], fd_out, cmds[i], envp);
}
