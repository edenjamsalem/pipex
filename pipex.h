/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:21:10 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/17 11:21:50 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/wait.h> 

void	check_input(int argc, char **argv, char **cmds);

pid_t	pipe_fork(int pipe_fd[2]);

void	pipe_infile_to_cmd(int pipe_fd[2], int fd_in, char *cmd);

void	pipe_cmd_to_cmd(int **pipe_fd, char *cmd, int i);

void	pipe_cmd_to_outfile(int pipe_fd[2], int fd_out, char *cmd);

void	ft_exec(char *cmd);