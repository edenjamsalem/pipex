/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:33:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/24 14:33:15 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	pipe_fork(int pipe_fd[2])
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	pipe_infile_to_cmd(int pipe_fd[2], int fd_in, char *cmd)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_exec(cmd);
	}
	close(pipe_fd[1]);
}

void	pipe_cmd_to_cmd(int **pipe_fd, char *cmd, int i)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd[i]);
	if (pid == 0)
	{
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		close(pipe_fd[i][0]);
		dup2(pipe_fd[i][1], STDOUT_FILENO);
		ft_exec(cmd);
	}
	close(pipe_fd[i][1]);
}

void	pipe_cmd_to_outfile(int pipe_fd[2], int fd_out, char *cmd)
{
	wait(0);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_exec(cmd);
}
