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

// execve() 	- executes the specified program with the specified argv and envp variables
//				  (if envp == NONE, the same environment parameters are used)
//				  this function replaces the current process image

// dup()		- creates a copy of a file descriptor using the lowest, unused number

// dup2()		- creates a copy of a file descriptor using the number passed as arg
//				  can use this to redirect printf from stdoutput to file2

// fork()		- creates a new (child) process by duplicating the calling process
//			  	  can be used to stop execve from overwriting our main process image

// pipe()		- redirects an output as input to another process
//				  can create a communication channel between parent & child processes

// perror()		- writes the error message arg to stderror

// strerror()	- returns a pointer to the textual representation of the error number arg

// access()		- checks whether a file is accessible for the specified mode

// unlink()		- removes the link to the specified file
//				  (if the no. fd's for a file drops to 0, its content can be overwritten)

// wait()		- suspend the calling process until a child process is complete

// waitpid()	- same as wait() but specifies the specific child process ID (PID)


void	ft_exec(char *cmd)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	cmd_path = ft_strjoin("/bin/", cmd_args[0]);
	if (execve(cmd_path, cmd_args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	pipe_infile_to_cmd(int pipe_fd[2], int fd_infile, char *cmd)
{
	close(pipe_fd[0]);
	dup2(fd_infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	ft_exec(cmd);
}

void	pipe_cmd_to_outfile(int pipe_fd[2], int fd_outfile, char *cmd)
{
	close(pipe_fd[1]);
	wait(0);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_outfile, STDOUT_FILENO);
	ft_exec(cmd);
}

int	main(int argc, char **argv)
{
	int		fd_infile;
	int		fd_outfile;
	pid_t	pid;
	int		pipe_fd[2];

	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[argc - 1], O_WRONLY, O_TRUNC, O_CREAT, 0644);
	if (fd_infile == -1 || fd_outfile == -1 || argc < 5)
	{
		perror("Invalid input");
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		pipe_infile_to_cmd(pipe_fd, fd_infile, argv[2]);
	pipe_cmd_to_outfile(pipe_fd, fd_outfile, argv[3]);	
}